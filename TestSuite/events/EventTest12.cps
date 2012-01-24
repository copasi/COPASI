<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.8 (Build 35) (http://www.copasi.org) at 2012-01-24 14:17:22 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="1" versionMinor="0" versionDevel="35">
  <ListOfFunctions>
    <Function key="Function_77" name="GK" type="UserDefined" reversible="unspecified">
      <Expression>
        2*A4*A1/(A2-A1+A3*A2+A4*A1+((A2-A1+A3*A2+A4*A1)^2-4*(A2-A1)*A4*A1)^(1/2))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_445" name="A1" order="0" role="variable"/>
        <ParameterDescription key="FunctionParameter_370" name="A2" order="1" role="variable"/>
        <ParameterDescription key="FunctionParameter_368" name="A3" order="2" role="variable"/>
        <ParameterDescription key="FunctionParameter_443" name="A4" order="3" role="variable"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_76" name="Mass_Action_1" type="UserDefined" reversible="unspecified">
      <Expression>
        k1*S1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_367" name="k1" order="0" role="variable"/>
        <ParameterDescription key="FunctionParameter_446" name="S1" order="1" role="variable"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_78" name="Mass_Action_2" type="UserDefined" reversible="unspecified">
      <Expression>
        k1*S1*S2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_444" name="k1" order="0" role="variable"/>
        <ParameterDescription key="FunctionParameter_366" name="S1" order="1" role="variable"/>
        <ParameterDescription key="FunctionParameter_364" name="S2" order="2" role="variable"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_80" name="Michaelis-Menten" type="UserDefined" reversible="unspecified">
      <Expression>
        k1*S1*M1/(J1+S1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_361" name="M1" order="0" role="variable"/>
        <ParameterDescription key="FunctionParameter_359" name="J1" order="1" role="variable"/>
        <ParameterDescription key="FunctionParameter_363" name="k1" order="2" role="variable"/>
        <ParameterDescription key="FunctionParameter_369" name="S1" order="3" role="variable"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_79" name="function_4_Synthesis of CLN2" type="UserDefined" reversible="false">
      <Expression>
        (ksn2_p+ksn2_p_p*(SBF*cell))*MASS
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_353" name="MASS" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_357" name="SBF" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_355" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_358" name="ksn2_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_362" name="ksn2_p_p" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_81" name="function_4_Degradation of CLN2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdn2,CLN2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_356" name="CLN2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_360" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_352" name="kdn2" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_72" name="function_4_Synthesis of CLB2" type="UserDefined" reversible="false">
      <Expression>
        (ksb2_p+ksb2_p_p*(MCM1*cell))*MASS
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_345" name="MASS" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_349" name="MCM1" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_347" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_351" name="ksb2_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_354" name="ksb2_p_p" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_71" name="function_4_Degradation of CLB2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,CLB2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_348" name="CLB2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_344" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_365" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_75" name="function_4_Synthesis of CLB5" type="UserDefined" reversible="false">
      <Expression>
        (ksb5_p+ksb5_p_p*(SBF*cell))*MASS
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_337" name="MASS" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_341" name="SBF" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_339" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_343" name="ksb5_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_346" name="ksb5_p_p" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_74" name="function_4_Degradation of CLB5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,CLB5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_340" name="CLB5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_336" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_350" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_73" name="function_4_Synthesis of SIC1" type="UserDefined" reversible="false">
      <Expression>
        (ksc1_p+ksc1_p_p*(SWI5*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_333" name="SWI5" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_331" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_335" name="ksc1_p" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_338" name="ksc1_p_p" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_93" name="function_4_Phosphorylation of SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpc1,SIC1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_334" name="SIC1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_330" name="Vkpc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_329" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_92" name="function_4_Dephosphorylation of SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppc1,SIC1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_332" name="SIC1P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_328" name="Vppc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_326" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_94" name="function_4_Fast Degradation of SIC1P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3c1,SIC1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_342" name="SIC1P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_323" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_325" name="kd3c1" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_95" name="function_4_Assoc. of CLB2 and SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasb2,CLB2*cell,SIC1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_327" name="CLB2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_318" name="SIC1" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_320" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_322" name="kasb2" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_96" name="function_4_Dissoc. of CLB2/SIC1 complex" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdib2,C2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_321" name="C2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_316" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_317" name="kdib2" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_97" name="function_4_Assoc. of CLB5 and SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasb5,CLB5*cell,SIC1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_319" name="CLB5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_311" name="SIC1" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_313" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_315" name="kasb5" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_98" name="function_4_Dissoc. of CLB5/SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdib5,C5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_314" name="C5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_309" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_310" name="kdib5" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_99" name="function_4_Phosphorylation of C2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpc1,C2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_312" name="C2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_308" name="Vkpc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_306" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_100" name="function_4_Dephosphorylation of C2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppc1,C2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_324" name="C2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_305" name="Vppc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_303" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_101" name="function_4_Phosphorylation of C5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpc1,C5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_307" name="C5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_302" name="Vkpc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_300" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_102" name="function_4_Dephosphorylation of C5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppc1,C5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_304" name="C5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_299" name="Vppc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_285" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_103" name="function_4_Degradation of CLB2 in C2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,C2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_301" name="C2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_281" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_275" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_104" name="function_4_Degradation of CLB5 in C5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,C5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_298" name="C5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_289" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_293" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_105" name="function_4_Degradation of SIC1 in C2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3c1,C2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_269" name="C2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_440" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_295" name="kd3c1" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_106" name="function_4_Degradation of SIC1P in C5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3c1,C5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_291" name="C5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_447" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_439" name="kd3c1" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_107" name="function_4_Degradation of CLB2 in C2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,C2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_297" name="C2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_448" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_450" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_108" name="function_4_Degradation of CLB5 in C5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,C5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_438" name="C5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_451" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_453" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_109" name="function_4_CDC6 synthesis" type="UserDefined" reversible="false">
      <Expression>
        (ksf6_p+ksf6_p_p*(SWI5*cell)+ksf6_p_p_p*(SBF*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_462" name="SBF" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_456" name="SWI5" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_458" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_454" name="ksf6_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_449" name="ksf6_p_p" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_460" name="ksf6_p_p_p" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_110" name="function_4_Phosphorylation of CDC6" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpf6,CDC6*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_459" name="CDC6" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_463" name="Vkpf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_455" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_111" name="function_4_Dephosphorylation of CDC6" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppf6,CDC6P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_461" name="CDC6P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_452" name="Vppf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_465" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_112" name="function_4_Degradation of CDC6P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3f6,CDC6P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_457" name="CDC6P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_468" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_466" name="kd3f6" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_113" name="function_4_CLB2/CDC6 complex formation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasf2,CLB2*cell,CDC6*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_473" name="CDC6" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_464" name="CLB2" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_471" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_469" name="kasf2" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_114" name="function_4_CLB2/CDC6 dissociation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdif2,F2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_470" name="F2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_475" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_474" name="kdif2" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_115" name="function_4_CLB5/CDC6 complex formation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasf5,CLB5*cell,CDC6*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_480" name="CDC6" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_472" name="CLB5" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_478" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_476" name="kasf5" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_116" name="function_4_CLB5/CDC6 dissociation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdif5,F5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_477" name="F5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_482" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_481" name="kdif5" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_117" name="function_4_F2 phosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpf6,F2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_479" name="F2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_483" name="Vkpf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_485" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_118" name="function_4_F2P dephosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppf6,F2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_467" name="F2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_486" name="Vppf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_488" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_119" name="function_4_F5 phosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpf6,F5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_484" name="F5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_489" name="Vkpf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_491" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_120" name="function_4_F5P dephosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppf6,F5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_487" name="F5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_492" name="Vppf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_494" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_121" name="function_4_CLB2 degradation in F2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,F2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_490" name="F2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_495" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_497" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_122" name="function_4_CLB5 degradation in F5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,F5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_493" name="F5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_498" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_500" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_123" name="function_4_CDC6 degradation in F2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3f6,F2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_496" name="F2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_503" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_501" name="kd3f6" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_124" name="function_4_CDC6 degradation in F5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3f6,F5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_499" name="F5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_506" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_504" name="kd3f6" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_125" name="function_4_CLB2 degradation in F2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,F2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_502" name="F2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_507" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_509" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_126" name="function_4_CLB5 degradation in F5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,F5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_505" name="F5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_510" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_512" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_127" name="function_4_Synthesis of SWI5" type="UserDefined" reversible="false">
      <Expression>
        (ksswi_p+ksswi_p_p*(MCM1*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_515" name="MCM1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_517" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_513" name="ksswi_p" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_508" name="ksswi_p_p" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_128" name="function_4_Degradation of SWI5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdswi,SWI5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_514" name="SWI5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_519" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_518" name="kdswi" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_129" name="function_4_Degradation of SWI5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdswi,SWI5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_516" name="SWI5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_522" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_520" name="kdswi" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_130" name="function_4_Activation of SWI5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kaswi*(CDC14*cell),SWI5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_511" name="CDC14" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_527" name="SWI5P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_525" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_523" name="kaswi" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_131" name="function_4_Inactivation of SWI5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kiswi*(CLB2*cell),SWI5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_524" name="CLB2" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_531" name="SWI5" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_529" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_528" name="kiswi" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_132" name="function_4_Activation of IEP" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(Vaiep,Jaiep,1,IE*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_533" name="IE" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_521" name="Jaiep" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_532" name="Vaiep" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_535" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_133" name="function_4_Inactivation" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(1,Jiiep,kiiep,IEP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_537" name="IEP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_536" name="Jiiep" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_539" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_526" name="kiiep" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_134" name="function_4_Synthesis of inactive CDC20" type="UserDefined" reversible="false">
      <Expression>
        (ks20_p+ks20_p_p*(MCM1*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_541" name="MCM1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_543" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_540" name="ks20_p" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_530" name="ks20_p_p" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_135" name="function_4_Degradation of inactiveCDC20" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd20,CDC20i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_534" name="CDC20i" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_545" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_544" name="kd20" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_136" name="function_4_Degradation of active CDC20" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd20,CDC20*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_542" name="CDC20" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_548" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_546" name="kd20" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_137" name="function_4_Activation of CDC20" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(ka20_p+ka20_p_p*(IEP*cell),CDC20i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_555" name="CDC20i" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_551" name="IEP" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_553" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_549" name="ka20_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_538" name="ka20_p_p" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_138" name="function_4_Inactivation_2" type="UserDefined" reversible="false">
      <Expression>
        k*Mass_Action_1(MAD2*cell,CDC20*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_558" name="CDC20" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_552" name="MAD2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_547" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_556" name="k" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_139" name="function_4_CDH1 synthesis" type="UserDefined" reversible="false">
      <Expression>
        kscdh/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_550" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_559" name="kscdh" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_140" name="function_4_CDH1 degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdcdh,CDH1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_560" name="CDH1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_562" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_554" name="kdcdh" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_141" name="function_4_CDH1i degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdcdh,CDH1i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_557" name="CDH1i" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_565" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_563" name="kdcdh" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_142" name="function_4_CDH1i activation" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(Vacdh,Jacdh,1,CDH1i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_568" name="CDH1i" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_561" name="Jacdh" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_566" name="Vacdh" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_570" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_143" name="function_4_Inactivation_3" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(Vicdh,Jicdh,1,CDH1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_572" name="CDH1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_567" name="Jicdh" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_571" name="Vicdh" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_574" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_144" name="function_4_CDC14 synthesis" type="UserDefined" reversible="false">
      <Expression>
        ks14/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_564" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_575" name="ks14" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_145" name="function_4_CDC14 degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd14,CDC14*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_576" name="CDC14" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_578" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_569" name="kd14" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_146" name="function_4_Assoc. with NET1 to form RENT" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasrent,CDC14*cell,NET1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_573" name="CDC14" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_583" name="NET1" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_581" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_579" name="kasrent" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_147" name="function_4_Dissoc. from RENT" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdirent,RENT*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_580" name="RENT" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_585" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_584" name="kdirent" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_148" name="function_4_Assoc with NET1P to form RENTP" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasrentp,CDC14*cell,NET1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_582" name="CDC14" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_590" name="NET1P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_588" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_586" name="kasrentp" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_149" name="function_4_Dissoc. from RENP" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdirentp,RENTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_587" name="RENTP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_592" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_591" name="kdirentp" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_150" name="function_4_Net1 synthesis" type="UserDefined" reversible="false">
      <Expression>
        ksnet/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_589" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_593" name="ksnet" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_151" name="function_4_Net1 degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdnet,NET1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_595" name="NET1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_597" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_594" name="kdnet" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_152" name="function_4_Net1P degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdnet,NET1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_577" name="NET1P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_600" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_598" name="kdnet" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_153" name="function_4_NET1 phosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpnet,NET1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_596" name="NET1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_601" name="Vkpnet" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_603" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_154" name="function_4_dephosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppnet,NET1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_599" name="NET1P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_604" name="Vppnet" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_606" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_155" name="function_4_RENT phosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpnet,RENT*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_602" name="RENT" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_607" name="Vkpnet" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_609" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_156" name="function_4_dephosphorylation_2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppnet,RENTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_605" name="RENTP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_610" name="Vppnet" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_612" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_157" name="function_4_Degradation of NET1 in RENT" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdnet,RENT*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_608" name="RENT" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_615" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_613" name="kdnet" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_158" name="function_4_Degradation of NET1P in RENTP" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdnet,RENTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_611" name="RENTP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_618" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_616" name="kdnet" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_159" name="function_4_Degradation of CDC14 in RENT" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd14,RENT*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_614" name="RENT" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_621" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_619" name="kd14" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_160" name="function_4_Degradation of CDC14 in RENTP" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd14,RENTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_617" name="RENTP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_624" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_622" name="kd14" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_161" name="function_4_TEM1 activation" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(LTE1*cell,Jatem,1,TEM1GDP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_627" name="Jatem" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_625" name="LTE1" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_629" name="TEM1GDP" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_620" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_162" name="function_4_inactivation" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(BUB2*cell,Jitem,1,TEM1GTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_630" name="BUB2" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_631" name="Jitem" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_633" name="TEM1GTP" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_626" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_163" name="function_4_CDC15 activation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(ka15_p*(TEM1GDP*cell)+ka15_p_p*(TEM1GTP*cell)+ka15p*(CDC14*cell),CDC15i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_643" name="CDC14" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_645" name="CDC15i" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_623" name="TEM1GDP" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_639" name="TEM1GTP" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_635" name="cell" order="4" role="volume"/>
        <ParameterDescription key="FunctionParameter_634" name="ka15_p" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_637" name="ka15_p_p" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_641" name="ka15p" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_164" name="function_4_inactivation_2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(ki15,CDC15*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_642" name="CDC15" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_638" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_646" name="ki15" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_165" name="function_4_PPX synthesis" type="UserDefined" reversible="false">
      <Expression>
        ksppx/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_644" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_636" name="ksppx" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_166" name="function_4_degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdppx,PPX*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_632" name="PPX" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_628" name="Vdppx" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_648" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_167" name="function_4_PDS1 synthesis" type="UserDefined" reversible="false">
      <Expression>
        (kspds_p+ks1pds_p_p*(SBF*cell)+ks2pds_p_p*(MCM1*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_657" name="MCM1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_651" name="SBF" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_653" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_640" name="ks1pds_p_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_655" name="ks2pds_p_p" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_649" name="kspds_p" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_168" name="function_4_degradation_2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdpds,PDS1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_654" name="PDS1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_658" name="Vdpds" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_650" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_169" name="function_4_Degradation of PDS1 in PE" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdpds,PE*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_656" name="PE" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_647" name="Vdpds" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_660" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_170" name="function_4_Assoc. with ESP1 to form PE" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasesp,PDS1*cell,ESP1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_665" name="ESP1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_652" name="PDS1" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_663" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_661" name="kasesp" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_171" name="function_4_Disso. from PE" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdiesp,PE*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_662" name="PE" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_667" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_666" name="kdiesp" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_172" name="function_4_DNA synthesis" type="UserDefined" reversible="false">
      <Expression>
        ksori*(eorib5*(CLB5*cell)+eorib2*(CLB2*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_676" name="CLB2" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_670" name="CLB5" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_672" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_674" name="eorib2" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_664" name="eorib5" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_668" name="ksori" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_173" name="function_4_Negative regulation of DNA synthesis" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdori,ORI*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_673" name="ORI" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_669" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_677" name="kdori" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_174" name="function_4_Budding" type="UserDefined" reversible="false">
      <Expression>
        ksbud*(ebudn2*(CLN2*cell)+ebudn3*(CLN3*cell)+ebudb5*(CLB5*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_689" name="CLB5" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_679" name="CLN2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_685" name="CLN3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_681" name="cell" order="3" role="volume"/>
        <ParameterDescription key="FunctionParameter_687" name="ebudb5" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_675" name="ebudn2" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_683" name="ebudn3" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_659" name="ksbud" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_175" name="function_4_Negative regulation of Cell budding" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdbud,BUD*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_686" name="BUD" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_682" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_690" name="kdbud" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_176" name="function_4_Spindle formation" type="UserDefined" reversible="false">
      <Expression>
        ksspn*CLB2/(Jspn+CLB2*cell)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_688" name="CLB2" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_671" name="Jspn" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_692" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_680" name="ksspn" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_177" name="function_4_Spindle disassembly" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdspn,SPN*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_678" name="SPN" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_694" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_693" name="kdspn" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_178" name="function_4_Growth-hyperbolic" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_178">
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
        <ParameterDescription key="FunctionParameter_695" name="activator" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_691" name="k" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_697" name="SUB" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_699" name="Kmsub" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_1" name="Chen2004_CellCycle Mother with GLU" simulationType="time" timeUnit="min" volumeUnit="l" areaUnit="m²" lengthUnit="m" quantityUnit="mol" type="deterministic" avogadroConstant="6.02214e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_1">
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
      <Compartment key="Compartment_1" name="cell" simulationType="fixed" dimensionality="3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_1">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0005623" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_69" name="BCK2" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_69">
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
      <Metabolite key="Metabolite_68" name="BUB2" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_68">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P26448" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_67" name="BUD" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_67">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0007114" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_66" name="C2" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_66">
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
      <Metabolite key="Metabolite_65" name="C2P" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_65">
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
      <Metabolite key="Metabolite_64" name="C5" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_64">
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
      <Metabolite key="Metabolite_63" name="C5P" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_63">
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
      <Metabolite key="Metabolite_62" name="CDC14" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_62">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:Q00684" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_61" name="CDC14T" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_61">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:Q00684" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENT],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENTP],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_60" name="CDC15" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_60">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P27636" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_59" name="CDC15i" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_59">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P27636" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[CDC15T],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC15],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_58" name="CDC20" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_58">
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
      <Metabolite key="Metabolite_57" name="CDC20i" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_57">
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
      <Metabolite key="Metabolite_56" name="CDC6" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_56">
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
      <Metabolite key="Metabolite_55" name="CDC6P" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_55">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P09119" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_54" name="CDC6T" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_54">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P09119" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_53" name="CDH1" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_53">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P53197" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_52" name="CDH1i" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_52">
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
      <Metabolite key="Metabolite_51" name="CKIT" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_51">
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
      <Metabolite key="Metabolite_50" name="CLB2" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_50">
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
      <Metabolite key="Metabolite_49" name="CLB2T" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_49">
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
      <Metabolite key="Metabolite_48" name="CLB5" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_48">
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
      <Metabolite key="Metabolite_47" name="CLB5T" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_47">
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
      <Metabolite key="Metabolite_46" name="CLN2" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_46">
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
      <Metabolite key="Metabolite_45" name="CLN3" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_45">
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
      <Metabolite key="Metabolite_44" name="ESP1" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_44">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:Q03018" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_43" name="F2" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_43">
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
      <Metabolite key="Metabolite_42" name="F2P" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_42">
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
      <Metabolite key="Metabolite_41" name="F5" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_41">
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
      <Metabolite key="Metabolite_40" name="F5P" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_40">
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
      <Metabolite key="Metabolite_39" name="IE" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_39">
    <CopasiMT:is rdf:resource="urn:miriam:obo.go:GO%3A0005680" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[IET],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[IEP],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_38" name="IEP" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_38">
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
      <Metabolite key="Metabolite_37" name="LTE1" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_37">
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
      <Metabolite key="Metabolite_36" name="MAD2" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_36">
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
      <Metabolite key="Metabolite_35" name="MASS" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_35">
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
      <Metabolite key="Metabolite_34" name="MCM1" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_34">
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
      <Metabolite key="Metabolite_33" name="NET1" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_33">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P47035" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_32" name="NET1P" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_32">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P47035" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_31" name="NET1T" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_31">
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
      <Metabolite key="Metabolite_30" name="ORI" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_30">
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
      <Metabolite key="Metabolite_29" name="PDS1" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_29">
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
      <Metabolite key="Metabolite_28" name="PE" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_28">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:Q03018" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ESP1T],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ESP1],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_27" name="PPX" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_27">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38698" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_26" name="RENT" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_26">
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
      <Metabolite key="Metabolite_25" name="RENTP" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_25">
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
      <Metabolite key="Metabolite_24" name="SBF" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_24">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P11938" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          GK(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vasbf],Reference=Value&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Visbf],Reference=Value&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jasbf],Reference=Value&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jisbf],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_23" name="SIC1" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_23">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38634" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_22" name="SIC1P" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_22">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38634" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_21" name="SIC1T" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_21">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38634" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_20" name="SPN" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_20">
    <CopasiMT:is rdf:resource="urn:miriam:obo.go:GO%3A0051225" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_19" name="SWI5" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_19">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P08153" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_18" name="SWI5P" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_18">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P08153" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_17" name="TEM1GDP" simulationType="assignment" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_17">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38987" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[TEM1T],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[TEM1GTP],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_12" name="TEM1GTP" simulationType="reactions" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_12">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38987" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_13" name="GLU" simulationType="fixed" compartment="Compartment_1">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_13">
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
      <ModelValue key="ModelValue_189" name="b0" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_189">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_188" name="bub2h" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_188">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_187" name="bub2l" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_187">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_186" name="C0" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_186">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:17:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_185" name="CDC15T" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_185">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:17:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_184" name="Dn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_184">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_183" name="ebudb5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_183">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_182" name="ebudn2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_182">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_181" name="ebudn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_181">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_180" name="ec1b2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_180">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_179" name="ec1b5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_179">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_178" name="ec1k2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_178">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_177" name="ec1n2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_177">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_176" name="ec1n3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_176">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_175" name="ef6b2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_175">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_174" name="ef6b5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_174">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_173" name="ef6k2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_173">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_172" name="ef6n2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_172">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_171" name="ef6n3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_171">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_170" name="eicdhb2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_170">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_169" name="eicdhb5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_169">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_168" name="eicdhn2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_168">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-05-07T16:15:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_167" name="eicdhn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_167">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_166" name="eorib2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_166">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_165" name="eorib5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_165">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_164" name="esbfb5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_164">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_163" name="esbfn2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_163">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_162" name="esbfn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_162">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_161" name="ESP1T" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_161">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:18:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_160" name="IET" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_160">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_159" name="J20ppx" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_159">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_158" name="Jacdh" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_158">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_157" name="Jaiep" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_157">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_156" name="Jamcm" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_156">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_155" name="Jasbf" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_155">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_154" name="Jatem" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_154">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_153" name="Jd2c1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_153">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_152" name="Jd2f6" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_152">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_151" name="Jicdh" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_151">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_150" name="Jiiep" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_150">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_149" name="Jimcm" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_149">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_148" name="Jisbf" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_148">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_147" name="Jitem" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_147">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_146" name="Jn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_146">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_145" name="Jpds" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_145">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_144" name="Jspn" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_144">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_143" name="ka15'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_143">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_142" name="ka15''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_142">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_141" name="ka15p" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_141">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_140" name="ka20'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_140">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_139" name="ka20''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_139">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_138" name="kacdh'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_138">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_137" name="kacdh''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_137">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_136" name="kaiep" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_136">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_135" name="kamcm" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_135">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_134" name="kasb2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_134">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_133" name="kasb5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_133">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_132" name="kasbf" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_132">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_131" name="kasesp" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_131">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_130" name="kasf2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_130">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_129" name="kasf5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_129">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_128" name="kasrent" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_128">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_127" name="kasrentp" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_127">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_126" name="kaswi" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_126">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_125" name="kd14" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_125">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_124" name="kd1c1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_124">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_123" name="kd1f6" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_123">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_122" name="kd1pds'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_122">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_121" name="kd20" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_121">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_120" name="kd2c1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_120">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_119" name="kd2f6" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_119">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_118" name="kd2pds''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_117" name="kd3c1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_117">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_116" name="kd3f6" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_116">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_115" name="kd3pds''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_115">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_114" name="kdb2'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_114">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:39Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_113" name="kdb2''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_113">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_112" name="kdb2p" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_112">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_111" name="kdb5'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_111">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_110" name="kdb5''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_109" name="kdbud" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_109">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_108" name="kdcdh" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_108">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_107" name="kdib2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_107">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_106" name="kdib5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_106">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_105" name="kdiesp" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_104" name="kdif2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_104">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_103" name="kdif5" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_102" name="kdirent" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_101" name="kdirentp" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_100" name="kdn2" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_99" name="kdnet" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_98" name="kdori" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_97" name="kdppx'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_96" name="kdppx''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_95" name="kdspn" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_94" name="kdswi" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_93" name="KEZ" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_93">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T12:17:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_92" name="KEZ2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_92">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_91" name="ki15" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_90" name="kicdh'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_89" name="kicdh''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_89">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-02-21T01:11:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_88" name="kiiep" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_87" name="kimcm" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_86" name="kisbf'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_85" name="kisbf''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_84" name="kiswi" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_83" name="kkpnet'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_82" name="kkpnet''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_82">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-02-21T22:13:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_81" name="kppc1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_80" name="kppf6" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_79" name="kppnet'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_78" name="kppnet''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_77" name="ks14" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_76" name="ks1pds''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_75" name="ks20'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_74" name="ks20''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_73" name="ks2pds''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_72" name="ksb2'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_71" name="ksb2''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_70" name="ksb5'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_69" name="ksb5''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_68" name="ksbud" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_67" name="ksc1'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_66" name="ksc1''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_65" name="kscdh" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_64" name="ksf6'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_63" name="ksf6''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_63">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:47Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_62" name="ksf6'''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_61" name="ksn2'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_61">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:57:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_60" name="ksn2''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_59" name="ksnet" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_59">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:47Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_58" name="ksori" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_58">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:27:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_57" name="kspds'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_57">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_56" name="ksppx" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_56">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_55" name="ksspn" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_55">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_54" name="ksswi'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_54">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_53" name="ksswi''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_53">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_52" name="lte1h" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_52">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_51" name="lte1l" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_51">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T13:31:54Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_50" name="mad2h" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_50">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_49" name="mad2l" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_49">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_48" name="mdt" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_48">
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
      <ModelValue key="ModelValue_47" name="TEM1T" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_47">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_46" name="D" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_46">
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
      <ModelValue key="ModelValue_45" name="mu" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_45">
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
      <ModelValue key="ModelValue_44" name="Vdb5" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_44">
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
      <ModelValue key="ModelValue_43" name="Vdb2" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_43">
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
      <ModelValue key="ModelValue_42" name="Vasbf" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_42">
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
      <ModelValue key="ModelValue_41" name="Visbf" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_41">
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
      <ModelValue key="ModelValue_40" name="Vkpc1" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_40">
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
      <ModelValue key="ModelValue_39" name="Vkpf6" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_39">
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
      <ModelValue key="ModelValue_38" name="Vacdh" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_38">
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
      <ModelValue key="ModelValue_37" name="Vicdh" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_37">
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
      <ModelValue key="ModelValue_36" name="Vppnet" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_36">
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
      <ModelValue key="ModelValue_35" name="Vkpnet" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_35">
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
      <ModelValue key="ModelValue_34" name="Vdppx" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_34">
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
      <ModelValue key="ModelValue_33" name="Vdpds" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_33">
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
      <ModelValue key="ModelValue_32" name="Vaiep" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_32">
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
      <ModelValue key="ModelValue_31" name="Vd2c1" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_31">
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
      <ModelValue key="ModelValue_30" name="Vd2f6" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_30">
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
      <ModelValue key="ModelValue_29" name="Vppc1" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_29">
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
      <ModelValue key="ModelValue_28" name="Vppf6" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_28">
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
      <ModelValue key="ModelValue_27" name="F" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_27">
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
      <ModelValue key="ModelValue_26" name="amount to particle factor" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_26">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T15:51:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_25" name="1stDivisionTime" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_25">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T16:10:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_24" name="mu2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_24">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-05-07T16:15:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_23" name="T0" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_23">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_22" name="Period" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_22">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T13:49:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_21" name="KmGLU" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_21">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:21:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_20" name="GLUconsumed" simulationType="ode">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_20">
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
      <ModelValue key="ModelValue_19" name="quantity_1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_19">
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
      <Reaction key="Reaction_116" name="Growth" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_116">
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
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1175" name="k" value="0.0077"/>
          <Constant key="Parameter_1174" name="Kmsub" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_178">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_695">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_691">
              <SourceParameter reference="ModelValue_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_697">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_699">
              <SourceParameter reference="ModelValue_21"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_115" name="Synthesis of CLN2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_115">
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
          <Product metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_24" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1173" name="ksn2_p" value="1"/>
          <Constant key="Parameter_1172" name="ksn2_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_79">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_353">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_357">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_355">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_358">
              <SourceParameter reference="ModelValue_61"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_362">
              <SourceParameter reference="ModelValue_60"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_114" name="Degradation of CLN2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_114">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1171" name="kdn2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_81">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_356">
              <SourceParameter reference="Metabolite_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_360">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_352">
              <SourceParameter reference="ModelValue_100"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_113" name="Synthesis of CLB2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_113">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1170" name="ksb2_p" value="1"/>
          <Constant key="Parameter_1169" name="ksb2_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_72">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_345">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_349">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_347">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_351">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_354">
              <SourceParameter reference="ModelValue_71"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_112" name="Degradation of CLB2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_112">
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
          <Substrate metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1168" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_71">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_348">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_344">
              <SourceParameter reference="ModelValue_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_365">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_111" name="Synthesis of CLB5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_111">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_24" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1167" name="ksb5_p" value="1"/>
          <Constant key="Parameter_1166" name="ksb5_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_75">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_337">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_341">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_339">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_343">
              <SourceParameter reference="ModelValue_70"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_346">
              <SourceParameter reference="ModelValue_69"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_110" name="Degradation of CLB5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_110">
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
          <Substrate metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1165" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_74">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_340">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_336">
              <SourceParameter reference="ModelValue_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_350">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_109" name="Synthesis of SIC1" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_109">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1164" name="ksc1_p" value="1"/>
          <Constant key="Parameter_1163" name="ksc1_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_73">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_333">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_331">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_335">
              <SourceParameter reference="ModelValue_67"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_338">
              <SourceParameter reference="ModelValue_66"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_108" name="Phosphorylation of SIC1" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_108">
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
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1162" name="Vkpc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_93">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_334">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_330">
              <SourceParameter reference="ModelValue_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_329">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_107" name="Dephosphorylation of SIC1" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_107">
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
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1161" name="Vppc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_92">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_332">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_328">
              <SourceParameter reference="ModelValue_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_326">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_106" name="Fast Degradation of SIC1P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_106">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1160" name="kd3c1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_94">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_342">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_323">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_325">
              <SourceParameter reference="ModelValue_117"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_105" name="Assoc. of CLB2 and SIC1" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_105">
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
          <Substrate metabolite="Metabolite_50" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_66" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1159" name="kasb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_95">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_327">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="ModelValue_134"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_104" name="Dissoc. of CLB2/SIC1 complex" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_104">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_66" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_50" stoichiometry="1"/>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1158" name="kdib2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_96">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="Metabolite_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="ModelValue_107"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_103" name="Assoc. of CLB5 and SIC1" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_103">
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
          <Substrate metabolite="Metabolite_48" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_64" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1157" name="kasb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_97">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_311">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_315">
              <SourceParameter reference="ModelValue_133"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_102" name="Dissoc. of CLB5/SIC1" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_102">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_64" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1156" name="kdib5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_98">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_314">
              <SourceParameter reference="Metabolite_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_309">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_310">
              <SourceParameter reference="ModelValue_106"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_101" name="Phosphorylation of C2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_101">
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
          <Substrate metabolite="Metabolite_66" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_65" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1155" name="Vkpc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_99">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Metabolite_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_308">
              <SourceParameter reference="ModelValue_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_100" name="Dephosphorylation of C2P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_100">
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
          <Substrate metabolite="Metabolite_65" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_66" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1154" name="Vppc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_100">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_324">
              <SourceParameter reference="Metabolite_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_305">
              <SourceParameter reference="ModelValue_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_303">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_99" name="Phosphorylation of C5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_99">
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
          <Substrate metabolite="Metabolite_64" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1153" name="Vkpc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_101">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_307">
              <SourceParameter reference="Metabolite_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_302">
              <SourceParameter reference="ModelValue_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_300">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_98" name="Dephosphorylation of C5P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_98">
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
          <Substrate metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_64" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1152" name="Vppc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_102">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_304">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_299">
              <SourceParameter reference="ModelValue_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_285">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_97" name="Degradation of CLB2 in C2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_97">
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
          <Substrate metabolite="Metabolite_66" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1151" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_103">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_301">
              <SourceParameter reference="Metabolite_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_281">
              <SourceParameter reference="ModelValue_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_96" name="Degradation of CLB5 in C5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_96">
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
          <Substrate metabolite="Metabolite_64" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1150" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_104">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_298">
              <SourceParameter reference="Metabolite_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_289">
              <SourceParameter reference="ModelValue_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_293">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_95" name="Degradation of SIC1 in C2P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_95">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_65" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1149" name="kd3c1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_105">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="Metabolite_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_440">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_295">
              <SourceParameter reference="ModelValue_117"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_94" name="Degradation of SIC1P in C5P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_94">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1148" name="kd3c1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_106">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_291">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_447">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_439">
              <SourceParameter reference="ModelValue_117"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_93" name="Degradation of CLB2 in C2P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_93">
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
          <Substrate metabolite="Metabolite_65" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1147" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_107">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_297">
              <SourceParameter reference="Metabolite_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_448">
              <SourceParameter reference="ModelValue_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_450">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_92" name="Degradation of CLB5 in C5P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_92">
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
          <Substrate metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1146" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_108">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_438">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_451">
              <SourceParameter reference="ModelValue_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_453">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_91" name="CDC6 synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_91">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1145" name="ksf6_p" value="1"/>
          <Constant key="Parameter_1144" name="ksf6_p_p" value="1"/>
          <Constant key="Parameter_1143" name="ksf6_p_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_109">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_462">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_456">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_458">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_454">
              <SourceParameter reference="ModelValue_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_449">
              <SourceParameter reference="ModelValue_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_460">
              <SourceParameter reference="ModelValue_62"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_90" name="Phosphorylation of CDC6" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_90">
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
          <Substrate metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1142" name="Vkpf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_110">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_459">
              <SourceParameter reference="Metabolite_56"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_463">
              <SourceParameter reference="ModelValue_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_455">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_89" name="Dephosphorylation of CDC6" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_89">
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
          <Substrate metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1141" name="Vppf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_111">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_461">
              <SourceParameter reference="Metabolite_55"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_452">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_465">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_88" name="Degradation of CDC6P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_88">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1140" name="kd3f6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_112">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_457">
              <SourceParameter reference="Metabolite_55"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_468">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_466">
              <SourceParameter reference="ModelValue_116"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_87" name="CLB2/CDC6 complex formation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_87">
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
          <Substrate metabolite="Metabolite_50" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1139" name="kasf2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_113">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_473">
              <SourceParameter reference="Metabolite_56"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_464">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_471">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_469">
              <SourceParameter reference="ModelValue_130"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_86" name="CLB2/CDC6 dissociation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_86">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_50" stoichiometry="1"/>
          <Product metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1138" name="kdif2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_114">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_470">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_475">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_474">
              <SourceParameter reference="ModelValue_104"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_85" name="CLB5/CDC6 complex formation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_85">
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
          <Substrate metabolite="Metabolite_48" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1137" name="kasf5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_115">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_480">
              <SourceParameter reference="Metabolite_56"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_472">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_478">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_476">
              <SourceParameter reference="ModelValue_129"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_84" name="CLB5/CDC6 dissociation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_84">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
          <Product metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1136" name="kdif5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_116">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_477">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_482">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_481">
              <SourceParameter reference="ModelValue_103"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_83" name="F2 phosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_83">
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
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1135" name="Vkpf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_117">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_479">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_483">
              <SourceParameter reference="ModelValue_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_485">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_82" name="F2P dephosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_82">
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
          <Substrate metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1134" name="Vppf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_118">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_467">
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_486">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_488">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_81" name="F5 phosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_81">
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
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1133" name="Vkpf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_119">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_484">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_489">
              <SourceParameter reference="ModelValue_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_491">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_80" name="F5P dephosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_80">
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
          <Substrate metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1132" name="Vppf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_120">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_487">
              <SourceParameter reference="Metabolite_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_492">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_494">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_79" name="CLB2 degradation in F2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_79">
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
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1131" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_121">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_490">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_495">
              <SourceParameter reference="ModelValue_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_497">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_78" name="CLB5 degradation in F5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_78">
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
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1130" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_122">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_493">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_498">
              <SourceParameter reference="ModelValue_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_500">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_77" name="CDC6 degradation in F2P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_77">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1129" name="kd3f6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_123">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_496">
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_503">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_501">
              <SourceParameter reference="ModelValue_116"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_76" name="CDC6 degradation in F5P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_76">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1128" name="kd3f6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_124">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_499">
              <SourceParameter reference="Metabolite_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_506">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_504">
              <SourceParameter reference="ModelValue_116"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_75" name="CLB2 degradation in F2P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_75">
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
          <Substrate metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1127" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_125">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_502">
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_507">
              <SourceParameter reference="ModelValue_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_509">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_74" name="CLB5 degradation in F5P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_74">
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
          <Substrate metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1126" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_126">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_505">
              <SourceParameter reference="Metabolite_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_510">
              <SourceParameter reference="ModelValue_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_512">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_73" name="Synthesis of SWI5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_73">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1125" name="ksswi_p" value="1"/>
          <Constant key="Parameter_1124" name="ksswi_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_127">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_515">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_517">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_513">
              <SourceParameter reference="ModelValue_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_508">
              <SourceParameter reference="ModelValue_53"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_72" name="Degradation of SWI5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_72">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1123" name="kdswi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_128">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_514">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_519">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_518">
              <SourceParameter reference="ModelValue_94"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_71" name="Degradation of SWI5P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_71">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1122" name="kdswi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_129">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_516">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_522">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_520">
              <SourceParameter reference="ModelValue_94"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_70" name="Activation of SWI5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_70">
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
          <Substrate metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1121" name="kaswi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_130">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_511">
              <SourceParameter reference="Metabolite_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_527">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_525">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_523">
              <SourceParameter reference="ModelValue_126"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_69" name="Inactivation of SWI5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_69">
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
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1120" name="kiswi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_131">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_524">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_531">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_529">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_528">
              <SourceParameter reference="ModelValue_84"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_68" name="Activation of IEP" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_68">
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
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1119" name="Jaiep" value="1"/>
          <Constant key="Parameter_1118" name="Vaiep" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_132">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_533">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_521">
              <SourceParameter reference="ModelValue_157"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_532">
              <SourceParameter reference="ModelValue_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_535">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_67" name="Inactivation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_67">
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
          <Substrate metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1117" name="Jiiep" value="1"/>
          <Constant key="Parameter_1116" name="kiiep" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_133">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_537">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_536">
              <SourceParameter reference="ModelValue_150"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_539">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_526">
              <SourceParameter reference="ModelValue_88"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_66" name="Synthesis of inactive CDC20" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_66">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1115" name="ks20_p" value="1"/>
          <Constant key="Parameter_1114" name="ks20_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_134">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_541">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_543">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_540">
              <SourceParameter reference="ModelValue_75"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_530">
              <SourceParameter reference="ModelValue_74"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_65" name="Degradation of inactiveCDC20" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_65">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1113" name="kd20" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_135">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_534">
              <SourceParameter reference="Metabolite_57"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_545">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_544">
              <SourceParameter reference="ModelValue_121"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_64" name="Degradation of active CDC20" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_64">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_58" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1112" name="kd20" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_136">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_542">
              <SourceParameter reference="Metabolite_58"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_548">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_546">
              <SourceParameter reference="ModelValue_121"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_63" name="Activation of CDC20" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_63">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0031536" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_58" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1111" name="ka20_p" value="1"/>
          <Constant key="Parameter_1110" name="ka20_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_137">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_555">
              <SourceParameter reference="Metabolite_57"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_551">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_553">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_549">
              <SourceParameter reference="ModelValue_140"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_538">
              <SourceParameter reference="ModelValue_139"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_62" name="Inactivation_2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_62">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0001100" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_58" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1109" name="k" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_138">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_558">
              <SourceParameter reference="Metabolite_58"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_552">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_547">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_556">
              <SourceParameter reference="Parameter_1109"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_61" name="CDH1 synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_61">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1108" name="kscdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_139">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_550">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_559">
              <SourceParameter reference="ModelValue_65"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_60" name="CDH1 degradation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_60">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1107" name="kdcdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_140">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_560">
              <SourceParameter reference="Metabolite_53"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_562">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_554">
              <SourceParameter reference="ModelValue_108"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_59" name="CDH1i degradation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_59">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1106" name="kdcdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_141">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_557">
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_565">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_563">
              <SourceParameter reference="ModelValue_108"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_58" name="CDH1i activation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_58">
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
          <Substrate metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1105" name="Jacdh" value="1"/>
          <Constant key="Parameter_1104" name="Vacdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_142">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_568">
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_561">
              <SourceParameter reference="ModelValue_158"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_566">
              <SourceParameter reference="ModelValue_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_570">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_57" name="Inactivation_3" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_57">
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
          <Substrate metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1103" name="Jicdh" value="1"/>
          <Constant key="Parameter_1102" name="Vicdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_143">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_572">
              <SourceParameter reference="Metabolite_53"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_567">
              <SourceParameter reference="ModelValue_151"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_571">
              <SourceParameter reference="ModelValue_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_574">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_56" name="CDC14 synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_56">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1101" name="ks14" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_144">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_564">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_575">
              <SourceParameter reference="ModelValue_77"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_55" name="CDC14 degradation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_55">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1100" name="kd14" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_145">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_576">
              <SourceParameter reference="Metabolite_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_578">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_569">
              <SourceParameter reference="ModelValue_125"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_54" name="Assoc. with NET1 to form RENT" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_54">
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
          <Substrate metabolite="Metabolite_62" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1099" name="kasrent" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_146">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_573">
              <SourceParameter reference="Metabolite_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_583">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_581">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_579">
              <SourceParameter reference="ModelValue_128"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_53" name="Dissoc. from RENT" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_53">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
          <Product metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1098" name="kdirent" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_147">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_580">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_585">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_584">
              <SourceParameter reference="ModelValue_102"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_52" name="Assoc with NET1P to form RENTP" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_52">
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
          <Substrate metabolite="Metabolite_62" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1097" name="kasrentp" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_148">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_582">
              <SourceParameter reference="Metabolite_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_590">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_588">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_586">
              <SourceParameter reference="ModelValue_127"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_51" name="Dissoc. from RENP" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_51">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_62" stoichiometry="1"/>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1096" name="kdirentp" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_149">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_587">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_592">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_591">
              <SourceParameter reference="ModelValue_101"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_50" name="Net1 synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_50">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1095" name="ksnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_150">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_589">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_593">
              <SourceParameter reference="ModelValue_59"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_49" name="Net1 degradation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_49">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1094" name="kdnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_151">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_595">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_597">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_594">
              <SourceParameter reference="ModelValue_99"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_48" name="Net1P degradation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_48">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1093" name="kdnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_152">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_577">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_600">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_598">
              <SourceParameter reference="ModelValue_99"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_47" name="NET1 phosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_47">
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
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1092" name="Vkpnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_153">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_596">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_601">
              <SourceParameter reference="ModelValue_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_603">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_46" name="dephosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_46">
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
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1091" name="Vppnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_154">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_599">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_604">
              <SourceParameter reference="ModelValue_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_606">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_45" name="RENT phosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_45">
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
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1090" name="Vkpnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_155">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_602">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_607">
              <SourceParameter reference="ModelValue_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_609">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_44" name="dephosphorylation_2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_44">
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
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1089" name="Vppnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_156">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_605">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_610">
              <SourceParameter reference="ModelValue_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_612">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_43" name="Degradation of NET1 in RENT" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_43">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1088" name="kdnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_157">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_608">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_615">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_613">
              <SourceParameter reference="ModelValue_99"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_42" name="Degradation of NET1P in RENTP" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_42">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1087" name="kdnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_158">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_611">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_618">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_616">
              <SourceParameter reference="ModelValue_99"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_41" name="Degradation of CDC14 in RENT" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_41">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1086" name="kd14" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_159">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_614">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_621">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_619">
              <SourceParameter reference="ModelValue_125"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_40" name="Degradation of CDC14 in RENTP" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_40">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1085" name="kd14" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_160">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_617">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_624">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_622">
              <SourceParameter reference="ModelValue_125"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_39" name="TEM1 activation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_39">
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
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1084" name="Jatem" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_161">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_627">
              <SourceParameter reference="ModelValue_154"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_625">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_629">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_620">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_38" name="inactivation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_38">
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
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_68" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1083" name="Jitem" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_162">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_630">
              <SourceParameter reference="Metabolite_68"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_631">
              <SourceParameter reference="ModelValue_147"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_633">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_626">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_37" name="CDC15 activation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_37">
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
          <Substrate metabolite="Metabolite_59" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_60" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_17" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_12" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1082" name="ka15_p" value="1"/>
          <Constant key="Parameter_1081" name="ka15_p_p" value="1"/>
          <Constant key="Parameter_1080" name="ka15p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_163">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_643">
              <SourceParameter reference="Metabolite_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_645">
              <SourceParameter reference="Metabolite_59"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_623">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_639">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_635">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_634">
              <SourceParameter reference="ModelValue_143"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_637">
              <SourceParameter reference="ModelValue_142"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_641">
              <SourceParameter reference="ModelValue_141"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_36" name="inactivation_2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_36">
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
          <Substrate metabolite="Metabolite_60" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_59" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1079" name="ki15" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_164">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_642">
              <SourceParameter reference="Metabolite_60"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_638">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_646">
              <SourceParameter reference="ModelValue_91"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="PPX synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_35">
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
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1078" name="ksppx" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_165">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_644">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_636">
              <SourceParameter reference="ModelValue_56"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_34" name="degradation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_34">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1077" name="Vdppx" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_166">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_632">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_628">
              <SourceParameter reference="ModelValue_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_648">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_33" name="PDS1 synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_33">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_24" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1076" name="ks1pds_p_p" value="1"/>
          <Constant key="Parameter_1075" name="ks2pds_p_p" value="1"/>
          <Constant key="Parameter_1074" name="kspds_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_167">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_657">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_651">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_653">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_640">
              <SourceParameter reference="ModelValue_76"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_655">
              <SourceParameter reference="ModelValue_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_649">
              <SourceParameter reference="ModelValue_57"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_32" name="degradation_2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_32">
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
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1073" name="Vdpds" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_168">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_654">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_658">
              <SourceParameter reference="ModelValue_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_650">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="Degradation of PDS1 in PE" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_31">
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
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1072" name="Vdpds" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_169">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_656">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_647">
              <SourceParameter reference="ModelValue_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_660">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="Assoc. with ESP1 to form PE" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_30">
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
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1071" name="kasesp" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_170">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_665">
              <SourceParameter reference="Metabolite_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_652">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_663">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_661">
              <SourceParameter reference="ModelValue_131"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="Disso. from PE" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_29">
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
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1070" name="kdiesp" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_171">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_662">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_667">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_666">
              <SourceParameter reference="ModelValue_105"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="DNA synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_28">
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
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_48" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1069" name="eorib2" value="1"/>
          <Constant key="Parameter_1068" name="eorib5" value="1"/>
          <Constant key="Parameter_1067" name="ksori" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_172">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_676">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_670">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_672">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_674">
              <SourceParameter reference="ModelValue_166"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_664">
              <SourceParameter reference="ModelValue_165"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_668">
              <SourceParameter reference="ModelValue_58"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="Negative regulation of DNA synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_27">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0008156" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1066" name="kdori" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_173">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_673">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_669">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_677">
              <SourceParameter reference="ModelValue_98"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="Budding" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_26">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0045782" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_67" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_46" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_45" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1065" name="ebudb5" value="1"/>
          <Constant key="Parameter_1064" name="ebudn2" value="1"/>
          <Constant key="Parameter_1063" name="ebudn3" value="1"/>
          <Constant key="Parameter_1062" name="ksbud" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_174">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_689">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_679">
              <SourceParameter reference="Metabolite_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_685">
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_681">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_687">
              <SourceParameter reference="ModelValue_183"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_675">
              <SourceParameter reference="ModelValue_182"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_683">
              <SourceParameter reference="ModelValue_181"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_659">
              <SourceParameter reference="ModelValue_68"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="Negative regulation of Cell budding" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_25">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0045781" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_67" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1061" name="kdbud" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_175">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_686">
              <SourceParameter reference="Metabolite_67"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_682">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_690">
              <SourceParameter reference="ModelValue_109"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="Spindle formation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_24">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0051225" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1060" name="Jspn" value="1"/>
          <Constant key="Parameter_1059" name="ksspn" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_176">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_688">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_671">
              <SourceParameter reference="ModelValue_144"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_692">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_680">
              <SourceParameter reference="ModelValue_55"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_0" name="Spindle disassembly" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0051228" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1058" name="kdspn" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_177">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_678">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_694">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_693">
              <SourceParameter reference="ModelValue_95"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfEvents>
      <Event key="Event_4" name="reset ORI" order="1">
        <TriggerExpression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[KEZ2],Reference=Value&gt; lt 0
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="Metabolite_30">
            <Expression>
              0/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_3" name="start DNA synthesis" order="2">
        <TriggerExpression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ORI],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;-1 gt 0
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="Metabolite_36">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mad2h],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_68">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[bub2h],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_2" name="spindle checkpoint" order="3">
        <TriggerExpression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SPN],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;-1 gt 0
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="Metabolite_36">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mad2l],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_37">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[lte1h],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_68">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[bub2l],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_1" name="cell division" order="4">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_1">
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
          <Assignment targetKey="Metabolite_35">
            <Expression>
              (1-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[F],Reference=Value&gt;)*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MASS],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_37">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[lte1l],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_67">
            <Expression>
              0/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_20">
            <Expression>
              0/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_25">
            <Expression>
              if(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[1stDivisionTime],Reference=Value&gt; lt 0,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[1stDivisionTime],Reference=Value&gt;)
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_22">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[T0],Reference=Value&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_23">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time&gt;
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
    </ListOfEvents>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_1"/>
      <StateTemplateVariable objectReference="ModelValue_20"/>
      <StateTemplateVariable objectReference="Metabolite_56"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="Metabolite_62"/>
      <StateTemplateVariable objectReference="Metabolite_50"/>
      <StateTemplateVariable objectReference="Metabolite_48"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Metabolite_55"/>
      <StateTemplateVariable objectReference="Metabolite_22"/>
      <StateTemplateVariable objectReference="Metabolite_53"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_57"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_32"/>
      <StateTemplateVariable objectReference="Metabolite_65"/>
      <StateTemplateVariable objectReference="Metabolite_40"/>
      <StateTemplateVariable objectReference="Metabolite_63"/>
      <StateTemplateVariable objectReference="Metabolite_42"/>
      <StateTemplateVariable objectReference="Metabolite_66"/>
      <StateTemplateVariable objectReference="Metabolite_41"/>
      <StateTemplateVariable objectReference="Metabolite_46"/>
      <StateTemplateVariable objectReference="Metabolite_38"/>
      <StateTemplateVariable objectReference="Metabolite_30"/>
      <StateTemplateVariable objectReference="Metabolite_27"/>
      <StateTemplateVariable objectReference="Metabolite_60"/>
      <StateTemplateVariable objectReference="Metabolite_67"/>
      <StateTemplateVariable objectReference="Metabolite_20"/>
      <StateTemplateVariable objectReference="Metabolite_12"/>
      <StateTemplateVariable objectReference="Metabolite_58"/>
      <StateTemplateVariable objectReference="Metabolite_52"/>
      <StateTemplateVariable objectReference="Metabolite_18"/>
      <StateTemplateVariable objectReference="Metabolite_44"/>
      <StateTemplateVariable objectReference="Metabolite_26"/>
      <StateTemplateVariable objectReference="Metabolite_43"/>
      <StateTemplateVariable objectReference="Metabolite_64"/>
      <StateTemplateVariable objectReference="Metabolite_35"/>
      <StateTemplateVariable objectReference="Metabolite_69"/>
      <StateTemplateVariable objectReference="Metabolite_59"/>
      <StateTemplateVariable objectReference="Metabolite_45"/>
      <StateTemplateVariable objectReference="Metabolite_39"/>
      <StateTemplateVariable objectReference="Metabolite_34"/>
      <StateTemplateVariable objectReference="Metabolite_28"/>
      <StateTemplateVariable objectReference="Metabolite_24"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="ModelValue_44"/>
      <StateTemplateVariable objectReference="ModelValue_43"/>
      <StateTemplateVariable objectReference="ModelValue_42"/>
      <StateTemplateVariable objectReference="ModelValue_41"/>
      <StateTemplateVariable objectReference="ModelValue_40"/>
      <StateTemplateVariable objectReference="ModelValue_39"/>
      <StateTemplateVariable objectReference="ModelValue_38"/>
      <StateTemplateVariable objectReference="ModelValue_37"/>
      <StateTemplateVariable objectReference="ModelValue_36"/>
      <StateTemplateVariable objectReference="ModelValue_35"/>
      <StateTemplateVariable objectReference="ModelValue_34"/>
      <StateTemplateVariable objectReference="ModelValue_33"/>
      <StateTemplateVariable objectReference="ModelValue_32"/>
      <StateTemplateVariable objectReference="ModelValue_31"/>
      <StateTemplateVariable objectReference="ModelValue_30"/>
      <StateTemplateVariable objectReference="ModelValue_29"/>
      <StateTemplateVariable objectReference="ModelValue_28"/>
      <StateTemplateVariable objectReference="Metabolite_61"/>
      <StateTemplateVariable objectReference="Metabolite_54"/>
      <StateTemplateVariable objectReference="Metabolite_51"/>
      <StateTemplateVariable objectReference="Metabolite_49"/>
      <StateTemplateVariable objectReference="Metabolite_47"/>
      <StateTemplateVariable objectReference="Metabolite_31"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="ModelValue_48"/>
      <StateTemplateVariable objectReference="ModelValue_46"/>
      <StateTemplateVariable objectReference="ModelValue_45"/>
      <StateTemplateVariable objectReference="ModelValue_27"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_68"/>
      <StateTemplateVariable objectReference="Metabolite_37"/>
      <StateTemplateVariable objectReference="Metabolite_36"/>
      <StateTemplateVariable objectReference="ModelValue_189"/>
      <StateTemplateVariable objectReference="ModelValue_188"/>
      <StateTemplateVariable objectReference="ModelValue_187"/>
      <StateTemplateVariable objectReference="ModelValue_186"/>
      <StateTemplateVariable objectReference="ModelValue_185"/>
      <StateTemplateVariable objectReference="ModelValue_184"/>
      <StateTemplateVariable objectReference="ModelValue_183"/>
      <StateTemplateVariable objectReference="ModelValue_182"/>
      <StateTemplateVariable objectReference="ModelValue_181"/>
      <StateTemplateVariable objectReference="ModelValue_180"/>
      <StateTemplateVariable objectReference="ModelValue_179"/>
      <StateTemplateVariable objectReference="ModelValue_178"/>
      <StateTemplateVariable objectReference="ModelValue_177"/>
      <StateTemplateVariable objectReference="ModelValue_176"/>
      <StateTemplateVariable objectReference="ModelValue_175"/>
      <StateTemplateVariable objectReference="ModelValue_174"/>
      <StateTemplateVariable objectReference="ModelValue_173"/>
      <StateTemplateVariable objectReference="ModelValue_172"/>
      <StateTemplateVariable objectReference="ModelValue_171"/>
      <StateTemplateVariable objectReference="ModelValue_170"/>
      <StateTemplateVariable objectReference="ModelValue_169"/>
      <StateTemplateVariable objectReference="ModelValue_168"/>
      <StateTemplateVariable objectReference="ModelValue_167"/>
      <StateTemplateVariable objectReference="ModelValue_166"/>
      <StateTemplateVariable objectReference="ModelValue_165"/>
      <StateTemplateVariable objectReference="ModelValue_164"/>
      <StateTemplateVariable objectReference="ModelValue_163"/>
      <StateTemplateVariable objectReference="ModelValue_162"/>
      <StateTemplateVariable objectReference="ModelValue_161"/>
      <StateTemplateVariable objectReference="ModelValue_160"/>
      <StateTemplateVariable objectReference="ModelValue_159"/>
      <StateTemplateVariable objectReference="ModelValue_158"/>
      <StateTemplateVariable objectReference="ModelValue_157"/>
      <StateTemplateVariable objectReference="ModelValue_156"/>
      <StateTemplateVariable objectReference="ModelValue_155"/>
      <StateTemplateVariable objectReference="ModelValue_154"/>
      <StateTemplateVariable objectReference="ModelValue_153"/>
      <StateTemplateVariable objectReference="ModelValue_152"/>
      <StateTemplateVariable objectReference="ModelValue_151"/>
      <StateTemplateVariable objectReference="ModelValue_150"/>
      <StateTemplateVariable objectReference="ModelValue_149"/>
      <StateTemplateVariable objectReference="ModelValue_148"/>
      <StateTemplateVariable objectReference="ModelValue_147"/>
      <StateTemplateVariable objectReference="ModelValue_146"/>
      <StateTemplateVariable objectReference="ModelValue_145"/>
      <StateTemplateVariable objectReference="ModelValue_144"/>
      <StateTemplateVariable objectReference="ModelValue_143"/>
      <StateTemplateVariable objectReference="ModelValue_142"/>
      <StateTemplateVariable objectReference="ModelValue_141"/>
      <StateTemplateVariable objectReference="ModelValue_140"/>
      <StateTemplateVariable objectReference="ModelValue_139"/>
      <StateTemplateVariable objectReference="ModelValue_138"/>
      <StateTemplateVariable objectReference="ModelValue_137"/>
      <StateTemplateVariable objectReference="ModelValue_136"/>
      <StateTemplateVariable objectReference="ModelValue_135"/>
      <StateTemplateVariable objectReference="ModelValue_134"/>
      <StateTemplateVariable objectReference="ModelValue_133"/>
      <StateTemplateVariable objectReference="ModelValue_132"/>
      <StateTemplateVariable objectReference="ModelValue_131"/>
      <StateTemplateVariable objectReference="ModelValue_130"/>
      <StateTemplateVariable objectReference="ModelValue_129"/>
      <StateTemplateVariable objectReference="ModelValue_128"/>
      <StateTemplateVariable objectReference="ModelValue_127"/>
      <StateTemplateVariable objectReference="ModelValue_126"/>
      <StateTemplateVariable objectReference="ModelValue_125"/>
      <StateTemplateVariable objectReference="ModelValue_124"/>
      <StateTemplateVariable objectReference="ModelValue_123"/>
      <StateTemplateVariable objectReference="ModelValue_122"/>
      <StateTemplateVariable objectReference="ModelValue_121"/>
      <StateTemplateVariable objectReference="ModelValue_120"/>
      <StateTemplateVariable objectReference="ModelValue_119"/>
      <StateTemplateVariable objectReference="ModelValue_118"/>
      <StateTemplateVariable objectReference="ModelValue_117"/>
      <StateTemplateVariable objectReference="ModelValue_116"/>
      <StateTemplateVariable objectReference="ModelValue_115"/>
      <StateTemplateVariable objectReference="ModelValue_114"/>
      <StateTemplateVariable objectReference="ModelValue_113"/>
      <StateTemplateVariable objectReference="ModelValue_112"/>
      <StateTemplateVariable objectReference="ModelValue_111"/>
      <StateTemplateVariable objectReference="ModelValue_110"/>
      <StateTemplateVariable objectReference="ModelValue_109"/>
      <StateTemplateVariable objectReference="ModelValue_108"/>
      <StateTemplateVariable objectReference="ModelValue_107"/>
      <StateTemplateVariable objectReference="ModelValue_106"/>
      <StateTemplateVariable objectReference="ModelValue_105"/>
      <StateTemplateVariable objectReference="ModelValue_104"/>
      <StateTemplateVariable objectReference="ModelValue_103"/>
      <StateTemplateVariable objectReference="ModelValue_102"/>
      <StateTemplateVariable objectReference="ModelValue_101"/>
      <StateTemplateVariable objectReference="ModelValue_100"/>
      <StateTemplateVariable objectReference="ModelValue_99"/>
      <StateTemplateVariable objectReference="ModelValue_98"/>
      <StateTemplateVariable objectReference="ModelValue_97"/>
      <StateTemplateVariable objectReference="ModelValue_96"/>
      <StateTemplateVariable objectReference="ModelValue_95"/>
      <StateTemplateVariable objectReference="ModelValue_94"/>
      <StateTemplateVariable objectReference="ModelValue_93"/>
      <StateTemplateVariable objectReference="ModelValue_92"/>
      <StateTemplateVariable objectReference="ModelValue_91"/>
      <StateTemplateVariable objectReference="ModelValue_90"/>
      <StateTemplateVariable objectReference="ModelValue_89"/>
      <StateTemplateVariable objectReference="ModelValue_88"/>
      <StateTemplateVariable objectReference="ModelValue_87"/>
      <StateTemplateVariable objectReference="ModelValue_86"/>
      <StateTemplateVariable objectReference="ModelValue_85"/>
      <StateTemplateVariable objectReference="ModelValue_84"/>
      <StateTemplateVariable objectReference="ModelValue_83"/>
      <StateTemplateVariable objectReference="ModelValue_82"/>
      <StateTemplateVariable objectReference="ModelValue_81"/>
      <StateTemplateVariable objectReference="ModelValue_80"/>
      <StateTemplateVariable objectReference="ModelValue_79"/>
      <StateTemplateVariable objectReference="ModelValue_78"/>
      <StateTemplateVariable objectReference="ModelValue_77"/>
      <StateTemplateVariable objectReference="ModelValue_76"/>
      <StateTemplateVariable objectReference="ModelValue_75"/>
      <StateTemplateVariable objectReference="ModelValue_74"/>
      <StateTemplateVariable objectReference="ModelValue_73"/>
      <StateTemplateVariable objectReference="ModelValue_72"/>
      <StateTemplateVariable objectReference="ModelValue_71"/>
      <StateTemplateVariable objectReference="ModelValue_70"/>
      <StateTemplateVariable objectReference="ModelValue_69"/>
      <StateTemplateVariable objectReference="ModelValue_68"/>
      <StateTemplateVariable objectReference="ModelValue_67"/>
      <StateTemplateVariable objectReference="ModelValue_66"/>
      <StateTemplateVariable objectReference="ModelValue_65"/>
      <StateTemplateVariable objectReference="ModelValue_64"/>
      <StateTemplateVariable objectReference="ModelValue_63"/>
      <StateTemplateVariable objectReference="ModelValue_62"/>
      <StateTemplateVariable objectReference="ModelValue_61"/>
      <StateTemplateVariable objectReference="ModelValue_60"/>
      <StateTemplateVariable objectReference="ModelValue_59"/>
      <StateTemplateVariable objectReference="ModelValue_58"/>
      <StateTemplateVariable objectReference="ModelValue_57"/>
      <StateTemplateVariable objectReference="ModelValue_56"/>
      <StateTemplateVariable objectReference="ModelValue_55"/>
      <StateTemplateVariable objectReference="ModelValue_54"/>
      <StateTemplateVariable objectReference="ModelValue_53"/>
      <StateTemplateVariable objectReference="ModelValue_52"/>
      <StateTemplateVariable objectReference="ModelValue_51"/>
      <StateTemplateVariable objectReference="ModelValue_50"/>
      <StateTemplateVariable objectReference="ModelValue_49"/>
      <StateTemplateVariable objectReference="ModelValue_47"/>
      <StateTemplateVariable objectReference="ModelValue_26"/>
      <StateTemplateVariable objectReference="ModelValue_25"/>
      <StateTemplateVariable objectReference="ModelValue_24"/>
      <StateTemplateVariable objectReference="ModelValue_23"/>
      <StateTemplateVariable objectReference="ModelValue_22"/>
      <StateTemplateVariable objectReference="ModelValue_21"/>
      <StateTemplateVariable objectReference="ModelValue_19"/>
      <StateTemplateVariable objectReference="Compartment_1"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 1.747366772326145e+23 6.153793596801723e+22 1.80535936470497e+23 9.253339255958898e+21 3.888445993186847e+21 2.019185755329673e+22 1.964083420555222e+23 6.987702526155101e+21 3.151195626929545e+21 6.004823451606606e+23 1.093220582617616e+22 6.649934635684339e+23 5.446744061809811e+23 6.421153989171979e+23 5.428453477226389e+21 2.417387190365045e+18 2.307420732690804e+21 5.07527926009403e+21 1.415750029349605e+23 6.000645303884879e+19 2.879579509269514e+22 2.196294727685002e+22 5.793351133464459e+22 7.235672544851775e+22 3.817302580975657e+23 9.000829013319018e+21 3.305249612645038e+22 4.758414978992805e+23 2.29204033134851e+23 1.731804839342614e+21 7.393161906544548e+21 2.159777877052535e+23 8.274840214739905e+23 1.056512290096014e+23 6.3287734055348e+22 5.128887707846334e+23 2.769599495608814e+22 2.204839025199744e+23 2.994240326851319e+22 5.802512306655105e+23 6.177544327875697e+21 3.862363808942007e+23 7.496745791131755e+21 1.263726581862738e+23 0.07089635273693944 0.4589400389952509 0.4049488649158367 0.7229242355857484 0.06235613837299574 0.06275344891616547 0.2498295509602317 0.009132056532627379 0.410453463847625 0.3324302671175435 0.8999351532761245 0.1260054117516113 0.001536552944821854 0.02672503759551066 0.02826159054033252 1.199147754801158 1.199147754801158 1.20442835800001e+24 2.925133259548562e+23 5.698011095421221e+23 2.669833167945896e+23 6.954602797048728e+22 1.686199701200007e+24 2.772877561481376e+23 104.9622873419346 123.3657142857143 0.006603773584905661 0.4427813287861195 1.204428358e+21 1.204428300000005e+23 6.022141500000027e+22 6.022141499999998e+21 0.054 1 0.2 0.4 1 1 1 0.25 0.05 0.45 0.1 0.03 0.06 0.3 0.55 0.1 0.03 0.06 0.3 1.2 8 0.4 0.25 0.45 0.9 2 2 10 1 1 0.15 0.03 0.1 0.1 0.01 0.1 0.05 0.05 0.03 0.1 0.1 0.01 0.1 6 0.04 0.14 0.002 1 0.001 0.05 0.2 0.01 0.8 0.1 1 50 50 0.38 50 15 0.01 200 1 2 0.1 0.01 0.01 0.01 0.3 1 1 0.2 1 1 0.04 0.003 0.4 0.15 0.01 0.16 0.06 0.01 0.05 0.06 0.5 0.5 0.01 1 2 0.12 0.03 0.06 0.17 2 0.06 0.08 0.3 0.2 0.5 0.001 0.08 0.15 0.15 0.6 8 0.05 0.01 0.6 4 4 0.05 3 0.2 0.03 0.006 0.6 0.055 0.001 0.04 0.0008 0.005 0.2 0.012 0.12 0.01 0.024 0.12 0.004 0 0.15 0.08400000000000001 2 0 0.1 0.1 0.005 0.08 1 0.1 8 0.01 1 6.0221415e+23 -1 0.007 0 0 0.00012 0 1 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_34" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_14" target="" append="1"/>
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
    <Task key="Task_21" name="Time-Course" type="timeCourse" scheduled="true" updateModel="false">
      <Report reference="Report_20" target="EventTest12.1.txt" append="0"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="2"/>
        <Parameter name="StepSize" type="float" value="200"/>
        <Parameter name="Duration" type="float" value="400"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="1"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_20" name="Scan" type="scan" scheduled="false" updateModel="false">
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
    <Task key="Task_19" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_13" target="" append="1"/>
      <Problem>
      </Problem>
      <Method name="Bit Pattern Tree Algorithm" type="EFMBitPatternTreeMethod">
      </Method>
    </Task>
    <Task key="Task_18" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_12" target="" append="1"/>
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
    <Task key="Task_17" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_11" target="" append="1"/>
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
      </Problem>
      <Method name="Evolutionary Programming" type="EvolutionaryProgram">
        <Parameter name="Number of Generations" type="unsignedInteger" value="200"/>
        <Parameter name="Population Size" type="unsignedInteger" value="20"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_16" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_10" target="" append="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value=""/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1e-09"/>
      </Method>
    </Task>
    <Task key="Task_15" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_9" target="" append="1"/>
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
    <Task key="Task_14" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_8" target="" append="1"/>
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
    <Task key="Task_13" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_16" target="" append="1"/>
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
    <Task key="Task_12" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_14" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_13" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_12" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_11" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_10" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_9" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <Report key="Report_8" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_16" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_20" name="Events" taskType="timeCourse" separator="&#x09;" precision="6">
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
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="Concentrations, Volumes, and Global Quantity Values" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="[BCK2]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BCK2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[BUB2]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BUB2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[BUD]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[BUD],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[C2]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[C2P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[C5]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[C5P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC14]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC14T]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC15]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC15],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC15i]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC15i],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC20]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC20],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC20i]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC20i],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC6]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC6P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDC6T]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDH1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDH1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CDH1i]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDH1i],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CKIT]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CKIT],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CLB2]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CLB2T]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CLB5]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CLB5T]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CLN2]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[CLN3]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLN3],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[ESP1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ESP1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[F2]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[F2P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[F5]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[F5P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IE]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[IE],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IEP]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[IEP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[LTE1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[LTE1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[MAD2]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MAD2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[MASS]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MASS],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[MCM1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MCM1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[NET1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[NET1P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[NET1T]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[NET1T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[ORI]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ORI],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[PDS1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PDS1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[PE]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PE],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[PPX]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[PPX],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[RENT]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENT],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[RENTP]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENTP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SBF]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SBF],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SIC1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SIC1P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SIC1T]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1T],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SPN]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SPN],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SWI5]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SWI5],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[SWI5P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SWI5P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[TEM1GDP]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[TEM1GDP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[TEM1GTP]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[TEM1GTP],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[mdt]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mdt],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[D]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[D],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[mu]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mu],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vdb5]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb5],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vdb2]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdb2],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vasbf]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vasbf],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Visbf]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Visbf],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vkpc1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpc1],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vkpf6]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpf6],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vacdh]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vacdh],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vicdh]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vicdh],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vppnet]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppnet],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vkpnet]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vkpnet],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vdppx]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdppx],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vdpds]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vdpds],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vaiep]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vaiep],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vd2c1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vd2c1],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vd2f6]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vd2f6],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vppc1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppc1],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Vppf6]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vppf6],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[F]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[F],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[1stDivisionTime]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[1stDivisionTime],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[T0]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[T0],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[Period]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Period],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[GLUconsumed]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
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
      <Slider key="Slider_0" associatedEntityKey="Task_21" objectCN="CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[GLU],Reference=InitialConcentration" objectType="float" objectValue="0.002" minValue="0.0008" maxValue="2e+07" tickNumber="1000" tickFactor="100" scaling="linear"/>
    </ListOfSliders>
  </GUI>
  <SBMLReference file="../../../../COPASI Files/Bugs/BIOMD0000000056.xml">
    <SBMLMap SBMLid="Activation_of_CDC20" COPASIkey="Reaction_63"/>
    <SBMLMap SBMLid="Activation_of_IEP" COPASIkey="Reaction_68"/>
    <SBMLMap SBMLid="Activation_of_SWI5" COPASIkey="Reaction_70"/>
    <SBMLMap SBMLid="Assoc_of_CLB2_and_SIC1" COPASIkey="Reaction_105"/>
    <SBMLMap SBMLid="Assoc_of_CLB5_and_SIC1" COPASIkey="Reaction_103"/>
    <SBMLMap SBMLid="Assoc_with_ESP1_to_form_PE" COPASIkey="Reaction_30"/>
    <SBMLMap SBMLid="Assoc_with_NET1P_to_form_RENTP" COPASIkey="Reaction_52"/>
    <SBMLMap SBMLid="Assoc_with_NET1_to_form_RENT" COPASIkey="Reaction_54"/>
    <SBMLMap SBMLid="BCK2" COPASIkey="Metabolite_69"/>
    <SBMLMap SBMLid="BUB2" COPASIkey="Metabolite_68"/>
    <SBMLMap SBMLid="BUD" COPASIkey="Metabolite_67"/>
    <SBMLMap SBMLid="Budding" COPASIkey="Reaction_26"/>
    <SBMLMap SBMLid="C0" COPASIkey="ModelValue_186"/>
    <SBMLMap SBMLid="C2" COPASIkey="Metabolite_66"/>
    <SBMLMap SBMLid="C2P" COPASIkey="Metabolite_65"/>
    <SBMLMap SBMLid="C5" COPASIkey="Metabolite_64"/>
    <SBMLMap SBMLid="C5P" COPASIkey="Metabolite_63"/>
    <SBMLMap SBMLid="CDC14" COPASIkey="Metabolite_62"/>
    <SBMLMap SBMLid="CDC14T" COPASIkey="Metabolite_61"/>
    <SBMLMap SBMLid="CDC14_degradation" COPASIkey="Reaction_55"/>
    <SBMLMap SBMLid="CDC14_synthesis" COPASIkey="Reaction_56"/>
    <SBMLMap SBMLid="CDC15" COPASIkey="Metabolite_60"/>
    <SBMLMap SBMLid="CDC15T" COPASIkey="ModelValue_185"/>
    <SBMLMap SBMLid="CDC15_activation" COPASIkey="Reaction_37"/>
    <SBMLMap SBMLid="CDC15i" COPASIkey="Metabolite_59"/>
    <SBMLMap SBMLid="CDC20" COPASIkey="Metabolite_58"/>
    <SBMLMap SBMLid="CDC20i" COPASIkey="Metabolite_57"/>
    <SBMLMap SBMLid="CDC6" COPASIkey="Metabolite_56"/>
    <SBMLMap SBMLid="CDC6P" COPASIkey="Metabolite_55"/>
    <SBMLMap SBMLid="CDC6T" COPASIkey="Metabolite_54"/>
    <SBMLMap SBMLid="CDC6_degradation_in_F2P" COPASIkey="Reaction_77"/>
    <SBMLMap SBMLid="CDC6_degradation_in_F5P" COPASIkey="Reaction_76"/>
    <SBMLMap SBMLid="CDC6_synthesis" COPASIkey="Reaction_91"/>
    <SBMLMap SBMLid="CDH1" COPASIkey="Metabolite_53"/>
    <SBMLMap SBMLid="CDH1_degradation" COPASIkey="Reaction_60"/>
    <SBMLMap SBMLid="CDH1_synthesis" COPASIkey="Reaction_61"/>
    <SBMLMap SBMLid="CDH1i" COPASIkey="Metabolite_52"/>
    <SBMLMap SBMLid="CDH1i_activation" COPASIkey="Reaction_58"/>
    <SBMLMap SBMLid="CDH1i_degradation" COPASIkey="Reaction_59"/>
    <SBMLMap SBMLid="CKIT" COPASIkey="Metabolite_51"/>
    <SBMLMap SBMLid="CLB2" COPASIkey="Metabolite_50"/>
    <SBMLMap SBMLid="CLB2CDC6_complex_formation" COPASIkey="Reaction_87"/>
    <SBMLMap SBMLid="CLB2CDC6_dissociation" COPASIkey="Reaction_86"/>
    <SBMLMap SBMLid="CLB2T" COPASIkey="Metabolite_49"/>
    <SBMLMap SBMLid="CLB2_degradation_in_F2" COPASIkey="Reaction_79"/>
    <SBMLMap SBMLid="CLB2_degradation_in_F2P" COPASIkey="Reaction_75"/>
    <SBMLMap SBMLid="CLB5" COPASIkey="Metabolite_48"/>
    <SBMLMap SBMLid="CLB5CDC6_complex_formation" COPASIkey="Reaction_85"/>
    <SBMLMap SBMLid="CLB5CDC6_dissociation" COPASIkey="Reaction_84"/>
    <SBMLMap SBMLid="CLB5T" COPASIkey="Metabolite_47"/>
    <SBMLMap SBMLid="CLB5_degradation_in_F5" COPASIkey="Reaction_78"/>
    <SBMLMap SBMLid="CLB5_degradation_in_F5P" COPASIkey="Reaction_74"/>
    <SBMLMap SBMLid="CLN2" COPASIkey="Metabolite_46"/>
    <SBMLMap SBMLid="CLN3" COPASIkey="Metabolite_45"/>
    <SBMLMap SBMLid="D" COPASIkey="ModelValue_46"/>
    <SBMLMap SBMLid="DNA_synthesis" COPASIkey="Reaction_28"/>
    <SBMLMap SBMLid="Degradation_of_CDC14_in_RENT" COPASIkey="Reaction_41"/>
    <SBMLMap SBMLid="Degradation_of_CDC14_in_RENTP" COPASIkey="Reaction_40"/>
    <SBMLMap SBMLid="Degradation_of_CDC6P" COPASIkey="Reaction_88"/>
    <SBMLMap SBMLid="Degradation_of_CLB2" COPASIkey="Reaction_112"/>
    <SBMLMap SBMLid="Degradation_of_CLB2_in_C2" COPASIkey="Reaction_97"/>
    <SBMLMap SBMLid="Degradation_of_CLB2_in_C2P" COPASIkey="Reaction_93"/>
    <SBMLMap SBMLid="Degradation_of_CLB5" COPASIkey="Reaction_110"/>
    <SBMLMap SBMLid="Degradation_of_CLB5_in_C5" COPASIkey="Reaction_96"/>
    <SBMLMap SBMLid="Degradation_of_CLB5_in_C5P" COPASIkey="Reaction_92"/>
    <SBMLMap SBMLid="Degradation_of_CLN2" COPASIkey="Reaction_114"/>
    <SBMLMap SBMLid="Degradation_of_NET1P_in_RENTP" COPASIkey="Reaction_42"/>
    <SBMLMap SBMLid="Degradation_of_NET1_in_RENT" COPASIkey="Reaction_43"/>
    <SBMLMap SBMLid="Degradation_of_PDS1_in_PE" COPASIkey="Reaction_31"/>
    <SBMLMap SBMLid="Degradation_of_SIC1P_in_C5P_" COPASIkey="Reaction_94"/>
    <SBMLMap SBMLid="Degradation_of_SIC1_in_C2P" COPASIkey="Reaction_95"/>
    <SBMLMap SBMLid="Degradation_of_SWI5" COPASIkey="Reaction_72"/>
    <SBMLMap SBMLid="Degradation_of_SWI5P" COPASIkey="Reaction_71"/>
    <SBMLMap SBMLid="Degradation_of_active_CDC20" COPASIkey="Reaction_64"/>
    <SBMLMap SBMLid="Degradation_of_inactiveCDC20" COPASIkey="Reaction_65"/>
    <SBMLMap SBMLid="Dephosphorylation_of_C2P" COPASIkey="Reaction_100"/>
    <SBMLMap SBMLid="Dephosphorylation_of_C5P" COPASIkey="Reaction_98"/>
    <SBMLMap SBMLid="Dephosphorylation_of_CDC6" COPASIkey="Reaction_89"/>
    <SBMLMap SBMLid="Dephosphorylation_of_SIC1" COPASIkey="Reaction_107"/>
    <SBMLMap SBMLid="Disso_from_PE" COPASIkey="Reaction_29"/>
    <SBMLMap SBMLid="Dissoc_from_RENP" COPASIkey="Reaction_51"/>
    <SBMLMap SBMLid="Dissoc_from_RENT" COPASIkey="Reaction_53"/>
    <SBMLMap SBMLid="Dissoc_of_CLB2SIC1_complex" COPASIkey="Reaction_104"/>
    <SBMLMap SBMLid="Dissoc_of_CLB5SIC1" COPASIkey="Reaction_102"/>
    <SBMLMap SBMLid="Dn3" COPASIkey="ModelValue_184"/>
    <SBMLMap SBMLid="ESP1" COPASIkey="Metabolite_44"/>
    <SBMLMap SBMLid="ESP1T" COPASIkey="ModelValue_161"/>
    <SBMLMap SBMLid="F" COPASIkey="ModelValue_27"/>
    <SBMLMap SBMLid="F2" COPASIkey="Metabolite_43"/>
    <SBMLMap SBMLid="F2P" COPASIkey="Metabolite_42"/>
    <SBMLMap SBMLid="F2P_dephosphorylation" COPASIkey="Reaction_82"/>
    <SBMLMap SBMLid="F2_phosphorylation" COPASIkey="Reaction_83"/>
    <SBMLMap SBMLid="F5" COPASIkey="Metabolite_41"/>
    <SBMLMap SBMLid="F5P" COPASIkey="Metabolite_40"/>
    <SBMLMap SBMLid="F5P_dephosphorylation" COPASIkey="Reaction_80"/>
    <SBMLMap SBMLid="F5_phosphorylation" COPASIkey="Reaction_81"/>
    <SBMLMap SBMLid="Fast_Degradation_of_SIC1P" COPASIkey="Reaction_106"/>
    <SBMLMap SBMLid="GK_219" COPASIkey="Function_77"/>
    <SBMLMap SBMLid="Growth" COPASIkey="Reaction_116"/>
    <SBMLMap SBMLid="IE" COPASIkey="Metabolite_39"/>
    <SBMLMap SBMLid="IEP" COPASIkey="Metabolite_38"/>
    <SBMLMap SBMLid="IET" COPASIkey="ModelValue_160"/>
    <SBMLMap SBMLid="Inactivation_1" COPASIkey="Reaction_67"/>
    <SBMLMap SBMLid="Inactivation_2" COPASIkey="Reaction_62"/>
    <SBMLMap SBMLid="Inactivation_3" COPASIkey="Reaction_57"/>
    <SBMLMap SBMLid="Inactivation_of_SWI5" COPASIkey="Reaction_69"/>
    <SBMLMap SBMLid="J20ppx" COPASIkey="ModelValue_159"/>
    <SBMLMap SBMLid="Jacdh" COPASIkey="ModelValue_158"/>
    <SBMLMap SBMLid="Jaiep" COPASIkey="ModelValue_157"/>
    <SBMLMap SBMLid="Jamcm" COPASIkey="ModelValue_156"/>
    <SBMLMap SBMLid="Jasbf" COPASIkey="ModelValue_155"/>
    <SBMLMap SBMLid="Jatem" COPASIkey="ModelValue_154"/>
    <SBMLMap SBMLid="Jd2c1" COPASIkey="ModelValue_153"/>
    <SBMLMap SBMLid="Jd2f6" COPASIkey="ModelValue_152"/>
    <SBMLMap SBMLid="Jicdh" COPASIkey="ModelValue_151"/>
    <SBMLMap SBMLid="Jiiep" COPASIkey="ModelValue_150"/>
    <SBMLMap SBMLid="Jimcm" COPASIkey="ModelValue_149"/>
    <SBMLMap SBMLid="Jisbf" COPASIkey="ModelValue_148"/>
    <SBMLMap SBMLid="Jitem" COPASIkey="ModelValue_147"/>
    <SBMLMap SBMLid="Jn3" COPASIkey="ModelValue_146"/>
    <SBMLMap SBMLid="Jpds" COPASIkey="ModelValue_145"/>
    <SBMLMap SBMLid="Jspn" COPASIkey="ModelValue_144"/>
    <SBMLMap SBMLid="KEZ" COPASIkey="ModelValue_93"/>
    <SBMLMap SBMLid="KEZ2" COPASIkey="ModelValue_92"/>
    <SBMLMap SBMLid="LTE1" COPASIkey="Metabolite_37"/>
    <SBMLMap SBMLid="MAD2" COPASIkey="Metabolite_36"/>
    <SBMLMap SBMLid="MASS" COPASIkey="Metabolite_35"/>
    <SBMLMap SBMLid="MCM1" COPASIkey="Metabolite_34"/>
    <SBMLMap SBMLid="Mass_Action_1_222" COPASIkey="Function_76"/>
    <SBMLMap SBMLid="Mass_Action_2_221" COPASIkey="Function_78"/>
    <SBMLMap SBMLid="MichaelisMenten_220" COPASIkey="Function_80"/>
    <SBMLMap SBMLid="NET1" COPASIkey="Metabolite_33"/>
    <SBMLMap SBMLid="NET1P" COPASIkey="Metabolite_32"/>
    <SBMLMap SBMLid="NET1T" COPASIkey="Metabolite_31"/>
    <SBMLMap SBMLid="NET1_phosphorylation" COPASIkey="Reaction_47"/>
    <SBMLMap SBMLid="Negative_regulation_of_Cell_budding" COPASIkey="Reaction_25"/>
    <SBMLMap SBMLid="Negative_regulation_of_DNA_synthesis" COPASIkey="Reaction_27"/>
    <SBMLMap SBMLid="Net1P_degradation" COPASIkey="Reaction_48"/>
    <SBMLMap SBMLid="Net1_degradation" COPASIkey="Reaction_49"/>
    <SBMLMap SBMLid="Net1_synthesis" COPASIkey="Reaction_50"/>
    <SBMLMap SBMLid="ORI" COPASIkey="Metabolite_30"/>
    <SBMLMap SBMLid="PDS1" COPASIkey="Metabolite_29"/>
    <SBMLMap SBMLid="PDS1_synthesis" COPASIkey="Reaction_33"/>
    <SBMLMap SBMLid="PE" COPASIkey="Metabolite_28"/>
    <SBMLMap SBMLid="PPX" COPASIkey="Metabolite_27"/>
    <SBMLMap SBMLid="PPX_synthesis" COPASIkey="Reaction_35"/>
    <SBMLMap SBMLid="Phosphorylation_of_C2" COPASIkey="Reaction_101"/>
    <SBMLMap SBMLid="Phosphorylation_of_C5" COPASIkey="Reaction_99"/>
    <SBMLMap SBMLid="Phosphorylation_of_CDC6" COPASIkey="Reaction_90"/>
    <SBMLMap SBMLid="Phosphorylation_of_SIC1" COPASIkey="Reaction_108"/>
    <SBMLMap SBMLid="RENT" COPASIkey="Metabolite_26"/>
    <SBMLMap SBMLid="RENTP" COPASIkey="Metabolite_25"/>
    <SBMLMap SBMLid="RENT_phosphorylation" COPASIkey="Reaction_45"/>
    <SBMLMap SBMLid="SBF" COPASIkey="Metabolite_24"/>
    <SBMLMap SBMLid="SIC1" COPASIkey="Metabolite_23"/>
    <SBMLMap SBMLid="SIC1P" COPASIkey="Metabolite_22"/>
    <SBMLMap SBMLid="SIC1T" COPASIkey="Metabolite_21"/>
    <SBMLMap SBMLid="SPN" COPASIkey="Metabolite_20"/>
    <SBMLMap SBMLid="SWI5" COPASIkey="Metabolite_19"/>
    <SBMLMap SBMLid="SWI5P" COPASIkey="Metabolite_18"/>
    <SBMLMap SBMLid="Spindle_disassembly" COPASIkey="Reaction_0"/>
    <SBMLMap SBMLid="Spindle_formation" COPASIkey="Reaction_24"/>
    <SBMLMap SBMLid="Synthesis_of_CLB2" COPASIkey="Reaction_113"/>
    <SBMLMap SBMLid="Synthesis_of_CLB5" COPASIkey="Reaction_111"/>
    <SBMLMap SBMLid="Synthesis_of_CLN2" COPASIkey="Reaction_115"/>
    <SBMLMap SBMLid="Synthesis_of_SIC1" COPASIkey="Reaction_109"/>
    <SBMLMap SBMLid="Synthesis_of_SWI5" COPASIkey="Reaction_73"/>
    <SBMLMap SBMLid="Synthesis_of_inactive_CDC20" COPASIkey="Reaction_66"/>
    <SBMLMap SBMLid="TEM1GDP" COPASIkey="Metabolite_17"/>
    <SBMLMap SBMLid="TEM1GTP" COPASIkey="Metabolite_12"/>
    <SBMLMap SBMLid="TEM1T" COPASIkey="ModelValue_47"/>
    <SBMLMap SBMLid="TEM1_activation" COPASIkey="Reaction_39"/>
    <SBMLMap SBMLid="Vacdh" COPASIkey="ModelValue_38"/>
    <SBMLMap SBMLid="Vaiep" COPASIkey="ModelValue_32"/>
    <SBMLMap SBMLid="Vasbf" COPASIkey="ModelValue_42"/>
    <SBMLMap SBMLid="Vd2c1" COPASIkey="ModelValue_31"/>
    <SBMLMap SBMLid="Vd2f6" COPASIkey="ModelValue_30"/>
    <SBMLMap SBMLid="Vdb2" COPASIkey="ModelValue_43"/>
    <SBMLMap SBMLid="Vdb5" COPASIkey="ModelValue_44"/>
    <SBMLMap SBMLid="Vdpds" COPASIkey="ModelValue_33"/>
    <SBMLMap SBMLid="Vdppx" COPASIkey="ModelValue_34"/>
    <SBMLMap SBMLid="Vicdh" COPASIkey="ModelValue_37"/>
    <SBMLMap SBMLid="Visbf" COPASIkey="ModelValue_41"/>
    <SBMLMap SBMLid="Vkpc1" COPASIkey="ModelValue_40"/>
    <SBMLMap SBMLid="Vkpf6" COPASIkey="ModelValue_39"/>
    <SBMLMap SBMLid="Vkpnet" COPASIkey="ModelValue_35"/>
    <SBMLMap SBMLid="Vppc1" COPASIkey="ModelValue_29"/>
    <SBMLMap SBMLid="Vppf6" COPASIkey="ModelValue_28"/>
    <SBMLMap SBMLid="Vppnet" COPASIkey="ModelValue_36"/>
    <SBMLMap SBMLid="b0" COPASIkey="ModelValue_189"/>
    <SBMLMap SBMLid="bub2h" COPASIkey="ModelValue_188"/>
    <SBMLMap SBMLid="bub2l" COPASIkey="ModelValue_187"/>
    <SBMLMap SBMLid="cell" COPASIkey="Compartment_1"/>
    <SBMLMap SBMLid="degradation_1" COPASIkey="Reaction_34"/>
    <SBMLMap SBMLid="degradation_2" COPASIkey="Reaction_32"/>
    <SBMLMap SBMLid="dephosphorylation_1" COPASIkey="Reaction_46"/>
    <SBMLMap SBMLid="dephosphorylation_2" COPASIkey="Reaction_44"/>
    <SBMLMap SBMLid="ebudb5" COPASIkey="ModelValue_183"/>
    <SBMLMap SBMLid="ebudn2" COPASIkey="ModelValue_182"/>
    <SBMLMap SBMLid="ebudn3" COPASIkey="ModelValue_181"/>
    <SBMLMap SBMLid="ec1b2" COPASIkey="ModelValue_180"/>
    <SBMLMap SBMLid="ec1b5" COPASIkey="ModelValue_179"/>
    <SBMLMap SBMLid="ec1k2" COPASIkey="ModelValue_178"/>
    <SBMLMap SBMLid="ec1n2" COPASIkey="ModelValue_177"/>
    <SBMLMap SBMLid="ec1n3" COPASIkey="ModelValue_176"/>
    <SBMLMap SBMLid="ef6b2" COPASIkey="ModelValue_175"/>
    <SBMLMap SBMLid="ef6b5" COPASIkey="ModelValue_174"/>
    <SBMLMap SBMLid="ef6k2" COPASIkey="ModelValue_173"/>
    <SBMLMap SBMLid="ef6n2" COPASIkey="ModelValue_172"/>
    <SBMLMap SBMLid="ef6n3" COPASIkey="ModelValue_171"/>
    <SBMLMap SBMLid="eicdhb2" COPASIkey="ModelValue_170"/>
    <SBMLMap SBMLid="eicdhb5" COPASIkey="ModelValue_169"/>
    <SBMLMap SBMLid="eicdhn2" COPASIkey="ModelValue_168"/>
    <SBMLMap SBMLid="eicdhn3" COPASIkey="ModelValue_167"/>
    <SBMLMap SBMLid="eorib2" COPASIkey="ModelValue_166"/>
    <SBMLMap SBMLid="eorib5" COPASIkey="ModelValue_165"/>
    <SBMLMap SBMLid="esbfb5" COPASIkey="ModelValue_164"/>
    <SBMLMap SBMLid="esbfn2" COPASIkey="ModelValue_163"/>
    <SBMLMap SBMLid="esbfn3" COPASIkey="ModelValue_162"/>
    <SBMLMap SBMLid="inactivation_1" COPASIkey="Reaction_38"/>
    <SBMLMap SBMLid="inactivation_2" COPASIkey="Reaction_36"/>
    <SBMLMap SBMLid="ka15_p" COPASIkey="ModelValue_143"/>
    <SBMLMap SBMLid="ka15_p_p" COPASIkey="ModelValue_142"/>
    <SBMLMap SBMLid="ka15p" COPASIkey="ModelValue_141"/>
    <SBMLMap SBMLid="ka20_p" COPASIkey="ModelValue_140"/>
    <SBMLMap SBMLid="ka20_p_p" COPASIkey="ModelValue_139"/>
    <SBMLMap SBMLid="kacdh_p" COPASIkey="ModelValue_138"/>
    <SBMLMap SBMLid="kacdh_p_p" COPASIkey="ModelValue_137"/>
    <SBMLMap SBMLid="kaiep" COPASIkey="ModelValue_136"/>
    <SBMLMap SBMLid="kamcm" COPASIkey="ModelValue_135"/>
    <SBMLMap SBMLid="kasb2" COPASIkey="ModelValue_134"/>
    <SBMLMap SBMLid="kasb5" COPASIkey="ModelValue_133"/>
    <SBMLMap SBMLid="kasbf" COPASIkey="ModelValue_132"/>
    <SBMLMap SBMLid="kasesp" COPASIkey="ModelValue_131"/>
    <SBMLMap SBMLid="kasf2" COPASIkey="ModelValue_130"/>
    <SBMLMap SBMLid="kasf5" COPASIkey="ModelValue_129"/>
    <SBMLMap SBMLid="kasrent" COPASIkey="ModelValue_128"/>
    <SBMLMap SBMLid="kasrentp" COPASIkey="ModelValue_127"/>
    <SBMLMap SBMLid="kaswi" COPASIkey="ModelValue_126"/>
    <SBMLMap SBMLid="kd14" COPASIkey="ModelValue_125"/>
    <SBMLMap SBMLid="kd1c1" COPASIkey="ModelValue_124"/>
    <SBMLMap SBMLid="kd1f6" COPASIkey="ModelValue_123"/>
    <SBMLMap SBMLid="kd1pds_p" COPASIkey="ModelValue_122"/>
    <SBMLMap SBMLid="kd20" COPASIkey="ModelValue_121"/>
    <SBMLMap SBMLid="kd2c1" COPASIkey="ModelValue_120"/>
    <SBMLMap SBMLid="kd2f6" COPASIkey="ModelValue_119"/>
    <SBMLMap SBMLid="kd2pds_p_p" COPASIkey="ModelValue_118"/>
    <SBMLMap SBMLid="kd3c1" COPASIkey="ModelValue_117"/>
    <SBMLMap SBMLid="kd3f6" COPASIkey="ModelValue_116"/>
    <SBMLMap SBMLid="kd3pds_p_p" COPASIkey="ModelValue_115"/>
    <SBMLMap SBMLid="kdb2_p" COPASIkey="ModelValue_114"/>
    <SBMLMap SBMLid="kdb2_p_p" COPASIkey="ModelValue_113"/>
    <SBMLMap SBMLid="kdb2p" COPASIkey="ModelValue_112"/>
    <SBMLMap SBMLid="kdb5_p" COPASIkey="ModelValue_111"/>
    <SBMLMap SBMLid="kdb5_p_p" COPASIkey="ModelValue_110"/>
    <SBMLMap SBMLid="kdbud" COPASIkey="ModelValue_109"/>
    <SBMLMap SBMLid="kdcdh" COPASIkey="ModelValue_108"/>
    <SBMLMap SBMLid="kdib2" COPASIkey="ModelValue_107"/>
    <SBMLMap SBMLid="kdib5" COPASIkey="ModelValue_106"/>
    <SBMLMap SBMLid="kdiesp" COPASIkey="ModelValue_105"/>
    <SBMLMap SBMLid="kdif2" COPASIkey="ModelValue_104"/>
    <SBMLMap SBMLid="kdif5" COPASIkey="ModelValue_103"/>
    <SBMLMap SBMLid="kdirent" COPASIkey="ModelValue_102"/>
    <SBMLMap SBMLid="kdirentp" COPASIkey="ModelValue_101"/>
    <SBMLMap SBMLid="kdn2" COPASIkey="ModelValue_100"/>
    <SBMLMap SBMLid="kdnet" COPASIkey="ModelValue_99"/>
    <SBMLMap SBMLid="kdori" COPASIkey="ModelValue_98"/>
    <SBMLMap SBMLid="kdppx_p" COPASIkey="ModelValue_97"/>
    <SBMLMap SBMLid="kdppx_p_p" COPASIkey="ModelValue_96"/>
    <SBMLMap SBMLid="kdspn" COPASIkey="ModelValue_95"/>
    <SBMLMap SBMLid="kdswi" COPASIkey="ModelValue_94"/>
    <SBMLMap SBMLid="ki15" COPASIkey="ModelValue_91"/>
    <SBMLMap SBMLid="kicdh_p" COPASIkey="ModelValue_90"/>
    <SBMLMap SBMLid="kicdh_p_p" COPASIkey="ModelValue_89"/>
    <SBMLMap SBMLid="kiiep" COPASIkey="ModelValue_88"/>
    <SBMLMap SBMLid="kimcm" COPASIkey="ModelValue_87"/>
    <SBMLMap SBMLid="kisbf_p" COPASIkey="ModelValue_86"/>
    <SBMLMap SBMLid="kisbf_p_p" COPASIkey="ModelValue_85"/>
    <SBMLMap SBMLid="kiswi" COPASIkey="ModelValue_84"/>
    <SBMLMap SBMLid="kkpnet_p" COPASIkey="ModelValue_83"/>
    <SBMLMap SBMLid="kkpnet_p_p" COPASIkey="ModelValue_82"/>
    <SBMLMap SBMLid="kppc1" COPASIkey="ModelValue_81"/>
    <SBMLMap SBMLid="kppf6" COPASIkey="ModelValue_80"/>
    <SBMLMap SBMLid="kppnet_p" COPASIkey="ModelValue_79"/>
    <SBMLMap SBMLid="kppnet_p_p" COPASIkey="ModelValue_78"/>
    <SBMLMap SBMLid="ks14" COPASIkey="ModelValue_77"/>
    <SBMLMap SBMLid="ks1pds_p_p" COPASIkey="ModelValue_76"/>
    <SBMLMap SBMLid="ks20_p" COPASIkey="ModelValue_75"/>
    <SBMLMap SBMLid="ks20_p_p" COPASIkey="ModelValue_74"/>
    <SBMLMap SBMLid="ks2pds_p_p" COPASIkey="ModelValue_73"/>
    <SBMLMap SBMLid="ksb2_p" COPASIkey="ModelValue_72"/>
    <SBMLMap SBMLid="ksb2_p_p" COPASIkey="ModelValue_71"/>
    <SBMLMap SBMLid="ksb5_p" COPASIkey="ModelValue_70"/>
    <SBMLMap SBMLid="ksb5_p_p" COPASIkey="ModelValue_69"/>
    <SBMLMap SBMLid="ksbud" COPASIkey="ModelValue_68"/>
    <SBMLMap SBMLid="ksc1_p" COPASIkey="ModelValue_67"/>
    <SBMLMap SBMLid="ksc1_p_p" COPASIkey="ModelValue_66"/>
    <SBMLMap SBMLid="kscdh" COPASIkey="ModelValue_65"/>
    <SBMLMap SBMLid="ksf6_p" COPASIkey="ModelValue_64"/>
    <SBMLMap SBMLid="ksf6_p_p" COPASIkey="ModelValue_63"/>
    <SBMLMap SBMLid="ksf6_p_p_p" COPASIkey="ModelValue_62"/>
    <SBMLMap SBMLid="ksn2_p" COPASIkey="ModelValue_61"/>
    <SBMLMap SBMLid="ksn2_p_p" COPASIkey="ModelValue_60"/>
    <SBMLMap SBMLid="ksnet" COPASIkey="ModelValue_59"/>
    <SBMLMap SBMLid="ksori" COPASIkey="ModelValue_58"/>
    <SBMLMap SBMLid="kspds_p" COPASIkey="ModelValue_57"/>
    <SBMLMap SBMLid="ksppx" COPASIkey="ModelValue_56"/>
    <SBMLMap SBMLid="ksspn" COPASIkey="ModelValue_55"/>
    <SBMLMap SBMLid="ksswi_p" COPASIkey="ModelValue_54"/>
    <SBMLMap SBMLid="ksswi_p_p" COPASIkey="ModelValue_53"/>
    <SBMLMap SBMLid="lte1h" COPASIkey="ModelValue_52"/>
    <SBMLMap SBMLid="lte1l" COPASIkey="ModelValue_51"/>
    <SBMLMap SBMLid="mad2h" COPASIkey="ModelValue_50"/>
    <SBMLMap SBMLid="mad2l" COPASIkey="ModelValue_49"/>
    <SBMLMap SBMLid="mdt" COPASIkey="ModelValue_48"/>
    <SBMLMap SBMLid="mu" COPASIkey="ModelValue_45"/>
    <SBMLMap SBMLid="parameter_1" COPASIkey="ModelValue_26"/>
  </SBMLReference>
</COPASI>
