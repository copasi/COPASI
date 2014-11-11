<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.14 (Build 89+) (http://www.copasi.org) at 2014-11-11 17:07:04 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="14" versionDevel="89" copasiSourcesModified="1">
  <ListOfFunctions>
    <Function key="Function_44" name="GK" type="UserDefined" reversible="unspecified">
      <Expression>
        2*A4*A1/(A2-A1+A3*A2+A4*A1+((A2-A1+A3*A2+A4*A1)^2-4*(A2-A1)*A4*A1)^(1/2))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_385" name="A1" order="0" role="variable"/>
        <ParameterDescription key="FunctionParameter_383" name="A2" order="1" role="variable"/>
        <ParameterDescription key="FunctionParameter_381" name="A3" order="2" role="variable"/>
        <ParameterDescription key="FunctionParameter_387" name="A4" order="3" role="variable"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_48" name="function_4_Synthesis of CLN2" type="UserDefined" reversible="false">
      <Expression>
        (ksn2_p+ksn2_p_p*(SBF*cell))*MASS
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_366" name="MASS" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_370" name="SBF" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_368" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_371" name="ksn2_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_375" name="ksn2_p_p" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_49" name="function_4_Degradation of CLN2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdn2,CLN2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_369" name="CLN2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_373" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_365" name="kdn2" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_50" name="function_4_Synthesis of CLB2" type="UserDefined" reversible="false">
      <Expression>
        (ksb2_p+ksb2_p_p*(MCM1*cell))*MASS
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_358" name="MASS" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_362" name="MCM1" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_360" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_364" name="ksb2_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_367" name="ksb2_p_p" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_51" name="function_4_Degradation of CLB2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,CLB2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_361" name="CLB2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_357" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_378" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_52" name="function_4_Synthesis of CLB5" type="UserDefined" reversible="false">
      <Expression>
        (ksb5_p+ksb5_p_p*(SBF*cell))*MASS
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_350" name="MASS" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_354" name="SBF" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_352" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_356" name="ksb5_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_359" name="ksb5_p_p" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_53" name="function_4_Degradation of CLB5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,CLB5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_353" name="CLB5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_349" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_363" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_54" name="function_4_Synthesis of SIC1" type="UserDefined" reversible="false">
      <Expression>
        (ksc1_p+ksc1_p_p*(SWI5*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_346" name="SWI5" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_344" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_348" name="ksc1_p" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_351" name="ksc1_p_p" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_55" name="function_4_Phosphorylation of SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpc1,SIC1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_347" name="SIC1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_343" name="Vkpc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_342" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_56" name="function_4_Dephosphorylation of SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppc1,SIC1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_345" name="SIC1P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_341" name="Vppc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_339" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_57" name="function_4_Fast Degradation of SIC1P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3c1,SIC1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_355" name="SIC1P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_336" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_338" name="kd3c1" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_58" name="function_4_Assoc. of CLB2 and SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasb2,CLB2*cell,SIC1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_340" name="CLB2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_331" name="SIC1" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_333" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_335" name="kasb2" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_59" name="function_4_Dissoc. of CLB2/SIC1 complex" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdib2,C2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_334" name="C2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_329" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_330" name="kdib2" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_60" name="function_4_Assoc. of CLB5 and SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasb5,CLB5*cell,SIC1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_332" name="CLB5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_324" name="SIC1" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_326" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_328" name="kasb5" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_61" name="function_4_Dissoc. of CLB5/SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdib5,C5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_327" name="C5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_322" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_323" name="kdib5" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_62" name="function_4_Phosphorylation of C2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpc1,C2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_325" name="C2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_321" name="Vkpc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_319" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_63" name="function_4_Dephosphorylation of C2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppc1,C2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_337" name="C2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_318" name="Vppc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_316" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_64" name="function_4_Phosphorylation of C5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpc1,C5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_320" name="C5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_315" name="Vkpc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_313" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_65" name="function_4_Dephosphorylation of C5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppc1,C5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_317" name="C5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_312" name="Vppc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_310" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_66" name="function_4_Degradation of CLB2 in C2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,C2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_314" name="C2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_309" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_307" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_67" name="function_4_Degradation of CLB5 in C5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,C5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_311" name="C5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_306" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_304" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_68" name="function_4_Degradation of SIC1 in C2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3c1,C2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_308" name="C2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_301" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_303" name="kd3c1" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_69" name="function_4_Degradation of SIC1P in C5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3c1,C5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_305" name="C5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_298" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_300" name="kd3c1" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_70" name="function_4_Degradation of CLB2 in C2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,C2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_302" name="C2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_297" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_295" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_71" name="function_4_Degradation of CLB5 in C5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,C5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_299" name="C5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_294" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_292" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_72" name="function_4_CDC6 synthesis" type="UserDefined" reversible="false">
      <Expression>
        (ksf6_p+ksf6_p_p*(SWI5*cell)+ksf6_p_p_p*(SBF*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_283" name="SBF" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_289" name="SWI5" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_287" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_291" name="ksf6_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_296" name="ksf6_p_p" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_285" name="ksf6_p_p_p" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_73" name="function_4_Phosphorylation of CDC6" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpf6,CDC6*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_286" name="CDC6" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_282" name="Vkpf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_290" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_74" name="function_4_Dephosphorylation of CDC6" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppf6,CDC6P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_284" name="CDC6P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_293" name="Vppf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_280" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_75" name="function_4_Degradation of CDC6P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3f6,CDC6P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_288" name="CDC6P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_277" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_279" name="kd3f6" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_76" name="function_4_CLB2/CDC6 complex formation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasf2,CLB2*cell,CDC6*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_272" name="CDC6" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_281" name="CLB2" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_274" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_276" name="kasf2" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_77" name="function_4_CLB2/CDC6 dissociation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdif2,F2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_275" name="F2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_270" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_271" name="kdif2" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_78" name="function_4_CLB5/CDC6 complex formation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasf5,CLB5*cell,CDC6*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_265" name="CDC6" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_273" name="CLB5" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_267" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_269" name="kasf5" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_79" name="function_4_CLB5/CDC6 dissociation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdif5,F5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_268" name="F5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_246" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_258" name="kdif5" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_80" name="function_4_F2 phosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpf6,F2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_266" name="F2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_254" name="Vkpf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_264" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_81" name="function_4_F2P dephosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppf6,F2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_278" name="F2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_566" name="Vppf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_568" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_82" name="function_4_F5 phosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpf6,F5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_262" name="F5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_569" name="Vkpf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_571" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_83" name="function_4_F5P dephosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppf6,F5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_567" name="F5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_572" name="Vppf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_574" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_84" name="function_4_CLB2 degradation in F2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,F2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_570" name="F2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_575" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_577" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_85" name="function_4_CLB5 degradation in F5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,F5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_573" name="F5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_578" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_580" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_86" name="function_4_CDC6 degradation in F2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3f6,F2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_576" name="F2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_583" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_581" name="kd3f6" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_87" name="function_4_CDC6 degradation in F5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3f6,F5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_579" name="F5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_586" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_584" name="kd3f6" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_88" name="function_4_CLB2 degradation in F2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,F2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_582" name="F2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_587" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_589" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_89" name="function_4_CLB5 degradation in F5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,F5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_585" name="F5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_590" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_592" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_90" name="function_4_Synthesis of SWI5" type="UserDefined" reversible="false">
      <Expression>
        (ksswi_p+ksswi_p_p*(MCM1*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_595" name="MCM1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_597" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_593" name="ksswi_p" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_588" name="ksswi_p_p" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_91" name="function_4_Degradation of SWI5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdswi,SWI5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_594" name="SWI5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_599" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_598" name="kdswi" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_92" name="function_4_Degradation of SWI5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdswi,SWI5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_596" name="SWI5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_602" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_600" name="kdswi" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_93" name="function_4_Activation of SWI5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kaswi*(CDC14*cell),SWI5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_591" name="CDC14" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_607" name="SWI5P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_605" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_603" name="kaswi" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_94" name="function_4_Inactivation of SWI5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kiswi*(CLB2*cell),SWI5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_604" name="CLB2" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_611" name="SWI5" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_609" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_608" name="kiswi" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_95" name="function_4_Activation of IEP" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(Vaiep,Jaiep,1,IE*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_613" name="IE" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_601" name="Jaiep" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_612" name="Vaiep" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_615" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_96" name="function_4_Inactivation" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(1,Jiiep,kiiep,IEP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_617" name="IEP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_616" name="Jiiep" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_619" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_606" name="kiiep" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_97" name="function_4_Synthesis of inactive CDC20" type="UserDefined" reversible="false">
      <Expression>
        (ks20_p+ks20_p_p*(MCM1*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_621" name="MCM1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_623" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_620" name="ks20_p" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_610" name="ks20_p_p" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_98" name="function_4_Degradation of inactiveCDC20" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd20,CDC20i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_614" name="CDC20i" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_625" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_624" name="kd20" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_99" name="function_4_Degradation of active CDC20" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd20,CDC20*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_622" name="CDC20" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_628" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_626" name="kd20" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_100" name="function_4_Activation of CDC20" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(ka20_p+ka20_p_p*(IEP*cell),CDC20i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_635" name="CDC20i" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_631" name="IEP" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_633" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_629" name="ka20_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_618" name="ka20_p_p" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_101" name="function_4_Inactivation_2" type="UserDefined" reversible="false">
      <Expression>
        k*Mass_Action_1(MAD2*cell,CDC20*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_638" name="CDC20" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_632" name="MAD2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_627" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_636" name="k" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_102" name="function_4_CDH1 synthesis" type="UserDefined" reversible="false">
      <Expression>
        kscdh/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_630" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_639" name="kscdh" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_103" name="function_4_CDH1 degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdcdh,CDH1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_640" name="CDH1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_642" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_634" name="kdcdh" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_104" name="function_4_CDH1i degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdcdh,CDH1i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_637" name="CDH1i" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_645" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_643" name="kdcdh" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_105" name="function_4_CDH1i activation" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(Vacdh,Jacdh,1,CDH1i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_648" name="CDH1i" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_641" name="Jacdh" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_646" name="Vacdh" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_650" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_106" name="function_4_Inactivation_3" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(Vicdh,Jicdh,1,CDH1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_652" name="CDH1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_647" name="Jicdh" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_651" name="Vicdh" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_654" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_107" name="function_4_CDC14 synthesis" type="UserDefined" reversible="false">
      <Expression>
        ks14/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_644" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_655" name="ks14" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_108" name="function_4_CDC14 degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd14,CDC14*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_656" name="CDC14" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_658" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_649" name="kd14" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_109" name="function_4_Assoc. with NET1 to form RENT" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasrent,CDC14*cell,NET1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_653" name="CDC14" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_663" name="NET1" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_661" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_659" name="kasrent" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_110" name="function_4_Dissoc. from RENT" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdirent,RENT*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_660" name="RENT" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_665" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_664" name="kdirent" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_111" name="function_4_Assoc with NET1P to form RENTP" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasrentp,CDC14*cell,NET1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_662" name="CDC14" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_670" name="NET1P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_668" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_666" name="kasrentp" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_112" name="function_4_Dissoc. from RENP" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdirentp,RENTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_667" name="RENTP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_672" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_671" name="kdirentp" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_113" name="function_4_Net1 synthesis" type="UserDefined" reversible="false">
      <Expression>
        ksnet/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_669" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_673" name="ksnet" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_114" name="function_4_Net1 degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdnet,NET1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_675" name="NET1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_677" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_674" name="kdnet" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_115" name="function_4_Net1P degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdnet,NET1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_657" name="NET1P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_680" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_678" name="kdnet" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_116" name="function_4_NET1 phosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpnet,NET1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_676" name="NET1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_681" name="Vkpnet" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_683" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_117" name="function_4_dephosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppnet,NET1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_679" name="NET1P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_684" name="Vppnet" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_686" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_118" name="function_4_RENT phosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpnet,RENT*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_682" name="RENT" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_687" name="Vkpnet" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_689" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_119" name="function_4_dephosphorylation_2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppnet,RENTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_685" name="RENTP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_690" name="Vppnet" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_692" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_120" name="function_4_Degradation of NET1 in RENT" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdnet,RENT*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_688" name="RENT" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_695" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_693" name="kdnet" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_121" name="function_4_Degradation of NET1P in RENTP" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdnet,RENTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_691" name="RENTP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_698" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_696" name="kdnet" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_122" name="function_4_Degradation of CDC14 in RENT" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd14,RENT*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_694" name="RENT" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_701" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_699" name="kd14" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_123" name="function_4_Degradation of CDC14 in RENTP" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd14,RENTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_697" name="RENTP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_704" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_702" name="kd14" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_124" name="function_4_TEM1 activation" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(LTE1*cell,Jatem,1,TEM1GDP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_707" name="Jatem" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_705" name="LTE1" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_709" name="TEM1GDP" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_700" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_125" name="function_4_inactivation" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(BUB2*cell,Jitem,1,TEM1GTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_710" name="BUB2" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_711" name="Jitem" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_713" name="TEM1GTP" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_706" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_126" name="function_4_CDC15 activation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(ka15_p*(TEM1GDP*cell)+ka15_p_p*(TEM1GTP*cell)+ka15p*(CDC14*cell),CDC15i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_723" name="CDC14" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_725" name="CDC15i" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_703" name="TEM1GDP" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_719" name="TEM1GTP" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_715" name="cell" order="4" role="volume"/>
        <ParameterDescription key="FunctionParameter_714" name="ka15_p" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_717" name="ka15_p_p" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_721" name="ka15p" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_127" name="function_4_inactivation_2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(ki15,CDC15*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_722" name="CDC15" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_718" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_726" name="ki15" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_128" name="function_4_PPX synthesis" type="UserDefined" reversible="false">
      <Expression>
        ksppx/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_724" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_716" name="ksppx" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_129" name="function_4_degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdppx,PPX*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_712" name="PPX" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_708" name="Vdppx" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_728" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_130" name="function_4_PDS1 synthesis" type="UserDefined" reversible="false">
      <Expression>
        (kspds_p+ks1pds_p_p*(SBF*cell)+ks2pds_p_p*(MCM1*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_737" name="MCM1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_731" name="SBF" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_733" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_720" name="ks1pds_p_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_735" name="ks2pds_p_p" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_729" name="kspds_p" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_131" name="function_4_degradation_2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdpds,PDS1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_734" name="PDS1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_738" name="Vdpds" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_730" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_132" name="function_4_Degradation of PDS1 in PE" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdpds,PE*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_736" name="PE" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_727" name="Vdpds" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_740" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_133" name="function_4_Assoc. with ESP1 to form PE" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasesp,PDS1*cell,ESP1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_745" name="ESP1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_732" name="PDS1" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_743" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_741" name="kasesp" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_134" name="function_4_Disso. from PE" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdiesp,PE*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_742" name="PE" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_747" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_746" name="kdiesp" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_135" name="function_4_DNA synthesis" type="UserDefined" reversible="false">
      <Expression>
        ksori*(eorib5*(CLB5*cell)+eorib2*(CLB2*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_756" name="CLB2" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_750" name="CLB5" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_752" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_754" name="eorib2" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_744" name="eorib5" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_748" name="ksori" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_136" name="function_4_Negative regulation of DNA synthesis" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdori,ORI*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_753" name="ORI" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_749" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_757" name="kdori" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_137" name="function_4_Budding" type="UserDefined" reversible="false">
      <Expression>
        ksbud*(ebudn2*(CLN2*cell)+ebudn3*(CLN3*cell)+ebudb5*(CLB5*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_769" name="CLB5" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_759" name="CLN2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_765" name="CLN3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_761" name="cell" order="3" role="volume"/>
        <ParameterDescription key="FunctionParameter_767" name="ebudb5" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_755" name="ebudn2" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_763" name="ebudn3" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_739" name="ksbud" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_138" name="function_4_Negative regulation of Cell budding" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdbud,BUD*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_766" name="BUD" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_762" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_770" name="kdbud" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_139" name="function_4_Spindle formation" type="UserDefined" reversible="false">
      <Expression>
        ksspn*CLB2/(Jspn+CLB2*cell)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_768" name="CLB2" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_751" name="Jspn" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_772" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_760" name="ksspn" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_140" name="function_4_Spindle disassembly" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdspn,SPN*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_758" name="SPN" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_774" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_773" name="kdspn" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_141" name="function_4_Growth-hyperbolic" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_141">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T13:10:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        activator*(k*SUB/(Kmsub+SUB))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_775" name="activator" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_771" name="k" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_777" name="SUB" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_779" name="Kmsub" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_45" name="Mass_Action_1" type="UserDefined" reversible="unspecified">
      <Expression>
        k1*S1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_380" name="k1" order="0" role="variable"/>
        <ParameterDescription key="FunctionParameter_384" name="S1" order="1" role="variable"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_46" name="Mass_Action_2" type="UserDefined" reversible="unspecified">
      <Expression>
        k1*S1*S2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_386" name="k1" order="0" role="variable"/>
        <ParameterDescription key="FunctionParameter_379" name="S1" order="1" role="variable"/>
        <ParameterDescription key="FunctionParameter_377" name="S2" order="2" role="variable"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_47" name="Michaelis-Menten" type="UserDefined" reversible="unspecified">
      <Expression>
        k1*S1*M1/(J1+S1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_374" name="M1" order="0" role="variable"/>
        <ParameterDescription key="FunctionParameter_372" name="J1" order="1" role="variable"/>
        <ParameterDescription key="FunctionParameter_376" name="k1" order="2" role="variable"/>
        <ParameterDescription key="FunctionParameter_382" name="S1" order="3" role="variable"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_7" name="Chen2004_CellCycle Mother with GLU" simulationType="time" timeUnit="min" volumeUnit="l" areaUnit="m²" lengthUnit="m" quantityUnit="mol" type="deterministic" avogadroConstant="6.02214e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_7">
    <dcterms:bibliographicCitation>
      <rdf:Description>
        <CopasiMT:isDescribedBy rdf:resource="urn:miriam:pubmed:15169868"/>
      </rdf:Description>
    </dcterms:bibliographicCitation>
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2006-05-08T11:05:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <dcterms:creator>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>kchen@vt.edu</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Chen</vCard:Family>
                <vCard:Given>Katherine C</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>Department of Biology, Virginia Polytechnic Institute</vCard:Orgname>
              </rdf:Description>
            </vCard:ORG>
          </rdf:Description>
        </rdf:li>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>lukas@ebi.ac.uk</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Endler</vCard:Family>
                <vCard:Given>Lukas</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>EMBL-EBI</vCard:Orgname>
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
        <dcterms:W3CDTF>2009-09-17T13:54:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:modified>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:biomodels.db:BIOMD0000000056"/>
        <rdf:li rdf:resource="urn:miriam:kegg.pathway:sce04111"/>
        <rdf:li rdf:resource="urn:miriam:taxonomy:4932"/>
        <rdf:li>
          <rdf:Bag>
            <rdf:li rdf:resource="urn:miriam:biomodels.db:MODEL6624073334"/>
          </rdf:Bag>
        </rdf:li>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isHomologTo rdf:resource="urn:miriam:reactome:REACT_152"/>
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0000278"/>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      <html xmlns="http://www.w3.org/1999/xhtml"><head><meta name="qrichtext" content="1" /></head><body style="font-size:11pt;font-family:Droid Sans">
<p style="margin-top:18px" dir="ltr"><span style="font-size:16pt;font-weight:600">Mother cell growth &amp; division</span></p>
<p dir="ltr">This is initialized with the conditions at time of division when a new bud is formed. The model follows the mother at time of division.</p>
<p dir="ltr">This model is essentially the Chen 2004 model, adapted to have variable rate of growth (depending on GLU)</p>
<p style="margin-top:18px" dir="ltr"><span style="font-size:13pt">SBML model of Cell cycle control mechanism </span></p>
<p dir="ltr">This is a hypothetical model of the cell cycle control mechanism by Chen et al(2004). The model reproduces the time profiles of the different species in Fig 2 of the paper. The figure depicts the cycle of a daughter cell. Since,the Mass Doubling Time(MDT) is 90 minutes, time t=90 from the model simulation will correspond to time t=0 in the paper. The model was successfully tested using MathSBML and SBML odeSolver. <br />To create valid SBML a local parameter k = 1 was added in reaction: &quot;Inactivation_274_CDC20&quot;. </p>
<p dir="ltr">This model originates from BioModels Database: A Database of Annotated Published Models. It is copyright (c) 2005-2010 The BioModels Team. <br />For more information see the <a href="http://www.ebi.ac.uk/biomodels/legal.html">terms of use</a>. <br />To cite BioModels Database, please use <a href="http://www.pubmedcentral.nih.gov/articlerender.fcgi?tool=pubmedpubmedid=16381960">Le Novere N., Bornstein B., Broicher A., Courtot M., Donizelli M., Dharuri H., Li L., Sauro H., Schilstra M., Shapiro B., Snoep J.L., Hucka M. (2006) BioModels Database: A Free, Centralized Database of Curated, Published, Quantitative Kinetic Models of Biochemical and Cellular Systems Nucleic Acids Res., 34: D689-D691.</a> </p>
</body></html>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_3" name="cell" simulationType="fixed" dimensionality="3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_3">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0005623" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_49" name="BCK2" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_49">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-03-02T13:11:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P33306" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[b0],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MASS],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_45" name="BUB2" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_45">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P26448" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_41" name="BUD" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_41">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0007114" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_37" name="C2" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_37">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P24868" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P24869" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P38634" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_33" name="C2P" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_33">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P24868" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P24869" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P38634" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_29" name="C5" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_29">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P30283" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P32943" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P38634" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_25" name="C5P" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_25">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P30283" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P32943" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P38634" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_21" name="CDC14" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_21">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:Q00684" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_17" name="CDC14T" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_17">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:Q00684" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENT],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENTP],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_13" name="CDC15" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_13">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P27636" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_9" name="CDC15i" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_9">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P27636" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[CDC15T],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC15],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_5" name="CDC20" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:07:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P26309" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_1" name="CDC20i" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:07:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P26309" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_77" name="CDC6" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_77">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:07:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P09119" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_79" name="CDC6P" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_79">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P09119" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_81" name="CDC6T" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_81">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P09119" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_83" name="CDH1" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_83">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P53197" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_85" name="CDH1i" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_85">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:07:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P53197" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_87" name="CKIT" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_87">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P09119" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P38634" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1T],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6T],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_89" name="CLB2" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_89">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P24868" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P24869" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_91" name="CLB2T" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_91">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:07:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P24868" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P24869" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_93" name="CLB5" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_93">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:07:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P30283" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P32943" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_95" name="CLB5T" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_95">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P30283" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P32943" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_97" name="CLN2" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_97">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P20437" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P20438" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_99" name="CLN3" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_99">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:38:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P13365" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[C0],Reference=Value&gt;*&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Dn3],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MASS],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jn3],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Dn3],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MASS],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;))/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_101" name="ESP1" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_101">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:Q03018" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_103" name="F2" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_103">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P09119" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P24868" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P24869" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_105" name="F2P" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_105">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-02-21T01:09:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P09119" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P24868" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P24869" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_107" name="F5" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_107">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P09119" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P30283" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P32943" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_109" name="F5P" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_109">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P09119" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P30283" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P32943" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_111" name="IE" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_111">
    <CopasiMT:is rdf:resource="urn:miriam:obo.go:GO%3A0005680" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[IET],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[IEP],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_113" name="IEP" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_113">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:23:39Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:obo.go:GO%3A0005680" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_115" name="LTE1" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_115">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:07:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P07866" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_117" name="MAD2" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_117">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:07:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P40958" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_119" name="MASS" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_119">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:23:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:obo.go:GO%3A0016049" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_121" name="MCM1" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_121">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:23:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P11746" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          GK(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kamcm],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;),&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kimcm],Reference=Value&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jamcm],Reference=Value&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jimcm],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_123" name="NET1" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_123">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P47035" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_125" name="NET1P" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_125">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P47035" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_127" name="NET1T" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_127">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:23:47Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P47035" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENT],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENTP],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_129" name="ORI" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_129">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T14:24:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:obo.go:GO%3A0006261" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_131" name="PDS1" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_131">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T16:23:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P40316" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_133" name="PE" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_133">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:Q03018" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ESP1T],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ESP1],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_135" name="PPX" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_135">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38698" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_137" name="RENT" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_137">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P06700" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P47035" />
        <rdf:li rdf:resource="urn:miriam:uniprot:Q00684" />
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:is rdf:resource="urn:miriam:obo.go:GO%3A0030869" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_139" name="RENTP" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_139">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:uniprot:P06700" />
        <rdf:li rdf:resource="urn:miriam:uniprot:P47035" />
        <rdf:li rdf:resource="urn:miriam:uniprot:Q00684" />
      </rdf:Bag>
    </CopasiMT:hasPart>
    <CopasiMT:is rdf:resource="urn:miriam:obo.go:GO%3A0030869" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_141" name="SBF" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_141">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P11938" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          GK(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vasbf],Reference=Value&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Visbf],Reference=Value&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jasbf],Reference=Value&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jisbf],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_143" name="SIC1" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_143">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38634" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_145" name="SIC1P" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_145">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38634" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_147" name="SIC1T" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_147">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38634" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_149" name="SPN" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_149">
    <CopasiMT:is rdf:resource="urn:miriam:obo.go:GO%3A0051225" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_151" name="SWI5" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_151">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P08153" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_153" name="SWI5P" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_153">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P08153" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_155" name="TEM1GDP" simulationType="assignment" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_155">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38987" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[TEM1T],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[TEM1GTP],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_157" name="TEM1GTP" simulationType="reactions" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_157">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38987" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_159" name="GLU" simulationType="fixed" compartment="Compartment_3">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_159">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-05-07T14:54:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_6" name="b0" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_5" name="bub2h" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_11" name="bub2l" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_12" name="C0" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:17:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_13" name="CDC15T" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:17:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_14" name="Dn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_15" name="ebudb5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_16" name="ebudn2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_16">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_17" name="ebudn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_18" name="ec1b2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_18">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_19" name="ec1b5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_19">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_20" name="ec1k2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_20">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_21" name="ec1n2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_21">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_22" name="ec1n3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_22">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_23" name="ef6b2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_23">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_24" name="ef6b5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_24">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_25" name="ef6k2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_25">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_26" name="ef6n2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_26">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_27" name="ef6n3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_27">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_28" name="eicdhb2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_28">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_29" name="eicdhb5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_29">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_30" name="eicdhn2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_30">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-05-07T16:15:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_31" name="eicdhn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_31">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_32" name="eorib2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_32">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_33" name="eorib5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_33">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_34" name="esbfb5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_34">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_35" name="esbfn2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_35">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_36" name="esbfn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_36">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_37" name="ESP1T" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_37">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:18:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_38" name="IET" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_38">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_39" name="J20ppx" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_39">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_40" name="Jacdh" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_41" name="Jaiep" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_42" name="Jamcm" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_42">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_43" name="Jasbf" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_43">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_44" name="Jatem" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_45" name="Jd2c1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_45">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_46" name="Jd2f6" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_46">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_47" name="Jicdh" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_47">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_48" name="Jiiep" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_48">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_49" name="Jimcm" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_49">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_50" name="Jisbf" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_50">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_51" name="Jitem" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_51">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_52" name="Jn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_52">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_53" name="Jpds" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_53">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_54" name="Jspn" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_54">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_55" name="ka15'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_55">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_56" name="ka15''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_56">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_57" name="ka15p" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_57">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_58" name="ka20'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_58">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_59" name="ka20''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_59">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_60" name="kacdh'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_60">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_61" name="kacdh''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_61">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_62" name="kaiep" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_62">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_63" name="kamcm" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_63">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_64" name="kasb2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_64">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_65" name="kasb5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_65">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_66" name="kasbf" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_66">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_67" name="kasesp" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_67">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_68" name="kasf2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_68">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_69" name="kasf5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_69">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_70" name="kasrent" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_70">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_71" name="kasrentp" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_71">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_72" name="kaswi" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_72">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_73" name="kd14" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_73">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_74" name="kd1c1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_74">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_75" name="kd1f6" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_75">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_76" name="kd1pds'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_76">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_77" name="kd20" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_77">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_78" name="kd2c1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_78">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_79" name="kd2f6" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_79">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_80" name="kd2pds''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_81" name="kd3c1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_81">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_82" name="kd3f6" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_82">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_83" name="kd3pds''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_83">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_84" name="kdb2'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_84">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:39Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_85" name="kdb2''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_85">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_86" name="kdb2p" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_86">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_87" name="kdb5'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_87">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_88" name="kdb5''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_89" name="kdbud" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_89">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_90" name="kdcdh" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_90">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_91" name="kdib2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_91">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_92" name="kdib5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_92">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_93" name="kdiesp" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_94" name="kdif2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_94">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_95" name="kdif5" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_96" name="kdirent" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_97" name="kdirentp" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_98" name="kdn2" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_99" name="kdnet" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_100" name="kdori" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_101" name="kdppx'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_102" name="kdppx''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_103" name="kdspn" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_104" name="kdswi" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_105" name="KEZ" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_105">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T12:17:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_106" name="KEZ2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_106">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_107" name="ki15" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_108" name="kicdh'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_109" name="kicdh''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_109">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-02-21T01:11:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_110" name="kiiep" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_111" name="kimcm" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_112" name="kisbf'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_113" name="kisbf''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_114" name="kiswi" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_115" name="kkpnet'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_116" name="kkpnet''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_116">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-02-21T22:13:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_117" name="kppc1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_118" name="kppf6" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_119" name="kppnet'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_120" name="kppnet''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_121" name="ks14" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_122" name="ks1pds''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_123" name="ks20'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_124" name="ks20''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_125" name="ks2pds''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_126" name="ksb2'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_127" name="ksb2''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_128" name="ksb5'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_129" name="ksb5''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_130" name="ksbud" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_131" name="ksc1'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_132" name="ksc1''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_133" name="kscdh" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_134" name="ksf6'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_135" name="ksf6''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_135">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:47Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_136" name="ksf6'''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_137" name="ksn2'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_137">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:57:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_138" name="ksn2''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_139" name="ksnet" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_139">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:47Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_140" name="ksori" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_140">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:27:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_141" name="kspds'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_141">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_142" name="ksppx" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_142">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_143" name="ksspn" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_143">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_144" name="ksswi'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_144">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_145" name="ksswi''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_145">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_146" name="lte1h" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_146">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_147" name="lte1l" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_147">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T13:31:54Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_148" name="mad2h" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_148">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_149" name="mad2l" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_149">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_150" name="mdt" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_150">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T15:51:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          log(2)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mu],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_151" name="TEM1T" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_151">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_152" name="D" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_152">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T15:50:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          1.026/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mu],Reference=Value&gt;-32
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_153" name="mu" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_153">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T15:50:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mu2],Reference=Value&gt;*&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[GLU],Reference=Concentration&gt;/(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[KmGLU],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[GLU],Reference=Concentration&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_154" name="Vdb5" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_154">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdb5&apos;],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdb5&apos;&apos;],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC20],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_155" name="Vdb2" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_155">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdb2&apos;],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdb2&apos;&apos;],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDH1],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdb2p],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC20],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_156" name="Vasbf" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_156">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasbf],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[esbfn2],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[esbfn3],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN3],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BCK2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[esbfb5],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_157" name="Visbf" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_157">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kisbf&apos;],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kisbf&apos;&apos;],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_158" name="Vkpc1" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_158">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd1c1],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vd2c1],Reference=Value&gt;/(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jd2c1],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_159" name="Vkpf6" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_159">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd1f6],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vd2f6],Reference=Value&gt;/(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jd2f6],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_160" name="Vacdh" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_160">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kacdh&apos;],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kacdh&apos;&apos;],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_161" name="Vicdh" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_161">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kicdh&apos;],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kicdh&apos;&apos;],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[eicdhn3],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN3],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[eicdhn2],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[eicdhb5],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[eicdhb2],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_162" name="Vppnet" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_162">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kppnet&apos;],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kppnet&apos;&apos;],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PPX],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_163" name="Vkpnet" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_163">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kkpnet&apos;],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kkpnet&apos;&apos;],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC15],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;))*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MASS],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_164" name="Vdppx" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_164">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdppx&apos;],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdppx&apos;&apos;],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[J20ppx],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC20],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)*&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jpds],Reference=Value&gt;/(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jpds],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PDS1],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_165" name="Vdpds" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_165">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd1pds&apos;],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd2pds&apos;&apos;],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC20],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd3pds&apos;&apos;],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDH1],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_166" name="Vaiep" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_166">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kaiep],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_167" name="Vd2c1" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_167">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd2c1],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ec1n3],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN3],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ec1k2],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BCK2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ec1n2],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ec1b5],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ec1b2],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_168" name="Vd2f6" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_168">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd2f6],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ef6n3],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN3],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ef6k2],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BCK2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ef6n2],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ef6b5],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ef6b2],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_169" name="Vppc1" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_169">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kppc1],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_170" name="Vppf6" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_170">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:29:58Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kppf6],Reference=Value&gt;*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_171" name="F" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_171">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T15:50:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          exp(-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mu],Reference=Value&gt;*&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[D],Reference=Value&gt;)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_172" name="amount to particle factor" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_172">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T15:51:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_173" name="1stDivisionTime" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_173">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T16:10:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_174" name="mu2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_174">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-05-07T16:15:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_175" name="T0" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_175">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_176" name="Period" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_176">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T13:49:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_177" name="KmGLU" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_177">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:21:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_178" name="GLUconsumed" simulationType="ode">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_178">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-02-14T17:55:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Growth],Reference=Flux&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_179" name="quantity_1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_179">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-02-21T01:11:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_63" name="Growth" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_63">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-05-07T15:16:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0016049" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_159" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_119" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_119" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4163" name="k" value="0.0077"/>
          <Constant key="Parameter_4164" name="Kmsub" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_141">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_775">
              <SourceParameter reference="Metabolite_119"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_771">
              <SourceParameter reference="ModelValue_174"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_777">
              <SourceParameter reference="Metabolite_159"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_779">
              <SourceParameter reference="ModelValue_177"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_62" name="Synthesis of CLN2" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_62">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:kegg.pathway:sce04110" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_97" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_141" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_119" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4139" name="ksn2_p" value="1"/>
          <Constant key="Parameter_4140" name="ksn2_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_48">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_366">
              <SourceParameter reference="Metabolite_119"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_370">
              <SourceParameter reference="Metabolite_141"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_368">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_371">
              <SourceParameter reference="ModelValue_137"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_375">
              <SourceParameter reference="ModelValue_138"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_61" name="Degradation of CLN2" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_61">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_97" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4141" name="kdn2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_49">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_369">
              <SourceParameter reference="Metabolite_97"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_373">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_365">
              <SourceParameter reference="ModelValue_98"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_60" name="Synthesis of CLB2" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_60">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_89" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_121" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_119" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4142" name="ksb2_p" value="1"/>
          <Constant key="Parameter_4143" name="ksb2_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_50">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_358">
              <SourceParameter reference="Metabolite_119"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_362">
              <SourceParameter reference="Metabolite_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_360">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_364">
              <SourceParameter reference="ModelValue_126"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_367">
              <SourceParameter reference="ModelValue_127"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_59" name="Degradation of CLB2" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_59">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051437" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_89" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4144" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_51">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_361">
              <SourceParameter reference="Metabolite_89"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_357">
              <SourceParameter reference="ModelValue_155"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_378">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_58" name="Synthesis of CLB5" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_58">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_93" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_141" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_119" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4145" name="ksb5_p" value="1"/>
          <Constant key="Parameter_4146" name="ksb5_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_52">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_350">
              <SourceParameter reference="Metabolite_119"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_354">
              <SourceParameter reference="Metabolite_141"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_352">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_356">
              <SourceParameter reference="ModelValue_128"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_359">
              <SourceParameter reference="ModelValue_129"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_57" name="Degradation of CLB5" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_57">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051437" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_93" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4147" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_53">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_353">
              <SourceParameter reference="Metabolite_93"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_349">
              <SourceParameter reference="ModelValue_154"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_363">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_56" name="Synthesis of SIC1" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_56">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_143" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_151" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4148" name="ksc1_p" value="1"/>
          <Constant key="Parameter_4149" name="ksc1_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_54">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_346">
              <SourceParameter reference="Metabolite_151"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_344">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_348">
              <SourceParameter reference="ModelValue_131"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_351">
              <SourceParameter reference="ModelValue_132"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_55" name="Phosphorylation of SIC1" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_55">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.22" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004693" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_143" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_145" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4150" name="Vkpc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_55">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_347">
              <SourceParameter reference="Metabolite_143"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_343">
              <SourceParameter reference="ModelValue_158"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_342">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_54" name="Dephosphorylation of SIC1" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_54">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.48" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004721" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_145" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_143" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4151" name="Vppc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_56">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_345">
              <SourceParameter reference="Metabolite_145"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_341">
              <SourceParameter reference="ModelValue_169"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_339">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_53" name="Fast Degradation of SIC1P" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_53">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_145" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4152" name="kd3c1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_57">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_355">
              <SourceParameter reference="Metabolite_145"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_336">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_338">
              <SourceParameter reference="ModelValue_81"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_52" name="Assoc. of CLB2 and SIC1" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_52">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0005515" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0043623" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_89" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_143" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4153" name="kasb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_58">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_340">
              <SourceParameter reference="Metabolite_89"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_331">
              <SourceParameter reference="Metabolite_143"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_333">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_335">
              <SourceParameter reference="ModelValue_64"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_51" name="Dissoc. of CLB2/SIC1 complex" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_51">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_89" stoichiometry="1"/>
          <Product metabolite="Metabolite_143" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4154" name="kdib2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_59">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_334">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_329">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_330">
              <SourceParameter reference="ModelValue_91"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_50" name="Assoc. of CLB5 and SIC1" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_50">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0005515" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0043623" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_93" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_143" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4155" name="kasb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_60">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_332">
              <SourceParameter reference="Metabolite_93"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_324">
              <SourceParameter reference="Metabolite_143"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_326">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_328">
              <SourceParameter reference="ModelValue_65"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_49" name="Dissoc. of CLB5/SIC1" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_49">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_93" stoichiometry="1"/>
          <Product metabolite="Metabolite_143" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4156" name="kdib5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_61">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_327">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_323">
              <SourceParameter reference="ModelValue_92"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_48" name="Phosphorylation of C2" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_48">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.22" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004693" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4157" name="Vkpc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_62">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_325">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="ModelValue_158"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_47" name="Dephosphorylation of C2P" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_47">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.48" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004721" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4158" name="Vppc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_63">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_337">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="ModelValue_169"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_46" name="Phosphorylation of C5" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_46">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.22" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004693" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4159" name="Vkpc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_64">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_315">
              <SourceParameter reference="ModelValue_158"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_45" name="Dephosphorylation of C5P" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_45">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.48" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004721" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4160" name="Vppc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_65">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="ModelValue_169"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_310">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_44" name="Degradation of CLB2 in C2" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_44">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051437" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_143" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4161" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_66">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_314">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_309">
              <SourceParameter reference="ModelValue_155"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_307">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_43" name="Degradation of CLB5 in C5" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_43">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051437" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_143" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4162" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_67">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_311">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="ModelValue_154"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_304">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_42" name="Degradation of SIC1 in C2P" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_42">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_89" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4191" name="kd3c1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_68">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_308">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_301">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_303">
              <SourceParameter reference="ModelValue_81"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_41" name="Degradation of SIC1P in C5P" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_41">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_93" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4193" name="kd3c1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_69">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_305">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_298">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_300">
              <SourceParameter reference="ModelValue_81"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_40" name="Degradation of CLB2 in C2P" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_40">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051437" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_145" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4194" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_70">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_302">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_297">
              <SourceParameter reference="ModelValue_155"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_295">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_39" name="Degradation of CLB5 in C5P" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_39">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051437" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_145" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4195" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_71">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_299">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_294">
              <SourceParameter reference="ModelValue_154"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_292">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_38" name="CDC6 synthesis" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_38">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_151" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_141" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4196" name="ksf6_p" value="1"/>
          <Constant key="Parameter_4192" name="ksf6_p_p" value="1"/>
          <Constant key="Parameter_4197" name="ksf6_p_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_72">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_283">
              <SourceParameter reference="Metabolite_141"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_289">
              <SourceParameter reference="Metabolite_151"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_287">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_291">
              <SourceParameter reference="ModelValue_134"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_296">
              <SourceParameter reference="ModelValue_135"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_285">
              <SourceParameter reference="ModelValue_136"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_37" name="Phosphorylation of CDC6" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_37">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.22" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004693" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4198" name="Vkpf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_73">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_286">
              <SourceParameter reference="Metabolite_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="ModelValue_159"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_290">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_36" name="Dephosphorylation of CDC6" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_36">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.48" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004721" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4199" name="Vppf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_74">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="Metabolite_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_293">
              <SourceParameter reference="ModelValue_170"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="Degradation of CDC6P" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_35">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4200" name="kd3f6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_75">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_288">
              <SourceParameter reference="Metabolite_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_279">
              <SourceParameter reference="ModelValue_82"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_34" name="CLB2/CDC6 complex formation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_34">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0005515" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0043623" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_89" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_103" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4201" name="kasf2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_76">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_272">
              <SourceParameter reference="Metabolite_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_281">
              <SourceParameter reference="Metabolite_89"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_276">
              <SourceParameter reference="ModelValue_68"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_33" name="CLB2/CDC6 dissociation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_33">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_103" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_89" stoichiometry="1"/>
          <Product metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4202" name="kdif2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_77">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="Metabolite_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_271">
              <SourceParameter reference="ModelValue_94"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_32" name="CLB5/CDC6 complex formation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_32">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0005515" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0043623" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_93" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_107" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4203" name="kasf5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_78">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="Metabolite_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="Metabolite_93"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_267">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="ModelValue_69"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="CLB5/CDC6 dissociation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_31">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_107" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_93" stoichiometry="1"/>
          <Product metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4204" name="kdif5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_79">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="Metabolite_107"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_246">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="ModelValue_95"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="F2 phosphorylation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_30">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.22" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004693" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_103" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_105" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4205" name="Vkpf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_80">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="Metabolite_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_254">
              <SourceParameter reference="ModelValue_159"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="F2P dephosphorylation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_29">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.48" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004721" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_105" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_103" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4206" name="Vppf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_81">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="Metabolite_105"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_566">
              <SourceParameter reference="ModelValue_170"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_568">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="F5 phosphorylation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_28">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.22" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004693" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_107" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_109" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4207" name="Vkpf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_82">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="Metabolite_107"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_569">
              <SourceParameter reference="ModelValue_159"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_571">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="F5P dephosphorylation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_27">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.48" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004721" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_109" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_107" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4208" name="Vppf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_83">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_567">
              <SourceParameter reference="Metabolite_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_572">
              <SourceParameter reference="ModelValue_170"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_574">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="CLB2 degradation in F2" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_26">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051437" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_103" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4209" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_84">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_570">
              <SourceParameter reference="Metabolite_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_575">
              <SourceParameter reference="ModelValue_155"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_577">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="CLB5 degradation in F5" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_25">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051437" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_107" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4210" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_85">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_573">
              <SourceParameter reference="Metabolite_107"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_578">
              <SourceParameter reference="ModelValue_154"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_580">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="CDC6 degradation in F2P" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_24">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_105" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_89" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4211" name="kd3f6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_86">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_576">
              <SourceParameter reference="Metabolite_105"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_583">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_581">
              <SourceParameter reference="ModelValue_82"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="CDC6 degradation in F5P" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_23">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_109" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_93" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4212" name="kd3f6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_87">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_579">
              <SourceParameter reference="Metabolite_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_586">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_584">
              <SourceParameter reference="ModelValue_82"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="CLB2 degradation in F2P" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_22">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051437" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_105" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4213" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_88">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_582">
              <SourceParameter reference="Metabolite_105"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_587">
              <SourceParameter reference="ModelValue_155"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_589">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="CLB5 degradation in F5P" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_21">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051437" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_109" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4214" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_89">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_585">
              <SourceParameter reference="Metabolite_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_590">
              <SourceParameter reference="ModelValue_154"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_592">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="Synthesis of SWI5" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_20">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_151" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_121" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4215" name="ksswi_p" value="1"/>
          <Constant key="Parameter_4216" name="ksswi_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_90">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_595">
              <SourceParameter reference="Metabolite_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_597">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_593">
              <SourceParameter reference="ModelValue_144"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_588">
              <SourceParameter reference="ModelValue_145"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="Degradation of SWI5" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_19">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_151" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4217" name="kdswi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_91">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_594">
              <SourceParameter reference="Metabolite_151"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_599">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_598">
              <SourceParameter reference="ModelValue_104"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="Degradation of SWI5P" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_18">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_153" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4218" name="kdswi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_92">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_596">
              <SourceParameter reference="Metabolite_153"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_602">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_600">
              <SourceParameter reference="ModelValue_104"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="Activation of SWI5" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_17">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.48" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004721" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051091" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_153" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_151" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4219" name="kaswi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_93">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_591">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_607">
              <SourceParameter reference="Metabolite_153"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_605">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_603">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="Inactivation of SWI5" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_16">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.22" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004693" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0043433" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_151" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_153" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_89" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4222" name="kiswi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_94">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_604">
              <SourceParameter reference="Metabolite_89"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_611">
              <SourceParameter reference="Metabolite_151"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_609">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_608">
              <SourceParameter reference="ModelValue_114"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="Activation of IEP" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_15">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.22" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004693" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_111" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_113" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4223" name="Jaiep" value="1"/>
          <Constant key="Parameter_4224" name="Vaiep" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_95">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_613">
              <SourceParameter reference="Metabolite_111"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_601">
              <SourceParameter reference="ModelValue_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_612">
              <SourceParameter reference="ModelValue_166"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_615">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="Inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_14">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0001100" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_113" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_111" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4220" name="Jiiep" value="1"/>
          <Constant key="Parameter_4221" name="kiiep" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_96">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_617">
              <SourceParameter reference="Metabolite_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_616">
              <SourceParameter reference="ModelValue_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_619">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_606">
              <SourceParameter reference="ModelValue_110"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="Synthesis of inactive CDC20" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_13">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_121" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4225" name="ks20_p" value="1"/>
          <Constant key="Parameter_4226" name="ks20_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_97">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_621">
              <SourceParameter reference="Metabolite_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_623">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_620">
              <SourceParameter reference="ModelValue_123"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_610">
              <SourceParameter reference="ModelValue_124"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="Degradation of inactiveCDC20" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_12">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4227" name="kd20" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_98">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_614">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_625">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_624">
              <SourceParameter reference="ModelValue_77"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="Degradation of active CDC20" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_11">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4228" name="kd20" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_99">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_622">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_628">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_626">
              <SourceParameter reference="ModelValue_77"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="Activation of CDC20" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_10">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0031536" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_113" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4229" name="ka20_p" value="1"/>
          <Constant key="Parameter_4230" name="ka20_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_100">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_635">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_631">
              <SourceParameter reference="Metabolite_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_633">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_629">
              <SourceParameter reference="ModelValue_58"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_618">
              <SourceParameter reference="ModelValue_59"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="Inactivation_2" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_9">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0001100" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_117" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4231" name="k" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_101">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_638">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_632">
              <SourceParameter reference="Metabolite_117"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_627">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_636">
              <SourceParameter reference="Parameter_4231"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="CDH1 synthesis" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_8">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_83" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4232" name="kscdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_102">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_630">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_639">
              <SourceParameter reference="ModelValue_133"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="CDH1 degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_7">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_83" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4233" name="kdcdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_103">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_640">
              <SourceParameter reference="Metabolite_83"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_642">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_634">
              <SourceParameter reference="ModelValue_90"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="CDH1i degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_6">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_85" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4234" name="kdcdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_104">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_637">
              <SourceParameter reference="Metabolite_85"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_645">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_643">
              <SourceParameter reference="ModelValue_90"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="CDH1i activation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_5">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.48" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004721" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0031536" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_85" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_83" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4235" name="Jacdh" value="1"/>
          <Constant key="Parameter_4236" name="Vacdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_105">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_648">
              <SourceParameter reference="Metabolite_85"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_641">
              <SourceParameter reference="ModelValue_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_646">
              <SourceParameter reference="ModelValue_160"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_650">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="Inactivation_3" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_4">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.22" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0001100" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004693" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_83" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_85" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4237" name="Jicdh" value="1"/>
          <Constant key="Parameter_4241" name="Vicdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_106">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_652">
              <SourceParameter reference="Metabolite_83"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_647">
              <SourceParameter reference="ModelValue_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_651">
              <SourceParameter reference="ModelValue_161"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_654">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="CDC14 synthesis" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_3">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4242" name="ks14" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_107">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_644">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_655">
              <SourceParameter reference="ModelValue_121"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="CDC14 degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_2">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4240" name="kd14" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_108">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_656">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_658">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_649">
              <SourceParameter reference="ModelValue_73"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="Assoc. with NET1 to form RENT" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_1">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0005515" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0030869" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0043623" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_123" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_137" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4246" name="kasrent" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_109">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_653">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_663">
              <SourceParameter reference="Metabolite_123"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_661">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_659">
              <SourceParameter reference="ModelValue_70"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_0" name="Dissoc. from RENT" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_137" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_123" stoichiometry="1"/>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4245" name="kdirent" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_110">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_660">
              <SourceParameter reference="Metabolite_137"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_665">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_664">
              <SourceParameter reference="ModelValue_96"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_88" name="Assoc with NET1P to form RENTP" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_88">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0005515" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0030869" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0043623" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_125" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_139" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4244" name="kasrentp" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_111">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_662">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_670">
              <SourceParameter reference="Metabolite_125"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_668">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_666">
              <SourceParameter reference="ModelValue_71"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_89" name="Dissoc. from RENP" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_89">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_139" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
          <Product metabolite="Metabolite_125" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4239" name="kdirentp" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_112">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_667">
              <SourceParameter reference="Metabolite_139"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_672">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_671">
              <SourceParameter reference="ModelValue_97"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_90" name="Net1 synthesis" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_90">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_123" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4238" name="ksnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_113">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_669">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_673">
              <SourceParameter reference="ModelValue_139"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_91" name="Net1 degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_91">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_123" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4243" name="kdnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_114">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_675">
              <SourceParameter reference="Metabolite_123"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_677">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_674">
              <SourceParameter reference="ModelValue_99"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_92" name="Net1P degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_92">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_125" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4247" name="kdnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_115">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_657">
              <SourceParameter reference="Metabolite_125"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_680">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_678">
              <SourceParameter reference="ModelValue_99"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_93" name="NET1 phosphorylation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_93">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.1" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004672" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0031536" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_123" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_125" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4389" name="Vkpnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_116">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_676">
              <SourceParameter reference="Metabolite_123"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_681">
              <SourceParameter reference="ModelValue_163"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_683">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_94" name="dephosphorylation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_94">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.6.1.11" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004309" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_125" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_123" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4391" name="Vppnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_117">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_679">
              <SourceParameter reference="Metabolite_125"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_684">
              <SourceParameter reference="ModelValue_162"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_686">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_95" name="RENT phosphorylation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_95">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.1" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004672" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006468" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0031536" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_137" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_139" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4392" name="Vkpnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_118">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_682">
              <SourceParameter reference="Metabolite_137"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_687">
              <SourceParameter reference="ModelValue_163"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_689">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_96" name="dephosphorylation_2" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_96">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.6.1.11" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004309" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_139" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_137" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4390" name="Vppnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_119">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_685">
              <SourceParameter reference="Metabolite_139"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_690">
              <SourceParameter reference="ModelValue_162"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_692">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_97" name="Degradation of NET1 in RENT" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_97">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_137" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4393" name="kdnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_120">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_688">
              <SourceParameter reference="Metabolite_137"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_695">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_693">
              <SourceParameter reference="ModelValue_99"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_98" name="Degradation of NET1P in RENTP" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_98">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_139" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4507" name="kdnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_121">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_691">
              <SourceParameter reference="Metabolite_139"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_698">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_696">
              <SourceParameter reference="ModelValue_99"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_99" name="Degradation of CDC14 in RENT" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_99">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_137" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_123" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4508" name="kd14" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_122">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_694">
              <SourceParameter reference="Metabolite_137"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_701">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_699">
              <SourceParameter reference="ModelValue_73"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_100" name="Degradation of CDC14 in RENTP" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_100">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_139" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_125" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4278" name="kd14" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_123">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_697">
              <SourceParameter reference="Metabolite_139"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_704">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_702">
              <SourceParameter reference="ModelValue_73"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_101" name="TEM1 activation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_101">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0005515" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0005525" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0031536" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_155" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_157" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_115" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4277" name="Jatem" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_124">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_707">
              <SourceParameter reference="ModelValue_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_705">
              <SourceParameter reference="Metabolite_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_709">
              <SourceParameter reference="Metabolite_155"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_700">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_102" name="inactivation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_102">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0005096" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0005515" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0007094" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_157" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_155" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4382" name="Jitem" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_125">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_710">
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_711">
              <SourceParameter reference="ModelValue_51"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_713">
              <SourceParameter reference="Metabolite_157"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_706">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_103" name="CDC15 activation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_103">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.1" />
        <rdf:li rdf:resource="urn:miriam:ec-code:3.1.3.48" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0004721" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006470" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0031536" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_155" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_157" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4381" name="ka15_p" value="1"/>
          <Constant key="Parameter_4289" name="ka15_p_p" value="1"/>
          <Constant key="Parameter_4288" name="ka15p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_126">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_723">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_725">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_703">
              <SourceParameter reference="Metabolite_155"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_719">
              <SourceParameter reference="Metabolite_157"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_715">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_714">
              <SourceParameter reference="ModelValue_55"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_717">
              <SourceParameter reference="ModelValue_56"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_721">
              <SourceParameter reference="ModelValue_57"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_104" name="inactivation_2" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_104">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-05-07T16:14:52Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:2.7.11.1" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0001100" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006469" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4287" name="ki15" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_127">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_722">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_718">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_726">
              <SourceParameter reference="ModelValue_107"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_105" name="PPX synthesis" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_105">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:ec-code:3.6.1.11" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_135" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4286" name="ksppx" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_128">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_724">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_716">
              <SourceParameter reference="ModelValue_142"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_106" name="degradation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_106">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_135" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4285" name="Vdppx" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_129">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_712">
              <SourceParameter reference="Metabolite_135"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_708">
              <SourceParameter reference="ModelValue_164"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_728">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_107" name="PDS1 synthesis" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_107">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_131" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_141" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_121" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4284" name="ks1pds_p_p" value="1"/>
          <Constant key="Parameter_4283" name="ks2pds_p_p" value="1"/>
          <Constant key="Parameter_4282" name="kspds_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_130">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_737">
              <SourceParameter reference="Metabolite_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_731">
              <SourceParameter reference="Metabolite_141"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_733">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_720">
              <SourceParameter reference="ModelValue_122"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_735">
              <SourceParameter reference="ModelValue_125"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_729">
              <SourceParameter reference="ModelValue_141"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_108" name="degradation_2" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_108">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051437" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_131" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4281" name="Vdpds" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_131">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_734">
              <SourceParameter reference="Metabolite_131"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_738">
              <SourceParameter reference="ModelValue_165"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_730">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_109" name="Degradation of PDS1 in PE" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_109">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0051437" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_133" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_101" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4280" name="Vdpds" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_132">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_736">
              <SourceParameter reference="Metabolite_133"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_727">
              <SourceParameter reference="ModelValue_165"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_740">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_110" name="Assoc. with ESP1 to form PE" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_110">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0005515" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0043027" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0043623" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_131" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_101" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_133" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4279" name="kasesp" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_133">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_745">
              <SourceParameter reference="Metabolite_101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_732">
              <SourceParameter reference="Metabolite_131"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_743">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_741">
              <SourceParameter reference="ModelValue_67"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_111" name="Disso. from PE" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_111">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0043280" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_133" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_131" stoichiometry="1"/>
          <Product metabolite="Metabolite_101" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4380" name="kdiesp" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_134">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_742">
              <SourceParameter reference="Metabolite_133"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_747">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_746">
              <SourceParameter reference="ModelValue_93"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_112" name="DNA synthesis" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_112">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0000082" />
        <rdf:li rdf:resource="urn:miriam:obo.go:GO%3A0006261" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_129" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_93" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_89" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4379" name="eorib2" value="1"/>
          <Constant key="Parameter_4378" name="eorib5" value="1"/>
          <Constant key="Parameter_4377" name="ksori" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_135">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_756">
              <SourceParameter reference="Metabolite_89"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_750">
              <SourceParameter reference="Metabolite_93"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_752">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_754">
              <SourceParameter reference="ModelValue_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_744">
              <SourceParameter reference="ModelValue_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_748">
              <SourceParameter reference="ModelValue_140"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_113" name="Negative regulation of DNA synthesis" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_113">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0008156" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_129" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4376" name="kdori" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_136">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_753">
              <SourceParameter reference="Metabolite_129"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_749">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_757">
              <SourceParameter reference="ModelValue_100"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_114" name="Budding" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_114">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0045782" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_97" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_99" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_93" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4375" name="ebudb5" value="1"/>
          <Constant key="Parameter_4374" name="ebudn2" value="1"/>
          <Constant key="Parameter_4373" name="ebudn3" value="1"/>
          <Constant key="Parameter_4372" name="ksbud" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_137">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_769">
              <SourceParameter reference="Metabolite_93"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_759">
              <SourceParameter reference="Metabolite_97"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_765">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_761">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_767">
              <SourceParameter reference="ModelValue_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_755">
              <SourceParameter reference="ModelValue_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_763">
              <SourceParameter reference="ModelValue_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_739">
              <SourceParameter reference="ModelValue_130"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_115" name="Negative regulation of Cell budding" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_115">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0045781" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4371" name="kdbud" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_138">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_766">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_762">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_770">
              <SourceParameter reference="ModelValue_89"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_116" name="Spindle formation" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_116">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0051225" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_149" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_89" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_4370" name="Jspn" value="1"/>
          <Constant key="Parameter_4369" name="ksspn" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_139">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_768">
              <SourceParameter reference="Metabolite_89"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_751">
              <SourceParameter reference="ModelValue_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_772">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_760">
              <SourceParameter reference="ModelValue_143"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_117" name="Spindle disassembly" reversible="false" fast="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_117">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0051228" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_149" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_4368" name="kdspn" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_140">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_758">
              <SourceParameter reference="Metabolite_149"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_774">
              <SourceParameter reference="Compartment_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_773">
              <SourceParameter reference="ModelValue_103"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfEvents>
      <Event key="Event_2" name="reset ORI" fireAtInitialTime="0" persistentTrigger="0">
        <TriggerExpression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[KEZ2],Reference=Value&gt; lt 0
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="Metabolite_129">
            <Expression>
              0/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_0" name="start DNA synthesis" fireAtInitialTime="0" persistentTrigger="0">
        <TriggerExpression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ORI],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;-1 gt 0
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="Metabolite_117">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mad2h],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_45">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[bub2h],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_3" name="spindle checkpoint" fireAtInitialTime="0" persistentTrigger="0">
        <TriggerExpression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SPN],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;-1 gt 0
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="Metabolite_117">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mad2l],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_115">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[lte1h],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_45">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[bub2l],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_4" name="cell division" fireAtInitialTime="0" persistentTrigger="0">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-03-02T13:14:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <TriggerExpression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[KEZ],Reference=Value&gt; lt 0
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="Metabolite_119">
            <Expression>
              (1-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[F],Reference=Value&gt;)*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MASS],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_115">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[lte1l],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_41">
            <Expression>
              0/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_149">
            <Expression>
              0/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_173">
            <Expression>
              if(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[1stDivisionTime],Reference=Value&gt; lt 0,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[1stDivisionTime],Reference=Value&gt;)
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_176">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[T0],Reference=Value&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_175">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time&gt;
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
    </ListOfEvents>
    <ListOfModelParameterSets activeSet="ModelParameterSet_1">
      <ModelParameterSet key="ModelParameterSet_1" name="Initial State">
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell]" value="1" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BCK2]" value="2.769598672382914e+22" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BUB2]" value="1.204428300000005e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BUD]" value="9.000829013319018e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2]" value="1.415750029349604e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2P]" value="5.428453477226389e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5]" value="6.3287734055348e+22" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5P]" value="2.307420732690804e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14]" value="1.80535936470497e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14T]" value="1.20442800000001e+24" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC15]" value="3.817302580975654e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC15i]" value="2.204838369841239e+23" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC20]" value="2.29204033134851e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC20i]" value="6.649934635684339e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6]" value="1.747366772326145e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6P]" value="6.987702526155101e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6T]" value="2.925132390092359e+23" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDH1]" value="6.004823451606606e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDH1i]" value="1.731804839342613e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CKIT]" value="5.698007708108632e+23" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2]" value="9.253339255958898e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2T]" value="2.669832374374183e+23" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5]" value="3.888445993186847e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5T]" value="6.954600729887336e+22" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN2]" value="2.879579509269514e+22" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN3]" value="2.994239436853977e+22" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ESP1]" value="2.159777877052535e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2]" value="1.056512290096014e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2P]" value="5.07527926009403e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5]" value="6.000645303884879e+19" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5P]" value="2.417387190365045e+18" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[IE]" value="5.802510581936991e+23" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[IEP]" value="2.196294727685002e+22" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[LTE1]" value="6.022141500000027e+22" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MAD2]" value="6.022141499999998e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MASS]" value="5.128887707846334e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MCM1]" value="6.177542491684398e+21" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1]" value="2.019185755329673e+22" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1P]" value="6.421153989171979e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1T]" value="1.686199200000007e+24" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ORI]" value="5.793351133464459e+22" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PDS1]" value="1.093220582617615e+22" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PE]" value="3.86236266090673e+23" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PPX]" value="7.235672544851775e+22" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENT]" value="8.274840214739905e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENTP]" value="1.964083420555222e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SBF]" value="7.496739071384451e+21" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1]" value="6.153793596801723e+22" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1P]" value="3.151195626929545e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1T]" value="2.772876737281114e+23" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SPN]" value="3.305249612645038e+22" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SWI5]" value="5.446744061809811e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SWI5P]" value="7.393161906544548e+21" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[TEM1GDP]" value="1.263726206237145e+23" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[TEM1GTP]" value="4.758414978992805e+23" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[GLU]" value="1.204428357999999e+21" type="Species" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[b0]" value="0.054" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[bub2h]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[bub2l]" value="0.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[C0]" value="0.4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[CDC15T]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Dn3]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ebudb5]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ebudn2]" value="0.25" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ebudn3]" value="0.05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ec1b2]" value="0.45" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ec1b5]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ec1k2]" value="0.03" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ec1n2]" value="0.06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ec1n3]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ef6b2]" value="0.55" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ef6b5]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ef6k2]" value="0.03" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ef6n2]" value="0.06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ef6n3]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[eicdhb2]" value="1.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[eicdhb5]" value="8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[eicdhn2]" value="0.4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[eicdhn3]" value="0.25" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[eorib2]" value="0.45" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[eorib5]" value="0.9" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[esbfb5]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[esbfn2]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[esbfn3]" value="10" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ESP1T]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[IET]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[J20ppx]" value="0.15" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jacdh]" value="0.03" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jaiep]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jamcm]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jasbf]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jatem]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jd2c1]" value="0.05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jd2f6]" value="0.05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jicdh]" value="0.03" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jiiep]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jimcm]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jisbf]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jitem]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jn3]" value="6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jpds]" value="0.04" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jspn]" value="0.14" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ka15']" value="0.002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ka15'']" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ka15p]" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ka20']" value="0.05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ka20'']" value="0.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kacdh']" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kacdh'']" value="0.8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kaiep]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kamcm]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasb2]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasb5]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasbf]" value="0.38" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasesp]" value="50" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasf2]" value="15" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasf5]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasrent]" value="200" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasrentp]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kaswi]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd14]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd1c1]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd1f6]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd1pds']" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd20]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd2c1]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd2f6]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd2pds'']" value="0.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd3c1]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd3f6]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd3pds'']" value="0.04" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdb2']" value="0.003" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdb2'']" value="0.4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdb2p]" value="0.15" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdb5']" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdb5'']" value="0.16" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdbud]" value="0.06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdcdh]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdib2]" value="0.05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdib5]" value="0.06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdiesp]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdif2]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdif5]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdirent]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdirentp]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdn2]" value="0.12" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdnet]" value="0.03" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdori]" value="0.06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdppx']" value="0.17" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdppx'']" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdspn]" value="0.06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdswi]" value="0.08" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[KEZ]" value="0.3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[KEZ2]" value="0.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ki15]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kicdh']" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kicdh'']" value="0.08" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kiiep]" value="0.15" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kimcm]" value="0.15" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kisbf']" value="0.6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kisbf'']" value="8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kiswi]" value="0.05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kkpnet']" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kkpnet'']" value="0.6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kppc1]" value="4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kppf6]" value="4" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kppnet']" value="0.05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kppnet'']" value="3" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ks14]" value="0.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ks1pds'']" value="0.03" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ks20']" value="0.006" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ks20'']" value="0.6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ks2pds'']" value="0.055" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksb2']" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksb2'']" value="0.04" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksb5']" value="0.0008" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksb5'']" value="0.005" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksbud]" value="0.2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksc1']" value="0.012" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksc1'']" value="0.12" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kscdh]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksf6']" value="0.024" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksf6'']" value="0.12" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksf6''']" value="0.004" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksn2']" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksn2'']" value="0.15" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksnet]" value="0.08400000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksori]" value="2" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kspds']" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksppx]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksspn]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksswi']" value="0.005" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksswi'']" value="0.08" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[lte1h]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[lte1l]" value="0.1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mad2h]" value="8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mad2l]" value="0.01" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mdt]" value="104.9622855759751" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[TEM1T]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[D]" value="123.3657116717321" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mu]" value="0.0066037736960122" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb5]" value="0.07089635273693944" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb2]" value="0.4589400389952509" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vasbf]" value="0.4049487568106332" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Visbf]" value="0.7229242355857484" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpc1]" value="0.0623561288838139" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpf6]" value="0.06275343987480581" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vacdh]" value="0.2498295509602317" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vicdh]" value="0.009132056237052346" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppnet]" value="0.410453463847625" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpnet]" value="0.3324302671175433" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdppx]" value="0.8999351532761247" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdpds]" value="0.1260054117516113" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vaiep]" value="0.001536552944821854" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vd2c1]" value="0.02672503275178556" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vd2f6]" value="0.02826158569660742" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppc1]" value="1.199147754801158" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppf6]" value="1.199147754801158" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[F]" value="0.4427813303603884" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor]" value="6.0221415e+23" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[1stDivisionTime]" value="-1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mu2]" value="0.007" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[T0]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Period]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[KmGLU]" value="0.00012" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[GLUconsumed]" value="0" type="ModelValue" simulationType="ode"/>
          <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[quantity_1]" value="0" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Growth]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Growth],ParameterGroup=Parameters,Parameter=k" value="0.007" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mu2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Growth],ParameterGroup=Parameters,Parameter=Kmsub" value="0.00012" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[KmGLU],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of CLN2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of CLN2],ParameterGroup=Parameters,Parameter=ksn2_p" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksn2&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of CLN2],ParameterGroup=Parameters,Parameter=ksn2_p_p" value="0.15" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksn2&apos;&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLN2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLN2],ParameterGroup=Parameters,Parameter=kdn2" value="0.12" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdn2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of CLB2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of CLB2],ParameterGroup=Parameters,Parameter=ksb2_p" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksb2&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of CLB2],ParameterGroup=Parameters,Parameter=ksb2_p_p" value="0.04" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksb2&apos;&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLB2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLB2],ParameterGroup=Parameters,Parameter=Vdb2" value="0.4589400389952509" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of CLB5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of CLB5],ParameterGroup=Parameters,Parameter=ksb5_p" value="0.0008" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksb5&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of CLB5],ParameterGroup=Parameters,Parameter=ksb5_p_p" value="0.005" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksb5&apos;&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLB5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLB5],ParameterGroup=Parameters,Parameter=Vdb5" value="0.07089635273693944" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb5],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of SIC1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of SIC1],ParameterGroup=Parameters,Parameter=ksc1_p" value="0.012" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksc1&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of SIC1],ParameterGroup=Parameters,Parameter=ksc1_p_p" value="0.12" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksc1&apos;&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Phosphorylation of SIC1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Phosphorylation of SIC1],ParameterGroup=Parameters,Parameter=Vkpc1" value="0.0623561288838139" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpc1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dephosphorylation of SIC1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dephosphorylation of SIC1],ParameterGroup=Parameters,Parameter=Vppc1" value="1.199147754801158" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppc1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Fast Degradation of SIC1P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Fast Degradation of SIC1P],ParameterGroup=Parameters,Parameter=kd3c1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd3c1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Assoc. of CLB2 and SIC1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Assoc. of CLB2 and SIC1],ParameterGroup=Parameters,Parameter=kasb2" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasb2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dissoc. of CLB2/SIC1 complex]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dissoc. of CLB2/SIC1 complex],ParameterGroup=Parameters,Parameter=kdib2" value="0.05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdib2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Assoc. of CLB5 and SIC1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Assoc. of CLB5 and SIC1],ParameterGroup=Parameters,Parameter=kasb5" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasb5],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dissoc. of CLB5/SIC1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dissoc. of CLB5/SIC1],ParameterGroup=Parameters,Parameter=kdib5" value="0.06" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdib5],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Phosphorylation of C2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Phosphorylation of C2],ParameterGroup=Parameters,Parameter=Vkpc1" value="0.0623561288838139" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpc1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dephosphorylation of C2P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dephosphorylation of C2P],ParameterGroup=Parameters,Parameter=Vppc1" value="1.199147754801158" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppc1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Phosphorylation of C5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Phosphorylation of C5],ParameterGroup=Parameters,Parameter=Vkpc1" value="0.0623561288838139" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpc1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dephosphorylation of C5P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dephosphorylation of C5P],ParameterGroup=Parameters,Parameter=Vppc1" value="1.199147754801158" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppc1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLB2 in C2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLB2 in C2],ParameterGroup=Parameters,Parameter=Vdb2" value="0.4589400389952509" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLB5 in C5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLB5 in C5],ParameterGroup=Parameters,Parameter=Vdb5" value="0.07089635273693944" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb5],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of SIC1 in C2P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of SIC1 in C2P],ParameterGroup=Parameters,Parameter=kd3c1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd3c1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of SIC1P in C5P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of SIC1P in C5P],ParameterGroup=Parameters,Parameter=kd3c1" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd3c1],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLB2 in C2P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLB2 in C2P],ParameterGroup=Parameters,Parameter=Vdb2" value="0.4589400389952509" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLB5 in C5P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CLB5 in C5P],ParameterGroup=Parameters,Parameter=Vdb5" value="0.07089635273693944" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb5],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC6 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC6 synthesis],ParameterGroup=Parameters,Parameter=ksf6_p" value="0.024" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksf6&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC6 synthesis],ParameterGroup=Parameters,Parameter=ksf6_p_p" value="0.12" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksf6&apos;&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC6 synthesis],ParameterGroup=Parameters,Parameter=ksf6_p_p_p" value="0.004" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksf6&apos;&apos;&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Phosphorylation of CDC6]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Phosphorylation of CDC6],ParameterGroup=Parameters,Parameter=Vkpf6" value="0.06275343987480581" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpf6],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dephosphorylation of CDC6]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dephosphorylation of CDC6],ParameterGroup=Parameters,Parameter=Vppf6" value="1.199147754801158" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppf6],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CDC6P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CDC6P],ParameterGroup=Parameters,Parameter=kd3f6" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd3f6],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB2/CDC6 complex formation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB2/CDC6 complex formation],ParameterGroup=Parameters,Parameter=kasf2" value="15" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasf2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB2/CDC6 dissociation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB2/CDC6 dissociation],ParameterGroup=Parameters,Parameter=kdif2" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdif2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB5/CDC6 complex formation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB5/CDC6 complex formation],ParameterGroup=Parameters,Parameter=kasf5" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasf5],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB5/CDC6 dissociation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB5/CDC6 dissociation],ParameterGroup=Parameters,Parameter=kdif5" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdif5],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[F2 phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[F2 phosphorylation],ParameterGroup=Parameters,Parameter=Vkpf6" value="0.06275343987480581" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpf6],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[F2P dephosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[F2P dephosphorylation],ParameterGroup=Parameters,Parameter=Vppf6" value="1.199147754801158" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppf6],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[F5 phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[F5 phosphorylation],ParameterGroup=Parameters,Parameter=Vkpf6" value="0.06275343987480581" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpf6],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[F5P dephosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[F5P dephosphorylation],ParameterGroup=Parameters,Parameter=Vppf6" value="1.199147754801158" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppf6],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB2 degradation in F2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB2 degradation in F2],ParameterGroup=Parameters,Parameter=Vdb2" value="0.4589400389952509" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB5 degradation in F5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB5 degradation in F5],ParameterGroup=Parameters,Parameter=Vdb5" value="0.07089635273693944" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb5],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC6 degradation in F2P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC6 degradation in F2P],ParameterGroup=Parameters,Parameter=kd3f6" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd3f6],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC6 degradation in F5P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC6 degradation in F5P],ParameterGroup=Parameters,Parameter=kd3f6" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd3f6],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB2 degradation in F2P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB2 degradation in F2P],ParameterGroup=Parameters,Parameter=Vdb2" value="0.4589400389952509" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB5 degradation in F5P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CLB5 degradation in F5P],ParameterGroup=Parameters,Parameter=Vdb5" value="0.07089635273693944" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb5],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of SWI5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of SWI5],ParameterGroup=Parameters,Parameter=ksswi_p" value="0.005" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksswi&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of SWI5],ParameterGroup=Parameters,Parameter=ksswi_p_p" value="0.08" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksswi&apos;&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of SWI5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of SWI5],ParameterGroup=Parameters,Parameter=kdswi" value="0.08" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdswi],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of SWI5P]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of SWI5P],ParameterGroup=Parameters,Parameter=kdswi" value="0.08" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdswi],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Activation of SWI5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Activation of SWI5],ParameterGroup=Parameters,Parameter=kaswi" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kaswi],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Inactivation of SWI5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Inactivation of SWI5],ParameterGroup=Parameters,Parameter=kiswi" value="0.05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kiswi],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Activation of IEP]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Activation of IEP],ParameterGroup=Parameters,Parameter=Jaiep" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jaiep],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Activation of IEP],ParameterGroup=Parameters,Parameter=Vaiep" value="0.001536552944821854" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vaiep],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Inactivation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Inactivation],ParameterGroup=Parameters,Parameter=Jiiep" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jiiep],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Inactivation],ParameterGroup=Parameters,Parameter=kiiep" value="0.15" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kiiep],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of inactive CDC20]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of inactive CDC20],ParameterGroup=Parameters,Parameter=ks20_p" value="0.006" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ks20&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Synthesis of inactive CDC20],ParameterGroup=Parameters,Parameter=ks20_p_p" value="0.6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ks20&apos;&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of inactiveCDC20]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of inactiveCDC20],ParameterGroup=Parameters,Parameter=kd20" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd20],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of active CDC20]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of active CDC20],ParameterGroup=Parameters,Parameter=kd20" value="0.3" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd20],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Activation of CDC20]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Activation of CDC20],ParameterGroup=Parameters,Parameter=ka20_p" value="0.05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ka20&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Activation of CDC20],ParameterGroup=Parameters,Parameter=ka20_p_p" value="0.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ka20&apos;&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Inactivation_2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Inactivation_2],ParameterGroup=Parameters,Parameter=k" value="1" type="ReactionParameter" simulationType="fixed"/>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDH1 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDH1 synthesis],ParameterGroup=Parameters,Parameter=kscdh" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kscdh],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDH1 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDH1 degradation],ParameterGroup=Parameters,Parameter=kdcdh" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdcdh],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDH1i degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDH1i degradation],ParameterGroup=Parameters,Parameter=kdcdh" value="0.01" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdcdh],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDH1i activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDH1i activation],ParameterGroup=Parameters,Parameter=Jacdh" value="0.03" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jacdh],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDH1i activation],ParameterGroup=Parameters,Parameter=Vacdh" value="0.2498295509602317" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vacdh],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Inactivation_3]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Inactivation_3],ParameterGroup=Parameters,Parameter=Jicdh" value="0.03" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jicdh],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Inactivation_3],ParameterGroup=Parameters,Parameter=Vicdh" value="0.009132056237052346" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vicdh],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC14 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC14 synthesis],ParameterGroup=Parameters,Parameter=ks14" value="0.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ks14],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC14 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC14 degradation],ParameterGroup=Parameters,Parameter=kd14" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd14],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Assoc. with NET1 to form RENT]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Assoc. with NET1 to form RENT],ParameterGroup=Parameters,Parameter=kasrent" value="200" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasrent],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dissoc. from RENT]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dissoc. from RENT],ParameterGroup=Parameters,Parameter=kdirent" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdirent],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Assoc with NET1P to form RENTP]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Assoc with NET1P to form RENTP],ParameterGroup=Parameters,Parameter=kasrentp" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasrentp],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dissoc. from RENP]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Dissoc. from RENP],ParameterGroup=Parameters,Parameter=kdirentp" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdirentp],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Net1 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Net1 synthesis],ParameterGroup=Parameters,Parameter=ksnet" value="0.08400000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksnet],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Net1 degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Net1 degradation],ParameterGroup=Parameters,Parameter=kdnet" value="0.03" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdnet],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Net1P degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Net1P degradation],ParameterGroup=Parameters,Parameter=kdnet" value="0.03" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdnet],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[NET1 phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[NET1 phosphorylation],ParameterGroup=Parameters,Parameter=Vkpnet" value="0.3324302671175433" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpnet],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[dephosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[dephosphorylation],ParameterGroup=Parameters,Parameter=Vppnet" value="0.410453463847625" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppnet],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[RENT phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[RENT phosphorylation],ParameterGroup=Parameters,Parameter=Vkpnet" value="0.3324302671175433" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpnet],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[dephosphorylation_2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[dephosphorylation_2],ParameterGroup=Parameters,Parameter=Vppnet" value="0.410453463847625" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppnet],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of NET1 in RENT]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of NET1 in RENT],ParameterGroup=Parameters,Parameter=kdnet" value="0.03" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdnet],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of NET1P in RENTP]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of NET1P in RENTP],ParameterGroup=Parameters,Parameter=kdnet" value="0.03" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdnet],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CDC14 in RENT]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CDC14 in RENT],ParameterGroup=Parameters,Parameter=kd14" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd14],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CDC14 in RENTP]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of CDC14 in RENTP],ParameterGroup=Parameters,Parameter=kd14" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kd14],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[TEM1 activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[TEM1 activation],ParameterGroup=Parameters,Parameter=Jatem" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jatem],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[inactivation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[inactivation],ParameterGroup=Parameters,Parameter=Jitem" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jitem],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC15 activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC15 activation],ParameterGroup=Parameters,Parameter=ka15_p" value="0.002" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ka15&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC15 activation],ParameterGroup=Parameters,Parameter=ka15_p_p" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ka15&apos;&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[CDC15 activation],ParameterGroup=Parameters,Parameter=ka15p" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ka15p],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[inactivation_2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[inactivation_2],ParameterGroup=Parameters,Parameter=ki15" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ki15],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[PPX synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[PPX synthesis],ParameterGroup=Parameters,Parameter=ksppx" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksppx],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[degradation],ParameterGroup=Parameters,Parameter=Vdppx" value="0.8999351532761247" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdppx],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[PDS1 synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[PDS1 synthesis],ParameterGroup=Parameters,Parameter=ks1pds_p_p" value="0.03" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ks1pds&apos;&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[PDS1 synthesis],ParameterGroup=Parameters,Parameter=ks2pds_p_p" value="0.055" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ks2pds&apos;&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[PDS1 synthesis],ParameterGroup=Parameters,Parameter=kspds_p" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kspds&apos;],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[degradation_2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[degradation_2],ParameterGroup=Parameters,Parameter=Vdpds" value="0.1260054117516113" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdpds],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of PDS1 in PE]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Degradation of PDS1 in PE],ParameterGroup=Parameters,Parameter=Vdpds" value="0.1260054117516113" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdpds],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Assoc. with ESP1 to form PE]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Assoc. with ESP1 to form PE],ParameterGroup=Parameters,Parameter=kasesp" value="50" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kasesp],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Disso. from PE]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Disso. from PE],ParameterGroup=Parameters,Parameter=kdiesp" value="0.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdiesp],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[DNA synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[DNA synthesis],ParameterGroup=Parameters,Parameter=eorib2" value="0.45" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[eorib2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[DNA synthesis],ParameterGroup=Parameters,Parameter=eorib5" value="0.9" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[eorib5],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[DNA synthesis],ParameterGroup=Parameters,Parameter=ksori" value="2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksori],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Negative regulation of DNA synthesis]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Negative regulation of DNA synthesis],ParameterGroup=Parameters,Parameter=kdori" value="0.06" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdori],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Budding]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Budding],ParameterGroup=Parameters,Parameter=ebudb5" value="1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ebudb5],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Budding],ParameterGroup=Parameters,Parameter=ebudn2" value="0.25" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ebudn2],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Budding],ParameterGroup=Parameters,Parameter=ebudn3" value="0.05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ebudn3],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Budding],ParameterGroup=Parameters,Parameter=ksbud" value="0.2" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksbud],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Negative regulation of Cell budding]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Negative regulation of Cell budding],ParameterGroup=Parameters,Parameter=kdbud" value="0.06" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdbud],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Spindle formation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Spindle formation],ParameterGroup=Parameters,Parameter=Jspn" value="0.14" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jspn],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Spindle formation],ParameterGroup=Parameters,Parameter=ksspn" value="0.1" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ksspn],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Spindle disassembly]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Reactions[Spindle disassembly],ParameterGroup=Parameters,Parameter=kdspn" value="0.06" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[kdspn],Reference=InitialValue&gt;
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_7"/>
      <StateTemplateVariable objectReference="ModelValue_178"/>
      <StateTemplateVariable objectReference="Metabolite_77"/>
      <StateTemplateVariable objectReference="Metabolite_143"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="Metabolite_89"/>
      <StateTemplateVariable objectReference="Metabolite_93"/>
      <StateTemplateVariable objectReference="Metabolite_123"/>
      <StateTemplateVariable objectReference="Metabolite_139"/>
      <StateTemplateVariable objectReference="Metabolite_79"/>
      <StateTemplateVariable objectReference="Metabolite_145"/>
      <StateTemplateVariable objectReference="Metabolite_83"/>
      <StateTemplateVariable objectReference="Metabolite_131"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_151"/>
      <StateTemplateVariable objectReference="Metabolite_125"/>
      <StateTemplateVariable objectReference="Metabolite_105"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Metabolite_109"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_107"/>
      <StateTemplateVariable objectReference="Metabolite_37"/>
      <StateTemplateVariable objectReference="Metabolite_113"/>
      <StateTemplateVariable objectReference="Metabolite_129"/>
      <StateTemplateVariable objectReference="Metabolite_135"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_97"/>
      <StateTemplateVariable objectReference="Metabolite_41"/>
      <StateTemplateVariable objectReference="Metabolite_149"/>
      <StateTemplateVariable objectReference="Metabolite_157"/>
      <StateTemplateVariable objectReference="Metabolite_101"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_85"/>
      <StateTemplateVariable objectReference="Metabolite_153"/>
      <StateTemplateVariable objectReference="Metabolite_137"/>
      <StateTemplateVariable objectReference="Metabolite_103"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_119"/>
      <StateTemplateVariable objectReference="Metabolite_49"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_99"/>
      <StateTemplateVariable objectReference="Metabolite_111"/>
      <StateTemplateVariable objectReference="Metabolite_121"/>
      <StateTemplateVariable objectReference="Metabolite_133"/>
      <StateTemplateVariable objectReference="Metabolite_141"/>
      <StateTemplateVariable objectReference="Metabolite_155"/>
      <StateTemplateVariable objectReference="ModelValue_154"/>
      <StateTemplateVariable objectReference="ModelValue_155"/>
      <StateTemplateVariable objectReference="ModelValue_156"/>
      <StateTemplateVariable objectReference="ModelValue_157"/>
      <StateTemplateVariable objectReference="ModelValue_158"/>
      <StateTemplateVariable objectReference="ModelValue_159"/>
      <StateTemplateVariable objectReference="ModelValue_160"/>
      <StateTemplateVariable objectReference="ModelValue_161"/>
      <StateTemplateVariable objectReference="ModelValue_162"/>
      <StateTemplateVariable objectReference="ModelValue_163"/>
      <StateTemplateVariable objectReference="ModelValue_164"/>
      <StateTemplateVariable objectReference="ModelValue_165"/>
      <StateTemplateVariable objectReference="ModelValue_166"/>
      <StateTemplateVariable objectReference="ModelValue_167"/>
      <StateTemplateVariable objectReference="ModelValue_168"/>
      <StateTemplateVariable objectReference="ModelValue_169"/>
      <StateTemplateVariable objectReference="ModelValue_170"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="Metabolite_81"/>
      <StateTemplateVariable objectReference="Metabolite_87"/>
      <StateTemplateVariable objectReference="Metabolite_91"/>
      <StateTemplateVariable objectReference="Metabolite_95"/>
      <StateTemplateVariable objectReference="Metabolite_127"/>
      <StateTemplateVariable objectReference="Metabolite_147"/>
      <StateTemplateVariable objectReference="ModelValue_150"/>
      <StateTemplateVariable objectReference="ModelValue_152"/>
      <StateTemplateVariable objectReference="ModelValue_153"/>
      <StateTemplateVariable objectReference="ModelValue_171"/>
      <StateTemplateVariable objectReference="Metabolite_159"/>
      <StateTemplateVariable objectReference="Metabolite_45"/>
      <StateTemplateVariable objectReference="Metabolite_115"/>
      <StateTemplateVariable objectReference="Metabolite_117"/>
      <StateTemplateVariable objectReference="Compartment_3"/>
      <StateTemplateVariable objectReference="ModelValue_6"/>
      <StateTemplateVariable objectReference="ModelValue_5"/>
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
      <StateTemplateVariable objectReference="ModelValue_115"/>
      <StateTemplateVariable objectReference="ModelValue_116"/>
      <StateTemplateVariable objectReference="ModelValue_117"/>
      <StateTemplateVariable objectReference="ModelValue_118"/>
      <StateTemplateVariable objectReference="ModelValue_119"/>
      <StateTemplateVariable objectReference="ModelValue_120"/>
      <StateTemplateVariable objectReference="ModelValue_121"/>
      <StateTemplateVariable objectReference="ModelValue_122"/>
      <StateTemplateVariable objectReference="ModelValue_123"/>
      <StateTemplateVariable objectReference="ModelValue_124"/>
      <StateTemplateVariable objectReference="ModelValue_125"/>
      <StateTemplateVariable objectReference="ModelValue_126"/>
      <StateTemplateVariable objectReference="ModelValue_127"/>
      <StateTemplateVariable objectReference="ModelValue_128"/>
      <StateTemplateVariable objectReference="ModelValue_129"/>
      <StateTemplateVariable objectReference="ModelValue_130"/>
      <StateTemplateVariable objectReference="ModelValue_131"/>
      <StateTemplateVariable objectReference="ModelValue_132"/>
      <StateTemplateVariable objectReference="ModelValue_133"/>
      <StateTemplateVariable objectReference="ModelValue_134"/>
      <StateTemplateVariable objectReference="ModelValue_135"/>
      <StateTemplateVariable objectReference="ModelValue_136"/>
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
      <StateTemplateVariable objectReference="ModelValue_147"/>
      <StateTemplateVariable objectReference="ModelValue_148"/>
      <StateTemplateVariable objectReference="ModelValue_149"/>
      <StateTemplateVariable objectReference="ModelValue_151"/>
      <StateTemplateVariable objectReference="ModelValue_172"/>
      <StateTemplateVariable objectReference="ModelValue_173"/>
      <StateTemplateVariable objectReference="ModelValue_174"/>
      <StateTemplateVariable objectReference="ModelValue_175"/>
      <StateTemplateVariable objectReference="ModelValue_176"/>
      <StateTemplateVariable objectReference="ModelValue_177"/>
      <StateTemplateVariable objectReference="ModelValue_179"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 1.747366772326145e+23 6.153793596801723e+22 1.80535936470497e+23 9.253339255958898e+21 3.888445993186847e+21 2.019185755329673e+22 1.964083420555222e+23 6.987702526155101e+21 3.151195626929545e+21 6.004823451606606e+23 1.093220582617615e+22 6.649934635684339e+23 5.446744061809811e+23 6.421153989171979e+23 5.07527926009403e+21 2.307420732690804e+21 2.417387190365045e+18 5.428453477226389e+21 6.000645303884879e+19 1.415750029349604e+23 2.196294727685002e+22 5.793351133464459e+22 7.235672544851775e+22 3.817302580975654e+23 2.879579509269514e+22 9.000829013319018e+21 3.305249612645038e+22 4.758414978992805e+23 2.159777877052535e+23 2.29204033134851e+23 1.731804839342613e+21 7.393161906544548e+21 8.274840214739905e+23 1.056512290096014e+23 6.3287734055348e+22 5.128887707846334e+23 2.769598672382914e+22 2.204838369841239e+23 2.994239436853977e+22 5.802510581936991e+23 6.177542491684398e+21 3.86236266090673e+23 7.496739071384451e+21 1.263726206237145e+23 0.07089635273693944 0.4589400389952509 0.4049487568106332 0.7229242355857484 0.0623561288838139 0.06275343987480581 0.2498295509602317 0.009132056237052346 0.410453463847625 0.3324302671175433 0.8999351532761247 0.1260054117516113 0.001536552944821854 0.02672503275178556 0.02826158569660742 1.199147754801158 1.199147754801158 1.20442800000001e+24 2.925132390092359e+23 5.698007708108632e+23 2.669832374374183e+23 6.954600729887336e+22 1.686199200000007e+24 2.772876737281114e+23 104.9622855759751 123.3657116717321 0.0066037736960122 0.4427813303603884 1.204428357999999e+21 1.204428300000005e+23 6.022141500000027e+22 6.022141499999998e+21 1 0.054 1 0.2 0.4 1 1 1 0.25 0.05 0.45 0.1 0.03 0.06 0.3 0.55 0.1 0.03 0.06 0.3 1.2 8 0.4 0.25 0.45 0.9 2 2 10 1 1 0.15 0.03 0.1 0.1 0.01 0.1 0.05 0.05 0.03 0.1 0.1 0.01 0.1 6 0.04 0.14 0.002 1 0.001 0.05 0.2 0.01 0.8 0.1 1 50 50 0.38 50 15 0.01 200 1 2 0.1 0.01 0.01 0.01 0.3 1 1 0.2 1 1 0.04 0.003 0.4 0.15 0.01 0.16 0.06 0.01 0.05 0.06 0.5 0.5 0.01 1 2 0.12 0.03 0.06 0.17 2 0.06 0.08 0.3 0.2 0.5 0.001 0.08 0.15 0.15 0.6 8 0.05 0.01 0.6 4 4 0.05 3 0.2 0.03 0.006 0.6 0.055 0.001 0.04 0.0008 0.005 0.2 0.012 0.12 0.01 0.024 0.12 0.004 0 0.15 0.08400000000000001 2 0 0.1 0.1 0.005 0.08 1 0.1 8 0.01 1 6.0221415e+23 -1 0.007 0 0 0.00012 0 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_27" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_20" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_15" name="Time-Course" type="timeCourse" scheduled="true" updateModel="false">
      <Report reference="Report_15" target="EventTest12.1.txt" append="0" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="2"/>
        <Parameter name="StepSize" type="float" value="200"/>
        <Parameter name="Duration" type="float" value="400"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="1"/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_16" name="Scan" type="scan" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="1"/>
        <ParameterGroup name="ScanItems">
          <ParameterGroup name="ScanItem">
            <Parameter name="Maximum" type="float" value="0.01"/>
            <Parameter name="Minimum" type="float" value="0.0004"/>
            <Parameter name="Number of steps" type="unsignedInteger" value="15"/>
            <Parameter name="Object" type="cn" value="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[GLU],Reference=InitialConcentration"/>
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
      <Report reference="Report_19" target="" append="1" confirmOverwrite="0"/>
      <Problem>
      </Problem>
      <Method name="Bit Pattern Tree Algorithm" type="EFMBitPatternTreeMethod">
      </Method>
    </Task>
    <Task key="Task_18" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_9" target="" append="1" confirmOverwrite="0"/>
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
      <Report reference="Report_10" target="" append="1" confirmOverwrite="0"/>
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
      <Report reference="Report_11" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value=""/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1e-09"/>
      </Method>
    </Task>
    <Task key="Task_21" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_12" target="" append="1" confirmOverwrite="0"/>
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
      <Report reference="Report_13" target="" append="1" confirmOverwrite="0"/>
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
      <Report reference="Report_14" target="" append="1" confirmOverwrite="0"/>
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
        <Parameter name="ConvergenceTolerance" type="float" value="1e-06"/>
        <Parameter name="Threshold" type="float" value="0"/>
        <Parameter name="DelayOutputUntilConvergence" type="bool" value="0"/>
        <Parameter name="OutputConvergenceTolerance" type="float" value="1e-06"/>
        <ParameterText name="TriggerExpression" type="expression">
          
        </ParameterText>
        <Parameter name="SingleVariable" type="cn" value=""/>
        <Parameter name="LimitTime" type="bool" value="1"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_14" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_16" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_27"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_20" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_19" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_9" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
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
    <Report key="Report_10" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
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
    <Report key="Report_11" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
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
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_13" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
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
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Sensitivities],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Sensitivities],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_15" name="Events" taskType="timeCourse" separator="&#x09;" precision="7">
      <Comment>
        A table of time, variable species concentrations, variable compartment volumes, and variable global quantity values.
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BCK2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BUB2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BUD],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14T],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC15],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC15i],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC20],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC20i],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6T],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDH1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDH1i],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CKIT],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2T],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5T],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN3],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ESP1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[IE],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[IEP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[LTE1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MAD2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MASS],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MCM1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1T],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ORI],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PDS1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PE],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PPX],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENT],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENTP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SBF],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1T],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SPN],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SWI5],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SWI5P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[TEM1GDP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[TEM1GTP],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mdt],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[D],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mu],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb5],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb2],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vasbf],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Visbf],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpc1],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpf6],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vacdh],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vicdh],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppnet],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpnet],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdppx],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdpds],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vaiep],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vd2c1],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vd2f6],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppc1],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppf6],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[F],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[1stDivisionTime],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[T0],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Period],Reference=Value"/>
        <Object cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[GLUconsumed],Reference=Value"/>
      </Table>
    </Report>
    <Report key="Report_16" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <PlotSpecification name="Concentrations, Volumes, and Global Quantity Values" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="[BCK2]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BCK2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[BUB2]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BUB2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[BUD]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BUD],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[C2]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[C2P]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[C5]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[C5P]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC14]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC14T]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC15]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC15],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC15i]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC15i],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC20]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC20],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC20i]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC20i],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC6]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC6P]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC6T]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDH1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDH1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDH1i]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDH1i],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CKIT]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CKIT],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CLB2]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CLB2T]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CLB5]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CLB5T]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CLN2]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CLN3]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN3],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[ESP1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ESP1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[F2]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[F2P]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[F5]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[F5P]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IE]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[IE],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IEP]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[IEP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[LTE1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[LTE1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[MAD2]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MAD2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[MASS]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MASS],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[MCM1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MCM1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[NET1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[NET1P]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[NET1T]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[ORI]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ORI],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[PDS1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PDS1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[PE]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PE],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[PPX]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PPX],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[RENT]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENT],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[RENTP]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENTP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SBF]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SBF],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SIC1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SIC1P]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SIC1T]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SPN]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SPN],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SWI5]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SWI5],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SWI5P]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SWI5P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[TEM1GDP]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[TEM1GDP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[TEM1GTP]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[TEM1GTP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[mdt]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mdt],Reference=Value"/>
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
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[D],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[mu]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mu],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vdb5]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb5],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vdb2]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb2],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vasbf]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vasbf],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Visbf]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Visbf],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vkpc1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpc1],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vkpf6]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpf6],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vacdh]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vacdh],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vicdh]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vicdh],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vppnet]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppnet],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vkpnet]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpnet],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vdppx]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdppx],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vdpds]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdpds],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vaiep]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vaiep],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vd2c1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vd2c1],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vd2f6]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vd2f6],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vppc1]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppc1],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vppf6]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppf6],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[F]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[F],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[1stDivisionTime]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[1stDivisionTime],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[T0]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[T0],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Period]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Period],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[GLUconsumed]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[GLUconsumed],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
    <ListOfSliders>
      <Slider key="Slider_0" associatedEntityKey="Task_15" objectCN="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[GLU],Reference=InitialConcentration" objectType="float" objectValue="0.002" minValue="0.0008" maxValue="2e+07" tickNumber="1000" tickFactor="100" scaling="linear"/>
    </ListOfSliders>
  </GUI>
  <SBMLReference file="BIOMD0000000056.xml">
    <SBMLMap SBMLid="Activation_of_CDC20" COPASIkey="Reaction_10"/>
    <SBMLMap SBMLid="Activation_of_IEP" COPASIkey="Reaction_15"/>
    <SBMLMap SBMLid="Activation_of_SWI5" COPASIkey="Reaction_17"/>
    <SBMLMap SBMLid="Assoc_of_CLB2_and_SIC1" COPASIkey="Reaction_52"/>
    <SBMLMap SBMLid="Assoc_of_CLB5_and_SIC1" COPASIkey="Reaction_50"/>
    <SBMLMap SBMLid="Assoc_with_ESP1_to_form_PE" COPASIkey="Reaction_110"/>
    <SBMLMap SBMLid="Assoc_with_NET1P_to_form_RENTP" COPASIkey="Reaction_88"/>
    <SBMLMap SBMLid="Assoc_with_NET1_to_form_RENT" COPASIkey="Reaction_1"/>
    <SBMLMap SBMLid="BCK2" COPASIkey="Metabolite_49"/>
    <SBMLMap SBMLid="BUB2" COPASIkey="Metabolite_45"/>
    <SBMLMap SBMLid="BUD" COPASIkey="Metabolite_41"/>
    <SBMLMap SBMLid="Budding" COPASIkey="Reaction_114"/>
    <SBMLMap SBMLid="C0" COPASIkey="ModelValue_12"/>
    <SBMLMap SBMLid="C2" COPASIkey="Metabolite_37"/>
    <SBMLMap SBMLid="C2P" COPASIkey="Metabolite_33"/>
    <SBMLMap SBMLid="C5" COPASIkey="Metabolite_29"/>
    <SBMLMap SBMLid="C5P" COPASIkey="Metabolite_25"/>
    <SBMLMap SBMLid="CDC14" COPASIkey="Metabolite_21"/>
    <SBMLMap SBMLid="CDC14T" COPASIkey="Metabolite_17"/>
    <SBMLMap SBMLid="CDC14_degradation" COPASIkey="Reaction_2"/>
    <SBMLMap SBMLid="CDC14_synthesis" COPASIkey="Reaction_3"/>
    <SBMLMap SBMLid="CDC15" COPASIkey="Metabolite_13"/>
    <SBMLMap SBMLid="CDC15T" COPASIkey="ModelValue_13"/>
    <SBMLMap SBMLid="CDC15_activation" COPASIkey="Reaction_103"/>
    <SBMLMap SBMLid="CDC15i" COPASIkey="Metabolite_9"/>
    <SBMLMap SBMLid="CDC20" COPASIkey="Metabolite_5"/>
    <SBMLMap SBMLid="CDC20i" COPASIkey="Metabolite_1"/>
    <SBMLMap SBMLid="CDC6" COPASIkey="Metabolite_77"/>
    <SBMLMap SBMLid="CDC6P" COPASIkey="Metabolite_79"/>
    <SBMLMap SBMLid="CDC6T" COPASIkey="Metabolite_81"/>
    <SBMLMap SBMLid="CDC6_degradation_in_F2P" COPASIkey="Reaction_24"/>
    <SBMLMap SBMLid="CDC6_degradation_in_F5P" COPASIkey="Reaction_23"/>
    <SBMLMap SBMLid="CDC6_synthesis" COPASIkey="Reaction_38"/>
    <SBMLMap SBMLid="CDH1" COPASIkey="Metabolite_83"/>
    <SBMLMap SBMLid="CDH1_degradation" COPASIkey="Reaction_7"/>
    <SBMLMap SBMLid="CDH1_synthesis" COPASIkey="Reaction_8"/>
    <SBMLMap SBMLid="CDH1i" COPASIkey="Metabolite_85"/>
    <SBMLMap SBMLid="CDH1i_activation" COPASIkey="Reaction_5"/>
    <SBMLMap SBMLid="CDH1i_degradation" COPASIkey="Reaction_6"/>
    <SBMLMap SBMLid="CKIT" COPASIkey="Metabolite_87"/>
    <SBMLMap SBMLid="CLB2" COPASIkey="Metabolite_89"/>
    <SBMLMap SBMLid="CLB2CDC6_complex_formation" COPASIkey="Reaction_34"/>
    <SBMLMap SBMLid="CLB2CDC6_dissociation" COPASIkey="Reaction_33"/>
    <SBMLMap SBMLid="CLB2T" COPASIkey="Metabolite_91"/>
    <SBMLMap SBMLid="CLB2_degradation_in_F2" COPASIkey="Reaction_26"/>
    <SBMLMap SBMLid="CLB2_degradation_in_F2P" COPASIkey="Reaction_22"/>
    <SBMLMap SBMLid="CLB5" COPASIkey="Metabolite_93"/>
    <SBMLMap SBMLid="CLB5CDC6_complex_formation" COPASIkey="Reaction_32"/>
    <SBMLMap SBMLid="CLB5CDC6_dissociation" COPASIkey="Reaction_31"/>
    <SBMLMap SBMLid="CLB5T" COPASIkey="Metabolite_95"/>
    <SBMLMap SBMLid="CLB5_degradation_in_F5" COPASIkey="Reaction_25"/>
    <SBMLMap SBMLid="CLB5_degradation_in_F5P" COPASIkey="Reaction_21"/>
    <SBMLMap SBMLid="CLN2" COPASIkey="Metabolite_97"/>
    <SBMLMap SBMLid="CLN3" COPASIkey="Metabolite_99"/>
    <SBMLMap SBMLid="D" COPASIkey="ModelValue_152"/>
    <SBMLMap SBMLid="DNA_synthesis" COPASIkey="Reaction_112"/>
    <SBMLMap SBMLid="Degradation_of_CDC14_in_RENT" COPASIkey="Reaction_99"/>
    <SBMLMap SBMLid="Degradation_of_CDC14_in_RENTP" COPASIkey="Reaction_100"/>
    <SBMLMap SBMLid="Degradation_of_CDC6P" COPASIkey="Reaction_35"/>
    <SBMLMap SBMLid="Degradation_of_CLB2" COPASIkey="Reaction_59"/>
    <SBMLMap SBMLid="Degradation_of_CLB2_in_C2" COPASIkey="Reaction_44"/>
    <SBMLMap SBMLid="Degradation_of_CLB2_in_C2P" COPASIkey="Reaction_40"/>
    <SBMLMap SBMLid="Degradation_of_CLB5" COPASIkey="Reaction_57"/>
    <SBMLMap SBMLid="Degradation_of_CLB5_in_C5" COPASIkey="Reaction_43"/>
    <SBMLMap SBMLid="Degradation_of_CLB5_in_C5P" COPASIkey="Reaction_39"/>
    <SBMLMap SBMLid="Degradation_of_CLN2" COPASIkey="Reaction_61"/>
    <SBMLMap SBMLid="Degradation_of_NET1P_in_RENTP" COPASIkey="Reaction_98"/>
    <SBMLMap SBMLid="Degradation_of_NET1_in_RENT" COPASIkey="Reaction_97"/>
    <SBMLMap SBMLid="Degradation_of_PDS1_in_PE" COPASIkey="Reaction_109"/>
    <SBMLMap SBMLid="Degradation_of_SIC1P_in_C5P_" COPASIkey="Reaction_41"/>
    <SBMLMap SBMLid="Degradation_of_SIC1_in_C2P" COPASIkey="Reaction_42"/>
    <SBMLMap SBMLid="Degradation_of_SWI5" COPASIkey="Reaction_19"/>
    <SBMLMap SBMLid="Degradation_of_SWI5P" COPASIkey="Reaction_18"/>
    <SBMLMap SBMLid="Degradation_of_active_CDC20" COPASIkey="Reaction_11"/>
    <SBMLMap SBMLid="Degradation_of_inactiveCDC20" COPASIkey="Reaction_12"/>
    <SBMLMap SBMLid="Dephosphorylation_of_C2P" COPASIkey="Reaction_47"/>
    <SBMLMap SBMLid="Dephosphorylation_of_C5P" COPASIkey="Reaction_45"/>
    <SBMLMap SBMLid="Dephosphorylation_of_CDC6" COPASIkey="Reaction_36"/>
    <SBMLMap SBMLid="Dephosphorylation_of_SIC1" COPASIkey="Reaction_54"/>
    <SBMLMap SBMLid="Disso_from_PE" COPASIkey="Reaction_111"/>
    <SBMLMap SBMLid="Dissoc_from_RENP" COPASIkey="Reaction_89"/>
    <SBMLMap SBMLid="Dissoc_from_RENT" COPASIkey="Reaction_0"/>
    <SBMLMap SBMLid="Dissoc_of_CLB2SIC1_complex" COPASIkey="Reaction_51"/>
    <SBMLMap SBMLid="Dissoc_of_CLB5SIC1" COPASIkey="Reaction_49"/>
    <SBMLMap SBMLid="Dn3" COPASIkey="ModelValue_14"/>
    <SBMLMap SBMLid="ESP1" COPASIkey="Metabolite_101"/>
    <SBMLMap SBMLid="ESP1T" COPASIkey="ModelValue_37"/>
    <SBMLMap SBMLid="F" COPASIkey="ModelValue_171"/>
    <SBMLMap SBMLid="F2" COPASIkey="Metabolite_103"/>
    <SBMLMap SBMLid="F2P" COPASIkey="Metabolite_105"/>
    <SBMLMap SBMLid="F2P_dephosphorylation" COPASIkey="Reaction_29"/>
    <SBMLMap SBMLid="F2_phosphorylation" COPASIkey="Reaction_30"/>
    <SBMLMap SBMLid="F5" COPASIkey="Metabolite_107"/>
    <SBMLMap SBMLid="F5P" COPASIkey="Metabolite_109"/>
    <SBMLMap SBMLid="F5P_dephosphorylation" COPASIkey="Reaction_27"/>
    <SBMLMap SBMLid="F5_phosphorylation" COPASIkey="Reaction_28"/>
    <SBMLMap SBMLid="Fast_Degradation_of_SIC1P" COPASIkey="Reaction_53"/>
    <SBMLMap SBMLid="GK_219" COPASIkey="Function_44"/>
    <SBMLMap SBMLid="Growth" COPASIkey="Reaction_63"/>
    <SBMLMap SBMLid="IE" COPASIkey="Metabolite_111"/>
    <SBMLMap SBMLid="IEP" COPASIkey="Metabolite_113"/>
    <SBMLMap SBMLid="IET" COPASIkey="ModelValue_38"/>
    <SBMLMap SBMLid="Inactivation_1" COPASIkey="Reaction_14"/>
    <SBMLMap SBMLid="Inactivation_2" COPASIkey="Reaction_9"/>
    <SBMLMap SBMLid="Inactivation_3" COPASIkey="Reaction_4"/>
    <SBMLMap SBMLid="Inactivation_of_SWI5" COPASIkey="Reaction_16"/>
    <SBMLMap SBMLid="J20ppx" COPASIkey="ModelValue_39"/>
    <SBMLMap SBMLid="Jacdh" COPASIkey="ModelValue_40"/>
    <SBMLMap SBMLid="Jaiep" COPASIkey="ModelValue_41"/>
    <SBMLMap SBMLid="Jamcm" COPASIkey="ModelValue_42"/>
    <SBMLMap SBMLid="Jasbf" COPASIkey="ModelValue_43"/>
    <SBMLMap SBMLid="Jatem" COPASIkey="ModelValue_44"/>
    <SBMLMap SBMLid="Jd2c1" COPASIkey="ModelValue_45"/>
    <SBMLMap SBMLid="Jd2f6" COPASIkey="ModelValue_46"/>
    <SBMLMap SBMLid="Jicdh" COPASIkey="ModelValue_47"/>
    <SBMLMap SBMLid="Jiiep" COPASIkey="ModelValue_48"/>
    <SBMLMap SBMLid="Jimcm" COPASIkey="ModelValue_49"/>
    <SBMLMap SBMLid="Jisbf" COPASIkey="ModelValue_50"/>
    <SBMLMap SBMLid="Jitem" COPASIkey="ModelValue_51"/>
    <SBMLMap SBMLid="Jn3" COPASIkey="ModelValue_52"/>
    <SBMLMap SBMLid="Jpds" COPASIkey="ModelValue_53"/>
    <SBMLMap SBMLid="Jspn" COPASIkey="ModelValue_54"/>
    <SBMLMap SBMLid="KEZ" COPASIkey="ModelValue_105"/>
    <SBMLMap SBMLid="KEZ2" COPASIkey="ModelValue_106"/>
    <SBMLMap SBMLid="LTE1" COPASIkey="Metabolite_115"/>
    <SBMLMap SBMLid="MAD2" COPASIkey="Metabolite_117"/>
    <SBMLMap SBMLid="MASS" COPASIkey="Metabolite_119"/>
    <SBMLMap SBMLid="MCM1" COPASIkey="Metabolite_121"/>
    <SBMLMap SBMLid="Mass_Action_1_222" COPASIkey="Function_45"/>
    <SBMLMap SBMLid="Mass_Action_2_221" COPASIkey="Function_46"/>
    <SBMLMap SBMLid="MichaelisMenten_220" COPASIkey="Function_47"/>
    <SBMLMap SBMLid="NET1" COPASIkey="Metabolite_123"/>
    <SBMLMap SBMLid="NET1P" COPASIkey="Metabolite_125"/>
    <SBMLMap SBMLid="NET1T" COPASIkey="Metabolite_127"/>
    <SBMLMap SBMLid="NET1_phosphorylation" COPASIkey="Reaction_93"/>
    <SBMLMap SBMLid="Negative_regulation_of_Cell_budding" COPASIkey="Reaction_115"/>
    <SBMLMap SBMLid="Negative_regulation_of_DNA_synthesis" COPASIkey="Reaction_113"/>
    <SBMLMap SBMLid="Net1P_degradation" COPASIkey="Reaction_92"/>
    <SBMLMap SBMLid="Net1_degradation" COPASIkey="Reaction_91"/>
    <SBMLMap SBMLid="Net1_synthesis" COPASIkey="Reaction_90"/>
    <SBMLMap SBMLid="ORI" COPASIkey="Metabolite_129"/>
    <SBMLMap SBMLid="PDS1" COPASIkey="Metabolite_131"/>
    <SBMLMap SBMLid="PDS1_synthesis" COPASIkey="Reaction_107"/>
    <SBMLMap SBMLid="PE" COPASIkey="Metabolite_133"/>
    <SBMLMap SBMLid="PPX" COPASIkey="Metabolite_135"/>
    <SBMLMap SBMLid="PPX_synthesis" COPASIkey="Reaction_105"/>
    <SBMLMap SBMLid="Phosphorylation_of_C2" COPASIkey="Reaction_48"/>
    <SBMLMap SBMLid="Phosphorylation_of_C5" COPASIkey="Reaction_46"/>
    <SBMLMap SBMLid="Phosphorylation_of_CDC6" COPASIkey="Reaction_37"/>
    <SBMLMap SBMLid="Phosphorylation_of_SIC1" COPASIkey="Reaction_55"/>
    <SBMLMap SBMLid="RENT" COPASIkey="Metabolite_137"/>
    <SBMLMap SBMLid="RENTP" COPASIkey="Metabolite_139"/>
    <SBMLMap SBMLid="RENT_phosphorylation" COPASIkey="Reaction_95"/>
    <SBMLMap SBMLid="SBF" COPASIkey="Metabolite_141"/>
    <SBMLMap SBMLid="SIC1" COPASIkey="Metabolite_143"/>
    <SBMLMap SBMLid="SIC1P" COPASIkey="Metabolite_145"/>
    <SBMLMap SBMLid="SIC1T" COPASIkey="Metabolite_147"/>
    <SBMLMap SBMLid="SPN" COPASIkey="Metabolite_149"/>
    <SBMLMap SBMLid="SWI5" COPASIkey="Metabolite_151"/>
    <SBMLMap SBMLid="SWI5P" COPASIkey="Metabolite_153"/>
    <SBMLMap SBMLid="Spindle_disassembly" COPASIkey="Reaction_117"/>
    <SBMLMap SBMLid="Spindle_formation" COPASIkey="Reaction_116"/>
    <SBMLMap SBMLid="Synthesis_of_CLB2" COPASIkey="Reaction_60"/>
    <SBMLMap SBMLid="Synthesis_of_CLB5" COPASIkey="Reaction_58"/>
    <SBMLMap SBMLid="Synthesis_of_CLN2" COPASIkey="Reaction_62"/>
    <SBMLMap SBMLid="Synthesis_of_SIC1" COPASIkey="Reaction_56"/>
    <SBMLMap SBMLid="Synthesis_of_SWI5" COPASIkey="Reaction_20"/>
    <SBMLMap SBMLid="Synthesis_of_inactive_CDC20" COPASIkey="Reaction_13"/>
    <SBMLMap SBMLid="TEM1GDP" COPASIkey="Metabolite_155"/>
    <SBMLMap SBMLid="TEM1GTP" COPASIkey="Metabolite_157"/>
    <SBMLMap SBMLid="TEM1T" COPASIkey="ModelValue_151"/>
    <SBMLMap SBMLid="TEM1_activation" COPASIkey="Reaction_101"/>
    <SBMLMap SBMLid="Vacdh" COPASIkey="ModelValue_160"/>
    <SBMLMap SBMLid="Vaiep" COPASIkey="ModelValue_166"/>
    <SBMLMap SBMLid="Vasbf" COPASIkey="ModelValue_156"/>
    <SBMLMap SBMLid="Vd2c1" COPASIkey="ModelValue_167"/>
    <SBMLMap SBMLid="Vd2f6" COPASIkey="ModelValue_168"/>
    <SBMLMap SBMLid="Vdb2" COPASIkey="ModelValue_155"/>
    <SBMLMap SBMLid="Vdb5" COPASIkey="ModelValue_154"/>
    <SBMLMap SBMLid="Vdpds" COPASIkey="ModelValue_165"/>
    <SBMLMap SBMLid="Vdppx" COPASIkey="ModelValue_164"/>
    <SBMLMap SBMLid="Vicdh" COPASIkey="ModelValue_161"/>
    <SBMLMap SBMLid="Visbf" COPASIkey="ModelValue_157"/>
    <SBMLMap SBMLid="Vkpc1" COPASIkey="ModelValue_158"/>
    <SBMLMap SBMLid="Vkpf6" COPASIkey="ModelValue_159"/>
    <SBMLMap SBMLid="Vkpnet" COPASIkey="ModelValue_163"/>
    <SBMLMap SBMLid="Vppc1" COPASIkey="ModelValue_169"/>
    <SBMLMap SBMLid="Vppf6" COPASIkey="ModelValue_170"/>
    <SBMLMap SBMLid="Vppnet" COPASIkey="ModelValue_162"/>
    <SBMLMap SBMLid="b0" COPASIkey="ModelValue_6"/>
    <SBMLMap SBMLid="bub2h" COPASIkey="ModelValue_5"/>
    <SBMLMap SBMLid="bub2l" COPASIkey="ModelValue_11"/>
    <SBMLMap SBMLid="cell" COPASIkey="Compartment_3"/>
    <SBMLMap SBMLid="degradation_1" COPASIkey="Reaction_106"/>
    <SBMLMap SBMLid="degradation_2" COPASIkey="Reaction_108"/>
    <SBMLMap SBMLid="dephosphorylation_1" COPASIkey="Reaction_94"/>
    <SBMLMap SBMLid="dephosphorylation_2" COPASIkey="Reaction_96"/>
    <SBMLMap SBMLid="ebudb5" COPASIkey="ModelValue_15"/>
    <SBMLMap SBMLid="ebudn2" COPASIkey="ModelValue_16"/>
    <SBMLMap SBMLid="ebudn3" COPASIkey="ModelValue_17"/>
    <SBMLMap SBMLid="ec1b2" COPASIkey="ModelValue_18"/>
    <SBMLMap SBMLid="ec1b5" COPASIkey="ModelValue_19"/>
    <SBMLMap SBMLid="ec1k2" COPASIkey="ModelValue_20"/>
    <SBMLMap SBMLid="ec1n2" COPASIkey="ModelValue_21"/>
    <SBMLMap SBMLid="ec1n3" COPASIkey="ModelValue_22"/>
    <SBMLMap SBMLid="ef6b2" COPASIkey="ModelValue_23"/>
    <SBMLMap SBMLid="ef6b5" COPASIkey="ModelValue_24"/>
    <SBMLMap SBMLid="ef6k2" COPASIkey="ModelValue_25"/>
    <SBMLMap SBMLid="ef6n2" COPASIkey="ModelValue_26"/>
    <SBMLMap SBMLid="ef6n3" COPASIkey="ModelValue_27"/>
    <SBMLMap SBMLid="eicdhb2" COPASIkey="ModelValue_28"/>
    <SBMLMap SBMLid="eicdhb5" COPASIkey="ModelValue_29"/>
    <SBMLMap SBMLid="eicdhn2" COPASIkey="ModelValue_30"/>
    <SBMLMap SBMLid="eicdhn3" COPASIkey="ModelValue_31"/>
    <SBMLMap SBMLid="eorib2" COPASIkey="ModelValue_32"/>
    <SBMLMap SBMLid="eorib5" COPASIkey="ModelValue_33"/>
    <SBMLMap SBMLid="esbfb5" COPASIkey="ModelValue_34"/>
    <SBMLMap SBMLid="esbfn2" COPASIkey="ModelValue_35"/>
    <SBMLMap SBMLid="esbfn3" COPASIkey="ModelValue_36"/>
    <SBMLMap SBMLid="inactivation_1" COPASIkey="Reaction_102"/>
    <SBMLMap SBMLid="inactivation_2" COPASIkey="Reaction_104"/>
    <SBMLMap SBMLid="ka15_p" COPASIkey="ModelValue_55"/>
    <SBMLMap SBMLid="ka15_p_p" COPASIkey="ModelValue_56"/>
    <SBMLMap SBMLid="ka15p" COPASIkey="ModelValue_57"/>
    <SBMLMap SBMLid="ka20_p" COPASIkey="ModelValue_58"/>
    <SBMLMap SBMLid="ka20_p_p" COPASIkey="ModelValue_59"/>
    <SBMLMap SBMLid="kacdh_p" COPASIkey="ModelValue_60"/>
    <SBMLMap SBMLid="kacdh_p_p" COPASIkey="ModelValue_61"/>
    <SBMLMap SBMLid="kaiep" COPASIkey="ModelValue_62"/>
    <SBMLMap SBMLid="kamcm" COPASIkey="ModelValue_63"/>
    <SBMLMap SBMLid="kasb2" COPASIkey="ModelValue_64"/>
    <SBMLMap SBMLid="kasb5" COPASIkey="ModelValue_65"/>
    <SBMLMap SBMLid="kasbf" COPASIkey="ModelValue_66"/>
    <SBMLMap SBMLid="kasesp" COPASIkey="ModelValue_67"/>
    <SBMLMap SBMLid="kasf2" COPASIkey="ModelValue_68"/>
    <SBMLMap SBMLid="kasf5" COPASIkey="ModelValue_69"/>
    <SBMLMap SBMLid="kasrent" COPASIkey="ModelValue_70"/>
    <SBMLMap SBMLid="kasrentp" COPASIkey="ModelValue_71"/>
    <SBMLMap SBMLid="kaswi" COPASIkey="ModelValue_72"/>
    <SBMLMap SBMLid="kd14" COPASIkey="ModelValue_73"/>
    <SBMLMap SBMLid="kd1c1" COPASIkey="ModelValue_74"/>
    <SBMLMap SBMLid="kd1f6" COPASIkey="ModelValue_75"/>
    <SBMLMap SBMLid="kd1pds_p" COPASIkey="ModelValue_76"/>
    <SBMLMap SBMLid="kd20" COPASIkey="ModelValue_77"/>
    <SBMLMap SBMLid="kd2c1" COPASIkey="ModelValue_78"/>
    <SBMLMap SBMLid="kd2f6" COPASIkey="ModelValue_79"/>
    <SBMLMap SBMLid="kd2pds_p_p" COPASIkey="ModelValue_80"/>
    <SBMLMap SBMLid="kd3c1" COPASIkey="ModelValue_81"/>
    <SBMLMap SBMLid="kd3f6" COPASIkey="ModelValue_82"/>
    <SBMLMap SBMLid="kd3pds_p_p" COPASIkey="ModelValue_83"/>
    <SBMLMap SBMLid="kdb2_p" COPASIkey="ModelValue_84"/>
    <SBMLMap SBMLid="kdb2_p_p" COPASIkey="ModelValue_85"/>
    <SBMLMap SBMLid="kdb2p" COPASIkey="ModelValue_86"/>
    <SBMLMap SBMLid="kdb5_p" COPASIkey="ModelValue_87"/>
    <SBMLMap SBMLid="kdb5_p_p" COPASIkey="ModelValue_88"/>
    <SBMLMap SBMLid="kdbud" COPASIkey="ModelValue_89"/>
    <SBMLMap SBMLid="kdcdh" COPASIkey="ModelValue_90"/>
    <SBMLMap SBMLid="kdib2" COPASIkey="ModelValue_91"/>
    <SBMLMap SBMLid="kdib5" COPASIkey="ModelValue_92"/>
    <SBMLMap SBMLid="kdiesp" COPASIkey="ModelValue_93"/>
    <SBMLMap SBMLid="kdif2" COPASIkey="ModelValue_94"/>
    <SBMLMap SBMLid="kdif5" COPASIkey="ModelValue_95"/>
    <SBMLMap SBMLid="kdirent" COPASIkey="ModelValue_96"/>
    <SBMLMap SBMLid="kdirentp" COPASIkey="ModelValue_97"/>
    <SBMLMap SBMLid="kdn2" COPASIkey="ModelValue_98"/>
    <SBMLMap SBMLid="kdnet" COPASIkey="ModelValue_99"/>
    <SBMLMap SBMLid="kdori" COPASIkey="ModelValue_100"/>
    <SBMLMap SBMLid="kdppx_p" COPASIkey="ModelValue_101"/>
    <SBMLMap SBMLid="kdppx_p_p" COPASIkey="ModelValue_102"/>
    <SBMLMap SBMLid="kdspn" COPASIkey="ModelValue_103"/>
    <SBMLMap SBMLid="kdswi" COPASIkey="ModelValue_104"/>
    <SBMLMap SBMLid="ki15" COPASIkey="ModelValue_107"/>
    <SBMLMap SBMLid="kicdh_p" COPASIkey="ModelValue_108"/>
    <SBMLMap SBMLid="kicdh_p_p" COPASIkey="ModelValue_109"/>
    <SBMLMap SBMLid="kiiep" COPASIkey="ModelValue_110"/>
    <SBMLMap SBMLid="kimcm" COPASIkey="ModelValue_111"/>
    <SBMLMap SBMLid="kisbf_p" COPASIkey="ModelValue_112"/>
    <SBMLMap SBMLid="kisbf_p_p" COPASIkey="ModelValue_113"/>
    <SBMLMap SBMLid="kiswi" COPASIkey="ModelValue_114"/>
    <SBMLMap SBMLid="kkpnet_p" COPASIkey="ModelValue_115"/>
    <SBMLMap SBMLid="kkpnet_p_p" COPASIkey="ModelValue_116"/>
    <SBMLMap SBMLid="kppc1" COPASIkey="ModelValue_117"/>
    <SBMLMap SBMLid="kppf6" COPASIkey="ModelValue_118"/>
    <SBMLMap SBMLid="kppnet_p" COPASIkey="ModelValue_119"/>
    <SBMLMap SBMLid="kppnet_p_p" COPASIkey="ModelValue_120"/>
    <SBMLMap SBMLid="ks14" COPASIkey="ModelValue_121"/>
    <SBMLMap SBMLid="ks1pds_p_p" COPASIkey="ModelValue_122"/>
    <SBMLMap SBMLid="ks20_p" COPASIkey="ModelValue_123"/>
    <SBMLMap SBMLid="ks20_p_p" COPASIkey="ModelValue_124"/>
    <SBMLMap SBMLid="ks2pds_p_p" COPASIkey="ModelValue_125"/>
    <SBMLMap SBMLid="ksb2_p" COPASIkey="ModelValue_126"/>
    <SBMLMap SBMLid="ksb2_p_p" COPASIkey="ModelValue_127"/>
    <SBMLMap SBMLid="ksb5_p" COPASIkey="ModelValue_128"/>
    <SBMLMap SBMLid="ksb5_p_p" COPASIkey="ModelValue_129"/>
    <SBMLMap SBMLid="ksbud" COPASIkey="ModelValue_130"/>
    <SBMLMap SBMLid="ksc1_p" COPASIkey="ModelValue_131"/>
    <SBMLMap SBMLid="ksc1_p_p" COPASIkey="ModelValue_132"/>
    <SBMLMap SBMLid="kscdh" COPASIkey="ModelValue_133"/>
    <SBMLMap SBMLid="ksf6_p" COPASIkey="ModelValue_134"/>
    <SBMLMap SBMLid="ksf6_p_p" COPASIkey="ModelValue_135"/>
    <SBMLMap SBMLid="ksf6_p_p_p" COPASIkey="ModelValue_136"/>
    <SBMLMap SBMLid="ksn2_p" COPASIkey="ModelValue_137"/>
    <SBMLMap SBMLid="ksn2_p_p" COPASIkey="ModelValue_138"/>
    <SBMLMap SBMLid="ksnet" COPASIkey="ModelValue_139"/>
    <SBMLMap SBMLid="ksori" COPASIkey="ModelValue_140"/>
    <SBMLMap SBMLid="kspds_p" COPASIkey="ModelValue_141"/>
    <SBMLMap SBMLid="ksppx" COPASIkey="ModelValue_142"/>
    <SBMLMap SBMLid="ksspn" COPASIkey="ModelValue_143"/>
    <SBMLMap SBMLid="ksswi_p" COPASIkey="ModelValue_144"/>
    <SBMLMap SBMLid="ksswi_p_p" COPASIkey="ModelValue_145"/>
    <SBMLMap SBMLid="lte1h" COPASIkey="ModelValue_146"/>
    <SBMLMap SBMLid="lte1l" COPASIkey="ModelValue_147"/>
    <SBMLMap SBMLid="mad2h" COPASIkey="ModelValue_148"/>
    <SBMLMap SBMLid="mad2l" COPASIkey="ModelValue_149"/>
    <SBMLMap SBMLid="mdt" COPASIkey="ModelValue_150"/>
    <SBMLMap SBMLid="mu" COPASIkey="ModelValue_153"/>
    <SBMLMap SBMLid="parameter_1" COPASIkey="ModelValue_172"/>
  </SBMLReference>
</COPASI>
