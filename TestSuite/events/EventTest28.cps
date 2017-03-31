<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.20.147+ (Debug) (http://www.copasi.org) at 2017-03-31 14:03:17 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="20" versionDevel="147" copasiSourcesModified="1">
  <ListOfFunctions>
    <Function key="Function_40" name="tanh() step function" type="UserDefined" reversible="unspecified">
      <Expression>
        offset+0.5*amplitude*(1+tanh(cyclePeriod*((t+phase)/cyclePeriod-floor((t+phase)/cyclePeriod))/rampDuration))-0.5*amplitude*(1+tanh((cyclePeriod*((t+phase)/cyclePeriod-floor((t+phase)/cyclePeriod))-pulseDuration)/rampDuration))+0.5*amplitude*(1+tanh((cyclePeriod*((t+phase)/cyclePeriod-floor((t+phase)/cyclePeriod))-cyclePeriod)/rampDuration))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_266" name="t" order="0" role="variable"/>
        <ParameterDescription key="FunctionParameter_264" name="offset" order="1" role="variable"/>
        <ParameterDescription key="FunctionParameter_254" name="amplitude" order="2" role="variable"/>
        <ParameterDescription key="FunctionParameter_268" name="phase" order="3" role="variable"/>
        <ParameterDescription key="FunctionParameter_272" name="pulseDuration" order="4" role="variable"/>
        <ParameterDescription key="FunctionParameter_258" name="cyclePeriod" order="5" role="variable"/>
        <ParameterDescription key="FunctionParameter_270" name="rampDuration" order="6" role="variable"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_41" name="function_4_cL_m_trscr" type="UserDefined" reversible="unspecified">
      <Expression>
        (L*q1*cP+n1*g1^a/((cP9+cP7+cNI+cT)^a+g1^a))/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_273" name="L" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_277" name="a" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_283" name="cNI" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_265" name="cP" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_281" name="cP7" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_279" name="cP9" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_285" name="cT" order="6" role="modifier"/>
        <ParameterDescription key="FunctionParameter_287" name="def" order="7" role="volume"/>
        <ParameterDescription key="FunctionParameter_275" name="g1" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_262" name="n1" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_269" name="q1" order="10" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_42" name="function_4_cE4_m_trscr_1" type="UserDefined" reversible="unspecified">
      <Expression>
        n13*g2/(cEC+g2)*g6^e/(cL^e+g6^e)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_280" name="cEC" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_271" name="cL" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_290" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_246" name="e" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_284" name="g2" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_276" name="g6" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_288" name="n13" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_43" name="function_4_cLUX_m_trscr" type="UserDefined" reversible="unspecified">
      <Expression>
        n13*g2/(cEC+g2)*g6^e/(cL^e+g6^e)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_278" name="cEC" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_295" name="cL" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_297" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_293" name="e" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_267" name="g2" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_286" name="g6" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_291" name="n13" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_44" name="function_4_cL_m_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        (m1*L+m2*D)*cL_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_289" name="D" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_294" name="L" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_300" name="cL_m" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_302" name="def" order="3" role="volume"/>
        <ParameterDescription key="FunctionParameter_298" name="m1" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_282" name="m2" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_45" name="function_4_cL_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        (m3*cL+p3*cL^c/(cL^c+g3^c))/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_304" name="c" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_299" name="cL" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_308" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_306" name="g3" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_303" name="m3" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_292" name="p3" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_46" name="function_4_cL_modif" type="UserDefined" reversible="unspecified">
      <Expression>
        p3*cL^c/(cL^c+g3^c)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_274" name="c" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_305" name="cL" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_312" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_310" name="g3" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_309" name="p3" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_47" name="function_4_cLm_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m4*cLm/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_301" name="cLm" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_307" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_313" name="m4" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_48" name="function_4_cP_trsl" type="UserDefined" reversible="unspecified">
      <Expression>
        p7*D*(1-cP)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_311" name="D" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_316" name="cP" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_318" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_314" name="p7" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_49" name="function_4_cP_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m11*cP*L/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_320" name="L" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_315" name="cP" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_322" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_319" name="m11" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_50" name="function_4_cP9_trsl" type="UserDefined" reversible="unspecified">
      <Expression>
        p8*cP9_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_296" name="cP9_m" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_324" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_323" name="p8" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_51" name="function_4_cP9_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        (m13+m22*D)*cP9/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_327" name="D" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_329" name="cP9" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_331" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_325" name="m13" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_321" name="m22" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_52" name="function_4_cP7_m_trscr" type="UserDefined" reversible="unspecified">
      <Expression>
        (n8*(cLm+cL)^e/((cLm+cL)^e+g10^e)+n9*cP9^f/(cP9^f+g11^f))/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_317" name="cL" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_328" name="cLm" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_340" name="cP9" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_346" name="def" order="3" role="volume"/>
        <ParameterDescription key="FunctionParameter_334" name="e" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_342" name="f" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_336" name="g10" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_344" name="g11" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_332" name="n8" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_338" name="n9" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_53" name="function_4_cP7_m_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m14*cP7_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_343" name="cP7_m" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_339" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_347" name="m14" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_54" name="function_4_cP7_trsl" type="UserDefined" reversible="unspecified">
      <Expression>
        p9*cP7_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_345" name="cP7_m" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_333" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_337" name="p9" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_55" name="function_4_cP7_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        (m15+m23*D)*cP7/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_348" name="D" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_350" name="cP7" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_352" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_326" name="m15" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_341" name="m23" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_56" name="function_4_cNI_m_trscr" type="UserDefined" reversible="unspecified">
      <Expression>
        (n10*cLm^e/(cLm^e+g12^e)+n11*cP7^b/(cP7^b+g13^b))/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_361" name="b" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_349" name="cLm" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_359" name="cP7" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_365" name="def" order="3" role="volume"/>
        <ParameterDescription key="FunctionParameter_335" name="e" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_355" name="g12" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_363" name="g13" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_353" name="n10" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_357" name="n11" order="8" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_57" name="function_4_cNI_m_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m16*cNI_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_362" name="cNI_m" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_358" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_366" name="m16" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_58" name="function_4_cNI_trsl" type="UserDefined" reversible="unspecified">
      <Expression>
        p10*cNI_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_364" name="cNI_m" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_330" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_356" name="p10" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_59" name="function_4_cNI_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        (m17+m24*D)*cNI/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_368" name="D" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_370" name="cNI" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_372" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_351" name="m17" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_360" name="m24" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_60" name="function_4_cE4_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        (m35*cE4+p25*cE4*cE3n-p21*p25*cE4*cE3n/(p26*cLUX+p21+m37*cCOP1d+m36*cCOP1n))/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_385" name="cCOP1d" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_389" name="cCOP1n" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_375" name="cE3n" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_369" name="cE4" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_381" name="cLUX" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_391" name="def" order="5" role="volume"/>
        <ParameterDescription key="FunctionParameter_373" name="m35" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_387" name="m36" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_383" name="m37" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_377" name="p21" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_354" name="p25" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_379" name="p26" order="11" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_61" name="function_4_cE3_trsl" type="UserDefined" reversible="unspecified">
      <Expression>
        p16*cE3_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_388" name="cE3_m" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_384" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_392" name="p16" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_62" name="function_4_cE3_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m9*cE3*cCOP1c/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_378" name="cCOP1c" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_390" name="cE3" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_374" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_382" name="m9" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_63" name="function_4_cE3n_import" type="UserDefined" reversible="unspecified">
      <Expression>
        (p19*cE3-p20*cE3n)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_380" name="cE3" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_394" name="cE3n" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_396" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_367" name="p19" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_371" name="p20" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_64" name="function_4_cCOP1n_import" type="UserDefined" reversible="unspecified">
      <Expression>
        p6*cCOP1c/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_393" name="cCOP1c" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_376" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_397" name="p6" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_65" name="function_4_cCOP1n_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m27*cCOP1n*(1+p15*L)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_402" name="L" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_395" name="cCOP1n" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_404" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_398" name="m27" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_400" name="p15" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_66" name="function_4_cZG_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m21*cZG/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_401" name="cZG" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_386" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_405" name="m21" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_67" name="function_4_cE3n_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        (m29*cE3n*cCOP1n+m30*cE3n*cCOP1d+p25*cE4*cE3n-p21*p25*cE4*cE3n/(p26*cLUX+p21+m37*cCOP1d+m36*cCOP1n)+p17*cE3n*p28*cG/(p29+m19+p17*cE3n))/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_412" name="cCOP1d" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_408" name="cCOP1n" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_403" name="cE3n" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_416" name="cE4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_432" name="cG" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_422" name="cLUX" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_438" name="def" order="6" role="volume"/>
        <ParameterDescription key="FunctionParameter_436" name="m19" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_406" name="m29" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_410" name="m30" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_426" name="m36" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_424" name="m37" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_428" name="p17" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_418" name="p21" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_414" name="p25" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_420" name="p26" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_430" name="p28" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_434" name="p29" order="17" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_68" name="function_4_cLUX_m_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m34*cLUX_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_435" name="cLUX_m" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_431" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_439" name="m34" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_69" name="function_4_cLUX_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        (m39*cLUX+p26*cLUX*p25*cE4*cE3n/(p26*cLUX+p21+m37*cCOP1d+m36*cCOP1n))/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_441" name="cCOP1d" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_445" name="cCOP1n" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_413" name="cE3n" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_417" name="cE4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_437" name="cLUX" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_447" name="def" order="5" role="volume"/>
        <ParameterDescription key="FunctionParameter_443" name="m36" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_399" name="m37" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_429" name="m39" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_409" name="p21" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_421" name="p25" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_425" name="p26" order="11" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_70" name="function_4_cCOP1c_trsl" type="UserDefined" reversible="unspecified">
      <Expression>
        n5/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_444" name="def" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_448" name="n5" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_71" name="function_4_cL_trsl" type="UserDefined" reversible="unspecified">
      <Expression>
        cL_m*(p1*L+p2)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_411" name="L" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_442" name="cL_m" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_427" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_440" name="p1" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_419" name="p2" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_72" name="function_4_cP9_m_trscr_1" type="UserDefined" reversible="unspecified">
      <Expression>
        (L*q3*cP+(n4+n7*cL^e/(cL^e+g9^e))*g8/(cEC+g8))/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_433" name="L" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_462" name="cEC" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_454" name="cL" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_446" name="cP" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_464" name="def" order="4" role="volume"/>
        <ParameterDescription key="FunctionParameter_456" name="e" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_460" name="g8" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_458" name="g9" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_450" name="n4" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_452" name="n7" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_415" name="q3" order="10" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_73" name="function_4_cP9_m_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m12*cP9_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_461" name="cP9_m" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_457" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_465" name="m12" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_74" name="function_4_cT_m_trscr_1" type="UserDefined" reversible="unspecified">
      <Expression>
        n2*g4/(cEC+g4)*g5^e/(cL^e+g5^e)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_451" name="cEC" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_468" name="cL" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_470" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_466" name="e" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_463" name="g4" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_407" name="g5" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_455" name="n2" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_75" name="function_4_cCOP1d_activ" type="UserDefined" reversible="unspecified">
      <Expression>
        (n6*L*cP*cCOP1n+n14*cCOP1n)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_467" name="L" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_459" name="cCOP1n" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_449" name="cP" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_475" name="def" order="3" role="volume"/>
        <ParameterDescription key="FunctionParameter_473" name="n14" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_471" name="n6" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_76" name="function_4_cT_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        ((m6+m7*D)*cT*(p5*cZTL+cZG)+m8*cT)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_423" name="D" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_477" name="cT" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_483" name="cZG" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_481" name="cZTL" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_487" name="def" order="4" role="volume"/>
        <ParameterDescription key="FunctionParameter_476" name="m6" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_472" name="m7" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_485" name="m8" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_479" name="p5" order="8" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_77" name="function_4_cT_trsl" type="UserDefined" reversible="unspecified">
      <Expression>
        p4*cT_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_484" name="cT_m" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_480" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_488" name="p4" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_78" name="function_4_cE4_trsl" type="UserDefined" reversible="unspecified">
      <Expression>
        p23*cE4_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_486" name="cE4_m" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_453" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_478" name="p23" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_79" name="function_4_cE4_m_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m34*cE4_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_482" name="cE4_m" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_490" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_474" name="m34" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_80" name="function_4_cT_m_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m5*cT_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_469" name="cT_m" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_493" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_491" name="m5" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_81" name="function_4_cE3_m_trscr" type="UserDefined" reversible="unspecified">
      <Expression>
        n3*g16^e/(cL^e+g16^e)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_498" name="cL" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_500" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_496" name="e" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_489" name="g16" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_494" name="n3" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_82" name="function_4_cE3_m_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m26*cE3_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_497" name="cE3_m" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_492" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_501" name="m26" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_83" name="function_4_cCOP1c_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m27*cCOP1c*(1+p15*L)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_506" name="L" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_499" name="cCOP1c" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_508" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_502" name="m27" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_504" name="p15" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_84" name="function_4_cLUX_trsl" type="UserDefined" reversible="unspecified">
      <Expression>
        p27*cLUX_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_505" name="cLUX_m" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_495" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_509" name="p27" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_85" name="function_4_cG_m_trscr_1" type="UserDefined" reversible="unspecified">
      <Expression>
        (L*q2*cP+n12*g14/(cEC+g14)*g15^e/(cL^e+g15^e))/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_510" name="L" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_518" name="cEC" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_524" name="cL" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_512" name="cP" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_526" name="def" order="4" role="volume"/>
        <ParameterDescription key="FunctionParameter_522" name="e" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_516" name="g14" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_520" name="g15" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_514" name="n12" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_507" name="q2" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_86" name="function_4_cG_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        (m19*cG+p28*cG-p29*p28*cG/(p29+m19+p17*cE3n))/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_528" name="cE3n" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_523" name="cG" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_530" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_527" name="m19" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_511" name="p17" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_519" name="p28" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_515" name="p29" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_87" name="function_4_cCOP1d_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m31*(1+m33*D)*cCOP1d/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_517" name="D" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_525" name="cCOP1d" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_533" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_531" name="m31" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_503" name="m33" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_88" name="function_4_cG_m_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m18*cG_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_521" name="cG_m" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_529" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_534" name="m18" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_89" name="function_4_cG_trsl" type="UserDefined" reversible="unspecified">
      <Expression>
        p11*cG_m/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_532" name="cG_m" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_537" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_535" name="p11" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_90" name="function_4_cEC_form" type="UserDefined" reversible="unspecified">
      <Expression>
        p26*cLUX*p25*cE4*cE3n/(p26*cLUX+p21+m37*cCOP1d+m36*cCOP1n)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_550" name="cCOP1d" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_554" name="cCOP1n" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_544" name="cE3n" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_542" name="cE4" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_513" name="cLUX" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_556" name="def" order="5" role="volume"/>
        <ParameterDescription key="FunctionParameter_552" name="m36" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_548" name="m37" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_546" name="p21" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_540" name="p25" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_538" name="p26" order="10" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_91" name="function_4_cEC_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        (m36*cCOP1n*cEC+m37*cCOP1d*cEC+m32*cEC*(1+p24*L*(p28*cG/(p29+m19+p17*cE3n)+(p18*cEG+p17*cE3n*p28*cG/(p29+m19+p17*cE3n))/(m9*cCOP1n+m10*cCOP1d+p31))^d/((p28*cG/(p29+m19+p17*cE3n)+(p18*cEG+p17*cE3n*p28*cG/(p29+m19+p17*cE3n))/(m9*cCOP1n+m10*cCOP1d+p31))^d+g7^d)))/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_561" name="L" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_541" name="cCOP1d" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_553" name="cCOP1n" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_573" name="cE3n" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_549" name="cEC" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_577" name="cEG" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_565" name="cG" order="6" role="modifier"/>
        <ParameterDescription key="FunctionParameter_585" name="d" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_589" name="def" order="8" role="volume"/>
        <ParameterDescription key="FunctionParameter_587" name="g7" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_581" name="m10" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_569" name="m19" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_536" name="m32" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_557" name="m36" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_545" name="m37" order="14" role="constant"/>
        <ParameterDescription key="FunctionParameter_579" name="m9" order="15" role="constant"/>
        <ParameterDescription key="FunctionParameter_571" name="p17" order="16" role="constant"/>
        <ParameterDescription key="FunctionParameter_575" name="p18" order="17" role="constant"/>
        <ParameterDescription key="FunctionParameter_559" name="p24" order="18" role="constant"/>
        <ParameterDescription key="FunctionParameter_563" name="p28" order="19" role="constant"/>
        <ParameterDescription key="FunctionParameter_567" name="p29" order="20" role="constant"/>
        <ParameterDescription key="FunctionParameter_583" name="p31" order="21" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_92" name="function_4_cG_cZTL_assoc" type="UserDefined" reversible="unspecified">
      <Expression>
        (p12*L*cZTL*cG-p13*D*cZG)/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_570" name="D" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_586" name="L" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_578" name="cG" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_566" name="cZG" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_582" name="cZTL" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_562" name="def" order="5" role="volume"/>
        <ParameterDescription key="FunctionParameter_590" name="p12" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_574" name="p13" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_93" name="function_4_cEG_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        (m9*cEG*cCOP1c+p18*cEG-p31*(p18*cEG+p17*cE3n*p28*cG/(p29+m19+p17*cE3n))/(m9*cCOP1n+m10*cCOP1d+p31))/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_576" name="cCOP1c" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_603" name="cCOP1d" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_599" name="cCOP1n" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_551" name="cE3n" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_568" name="cEG" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_593" name="cG" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_605" name="def" order="6" role="volume"/>
        <ParameterDescription key="FunctionParameter_601" name="m10" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_597" name="m19" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_560" name="m9" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_543" name="p17" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_584" name="p18" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_591" name="p28" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_595" name="p29" order="13" role="constant"/>
        <ParameterDescription key="FunctionParameter_558" name="p31" order="14" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_94" name="function_4_cZTL_trsl" type="UserDefined" reversible="unspecified">
      <Expression>
        p14/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_602" name="def" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_606" name="p14" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_95" name="function_4_cG_cE3_assoc" type="UserDefined" reversible="unspecified">
      <Expression>
        p17*cE3*cG/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_598" name="cE3" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_594" name="cG" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_555" name="def" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_600" name="p17" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_96" name="function_4_cZTL_degr" type="UserDefined" reversible="unspecified">
      <Expression>
        m20*cZTL/def
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_596" name="cZTL" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_539" name="def" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_547" name="m20" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_5" name="Alex" simulationType="time" timeUnit="h" volumeUnit="µl" areaUnit="m²" lengthUnit="m" quantityUnit="nmol" type="deterministic" avogadroConstant="6.02214179e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Model_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-08-18T14:47:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <ListOfCompartments>
      <Compartment key="Compartment_1" name="def" simulationType="fixed" dimensionality="3">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-06-27T12:53:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_1" name="cCOP1c" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_3" name="cCOP1d" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_5" name="cCOP1n" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_7" name="cE3" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_9" name="cE3_m" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_11" name="cE3n" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_13" name="cE4" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_15" name="cE4_m" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_17" name="cEC" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_19" name="cEG" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_21" name="cG" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_23" name="cG_m" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_25" name="cL" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_27" name="cLUX" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_29" name="cLUX_m" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_31" name="cL_m" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_33" name="cLm" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_35" name="cNI" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_37" name="cNI_m" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_39" name="cP" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_41" name="cP7" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_43" name="cP7_m" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_45" name="cP9" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_47" name="cP9_m" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_49" name="cT" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_51" name="cT_m" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_53" name="cZG" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
      <Metabolite key="Metabolite_55" name="cZTL" simulationType="reactions" compartment="Compartment_1">
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_6" name="n1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_7" name="n2" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_8" name="n3" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_9" name="n4" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_10" name="n5" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_11" name="n6" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_12" name="n7" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_13" name="n8" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_14" name="n9" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_15" name="n10" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_16" name="n11" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_17" name="n12" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_18" name="n13" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_19" name="n14" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_20" name="g1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_21" name="g2" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_22" name="g3" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_23" name="g4" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_24" name="g5" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_25" name="g6" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_26" name="g7" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_27" name="g8" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_28" name="g9" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_29" name="g10" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_29">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-08-18T14:59:52Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_30" name="g11" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_31" name="g12" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_32" name="g13" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_33" name="g14" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_34" name="g15" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_35" name="g16" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_36" name="m1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_37" name="m2" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_38" name="m3" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_39" name="m4" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_40" name="m5" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_41" name="m6" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_42" name="m7" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_43" name="m8" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_44" name="m9" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_45" name="m10" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_46" name="m11" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_47" name="m12" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_48" name="m13" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_49" name="m14" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_50" name="m15" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_51" name="m16" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_52" name="m17" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_53" name="m18" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_54" name="m19" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_55" name="m20" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_56" name="m21" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_57" name="m22" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_58" name="m23" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_58">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-08-18T15:12:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_59" name="m24" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_60" name="m25" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_61" name="m26" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_62" name="m27" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_63" name="m28" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_64" name="m29" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_65" name="m30" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_66" name="m31" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_67" name="m32" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_68" name="m33" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_69" name="m34" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_70" name="m35" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_71" name="m36" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_72" name="m37" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_73" name="m38" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_74" name="m39" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_75" name="a" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_76" name="b" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_77" name="c" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_78" name="d" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_78">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-08-18T14:51:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_79" name="e" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_80" name="f" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_81" name="p1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_82" name="p2" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_83" name="p3" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_84" name="p4" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_85" name="p5" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_86" name="p6" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_87" name="p7" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_88" name="p8" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_89" name="p9" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_90" name="p10" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_91" name="p11" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_92" name="p12" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_93" name="p13" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_94" name="p14" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_95" name="p15" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_96" name="p16" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_97" name="p17" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_98" name="p18" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_99" name="p19" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_100" name="p20" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_101" name="p21" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_102" name="p22" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_103" name="p23" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_104" name="p24" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_105" name="p25" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_106" name="p26" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_107" name="p27" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_108" name="p28" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_109" name="p29" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_110" name="p30" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_111" name="p31" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_112" name="q1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_113" name="q2" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_114" name="q3" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_115" name="L" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_115">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-08-18T14:55:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Alex,Vector=Values[Lightstep],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_116" name="D" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_116">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-08-18T15:00:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          1-&lt;CN=Root,Model=Alex,Vector=Values[L],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_117" name="E34" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_118" name="Gn" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_118">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-08-18T14:48:55Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_119" name="EGn" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_119">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-08-18T14:47:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_120" name="Lightstep" simulationType="assignment">
        <Expression>
          "tanh() step function"(&lt;CN=Root,Model=Alex,Reference=Time>,&lt;CN=Root,Model=Alex,Vector=Values[offsetStep1],Reference=Value>,&lt;CN=Root,Model=Alex,Vector=Values[amplitudeStep1],Reference=Value>,&lt;CN=Root,Model=Alex,Vector=Values[phaseStep1],Reference=Value>,&lt;CN=Root,Model=Alex,Vector=Values[pulseDurationStep1],Reference=Value>,&lt;CN=Root,Model=Alex,Vector=Values[cyclePeriodStep1],Reference=Value>,&lt;CN=Root,Model=Alex,Vector=Values[rampDurationStep1],Reference=Value>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_121" name="offsetStep1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_122" name="amplitudeStep1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_123" name="phaseStep1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_124" name="pulseDurationStep1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_125" name="cyclePeriodStep1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_126" name="rampDurationStep1" simulationType="fixed">
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="cL_m_trscr" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-06-27T13:07:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_35" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_39" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_41" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_45" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4835" name="L" value="0.5"/>
          <Constant key="Parameter_4836" name="a" value="2"/>
          <Constant key="Parameter_4837" name="g1" value="0.1"/>
          <Constant key="Parameter_4838" name="n1" value="2.6"/>
          <Constant key="Parameter_4839" name="q1" value="1.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_41" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="ModelValue_75"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_283">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_281">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_279">
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_285">
              <SourceParameter reference="Metabolite_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_287">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="ModelValue_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="ModelValue_112"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="cL_m_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4840" name="D" value="0.5"/>
          <Constant key="Parameter_4841" name="L" value="0.5"/>
          <Constant key="Parameter_4842" name="m1" value="0.54"/>
          <Constant key="Parameter_4843" name="m2" value="0.24"/>
        </ListOfConstants>
        <KineticLaw function="Function_44" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_289">
              <SourceParameter reference="ModelValue_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_294">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_300">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_302">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_298">
              <SourceParameter reference="ModelValue_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="ModelValue_37"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="cL_trsl" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4844" name="L" value="0.5"/>
          <Constant key="Parameter_4845" name="p1" value="0.13"/>
          <Constant key="Parameter_4846" name="p2" value="0.27"/>
        </ListOfConstants>
        <KineticLaw function="Function_71" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_411">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_442">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_427">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_440">
              <SourceParameter reference="ModelValue_81"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_419">
              <SourceParameter reference="ModelValue_82"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="cL_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4847" name="c" value="2"/>
          <Constant key="Parameter_4848" name="g3" value="0.6"/>
          <Constant key="Parameter_4849" name="m3" value="0.2"/>
          <Constant key="Parameter_4850" name="p3" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_45" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_304">
              <SourceParameter reference="ModelValue_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_299">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_308">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="ModelValue_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_303">
              <SourceParameter reference="ModelValue_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_292">
              <SourceParameter reference="ModelValue_83"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="cL_modif" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4851" name="c" value="2"/>
          <Constant key="Parameter_4852" name="g3" value="0.6"/>
          <Constant key="Parameter_4853" name="p3" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_46" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="ModelValue_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_305">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_310">
              <SourceParameter reference="ModelValue_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_309">
              <SourceParameter reference="ModelValue_83"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="cLm_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4854" name="m4" value="0.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_47" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_301">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_307">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="ModelValue_39"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="cP_trsl" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4855" name="D" value="0.5"/>
          <Constant key="Parameter_4856" name="p7" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_48" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_311">
              <SourceParameter reference="ModelValue_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_314">
              <SourceParameter reference="ModelValue_87"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="cP_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4857" name="L" value="0.5"/>
          <Constant key="Parameter_4858" name="m11" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_49" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_315">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="ModelValue_46"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="cP9_m_trscr" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_47" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_17" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4859" name="L" value="0.5"/>
          <Constant key="Parameter_4860" name="e" value="2"/>
          <Constant key="Parameter_4874" name="g8" value="0.01"/>
          <Constant key="Parameter_4875" name="g9" value="0.3"/>
          <Constant key="Parameter_4876" name="n4" value="0.07"/>
          <Constant key="Parameter_4877" name="n7" value="0.2"/>
          <Constant key="Parameter_4878" name="q3" value="2.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_72" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_433">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_462">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_454">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_446">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_464">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_456">
              <SourceParameter reference="ModelValue_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_460">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_458">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_450">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_452">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_415">
              <SourceParameter reference="ModelValue_114"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="cP9_m_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_47" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4879" name="m12" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_73" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_461">
              <SourceParameter reference="Metabolite_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_457">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_465">
              <SourceParameter reference="ModelValue_47"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="cP9_trsl" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_47" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4880" name="p8" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_50" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_296">
              <SourceParameter reference="Metabolite_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_324">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_323">
              <SourceParameter reference="ModelValue_88"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="cP9_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4881" name="D" value="0.5"/>
          <Constant key="Parameter_4882" name="m13" value="0.32"/>
          <Constant key="Parameter_4883" name="m22" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_51" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_327">
              <SourceParameter reference="ModelValue_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_329">
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_331">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_325">
              <SourceParameter reference="ModelValue_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="ModelValue_57"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="cP7_m_trscr" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4884" name="e" value="2"/>
          <Constant key="Parameter_4885" name="f" value="2"/>
          <Constant key="Parameter_4886" name="g10" value="0.5"/>
          <Constant key="Parameter_4887" name="g11" value="0.7"/>
          <Constant key="Parameter_4888" name="n8" value="0.5"/>
          <Constant key="Parameter_4889" name="n9" value="0.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_328">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_340">
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_346">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_334">
              <SourceParameter reference="ModelValue_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_342">
              <SourceParameter reference="ModelValue_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_336">
              <SourceParameter reference="ModelValue_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_344">
              <SourceParameter reference="ModelValue_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_332">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_338">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="cP7_m_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4890" name="m14" value="0.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_53" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_343">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_339">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_347">
              <SourceParameter reference="ModelValue_49"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="cP7_trsl" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4891" name="p9" value="0.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_54" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_345">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_333">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_337">
              <SourceParameter reference="ModelValue_89"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="cP7_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4892" name="D" value="0.5"/>
          <Constant key="Parameter_4893" name="m15" value="0.7"/>
          <Constant key="Parameter_4894" name="m23" value="1.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_55" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_348">
              <SourceParameter reference="ModelValue_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_350">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_352">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_326">
              <SourceParameter reference="ModelValue_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_341">
              <SourceParameter reference="ModelValue_58"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="cNI_m_trscr" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4895" name="b" value="2"/>
          <Constant key="Parameter_4896" name="e" value="2"/>
          <Constant key="Parameter_4897" name="g12" value="0.2"/>
          <Constant key="Parameter_4898" name="g13" value="1"/>
          <Constant key="Parameter_4899" name="n10" value="0.4"/>
          <Constant key="Parameter_4900" name="n11" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_56" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_361">
              <SourceParameter reference="ModelValue_76"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_349">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_359">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_365">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_335">
              <SourceParameter reference="ModelValue_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_355">
              <SourceParameter reference="ModelValue_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_363">
              <SourceParameter reference="ModelValue_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_353">
              <SourceParameter reference="ModelValue_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_357">
              <SourceParameter reference="ModelValue_16"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="cNI_m_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4901" name="m16" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_57" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_362">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_358">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_366">
              <SourceParameter reference="ModelValue_51"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="cNI_trsl" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4902" name="p10" value="0.54"/>
        </ListOfConstants>
        <KineticLaw function="Function_58" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_364">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_330">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_356">
              <SourceParameter reference="ModelValue_90"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="cNI_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4903" name="D" value="0.5"/>
          <Constant key="Parameter_4904" name="m17" value="0.5"/>
          <Constant key="Parameter_4905" name="m24" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_59" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_368">
              <SourceParameter reference="ModelValue_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_370">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_372">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_351">
              <SourceParameter reference="ModelValue_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_360">
              <SourceParameter reference="ModelValue_59"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="cT_m_trscr" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_17" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4906" name="e" value="2"/>
          <Constant key="Parameter_4912" name="g4" value="0.01"/>
          <Constant key="Parameter_4911" name="g5" value="0.15"/>
          <Constant key="Parameter_4910" name="n2" value="0.64"/>
        </ListOfConstants>
        <KineticLaw function="Function_74" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_451">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_468">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_470">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_466">
              <SourceParameter reference="ModelValue_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_463">
              <SourceParameter reference="ModelValue_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_407">
              <SourceParameter reference="ModelValue_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_455">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="cT_m_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4907" name="m5" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_80" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_469">
              <SourceParameter reference="Metabolite_51"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_493">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_491">
              <SourceParameter reference="ModelValue_40"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="cT_trsl" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4908" name="p4" value="0.56"/>
        </ListOfConstants>
        <KineticLaw function="Function_77" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_484">
              <SourceParameter reference="Metabolite_51"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_480">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_488">
              <SourceParameter reference="ModelValue_84"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="cT_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_53" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4909" name="D" value="0.5"/>
          <Constant key="Parameter_4913" name="m6" value="0.3"/>
          <Constant key="Parameter_4914" name="m7" value="0.7"/>
          <Constant key="Parameter_4917" name="m8" value="0.4"/>
          <Constant key="Parameter_4916" name="p5" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_76" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_423">
              <SourceParameter reference="ModelValue_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_477">
              <SourceParameter reference="Metabolite_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_483">
              <SourceParameter reference="Metabolite_53"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_481">
              <SourceParameter reference="Metabolite_55"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_487">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_476">
              <SourceParameter reference="ModelValue_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_472">
              <SourceParameter reference="ModelValue_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_485">
              <SourceParameter reference="ModelValue_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_479">
              <SourceParameter reference="ModelValue_85"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="cE4_m_trscr" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_17" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4915" name="e" value="2"/>
          <Constant key="Parameter_4918" name="g2" value="0.01"/>
          <Constant key="Parameter_4919" name="g6" value="0.3"/>
          <Constant key="Parameter_4920" name="n13" value="1.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_43" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_295">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_297">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_293">
              <SourceParameter reference="ModelValue_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_267">
              <SourceParameter reference="ModelValue_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_286">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_291">
              <SourceParameter reference="ModelValue_18"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="cE4_m_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4921" name="m34" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_482">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_490">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_474">
              <SourceParameter reference="ModelValue_69"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="cE4_trsl" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4922" name="p23" value="0.37"/>
        </ListOfConstants>
        <KineticLaw function="Function_78" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_486">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_453">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_478">
              <SourceParameter reference="ModelValue_103"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="cE4_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_11" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4923" name="m35" value="0.3"/>
          <Constant key="Parameter_4924" name="m36" value="0.1"/>
          <Constant key="Parameter_4925" name="m37" value="0.8"/>
          <Constant key="Parameter_4926" name="p21" value="1"/>
          <Constant key="Parameter_4927" name="p25" value="8"/>
          <Constant key="Parameter_4928" name="p26" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_60" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_385">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_389">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_375">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_369">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_381">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_391">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_373">
              <SourceParameter reference="ModelValue_70"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_387">
              <SourceParameter reference="ModelValue_71"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_383">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_377">
              <SourceParameter reference="ModelValue_101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_354">
              <SourceParameter reference="ModelValue_105"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_379">
              <SourceParameter reference="ModelValue_106"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="cE3_m_trscr" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4929" name="e" value="2"/>
          <Constant key="Parameter_4930" name="g16" value="0.3"/>
          <Constant key="Parameter_4931" name="n3" value="0.29"/>
        </ListOfConstants>
        <KineticLaw function="Function_81" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_498">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_500">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_496">
              <SourceParameter reference="ModelValue_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_489">
              <SourceParameter reference="ModelValue_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_494">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="cE3_m_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4932" name="m26" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_82" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_497">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_492">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_501">
              <SourceParameter reference="ModelValue_61"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="cE3_trsl" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4933" name="p16" value="0.62"/>
        </ListOfConstants>
        <KineticLaw function="Function_61" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_388">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_384">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_392">
              <SourceParameter reference="ModelValue_96"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="cE3_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4934" name="m9" value="1.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_62" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_378">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_390">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_374">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_382">
              <SourceParameter reference="ModelValue_44"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_32" name="cE3n_import" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4935" name="p19" value="1"/>
          <Constant key="Parameter_4936" name="p20" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_63" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_380">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_394">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_396">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_367">
              <SourceParameter reference="ModelValue_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_371">
              <SourceParameter reference="ModelValue_100"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_33" name="cE3n_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_13" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_21" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4937" name="m19" value="0.2"/>
          <Constant key="Parameter_4938" name="m29" value="5"/>
          <Constant key="Parameter_4939" name="m30" value="3"/>
          <Constant key="Parameter_4940" name="m36" value="0.1"/>
          <Constant key="Parameter_4941" name="m37" value="0.8"/>
          <Constant key="Parameter_4942" name="p17" value="4.8"/>
          <Constant key="Parameter_4943" name="p21" value="1"/>
          <Constant key="Parameter_4944" name="p25" value="8"/>
          <Constant key="Parameter_4945" name="p26" value="0.3"/>
          <Constant key="Parameter_4946" name="p28" value="2"/>
          <Constant key="Parameter_4947" name="p29" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_67" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_412">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_408">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_403">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_416">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_432">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_422">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_438">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_436">
              <SourceParameter reference="ModelValue_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_406">
              <SourceParameter reference="ModelValue_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_410">
              <SourceParameter reference="ModelValue_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_426">
              <SourceParameter reference="ModelValue_71"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_424">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_428">
              <SourceParameter reference="ModelValue_97"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_418">
              <SourceParameter reference="ModelValue_101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_414">
              <SourceParameter reference="ModelValue_105"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_420">
              <SourceParameter reference="ModelValue_106"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_430">
              <SourceParameter reference="ModelValue_108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_434">
              <SourceParameter reference="ModelValue_109"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_34" name="cLUX_m_trscr" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_17" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4948" name="e" value="2"/>
          <Constant key="Parameter_4949" name="g2" value="0.01"/>
          <Constant key="Parameter_4950" name="g6" value="0.3"/>
          <Constant key="Parameter_4821" name="n13" value="1.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_42" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_271">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_290">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_246">
              <SourceParameter reference="ModelValue_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="ModelValue_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_276">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_288">
              <SourceParameter reference="ModelValue_18"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="cLUX_m_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4822" name="m34" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_68" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_435">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_431">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_439">
              <SourceParameter reference="ModelValue_69"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_36" name="cLUX_trsl" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4823" name="p27" value="0.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_84" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_505">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_495">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_509">
              <SourceParameter reference="ModelValue_107"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_37" name="cLUX_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_11" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4824" name="m36" value="0.1"/>
          <Constant key="Parameter_4825" name="m37" value="0.8"/>
          <Constant key="Parameter_4826" name="m39" value="0.3"/>
          <Constant key="Parameter_4827" name="p21" value="1"/>
          <Constant key="Parameter_4828" name="p25" value="8"/>
          <Constant key="Parameter_4829" name="p26" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_69" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_441">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_445">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_413">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_417">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_437">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_447">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_443">
              <SourceParameter reference="ModelValue_71"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_399">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_429">
              <SourceParameter reference="ModelValue_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_409">
              <SourceParameter reference="ModelValue_101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_421">
              <SourceParameter reference="ModelValue_105"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_425">
              <SourceParameter reference="ModelValue_106"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_38" name="cCOP1c_trsl" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_38">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-06-27T12:53:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4830" name="n5" value="0.23"/>
        </ListOfConstants>
        <KineticLaw function="Function_70" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_444">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_448">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_39" name="cCOP1c_degr" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_39">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-06-27T12:53:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4831" name="L" value="0.5"/>
          <Constant key="Parameter_4832" name="m27" value="0.1"/>
          <Constant key="Parameter_4833" name="p15" value="3"/>
        </ListOfConstants>
        <KineticLaw function="Function_83" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_506">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_499">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_508">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_502">
              <SourceParameter reference="ModelValue_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_504">
              <SourceParameter reference="ModelValue_95"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_40" name="cCOP1n_import" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-06-27T12:53:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4951" name="p6" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_64" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_393">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_376">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_397">
              <SourceParameter reference="ModelValue_86"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_41" name="cCOP1n_degr" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-06-27T12:53:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4952" name="L" value="0.5"/>
          <Constant key="Parameter_4807" name="m27" value="0.1"/>
          <Constant key="Parameter_4808" name="p15" value="3"/>
        </ListOfConstants>
        <KineticLaw function="Function_65" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_402">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_395">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_404">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_398">
              <SourceParameter reference="ModelValue_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_400">
              <SourceParameter reference="ModelValue_95"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_42" name="cCOP1d_activ" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_42">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-06-27T12:53:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4809" name="L" value="0.5"/>
          <Constant key="Parameter_4810" name="n14" value="0.1"/>
          <Constant key="Parameter_4811" name="n6" value="20"/>
        </ListOfConstants>
        <KineticLaw function="Function_75" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_467">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_459">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_449">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_475">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_473">
              <SourceParameter reference="ModelValue_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_471">
              <SourceParameter reference="ModelValue_11"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_43" name="cCOP1d_degr" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_43">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-06-27T12:53:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4812" name="D" value="0.5"/>
          <Constant key="Parameter_4813" name="m31" value="0.3"/>
          <Constant key="Parameter_4814" name="m33" value="13"/>
        </ListOfConstants>
        <KineticLaw function="Function_87" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_517">
              <SourceParameter reference="ModelValue_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_525">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_533">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_531">
              <SourceParameter reference="ModelValue_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_503">
              <SourceParameter reference="ModelValue_68"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_44" name="cG_m_trscr" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_17" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4815" name="L" value="0.5"/>
          <Constant key="Parameter_4816" name="e" value="2"/>
          <Constant key="Parameter_4817" name="g14" value="0.004"/>
          <Constant key="Parameter_4818" name="g15" value="0.4"/>
          <Constant key="Parameter_4819" name="n12" value="12.5"/>
          <Constant key="Parameter_4820" name="q2" value="1.56"/>
        </ListOfConstants>
        <KineticLaw function="Function_85" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_510">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_518">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_524">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_512">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_526">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_522">
              <SourceParameter reference="ModelValue_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_516">
              <SourceParameter reference="ModelValue_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_520">
              <SourceParameter reference="ModelValue_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_514">
              <SourceParameter reference="ModelValue_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_507">
              <SourceParameter reference="ModelValue_113"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_45" name="cG_m_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5101" name="m18" value="3.4"/>
        </ListOfConstants>
        <KineticLaw function="Function_88" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_521">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_529">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_534">
              <SourceParameter reference="ModelValue_53"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_46" name="cG_trsl" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_5100" name="p11" value="0.51"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_532">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_537">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_535">
              <SourceParameter reference="ModelValue_91"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_47" name="cG_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4965" name="m19" value="0.2"/>
          <Constant key="Parameter_4964" name="p17" value="4.8"/>
          <Constant key="Parameter_4963" name="p28" value="2"/>
          <Constant key="Parameter_4962" name="p29" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_528">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_523">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_530">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_527">
              <SourceParameter reference="ModelValue_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_511">
              <SourceParameter reference="ModelValue_97"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_519">
              <SourceParameter reference="ModelValue_108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_515">
              <SourceParameter reference="ModelValue_109"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_48" name="cG_cZTL_assoc" reversible="true" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4961" name="D" value="0.5"/>
          <Constant key="Parameter_4960" name="L" value="0.5"/>
          <Constant key="Parameter_4959" name="p12" value="3.4"/>
          <Constant key="Parameter_4958" name="p13" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_92" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_570">
              <SourceParameter reference="ModelValue_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_586">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_578">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_566">
              <SourceParameter reference="Metabolite_53"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_582">
              <SourceParameter reference="Metabolite_55"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_562">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_590">
              <SourceParameter reference="ModelValue_92"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_574">
              <SourceParameter reference="ModelValue_93"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_49" name="cZTL_trsl" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_49">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-06-27T13:20:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4957" name="p14" value="0.14"/>
        </ListOfConstants>
        <KineticLaw function="Function_94" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_602">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_606">
              <SourceParameter reference="ModelValue_94"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_50" name="cZTL_degr" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_50">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2013-06-27T13:20:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4757" name="m20" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_96" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_596">
              <SourceParameter reference="Metabolite_55"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_539">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_547">
              <SourceParameter reference="ModelValue_55"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_51" name="cZG_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4756" name="m21" value="0.08"/>
        </ListOfConstants>
        <KineticLaw function="Function_66" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_401">
              <SourceParameter reference="Metabolite_53"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_386">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_405">
              <SourceParameter reference="ModelValue_56"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_52" name="cG_cE3_assoc" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4755" name="p17" value="4.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_95" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_598">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_594">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_555">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_600">
              <SourceParameter reference="ModelValue_97"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_53" name="cEG_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_1" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_11" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4754" name="m10" value="1"/>
          <Constant key="Parameter_4753" name="m19" value="0.2"/>
          <Constant key="Parameter_4752" name="m9" value="1.1"/>
          <Constant key="Parameter_4751" name="p17" value="4.8"/>
          <Constant key="Parameter_4750" name="p18" value="4"/>
          <Constant key="Parameter_4749" name="p28" value="2"/>
          <Constant key="Parameter_4748" name="p29" value="0.1"/>
          <Constant key="Parameter_4747" name="p31" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_93" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_576">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_603">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_599">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_551">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_568">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_593">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_605">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_601">
              <SourceParameter reference="ModelValue_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_597">
              <SourceParameter reference="ModelValue_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_560">
              <SourceParameter reference="ModelValue_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_543">
              <SourceParameter reference="ModelValue_97"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_584">
              <SourceParameter reference="ModelValue_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_591">
              <SourceParameter reference="ModelValue_108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_595">
              <SourceParameter reference="ModelValue_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_558">
              <SourceParameter reference="ModelValue_111"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_54" name="cEC_form" reversible="false" fast="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_11" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_13" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4746" name="m36" value="0.1"/>
          <Constant key="Parameter_4745" name="m37" value="0.8"/>
          <Constant key="Parameter_4744" name="p21" value="1"/>
          <Constant key="Parameter_4743" name="p25" value="8"/>
          <Constant key="Parameter_4742" name="p26" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_550">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_554">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_544">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_542">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_513">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_556">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_552">
              <SourceParameter reference="ModelValue_71"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_548">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_546">
              <SourceParameter reference="ModelValue_101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_540">
              <SourceParameter reference="ModelValue_105"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_538">
              <SourceParameter reference="ModelValue_106"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_55" name="cEC_degr" reversible="false" fast="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_11" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4741" name="L" value="0.5"/>
          <Constant key="Parameter_4740" name="d" value="2"/>
          <Constant key="Parameter_4739" name="g7" value="0.6"/>
          <Constant key="Parameter_4738" name="m10" value="1"/>
          <Constant key="Parameter_4737" name="m19" value="0.2"/>
          <Constant key="Parameter_4736" name="m32" value="0.2"/>
          <Constant key="Parameter_4735" name="m36" value="0.1"/>
          <Constant key="Parameter_4734" name="m37" value="0.8"/>
          <Constant key="Parameter_4733" name="m9" value="1.1"/>
          <Constant key="Parameter_4732" name="p17" value="4.8"/>
          <Constant key="Parameter_4731" name="p18" value="4"/>
          <Constant key="Parameter_4730" name="p24" value="10"/>
          <Constant key="Parameter_4729" name="p28" value="2"/>
          <Constant key="Parameter_4728" name="p29" value="0.1"/>
          <Constant key="Parameter_4727" name="p31" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_91" unitType="Default" scalingCompartment="CN=Root,Model=Alex,Vector=Compartments[def]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_561">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_541">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_553">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_573">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_549">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_577">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_565">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_585">
              <SourceParameter reference="ModelValue_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_589">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_587">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_581">
              <SourceParameter reference="ModelValue_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_569">
              <SourceParameter reference="ModelValue_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_536">
              <SourceParameter reference="ModelValue_67"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_557">
              <SourceParameter reference="ModelValue_71"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_545">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_579">
              <SourceParameter reference="ModelValue_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_571">
              <SourceParameter reference="ModelValue_97"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_575">
              <SourceParameter reference="ModelValue_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_559">
              <SourceParameter reference="ModelValue_104"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_563">
              <SourceParameter reference="ModelValue_108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_567">
              <SourceParameter reference="ModelValue_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_583">
              <SourceParameter reference="ModelValue_111"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfEvents>
      <Event key="Event_4" name="Event" fireAtInitialTime="0" persistentTrigger="1">
        <TriggerExpression>
          &lt;CN=Root,Model=Alex,Reference=Time> gt 96
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="ModelValue_122">
            <Expression>
              0
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_121">
            <Expression>
              1
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
    </ListOfEvents>
    <ListOfModelParameterSets activeSet="ModelParameterSet_1">
      <ModelParameterSet key="ModelParameterSet_1" name="Initial State">
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Alex" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def]" value="1" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cCOP1c]" value="196863815115100" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cCOP1d]" value="154528158331400" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cCOP1n]" value="391439216350000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE3]" value="90512791103700.05" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE3_m]" value="180122260938900.1" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE3n]" value="17223325519400" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE4]" value="124658335053000.1" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE4_m]" value="60944074914800" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cEC]" value="42696985291100" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cEG]" value="2469078133900" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cG]" value="11803397908400" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cG_m]" value="61245182004300" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cL]" value="304720374574000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cLUX]" value="346875367104000.1" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cLUX_m]" value="60944074914800" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cL_m]" value="611307613102899.9" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cLm]" value="47454477305200.02" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cNI]" value="41974328276300" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cNI_m]" value="44021856484900" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP]" value="575716755124000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP7]" value="70278394689300.01" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP7_m]" value="241849214286400" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP9]" value="14332697460200.01" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP9_m]" value="39625692978200" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cT]" value="26196316786500.02" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cT_m]" value="58836325288300.02" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cZG]" value="45467170514500" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cZTL]" value="150854651839500" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n1]" value="2.6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n2]" value="0.64" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n3]" value="0.29" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n4]" value="0.07000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n5]" value="0.23" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n6]" value="20" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n7]" value="0.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n8]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n9]" value="0.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n10]" value="0.4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n11]" value="0.6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n12]" value="12.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n13]" value="1.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[n14]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g1]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g2]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g3]" value="0.6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g4]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g5]" value="0.15" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g6]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g7]" value="0.6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g8]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g9]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g10]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g11]" value="0.7" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g12]" value="0.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g13]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g14]" value="0.004" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g15]" value="0.4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[g16]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m1]" value="0.54" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m2]" value="0.24" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m3]" value="0.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m4]" value="0.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m5]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m6]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m7]" value="0.7" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m8]" value="0.4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m9]" value="1.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m10]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m11]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m12]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m13]" value="0.32" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m14]" value="0.4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m15]" value="0.7" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m16]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m17]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m18]" value="3.4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m19]" value="0.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m20]" value="0.6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m21]" value="0.08" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m22]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m23]" value="1.8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m24]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m25]" value="1.8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m26]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m27]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m28]" value="20" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m29]" value="5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m30]" value="3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m31]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m32]" value="0.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m33]" value="13" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m34]" value="0.6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m35]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m36]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m37]" value="0.8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m38]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[m39]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[a]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[b]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[c]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[d]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[e]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[f]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p1]" value="0.13" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p2]" value="0.27" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p3]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p4]" value="0.5600000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p5]" value="4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p6]" value="0.6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p7]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p8]" value="0.6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p9]" value="0.8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p10]" value="0.54" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p11]" value="0.51" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p12]" value="3.4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p13]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p14]" value="0.14" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p15]" value="3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p16]" value="0.62" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p17]" value="4.8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p18]" value="4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p19]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p20]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p21]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p22]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p23]" value="0.37" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p24]" value="10" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p25]" value="8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p26]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p27]" value="0.8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p28]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p29]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p30]" value="0.9" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[p31]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[q1]" value="1.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[q2]" value="1.56" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[q3]" value="2.8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[L]" value="0.5" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[D]" value="0.5" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[E34]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[Gn]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[EGn]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[Lightstep]" value="0.5" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[offsetStep1]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[amplitudeStep1]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[phaseStep1]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[pulseDurationStep1]" value="12" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[cyclePeriodStep1]" value="24" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Alex,Vector=Values[rampDurationStep1]" value="0.2" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cL_m_trscr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_m_trscr],ParameterGroup=Parameters,Parameter=L" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[L],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_m_trscr],ParameterGroup=Parameters,Parameter=a" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[a],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_m_trscr],ParameterGroup=Parameters,Parameter=g1" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_m_trscr],ParameterGroup=Parameters,Parameter=n1" value="2.6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_m_trscr],ParameterGroup=Parameters,Parameter=q1" value="1.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[q1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cL_m_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_m_degr],ParameterGroup=Parameters,Parameter=D" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[D],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_m_degr],ParameterGroup=Parameters,Parameter=L" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[L],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_m_degr],ParameterGroup=Parameters,Parameter=m1" value="0.54" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_m_degr],ParameterGroup=Parameters,Parameter=m2" value="0.24" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cL_trsl]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_trsl],ParameterGroup=Parameters,Parameter=L" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[L],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_trsl],ParameterGroup=Parameters,Parameter=p1" value="0.13" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_trsl],ParameterGroup=Parameters,Parameter=p2" value="0.27" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cL_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_degr],ParameterGroup=Parameters,Parameter=c" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[c],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_degr],ParameterGroup=Parameters,Parameter=g3" value="0.6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_degr],ParameterGroup=Parameters,Parameter=m3" value="0.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_degr],ParameterGroup=Parameters,Parameter=p3" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cL_modif]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_modif],ParameterGroup=Parameters,Parameter=c" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[c],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_modif],ParameterGroup=Parameters,Parameter=g3" value="0.6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cL_modif],ParameterGroup=Parameters,Parameter=p3" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cLm_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cLm_degr],ParameterGroup=Parameters,Parameter=m4" value="0.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cP_trsl]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP_trsl],ParameterGroup=Parameters,Parameter=D" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[D],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP_trsl],ParameterGroup=Parameters,Parameter=p7" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p7],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cP_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP_degr],ParameterGroup=Parameters,Parameter=L" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[L],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP_degr],ParameterGroup=Parameters,Parameter=m11" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m11],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cP9_m_trscr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP9_m_trscr],ParameterGroup=Parameters,Parameter=L" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[L],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP9_m_trscr],ParameterGroup=Parameters,Parameter=e" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[e],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP9_m_trscr],ParameterGroup=Parameters,Parameter=g8" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g8],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP9_m_trscr],ParameterGroup=Parameters,Parameter=g9" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g9],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP9_m_trscr],ParameterGroup=Parameters,Parameter=n4" value="0.07000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP9_m_trscr],ParameterGroup=Parameters,Parameter=n7" value="0.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n7],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP9_m_trscr],ParameterGroup=Parameters,Parameter=q3" value="2.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[q3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cP9_m_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP9_m_degr],ParameterGroup=Parameters,Parameter=m12" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m12],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cP9_trsl]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP9_trsl],ParameterGroup=Parameters,Parameter=p8" value="0.6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p8],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cP9_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP9_degr],ParameterGroup=Parameters,Parameter=D" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[D],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP9_degr],ParameterGroup=Parameters,Parameter=m13" value="0.32" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m13],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP9_degr],ParameterGroup=Parameters,Parameter=m22" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m22],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cP7_m_trscr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP7_m_trscr],ParameterGroup=Parameters,Parameter=e" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[e],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP7_m_trscr],ParameterGroup=Parameters,Parameter=f" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[f],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP7_m_trscr],ParameterGroup=Parameters,Parameter=g10" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g10],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP7_m_trscr],ParameterGroup=Parameters,Parameter=g11" value="0.7" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g11],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP7_m_trscr],ParameterGroup=Parameters,Parameter=n8" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n8],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP7_m_trscr],ParameterGroup=Parameters,Parameter=n9" value="0.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n9],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cP7_m_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP7_m_degr],ParameterGroup=Parameters,Parameter=m14" value="0.4" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m14],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cP7_trsl]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP7_trsl],ParameterGroup=Parameters,Parameter=p9" value="0.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p9],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cP7_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP7_degr],ParameterGroup=Parameters,Parameter=D" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[D],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP7_degr],ParameterGroup=Parameters,Parameter=m15" value="0.7" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m15],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cP7_degr],ParameterGroup=Parameters,Parameter=m23" value="1.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m23],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cNI_m_trscr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cNI_m_trscr],ParameterGroup=Parameters,Parameter=b" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[b],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cNI_m_trscr],ParameterGroup=Parameters,Parameter=e" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[e],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cNI_m_trscr],ParameterGroup=Parameters,Parameter=g12" value="0.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g12],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cNI_m_trscr],ParameterGroup=Parameters,Parameter=g13" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g13],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cNI_m_trscr],ParameterGroup=Parameters,Parameter=n10" value="0.4" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n10],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cNI_m_trscr],ParameterGroup=Parameters,Parameter=n11" value="0.6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n11],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cNI_m_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cNI_m_degr],ParameterGroup=Parameters,Parameter=m16" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m16],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cNI_trsl]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cNI_trsl],ParameterGroup=Parameters,Parameter=p10" value="0.54" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p10],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cNI_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cNI_degr],ParameterGroup=Parameters,Parameter=D" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[D],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cNI_degr],ParameterGroup=Parameters,Parameter=m17" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m17],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cNI_degr],ParameterGroup=Parameters,Parameter=m24" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m24],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cT_m_trscr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cT_m_trscr],ParameterGroup=Parameters,Parameter=e" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[e],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cT_m_trscr],ParameterGroup=Parameters,Parameter=g4" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cT_m_trscr],ParameterGroup=Parameters,Parameter=g5" value="0.15" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g5],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cT_m_trscr],ParameterGroup=Parameters,Parameter=n2" value="0.64" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cT_m_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cT_m_degr],ParameterGroup=Parameters,Parameter=m5" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m5],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cT_trsl]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cT_trsl],ParameterGroup=Parameters,Parameter=p4" value="0.5600000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cT_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cT_degr],ParameterGroup=Parameters,Parameter=D" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[D],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cT_degr],ParameterGroup=Parameters,Parameter=m6" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cT_degr],ParameterGroup=Parameters,Parameter=m7" value="0.7" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m7],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cT_degr],ParameterGroup=Parameters,Parameter=m8" value="0.4" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m8],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cT_degr],ParameterGroup=Parameters,Parameter=p5" value="4" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p5],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cE4_m_trscr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE4_m_trscr],ParameterGroup=Parameters,Parameter=e" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[e],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE4_m_trscr],ParameterGroup=Parameters,Parameter=g2" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE4_m_trscr],ParameterGroup=Parameters,Parameter=g6" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE4_m_trscr],ParameterGroup=Parameters,Parameter=n13" value="1.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n13],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cE4_m_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE4_m_degr],ParameterGroup=Parameters,Parameter=m34" value="0.6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m34],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cE4_trsl]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE4_trsl],ParameterGroup=Parameters,Parameter=p23" value="0.37" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p23],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cE4_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE4_degr],ParameterGroup=Parameters,Parameter=m35" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m35],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE4_degr],ParameterGroup=Parameters,Parameter=m36" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m36],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE4_degr],ParameterGroup=Parameters,Parameter=m37" value="0.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m37],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE4_degr],ParameterGroup=Parameters,Parameter=p21" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p21],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE4_degr],ParameterGroup=Parameters,Parameter=p25" value="8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p25],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE4_degr],ParameterGroup=Parameters,Parameter=p26" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p26],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cE3_m_trscr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3_m_trscr],ParameterGroup=Parameters,Parameter=e" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[e],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3_m_trscr],ParameterGroup=Parameters,Parameter=g16" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g16],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3_m_trscr],ParameterGroup=Parameters,Parameter=n3" value="0.29" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cE3_m_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3_m_degr],ParameterGroup=Parameters,Parameter=m26" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m26],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cE3_trsl]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3_trsl],ParameterGroup=Parameters,Parameter=p16" value="0.62" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p16],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cE3_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3_degr],ParameterGroup=Parameters,Parameter=m9" value="1.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m9],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_import]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_import],ParameterGroup=Parameters,Parameter=p19" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p19],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_import],ParameterGroup=Parameters,Parameter=p20" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p20],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_degr],ParameterGroup=Parameters,Parameter=m19" value="0.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m19],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_degr],ParameterGroup=Parameters,Parameter=m29" value="5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m29],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_degr],ParameterGroup=Parameters,Parameter=m30" value="3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m30],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_degr],ParameterGroup=Parameters,Parameter=m36" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m36],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_degr],ParameterGroup=Parameters,Parameter=m37" value="0.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m37],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_degr],ParameterGroup=Parameters,Parameter=p17" value="4.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p17],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_degr],ParameterGroup=Parameters,Parameter=p21" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p21],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_degr],ParameterGroup=Parameters,Parameter=p25" value="8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p25],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_degr],ParameterGroup=Parameters,Parameter=p26" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p26],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_degr],ParameterGroup=Parameters,Parameter=p28" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p28],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cE3n_degr],ParameterGroup=Parameters,Parameter=p29" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p29],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_m_trscr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_m_trscr],ParameterGroup=Parameters,Parameter=e" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[e],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_m_trscr],ParameterGroup=Parameters,Parameter=g2" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_m_trscr],ParameterGroup=Parameters,Parameter=g6" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_m_trscr],ParameterGroup=Parameters,Parameter=n13" value="1.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n13],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_m_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_m_degr],ParameterGroup=Parameters,Parameter=m34" value="0.6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m34],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_trsl]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_trsl],ParameterGroup=Parameters,Parameter=p27" value="0.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p27],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_degr],ParameterGroup=Parameters,Parameter=m36" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m36],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_degr],ParameterGroup=Parameters,Parameter=m37" value="0.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m37],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_degr],ParameterGroup=Parameters,Parameter=m39" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m39],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_degr],ParameterGroup=Parameters,Parameter=p21" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p21],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_degr],ParameterGroup=Parameters,Parameter=p25" value="8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p25],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cLUX_degr],ParameterGroup=Parameters,Parameter=p26" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p26],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1c_trsl]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1c_trsl],ParameterGroup=Parameters,Parameter=n5" value="0.23" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n5],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1c_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1c_degr],ParameterGroup=Parameters,Parameter=L" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[L],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1c_degr],ParameterGroup=Parameters,Parameter=m27" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m27],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1c_degr],ParameterGroup=Parameters,Parameter=p15" value="3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p15],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1n_import]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1n_import],ParameterGroup=Parameters,Parameter=p6" value="0.6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1n_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1n_degr],ParameterGroup=Parameters,Parameter=L" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[L],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1n_degr],ParameterGroup=Parameters,Parameter=m27" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m27],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1n_degr],ParameterGroup=Parameters,Parameter=p15" value="3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p15],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1d_activ]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1d_activ],ParameterGroup=Parameters,Parameter=L" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[L],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1d_activ],ParameterGroup=Parameters,Parameter=n14" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n14],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1d_activ],ParameterGroup=Parameters,Parameter=n6" value="20" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1d_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1d_degr],ParameterGroup=Parameters,Parameter=D" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[D],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1d_degr],ParameterGroup=Parameters,Parameter=m31" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m31],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cCOP1d_degr],ParameterGroup=Parameters,Parameter=m33" value="13" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m33],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cG_m_trscr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_m_trscr],ParameterGroup=Parameters,Parameter=L" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[L],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_m_trscr],ParameterGroup=Parameters,Parameter=e" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[e],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_m_trscr],ParameterGroup=Parameters,Parameter=g14" value="0.004" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g14],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_m_trscr],ParameterGroup=Parameters,Parameter=g15" value="0.4" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g15],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_m_trscr],ParameterGroup=Parameters,Parameter=n12" value="12.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[n12],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_m_trscr],ParameterGroup=Parameters,Parameter=q2" value="1.56" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[q2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cG_m_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_m_degr],ParameterGroup=Parameters,Parameter=m18" value="3.4" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m18],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cG_trsl]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_trsl],ParameterGroup=Parameters,Parameter=p11" value="0.51" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p11],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cG_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_degr],ParameterGroup=Parameters,Parameter=m19" value="0.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m19],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_degr],ParameterGroup=Parameters,Parameter=p17" value="4.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p17],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_degr],ParameterGroup=Parameters,Parameter=p28" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p28],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_degr],ParameterGroup=Parameters,Parameter=p29" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p29],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cG_cZTL_assoc]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_cZTL_assoc],ParameterGroup=Parameters,Parameter=D" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[D],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_cZTL_assoc],ParameterGroup=Parameters,Parameter=L" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[L],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_cZTL_assoc],ParameterGroup=Parameters,Parameter=p12" value="3.4" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p12],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_cZTL_assoc],ParameterGroup=Parameters,Parameter=p13" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p13],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cZTL_trsl]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cZTL_trsl],ParameterGroup=Parameters,Parameter=p14" value="0.14" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p14],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cZTL_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cZTL_degr],ParameterGroup=Parameters,Parameter=m20" value="0.6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m20],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cZG_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cZG_degr],ParameterGroup=Parameters,Parameter=m21" value="0.08" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m21],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cG_cE3_assoc]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cG_cE3_assoc],ParameterGroup=Parameters,Parameter=p17" value="4.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p17],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cEG_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEG_degr],ParameterGroup=Parameters,Parameter=m10" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m10],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEG_degr],ParameterGroup=Parameters,Parameter=m19" value="0.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m19],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEG_degr],ParameterGroup=Parameters,Parameter=m9" value="1.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m9],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEG_degr],ParameterGroup=Parameters,Parameter=p17" value="4.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p17],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEG_degr],ParameterGroup=Parameters,Parameter=p18" value="4" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p18],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEG_degr],ParameterGroup=Parameters,Parameter=p28" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p28],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEG_degr],ParameterGroup=Parameters,Parameter=p29" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p29],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEG_degr],ParameterGroup=Parameters,Parameter=p31" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p31],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cEC_form]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_form],ParameterGroup=Parameters,Parameter=m36" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m36],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_form],ParameterGroup=Parameters,Parameter=m37" value="0.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m37],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_form],ParameterGroup=Parameters,Parameter=p21" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p21],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_form],ParameterGroup=Parameters,Parameter=p25" value="8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p25],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_form],ParameterGroup=Parameters,Parameter=p26" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p26],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=L" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[L],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=d" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[d],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=g7" value="0.6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[g7],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=m10" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m10],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=m19" value="0.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m19],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=m32" value="0.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m32],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=m36" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m36],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=m37" value="0.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m37],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=m9" value="1.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[m9],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=p17" value="4.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p17],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=p18" value="4" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p18],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=p24" value="10" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p24],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=p28" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p28],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=p29" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p29],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Alex,Vector=Reactions[cEC_degr],ParameterGroup=Parameters,Parameter=p31" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Alex,Vector=Values[p31],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_5"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_55"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Metabolite_27"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_31"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_35"/>
      <StateTemplateVariable objectReference="Metabolite_37"/>
      <StateTemplateVariable objectReference="Metabolite_39"/>
      <StateTemplateVariable objectReference="Metabolite_41"/>
      <StateTemplateVariable objectReference="Metabolite_43"/>
      <StateTemplateVariable objectReference="Metabolite_45"/>
      <StateTemplateVariable objectReference="Metabolite_47"/>
      <StateTemplateVariable objectReference="Metabolite_49"/>
      <StateTemplateVariable objectReference="Metabolite_51"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_11"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_53"/>
      <StateTemplateVariable objectReference="ModelValue_115"/>
      <StateTemplateVariable objectReference="ModelValue_116"/>
      <StateTemplateVariable objectReference="ModelValue_120"/>
      <StateTemplateVariable objectReference="Compartment_1"/>
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
      <StateTemplateVariable objectReference="ModelValue_97"/>
      <StateTemplateVariable objectReference="ModelValue_98"/>
      <StateTemplateVariable objectReference="ModelValue_99"/>
      <StateTemplateVariable objectReference="ModelValue_100"/>
      <StateTemplateVariable objectReference="ModelValue_101"/>
      <StateTemplateVariable objectReference="ModelValue_102"/>
      <StateTemplateVariable objectReference="ModelValue_103"/>
      <StateTemplateVariable objectReference="ModelValue_104"/>
      <StateTemplateVariable objectReference="ModelValue_105"/>
      <StateTemplateVariable objectReference="ModelValue_106"/>
      <StateTemplateVariable objectReference="ModelValue_107"/>
      <StateTemplateVariable objectReference="ModelValue_108"/>
      <StateTemplateVariable objectReference="ModelValue_109"/>
      <StateTemplateVariable objectReference="ModelValue_110"/>
      <StateTemplateVariable objectReference="ModelValue_111"/>
      <StateTemplateVariable objectReference="ModelValue_112"/>
      <StateTemplateVariable objectReference="ModelValue_113"/>
      <StateTemplateVariable objectReference="ModelValue_114"/>
      <StateTemplateVariable objectReference="ModelValue_117"/>
      <StateTemplateVariable objectReference="ModelValue_118"/>
      <StateTemplateVariable objectReference="ModelValue_119"/>
      <StateTemplateVariable objectReference="ModelValue_121"/>
      <StateTemplateVariable objectReference="ModelValue_122"/>
      <StateTemplateVariable objectReference="ModelValue_123"/>
      <StateTemplateVariable objectReference="ModelValue_124"/>
      <StateTemplateVariable objectReference="ModelValue_125"/>
      <StateTemplateVariable objectReference="ModelValue_126"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 90512791103700.05 11803397908400 391439216350000 150854651839500 196863815115100 124658335053000.1 60944074914800 42696985291100 61245182004300 304720374574000 346875367104000.1 60944074914800 611307613102899.9 47454477305200.02 41974328276300 44021856484900 575716755124000 70278394689300.01 241849214286400 14332697460200.01 39625692978200 26196316786500.02 58836325288300.02 180122260938900.1 17223325519400 154528158331400 2469078133900 45467170514500 0.5 0.5 0.5 1 2.6 0.64 0.29 0.07000000000000001 0.23 20 0.2 0.5 0.2 0.4 0.6 12.5 1.3 0.1 0.1 0.01 0.6 0.01 0.15 0.3 0.6 0.01 0.3 0.5 0.7 0.2 1 0.004 0.4 0.3 0.54 0.24 0.2 0.2 0.3 0.3 0.7 0.4 1.1 1 1 1 0.32 0.4 0.7 0.5 0.5 3.4 0.2 0.6 0.08 0.1 1.8 0.1 1.8 0.5 0.1 20 5 3 0.3 0.2 13 0.6 0.3 0.1 0.8 0.5 0.3 2 2 2 2 2 2 0.13 0.27 0.1 0.5600000000000001 4 0.6 0.3 0.6 0.8 0.54 0.51 3.4 0.1 0.14 3 0.62 4.8 4 1 0.1 1 0.5 0.37 10 8 0.3 0.8 2 0.1 0.9 0.1 1.2 1.56 2.8 1 1 1 0 1 0 12 24 0.2 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_26" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_17" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_25" name="Time-Course" type="timeCourse" scheduled="true" updateModel="false">
      <Report reference="Report_19" target="EventTest28.1.txt" append="0" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="1"/>
        <Parameter name="Duration" type="float" value="100"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_24" name="Scan" type="scan" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="1"/>
        <ParameterGroup name="ScanItems">
        </ParameterGroup>
        <Parameter name="Output in subtask" type="bool" value="1"/>
        <Parameter name="Adjust initial conditions" type="bool" value="0"/>
      </Problem>
      <Method name="Scan Framework" type="ScanFramework">
      </Method>
    </Task>
    <Task key="Task_23" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_16" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_22" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_15" target="" append="1" confirmOverwrite="1"/>
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
        <Parameter name="Steady-State" type="key" value="Task_26"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1e-09"/>
        <Parameter name="Use Reder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
      </Method>
    </Task>
    <Task key="Task_19" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_12" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_18" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_11" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_17" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_10" target="" append="1" confirmOverwrite="1"/>
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
        <Parameter name="Delta minimum" type="unsignedFloat" value="1e-12"/>
      </Method>
    </Task>
    <Task key="Task_16" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_15" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
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
        <Parameter name="ConvergenceTolerance" type="float" value="1e-06"/>
        <Parameter name="Threshold" type="float" value="0"/>
        <Parameter name="DelayOutputUntilConvergence" type="bool" value="0"/>
        <Parameter name="OutputConvergenceTolerance" type="float" value="1e-06"/>
        <ParameterText name="TriggerExpression" type="expression">
          
        </ParameterText>
        <Parameter name="SingleVariable" type="cn" value=""/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_27" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_9" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_26"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_17" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_16" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_15" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_12" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <Report key="Report_11" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_10" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_9" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <Report key="Report_19" name="Time, Concentrations, Volumes, and Global Quantity Values" taskType="timeCourse" separator="&#x09;" precision="6">
      <Comment>
        A table of time, variable species concentrations, variable compartment volumes, and variable global quantity values.
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Model=Alex,Reference=Time"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cCOP1c],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cCOP1d],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cCOP1n],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE3],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE3_m],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE3n],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE4],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE4_m],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cEC],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cEG],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cG],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cG_m],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cL],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cLUX],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cLUX_m],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cL_m],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cLm],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cNI],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cNI_m],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP7],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP7_m],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP9],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP9_m],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cT],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cT_m],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cZG],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cZTL],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Alex,Vector=Values[L],Reference=Value"/>
        <Object cn="CN=Root,Model=Alex,Vector=Values[D],Reference=Value"/>
        <Object cn="CN=Root,Model=Alex,Vector=Values[Lightstep],Reference=Value"/>
        <Object cn="CN=Root,Model=Alex,Vector=Values[offsetStep1],Reference=Value"/>
        <Object cn="CN=Root,Model=Alex,Vector=Values[amplitudeStep1],Reference=Value"/>
      </Table>
    </Report>
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="Concentrations, Volumes, and Global Quantity Values" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="[cCOP1c]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cCOP1c],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cCOP1d]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cCOP1d],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cCOP1n]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cCOP1n],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cE3]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE3],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cE3_m]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE3_m],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cE3n]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE3n],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cE4]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE4],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cE4_m]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cE4_m],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cEC]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cEC],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cEG]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cEG],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cG]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cG],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cG_m]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cG_m],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cL]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cL],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cLUX]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cLUX],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cLUX_m]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cLUX_m],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cL_m]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cL_m],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cLm]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cLm],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cNI]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cNI],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cNI_m]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cNI_m],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cP]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cP7]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP7],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cP7_m]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP7_m],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cP9]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP9],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cP9_m]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cP9_m],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cT]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cT],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cT_m]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cT_m],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cZG]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cZG],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[cZTL]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Compartments[def],Vector=Metabolites[cZTL],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[L]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Values[L],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[D]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Values[D],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Lightstep]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Values[Lightstep],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[offsetStep1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Values[offsetStep1],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[amplitudeStep1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Alex,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Alex,Vector=Values[amplitudeStep1],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
  </GUI>
  <SBMLReference file="Bug1912b.xml">
    <SBMLMap SBMLid="D" COPASIkey="ModelValue_116"/>
    <SBMLMap SBMLid="E34" COPASIkey="ModelValue_117"/>
    <SBMLMap SBMLid="EGn" COPASIkey="ModelValue_119"/>
    <SBMLMap SBMLid="Gn" COPASIkey="ModelValue_118"/>
    <SBMLMap SBMLid="L" COPASIkey="ModelValue_115"/>
    <SBMLMap SBMLid="a" COPASIkey="ModelValue_75"/>
    <SBMLMap SBMLid="amplitudeStep1" COPASIkey="ModelValue_122"/>
    <SBMLMap SBMLid="b" COPASIkey="ModelValue_76"/>
    <SBMLMap SBMLid="c" COPASIkey="ModelValue_77"/>
    <SBMLMap SBMLid="cCOP1c" COPASIkey="Metabolite_1"/>
    <SBMLMap SBMLid="cCOP1c_degr" COPASIkey="Reaction_39"/>
    <SBMLMap SBMLid="cCOP1c_trsl" COPASIkey="Reaction_38"/>
    <SBMLMap SBMLid="cCOP1d" COPASIkey="Metabolite_3"/>
    <SBMLMap SBMLid="cCOP1d_activ" COPASIkey="Reaction_42"/>
    <SBMLMap SBMLid="cCOP1d_degr" COPASIkey="Reaction_43"/>
    <SBMLMap SBMLid="cCOP1n" COPASIkey="Metabolite_5"/>
    <SBMLMap SBMLid="cCOP1n_degr" COPASIkey="Reaction_41"/>
    <SBMLMap SBMLid="cCOP1n_import" COPASIkey="Reaction_40"/>
    <SBMLMap SBMLid="cE3" COPASIkey="Metabolite_7"/>
    <SBMLMap SBMLid="cE3_degr" COPASIkey="Reaction_31"/>
    <SBMLMap SBMLid="cE3_m" COPASIkey="Metabolite_9"/>
    <SBMLMap SBMLid="cE3_m_degr" COPASIkey="Reaction_29"/>
    <SBMLMap SBMLid="cE3_m_trscr" COPASIkey="Reaction_28"/>
    <SBMLMap SBMLid="cE3_trsl" COPASIkey="Reaction_30"/>
    <SBMLMap SBMLid="cE3n" COPASIkey="Metabolite_11"/>
    <SBMLMap SBMLid="cE3n_degr" COPASIkey="Reaction_33"/>
    <SBMLMap SBMLid="cE3n_import" COPASIkey="Reaction_32"/>
    <SBMLMap SBMLid="cE4" COPASIkey="Metabolite_13"/>
    <SBMLMap SBMLid="cE4_degr" COPASIkey="Reaction_27"/>
    <SBMLMap SBMLid="cE4_m" COPASIkey="Metabolite_15"/>
    <SBMLMap SBMLid="cE4_m_degr" COPASIkey="Reaction_25"/>
    <SBMLMap SBMLid="cE4_m_trscr" COPASIkey="Reaction_24"/>
    <SBMLMap SBMLid="cE4_trsl" COPASIkey="Reaction_26"/>
    <SBMLMap SBMLid="cEC" COPASIkey="Metabolite_17"/>
    <SBMLMap SBMLid="cEC_degr" COPASIkey="Reaction_55"/>
    <SBMLMap SBMLid="cEC_form" COPASIkey="Reaction_54"/>
    <SBMLMap SBMLid="cEG" COPASIkey="Metabolite_19"/>
    <SBMLMap SBMLid="cEG_degr" COPASIkey="Reaction_53"/>
    <SBMLMap SBMLid="cG" COPASIkey="Metabolite_21"/>
    <SBMLMap SBMLid="cG_cE3_assoc" COPASIkey="Reaction_52"/>
    <SBMLMap SBMLid="cG_cZTL_assoc" COPASIkey="Reaction_48"/>
    <SBMLMap SBMLid="cG_degr" COPASIkey="Reaction_47"/>
    <SBMLMap SBMLid="cG_m" COPASIkey="Metabolite_23"/>
    <SBMLMap SBMLid="cG_m_degr" COPASIkey="Reaction_45"/>
    <SBMLMap SBMLid="cG_m_trscr" COPASIkey="Reaction_44"/>
    <SBMLMap SBMLid="cG_trsl" COPASIkey="Reaction_46"/>
    <SBMLMap SBMLid="cL" COPASIkey="Metabolite_25"/>
    <SBMLMap SBMLid="cLUX" COPASIkey="Metabolite_27"/>
    <SBMLMap SBMLid="cLUX_degr" COPASIkey="Reaction_37"/>
    <SBMLMap SBMLid="cLUX_m" COPASIkey="Metabolite_29"/>
    <SBMLMap SBMLid="cLUX_m_degr" COPASIkey="Reaction_35"/>
    <SBMLMap SBMLid="cLUX_m_trscr" COPASIkey="Reaction_34"/>
    <SBMLMap SBMLid="cLUX_trsl" COPASIkey="Reaction_36"/>
    <SBMLMap SBMLid="cL_degr" COPASIkey="Reaction_3"/>
    <SBMLMap SBMLid="cL_m" COPASIkey="Metabolite_31"/>
    <SBMLMap SBMLid="cL_m_degr" COPASIkey="Reaction_1"/>
    <SBMLMap SBMLid="cL_m_trscr" COPASIkey="Reaction_0"/>
    <SBMLMap SBMLid="cL_modif" COPASIkey="Reaction_4"/>
    <SBMLMap SBMLid="cL_trsl" COPASIkey="Reaction_2"/>
    <SBMLMap SBMLid="cLm" COPASIkey="Metabolite_33"/>
    <SBMLMap SBMLid="cLm_degr" COPASIkey="Reaction_5"/>
    <SBMLMap SBMLid="cNI" COPASIkey="Metabolite_35"/>
    <SBMLMap SBMLid="cNI_degr" COPASIkey="Reaction_19"/>
    <SBMLMap SBMLid="cNI_m" COPASIkey="Metabolite_37"/>
    <SBMLMap SBMLid="cNI_m_degr" COPASIkey="Reaction_17"/>
    <SBMLMap SBMLid="cNI_m_trscr" COPASIkey="Reaction_16"/>
    <SBMLMap SBMLid="cNI_trsl" COPASIkey="Reaction_18"/>
    <SBMLMap SBMLid="cP" COPASIkey="Metabolite_39"/>
    <SBMLMap SBMLid="cP7" COPASIkey="Metabolite_41"/>
    <SBMLMap SBMLid="cP7_degr" COPASIkey="Reaction_15"/>
    <SBMLMap SBMLid="cP7_m" COPASIkey="Metabolite_43"/>
    <SBMLMap SBMLid="cP7_m_degr" COPASIkey="Reaction_13"/>
    <SBMLMap SBMLid="cP7_m_trscr" COPASIkey="Reaction_12"/>
    <SBMLMap SBMLid="cP7_trsl" COPASIkey="Reaction_14"/>
    <SBMLMap SBMLid="cP9" COPASIkey="Metabolite_45"/>
    <SBMLMap SBMLid="cP9_degr" COPASIkey="Reaction_11"/>
    <SBMLMap SBMLid="cP9_m" COPASIkey="Metabolite_47"/>
    <SBMLMap SBMLid="cP9_m_degr" COPASIkey="Reaction_9"/>
    <SBMLMap SBMLid="cP9_m_trscr" COPASIkey="Reaction_8"/>
    <SBMLMap SBMLid="cP9_trsl" COPASIkey="Reaction_10"/>
    <SBMLMap SBMLid="cP_degr" COPASIkey="Reaction_7"/>
    <SBMLMap SBMLid="cP_trsl" COPASIkey="Reaction_6"/>
    <SBMLMap SBMLid="cT" COPASIkey="Metabolite_49"/>
    <SBMLMap SBMLid="cT_degr" COPASIkey="Reaction_23"/>
    <SBMLMap SBMLid="cT_m" COPASIkey="Metabolite_51"/>
    <SBMLMap SBMLid="cT_m_degr" COPASIkey="Reaction_21"/>
    <SBMLMap SBMLid="cT_m_trscr" COPASIkey="Reaction_20"/>
    <SBMLMap SBMLid="cT_trsl" COPASIkey="Reaction_22"/>
    <SBMLMap SBMLid="cZG" COPASIkey="Metabolite_53"/>
    <SBMLMap SBMLid="cZG_degr" COPASIkey="Reaction_51"/>
    <SBMLMap SBMLid="cZTL" COPASIkey="Metabolite_55"/>
    <SBMLMap SBMLid="cZTL_degr" COPASIkey="Reaction_50"/>
    <SBMLMap SBMLid="cZTL_trsl" COPASIkey="Reaction_49"/>
    <SBMLMap SBMLid="cyclePeriodStep1" COPASIkey="ModelValue_125"/>
    <SBMLMap SBMLid="d" COPASIkey="ModelValue_78"/>
    <SBMLMap SBMLid="def" COPASIkey="Compartment_1"/>
    <SBMLMap SBMLid="e" COPASIkey="ModelValue_79"/>
    <SBMLMap SBMLid="f" COPASIkey="ModelValue_80"/>
    <SBMLMap SBMLid="function_4_cCOP1c_degr" COPASIkey="Function_83"/>
    <SBMLMap SBMLid="function_4_cCOP1c_trsl" COPASIkey="Function_70"/>
    <SBMLMap SBMLid="function_4_cCOP1d_activ" COPASIkey="Function_75"/>
    <SBMLMap SBMLid="function_4_cCOP1d_degr" COPASIkey="Function_87"/>
    <SBMLMap SBMLid="function_4_cCOP1n_degr" COPASIkey="Function_65"/>
    <SBMLMap SBMLid="function_4_cCOP1n_import" COPASIkey="Function_64"/>
    <SBMLMap SBMLid="function_4_cE3_degr" COPASIkey="Function_62"/>
    <SBMLMap SBMLid="function_4_cE3_m_degr" COPASIkey="Function_82"/>
    <SBMLMap SBMLid="function_4_cE3_m_trscr" COPASIkey="Function_81"/>
    <SBMLMap SBMLid="function_4_cE3_trsl" COPASIkey="Function_61"/>
    <SBMLMap SBMLid="function_4_cE3n_degr" COPASIkey="Function_67"/>
    <SBMLMap SBMLid="function_4_cE3n_import" COPASIkey="Function_63"/>
    <SBMLMap SBMLid="function_4_cE4_degr" COPASIkey="Function_60"/>
    <SBMLMap SBMLid="function_4_cE4_m_degr" COPASIkey="Function_79"/>
    <SBMLMap SBMLid="function_4_cE4_m_trscr_1" COPASIkey="Function_42"/>
    <SBMLMap SBMLid="function_4_cE4_trsl" COPASIkey="Function_78"/>
    <SBMLMap SBMLid="function_4_cEC_degr" COPASIkey="Function_91"/>
    <SBMLMap SBMLid="function_4_cEC_form" COPASIkey="Function_90"/>
    <SBMLMap SBMLid="function_4_cEG_degr" COPASIkey="Function_93"/>
    <SBMLMap SBMLid="function_4_cG_cE3_assoc" COPASIkey="Function_95"/>
    <SBMLMap SBMLid="function_4_cG_cZTL_assoc" COPASIkey="Function_92"/>
    <SBMLMap SBMLid="function_4_cG_degr" COPASIkey="Function_86"/>
    <SBMLMap SBMLid="function_4_cG_m_degr" COPASIkey="Function_88"/>
    <SBMLMap SBMLid="function_4_cG_m_trscr_1" COPASIkey="Function_85"/>
    <SBMLMap SBMLid="function_4_cG_trsl" COPASIkey="Function_89"/>
    <SBMLMap SBMLid="function_4_cLUX_degr" COPASIkey="Function_69"/>
    <SBMLMap SBMLid="function_4_cLUX_m_degr" COPASIkey="Function_68"/>
    <SBMLMap SBMLid="function_4_cLUX_m_trscr" COPASIkey="Function_43"/>
    <SBMLMap SBMLid="function_4_cLUX_trsl" COPASIkey="Function_84"/>
    <SBMLMap SBMLid="function_4_cL_degr" COPASIkey="Function_45"/>
    <SBMLMap SBMLid="function_4_cL_m_degr" COPASIkey="Function_44"/>
    <SBMLMap SBMLid="function_4_cL_m_trscr" COPASIkey="Function_41"/>
    <SBMLMap SBMLid="function_4_cL_modif" COPASIkey="Function_46"/>
    <SBMLMap SBMLid="function_4_cL_trsl" COPASIkey="Function_71"/>
    <SBMLMap SBMLid="function_4_cLm_degr" COPASIkey="Function_47"/>
    <SBMLMap SBMLid="function_4_cNI_degr" COPASIkey="Function_59"/>
    <SBMLMap SBMLid="function_4_cNI_m_degr" COPASIkey="Function_57"/>
    <SBMLMap SBMLid="function_4_cNI_m_trscr" COPASIkey="Function_56"/>
    <SBMLMap SBMLid="function_4_cNI_trsl" COPASIkey="Function_58"/>
    <SBMLMap SBMLid="function_4_cP7_degr" COPASIkey="Function_55"/>
    <SBMLMap SBMLid="function_4_cP7_m_degr" COPASIkey="Function_53"/>
    <SBMLMap SBMLid="function_4_cP7_m_trscr" COPASIkey="Function_52"/>
    <SBMLMap SBMLid="function_4_cP7_trsl" COPASIkey="Function_54"/>
    <SBMLMap SBMLid="function_4_cP9_degr" COPASIkey="Function_51"/>
    <SBMLMap SBMLid="function_4_cP9_m_degr" COPASIkey="Function_73"/>
    <SBMLMap SBMLid="function_4_cP9_m_trscr_1" COPASIkey="Function_72"/>
    <SBMLMap SBMLid="function_4_cP9_trsl" COPASIkey="Function_50"/>
    <SBMLMap SBMLid="function_4_cP_degr" COPASIkey="Function_49"/>
    <SBMLMap SBMLid="function_4_cP_trsl" COPASIkey="Function_48"/>
    <SBMLMap SBMLid="function_4_cT_degr" COPASIkey="Function_76"/>
    <SBMLMap SBMLid="function_4_cT_m_degr" COPASIkey="Function_80"/>
    <SBMLMap SBMLid="function_4_cT_m_trscr_1" COPASIkey="Function_74"/>
    <SBMLMap SBMLid="function_4_cT_trsl" COPASIkey="Function_77"/>
    <SBMLMap SBMLid="function_4_cZG_degr" COPASIkey="Function_66"/>
    <SBMLMap SBMLid="function_4_cZTL_degr" COPASIkey="Function_96"/>
    <SBMLMap SBMLid="function_4_cZTL_trsl" COPASIkey="Function_94"/>
    <SBMLMap SBMLid="g1" COPASIkey="ModelValue_20"/>
    <SBMLMap SBMLid="g10" COPASIkey="ModelValue_29"/>
    <SBMLMap SBMLid="g11" COPASIkey="ModelValue_30"/>
    <SBMLMap SBMLid="g12" COPASIkey="ModelValue_31"/>
    <SBMLMap SBMLid="g13" COPASIkey="ModelValue_32"/>
    <SBMLMap SBMLid="g14" COPASIkey="ModelValue_33"/>
    <SBMLMap SBMLid="g15" COPASIkey="ModelValue_34"/>
    <SBMLMap SBMLid="g16" COPASIkey="ModelValue_35"/>
    <SBMLMap SBMLid="g2" COPASIkey="ModelValue_21"/>
    <SBMLMap SBMLid="g3" COPASIkey="ModelValue_22"/>
    <SBMLMap SBMLid="g4" COPASIkey="ModelValue_23"/>
    <SBMLMap SBMLid="g5" COPASIkey="ModelValue_24"/>
    <SBMLMap SBMLid="g6" COPASIkey="ModelValue_25"/>
    <SBMLMap SBMLid="g7" COPASIkey="ModelValue_26"/>
    <SBMLMap SBMLid="g8" COPASIkey="ModelValue_27"/>
    <SBMLMap SBMLid="g9" COPASIkey="ModelValue_28"/>
    <SBMLMap SBMLid="m1" COPASIkey="ModelValue_36"/>
    <SBMLMap SBMLid="m10" COPASIkey="ModelValue_45"/>
    <SBMLMap SBMLid="m11" COPASIkey="ModelValue_46"/>
    <SBMLMap SBMLid="m12" COPASIkey="ModelValue_47"/>
    <SBMLMap SBMLid="m13" COPASIkey="ModelValue_48"/>
    <SBMLMap SBMLid="m14" COPASIkey="ModelValue_49"/>
    <SBMLMap SBMLid="m15" COPASIkey="ModelValue_50"/>
    <SBMLMap SBMLid="m16" COPASIkey="ModelValue_51"/>
    <SBMLMap SBMLid="m17" COPASIkey="ModelValue_52"/>
    <SBMLMap SBMLid="m18" COPASIkey="ModelValue_53"/>
    <SBMLMap SBMLid="m19" COPASIkey="ModelValue_54"/>
    <SBMLMap SBMLid="m2" COPASIkey="ModelValue_37"/>
    <SBMLMap SBMLid="m20" COPASIkey="ModelValue_55"/>
    <SBMLMap SBMLid="m21" COPASIkey="ModelValue_56"/>
    <SBMLMap SBMLid="m22" COPASIkey="ModelValue_57"/>
    <SBMLMap SBMLid="m23" COPASIkey="ModelValue_58"/>
    <SBMLMap SBMLid="m24" COPASIkey="ModelValue_59"/>
    <SBMLMap SBMLid="m25" COPASIkey="ModelValue_60"/>
    <SBMLMap SBMLid="m26" COPASIkey="ModelValue_61"/>
    <SBMLMap SBMLid="m27" COPASIkey="ModelValue_62"/>
    <SBMLMap SBMLid="m28" COPASIkey="ModelValue_63"/>
    <SBMLMap SBMLid="m29" COPASIkey="ModelValue_64"/>
    <SBMLMap SBMLid="m3" COPASIkey="ModelValue_38"/>
    <SBMLMap SBMLid="m30" COPASIkey="ModelValue_65"/>
    <SBMLMap SBMLid="m31" COPASIkey="ModelValue_66"/>
    <SBMLMap SBMLid="m32" COPASIkey="ModelValue_67"/>
    <SBMLMap SBMLid="m33" COPASIkey="ModelValue_68"/>
    <SBMLMap SBMLid="m34" COPASIkey="ModelValue_69"/>
    <SBMLMap SBMLid="m35" COPASIkey="ModelValue_70"/>
    <SBMLMap SBMLid="m36" COPASIkey="ModelValue_71"/>
    <SBMLMap SBMLid="m37" COPASIkey="ModelValue_72"/>
    <SBMLMap SBMLid="m38" COPASIkey="ModelValue_73"/>
    <SBMLMap SBMLid="m39" COPASIkey="ModelValue_74"/>
    <SBMLMap SBMLid="m4" COPASIkey="ModelValue_39"/>
    <SBMLMap SBMLid="m5" COPASIkey="ModelValue_40"/>
    <SBMLMap SBMLid="m6" COPASIkey="ModelValue_41"/>
    <SBMLMap SBMLid="m7" COPASIkey="ModelValue_42"/>
    <SBMLMap SBMLid="m8" COPASIkey="ModelValue_43"/>
    <SBMLMap SBMLid="m9" COPASIkey="ModelValue_44"/>
    <SBMLMap SBMLid="n1" COPASIkey="ModelValue_6"/>
    <SBMLMap SBMLid="n10" COPASIkey="ModelValue_15"/>
    <SBMLMap SBMLid="n11" COPASIkey="ModelValue_16"/>
    <SBMLMap SBMLid="n12" COPASIkey="ModelValue_17"/>
    <SBMLMap SBMLid="n13" COPASIkey="ModelValue_18"/>
    <SBMLMap SBMLid="n14" COPASIkey="ModelValue_19"/>
    <SBMLMap SBMLid="n2" COPASIkey="ModelValue_7"/>
    <SBMLMap SBMLid="n3" COPASIkey="ModelValue_8"/>
    <SBMLMap SBMLid="n4" COPASIkey="ModelValue_9"/>
    <SBMLMap SBMLid="n5" COPASIkey="ModelValue_10"/>
    <SBMLMap SBMLid="n6" COPASIkey="ModelValue_11"/>
    <SBMLMap SBMLid="n7" COPASIkey="ModelValue_12"/>
    <SBMLMap SBMLid="n8" COPASIkey="ModelValue_13"/>
    <SBMLMap SBMLid="n9" COPASIkey="ModelValue_14"/>
    <SBMLMap SBMLid="offsetStep1" COPASIkey="ModelValue_121"/>
    <SBMLMap SBMLid="p1" COPASIkey="ModelValue_81"/>
    <SBMLMap SBMLid="p10" COPASIkey="ModelValue_90"/>
    <SBMLMap SBMLid="p11" COPASIkey="ModelValue_91"/>
    <SBMLMap SBMLid="p12" COPASIkey="ModelValue_92"/>
    <SBMLMap SBMLid="p13" COPASIkey="ModelValue_93"/>
    <SBMLMap SBMLid="p14" COPASIkey="ModelValue_94"/>
    <SBMLMap SBMLid="p15" COPASIkey="ModelValue_95"/>
    <SBMLMap SBMLid="p16" COPASIkey="ModelValue_96"/>
    <SBMLMap SBMLid="p17" COPASIkey="ModelValue_97"/>
    <SBMLMap SBMLid="p18" COPASIkey="ModelValue_98"/>
    <SBMLMap SBMLid="p19" COPASIkey="ModelValue_99"/>
    <SBMLMap SBMLid="p2" COPASIkey="ModelValue_82"/>
    <SBMLMap SBMLid="p20" COPASIkey="ModelValue_100"/>
    <SBMLMap SBMLid="p21" COPASIkey="ModelValue_101"/>
    <SBMLMap SBMLid="p22" COPASIkey="ModelValue_102"/>
    <SBMLMap SBMLid="p23" COPASIkey="ModelValue_103"/>
    <SBMLMap SBMLid="p24" COPASIkey="ModelValue_104"/>
    <SBMLMap SBMLid="p25" COPASIkey="ModelValue_105"/>
    <SBMLMap SBMLid="p26" COPASIkey="ModelValue_106"/>
    <SBMLMap SBMLid="p27" COPASIkey="ModelValue_107"/>
    <SBMLMap SBMLid="p28" COPASIkey="ModelValue_108"/>
    <SBMLMap SBMLid="p29" COPASIkey="ModelValue_109"/>
    <SBMLMap SBMLid="p3" COPASIkey="ModelValue_83"/>
    <SBMLMap SBMLid="p30" COPASIkey="ModelValue_110"/>
    <SBMLMap SBMLid="p31" COPASIkey="ModelValue_111"/>
    <SBMLMap SBMLid="p4" COPASIkey="ModelValue_84"/>
    <SBMLMap SBMLid="p5" COPASIkey="ModelValue_85"/>
    <SBMLMap SBMLid="p6" COPASIkey="ModelValue_86"/>
    <SBMLMap SBMLid="p7" COPASIkey="ModelValue_87"/>
    <SBMLMap SBMLid="p8" COPASIkey="ModelValue_88"/>
    <SBMLMap SBMLid="p9" COPASIkey="ModelValue_89"/>
    <SBMLMap SBMLid="phaseStep1" COPASIkey="ModelValue_123"/>
    <SBMLMap SBMLid="pulseDurationStep1" COPASIkey="ModelValue_124"/>
    <SBMLMap SBMLid="q1" COPASIkey="ModelValue_112"/>
    <SBMLMap SBMLid="q2" COPASIkey="ModelValue_113"/>
    <SBMLMap SBMLid="q3" COPASIkey="ModelValue_114"/>
    <SBMLMap SBMLid="rampDurationStep1" COPASIkey="ModelValue_126"/>
    <SBMLMap SBMLid="step1" COPASIkey="ModelValue_120"/>
    <SBMLMap SBMLid="stepFunction" COPASIkey="Function_40"/>
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
  </ListOfUnitDefinitions>
</COPASI>
