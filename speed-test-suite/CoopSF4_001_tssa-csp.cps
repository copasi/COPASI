<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.30 (Build 237) (http://www.copasi.org) at 2020-12-31T22:40:58Z -->
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
    <Function key="Function_142" name="transcr 3 inh 9 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_142">
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
        <ParameterDescription key="FunctionParameter_3262" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3261" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3260" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3259" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3258" name="A5" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3257" name="A6" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3256" name="A7" order="6" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3255" name="A8" order="7" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3254" name="A9" order="8" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3253" name="I1" order="9" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3252" name="I2" order="10" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3251" name="I3" order="11" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3250" name="V" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_3249" name="Ka1" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_3248" name="na1" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_3247" name="Ka2" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_3246" name="na2" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_3245" name="Ka3" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_3244" name="na3" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_3243" name="Ka4" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_3242" name="na4" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_3241" name="Ka5" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_3240" name="na5" order="22" role="constant"/>
        <ParameterDescription key="FunctionParameter_3239" name="Ka6" order="23" role="constant"/>
        <ParameterDescription key="FunctionParameter_3238" name="na6" order="24" role="constant"/>
        <ParameterDescription key="FunctionParameter_3237" name="Ka7" order="25" role="constant"/>
        <ParameterDescription key="FunctionParameter_3236" name="na7" order="26" role="constant"/>
        <ParameterDescription key="FunctionParameter_3235" name="Ka8" order="27" role="constant"/>
        <ParameterDescription key="FunctionParameter_3234" name="na8" order="28" role="constant"/>
        <ParameterDescription key="FunctionParameter_3233" name="Ka9" order="29" role="constant"/>
        <ParameterDescription key="FunctionParameter_3232" name="na9" order="30" role="constant"/>
        <ParameterDescription key="FunctionParameter_3231" name="Ki1" order="31" role="constant"/>
        <ParameterDescription key="FunctionParameter_3230" name="ni1" order="32" role="constant"/>
        <ParameterDescription key="FunctionParameter_3229" name="Ki2" order="33" role="constant"/>
        <ParameterDescription key="FunctionParameter_3228" name="ni2" order="34" role="constant"/>
        <ParameterDescription key="FunctionParameter_3227" name="Ki3" order="35" role="constant"/>
        <ParameterDescription key="FunctionParameter_3226" name="ni3" order="36" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_132" name="transcr 2 inh 5 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_132">
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
        <ParameterDescription key="FunctionParameter_3189" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3190" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3191" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3192" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3193" name="A5" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3194" name="I1" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3195" name="I2" order="6" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3196" name="V" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_3197" name="Ka1" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_3198" name="na1" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_3199" name="Ka2" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_3200" name="na2" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_3201" name="Ka3" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_3202" name="na3" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_3203" name="Ka4" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_3204" name="na4" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_3205" name="Ka5" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_3206" name="na5" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_3207" name="Ki1" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_3208" name="ni1" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_3209" name="Ki2" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_3210" name="ni2" order="21" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_131" name="transcr 7 inh 8 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_131">
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
        <ParameterDescription key="FunctionParameter_3182" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3183" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3184" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3185" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3186" name="A5" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3187" name="A6" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3188" name="A7" order="6" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3225" name="A8" order="7" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3224" name="I1" order="8" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3223" name="I2" order="9" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3222" name="I3" order="10" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3221" name="I4" order="11" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3220" name="I5" order="12" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3219" name="I6" order="13" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3218" name="I7" order="14" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3217" name="V" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_3216" name="Ka1" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_3215" name="na1" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_3214" name="Ka2" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_3213" name="na2" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_3212" name="Ka3" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_3211" name="na3" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_3181" name="Ka4" order="22" role="constant"/>
        <ParameterDescription key="FunctionParameter_3180" name="na4" order="23" role="constant"/>
        <ParameterDescription key="FunctionParameter_3179" name="Ka5" order="24" role="constant"/>
        <ParameterDescription key="FunctionParameter_3178" name="na5" order="25" role="constant"/>
        <ParameterDescription key="FunctionParameter_3177" name="Ka6" order="26" role="constant"/>
        <ParameterDescription key="FunctionParameter_3176" name="na6" order="27" role="constant"/>
        <ParameterDescription key="FunctionParameter_3175" name="Ka7" order="28" role="constant"/>
        <ParameterDescription key="FunctionParameter_3174" name="na7" order="29" role="constant"/>
        <ParameterDescription key="FunctionParameter_3173" name="Ka8" order="30" role="constant"/>
        <ParameterDescription key="FunctionParameter_3172" name="na8" order="31" role="constant"/>
        <ParameterDescription key="FunctionParameter_3171" name="Ki1" order="32" role="constant"/>
        <ParameterDescription key="FunctionParameter_3170" name="ni1" order="33" role="constant"/>
        <ParameterDescription key="FunctionParameter_3169" name="Ki2" order="34" role="constant"/>
        <ParameterDescription key="FunctionParameter_3168" name="ni2" order="35" role="constant"/>
        <ParameterDescription key="FunctionParameter_3167" name="Ki3" order="36" role="constant"/>
        <ParameterDescription key="FunctionParameter_3166" name="ni3" order="37" role="constant"/>
        <ParameterDescription key="FunctionParameter_3165" name="Ki4" order="38" role="constant"/>
        <ParameterDescription key="FunctionParameter_3164" name="ni4" order="39" role="constant"/>
        <ParameterDescription key="FunctionParameter_3163" name="Ki5" order="40" role="constant"/>
        <ParameterDescription key="FunctionParameter_3162" name="ni5" order="41" role="constant"/>
        <ParameterDescription key="FunctionParameter_3161" name="Ki6" order="42" role="constant"/>
        <ParameterDescription key="FunctionParameter_3160" name="ni6" order="43" role="constant"/>
        <ParameterDescription key="FunctionParameter_3159" name="Ki7" order="44" role="constant"/>
        <ParameterDescription key="FunctionParameter_3158" name="ni7" order="45" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_130" name="transcr 1 inh 3 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_130">
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
        <ParameterDescription key="FunctionParameter_3112" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3113" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3114" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3115" name="I1" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3116" name="V" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_3117" name="Ka1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_3118" name="na1" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_3119" name="Ka2" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_3120" name="na2" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_3121" name="Ka3" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_3122" name="na3" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_3123" name="Ki1" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_3124" name="ni1" order="12" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_129" name="transcr 5 inh 4 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_129">
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
        <ParameterDescription key="FunctionParameter_3137" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3136" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3135" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3134" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3133" name="I1" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3132" name="I2" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3131" name="I3" order="6" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3130" name="I4" order="7" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3129" name="I5" order="8" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3128" name="V" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_3127" name="Ka1" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_3126" name="na1" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_3125" name="Ka2" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_3138" name="na2" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_3139" name="Ka3" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_3140" name="na3" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_3141" name="Ka4" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_3142" name="na4" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_3143" name="Ki1" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_3144" name="ni1" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_3145" name="Ki2" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_3146" name="ni2" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_3147" name="Ki3" order="22" role="constant"/>
        <ParameterDescription key="FunctionParameter_3148" name="ni3" order="23" role="constant"/>
        <ParameterDescription key="FunctionParameter_3149" name="Ki4" order="24" role="constant"/>
        <ParameterDescription key="FunctionParameter_3150" name="ni4" order="25" role="constant"/>
        <ParameterDescription key="FunctionParameter_3151" name="Ki5" order="26" role="constant"/>
        <ParameterDescription key="FunctionParameter_3152" name="ni5" order="27" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_128" name="transcr 0 inh 1 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_128">
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
        <ParameterDescription key="FunctionParameter_3089" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3090" name="V" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_3091" name="Ka1" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_3092" name="na1" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_127" name="transcr 2 inh 4 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_127">
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
        <ParameterDescription key="FunctionParameter_3096" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3095" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3094" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3093" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3097" name="I1" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3098" name="I2" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3099" name="V" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_3100" name="Ka1" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_3101" name="na1" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_3102" name="Ka2" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_3103" name="na2" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_3104" name="Ka3" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_3105" name="na3" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_3106" name="Ka4" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_3107" name="na4" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_3108" name="Ki1" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_3109" name="ni1" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_3110" name="Ki2" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_3111" name="ni2" order="18" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_126" name="transcr 3 inh 5 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_126">
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
        <ParameterDescription key="FunctionParameter_3075" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3076" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3077" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3078" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3079" name="A5" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3080" name="I1" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3081" name="I2" order="6" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3082" name="I3" order="7" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3083" name="V" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_3084" name="Ka1" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_3085" name="na1" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_3086" name="Ka2" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_3087" name="na2" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_3088" name="Ka3" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_3153" name="na3" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_3154" name="Ka4" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_3155" name="na4" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_3156" name="Ka5" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_3157" name="na5" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_3074" name="Ki1" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_3073" name="ni1" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_3072" name="Ki2" order="21" role="constant"/>
        <ParameterDescription key="FunctionParameter_3071" name="ni2" order="22" role="constant"/>
        <ParameterDescription key="FunctionParameter_3070" name="Ki3" order="23" role="constant"/>
        <ParameterDescription key="FunctionParameter_3069" name="ni3" order="24" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_125" name="transcr 0 inh 2 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_125">
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
        <ParameterDescription key="FunctionParameter_3044" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3045" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3046" name="V" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_3047" name="Ka1" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_3048" name="na1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_3049" name="Ka2" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_3050" name="na2" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_124" name="transcr 3 inh 2 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_124">
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
        <ParameterDescription key="FunctionParameter_3057" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3056" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3055" name="I1" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3054" name="I2" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3053" name="I3" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3052" name="V" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_3051" name="Ka1" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_3058" name="na1" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_3059" name="Ka2" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_3060" name="na2" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_3061" name="Ki1" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_3062" name="ni1" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_3063" name="Ki2" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_3064" name="ni2" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_3065" name="Ki3" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_3066" name="ni3" order="15" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_123" name="transcr 1 inh 0 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_123">
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
        <ParameterDescription key="FunctionParameter_3030" name="I1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3031" name="V" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_3032" name="Ki1" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_3033" name="ni1" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_122" name="transcr 1 inh 4 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_122">
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
        <ParameterDescription key="FunctionParameter_3037" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3036" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3035" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3034" name="A4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3038" name="I1" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3039" name="V" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_3040" name="Ka1" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_3041" name="na1" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_3042" name="Ka2" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_3043" name="na2" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_3068" name="Ka3" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_3067" name="na3" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_3029" name="Ka4" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_3028" name="na4" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_3027" name="Ki1" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_3026" name="ni1" order="15" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_201" name="transcr 2 inh 0 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_201">
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
        <ParameterDescription key="FunctionParameter_3010" name="I1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3011" name="I2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3012" name="V" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_3013" name="Ki1" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_3014" name="ni1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_3015" name="Ki2" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_3016" name="ni2" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_202" name="transcr 5 inh 0 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_202">
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
        <ParameterDescription key="FunctionParameter_3023" name="I1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3022" name="I2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3021" name="I3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3020" name="I4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3019" name="I5" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_3018" name="V" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_3017" name="Ki1" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_3024" name="ni1" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_3025" name="Ki2" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_3009" name="ni2" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_3008" name="Ki3" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_3007" name="ni3" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_3006" name="Ki4" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_3005" name="ni4" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_3004" name="Ki5" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_3003" name="ni5" order="15" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_203" name="transcr 0 inh 3 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_203">
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
        <ParameterDescription key="FunctionParameter_2987" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2988" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2989" name="A3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2990" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_2991" name="Ka1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_2992" name="na1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_2993" name="Ka2" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_2994" name="na2" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_2995" name="Ka3" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_2996" name="na3" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_204" name="transcr 0 inh 0 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_204">
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
        <ParameterDescription key="FunctionParameter_2983" name="V" order="0" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_205" name="transcr 1 inh 1 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_205">
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
        <ParameterDescription key="FunctionParameter_2984" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2985" name="I1" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2986" name="V" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_3002" name="Ka1" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_3001" name="na1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_3000" name="Ki1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_2999" name="ni1" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_206" name="transcr 1 inh 2 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_206">
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
        <ParameterDescription key="FunctionParameter_2978" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2979" name="A2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2980" name="I1" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2981" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_2982" name="Ka1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_2997" name="na1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_2998" name="Ka2" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_2977" name="na2" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_2976" name="Ki1" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_2975" name="ni1" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_207" name="transcr 4 inh 0 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_207">
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
        <ParameterDescription key="FunctionParameter_2965" name="I1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2966" name="I2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2967" name="I3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2968" name="I4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2969" name="V" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_2970" name="Ki1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_2971" name="ni1" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_2972" name="Ki2" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_2973" name="ni2" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_2974" name="Ki3" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_2964" name="ni3" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_2963" name="Ki4" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_2962" name="ni4" order="12" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_208" name="transcr 2 inh 1 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_208">
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
        <ParameterDescription key="FunctionParameter_2949" name="A1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2950" name="I1" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2951" name="I2" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2952" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_2953" name="Ka1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_2954" name="na1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_2955" name="Ki1" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_2956" name="ni1" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_2957" name="Ki2" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_2958" name="ni2" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_209" name="transcr 3 inh 0 act (indp)" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_209">
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
        <ParameterDescription key="FunctionParameter_2942" name="I1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2943" name="I2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2944" name="I3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2945" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_2946" name="Ki1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_2947" name="ni1" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_2948" name="Ki2" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_2961" name="ni2" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_2960" name="Ki3" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_2959" name="ni3" order="9" role="constant"/>
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
      <Compartment key="Compartment_3" name="cell" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Compartment_3">
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
      <Metabolite key="Metabolite_458" name="G1" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_458">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_459" name="G2" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_459">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_460" name="G3" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_460">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_461" name="G4" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_461">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_462" name="G5" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_462">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_463" name="G6" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_463">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_464" name="G7" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_464">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_465" name="G8" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_465">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_466" name="G9" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_466">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_467" name="G10" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_467">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_468" name="G11" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_468">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_469" name="G12" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_469">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_470" name="G13" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_470">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_471" name="G14" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_471">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_472" name="G15" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_472">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_473" name="G16" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_473">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_474" name="G17" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_474">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_475" name="G18" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_475">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_476" name="G19" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_476">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_477" name="G20" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_477">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_478" name="G21" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_478">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_479" name="G22" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_479">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_480" name="G23" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_480">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_481" name="G24" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_481">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_482" name="G25" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_482">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_483" name="G26" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_483">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_484" name="G27" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_484">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_485" name="G28" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_485">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_486" name="G29" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_486">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_487" name="G30" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_487">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_488" name="G31" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_488">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_489" name="G32" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_489">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_490" name="G33" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_490">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_491" name="G34" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_491">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_492" name="G35" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_492">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_493" name="G36" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_493">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_494" name="G37" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_494">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_495" name="G38" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_495">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_496" name="G39" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_496">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_497" name="G40" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_497">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_498" name="G41" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_498">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_499" name="G42" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_499">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_500" name="G43" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_500">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_501" name="G44" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_501">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_502" name="G45" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_502">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_503" name="G46" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_503">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_504" name="G47" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_504">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_505" name="G48" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_505">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_506" name="G49" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_506">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_507" name="G50" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_507">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_508" name="G51" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_508">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_509" name="G52" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_509">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_510" name="G53" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_510">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_511" name="G54" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_511">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_512" name="G55" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_512">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_513" name="G56" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_513">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_514" name="G57" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_514">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_515" name="G58" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_515">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_516" name="G59" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_516">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_517" name="G60" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_517">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_518" name="G61" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_518">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_519" name="G62" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_519">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_520" name="G63" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_520">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_521" name="G64" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_521">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_522" name="G65" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_522">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_523" name="G66" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_523">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_524" name="G67" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_524">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_525" name="G68" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_525">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_526" name="G69" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_526">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_527" name="G70" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_527">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_528" name="G71" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_528">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_529" name="G72" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_529">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_530" name="G73" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_530">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_531" name="G74" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_531">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_532" name="G75" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_532">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_533" name="G76" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_533">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_534" name="G77" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_534">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_535" name="G78" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_535">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_536" name="G79" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_536">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_537" name="G80" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_537">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_538" name="G81" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_538">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_539" name="G82" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_539">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_540" name="G83" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_540">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_541" name="G84" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_541">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_542" name="G85" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_542">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_543" name="G86" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_543">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_544" name="G87" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_544">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_545" name="G88" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_545">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_546" name="G89" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_546">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_547" name="G90" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_547">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_548" name="G91" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_548">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_549" name="G92" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_549">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_550" name="G93" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_550">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_551" name="G94" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_551">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_552" name="G95" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_552">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_553" name="G96" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_553">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_554" name="G97" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_554">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_555" name="G98" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_555">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_556" name="G99" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_556">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_557" name="G100" simulationType="reactions" compartment="Compartment_3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_557">
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
      <Reaction key="Reaction_49" name="G1 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_49">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_458" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_535" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_458" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_461" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_462" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_534" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_467" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_474" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_497" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_504" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_518" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_465" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3782" name="V" value="5.8"/>
          <Constant key="Parameter_3904" name="Ka1" value="0.4"/>
          <Constant key="Parameter_3893" name="na1" value="4"/>
          <Constant key="Parameter_3779" name="Ka2" value="1e-06"/>
          <Constant key="Parameter_3894" name="na2" value="2.2"/>
          <Constant key="Parameter_3752" name="Ka3" value="42.4453"/>
          <Constant key="Parameter_3783" name="na3" value="4"/>
          <Constant key="Parameter_3754" name="Ka4" value="0.01"/>
          <Constant key="Parameter_3753" name="na4" value="4"/>
          <Constant key="Parameter_3755" name="Ka5" value="2"/>
          <Constant key="Parameter_3788" name="na5" value="4"/>
          <Constant key="Parameter_3751" name="Ka6" value="4e-05"/>
          <Constant key="Parameter_3781" name="na6" value="4"/>
          <Constant key="Parameter_3757" name="Ka7" value="0.01"/>
          <Constant key="Parameter_3769" name="na7" value="4"/>
          <Constant key="Parameter_3774" name="Ka8" value="0.01"/>
          <Constant key="Parameter_3799" name="na8" value="4"/>
          <Constant key="Parameter_3797" name="Ka9" value="0.01"/>
          <Constant key="Parameter_3855" name="na9" value="4"/>
          <Constant key="Parameter_3802" name="Ki1" value="0.008"/>
          <Constant key="Parameter_3803" name="ni1" value="4"/>
          <Constant key="Parameter_3801" name="Ki2" value="8.5"/>
          <Constant key="Parameter_3804" name="ni2" value="2.6"/>
          <Constant key="Parameter_3796" name="Ki3" value="123"/>
          <Constant key="Parameter_3857" name="ni3" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_142" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3262">
              <SourceParameter reference="Metabolite_535"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3261">
              <SourceParameter reference="Metabolite_458"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3260">
              <SourceParameter reference="Metabolite_461"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3259">
              <SourceParameter reference="Metabolite_462"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3258">
              <SourceParameter reference="Metabolite_534"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3257">
              <SourceParameter reference="Metabolite_467"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3256">
              <SourceParameter reference="Metabolite_474"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3255">
              <SourceParameter reference="Metabolite_497"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3254">
              <SourceParameter reference="Metabolite_504"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3253">
              <SourceParameter reference="Metabolite_518"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3252">
              <SourceParameter reference="Metabolite_465"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3251">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3250">
              <SourceParameter reference="Parameter_3782"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3249">
              <SourceParameter reference="Parameter_3904"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3248">
              <SourceParameter reference="Parameter_3893"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3247">
              <SourceParameter reference="Parameter_3779"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3246">
              <SourceParameter reference="Parameter_3894"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3245">
              <SourceParameter reference="Parameter_3752"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3244">
              <SourceParameter reference="Parameter_3783"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3243">
              <SourceParameter reference="Parameter_3754"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3242">
              <SourceParameter reference="Parameter_3753"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3241">
              <SourceParameter reference="Parameter_3755"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3240">
              <SourceParameter reference="Parameter_3788"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3239">
              <SourceParameter reference="Parameter_3751"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3238">
              <SourceParameter reference="Parameter_3781"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3237">
              <SourceParameter reference="Parameter_3757"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3236">
              <SourceParameter reference="Parameter_3769"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3235">
              <SourceParameter reference="Parameter_3774"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3234">
              <SourceParameter reference="Parameter_3799"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3233">
              <SourceParameter reference="Parameter_3797"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3232">
              <SourceParameter reference="Parameter_3855"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3231">
              <SourceParameter reference="Parameter_3802"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3230">
              <SourceParameter reference="Parameter_3803"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3229">
              <SourceParameter reference="Parameter_3801"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3228">
              <SourceParameter reference="Parameter_3804"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3227">
              <SourceParameter reference="Parameter_3796"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3226">
              <SourceParameter reference="Parameter_3857"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_48" name="G1 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_48">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_458" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3800" name="k1" value="1.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3800"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_458"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_47" name="G2 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_47">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_459" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_530" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_520" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_479" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_504" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_466" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_459" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3856" name="V" value="12300"/>
          <Constant key="Parameter_3858" name="Ka1" value="0.003"/>
          <Constant key="Parameter_3795" name="na1" value="4"/>
          <Constant key="Parameter_3798" name="Ka2" value="0.607897"/>
          <Constant key="Parameter_3861" name="na2" value="4"/>
          <Constant key="Parameter_3760" name="Ka3" value="0.152614"/>
          <Constant key="Parameter_4294" name="na3" value="4"/>
          <Constant key="Parameter_3770" name="Ka4" value="0.235689"/>
          <Constant key="Parameter_3777" name="na4" value="4"/>
          <Constant key="Parameter_3776" name="Ka5" value="12"/>
          <Constant key="Parameter_3763" name="na5" value="4"/>
          <Constant key="Parameter_3759" name="Ki1" value="0.490247"/>
          <Constant key="Parameter_3906" name="ni1" value="4"/>
          <Constant key="Parameter_3761" name="Ki2" value="0.000721363"/>
          <Constant key="Parameter_3891" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_132" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3189">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3190">
              <SourceParameter reference="Metabolite_530"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3191">
              <SourceParameter reference="Metabolite_520"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3192">
              <SourceParameter reference="Metabolite_479"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3193">
              <SourceParameter reference="Metabolite_504"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3194">
              <SourceParameter reference="Metabolite_466"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3195">
              <SourceParameter reference="Metabolite_459"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3196">
              <SourceParameter reference="Parameter_3856"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3197">
              <SourceParameter reference="Parameter_3858"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3198">
              <SourceParameter reference="Parameter_3795"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3199">
              <SourceParameter reference="Parameter_3798"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3200">
              <SourceParameter reference="Parameter_3861"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3201">
              <SourceParameter reference="Parameter_3760"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3202">
              <SourceParameter reference="Parameter_4294"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3203">
              <SourceParameter reference="Parameter_3770"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3204">
              <SourceParameter reference="Parameter_3777"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3205">
              <SourceParameter reference="Parameter_3776"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3206">
              <SourceParameter reference="Parameter_3763"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3207">
              <SourceParameter reference="Parameter_3759"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3208">
              <SourceParameter reference="Parameter_3906"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3209">
              <SourceParameter reference="Parameter_3761"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3210">
              <SourceParameter reference="Parameter_3891"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_46" name="G2 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_46">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_459" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3817" name="k1" value="0.031"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3817"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_459"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_45" name="G3 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_45">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_460" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_548" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_458" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_462" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_542" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_465" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_522" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_480" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_502" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_503" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_508" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_512" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_474" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_463" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_459" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_554" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3794" name="V" value="49"/>
          <Constant key="Parameter_3765" name="Ka1" value="12.243"/>
          <Constant key="Parameter_4173" name="na1" value="4"/>
          <Constant key="Parameter_3767" name="Ka2" value="3.25203e-08"/>
          <Constant key="Parameter_3768" name="na2" value="4"/>
          <Constant key="Parameter_3756" name="Ka3" value="5.673e-06"/>
          <Constant key="Parameter_3766" name="na3" value="4"/>
          <Constant key="Parameter_3771" name="Ka4" value="0.877014"/>
          <Constant key="Parameter_3772" name="na4" value="4"/>
          <Constant key="Parameter_3764" name="Ka5" value="0.008"/>
          <Constant key="Parameter_3773" name="na5" value="4"/>
          <Constant key="Parameter_3758" name="Ka6" value="1.73921e-12"/>
          <Constant key="Parameter_3762" name="na6" value="4"/>
          <Constant key="Parameter_3775" name="Ka7" value="7.1734"/>
          <Constant key="Parameter_3895" name="na7" value="4"/>
          <Constant key="Parameter_3793" name="Ka8" value="0.246835"/>
          <Constant key="Parameter_3778" name="na8" value="4"/>
          <Constant key="Parameter_3808" name="Ki1" value="4.74523e-07"/>
          <Constant key="Parameter_3806" name="ni1" value="4"/>
          <Constant key="Parameter_3812" name="Ki2" value="2.37538"/>
          <Constant key="Parameter_3820" name="ni2" value="4"/>
          <Constant key="Parameter_3811" name="Ki3" value="3.69e-05"/>
          <Constant key="Parameter_3810" name="ni3" value="4"/>
          <Constant key="Parameter_3809" name="Ki4" value="31962"/>
          <Constant key="Parameter_3807" name="ni4" value="4"/>
          <Constant key="Parameter_3805" name="Ki5" value="10.2279"/>
          <Constant key="Parameter_6636" name="ni5" value="4"/>
          <Constant key="Parameter_7360" name="Ki6" value="0.000391"/>
          <Constant key="Parameter_6640" name="ni6" value="4"/>
          <Constant key="Parameter_6628" name="Ki7" value="3.90854"/>
          <Constant key="Parameter_6171" name="ni7" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_131" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3182">
              <SourceParameter reference="Metabolite_548"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3183">
              <SourceParameter reference="Metabolite_458"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3184">
              <SourceParameter reference="Metabolite_462"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3185">
              <SourceParameter reference="Metabolite_542"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3186">
              <SourceParameter reference="Metabolite_465"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3187">
              <SourceParameter reference="Metabolite_522"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3188">
              <SourceParameter reference="Metabolite_480"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3225">
              <SourceParameter reference="Metabolite_502"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3224">
              <SourceParameter reference="Metabolite_503"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3223">
              <SourceParameter reference="Metabolite_508"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3222">
              <SourceParameter reference="Metabolite_512"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3221">
              <SourceParameter reference="Metabolite_474"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3220">
              <SourceParameter reference="Metabolite_463"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3219">
              <SourceParameter reference="Metabolite_459"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3218">
              <SourceParameter reference="Metabolite_554"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3217">
              <SourceParameter reference="Parameter_3794"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3216">
              <SourceParameter reference="Parameter_3765"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3215">
              <SourceParameter reference="Parameter_4173"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3214">
              <SourceParameter reference="Parameter_3767"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3213">
              <SourceParameter reference="Parameter_3768"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3212">
              <SourceParameter reference="Parameter_3756"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3211">
              <SourceParameter reference="Parameter_3766"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3181">
              <SourceParameter reference="Parameter_3771"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3180">
              <SourceParameter reference="Parameter_3772"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3179">
              <SourceParameter reference="Parameter_3764"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3178">
              <SourceParameter reference="Parameter_3773"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3177">
              <SourceParameter reference="Parameter_3758"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3176">
              <SourceParameter reference="Parameter_3762"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3175">
              <SourceParameter reference="Parameter_3775"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3174">
              <SourceParameter reference="Parameter_3895"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3173">
              <SourceParameter reference="Parameter_3793"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3172">
              <SourceParameter reference="Parameter_3778"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3171">
              <SourceParameter reference="Parameter_3808"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3170">
              <SourceParameter reference="Parameter_3806"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3169">
              <SourceParameter reference="Parameter_3812"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3168">
              <SourceParameter reference="Parameter_3820"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3167">
              <SourceParameter reference="Parameter_3811"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3166">
              <SourceParameter reference="Parameter_3810"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3165">
              <SourceParameter reference="Parameter_3809"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3164">
              <SourceParameter reference="Parameter_3807"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3163">
              <SourceParameter reference="Parameter_3805"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3162">
              <SourceParameter reference="Parameter_6636"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3161">
              <SourceParameter reference="Parameter_7360"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3160">
              <SourceParameter reference="Parameter_6640"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3159">
              <SourceParameter reference="Parameter_6628"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3158">
              <SourceParameter reference="Parameter_6171"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_44" name="G3 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_44">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_460" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6166" name="k1" value="0.008"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6166"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_43" name="G4 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_43">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_461" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_470" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_514" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_513" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_478" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6167" name="V" value="33"/>
          <Constant key="Parameter_4448" name="Ka1" value="0.122081"/>
          <Constant key="Parameter_6172" name="na1" value="3"/>
          <Constant key="Parameter_4390" name="Ka2" value="1.41285e-06"/>
          <Constant key="Parameter_4459" name="na2" value="3"/>
          <Constant key="Parameter_4383" name="Ka3" value="5.36239e-05"/>
          <Constant key="Parameter_4464" name="na3" value="3"/>
          <Constant key="Parameter_4451" name="Ki1" value="0.0184689"/>
          <Constant key="Parameter_4449" name="ni1" value="3"/>
        </ListOfConstants>
        <KineticLaw function="Function_130" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3112">
              <SourceParameter reference="Metabolite_470"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3113">
              <SourceParameter reference="Metabolite_514"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3114">
              <SourceParameter reference="Metabolite_513"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3115">
              <SourceParameter reference="Metabolite_478"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3116">
              <SourceParameter reference="Parameter_6167"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3117">
              <SourceParameter reference="Parameter_4448"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3118">
              <SourceParameter reference="Parameter_6172"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3119">
              <SourceParameter reference="Parameter_4390"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3120">
              <SourceParameter reference="Parameter_4459"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3121">
              <SourceParameter reference="Parameter_4383"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3122">
              <SourceParameter reference="Parameter_4464"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3123">
              <SourceParameter reference="Parameter_4451"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3124">
              <SourceParameter reference="Parameter_4449"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="G4 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_461" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4386" name="k1" value="0.06"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4386"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_461"/>
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
          <Product metabolite="Metabolite_462" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_548" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_476" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_482" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_550" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_513" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_531" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_532" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_507" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_464" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4391" name="V" value="43"/>
          <Constant key="Parameter_4467" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4460" name="na1" value="4"/>
          <Constant key="Parameter_4394" name="Ka2" value="0.12"/>
          <Constant key="Parameter_4456" name="na2" value="4"/>
          <Constant key="Parameter_4462" name="Ka3" value="0.01"/>
          <Constant key="Parameter_4393" name="na3" value="4"/>
          <Constant key="Parameter_4381" name="Ka4" value="0.07"/>
          <Constant key="Parameter_4468" name="na4" value="4"/>
          <Constant key="Parameter_4458" name="Ki1" value="23"/>
          <Constant key="Parameter_4380" name="ni1" value="4"/>
          <Constant key="Parameter_4409" name="Ki2" value="2.3e-05"/>
          <Constant key="Parameter_4457" name="ni2" value="4"/>
          <Constant key="Parameter_7189" name="Ki3" value="0.43"/>
          <Constant key="Parameter_4461" name="ni3" value="4"/>
          <Constant key="Parameter_4453" name="Ki4" value="0.143"/>
          <Constant key="Parameter_4463" name="ni4" value="4"/>
          <Constant key="Parameter_3150" name="Ki5" value="0.0004"/>
          <Constant key="Parameter_4274" name="ni5" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_129" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3137">
              <SourceParameter reference="Metabolite_548"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3136">
              <SourceParameter reference="Metabolite_476"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3135">
              <SourceParameter reference="Metabolite_482"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3134">
              <SourceParameter reference="Metabolite_550"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3133">
              <SourceParameter reference="Metabolite_513"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3132">
              <SourceParameter reference="Metabolite_531"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3131">
              <SourceParameter reference="Metabolite_532"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3130">
              <SourceParameter reference="Metabolite_507"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3129">
              <SourceParameter reference="Metabolite_464"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3128">
              <SourceParameter reference="Parameter_4391"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3127">
              <SourceParameter reference="Parameter_4467"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3126">
              <SourceParameter reference="Parameter_4460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3125">
              <SourceParameter reference="Parameter_4394"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3138">
              <SourceParameter reference="Parameter_4456"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3139">
              <SourceParameter reference="Parameter_4462"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3140">
              <SourceParameter reference="Parameter_4393"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3141">
              <SourceParameter reference="Parameter_4381"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3142">
              <SourceParameter reference="Parameter_4468"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3143">
              <SourceParameter reference="Parameter_4458"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3144">
              <SourceParameter reference="Parameter_4380"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3145">
              <SourceParameter reference="Parameter_4409"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3146">
              <SourceParameter reference="Parameter_4457"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3147">
              <SourceParameter reference="Parameter_7189"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3148">
              <SourceParameter reference="Parameter_4461"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3149">
              <SourceParameter reference="Parameter_4453"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3150">
              <SourceParameter reference="Parameter_4463"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3151">
              <SourceParameter reference="Parameter_3150"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3152">
              <SourceParameter reference="Parameter_4274"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="G5 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_462" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4465" name="k1" value="0.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4465"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_462"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="G6 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_463" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_458" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7356" name="V" value="1.2"/>
          <Constant key="Parameter_4385" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4454" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_458"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_7356"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_4385"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_4454"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="G6 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_463" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4396" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4396"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_463"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="G7 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_464" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_472" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_486" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_504" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_471" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_557" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_539" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7320" name="V" value="23"/>
          <Constant key="Parameter_3911" name="Ka1" value="6e-05"/>
          <Constant key="Parameter_3219" name="na1" value="4"/>
          <Constant key="Parameter_7317" name="Ka2" value="0.01"/>
          <Constant key="Parameter_3149" name="na2" value="4"/>
          <Constant key="Parameter_3429" name="Ka3" value="0.01"/>
          <Constant key="Parameter_3917" name="na3" value="4"/>
          <Constant key="Parameter_3319" name="Ka4" value="0.01"/>
          <Constant key="Parameter_3422" name="na4" value="4"/>
          <Constant key="Parameter_3916" name="Ki1" value="5"/>
          <Constant key="Parameter_4574" name="ni1" value="4"/>
          <Constant key="Parameter_3317" name="Ki2" value="0.01"/>
          <Constant key="Parameter_3310" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_127" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3096">
              <SourceParameter reference="Metabolite_472"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3095">
              <SourceParameter reference="Metabolite_486"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3094">
              <SourceParameter reference="Metabolite_504"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3093">
              <SourceParameter reference="Metabolite_471"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3097">
              <SourceParameter reference="Metabolite_557"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3098">
              <SourceParameter reference="Metabolite_539"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3099">
              <SourceParameter reference="Parameter_7320"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3100">
              <SourceParameter reference="Parameter_3911"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3101">
              <SourceParameter reference="Parameter_3219"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3102">
              <SourceParameter reference="Parameter_7317"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3103">
              <SourceParameter reference="Parameter_3149"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3104">
              <SourceParameter reference="Parameter_3429"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3105">
              <SourceParameter reference="Parameter_3917"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3106">
              <SourceParameter reference="Parameter_3319"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3107">
              <SourceParameter reference="Parameter_3422"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3108">
              <SourceParameter reference="Parameter_3916"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3109">
              <SourceParameter reference="Parameter_4574"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3110">
              <SourceParameter reference="Parameter_3317"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3111">
              <SourceParameter reference="Parameter_3310"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="G7 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_464" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3417" name="k1" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3417"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_464"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="G8 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_465" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_556" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_471" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_478" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_479" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_541" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_499" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_552" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_467" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3478" name="V" value="5.3"/>
          <Constant key="Parameter_3425" name="Ka1" value="0.1"/>
          <Constant key="Parameter_4581" name="na1" value="4"/>
          <Constant key="Parameter_7208" name="Ka2" value="19"/>
          <Constant key="Parameter_4590" name="na2" value="4"/>
          <Constant key="Parameter_3316" name="Ka3" value="0.811048"/>
          <Constant key="Parameter_3156" name="na3" value="3"/>
          <Constant key="Parameter_4559" name="Ka4" value="20"/>
          <Constant key="Parameter_3426" name="na4" value="4"/>
          <Constant key="Parameter_3421" name="Ka5" value="0.01"/>
          <Constant key="Parameter_4539" name="na5" value="4"/>
          <Constant key="Parameter_3309" name="Ki1" value="0.08"/>
          <Constant key="Parameter_3510" name="ni1" value="4"/>
          <Constant key="Parameter_4580" name="Ki2" value="1.7"/>
          <Constant key="Parameter_7185" name="ni2" value="3"/>
          <Constant key="Parameter_3910" name="Ki3" value="0.1"/>
          <Constant key="Parameter_4588" name="ni3" value="3.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_126" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3075">
              <SourceParameter reference="Metabolite_556"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3076">
              <SourceParameter reference="Metabolite_471"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3077">
              <SourceParameter reference="Metabolite_478"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3078">
              <SourceParameter reference="Metabolite_479"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3079">
              <SourceParameter reference="Metabolite_541"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3080">
              <SourceParameter reference="Metabolite_499"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3081">
              <SourceParameter reference="Metabolite_552"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3082">
              <SourceParameter reference="Metabolite_467"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3083">
              <SourceParameter reference="Parameter_3478"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3084">
              <SourceParameter reference="Parameter_3425"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3085">
              <SourceParameter reference="Parameter_4581"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3086">
              <SourceParameter reference="Parameter_7208"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3087">
              <SourceParameter reference="Parameter_4590"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3088">
              <SourceParameter reference="Parameter_3316"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3153">
              <SourceParameter reference="Parameter_3156"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3154">
              <SourceParameter reference="Parameter_4559"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3155">
              <SourceParameter reference="Parameter_3426"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3156">
              <SourceParameter reference="Parameter_3421"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3157">
              <SourceParameter reference="Parameter_4539"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3074">
              <SourceParameter reference="Parameter_3309"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3073">
              <SourceParameter reference="Parameter_3510"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3072">
              <SourceParameter reference="Parameter_4580"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3071">
              <SourceParameter reference="Parameter_7185"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3070">
              <SourceParameter reference="Parameter_3910"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3069">
              <SourceParameter reference="Parameter_4588"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="G8 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_465" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3157" name="k1" value="2.53"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3157"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_465"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="G9 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_466" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_465" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_540" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4555" name="V" value="1"/>
          <Constant key="Parameter_4043" name="Ka1" value="0.05"/>
          <Constant key="Parameter_3427" name="na1" value="4"/>
          <Constant key="Parameter_3666" name="Ka2" value="0.02"/>
          <Constant key="Parameter_4585" name="na2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_125" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3044">
              <SourceParameter reference="Metabolite_465"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3045">
              <SourceParameter reference="Metabolite_540"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3046">
              <SourceParameter reference="Parameter_4555"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3047">
              <SourceParameter reference="Parameter_4043"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3048">
              <SourceParameter reference="Parameter_3427"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3049">
              <SourceParameter reference="Parameter_3666"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3050">
              <SourceParameter reference="Parameter_4585"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="G9 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_26">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_466" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3500" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3500"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_466"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="G10 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_27">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_467" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_524" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_495" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_487" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_483" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_477" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3430" name="V" value="6"/>
          <Constant key="Parameter_3424" name="Ka1" value="1e-08"/>
          <Constant key="Parameter_3340" name="na1" value="4"/>
          <Constant key="Parameter_4569" name="Ka2" value="0.01"/>
          <Constant key="Parameter_3684" name="na2" value="4"/>
          <Constant key="Parameter_3676" name="Ki1" value="0.3"/>
          <Constant key="Parameter_3679" name="ni1" value="4"/>
          <Constant key="Parameter_3428" name="Ki2" value="0.01"/>
          <Constant key="Parameter_4537" name="ni2" value="4"/>
          <Constant key="Parameter_6094" name="Ki3" value="1e-05"/>
          <Constant key="Parameter_6125" name="ni3" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_124" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3057">
              <SourceParameter reference="Metabolite_524"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3056">
              <SourceParameter reference="Metabolite_495"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3055">
              <SourceParameter reference="Metabolite_487"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3054">
              <SourceParameter reference="Metabolite_483"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3053">
              <SourceParameter reference="Metabolite_477"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3052">
              <SourceParameter reference="Parameter_3430"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3051">
              <SourceParameter reference="Parameter_3424"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3058">
              <SourceParameter reference="Parameter_3340"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3059">
              <SourceParameter reference="Parameter_4569"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3060">
              <SourceParameter reference="Parameter_3684"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3061">
              <SourceParameter reference="Parameter_3676"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3062">
              <SourceParameter reference="Parameter_3679"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3063">
              <SourceParameter reference="Parameter_3428"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3064">
              <SourceParameter reference="Parameter_4537"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3065">
              <SourceParameter reference="Parameter_6094"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3066">
              <SourceParameter reference="Parameter_6125"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="G10 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_28">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_467" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3780" name="k1" value="0.7"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3780"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_467"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="G11 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_29">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_468" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_462" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6882" name="V" value="27"/>
          <Constant key="Parameter_6136" name="Ki1" value="5.4"/>
          <Constant key="Parameter_6127" name="ni1" value="2.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_123" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3030">
              <SourceParameter reference="Metabolite_462"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3031">
              <SourceParameter reference="Parameter_6882"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3032">
              <SourceParameter reference="Parameter_6136"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3033">
              <SourceParameter reference="Parameter_6127"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="G11 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_30">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_468" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6095" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6095"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_468"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="G12 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_31">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_469" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_467" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4444" name="V" value="1.2"/>
          <Constant key="Parameter_6128" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6877" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_467"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_4444"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_6128"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_6877"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="G12 degradation" reversible="false" fast="false" addNoise="false">
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
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_469" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6131" name="k1" value="1.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6131"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_469"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_42" name="G13 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_42">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_470" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_528" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_473" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_488" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_491" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6093" name="V" value="3.6"/>
          <Constant key="Parameter_4024" name="Ka1" value="1e-06"/>
          <Constant key="Parameter_3743" name="na1" value="4"/>
          <Constant key="Parameter_6873" name="Ka2" value="0.8"/>
          <Constant key="Parameter_6879" name="na2" value="4"/>
          <Constant key="Parameter_6088" name="Ka3" value="1e-06"/>
          <Constant key="Parameter_3503" name="na3" value="4"/>
          <Constant key="Parameter_3314" name="Ka4" value="2e-06"/>
          <Constant key="Parameter_3704" name="na4" value="4"/>
          <Constant key="Parameter_3198" name="Ki1" value="0.032"/>
          <Constant key="Parameter_3203" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_122" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3037">
              <SourceParameter reference="Metabolite_528"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3036">
              <SourceParameter reference="Metabolite_473"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3035">
              <SourceParameter reference="Metabolite_488"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3034">
              <SourceParameter reference="Metabolite_491"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3038">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3039">
              <SourceParameter reference="Parameter_6093"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3040">
              <SourceParameter reference="Parameter_4024"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3041">
              <SourceParameter reference="Parameter_3743"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3042">
              <SourceParameter reference="Parameter_6873"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3043">
              <SourceParameter reference="Parameter_6879"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3068">
              <SourceParameter reference="Parameter_6088"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3067">
              <SourceParameter reference="Parameter_3503"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3029">
              <SourceParameter reference="Parameter_3314"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3028">
              <SourceParameter reference="Parameter_3704"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3027">
              <SourceParameter reference="Parameter_3198"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3026">
              <SourceParameter reference="Parameter_3203"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_41" name="G13 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_41">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_470" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3521" name="k1" value="2.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3521"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_470"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_40" name="G14 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_40">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_471" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_467" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3311" name="V" value="1.6"/>
          <Constant key="Parameter_3677" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3210" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_467"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_3311"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_3677"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_3210"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_39" name="G14 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_39">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_471" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3205" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3205"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_471"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_38" name="G15 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_38">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_472" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_533" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3423" name="V" value="3"/>
          <Constant key="Parameter_3499" name="Ki1" value="12"/>
          <Constant key="Parameter_3208" name="ni1" value="4"/>
          <Constant key="Parameter_3207" name="Ki2" value="58"/>
          <Constant key="Parameter_3678" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_533"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_3423"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_3499"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_3208"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_3207"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_3678"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_37" name="G15 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_37">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_472" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3204" name="k1" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3204"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_472"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_36" name="G16 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_36">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_473" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_459" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_476" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_498" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_520" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_555" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3195" name="V" value="7"/>
          <Constant key="Parameter_3196" name="Ki1" value="933"/>
          <Constant key="Parameter_6923" name="ni1" value="4"/>
          <Constant key="Parameter_6963" name="Ki2" value="21"/>
          <Constant key="Parameter_6866" name="ni2" value="4"/>
          <Constant key="Parameter_3915" name="Ki3" value="235"/>
          <Constant key="Parameter_3318" name="ni3" value="4"/>
          <Constant key="Parameter_3323" name="Ki4" value="1000"/>
          <Constant key="Parameter_3320" name="ni4" value="4"/>
          <Constant key="Parameter_3313" name="Ki5" value="0.503603"/>
          <Constant key="Parameter_3312" name="ni5" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_202" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3023">
              <SourceParameter reference="Metabolite_459"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3022">
              <SourceParameter reference="Metabolite_476"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3021">
              <SourceParameter reference="Metabolite_498"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3020">
              <SourceParameter reference="Metabolite_520"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3019">
              <SourceParameter reference="Metabolite_555"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3018">
              <SourceParameter reference="Parameter_3195"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3017">
              <SourceParameter reference="Parameter_3196"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3024">
              <SourceParameter reference="Parameter_6923"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3025">
              <SourceParameter reference="Parameter_6963"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3009">
              <SourceParameter reference="Parameter_6866"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3008">
              <SourceParameter reference="Parameter_3915"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3007">
              <SourceParameter reference="Parameter_3318"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3006">
              <SourceParameter reference="Parameter_3323"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3005">
              <SourceParameter reference="Parameter_3320"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3004">
              <SourceParameter reference="Parameter_3313"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3003">
              <SourceParameter reference="Parameter_3312"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="G16 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_35">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_473" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3202" name="k1" value="0.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3202"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_473"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_306" name="G17 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_474" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_502" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_506" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_535" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3315" name="V" value="1"/>
          <Constant key="Parameter_3192" name="Ka1" value="231"/>
          <Constant key="Parameter_3189" name="na1" value="4"/>
          <Constant key="Parameter_3187" name="Ka2" value="189"/>
          <Constant key="Parameter_3200" name="na2" value="4"/>
          <Constant key="Parameter_3191" name="Ka3" value="0.01"/>
          <Constant key="Parameter_3194" name="na3" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_203" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2987">
              <SourceParameter reference="Metabolite_502"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2988">
              <SourceParameter reference="Metabolite_506"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2989">
              <SourceParameter reference="Metabolite_535"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2990">
              <SourceParameter reference="Parameter_3315"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2991">
              <SourceParameter reference="Parameter_3192"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2992">
              <SourceParameter reference="Parameter_3189"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2993">
              <SourceParameter reference="Parameter_3187"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2994">
              <SourceParameter reference="Parameter_3200"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2995">
              <SourceParameter reference="Parameter_3191"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2996">
              <SourceParameter reference="Parameter_3194"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_307" name="G17 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_474" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3142" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3142"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_474"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_308" name="G18 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_475" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_461" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_459" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3307" name="V" value="100"/>
          <Constant key="Parameter_3188" name="Ki1" value="43"/>
          <Constant key="Parameter_3199" name="ni1" value="4"/>
          <Constant key="Parameter_3193" name="Ki2" value="0.01"/>
          <Constant key="Parameter_3201" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_461"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_459"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_3307"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_3188"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_3199"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_3193"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_3201"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_309" name="G18 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_475" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3308" name="k1" value="30"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3308"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_475"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_310" name="G19 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_476" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_482" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3141" name="V" value="1"/>
          <Constant key="Parameter_3080" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3190" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_482"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_3141"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_3080"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_3190"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_311" name="G19 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_476" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3197" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3197"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_476"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_312" name="G20 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_477" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_462" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_548" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3075" name="V" value="12.3"/>
          <Constant key="Parameter_3683" name="Ki1" value="7.43"/>
          <Constant key="Parameter_3669" name="ni1" value="4"/>
          <Constant key="Parameter_4080" name="Ki2" value="4.6"/>
          <Constant key="Parameter_3094" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_462"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_548"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_3075"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_3683"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_3669"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_4080"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_3094"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_313" name="G20 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_477" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3681" name="k1" value="0.05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3681"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_477"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_314" name="G21 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_478" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_505" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_515" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_523" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_551" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_461" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3092" name="V" value="0.6"/>
          <Constant key="Parameter_4319" name="Ka1" value="5.87104"/>
          <Constant key="Parameter_3689" name="na1" value="4"/>
          <Constant key="Parameter_3699" name="Ka2" value="165.852"/>
          <Constant key="Parameter_4441" name="na2" value="4"/>
          <Constant key="Parameter_4566" name="Ka3" value="3.58648"/>
          <Constant key="Parameter_3077" name="na3" value="4"/>
          <Constant key="Parameter_3682" name="Ka4" value="386.19"/>
          <Constant key="Parameter_4048" name="na4" value="4"/>
          <Constant key="Parameter_4271" name="Ki1" value="11.405"/>
          <Constant key="Parameter_4560" name="ni1" value="2.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_122" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3037">
              <SourceParameter reference="Metabolite_505"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3036">
              <SourceParameter reference="Metabolite_515"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3035">
              <SourceParameter reference="Metabolite_523"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3034">
              <SourceParameter reference="Metabolite_551"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3038">
              <SourceParameter reference="Metabolite_461"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3039">
              <SourceParameter reference="Parameter_3092"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3040">
              <SourceParameter reference="Parameter_4319"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3041">
              <SourceParameter reference="Parameter_3689"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3042">
              <SourceParameter reference="Parameter_3699"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3043">
              <SourceParameter reference="Parameter_4441"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3068">
              <SourceParameter reference="Parameter_4566"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3067">
              <SourceParameter reference="Parameter_3077"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3029">
              <SourceParameter reference="Parameter_3682"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3028">
              <SourceParameter reference="Parameter_4048"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3027">
              <SourceParameter reference="Parameter_4271"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3026">
              <SourceParameter reference="Parameter_4560"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_315" name="G21 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_478" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4061" name="k1" value="5.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4061"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_478"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_316" name="G22 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_479" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4558" name="V" value="3"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_4558"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_317" name="G22 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_479" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4535" name="k1" value="0.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4535"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_479"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_318" name="G23 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_480" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4562" name="V" value="1"/>
          <Constant key="Parameter_4035" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4858" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_4562"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_4035"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_4858"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_319" name="G23 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_480" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4556" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4556"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_480"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_320" name="G24 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_481" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_459" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4553" name="V" value="1"/>
          <Constant key="Parameter_3351" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4552" name="na1" value="4"/>
          <Constant key="Parameter_3356" name="Ka2" value="0.01"/>
          <Constant key="Parameter_2937" name="na2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_125" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3044">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3045">
              <SourceParameter reference="Metabolite_459"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3046">
              <SourceParameter reference="Parameter_4553"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3047">
              <SourceParameter reference="Parameter_3351"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3048">
              <SourceParameter reference="Parameter_4552"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3049">
              <SourceParameter reference="Parameter_3356"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3050">
              <SourceParameter reference="Parameter_2937"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_321" name="G24 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_481" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3096" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3096"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_481"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_322" name="G25 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_482" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4563" name="V" value="2.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_4563"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_323" name="G25 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_482" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4549" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4549"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_482"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_324" name="G26 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_483" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_544" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_556" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3673" name="V" value="3"/>
          <Constant key="Parameter_4561" name="Ka1" value="0.02"/>
          <Constant key="Parameter_4546" name="na1" value="4"/>
          <Constant key="Parameter_3073" name="Ki1" value="0.05"/>
          <Constant key="Parameter_2940" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_544"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_556"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_3673"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_4561"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_4546"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_3073"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_2940"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_325" name="G26 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_483" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4573" name="k1" value="1.9"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4573"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_483"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_326" name="G27 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_484" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_467" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3488" name="V" value="1"/>
          <Constant key="Parameter_3674" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3375" name="na1" value="4"/>
          <Constant key="Parameter_3376" name="Ki1" value="2323"/>
          <Constant key="Parameter_3719" name="ni1" value="2.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_467"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_3488"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_3674"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_3375"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_3376"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_3719"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_327" name="G27 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_484" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3245" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3245"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_484"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_328" name="G28 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_485" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_458" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_479" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3380" name="V" value="15"/>
          <Constant key="Parameter_3864" name="Ki1" value="3.2"/>
          <Constant key="Parameter_3361" name="ni1" value="4"/>
          <Constant key="Parameter_3501" name="Ki2" value="8.4"/>
          <Constant key="Parameter_7138" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_458"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_479"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_3380"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_3864"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_3361"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_3501"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_7138"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_329" name="G28 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_485" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4395" name="k1" value="0.07"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4395"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_485"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_330" name="G29 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_486" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_467" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_495" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_553" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3368" name="V" value="1.2"/>
          <Constant key="Parameter_4610" name="Ka1" value="0.01"/>
          <Constant key="Parameter_7638" name="na1" value="4"/>
          <Constant key="Parameter_4609" name="Ka2" value="12"/>
          <Constant key="Parameter_7641" name="na2" value="4"/>
          <Constant key="Parameter_7632" name="Ki1" value="163"/>
          <Constant key="Parameter_3366" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_206" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2978">
              <SourceParameter reference="Metabolite_467"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2979">
              <SourceParameter reference="Metabolite_495"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2980">
              <SourceParameter reference="Metabolite_553"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2981">
              <SourceParameter reference="Parameter_3368"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2982">
              <SourceParameter reference="Parameter_4610"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2997">
              <SourceParameter reference="Parameter_7638"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2998">
              <SourceParameter reference="Parameter_4609"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2977">
              <SourceParameter reference="Parameter_7641"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2976">
              <SourceParameter reference="Parameter_7632"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2975">
              <SourceParameter reference="Parameter_3366"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_331" name="G29 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_486" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3363" name="k1" value="0.134"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3363"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_486"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_332" name="G30 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_487" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_464" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4547" name="V" value="1"/>
          <Constant key="Parameter_3322" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4496" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_464"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_4547"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_3322"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_4496"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_333" name="G30 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_487" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4589" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4589"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_487"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_334" name="G31 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_488" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_490" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_518" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_554" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4579" name="V" value="14"/>
          <Constant key="Parameter_4582" name="Ki1" value="5.3"/>
          <Constant key="Parameter_2925" name="ni1" value="4"/>
          <Constant key="Parameter_3369" name="Ki2" value="3"/>
          <Constant key="Parameter_4540" name="ni2" value="4"/>
          <Constant key="Parameter_2926" name="Ki3" value="15"/>
          <Constant key="Parameter_2924" name="ni3" value="4"/>
          <Constant key="Parameter_3023" name="Ki4" value="0.15"/>
          <Constant key="Parameter_2923" name="ni4" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_207" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2965">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2966">
              <SourceParameter reference="Metabolite_490"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2967">
              <SourceParameter reference="Metabolite_518"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2968">
              <SourceParameter reference="Metabolite_554"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2969">
              <SourceParameter reference="Parameter_4579"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2970">
              <SourceParameter reference="Parameter_4582"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2971">
              <SourceParameter reference="Parameter_2925"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2972">
              <SourceParameter reference="Parameter_3369"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2973">
              <SourceParameter reference="Parameter_4540"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2974">
              <SourceParameter reference="Parameter_2926"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2964">
              <SourceParameter reference="Parameter_2924"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2963">
              <SourceParameter reference="Parameter_3023"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2962">
              <SourceParameter reference="Parameter_2923"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_335" name="G31 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_488" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3099" name="k1" value="0.7"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3099"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_488"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_336" name="G32 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_489" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_462" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_478" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3036" name="V" value="9"/>
          <Constant key="Parameter_3041" name="Ki1" value="36"/>
          <Constant key="Parameter_2919" name="ni1" value="2"/>
          <Constant key="Parameter_2938" name="Ki2" value="42"/>
          <Constant key="Parameter_6591" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_462"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_478"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_3036"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_3041"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_2919"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_2938"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_6591"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_337" name="G32 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_489" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6592" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6592"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_489"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_338" name="G33 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_490" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_487" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_505" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3378" name="V" value="1"/>
          <Constant key="Parameter_3161" name="Ki1" value="23"/>
          <Constant key="Parameter_2921" name="ni1" value="4"/>
          <Constant key="Parameter_3339" name="Ki2" value="12"/>
          <Constant key="Parameter_6593" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_487"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_505"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_3378"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_3161"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_2921"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_3339"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_6593"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_339" name="G33 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_490" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_2935" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_2935"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_490"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_340" name="G34 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_491" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_540" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_537" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_470" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_2939" name="V" value="45"/>
          <Constant key="Parameter_2945" name="Ka1" value="0.2"/>
          <Constant key="Parameter_3530" name="na1" value="4"/>
          <Constant key="Parameter_3549" name="Ki1" value="0.05"/>
          <Constant key="Parameter_4159" name="ni1" value="4"/>
          <Constant key="Parameter_4160" name="Ki2" value="532"/>
          <Constant key="Parameter_4150" name="ni2" value="3"/>
        </ListOfConstants>
        <KineticLaw function="Function_208" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2949">
              <SourceParameter reference="Metabolite_540"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2950">
              <SourceParameter reference="Metabolite_537"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2951">
              <SourceParameter reference="Metabolite_470"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2952">
              <SourceParameter reference="Parameter_2939"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2953">
              <SourceParameter reference="Parameter_2945"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2954">
              <SourceParameter reference="Parameter_3530"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2955">
              <SourceParameter reference="Parameter_3549"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2956">
              <SourceParameter reference="Parameter_4159"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2957">
              <SourceParameter reference="Parameter_4160"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2958">
              <SourceParameter reference="Parameter_4150"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_341" name="G34 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_491" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4213" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4213"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_491"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_342" name="G35 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_492" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_487" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_488" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4172" name="V" value="1"/>
          <Constant key="Parameter_4211" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3736" name="na1" value="4"/>
          <Constant key="Parameter_3738" name="Ki1" value="0.01"/>
          <Constant key="Parameter_3739" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_487"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_488"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_4172"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_4211"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_3736"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_3738"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_3739"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_343" name="G35 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_492" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3947" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3947"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_492"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_344" name="G36 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_493" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_462" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4867" name="V" value="5"/>
          <Constant key="Parameter_3109" name="Ka1" value="0.62"/>
          <Constant key="Parameter_3735" name="na1" value="4"/>
          <Constant key="Parameter_4166" name="Ki1" value="20.2"/>
          <Constant key="Parameter_4423" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_462"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_4867"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_3109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_3735"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_4166"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_4423"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_345" name="G36 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_493" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4161" name="k1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4161"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_493"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_346" name="G37 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_494" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_478" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_462" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6865" name="V" value="8.5"/>
          <Constant key="Parameter_6885" name="Ki1" value="1351"/>
          <Constant key="Parameter_6909" name="ni1" value="4"/>
          <Constant key="Parameter_3853" name="Ki2" value="16.8"/>
          <Constant key="Parameter_6961" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_478"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_462"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_6865"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_6885"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_6909"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_3853"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_6961"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_347" name="G37 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_494" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3106" name="k1" value="0.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3106"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_494"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_348" name="G38 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_495" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3354" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_3354"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_349" name="G38 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_495" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3789" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3789"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_495"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_350" name="G39 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_496" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_474" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3905" name="V" value="7"/>
          <Constant key="Parameter_3927" name="Ki1" value="87"/>
          <Constant key="Parameter_6920" name="ni1" value="4"/>
          <Constant key="Parameter_6880" name="Ki2" value="0.14"/>
          <Constant key="Parameter_3737" name="ni2" value="1.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_474"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_3905"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_3927"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_6920"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_6880"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_3737"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_351" name="G39 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_496" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3543" name="k1" value="0.04"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3543"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_496"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_352" name="G40 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_497" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_506" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_465" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3544" name="V" value="1"/>
          <Constant key="Parameter_3539" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3542" name="na1" value="4"/>
          <Constant key="Parameter_4604" name="Ki1" value="0.01"/>
          <Constant key="Parameter_3741" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_506"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_465"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_3544"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_3539"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_3542"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_4604"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_3741"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_353" name="G40 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_497" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3740" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3740"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_497"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_354" name="G41 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_498" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_497" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4619" name="V" value="1"/>
          <Constant key="Parameter_3538" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4608" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_497"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_4619"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_3538"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_4608"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_355" name="G41 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_498" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3924" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3924"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_498"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_356" name="G42 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_499" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_537" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4615" name="V" value="2.6"/>
          <Constant key="Parameter_4616" name="Ki1" value="0.82"/>
          <Constant key="Parameter_3869" name="ni1" value="4"/>
          <Constant key="Parameter_4163" name="Ki2" value="0.36"/>
          <Constant key="Parameter_3952" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_537"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_4615"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_4616"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_3869"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_4163"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_3952"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_357" name="G42 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_499" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3928" name="k1" value="0.11"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3928"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_499"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_358" name="G43 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_500" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_480" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_478" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3954" name="V" value="1"/>
          <Constant key="Parameter_3867" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4434" name="na1" value="4"/>
          <Constant key="Parameter_3925" name="Ka2" value="0.01"/>
          <Constant key="Parameter_3956" name="na2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_125" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3044">
              <SourceParameter reference="Metabolite_480"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3045">
              <SourceParameter reference="Metabolite_478"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3046">
              <SourceParameter reference="Parameter_3954"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3047">
              <SourceParameter reference="Parameter_3867"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3048">
              <SourceParameter reference="Parameter_4434"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3049">
              <SourceParameter reference="Parameter_3925"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3050">
              <SourceParameter reference="Parameter_3956"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_359" name="G43 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_500" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4626" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4626"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_500"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_360" name="G44 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_501" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_482" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_474" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3823" name="V" value="1.9"/>
          <Constant key="Parameter_3942" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3826" name="na1" value="4"/>
          <Constant key="Parameter_4611" name="Ki1" value="15"/>
          <Constant key="Parameter_3930" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_482"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_474"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_3823"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_3942"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_3826"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_4611"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_3930"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_361" name="G44 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_501" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3943" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3943"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_501"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_362" name="G45 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_502" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_516" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3933" name="V" value="1"/>
          <Constant key="Parameter_3859" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3950" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_516"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_3933"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_3859"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_3950"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_363" name="G45 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_502" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3944" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3944"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_502"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_364" name="G46 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_503" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_473" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_544" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4598" name="V" value="1"/>
          <Constant key="Parameter_4671" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3926" name="na1" value="4"/>
          <Constant key="Parameter_4437" name="Ki1" value="0.01"/>
          <Constant key="Parameter_3866" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_473"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_544"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_4598"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_4671"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_3926"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_4437"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_3866"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_365" name="G46 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_503" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4617" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4617"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_503"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_366" name="G47 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_504" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4630" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_4630"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_367" name="G47 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_504" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3865" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3865"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_504"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_368" name="G48 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_505" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_510" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_547" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_549" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3825" name="V" value="3.1"/>
          <Constant key="Parameter_3863" name="Ki1" value="243"/>
          <Constant key="Parameter_4600" name="ni1" value="4"/>
          <Constant key="Parameter_3012" name="Ki2" value="0.001"/>
          <Constant key="Parameter_6889" name="ni2" value="4"/>
          <Constant key="Parameter_3117" name="Ki3" value="43"/>
          <Constant key="Parameter_4073" name="ni3" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_209" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2942">
              <SourceParameter reference="Metabolite_510"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2943">
              <SourceParameter reference="Metabolite_547"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2944">
              <SourceParameter reference="Metabolite_549"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2945">
              <SourceParameter reference="Parameter_3825"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2946">
              <SourceParameter reference="Parameter_3863"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2947">
              <SourceParameter reference="Parameter_4600"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2948">
              <SourceParameter reference="Parameter_3012"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2961">
              <SourceParameter reference="Parameter_6889"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2960">
              <SourceParameter reference="Parameter_3117"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2959">
              <SourceParameter reference="Parameter_4073"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_369" name="G48 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_505" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3258" name="k1" value="1.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3258"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_505"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_370" name="G49 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_506" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_525" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6930" name="V" value="1"/>
          <Constant key="Parameter_6886" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4567" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_525"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_6930"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_6886"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_4567"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_371" name="G49 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_506" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6973" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6973"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_506"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_372" name="G50 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_507" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_491" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6970" name="V" value="1"/>
          <Constant key="Parameter_4050" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3119" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_491"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_6970"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_4050"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_3119"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_373" name="G50 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_507" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3333" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3333"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_507"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_374" name="G51 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_508" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_478" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3005" name="V" value="1"/>
          <Constant key="Parameter_3047" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3139" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_478"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_3005"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_3047"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_3139"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_375" name="G51 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_508" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3332" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3332"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_508"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_376" name="G52 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_509" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_478" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6929" name="V" value="1"/>
          <Constant key="Parameter_6928" name="Ki1" value="0.01"/>
          <Constant key="Parameter_4045" name="ni1" value="4"/>
          <Constant key="Parameter_6855" name="Ki2" value="0.01"/>
          <Constant key="Parameter_4047" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_478"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_6929"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_6928"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_4045"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_6855"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_4047"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_377" name="G52 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_509" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3134" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3134"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_509"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_378" name="G53 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_510" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_474" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3446" name="V" value="1"/>
          <Constant key="Parameter_4033" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6954" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_474"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_3446"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_4033"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_6954"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_379" name="G53 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_510" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3118" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3118"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_510"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_380" name="G54 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_511" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_483" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_461" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4551" name="V" value="1"/>
          <Constant key="Parameter_7198" name="Ki1" value="1e-05"/>
          <Constant key="Parameter_3418" name="ni1" value="2"/>
          <Constant key="Parameter_3151" name="Ki2" value="4300"/>
          <Constant key="Parameter_3364" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_483"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_461"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_4551"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_7198"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_3418"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_3151"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_3364"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_381" name="G54 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_511" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3100" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3100"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_511"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_382" name="G55 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_512" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_483" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_525" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3381" name="V" value="1.6"/>
          <Constant key="Parameter_3414" name="Ki1" value="0.1"/>
          <Constant key="Parameter_3411" name="ni1" value="4"/>
          <Constant key="Parameter_3377" name="Ki2" value="0.07"/>
          <Constant key="Parameter_3409" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_483"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_525"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_3381"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_3414"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_3411"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_3377"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_3409"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_383" name="G55 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_512" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3130" name="k1" value="0.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3130"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_512"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_384" name="G56 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_513" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3388" name="V" value="10"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_3388"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_385" name="G56 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_513" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3352" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3352"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_513"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_386" name="G57 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_514" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3379" name="V" value="1"/>
          <Constant key="Parameter_4037" name="Ki1" value="1"/>
          <Constant key="Parameter_3147" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_123" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3030">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3031">
              <SourceParameter reference="Parameter_3379"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3032">
              <SourceParameter reference="Parameter_4037"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3033">
              <SourceParameter reference="Parameter_3147"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_387" name="G57 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_514" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3420" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3420"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_514"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_388" name="G58 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_515" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_462" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3397" name="V" value="23"/>
          <Constant key="Parameter_3383" name="Ki1" value="234"/>
          <Constant key="Parameter_3413" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_123" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3030">
              <SourceParameter reference="Metabolite_462"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3031">
              <SourceParameter reference="Parameter_3397"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3032">
              <SourceParameter reference="Parameter_3383"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3033">
              <SourceParameter reference="Parameter_3413"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_389" name="G58 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_515" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3390" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3390"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_515"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_390" name="G59 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_516" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_459" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3389" name="V" value="1"/>
          <Constant key="Parameter_3385" name="Ka1" value="0.01"/>
          <Constant key="Parameter_6515" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_459"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_3389"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_3385"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_6515"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_391" name="G59 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_516" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3386" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3386"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_516"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_392" name="G60 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_517" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_462" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_466" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7010" name="V" value="4"/>
          <Constant key="Parameter_6509" name="Ka1" value="0.005"/>
          <Constant key="Parameter_3404" name="na1" value="4"/>
          <Constant key="Parameter_6978" name="Ki1" value="8"/>
          <Constant key="Parameter_6516" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_462"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_466"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_7010"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_6509"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_3404"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_6978"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_6516"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_393" name="G60 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_517" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6933" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6933"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_517"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_394" name="G61 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_518" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6950" name="V" value="0.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_6950"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_395" name="G61 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_518" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3963" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3963"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_518"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_396" name="G62 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_519" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_512" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_474" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3408" name="V" value="3.2"/>
          <Constant key="Parameter_6514" name="Ki1" value="0.1"/>
          <Constant key="Parameter_3398" name="ni1" value="4"/>
          <Constant key="Parameter_6955" name="Ki2" value="0.4"/>
          <Constant key="Parameter_3346" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_512"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_474"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_3408"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_6514"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_3398"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_6955"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_3346"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_397" name="G62 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_519" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6919" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6919"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_519"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_398" name="G63 synthesis" reversible="false" fast="false" addNoise="false">
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
          <Product metabolite="Metabolite_520" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3416" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_3416"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_399" name="G63 degradation" reversible="false" fast="false" addNoise="false">
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
          <Substrate metabolite="Metabolite_520" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6945" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6945"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_520"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_400" name="G64 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_400">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_521" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_482" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_474" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3393" name="V" value="1"/>
          <Constant key="Parameter_4602" name="Ki1" value="23"/>
          <Constant key="Parameter_6893" name="ni1" value="4"/>
          <Constant key="Parameter_3345" name="Ki2" value="1"/>
          <Constant key="Parameter_6513" name="ni2" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_482"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_474"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_3393"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_4602"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_6893"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_3345"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_6513"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_401" name="G64 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_401">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_521" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6974" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6974"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_521"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_402" name="G65 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_402">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_522" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_491" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_526" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6906" name="V" value="1"/>
          <Constant key="Parameter_3396" name="Ki1" value="0.01"/>
          <Constant key="Parameter_3402" name="ni1" value="4"/>
          <Constant key="Parameter_6523" name="Ki2" value="5.1"/>
          <Constant key="Parameter_3391" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_491"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_526"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_6906"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_3396"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_3402"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_6523"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_3391"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_403" name="G65 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_403">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_522" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6944" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6944"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_522"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_404" name="G66 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_404">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_523" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_464" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6968" name="V" value="1"/>
          <Constant key="Parameter_3415" name="Ka1" value="0.0001"/>
          <Constant key="Parameter_6878" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_464"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_6968"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_3415"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_6878"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_405" name="G66 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_405">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_523" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6869" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6869"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_523"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_406" name="G67 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_406">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_524" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_474" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3400" name="V" value="0.3"/>
          <Constant key="Parameter_6931" name="Ki1" value="8.2"/>
          <Constant key="Parameter_3384" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_123" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3030">
              <SourceParameter reference="Metabolite_474"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3031">
              <SourceParameter reference="Parameter_3400"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3032">
              <SourceParameter reference="Parameter_6931"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3033">
              <SourceParameter reference="Parameter_3384"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_407" name="G67 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_407">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_524" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3326" name="k1" value="0.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3326"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_524"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_408" name="G68 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_408">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_525" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3392" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_3392"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_409" name="G68 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_409">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_525" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4596" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4596"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_525"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_410" name="G69 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_410">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_526" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_474" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_460" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3348" name="V" value="3"/>
          <Constant key="Parameter_3382" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3324" name="na1" value="4"/>
          <Constant key="Parameter_3399" name="Ki1" value="2"/>
          <Constant key="Parameter_6512" name="ni1" value="3"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_474"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_460"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_3348"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_3382"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_3324"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_3399"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_6512"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_411" name="G69 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_411">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_526" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6506" name="k1" value="2.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6506"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_526"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_412" name="G70 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_412">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_527" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_466" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_470" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3353" name="V" value="1.4"/>
          <Constant key="Parameter_6505" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3112" name="na1" value="4"/>
          <Constant key="Parameter_6471" name="Ki1" value="123"/>
          <Constant key="Parameter_3407" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_466"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_470"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_3353"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_6505"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_3112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_6471"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_3407"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_413" name="G70 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_413">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_527" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6472" name="k1" value="0.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6472"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_527"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_414" name="G71 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_414">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_528" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_487" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_552" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4308" name="V" value="1"/>
          <Constant key="Parameter_6938" name="Ki1" value="0.08"/>
          <Constant key="Parameter_3160" name="ni1" value="4"/>
          <Constant key="Parameter_3107" name="Ki2" value="56"/>
          <Constant key="Parameter_3086" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_487"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_552"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_4308"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_6938"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_3160"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_3107"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_3086"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_415" name="G71 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_415">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_528" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3158" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3158"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_528"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_416" name="G72 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_416">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_529" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_508" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_504" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3254" name="V" value="1"/>
          <Constant key="Parameter_3066" name="Ki1" value="2.3"/>
          <Constant key="Parameter_3103" name="ni1" value="4"/>
          <Constant key="Parameter_3074" name="Ki2" value="2.4"/>
          <Constant key="Parameter_3085" name="ni2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_201" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3010">
              <SourceParameter reference="Metabolite_508"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3011">
              <SourceParameter reference="Metabolite_504"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3012">
              <SourceParameter reference="Parameter_3254"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3013">
              <SourceParameter reference="Parameter_3066"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3014">
              <SourceParameter reference="Parameter_3103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3015">
              <SourceParameter reference="Parameter_3074"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3016">
              <SourceParameter reference="Parameter_3085"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_417" name="G72 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_417">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_529" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4498" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4498"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_529"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_418" name="G73 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_418">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_530" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3028" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_3028"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_419" name="G73 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_419">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_530" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3014" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3014"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_530"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_420" name="G74 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_420">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_531" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_473" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3228" name="V" value="1"/>
          <Constant key="Parameter_3026" name="Ki1" value="0.01"/>
          <Constant key="Parameter_3221" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_123" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3030">
              <SourceParameter reference="Metabolite_473"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3031">
              <SourceParameter reference="Parameter_3228"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3032">
              <SourceParameter reference="Parameter_3026"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3033">
              <SourceParameter reference="Parameter_3221"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_421" name="G74 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_421">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_531" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3225" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3225"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_531"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_422" name="G75 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_422">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_532" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_478" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3114" name="V" value="1"/>
          <Constant key="Parameter_3108" name="Ki1" value="0.01"/>
          <Constant key="Parameter_3113" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_123" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3030">
              <SourceParameter reference="Metabolite_478"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3031">
              <SourceParameter reference="Parameter_3114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3032">
              <SourceParameter reference="Parameter_3108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3033">
              <SourceParameter reference="Parameter_3113"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_423" name="G75 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_423">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_532" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3710" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3710"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_532"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_424" name="G76 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_424">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_533" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_470" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3116" name="V" value="1"/>
          <Constant key="Parameter_3111" name="Ka1" value="6e-09"/>
          <Constant key="Parameter_3226" name="na1" value="3.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_470"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_3116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_3111"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_3226"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_425" name="G76 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_425">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_533" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3227" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3227"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_533"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_426" name="G77 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_426">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_534" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_491" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3263" name="V" value="1"/>
          <Constant key="Parameter_3218" name="Ki1" value="0.01"/>
          <Constant key="Parameter_3104" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_123" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3030">
              <SourceParameter reference="Metabolite_491"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3031">
              <SourceParameter reference="Parameter_3263"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3032">
              <SourceParameter reference="Parameter_3218"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3033">
              <SourceParameter reference="Parameter_3104"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_427" name="G77 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_427">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_534" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3259" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3259"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_534"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_428" name="G78 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_428">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_535" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3222" name="V" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_3222"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_429" name="G78 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_429">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_535" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3261" name="k1" value="2.9"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3261"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_535"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_430" name="G79 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_430">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_536" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_491" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_465" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3115" name="V" value="1"/>
          <Constant key="Parameter_3123" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3213" name="na1" value="4"/>
          <Constant key="Parameter_3265" name="Ka2" value="0.01"/>
          <Constant key="Parameter_3220" name="na2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_125" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3044">
              <SourceParameter reference="Metabolite_491"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3045">
              <SourceParameter reference="Metabolite_465"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3046">
              <SourceParameter reference="Parameter_3115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3047">
              <SourceParameter reference="Parameter_3123"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3048">
              <SourceParameter reference="Parameter_3213"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3049">
              <SourceParameter reference="Parameter_3265"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3050">
              <SourceParameter reference="Parameter_3220"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_431" name="G79 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_431">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_536" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3089" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3089"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_536"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_432" name="G80 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_432">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_537" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3105" name="V" value="0.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_3105"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_433" name="G80 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_433">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_537" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7187" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_7187"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_537"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_434" name="G81 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_434">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_538" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_504" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_506" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3087" name="V" value="1"/>
          <Constant key="Parameter_3691" name="Ka1" value="0.001"/>
          <Constant key="Parameter_3078" name="na1" value="4"/>
          <Constant key="Parameter_3716" name="Ki1" value="1"/>
          <Constant key="Parameter_3076" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_504"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_506"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_3087"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_3691"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_3078"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_3716"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_3076"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_435" name="G81 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_435">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_538" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3069" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3069"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_538"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_436" name="G82 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_436">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_539" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_518" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3687" name="V" value="1"/>
          <Constant key="Parameter_3267" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3072" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_518"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_3687"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_3267"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_3072"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_437" name="G82 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_437">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_539" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3070" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3070"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_539"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_438" name="G83 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_438">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_540" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3270" name="V" value="1.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_3270"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_439" name="G83 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_439">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_540" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3897" name="k1" value="1.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3897"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_540"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_440" name="G84 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_440">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_541" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_497" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3091" name="V" value="1"/>
          <Constant key="Parameter_4076" name="Ki1" value="1.5"/>
          <Constant key="Parameter_3120" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_123" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3030">
              <SourceParameter reference="Metabolite_497"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3031">
              <SourceParameter reference="Parameter_3091"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3032">
              <SourceParameter reference="Parameter_4076"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3033">
              <SourceParameter reference="Parameter_3120"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_441" name="G84 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_441">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_541" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3079" name="k1" value="2.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3079"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_541"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_442" name="G85 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_442">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_542" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_462" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4063" name="V" value="1"/>
          <Constant key="Parameter_4042" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4534" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_462"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_4063"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_4042"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_4534"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_443" name="G85 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_443">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_542" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4056" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4056"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_542"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_444" name="G86 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_444">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_543" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_478" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_480" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3159" name="V" value="1"/>
          <Constant key="Parameter_3068" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3081" name="na1" value="4"/>
          <Constant key="Parameter_4046" name="Ka2" value="0.01"/>
          <Constant key="Parameter_3164" name="na2" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_125" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3044">
              <SourceParameter reference="Metabolite_478"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3045">
              <SourceParameter reference="Metabolite_480"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3046">
              <SourceParameter reference="Parameter_3159"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3047">
              <SourceParameter reference="Parameter_3068"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3048">
              <SourceParameter reference="Parameter_3081"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3049">
              <SourceParameter reference="Parameter_4046"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3050">
              <SourceParameter reference="Parameter_3164"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_445" name="G86 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_445">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_543" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3082" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3082"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_543"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_446" name="G87 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_446">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_544" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3090" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_3090"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_447" name="G87 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_447">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_544" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3715" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3715"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_544"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_448" name="G88 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_448">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_545" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_542" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_467" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3095" name="V" value="1"/>
          <Constant key="Parameter_4490" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4493" name="na1" value="4"/>
          <Constant key="Parameter_3685" name="Ki1" value="0.01"/>
          <Constant key="Parameter_3063" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_542"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_467"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_3095"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_4490"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_4493"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_3685"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_3063"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_449" name="G88 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_449">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_545" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3814" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3814"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_545"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_450" name="G89 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_450">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_546" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_535" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_476" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_6887" name="V" value="1.3"/>
          <Constant key="Parameter_4508" name="Ka1" value="0.001"/>
          <Constant key="Parameter_3083" name="na1" value="4"/>
          <Constant key="Parameter_3918" name="Ki1" value="0.1"/>
          <Constant key="Parameter_3065" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_535"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_476"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_6887"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_4508"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_3083"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_3918"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_3065"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_451" name="G89 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_451">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_546" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4062" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4062"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_546"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_452" name="G90 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_452">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_547" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_480" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_557" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3955" name="V" value="1"/>
          <Constant key="Parameter_3524" name="Ka1" value="0.01"/>
          <Constant key="Parameter_3093" name="na1" value="4"/>
          <Constant key="Parameter_3750" name="Ki1" value="0.01"/>
          <Constant key="Parameter_4501" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_205" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2984">
              <SourceParameter reference="Metabolite_480"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2985">
              <SourceParameter reference="Metabolite_557"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2986">
              <SourceParameter reference="Parameter_3955"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3002">
              <SourceParameter reference="Parameter_3524"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3001">
              <SourceParameter reference="Parameter_3093"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3000">
              <SourceParameter reference="Parameter_3750"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2999">
              <SourceParameter reference="Parameter_4501"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_453" name="G90 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_453">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_547" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_6891" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_6891"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_547"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_454" name="G91 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_454">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_548" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4504" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_4504"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_455" name="G91 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_455">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_548" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3062" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3062"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_548"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_456" name="G92 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_456">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_549" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_520" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3126" name="V" value="1"/>
          <Constant key="Parameter_3892" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4060" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_520"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_3126"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_3892"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_4060"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_457" name="G92 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_457">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_549" stoichiometry="1"/>
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
              <SourceParameter reference="Metabolite_549"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_458" name="G93 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_458">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_550" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_491" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3921" name="V" value="1"/>
          <Constant key="Parameter_4032" name="Ki1" value="0.01"/>
          <Constant key="Parameter_4038" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_123" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3030">
              <SourceParameter reference="Metabolite_491"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3031">
              <SourceParameter reference="Parameter_3921"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3032">
              <SourceParameter reference="Parameter_4032"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3033">
              <SourceParameter reference="Parameter_4038"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_459" name="G93 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_459">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_550" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4167" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4167"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_550"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_460" name="G94 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_460">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_551" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_462" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4136" name="V" value="2.1"/>
          <Constant key="Parameter_4162" name="Ka1" value="2"/>
          <Constant key="Parameter_3662" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_462"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_4136"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_4162"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_3662"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_461" name="G94 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_461">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_551" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4039" name="k1" value="1.04"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4039"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_551"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_462" name="G95 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_462">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_552" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_3749" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_3749"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_463" name="G95 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_463">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_552" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3242" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3242"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_552"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_464" name="G96 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_464">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_553" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_466" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3748" name="V" value="1"/>
          <Constant key="Parameter_3901" name="Ka1" value="0.01"/>
          <Constant key="Parameter_4513" name="na1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3089">
              <SourceParameter reference="Metabolite_466"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3090">
              <SourceParameter reference="Parameter_3748"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3091">
              <SourceParameter reference="Parameter_3901"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3092">
              <SourceParameter reference="Parameter_4513"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_465" name="G96 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_465">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_553" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3071" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3071"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_553"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_466" name="G97 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_466">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_554" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_532" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_3243" name="V" value="1"/>
          <Constant key="Parameter_4487" name="Ki1" value="0.01"/>
          <Constant key="Parameter_7635" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_123" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3030">
              <SourceParameter reference="Metabolite_532"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3031">
              <SourceParameter reference="Parameter_3243"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3032">
              <SourceParameter reference="Parameter_4487"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3033">
              <SourceParameter reference="Parameter_7635"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_467" name="G97 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_467">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_554" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4511" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4511"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_554"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_468" name="G98 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_468">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_555" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_504" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4049" name="V" value="1"/>
          <Constant key="Parameter_4066" name="Ki1" value="0.7"/>
          <Constant key="Parameter_4518" name="ni1" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_123" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_3030">
              <SourceParameter reference="Metabolite_504"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3031">
              <SourceParameter reference="Parameter_4049"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3032">
              <SourceParameter reference="Parameter_4066"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3033">
              <SourceParameter reference="Parameter_4518"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_469" name="G98 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_469">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_555" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4542" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4542"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_555"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_470" name="G99 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_470">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_556" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4051" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_4051"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_471" name="G99 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_471">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_556" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4510" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_4510"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_556"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_472" name="G100 synthesis" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_472">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_557" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_6884" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_204" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_2983">
              <SourceParameter reference="Parameter_6884"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_473" name="G100 degradation" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_473">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T22:15:25Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_557" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_3088" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=wt CoopSF41b - Perturbation 1 - G56 10x induction,Vector=Compartments[cell]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Parameter_3088"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_557"/>
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
<dcterms:W3CDTF>2020-12-31T22:36:59Z</dcterms:W3CDTF>
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
      <StateTemplateVariable objectReference="Metabolite_458"/>
      <StateTemplateVariable objectReference="Metabolite_459"/>
      <StateTemplateVariable objectReference="Metabolite_460"/>
      <StateTemplateVariable objectReference="Metabolite_461"/>
      <StateTemplateVariable objectReference="Metabolite_462"/>
      <StateTemplateVariable objectReference="Metabolite_463"/>
      <StateTemplateVariable objectReference="Metabolite_464"/>
      <StateTemplateVariable objectReference="Metabolite_465"/>
      <StateTemplateVariable objectReference="Metabolite_466"/>
      <StateTemplateVariable objectReference="Metabolite_467"/>
      <StateTemplateVariable objectReference="Metabolite_468"/>
      <StateTemplateVariable objectReference="Metabolite_469"/>
      <StateTemplateVariable objectReference="Metabolite_470"/>
      <StateTemplateVariable objectReference="Metabolite_471"/>
      <StateTemplateVariable objectReference="Metabolite_472"/>
      <StateTemplateVariable objectReference="Metabolite_473"/>
      <StateTemplateVariable objectReference="Metabolite_474"/>
      <StateTemplateVariable objectReference="Metabolite_475"/>
      <StateTemplateVariable objectReference="Metabolite_476"/>
      <StateTemplateVariable objectReference="Metabolite_477"/>
      <StateTemplateVariable objectReference="Metabolite_478"/>
      <StateTemplateVariable objectReference="Metabolite_479"/>
      <StateTemplateVariable objectReference="Metabolite_480"/>
      <StateTemplateVariable objectReference="Metabolite_481"/>
      <StateTemplateVariable objectReference="Metabolite_482"/>
      <StateTemplateVariable objectReference="Metabolite_483"/>
      <StateTemplateVariable objectReference="Metabolite_484"/>
      <StateTemplateVariable objectReference="Metabolite_485"/>
      <StateTemplateVariable objectReference="Metabolite_486"/>
      <StateTemplateVariable objectReference="Metabolite_487"/>
      <StateTemplateVariable objectReference="Metabolite_488"/>
      <StateTemplateVariable objectReference="Metabolite_489"/>
      <StateTemplateVariable objectReference="Metabolite_490"/>
      <StateTemplateVariable objectReference="Metabolite_491"/>
      <StateTemplateVariable objectReference="Metabolite_492"/>
      <StateTemplateVariable objectReference="Metabolite_493"/>
      <StateTemplateVariable objectReference="Metabolite_494"/>
      <StateTemplateVariable objectReference="Metabolite_495"/>
      <StateTemplateVariable objectReference="Metabolite_496"/>
      <StateTemplateVariable objectReference="Metabolite_497"/>
      <StateTemplateVariable objectReference="Metabolite_498"/>
      <StateTemplateVariable objectReference="Metabolite_499"/>
      <StateTemplateVariable objectReference="Metabolite_500"/>
      <StateTemplateVariable objectReference="Metabolite_501"/>
      <StateTemplateVariable objectReference="Metabolite_502"/>
      <StateTemplateVariable objectReference="Metabolite_503"/>
      <StateTemplateVariable objectReference="Metabolite_504"/>
      <StateTemplateVariable objectReference="Metabolite_505"/>
      <StateTemplateVariable objectReference="Metabolite_506"/>
      <StateTemplateVariable objectReference="Metabolite_507"/>
      <StateTemplateVariable objectReference="Metabolite_508"/>
      <StateTemplateVariable objectReference="Metabolite_509"/>
      <StateTemplateVariable objectReference="Metabolite_510"/>
      <StateTemplateVariable objectReference="Metabolite_511"/>
      <StateTemplateVariable objectReference="Metabolite_512"/>
      <StateTemplateVariable objectReference="Metabolite_513"/>
      <StateTemplateVariable objectReference="Metabolite_514"/>
      <StateTemplateVariable objectReference="Metabolite_515"/>
      <StateTemplateVariable objectReference="Metabolite_516"/>
      <StateTemplateVariable objectReference="Metabolite_517"/>
      <StateTemplateVariable objectReference="Metabolite_518"/>
      <StateTemplateVariable objectReference="Metabolite_519"/>
      <StateTemplateVariable objectReference="Metabolite_520"/>
      <StateTemplateVariable objectReference="Metabolite_521"/>
      <StateTemplateVariable objectReference="Metabolite_522"/>
      <StateTemplateVariable objectReference="Metabolite_523"/>
      <StateTemplateVariable objectReference="Metabolite_524"/>
      <StateTemplateVariable objectReference="Metabolite_525"/>
      <StateTemplateVariable objectReference="Metabolite_526"/>
      <StateTemplateVariable objectReference="Metabolite_527"/>
      <StateTemplateVariable objectReference="Metabolite_528"/>
      <StateTemplateVariable objectReference="Metabolite_529"/>
      <StateTemplateVariable objectReference="Metabolite_530"/>
      <StateTemplateVariable objectReference="Metabolite_531"/>
      <StateTemplateVariable objectReference="Metabolite_532"/>
      <StateTemplateVariable objectReference="Metabolite_533"/>
      <StateTemplateVariable objectReference="Metabolite_534"/>
      <StateTemplateVariable objectReference="Metabolite_535"/>
      <StateTemplateVariable objectReference="Metabolite_536"/>
      <StateTemplateVariable objectReference="Metabolite_537"/>
      <StateTemplateVariable objectReference="Metabolite_538"/>
      <StateTemplateVariable objectReference="Metabolite_539"/>
      <StateTemplateVariable objectReference="Metabolite_540"/>
      <StateTemplateVariable objectReference="Metabolite_541"/>
      <StateTemplateVariable objectReference="Metabolite_542"/>
      <StateTemplateVariable objectReference="Metabolite_543"/>
      <StateTemplateVariable objectReference="Metabolite_544"/>
      <StateTemplateVariable objectReference="Metabolite_545"/>
      <StateTemplateVariable objectReference="Metabolite_546"/>
      <StateTemplateVariable objectReference="Metabolite_547"/>
      <StateTemplateVariable objectReference="Metabolite_548"/>
      <StateTemplateVariable objectReference="Metabolite_549"/>
      <StateTemplateVariable objectReference="Metabolite_550"/>
      <StateTemplateVariable objectReference="Metabolite_551"/>
      <StateTemplateVariable objectReference="Metabolite_552"/>
      <StateTemplateVariable objectReference="Metabolite_553"/>
      <StateTemplateVariable objectReference="Metabolite_554"/>
      <StateTemplateVariable objectReference="Metabolite_555"/>
      <StateTemplateVariable objectReference="Metabolite_556"/>
      <StateTemplateVariable objectReference="Metabolite_557"/>
      <StateTemplateVariable objectReference="Compartment_3"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 22691800000000000 6986120000000 323777000000 606782000000000 4.67668e+17 11556400000000000 79403100000 3461590000 9345020000000000 2107670000000000 105972000000 10451600000000000 8.6059e+18 15328999999999998 3343310000000000 680574000000000 15146300000000000 84046500000000 9552270000000000 544044000 716033000000000 2258300000000000 734847000000000 4101590000000000 1385090000000000 75204900000 9580630000000000 1106850000000 79386700000000000 634179000000000 1339090000000 9514160000000 428401000000000 1811810000 4235300000000000 312045000 2563850000 602214000000000 43403000000000 9601060000000000 9623350000000000 131696000000000 1.49162e+17 35353900000000000 9601010000000000 90980900 602214000000000 297703000000000 9446040000000000 602938999999999.88 9475700000000000 2363190 9627770000000000 3307079999999.9995 21951800000 602214000000000 600921000000000 39816100000000 3361290000000000 516061000000000 240886000000000 115577000 602214000000000 601452000000 1172960000000 3646700000000000 1650550000000 602214000000000 11544000000000000 178620000 13941900000 39550200000 602214000000000 3564099.9999999995 2913890 5534100000000001 601490000000000 124596000000000 604326000000000 481771000000000 124064000000 9173930000000000 766454000000000 14969800000 9635180000000000 1.49162e+17 602214000000000 634107 19111300 91098400 602214000000000 9446040000000000 601490000000000 19356400000000000 602214000000000 9623020000000000 602213000000000 17312000000000 602214000000000 602214000000000 1 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_28" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_44" target="../../Test/CopasiTestSSReport.txt" append="0" confirmOverwrite="0"/>
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
      <Report reference="Report_23" target="../../Test/100GeneTestDyn.dat" append="0" confirmOverwrite="0"/>
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
    <Task key="Task_26" name="Scan" type="scan" scheduled="false" updateModel="false">
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
    <Task key="Task_25" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_9" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_24" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_17" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_23" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_19" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_22" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
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
    <Task key="Task_20" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="true" updateModel="false">
      <Report reference="Report_36" target="CoopSF4_001_tssa-csp.out" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="4"/>
        <Parameter name="StepSize" type="float" value="25"/>
        <Parameter name="Duration" type="float" value="100"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="CSP (LSODA)" type="TimeScaleSeparation(CSP)">
        <Parameter name="Integrate Reduced Model" type="bool" value="1"/>
        <Parameter name="Ratio of Modes Separation" type="unsignedFloat" value="0.90000000000000002"/>
        <Parameter name="Maximum Relative Error" type="unsignedFloat" value="0.001"/>
        <Parameter name="Maximum Absolute Error" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Refinement Iterations Number" type="unsignedInteger" value="1000"/>
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
        <Parameter name="Steady-State" type="key" value="Task_28"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
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
    <Report key="Report_44" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_9" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_23" name="report" taskType="timeCourse" separator="&#x09;" precision="6">
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
    <Report key="Report_20" name="Time-Course" taskType="timeCourse" separator="&#x09;" precision="6">
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
    <Report key="Report_19" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
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
    <Report key="Report_36" name="Speed test" taskType="scan" separator="&#x09;" precision="8">
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
    <UnitDefinition key="Unit_65" name="minute" symbol="min">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_64">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-31T13:58:51Z</dcterms:W3CDTF>
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
