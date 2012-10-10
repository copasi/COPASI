<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.9.37+ (Debug) (http://www.copasi.org) at 2012-10-09 17:49:04 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="9" versionDevel="37" copasiSourcesModified="1">
  <ListOfFunctions>
    <Function key="Function_46" name="GK" type="UserDefined" reversible="unspecified">
      <Expression>
        2*A4*A1/(A2-A1+A3*A2+A4*A1+((A2-A1+A3*A2+A4*A1)^2-4*(A2-A1)*A4*A1)^(1/2))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_502" name="A1" order="0" role="variable"/>
        <ParameterDescription key="FunctionParameter_500" name="A2" order="1" role="variable"/>
        <ParameterDescription key="FunctionParameter_498" name="A3" order="2" role="variable"/>
        <ParameterDescription key="FunctionParameter_504" name="A4" order="3" role="variable"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_47" name="Mass_Action_1" type="UserDefined" reversible="unspecified">
      <Expression>
        k1*S1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_497" name="k1" order="0" role="variable"/>
        <ParameterDescription key="FunctionParameter_501" name="S1" order="1" role="variable"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_48" name="Mass_Action_2" type="UserDefined" reversible="unspecified">
      <Expression>
        k1*S1*S2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_503" name="k1" order="0" role="variable"/>
        <ParameterDescription key="FunctionParameter_496" name="S1" order="1" role="variable"/>
        <ParameterDescription key="FunctionParameter_494" name="S2" order="2" role="variable"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_49" name="Michaelis-Menten" type="UserDefined" reversible="unspecified">
      <Expression>
        k1*S1*M1/(J1+S1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_491" name="M1" order="0" role="variable"/>
        <ParameterDescription key="FunctionParameter_489" name="J1" order="1" role="variable"/>
        <ParameterDescription key="FunctionParameter_493" name="k1" order="2" role="variable"/>
        <ParameterDescription key="FunctionParameter_499" name="S1" order="3" role="variable"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_50" name="function_4_Synthesis of CLN2" type="UserDefined" reversible="false">
      <Expression>
        (ksn2_p+ksn2_p_p*(SBF*cell))*MASS
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_483" name="MASS" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_487" name="SBF" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_485" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_488" name="ksn2_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_492" name="ksn2_p_p" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_51" name="function_4_Degradation of CLN2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdn2,CLN2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_486" name="CLN2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_490" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_482" name="kdn2" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_52" name="function_4_Synthesis of CLB2" type="UserDefined" reversible="false">
      <Expression>
        (ksb2_p+ksb2_p_p*(MCM1*cell))*MASS
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_475" name="MASS" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_479" name="MCM1" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_477" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_481" name="ksb2_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_484" name="ksb2_p_p" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_53" name="function_4_Degradation of CLB2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,CLB2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_478" name="CLB2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_474" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_495" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_54" name="function_4_Synthesis of CLB5" type="UserDefined" reversible="false">
      <Expression>
        (ksb5_p+ksb5_p_p*(SBF*cell))*MASS
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_467" name="MASS" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_471" name="SBF" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_469" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_473" name="ksb5_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_476" name="ksb5_p_p" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_55" name="function_4_Degradation of CLB5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,CLB5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_470" name="CLB5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_466" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_480" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_56" name="function_4_Synthesis of SIC1" type="UserDefined" reversible="false">
      <Expression>
        (ksc1_p+ksc1_p_p*(SWI5*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_463" name="SWI5" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_461" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_465" name="ksc1_p" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_468" name="ksc1_p_p" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_57" name="function_4_Phosphorylation of SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpc1,SIC1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_464" name="SIC1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_460" name="Vkpc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_459" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_58" name="function_4_Dephosphorylation of SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppc1,SIC1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_462" name="SIC1P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_458" name="Vppc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_456" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_59" name="function_4_Fast Degradation of SIC1P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3c1,SIC1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_472" name="SIC1P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_453" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_455" name="kd3c1" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_60" name="function_4_Assoc. of CLB2 and SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasb2,CLB2*cell,SIC1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_457" name="CLB2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_448" name="SIC1" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_450" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_452" name="kasb2" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_61" name="function_4_Dissoc. of CLB2/SIC1 complex" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdib2,C2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_451" name="C2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_446" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_447" name="kdib2" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_62" name="function_4_Assoc. of CLB5 and SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasb5,CLB5*cell,SIC1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_449" name="CLB5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_441" name="SIC1" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_443" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_445" name="kasb5" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_63" name="function_4_Dissoc. of CLB5/SIC1" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdib5,C5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_444" name="C5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_439" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_440" name="kdib5" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_64" name="function_4_Phosphorylation of C2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpc1,C2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_442" name="C2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_438" name="Vkpc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_436" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_65" name="function_4_Dephosphorylation of C2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppc1,C2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_454" name="C2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_435" name="Vppc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_433" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_66" name="function_4_Phosphorylation of C5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpc1,C5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_437" name="C5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_432" name="Vkpc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_430" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_67" name="function_4_Dephosphorylation of C5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppc1,C5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_434" name="C5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_429" name="Vppc1" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_427" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_68" name="function_4_Degradation of CLB2 in C2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,C2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_431" name="C2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_426" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_424" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_69" name="function_4_Degradation of CLB5 in C5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,C5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_428" name="C5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_423" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_421" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_70" name="function_4_Degradation of SIC1 in C2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3c1,C2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_425" name="C2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_418" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_420" name="kd3c1" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_71" name="function_4_Degradation of SIC1P in C5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3c1,C5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_422" name="C5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_415" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_417" name="kd3c1" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_72" name="function_4_Degradation of CLB2 in C2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,C2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_419" name="C2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_414" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_412" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_73" name="function_4_Degradation of CLB5 in C5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,C5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_416" name="C5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_411" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_409" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_74" name="function_4_CDC6 synthesis" type="UserDefined" reversible="false">
      <Expression>
        (ksf6_p+ksf6_p_p*(SWI5*cell)+ksf6_p_p_p*(SBF*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_400" name="SBF" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_406" name="SWI5" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_404" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_408" name="ksf6_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_413" name="ksf6_p_p" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_402" name="ksf6_p_p_p" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_75" name="function_4_Phosphorylation of CDC6" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpf6,CDC6*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_403" name="CDC6" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_399" name="Vkpf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_407" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_76" name="function_4_Dephosphorylation of CDC6" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppf6,CDC6P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_401" name="CDC6P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_410" name="Vppf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_397" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_77" name="function_4_Degradation of CDC6P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3f6,CDC6P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_405" name="CDC6P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_394" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_396" name="kd3f6" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_78" name="function_4_CLB2/CDC6 complex formation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasf2,CLB2*cell,CDC6*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_389" name="CDC6" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_398" name="CLB2" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_391" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_393" name="kasf2" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_79" name="function_4_CLB2/CDC6 dissociation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdif2,F2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_392" name="F2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_387" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_388" name="kdif2" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_80" name="function_4_CLB5/CDC6 complex formation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasf5,CLB5*cell,CDC6*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_382" name="CDC6" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_390" name="CLB5" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_384" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_386" name="kasf5" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_81" name="function_4_CLB5/CDC6 dissociation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdif5,F5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_385" name="F5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_380" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_381" name="kdif5" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_82" name="function_4_F2 phosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpf6,F2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_383" name="F2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_379" name="Vkpf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_377" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_83" name="function_4_F2P dephosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppf6,F2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_395" name="F2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_376" name="Vppf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_374" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_84" name="function_4_F5 phosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpf6,F5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_378" name="F5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_373" name="Vkpf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_371" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_85" name="function_4_F5P dephosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppf6,F5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_375" name="F5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_370" name="Vppf6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_368" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_86" name="function_4_CLB2 degradation in F2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,F2*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_372" name="F2" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_367" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_365" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_87" name="function_4_CLB5 degradation in F5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,F5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_369" name="F5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_352" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_336" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_88" name="function_4_CDC6 degradation in F2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3f6,F2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_366" name="F2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_358" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_342" name="kd3f6" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_89" name="function_4_CDC6 degradation in F5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd3f6,F5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_348" name="F5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_364" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_360" name="kd3f6" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_90" name="function_4_CLB2 degradation in F2P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb2,F2P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_356" name="F2P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_326" name="Vdb2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_324" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_91" name="function_4_CLB5 degradation in F5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdb5,F5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_362" name="F5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_323" name="Vdb5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_321" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_92" name="function_4_Synthesis of SWI5" type="UserDefined" reversible="false">
      <Expression>
        (ksswi_p+ksswi_p_p*(MCM1*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_318" name="MCM1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_316" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_320" name="ksswi_p" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_325" name="ksswi_p_p" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_93" name="function_4_Degradation of SWI5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdswi,SWI5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_319" name="SWI5" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_314" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_315" name="kdswi" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_94" name="function_4_Degradation of SWI5P" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdswi,SWI5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_317" name="SWI5P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_311" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_313" name="kdswi" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_95" name="function_4_Activation of SWI5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kaswi*(CDC14*cell),SWI5P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_322" name="CDC14" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_306" name="SWI5P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_308" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_310" name="kaswi" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_96" name="function_4_Inactivation of SWI5" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kiswi*(CLB2*cell),SWI5*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_309" name="CLB2" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_302" name="SWI5" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_304" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_305" name="kiswi" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_97" name="function_4_Activation of IEP" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(Vaiep,Jaiep,1,IE*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_300" name="IE" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_312" name="Jaiep" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_301" name="Vaiep" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_298" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_98" name="function_4_Inactivation" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(1,Jiiep,kiiep,IEP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_296" name="IEP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_297" name="Jiiep" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_294" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_307" name="kiiep" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_99" name="function_4_Synthesis of inactive CDC20" type="UserDefined" reversible="false">
      <Expression>
        (ks20_p+ks20_p_p*(MCM1*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_292" name="MCM1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_290" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_293" name="ks20_p" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_303" name="ks20_p_p" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_100" name="function_4_Degradation of inactiveCDC20" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd20,CDC20i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_299" name="CDC20i" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_288" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_289" name="kd20" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_101" name="function_4_Degradation of active CDC20" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd20,CDC20*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_291" name="CDC20" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_285" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_287" name="kd20" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_102" name="function_4_Activation of CDC20" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(ka20_p+ka20_p_p*(IEP*cell),CDC20i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_278" name="CDC20i" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_282" name="IEP" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_280" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_284" name="ka20_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_295" name="ka20_p_p" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_103" name="function_4_Inactivation_2" type="UserDefined" reversible="false">
      <Expression>
        k*Mass_Action_1(MAD2*cell,CDC20*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_275" name="CDC20" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_281" name="MAD2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_286" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_277" name="k" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_104" name="function_4_CDH1 synthesis" type="UserDefined" reversible="false">
      <Expression>
        kscdh/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_283" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_274" name="kscdh" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_105" name="function_4_CDH1 degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdcdh,CDH1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_262" name="CDH1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_267" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_279" name="kdcdh" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_106" name="function_4_CDH1i degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdcdh,CDH1i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_276" name="CDH1i" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_506" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_246" name="kdcdh" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_107" name="function_4_CDH1i activation" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(Vacdh,Jacdh,1,CDH1i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_509" name="CDH1i" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_271" name="Jacdh" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_507" name="Vacdh" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_511" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_108" name="function_4_Inactivation_3" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(Vicdh,Jicdh,1,CDH1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_513" name="CDH1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_508" name="Jicdh" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_512" name="Vicdh" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_515" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_109" name="function_4_CDC14 synthesis" type="UserDefined" reversible="false">
      <Expression>
        ks14/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_505" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_516" name="ks14" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_110" name="function_4_CDC14 degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd14,CDC14*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_517" name="CDC14" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_519" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_510" name="kd14" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_111" name="function_4_Assoc. with NET1 to form RENT" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasrent,CDC14*cell,NET1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_514" name="CDC14" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_524" name="NET1" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_522" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_520" name="kasrent" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_112" name="function_4_Dissoc. from RENT" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdirent,RENT*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_521" name="RENT" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_526" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_525" name="kdirent" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_113" name="function_4_Assoc with NET1P to form RENTP" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasrentp,CDC14*cell,NET1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_523" name="CDC14" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_531" name="NET1P" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_529" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_527" name="kasrentp" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_114" name="function_4_Dissoc. from RENP" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdirentp,RENTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_528" name="RENTP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_533" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_532" name="kdirentp" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_115" name="function_4_Net1 synthesis" type="UserDefined" reversible="false">
      <Expression>
        ksnet/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_530" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_534" name="ksnet" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_116" name="function_4_Net1 degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdnet,NET1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_536" name="NET1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_538" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_535" name="kdnet" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_117" name="function_4_Net1P degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdnet,NET1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_518" name="NET1P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_541" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_539" name="kdnet" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_118" name="function_4_NET1 phosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpnet,NET1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_537" name="NET1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_542" name="Vkpnet" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_544" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_119" name="function_4_dephosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppnet,NET1P*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_540" name="NET1P" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_545" name="Vppnet" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_547" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_120" name="function_4_RENT phosphorylation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vkpnet,RENT*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_543" name="RENT" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_548" name="Vkpnet" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_550" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_121" name="function_4_dephosphorylation_2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vppnet,RENTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_546" name="RENTP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_551" name="Vppnet" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_553" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_122" name="function_4_Degradation of NET1 in RENT" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdnet,RENT*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_549" name="RENT" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_556" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_554" name="kdnet" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_123" name="function_4_Degradation of NET1P in RENTP" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdnet,RENTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_552" name="RENTP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_559" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_557" name="kdnet" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_124" name="function_4_Degradation of CDC14 in RENT" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd14,RENT*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_555" name="RENT" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_562" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_560" name="kd14" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_125" name="function_4_Degradation of CDC14 in RENTP" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kd14,RENTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_558" name="RENTP" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_565" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_563" name="kd14" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_126" name="function_4_TEM1 activation" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(LTE1*cell,Jatem,1,TEM1GDP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_568" name="Jatem" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_566" name="LTE1" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_570" name="TEM1GDP" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_561" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_127" name="function_4_inactivation" type="UserDefined" reversible="false">
      <Expression>
        &quot;Michaelis-Menten&quot;(BUB2*cell,Jitem,1,TEM1GTP*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_571" name="BUB2" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_572" name="Jitem" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_574" name="TEM1GTP" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_567" name="cell" order="3" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_128" name="function_4_CDC15 activation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(ka15_p*(TEM1GDP*cell)+ka15_p_p*(TEM1GTP*cell)+ka15p*(CDC14*cell),CDC15i*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_584" name="CDC14" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_586" name="CDC15i" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_564" name="TEM1GDP" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_580" name="TEM1GTP" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_576" name="cell" order="4" role="volume"/>
        <ParameterDescription key="FunctionParameter_575" name="ka15_p" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_578" name="ka15_p_p" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_582" name="ka15p" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_129" name="function_4_inactivation_2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(ki15,CDC15*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_583" name="CDC15" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_579" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_587" name="ki15" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_130" name="function_4_PPX synthesis" type="UserDefined" reversible="false">
      <Expression>
        ksppx/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_585" name="cell" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_577" name="ksppx" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_131" name="function_4_degradation" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdppx,PPX*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_573" name="PPX" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_569" name="Vdppx" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_589" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_132" name="function_4_PDS1 synthesis" type="UserDefined" reversible="false">
      <Expression>
        (kspds_p+ks1pds_p_p*(SBF*cell)+ks2pds_p_p*(MCM1*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_598" name="MCM1" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_592" name="SBF" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_594" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_581" name="ks1pds_p_p" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_596" name="ks2pds_p_p" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_590" name="kspds_p" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_133" name="function_4_degradation_2" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdpds,PDS1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_595" name="PDS1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_599" name="Vdpds" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_591" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_134" name="function_4_Degradation of PDS1 in PE" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(Vdpds,PE*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_597" name="PE" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_588" name="Vdpds" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_601" name="cell" order="2" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_135" name="function_4_Assoc. with ESP1 to form PE" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_2(kasesp,PDS1*cell,ESP1*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_606" name="ESP1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_593" name="PDS1" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_604" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_602" name="kasesp" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_136" name="function_4_Disso. from PE" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdiesp,PE*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_603" name="PE" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_608" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_607" name="kdiesp" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_137" name="function_4_DNA synthesis" type="UserDefined" reversible="false">
      <Expression>
        ksori*(eorib5*(CLB5*cell)+eorib2*(CLB2*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_617" name="CLB2" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_611" name="CLB5" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_613" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_615" name="eorib2" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_605" name="eorib5" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_609" name="ksori" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_138" name="function_4_Negative regulation of DNA synthesis" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdori,ORI*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_614" name="ORI" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_610" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_618" name="kdori" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_139" name="function_4_Budding" type="UserDefined" reversible="false">
      <Expression>
        ksbud*(ebudn2*(CLN2*cell)+ebudn3*(CLN3*cell)+ebudb5*(CLB5*cell))/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_630" name="CLB5" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_620" name="CLN2" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_626" name="CLN3" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_622" name="cell" order="3" role="volume"/>
        <ParameterDescription key="FunctionParameter_628" name="ebudb5" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_616" name="ebudn2" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_624" name="ebudn3" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_600" name="ksbud" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_140" name="function_4_Negative regulation of Cell budding" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdbud,BUD*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_627" name="BUD" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_623" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_631" name="kdbud" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_141" name="function_4_Spindle formation" type="UserDefined" reversible="false">
      <Expression>
        ksspn*CLB2/(Jspn+CLB2*cell)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_629" name="CLB2" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_612" name="Jspn" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_633" name="cell" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_621" name="ksspn" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_142" name="function_4_Spindle disassembly" type="UserDefined" reversible="false">
      <Expression>
        Mass_Action_1(kdspn,SPN*cell)/cell
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_619" name="SPN" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_635" name="cell" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_634" name="kdspn" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_143" name="function_4_Growth-hyperbolic" type="UserDefined" reversible="unspecified">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_143">
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
        <ParameterDescription key="FunctionParameter_636" name="activator" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_632" name="k" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_638" name="SUB" order="2" role="substrate"/>
        <ParameterDescription key="FunctionParameter_640" name="Kmsub" order="3" role="constant"/>
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
      <Compartment key="Compartment_2" name="cell" simulationType="fixed" dimensionality="3">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_2">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0005623" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_26" name="BCK2" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_26">
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
      <Metabolite key="Metabolite_25" name="BUB2" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_25">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P26448" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_24" name="BUD" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_24">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0007114" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_23" name="C2" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_23">
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
      <Metabolite key="Metabolite_22" name="C2P" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_22">
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
      <Metabolite key="Metabolite_21" name="C5" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_21">
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
      <Metabolite key="Metabolite_20" name="C5P" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_20">
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
      <Metabolite key="Metabolite_19" name="CDC14" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_19">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:Q00684" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_18" name="CDC14T" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_18">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:Q00684" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC14],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENT],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[RENTP],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_17" name="CDC15" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_17">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P27636" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_16" name="CDC15i" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_16">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P27636" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[CDC15T],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC15],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_15" name="CDC20" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_15">
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
      <Metabolite key="Metabolite_12" name="CDC20i" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_12">
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
      <Metabolite key="Metabolite_11" name="CDC6" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_11">
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
      <Metabolite key="Metabolite_10" name="CDC6P" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_10">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P09119" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_9" name="CDC6T" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_9">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P09119" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CDC6P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F2P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[F5P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_8" name="CDH1" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_8">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P53197" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_7" name="CDH1i" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_7">
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
      <Metabolite key="Metabolite_6" name="CKIT" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_6">
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
      <Metabolite key="Metabolite_5" name="CLB2" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_5">
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
      <Metabolite key="Metabolite_4" name="CLB2T" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_4">
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
      <Metabolite key="Metabolite_3" name="CLB5" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_3">
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
      <Metabolite key="Metabolite_2" name="CLB5T" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_2">
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
      <Metabolite key="Metabolite_1" name="CLN2" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_1">
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
      <Metabolite key="Metabolite_0" name="CLN3" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_0">
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
      <Metabolite key="Metabolite_27" name="ESP1" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_27">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:Q03018" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_28" name="F2" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_28">
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
      <Metabolite key="Metabolite_29" name="F2P" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_29">
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
      <Metabolite key="Metabolite_30" name="F5" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_30">
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
      <Metabolite key="Metabolite_31" name="F5P" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_31">
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
      <Metabolite key="Metabolite_32" name="IE" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_32">
    <CopasiMT:is rdf:resource="urn:miriam:obo.go:GO%3A0005680" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[IET],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[IEP],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_33" name="IEP" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_33">
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
      <Metabolite key="Metabolite_34" name="LTE1" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_34">
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
      <Metabolite key="Metabolite_35" name="MAD2" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_35">
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
      <Metabolite key="Metabolite_36" name="MASS" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_36">
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
      <Metabolite key="Metabolite_37" name="MCM1" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_37">
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
      <Metabolite key="Metabolite_38" name="NET1" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_38">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P47035" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_39" name="NET1P" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_39">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P47035" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_40" name="NET1T" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_40">
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
      <Metabolite key="Metabolite_41" name="ORI" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_41">
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
      <Metabolite key="Metabolite_42" name="PDS1" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_42">
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
      <Metabolite key="Metabolite_43" name="PE" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_43">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:Q03018" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[ESP1T],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ESP1],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_44" name="PPX" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_44">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38698" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_45" name="RENT" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_45">
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
      <Metabolite key="Metabolite_46" name="RENTP" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_46">
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
      <Metabolite key="Metabolite_47" name="SBF" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_47">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P11938" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          GK(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Vasbf],Reference=Value&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Visbf],Reference=Value&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jasbf],Reference=Value&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[Jisbf],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_48" name="SIC1" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_48">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38634" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_49" name="SIC1P" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_49">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38634" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_50" name="SIC1T" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_50">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38634" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[SIC1P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C2P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[C5P],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_51" name="SPN" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_51">
    <CopasiMT:is rdf:resource="urn:miriam:obo.go:GO%3A0051225" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_52" name="SWI5" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_52">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P08153" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_53" name="SWI5P" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_53">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P08153" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_54" name="TEM1GDP" simulationType="assignment" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_54">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38987" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[TEM1T],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[TEM1GTP],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_55" name="TEM1GTP" simulationType="reactions" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_55">
    <CopasiMT:is rdf:resource="urn:miriam:uniprot:P38987" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_56" name="GLU" simulationType="fixed" compartment="Compartment_2">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_56">
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
      <ModelValue key="ModelValue_27" name="b0" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_27">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_26" name="bub2h" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_26">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_25" name="bub2l" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_25">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_24" name="C0" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_24">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:17:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_23" name="CDC15T" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_23">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:17:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_22" name="Dn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_22">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_21" name="ebudb5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_21">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:04Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_20" name="ebudn2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_20">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:05Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_19" name="ebudn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_19">
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
      <ModelValue key="ModelValue_17" name="ec1b5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_16" name="ec1k2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_16">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_15" name="ec1n2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_15">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_14" name="ec1n3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_14">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_13" name="ef6b2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_13">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_12" name="ef6b5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_12">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:12Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_11" name="ef6k2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_11">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:13Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_10" name="ef6n2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_10">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_9" name="ef6n3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_8" name="eicdhb2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_8">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:15Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_7" name="eicdhb5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:16Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_6" name="eicdhn2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-05-07T16:15:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_5" name="eicdhn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:17Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_4" name="eorib2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:18Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_3" name="eorib5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:19Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_2" name="esbfb5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_2">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_1" name="esbfn2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_0" name="esbfn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_28" name="ESP1T" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_28">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:18:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_29" name="IET" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_29">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_30" name="J20ppx" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_30">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_31" name="Jacdh" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_31">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_32" name="Jaiep" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_32">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:37Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_33" name="Jamcm" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_33">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_34" name="Jasbf" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_34">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_35" name="Jatem" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_35">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_36" name="Jd2c1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_36">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_37" name="Jd2f6" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_37">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_38" name="Jicdh" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_38">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_39" name="Jiiep" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_39">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_40" name="Jimcm" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_41" name="Jisbf" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_41">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_42" name="Jitem" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_42">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_43" name="Jn3" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_43">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_44" name="Jpds" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_45" name="Jspn" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_45">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:48Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_46" name="ka15'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_46">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_47" name="ka15''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_47">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_48" name="ka15p" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_48">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_49" name="ka20'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_49">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_50" name="ka20''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_50">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_51" name="kacdh'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_51">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_52" name="kacdh''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_52">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:25Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_53" name="kaiep" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_53">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_54" name="kamcm" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_54">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_55" name="kasb2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_55">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_56" name="kasb5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_56">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_57" name="kasbf" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_57">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_58" name="kasesp" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_58">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:29Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_59" name="kasf2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_59">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_60" name="kasf5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_60">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_61" name="kasrent" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_61">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_62" name="kasrentp" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_62">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_63" name="kaswi" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_63">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_64" name="kd14" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_64">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_65" name="kd1c1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_65">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_66" name="kd1f6" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_66">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_67" name="kd1pds'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_67">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_68" name="kd20" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_68">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:36Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_69" name="kd2c1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_69">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_70" name="kd2f6" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_70">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_71" name="kd2pds''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_72" name="kd3c1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_72">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_73" name="kd3f6" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_73">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_74" name="kd3pds''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_74">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_75" name="kdb2'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_75">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:39Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_76" name="kdb2''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_76">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_77" name="kdb2p" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_77">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_78" name="kdb5'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_78">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_79" name="kdb5''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_80" name="kdbud" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_80">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:42Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_81" name="kdcdh" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_81">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:43Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_82" name="kdib2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_82">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_83" name="kdib5" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_83">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_84" name="kdiesp" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_85" name="kdif2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_85">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:44Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_86" name="kdif5" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_87" name="kdirent" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_88" name="kdirentp" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_89" name="kdn2" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_90" name="kdnet" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_91" name="kdori" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_92" name="kdppx'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_93" name="kdppx''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_94" name="kdspn" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_95" name="kdswi" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_96" name="KEZ" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_96">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T12:17:27Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_97" name="KEZ2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_97">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_98" name="ki15" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_99" name="kicdh'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_100" name="kicdh''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_100">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-02-21T01:11:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_101" name="kiiep" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_102" name="kimcm" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_103" name="kisbf'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_104" name="kisbf''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_105" name="kiswi" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_106" name="kkpnet'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_107" name="kkpnet''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_107">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2011-02-21T22:13:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_108" name="kppc1" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_109" name="kppf6" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_110" name="kppnet'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_111" name="kppnet''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_112" name="ks14" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_113" name="ks1pds''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_114" name="ks20'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_115" name="ks20''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_116" name="ks2pds''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_117" name="ksb2'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_118" name="ksb2''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_119" name="ksb5'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_120" name="ksb5''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_121" name="ksbud" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_122" name="ksc1'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_123" name="ksc1''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_124" name="kscdh" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_125" name="ksf6'" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_126" name="ksf6''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_126">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:47Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_127" name="ksf6'''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_128" name="ksn2'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_128">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:57:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_129" name="ksn2''" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_130" name="ksnet" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_130">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:30:47Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_131" name="ksori" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_131">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:27:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_132" name="kspds'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_132">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_133" name="ksppx" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_133">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:35Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_134" name="ksspn" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_134">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_135" name="ksswi'" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_135">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_136" name="ksswi''" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_136">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:33Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_137" name="lte1h" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_137">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:32Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_138" name="lte1l" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_138">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T13:31:54Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_139" name="mad2h" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_139">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_140" name="mad2l" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_140">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T10:53:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_141" name="mdt" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_141">
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
      <ModelValue key="ModelValue_142" name="TEM1T" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_142">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_143" name="D" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_143">
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
      <ModelValue key="ModelValue_144" name="mu" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_144">
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
      <ModelValue key="ModelValue_145" name="Vdb5" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_145">
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
      <ModelValue key="ModelValue_146" name="Vdb2" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_146">
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
      <ModelValue key="ModelValue_147" name="Vasbf" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_147">
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
      <ModelValue key="ModelValue_148" name="Visbf" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_148">
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
      <ModelValue key="ModelValue_149" name="Vkpc1" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_149">
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
      <ModelValue key="ModelValue_150" name="Vkpf6" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_150">
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
      <ModelValue key="ModelValue_151" name="Vacdh" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_151">
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
      <ModelValue key="ModelValue_152" name="Vicdh" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_152">
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
      <ModelValue key="ModelValue_153" name="Vppnet" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_153">
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
      <ModelValue key="ModelValue_154" name="Vkpnet" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_154">
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
      <ModelValue key="ModelValue_155" name="Vdppx" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_155">
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
      <ModelValue key="ModelValue_156" name="Vdpds" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_156">
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
      <ModelValue key="ModelValue_157" name="Vaiep" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_157">
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
      <ModelValue key="ModelValue_158" name="Vd2c1" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_158">
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
      <ModelValue key="ModelValue_159" name="Vd2f6" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_159">
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
      <ModelValue key="ModelValue_160" name="Vppc1" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_160">
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
      <ModelValue key="ModelValue_161" name="Vppf6" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_161">
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
      <ModelValue key="ModelValue_162" name="F" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_162">
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
      <ModelValue key="ModelValue_163" name="amount to particle factor" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_163">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T15:51:14Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_164" name="1stDivisionTime" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_164">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-03-16T16:10:40Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_165" name="mu2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_165">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-05-07T16:15:49Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_166" name="T0" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_166">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:28:50Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_167" name="Period" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_167">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T13:49:41Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_168" name="KmGLU" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_168">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2010-08-05T15:21:08Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_169" name="GLUconsumed" simulationType="ode">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_169">
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
      <ModelValue key="ModelValue_170" name="quantity_1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_170">
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
      <Reaction key="Reaction_46" name="Growth" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_46">
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
          <Substrate metabolite="Metabolite_56" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1133" name="k" value="0.0077"/>
          <Constant key="Parameter_1134" name="Kmsub" value="0.001"/>
        </ListOfConstants>
        <KineticLaw function="Function_143">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_636">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_632">
              <SourceParameter reference="ModelValue_165"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_638">
              <SourceParameter reference="Metabolite_56"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_640">
              <SourceParameter reference="ModelValue_168"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_45" name="Synthesis of CLN2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_45">
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
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_47" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1031" name="ksn2_p" value="1"/>
          <Constant key="Parameter_1032" name="ksn2_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_50">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_483">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_487">
              <SourceParameter reference="Metabolite_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_485">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_488">
              <SourceParameter reference="ModelValue_128"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_492">
              <SourceParameter reference="ModelValue_129"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_44" name="Degradation of CLN2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_44">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0008054" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1033" name="kdn2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_51">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_486">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_490">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_482">
              <SourceParameter reference="ModelValue_89"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_43" name="Synthesis of CLB2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_43">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_37" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1034" name="ksb2_p" value="1"/>
          <Constant key="Parameter_1035" name="ksb2_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_52">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_475">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_479">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_477">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_481">
              <SourceParameter reference="ModelValue_117"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_484">
              <SourceParameter reference="ModelValue_118"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_42" name="Degradation of CLB2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_42">
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
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1036" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_53">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_478">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_474">
              <SourceParameter reference="ModelValue_146"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_495">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_41" name="Synthesis of CLB5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_41">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_47" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1037" name="ksb5_p" value="1"/>
          <Constant key="Parameter_1038" name="ksb5_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_54">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_467">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_471">
              <SourceParameter reference="Metabolite_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_469">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_473">
              <SourceParameter reference="ModelValue_119"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_476">
              <SourceParameter reference="ModelValue_120"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_40" name="Degradation of CLB5" reversible="false">
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
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1039" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_55">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_470">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_466">
              <SourceParameter reference="ModelValue_145"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_480">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_39" name="Synthesis of SIC1" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_39">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1040" name="ksc1_p" value="1"/>
          <Constant key="Parameter_1041" name="ksc1_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_56">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_463">
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_461">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_465">
              <SourceParameter reference="ModelValue_122"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_468">
              <SourceParameter reference="ModelValue_123"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_38" name="Phosphorylation of SIC1" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_38">
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
          <Substrate metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1042" name="Vkpc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_57">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_464">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_460">
              <SourceParameter reference="ModelValue_149"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_459">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_37" name="Dephosphorylation of SIC1" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_37">
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
          <Substrate metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1043" name="Vppc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_58">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_462">
              <SourceParameter reference="Metabolite_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_458">
              <SourceParameter reference="ModelValue_160"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_456">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_36" name="Fast Degradation of SIC1P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_36">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1044" name="kd3c1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_59">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_472">
              <SourceParameter reference="Metabolite_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_453">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_455">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="Assoc. of CLB2 and SIC1" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_35">
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
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1045" name="kasb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_60">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_457">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_448">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_450">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_452">
              <SourceParameter reference="ModelValue_55"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_34" name="Dissoc. of CLB2/SIC1 complex" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_34">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1046" name="kdib2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_61">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_451">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_446">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_447">
              <SourceParameter reference="ModelValue_82"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_33" name="Assoc. of CLB5 and SIC1" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_33">
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
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1047" name="kasb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_62">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_449">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_441">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_443">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_445">
              <SourceParameter reference="ModelValue_56"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_32" name="Dissoc. of CLB5/SIC1" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_32">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1048" name="kdib5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_63">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_444">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_439">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_440">
              <SourceParameter reference="ModelValue_83"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="Phosphorylation of C2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_31">
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
          <Constant key="Parameter_1049" name="Vkpc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_64">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_442">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_438">
              <SourceParameter reference="ModelValue_149"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_436">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="Dephosphorylation of C2P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_30">
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
          <Constant key="Parameter_1050" name="Vppc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_65">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_454">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_435">
              <SourceParameter reference="ModelValue_160"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_433">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="Phosphorylation of C5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_29">
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
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1051" name="Vkpc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_66">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_437">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_432">
              <SourceParameter reference="ModelValue_149"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_430">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="Dephosphorylation of C5P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_28">
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
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1052" name="Vppc1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_67">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_434">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_429">
              <SourceParameter reference="ModelValue_160"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_427">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="Degradation of CLB2 in C2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_27">
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
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1053" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_68">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_431">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_426">
              <SourceParameter reference="ModelValue_146"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_424">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="Degradation of CLB5 in C5" reversible="false">
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
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1054" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_69">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_428">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_423">
              <SourceParameter reference="ModelValue_145"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_421">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="Degradation of SIC1 in C2P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_25">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1055" name="kd3c1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_70">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_425">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_418">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_420">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="Degradation of SIC1P in C5P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_24">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1056" name="kd3c1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_71">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_422">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_415">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_417">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="Degradation of CLB2 in C2P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_23">
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
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1057" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_72">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_419">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_414">
              <SourceParameter reference="ModelValue_146"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_412">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="Degradation of CLB5 in C5P" reversible="false">
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
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1058" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_73">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_416">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_411">
              <SourceParameter reference="ModelValue_145"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_409">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="CDC6 synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_21">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_52" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_47" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1059" name="ksf6_p" value="1"/>
          <Constant key="Parameter_1060" name="ksf6_p_p" value="1"/>
          <Constant key="Parameter_1061" name="ksf6_p_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_74">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_400">
              <SourceParameter reference="Metabolite_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_406">
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_404">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_408">
              <SourceParameter reference="ModelValue_125"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_413">
              <SourceParameter reference="ModelValue_126"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_402">
              <SourceParameter reference="ModelValue_127"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="Phosphorylation of CDC6" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_20">
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
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1062" name="Vkpf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_75">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_403">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_399">
              <SourceParameter reference="ModelValue_150"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_407">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="Dephosphorylation of CDC6" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_19">
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
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1063" name="Vppf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_76">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_401">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_410">
              <SourceParameter reference="ModelValue_161"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_397">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="Degradation of CDC6P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_18">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1064" name="kd3f6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_77">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_405">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_394">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_396">
              <SourceParameter reference="ModelValue_73"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="CLB2/CDC6 complex formation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_17">
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
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1065" name="kasf2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_78">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_389">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_398">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_391">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_393">
              <SourceParameter reference="ModelValue_59"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="CLB2/CDC6 dissociation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_16">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1066" name="kdif2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_79">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_392">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_387">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_388">
              <SourceParameter reference="ModelValue_85"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="CLB5/CDC6 complex formation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_15">
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
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1067" name="kasf5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_80">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_382">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_390">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_384">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_386">
              <SourceParameter reference="ModelValue_60"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="CLB5/CDC6 dissociation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_14">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1068" name="kdif5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_81">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_385">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_380">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_381">
              <SourceParameter reference="ModelValue_86"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="F2 phosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_13">
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
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1069" name="Vkpf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_82">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_383">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_379">
              <SourceParameter reference="ModelValue_150"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_377">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="F2P dephosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_12">
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
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1070" name="Vppf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_83">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_395">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_376">
              <SourceParameter reference="ModelValue_161"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_374">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="F5 phosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_11">
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
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1071" name="Vkpf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_84">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_378">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_373">
              <SourceParameter reference="ModelValue_150"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_371">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="F5P dephosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_10">
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
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1072" name="Vppf6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_85">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_375">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_370">
              <SourceParameter reference="ModelValue_161"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_368">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="CLB2 degradation in F2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_9">
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
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1073" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_86">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_372">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_367">
              <SourceParameter reference="ModelValue_146"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_365">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="CLB5 degradation in F5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_8">
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
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1074" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_87">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_369">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_352">
              <SourceParameter reference="ModelValue_145"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_336">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="CDC6 degradation in F2P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_7">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1075" name="kd3f6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_88">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_366">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_358">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_342">
              <SourceParameter reference="ModelValue_73"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="CDC6 degradation in F5P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_6">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1076" name="kd3f6" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_89">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_348">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_364">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_360">
              <SourceParameter reference="ModelValue_73"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="CLB2 degradation in F2P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_5">
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
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1077" name="Vdb2" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_90">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_356">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_326">
              <SourceParameter reference="ModelValue_146"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_324">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="CLB5 degradation in F5P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_4">
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
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1078" name="Vdb5" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_91">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_362">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_323">
              <SourceParameter reference="ModelValue_145"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="Synthesis of SWI5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_3">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1079" name="ksswi_p" value="1"/>
          <Constant key="Parameter_1080" name="ksswi_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_92">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="ModelValue_135"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_325">
              <SourceParameter reference="ModelValue_136"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="Degradation of SWI5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_2">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1081" name="kdswi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_93">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_314">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_315">
              <SourceParameter reference="ModelValue_95"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="Degradation of SWI5P" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_1">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1082" name="kdswi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_94">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_53"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_311">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="ModelValue_95"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_0" name="Activation of SWI5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
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
          <Substrate metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1083" name="kaswi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_95">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Metabolite_53"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_308">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_310">
              <SourceParameter reference="ModelValue_63"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_47" name="Inactivation of SWI5" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_47">
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
          <Substrate metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1084" name="kiswi" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_96">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_309">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_302">
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_304">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_305">
              <SourceParameter reference="ModelValue_105"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_48" name="Activation of IEP" reversible="false">
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
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1085" name="Jaiep" value="1"/>
          <Constant key="Parameter_1086" name="Vaiep" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_97">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_300">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="ModelValue_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_301">
              <SourceParameter reference="ModelValue_157"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_298">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_49" name="Inactivation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_49">
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
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1087" name="Jiiep" value="1"/>
          <Constant key="Parameter_1088" name="kiiep" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_98">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_296">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_297">
              <SourceParameter reference="ModelValue_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_294">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_307">
              <SourceParameter reference="ModelValue_101"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_50" name="Synthesis of inactive CDC20" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_50">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1089" name="ks20_p" value="1"/>
          <Constant key="Parameter_1090" name="ks20_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_99">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_292">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_290">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_293">
              <SourceParameter reference="ModelValue_114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_303">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_51" name="Degradation of inactiveCDC20" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_51">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1091" name="kd20" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_100">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_299">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_288">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_289">
              <SourceParameter reference="ModelValue_68"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_52" name="Degradation of active CDC20" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_52">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1092" name="kd20" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_101">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_291">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_285">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_287">
              <SourceParameter reference="ModelValue_68"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_53" name="Activation of CDC20" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_53">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0031536" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1093" name="ka20_p" value="1"/>
          <Constant key="Parameter_1094" name="ka20_p_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_102">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="ModelValue_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_295">
              <SourceParameter reference="ModelValue_50"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_54" name="Inactivation_2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_54">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0001100" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1095" name="k" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_103">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_281">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_286">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="Parameter_1095"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_55" name="CDH1 synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_55">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1096" name="kscdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_104">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_283">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="ModelValue_124"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_56" name="CDH1 degradation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_56">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1097" name="kdcdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_105">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_267">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_279">
              <SourceParameter reference="ModelValue_81"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_57" name="CDH1i degradation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_57">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1098" name="kdcdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_106">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_276">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_506">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_246">
              <SourceParameter reference="ModelValue_81"/>
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
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1099" name="Jacdh" value="1"/>
          <Constant key="Parameter_1100" name="Vacdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_107">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_509">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_271">
              <SourceParameter reference="ModelValue_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_507">
              <SourceParameter reference="ModelValue_151"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_511">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_59" name="Inactivation_3" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_59">
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
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1101" name="Jicdh" value="1"/>
          <Constant key="Parameter_1102" name="Vicdh" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_108">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_513">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_508">
              <SourceParameter reference="ModelValue_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_512">
              <SourceParameter reference="ModelValue_152"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_515">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_60" name="CDC14 synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_60">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1103" name="ks14" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_109">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_505">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_516">
              <SourceParameter reference="ModelValue_112"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_61" name="CDC14 degradation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_61">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1104" name="kd14" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_110">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_517">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_519">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_510">
              <SourceParameter reference="ModelValue_64"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_62" name="Assoc. with NET1 to form RENT" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_62">
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
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1105" name="kasrent" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_111">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_514">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_524">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_522">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_520">
              <SourceParameter reference="ModelValue_61"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_63" name="Dissoc. from RENT" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_63">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1106" name="kdirent" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_112">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_521">
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_526">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_525">
              <SourceParameter reference="ModelValue_87"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_64" name="Assoc with NET1P to form RENTP" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_64">
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
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1107" name="kasrentp" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_113">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_523">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_531">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_529">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_527">
              <SourceParameter reference="ModelValue_62"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_65" name="Dissoc. from RENP" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_65">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0043624" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
          <Product metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1108" name="kdirentp" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_114">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_528">
              <SourceParameter reference="Metabolite_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_533">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_532">
              <SourceParameter reference="ModelValue_88"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_66" name="Net1 synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_66">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1109" name="ksnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_115">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_530">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_534">
              <SourceParameter reference="ModelValue_130"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_67" name="Net1 degradation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_67">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1110" name="kdnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_116">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_536">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_538">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_535">
              <SourceParameter reference="ModelValue_90"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_68" name="Net1P degradation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_68">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1111" name="kdnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_117">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_518">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_541">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_539">
              <SourceParameter reference="ModelValue_90"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_69" name="NET1 phosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_69">
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
          <Substrate metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1112" name="Vkpnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_118">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_537">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_542">
              <SourceParameter reference="ModelValue_154"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_544">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_70" name="dephosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_70">
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
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1113" name="Vppnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_119">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_540">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_545">
              <SourceParameter reference="ModelValue_153"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_547">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_71" name="RENT phosphorylation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_71">
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
          <Substrate metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1114" name="Vkpnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_120">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_543">
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_548">
              <SourceParameter reference="ModelValue_154"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_550">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_72" name="dephosphorylation_2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_72">
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
          <Substrate metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1115" name="Vppnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_121">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_546">
              <SourceParameter reference="Metabolite_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_551">
              <SourceParameter reference="ModelValue_153"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_553">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_73" name="Degradation of NET1 in RENT" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_73">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1116" name="kdnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_122">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_549">
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_556">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_554">
              <SourceParameter reference="ModelValue_90"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_74" name="Degradation of NET1P in RENTP" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_74">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1117" name="kdnet" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_123">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_552">
              <SourceParameter reference="Metabolite_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_559">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_557">
              <SourceParameter reference="ModelValue_90"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_75" name="Degradation of CDC14 in RENT" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_75">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1118" name="kd14" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_124">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_555">
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_562">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_560">
              <SourceParameter reference="ModelValue_64"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_76" name="Degradation of CDC14 in RENTP" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_76">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1119" name="kd14" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_125">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_558">
              <SourceParameter reference="Metabolite_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_565">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_563">
              <SourceParameter reference="ModelValue_64"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_77" name="TEM1 activation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_77">
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
          <Substrate metabolite="Metabolite_54" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1120" name="Jatem" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_126">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_568">
              <SourceParameter reference="ModelValue_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_566">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_570">
              <SourceParameter reference="Metabolite_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_561">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_78" name="inactivation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_78">
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
          <Substrate metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_54" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1121" name="Jitem" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_127">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_571">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_572">
              <SourceParameter reference="ModelValue_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_574">
              <SourceParameter reference="Metabolite_55"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_567">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_79" name="CDC15 activation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_79">
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
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_54" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_55" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1122" name="ka15_p" value="1"/>
          <Constant key="Parameter_1123" name="ka15_p_p" value="1"/>
          <Constant key="Parameter_1124" name="ka15p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_128">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_584">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_586">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_564">
              <SourceParameter reference="Metabolite_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_580">
              <SourceParameter reference="Metabolite_55"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_576">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_575">
              <SourceParameter reference="ModelValue_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_578">
              <SourceParameter reference="ModelValue_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_582">
              <SourceParameter reference="ModelValue_48"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_80" name="inactivation_2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_80">
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
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1125" name="ki15" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_129">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_583">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_579">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_587">
              <SourceParameter reference="ModelValue_98"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_81" name="PPX synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_81">
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
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1126" name="ksppx" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_130">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_585">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_577">
              <SourceParameter reference="ModelValue_133"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_82" name="degradation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_82">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0030163" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1127" name="Vdppx" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_131">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_573">
              <SourceParameter reference="Metabolite_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_569">
              <SourceParameter reference="ModelValue_155"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_589">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_83" name="PDS1 synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_83">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0006412" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_47" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1128" name="ks1pds_p_p" value="1"/>
          <Constant key="Parameter_1129" name="ks2pds_p_p" value="1"/>
          <Constant key="Parameter_1130" name="kspds_p" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_132">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_598">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_592">
              <SourceParameter reference="Metabolite_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_594">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_581">
              <SourceParameter reference="ModelValue_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_596">
              <SourceParameter reference="ModelValue_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_590">
              <SourceParameter reference="ModelValue_132"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_84" name="degradation_2" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_84">
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
          <Substrate metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1131" name="Vdpds" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_133">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_595">
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_599">
              <SourceParameter reference="ModelValue_156"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_591">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_85" name="Degradation of PDS1 in PE" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_85">
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
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1132" name="Vdpds" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_134">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_597">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_588">
              <SourceParameter reference="ModelValue_156"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_601">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_86" name="Assoc. with ESP1 to form PE" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_86">
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
          <Substrate metabolite="Metabolite_42" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1147" name="kasesp" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_135">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_606">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_593">
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_604">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_602">
              <SourceParameter reference="ModelValue_58"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_87" name="Disso. from PE" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_87">
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
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_42" stoichiometry="1"/>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1146" name="kdiesp" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_136">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_603">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_608">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_607">
              <SourceParameter reference="ModelValue_84"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_88" name="DNA synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_88">
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
          <Product metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1145" name="eorib2" value="1"/>
          <Constant key="Parameter_1144" name="eorib5" value="1"/>
          <Constant key="Parameter_1143" name="ksori" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_137">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_617">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_611">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_613">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_615">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_605">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_609">
              <SourceParameter reference="ModelValue_131"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_89" name="Negative regulation of DNA synthesis" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_89">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0008156" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1142" name="kdori" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_138">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_614">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_610">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_618">
              <SourceParameter reference="ModelValue_91"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_90" name="Budding" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_90">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0045782" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_1" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_0" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1141" name="ebudb5" value="1"/>
          <Constant key="Parameter_1140" name="ebudn2" value="1"/>
          <Constant key="Parameter_1139" name="ebudn3" value="1"/>
          <Constant key="Parameter_1138" name="ksbud" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_139">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_630">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_620">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_626">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_622">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_628">
              <SourceParameter reference="ModelValue_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_616">
              <SourceParameter reference="ModelValue_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_624">
              <SourceParameter reference="ModelValue_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_600">
              <SourceParameter reference="ModelValue_121"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_91" name="Negative regulation of Cell budding" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_91">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0045781" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1137" name="kdbud" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_140">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_627">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_623">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_631">
              <SourceParameter reference="ModelValue_80"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_92" name="Spindle formation" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_92">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0051225" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_1136" name="Jspn" value="1"/>
          <Constant key="Parameter_1135" name="ksspn" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_141">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_629">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_612">
              <SourceParameter reference="ModelValue_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_633">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_621">
              <SourceParameter reference="ModelValue_134"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_93" name="Spindle disassembly" reversible="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_93">
    <CopasiMT:isVersionOf rdf:resource="urn:miriam:obo.go:GO%3A0051228" />
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_1517" name="kdspn" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_142">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_619">
              <SourceParameter reference="Metabolite_51"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_635">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_634">
              <SourceParameter reference="ModelValue_94"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfEvents>
      <Event key="Event_1" name="reset ORI" fireAtInitialTime="0" persistentTrigger="0">
        <TriggerExpression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB2],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;+&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[CLB5],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[KEZ2],Reference=Value&gt; lt 0
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="Metabolite_41">
            <Expression>
              0/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_2" name="start DNA synthesis" fireAtInitialTime="0" persistentTrigger="0">
        <TriggerExpression>
          &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[ORI],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;-1 gt 0
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="Metabolite_35">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mad2h],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_25">
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
          <Assignment targetKey="Metabolite_35">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[mad2l],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_34">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[lte1h],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_25">
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
          <Assignment targetKey="Metabolite_36">
            <Expression>
              (1-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[F],Reference=Value&gt;)*(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Vector=Metabolites[MASS],Reference=ParticleNumber&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[amount to particle factor],Reference=Value&gt;)/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_34">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[lte1l],Reference=Value&gt;/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_24">
            <Expression>
              0/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="Metabolite_51">
            <Expression>
              0/&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Compartments[cell],Reference=Volume&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_164">
            <Expression>
              if(&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[1stDivisionTime],Reference=Value&gt; lt 0,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time&gt;,&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[1stDivisionTime],Reference=Value&gt;)
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_167">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time&gt;-&lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Vector=Values[T0],Reference=Value&gt;
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_166">
            <Expression>
              &lt;CN=Root,Model=Chen2004_CellCycle Mother with GLU,Reference=Time&gt;
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
    </ListOfEvents>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_1"/>
      <StateTemplateVariable objectReference="ModelValue_169"/>
      <StateTemplateVariable objectReference="Metabolite_11"/>
      <StateTemplateVariable objectReference="Metabolite_48"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_38"/>
      <StateTemplateVariable objectReference="Metabolite_46"/>
      <StateTemplateVariable objectReference="Metabolite_10"/>
      <StateTemplateVariable objectReference="Metabolite_49"/>
      <StateTemplateVariable objectReference="Metabolite_8"/>
      <StateTemplateVariable objectReference="Metabolite_42"/>
      <StateTemplateVariable objectReference="Metabolite_12"/>
      <StateTemplateVariable objectReference="Metabolite_52"/>
      <StateTemplateVariable objectReference="Metabolite_39"/>
      <StateTemplateVariable objectReference="Metabolite_20"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_22"/>
      <StateTemplateVariable objectReference="Metabolite_31"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="Metabolite_28"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_41"/>
      <StateTemplateVariable objectReference="Metabolite_44"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="Metabolite_24"/>
      <StateTemplateVariable objectReference="Metabolite_51"/>
      <StateTemplateVariable objectReference="Metabolite_55"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_53"/>
      <StateTemplateVariable objectReference="Metabolite_27"/>
      <StateTemplateVariable objectReference="Metabolite_45"/>
      <StateTemplateVariable objectReference="Metabolite_30"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="Metabolite_36"/>
      <StateTemplateVariable objectReference="Metabolite_26"/>
      <StateTemplateVariable objectReference="Metabolite_16"/>
      <StateTemplateVariable objectReference="Metabolite_0"/>
      <StateTemplateVariable objectReference="Metabolite_32"/>
      <StateTemplateVariable objectReference="Metabolite_37"/>
      <StateTemplateVariable objectReference="Metabolite_43"/>
      <StateTemplateVariable objectReference="Metabolite_47"/>
      <StateTemplateVariable objectReference="Metabolite_54"/>
      <StateTemplateVariable objectReference="ModelValue_145"/>
      <StateTemplateVariable objectReference="ModelValue_146"/>
      <StateTemplateVariable objectReference="ModelValue_147"/>
      <StateTemplateVariable objectReference="ModelValue_148"/>
      <StateTemplateVariable objectReference="ModelValue_149"/>
      <StateTemplateVariable objectReference="ModelValue_150"/>
      <StateTemplateVariable objectReference="ModelValue_151"/>
      <StateTemplateVariable objectReference="ModelValue_152"/>
      <StateTemplateVariable objectReference="ModelValue_153"/>
      <StateTemplateVariable objectReference="ModelValue_154"/>
      <StateTemplateVariable objectReference="ModelValue_155"/>
      <StateTemplateVariable objectReference="ModelValue_156"/>
      <StateTemplateVariable objectReference="ModelValue_157"/>
      <StateTemplateVariable objectReference="ModelValue_158"/>
      <StateTemplateVariable objectReference="ModelValue_159"/>
      <StateTemplateVariable objectReference="ModelValue_160"/>
      <StateTemplateVariable objectReference="ModelValue_161"/>
      <StateTemplateVariable objectReference="Metabolite_18"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_6"/>
      <StateTemplateVariable objectReference="Metabolite_4"/>
      <StateTemplateVariable objectReference="Metabolite_2"/>
      <StateTemplateVariable objectReference="Metabolite_40"/>
      <StateTemplateVariable objectReference="Metabolite_50"/>
      <StateTemplateVariable objectReference="ModelValue_141"/>
      <StateTemplateVariable objectReference="ModelValue_143"/>
      <StateTemplateVariable objectReference="ModelValue_144"/>
      <StateTemplateVariable objectReference="ModelValue_162"/>
      <StateTemplateVariable objectReference="Metabolite_56"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Metabolite_34"/>
      <StateTemplateVariable objectReference="Metabolite_35"/>
      <StateTemplateVariable objectReference="Compartment_2"/>
      <StateTemplateVariable objectReference="ModelValue_27"/>
      <StateTemplateVariable objectReference="ModelValue_26"/>
      <StateTemplateVariable objectReference="ModelValue_25"/>
      <StateTemplateVariable objectReference="ModelValue_24"/>
      <StateTemplateVariable objectReference="ModelValue_23"/>
      <StateTemplateVariable objectReference="ModelValue_22"/>
      <StateTemplateVariable objectReference="ModelValue_21"/>
      <StateTemplateVariable objectReference="ModelValue_20"/>
      <StateTemplateVariable objectReference="ModelValue_19"/>
      <StateTemplateVariable objectReference="ModelValue_18"/>
      <StateTemplateVariable objectReference="ModelValue_17"/>
      <StateTemplateVariable objectReference="ModelValue_16"/>
      <StateTemplateVariable objectReference="ModelValue_15"/>
      <StateTemplateVariable objectReference="ModelValue_14"/>
      <StateTemplateVariable objectReference="ModelValue_13"/>
      <StateTemplateVariable objectReference="ModelValue_12"/>
      <StateTemplateVariable objectReference="ModelValue_11"/>
      <StateTemplateVariable objectReference="ModelValue_10"/>
      <StateTemplateVariable objectReference="ModelValue_9"/>
      <StateTemplateVariable objectReference="ModelValue_8"/>
      <StateTemplateVariable objectReference="ModelValue_7"/>
      <StateTemplateVariable objectReference="ModelValue_6"/>
      <StateTemplateVariable objectReference="ModelValue_5"/>
      <StateTemplateVariable objectReference="ModelValue_4"/>
      <StateTemplateVariable objectReference="ModelValue_3"/>
      <StateTemplateVariable objectReference="ModelValue_2"/>
      <StateTemplateVariable objectReference="ModelValue_1"/>
      <StateTemplateVariable objectReference="ModelValue_0"/>
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
      <StateTemplateVariable objectReference="ModelValue_142"/>
      <StateTemplateVariable objectReference="ModelValue_163"/>
      <StateTemplateVariable objectReference="ModelValue_164"/>
      <StateTemplateVariable objectReference="ModelValue_165"/>
      <StateTemplateVariable objectReference="ModelValue_166"/>
      <StateTemplateVariable objectReference="ModelValue_167"/>
      <StateTemplateVariable objectReference="ModelValue_168"/>
      <StateTemplateVariable objectReference="ModelValue_170"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 1.747366772326145e+23 6.153793596801723e+22 1.80535936470497e+23 9.253339255958898e+21 3.888445993186847e+21 2.019185755329673e+22 1.964083420555222e+23 6.987702526155101e+21 3.151195626929545e+21 6.004823451606606e+23 1.093220582617616e+22 6.649934635684339e+23 5.446744061809811e+23 6.421153989171979e+23 2.307420732690804e+21 5.07527926009403e+21 5.428453477226389e+21 2.417387190365045e+18 6.3287734055348e+22 1.056512290096014e+23 2.196294727685002e+22 2.879579509269514e+22 5.793351133464459e+22 7.235672544851775e+22 3.817302580975657e+23 9.000829013319018e+21 3.305249612645038e+22 4.758414978992805e+23 2.29204033134851e+23 1.731804839342614e+21 7.393161906544548e+21 2.159777877052535e+23 8.274840214739905e+23 6.000645303884879e+19 1.415750029349605e+23 5.128887707846334e+23 2.769599495608814e+22 2.204839025199744e+23 2.994240326851319e+22 5.802512306655105e+23 6.177544327875697e+21 3.862363808942007e+23 7.496745791131755e+21 1.263726581862738e+23 0.07089635273693944 0.4589400389952509 0.4049488649158367 0.7229242355857484 0.06235613837299574 0.06275344891616547 0.2498295509602317 0.009132056532627379 0.410453463847625 0.3324302671175435 0.8999351532761245 0.1260054117516113 0.001536552944821854 0.02672503759551066 0.02826159054033252 1.199147754801158 1.199147754801158 1.20442835800001e+24 2.925133259548562e+23 5.698011095421221e+23 2.669833167945896e+23 6.954602797048728e+22 1.686199701200007e+24 2.772877561481376e+23 104.9622873419346 123.3657142857143 0.006603773584905661 0.4427813287861195 1.204428358e+21 1.204428300000005e+23 6.022141500000027e+22 6.022141499999998e+21 1 0.054 1 0.2 0.4 1 1 1 0.25 0.05 0.45 0.1 0.03 0.06 0.3 0.55 0.1 0.03 0.06 0.3 1.2 8 0.4 0.25 0.45 0.9 2 2 10 1 1 0.15 0.03 0.1 0.1 0.01 0.1 0.05 0.05 0.03 0.1 0.1 0.01 0.1 6 0.04 0.14 0.002 1 0.001 0.05 0.2 0.01 0.8 0.1 1 50 50 0.38 50 15 0.01 200 1 2 0.1 0.01 0.01 0.01 0.3 1 1 0.2 1 1 0.04 0.003 0.4 0.15 0.01 0.16 0.06 0.01 0.05 0.06 0.5 0.5 0.01 1 2 0.12 0.03 0.06 0.17 2 0.06 0.08 0.3 0.2 0.5 0.001 0.08 0.15 0.15 0.6 8 0.05 0.01 0.6 4 4 0.05 3 0.2 0.03 0.006 0.6 0.055 0.001 0.04 0.0008 0.005 0.2 0.012 0.12 0.01 0.024 0.12 0.004 0 0.15 0.08400000000000001 2 0 0.1 0.1 0.005 0.08 1 0.1 8 0.01 1 6.0221415e+23 -1 0.007 0 0 0.00012 0 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_27" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_19" target="" append="1" confirmOverwrite="0"/>
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
      <Report reference="Report_16" target="EventTest12.1.txt" append="0" confirmOverwrite="0"/>
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
      <Report reference="Report_9" target="" append="1" confirmOverwrite="0"/>
      <Problem>
      </Problem>
      <Method name="Bit Pattern Tree Algorithm" type="EFMBitPatternTreeMethod">
      </Method>
    </Task>
    <Task key="Task_18" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_10" target="" append="1" confirmOverwrite="0"/>
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
      <Report reference="Report_11" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_20" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_12" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value=""/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1e-09"/>
      </Method>
    </Task>
    <Task key="Task_21" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_13" target="" append="1" confirmOverwrite="0"/>
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
      <Report reference="Report_14" target="" append="1" confirmOverwrite="0"/>
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
      <Report reference="Report_15" target="" append="1" confirmOverwrite="0"/>
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
        <Parameter name="LimitCrossings" type="bool" value="0"/>
        <Parameter name="NumCrossingsLimit" type="unsignedInteger" value="0"/>
        <Parameter name="LimitTime" type="bool" value="1"/>
        <ParameterText name="TriggerExpression" type="expression">
          
        </ParameterText>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_14" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_17" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_27"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_19" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_9" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_10" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_12" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_13" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <Report key="Report_14" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_15" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_16" name="Events" taskType="timeCourse" separator="&#x09;" precision="7">
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
    <SBMLMap SBMLid="Activation_of_CDC20" COPASIkey="Reaction_53"/>
    <SBMLMap SBMLid="Activation_of_IEP" COPASIkey="Reaction_48"/>
    <SBMLMap SBMLid="Activation_of_SWI5" COPASIkey="Reaction_0"/>
    <SBMLMap SBMLid="Assoc_of_CLB2_and_SIC1" COPASIkey="Reaction_35"/>
    <SBMLMap SBMLid="Assoc_of_CLB5_and_SIC1" COPASIkey="Reaction_33"/>
    <SBMLMap SBMLid="Assoc_with_ESP1_to_form_PE" COPASIkey="Reaction_86"/>
    <SBMLMap SBMLid="Assoc_with_NET1P_to_form_RENTP" COPASIkey="Reaction_64"/>
    <SBMLMap SBMLid="Assoc_with_NET1_to_form_RENT" COPASIkey="Reaction_62"/>
    <SBMLMap SBMLid="BCK2" COPASIkey="Metabolite_26"/>
    <SBMLMap SBMLid="BUB2" COPASIkey="Metabolite_25"/>
    <SBMLMap SBMLid="BUD" COPASIkey="Metabolite_24"/>
    <SBMLMap SBMLid="Budding" COPASIkey="Reaction_90"/>
    <SBMLMap SBMLid="C0" COPASIkey="ModelValue_24"/>
    <SBMLMap SBMLid="C2" COPASIkey="Metabolite_23"/>
    <SBMLMap SBMLid="C2P" COPASIkey="Metabolite_22"/>
    <SBMLMap SBMLid="C5" COPASIkey="Metabolite_21"/>
    <SBMLMap SBMLid="C5P" COPASIkey="Metabolite_20"/>
    <SBMLMap SBMLid="CDC14" COPASIkey="Metabolite_19"/>
    <SBMLMap SBMLid="CDC14T" COPASIkey="Metabolite_18"/>
    <SBMLMap SBMLid="CDC14_degradation" COPASIkey="Reaction_61"/>
    <SBMLMap SBMLid="CDC14_synthesis" COPASIkey="Reaction_60"/>
    <SBMLMap SBMLid="CDC15" COPASIkey="Metabolite_17"/>
    <SBMLMap SBMLid="CDC15T" COPASIkey="ModelValue_23"/>
    <SBMLMap SBMLid="CDC15_activation" COPASIkey="Reaction_79"/>
    <SBMLMap SBMLid="CDC15i" COPASIkey="Metabolite_16"/>
    <SBMLMap SBMLid="CDC20" COPASIkey="Metabolite_15"/>
    <SBMLMap SBMLid="CDC20i" COPASIkey="Metabolite_12"/>
    <SBMLMap SBMLid="CDC6" COPASIkey="Metabolite_11"/>
    <SBMLMap SBMLid="CDC6P" COPASIkey="Metabolite_10"/>
    <SBMLMap SBMLid="CDC6T" COPASIkey="Metabolite_9"/>
    <SBMLMap SBMLid="CDC6_degradation_in_F2P" COPASIkey="Reaction_7"/>
    <SBMLMap SBMLid="CDC6_degradation_in_F5P" COPASIkey="Reaction_6"/>
    <SBMLMap SBMLid="CDC6_synthesis" COPASIkey="Reaction_21"/>
    <SBMLMap SBMLid="CDH1" COPASIkey="Metabolite_8"/>
    <SBMLMap SBMLid="CDH1_degradation" COPASIkey="Reaction_56"/>
    <SBMLMap SBMLid="CDH1_synthesis" COPASIkey="Reaction_55"/>
    <SBMLMap SBMLid="CDH1i" COPASIkey="Metabolite_7"/>
    <SBMLMap SBMLid="CDH1i_activation" COPASIkey="Reaction_58"/>
    <SBMLMap SBMLid="CDH1i_degradation" COPASIkey="Reaction_57"/>
    <SBMLMap SBMLid="CKIT" COPASIkey="Metabolite_6"/>
    <SBMLMap SBMLid="CLB2" COPASIkey="Metabolite_5"/>
    <SBMLMap SBMLid="CLB2CDC6_complex_formation" COPASIkey="Reaction_17"/>
    <SBMLMap SBMLid="CLB2CDC6_dissociation" COPASIkey="Reaction_16"/>
    <SBMLMap SBMLid="CLB2T" COPASIkey="Metabolite_4"/>
    <SBMLMap SBMLid="CLB2_degradation_in_F2" COPASIkey="Reaction_9"/>
    <SBMLMap SBMLid="CLB2_degradation_in_F2P" COPASIkey="Reaction_5"/>
    <SBMLMap SBMLid="CLB5" COPASIkey="Metabolite_3"/>
    <SBMLMap SBMLid="CLB5CDC6_complex_formation" COPASIkey="Reaction_15"/>
    <SBMLMap SBMLid="CLB5CDC6_dissociation" COPASIkey="Reaction_14"/>
    <SBMLMap SBMLid="CLB5T" COPASIkey="Metabolite_2"/>
    <SBMLMap SBMLid="CLB5_degradation_in_F5" COPASIkey="Reaction_8"/>
    <SBMLMap SBMLid="CLB5_degradation_in_F5P" COPASIkey="Reaction_4"/>
    <SBMLMap SBMLid="CLN2" COPASIkey="Metabolite_1"/>
    <SBMLMap SBMLid="CLN3" COPASIkey="Metabolite_0"/>
    <SBMLMap SBMLid="D" COPASIkey="ModelValue_143"/>
    <SBMLMap SBMLid="DNA_synthesis" COPASIkey="Reaction_88"/>
    <SBMLMap SBMLid="Degradation_of_CDC14_in_RENT" COPASIkey="Reaction_75"/>
    <SBMLMap SBMLid="Degradation_of_CDC14_in_RENTP" COPASIkey="Reaction_76"/>
    <SBMLMap SBMLid="Degradation_of_CDC6P" COPASIkey="Reaction_18"/>
    <SBMLMap SBMLid="Degradation_of_CLB2" COPASIkey="Reaction_42"/>
    <SBMLMap SBMLid="Degradation_of_CLB2_in_C2" COPASIkey="Reaction_27"/>
    <SBMLMap SBMLid="Degradation_of_CLB2_in_C2P" COPASIkey="Reaction_23"/>
    <SBMLMap SBMLid="Degradation_of_CLB5" COPASIkey="Reaction_40"/>
    <SBMLMap SBMLid="Degradation_of_CLB5_in_C5" COPASIkey="Reaction_26"/>
    <SBMLMap SBMLid="Degradation_of_CLB5_in_C5P" COPASIkey="Reaction_22"/>
    <SBMLMap SBMLid="Degradation_of_CLN2" COPASIkey="Reaction_44"/>
    <SBMLMap SBMLid="Degradation_of_NET1P_in_RENTP" COPASIkey="Reaction_74"/>
    <SBMLMap SBMLid="Degradation_of_NET1_in_RENT" COPASIkey="Reaction_73"/>
    <SBMLMap SBMLid="Degradation_of_PDS1_in_PE" COPASIkey="Reaction_85"/>
    <SBMLMap SBMLid="Degradation_of_SIC1P_in_C5P_" COPASIkey="Reaction_24"/>
    <SBMLMap SBMLid="Degradation_of_SIC1_in_C2P" COPASIkey="Reaction_25"/>
    <SBMLMap SBMLid="Degradation_of_SWI5" COPASIkey="Reaction_2"/>
    <SBMLMap SBMLid="Degradation_of_SWI5P" COPASIkey="Reaction_1"/>
    <SBMLMap SBMLid="Degradation_of_active_CDC20" COPASIkey="Reaction_52"/>
    <SBMLMap SBMLid="Degradation_of_inactiveCDC20" COPASIkey="Reaction_51"/>
    <SBMLMap SBMLid="Dephosphorylation_of_C2P" COPASIkey="Reaction_30"/>
    <SBMLMap SBMLid="Dephosphorylation_of_C5P" COPASIkey="Reaction_28"/>
    <SBMLMap SBMLid="Dephosphorylation_of_CDC6" COPASIkey="Reaction_19"/>
    <SBMLMap SBMLid="Dephosphorylation_of_SIC1" COPASIkey="Reaction_37"/>
    <SBMLMap SBMLid="Disso_from_PE" COPASIkey="Reaction_87"/>
    <SBMLMap SBMLid="Dissoc_from_RENP" COPASIkey="Reaction_65"/>
    <SBMLMap SBMLid="Dissoc_from_RENT" COPASIkey="Reaction_63"/>
    <SBMLMap SBMLid="Dissoc_of_CLB2SIC1_complex" COPASIkey="Reaction_34"/>
    <SBMLMap SBMLid="Dissoc_of_CLB5SIC1" COPASIkey="Reaction_32"/>
    <SBMLMap SBMLid="Dn3" COPASIkey="ModelValue_22"/>
    <SBMLMap SBMLid="ESP1" COPASIkey="Metabolite_27"/>
    <SBMLMap SBMLid="ESP1T" COPASIkey="ModelValue_28"/>
    <SBMLMap SBMLid="F" COPASIkey="ModelValue_162"/>
    <SBMLMap SBMLid="F2" COPASIkey="Metabolite_28"/>
    <SBMLMap SBMLid="F2P" COPASIkey="Metabolite_29"/>
    <SBMLMap SBMLid="F2P_dephosphorylation" COPASIkey="Reaction_12"/>
    <SBMLMap SBMLid="F2_phosphorylation" COPASIkey="Reaction_13"/>
    <SBMLMap SBMLid="F5" COPASIkey="Metabolite_30"/>
    <SBMLMap SBMLid="F5P" COPASIkey="Metabolite_31"/>
    <SBMLMap SBMLid="F5P_dephosphorylation" COPASIkey="Reaction_10"/>
    <SBMLMap SBMLid="F5_phosphorylation" COPASIkey="Reaction_11"/>
    <SBMLMap SBMLid="Fast_Degradation_of_SIC1P" COPASIkey="Reaction_36"/>
    <SBMLMap SBMLid="GK_219" COPASIkey="Function_46"/>
    <SBMLMap SBMLid="Growth" COPASIkey="Reaction_46"/>
    <SBMLMap SBMLid="IE" COPASIkey="Metabolite_32"/>
    <SBMLMap SBMLid="IEP" COPASIkey="Metabolite_33"/>
    <SBMLMap SBMLid="IET" COPASIkey="ModelValue_29"/>
    <SBMLMap SBMLid="Inactivation_1" COPASIkey="Reaction_49"/>
    <SBMLMap SBMLid="Inactivation_2" COPASIkey="Reaction_54"/>
    <SBMLMap SBMLid="Inactivation_3" COPASIkey="Reaction_59"/>
    <SBMLMap SBMLid="Inactivation_of_SWI5" COPASIkey="Reaction_47"/>
    <SBMLMap SBMLid="J20ppx" COPASIkey="ModelValue_30"/>
    <SBMLMap SBMLid="Jacdh" COPASIkey="ModelValue_31"/>
    <SBMLMap SBMLid="Jaiep" COPASIkey="ModelValue_32"/>
    <SBMLMap SBMLid="Jamcm" COPASIkey="ModelValue_33"/>
    <SBMLMap SBMLid="Jasbf" COPASIkey="ModelValue_34"/>
    <SBMLMap SBMLid="Jatem" COPASIkey="ModelValue_35"/>
    <SBMLMap SBMLid="Jd2c1" COPASIkey="ModelValue_36"/>
    <SBMLMap SBMLid="Jd2f6" COPASIkey="ModelValue_37"/>
    <SBMLMap SBMLid="Jicdh" COPASIkey="ModelValue_38"/>
    <SBMLMap SBMLid="Jiiep" COPASIkey="ModelValue_39"/>
    <SBMLMap SBMLid="Jimcm" COPASIkey="ModelValue_40"/>
    <SBMLMap SBMLid="Jisbf" COPASIkey="ModelValue_41"/>
    <SBMLMap SBMLid="Jitem" COPASIkey="ModelValue_42"/>
    <SBMLMap SBMLid="Jn3" COPASIkey="ModelValue_43"/>
    <SBMLMap SBMLid="Jpds" COPASIkey="ModelValue_44"/>
    <SBMLMap SBMLid="Jspn" COPASIkey="ModelValue_45"/>
    <SBMLMap SBMLid="KEZ" COPASIkey="ModelValue_96"/>
    <SBMLMap SBMLid="KEZ2" COPASIkey="ModelValue_97"/>
    <SBMLMap SBMLid="LTE1" COPASIkey="Metabolite_34"/>
    <SBMLMap SBMLid="MAD2" COPASIkey="Metabolite_35"/>
    <SBMLMap SBMLid="MASS" COPASIkey="Metabolite_36"/>
    <SBMLMap SBMLid="MCM1" COPASIkey="Metabolite_37"/>
    <SBMLMap SBMLid="Mass_Action_1_222" COPASIkey="Function_47"/>
    <SBMLMap SBMLid="Mass_Action_2_221" COPASIkey="Function_48"/>
    <SBMLMap SBMLid="MichaelisMenten_220" COPASIkey="Function_49"/>
    <SBMLMap SBMLid="NET1" COPASIkey="Metabolite_38"/>
    <SBMLMap SBMLid="NET1P" COPASIkey="Metabolite_39"/>
    <SBMLMap SBMLid="NET1T" COPASIkey="Metabolite_40"/>
    <SBMLMap SBMLid="NET1_phosphorylation" COPASIkey="Reaction_69"/>
    <SBMLMap SBMLid="Negative_regulation_of_Cell_budding" COPASIkey="Reaction_91"/>
    <SBMLMap SBMLid="Negative_regulation_of_DNA_synthesis" COPASIkey="Reaction_89"/>
    <SBMLMap SBMLid="Net1P_degradation" COPASIkey="Reaction_68"/>
    <SBMLMap SBMLid="Net1_degradation" COPASIkey="Reaction_67"/>
    <SBMLMap SBMLid="Net1_synthesis" COPASIkey="Reaction_66"/>
    <SBMLMap SBMLid="ORI" COPASIkey="Metabolite_41"/>
    <SBMLMap SBMLid="PDS1" COPASIkey="Metabolite_42"/>
    <SBMLMap SBMLid="PDS1_synthesis" COPASIkey="Reaction_83"/>
    <SBMLMap SBMLid="PE" COPASIkey="Metabolite_43"/>
    <SBMLMap SBMLid="PPX" COPASIkey="Metabolite_44"/>
    <SBMLMap SBMLid="PPX_synthesis" COPASIkey="Reaction_81"/>
    <SBMLMap SBMLid="Phosphorylation_of_C2" COPASIkey="Reaction_31"/>
    <SBMLMap SBMLid="Phosphorylation_of_C5" COPASIkey="Reaction_29"/>
    <SBMLMap SBMLid="Phosphorylation_of_CDC6" COPASIkey="Reaction_20"/>
    <SBMLMap SBMLid="Phosphorylation_of_SIC1" COPASIkey="Reaction_38"/>
    <SBMLMap SBMLid="RENT" COPASIkey="Metabolite_45"/>
    <SBMLMap SBMLid="RENTP" COPASIkey="Metabolite_46"/>
    <SBMLMap SBMLid="RENT_phosphorylation" COPASIkey="Reaction_71"/>
    <SBMLMap SBMLid="SBF" COPASIkey="Metabolite_47"/>
    <SBMLMap SBMLid="SIC1" COPASIkey="Metabolite_48"/>
    <SBMLMap SBMLid="SIC1P" COPASIkey="Metabolite_49"/>
    <SBMLMap SBMLid="SIC1T" COPASIkey="Metabolite_50"/>
    <SBMLMap SBMLid="SPN" COPASIkey="Metabolite_51"/>
    <SBMLMap SBMLid="SWI5" COPASIkey="Metabolite_52"/>
    <SBMLMap SBMLid="SWI5P" COPASIkey="Metabolite_53"/>
    <SBMLMap SBMLid="Spindle_disassembly" COPASIkey="Reaction_93"/>
    <SBMLMap SBMLid="Spindle_formation" COPASIkey="Reaction_92"/>
    <SBMLMap SBMLid="Synthesis_of_CLB2" COPASIkey="Reaction_43"/>
    <SBMLMap SBMLid="Synthesis_of_CLB5" COPASIkey="Reaction_41"/>
    <SBMLMap SBMLid="Synthesis_of_CLN2" COPASIkey="Reaction_45"/>
    <SBMLMap SBMLid="Synthesis_of_SIC1" COPASIkey="Reaction_39"/>
    <SBMLMap SBMLid="Synthesis_of_SWI5" COPASIkey="Reaction_3"/>
    <SBMLMap SBMLid="Synthesis_of_inactive_CDC20" COPASIkey="Reaction_50"/>
    <SBMLMap SBMLid="TEM1GDP" COPASIkey="Metabolite_54"/>
    <SBMLMap SBMLid="TEM1GTP" COPASIkey="Metabolite_55"/>
    <SBMLMap SBMLid="TEM1T" COPASIkey="ModelValue_142"/>
    <SBMLMap SBMLid="TEM1_activation" COPASIkey="Reaction_77"/>
    <SBMLMap SBMLid="Vacdh" COPASIkey="ModelValue_151"/>
    <SBMLMap SBMLid="Vaiep" COPASIkey="ModelValue_157"/>
    <SBMLMap SBMLid="Vasbf" COPASIkey="ModelValue_147"/>
    <SBMLMap SBMLid="Vd2c1" COPASIkey="ModelValue_158"/>
    <SBMLMap SBMLid="Vd2f6" COPASIkey="ModelValue_159"/>
    <SBMLMap SBMLid="Vdb2" COPASIkey="ModelValue_146"/>
    <SBMLMap SBMLid="Vdb5" COPASIkey="ModelValue_145"/>
    <SBMLMap SBMLid="Vdpds" COPASIkey="ModelValue_156"/>
    <SBMLMap SBMLid="Vdppx" COPASIkey="ModelValue_155"/>
    <SBMLMap SBMLid="Vicdh" COPASIkey="ModelValue_152"/>
    <SBMLMap SBMLid="Visbf" COPASIkey="ModelValue_148"/>
    <SBMLMap SBMLid="Vkpc1" COPASIkey="ModelValue_149"/>
    <SBMLMap SBMLid="Vkpf6" COPASIkey="ModelValue_150"/>
    <SBMLMap SBMLid="Vkpnet" COPASIkey="ModelValue_154"/>
    <SBMLMap SBMLid="Vppc1" COPASIkey="ModelValue_160"/>
    <SBMLMap SBMLid="Vppf6" COPASIkey="ModelValue_161"/>
    <SBMLMap SBMLid="Vppnet" COPASIkey="ModelValue_153"/>
    <SBMLMap SBMLid="b0" COPASIkey="ModelValue_27"/>
    <SBMLMap SBMLid="bub2h" COPASIkey="ModelValue_26"/>
    <SBMLMap SBMLid="bub2l" COPASIkey="ModelValue_25"/>
    <SBMLMap SBMLid="cell" COPASIkey="Compartment_2"/>
    <SBMLMap SBMLid="degradation_1" COPASIkey="Reaction_82"/>
    <SBMLMap SBMLid="degradation_2" COPASIkey="Reaction_84"/>
    <SBMLMap SBMLid="dephosphorylation_1" COPASIkey="Reaction_70"/>
    <SBMLMap SBMLid="dephosphorylation_2" COPASIkey="Reaction_72"/>
    <SBMLMap SBMLid="ebudb5" COPASIkey="ModelValue_21"/>
    <SBMLMap SBMLid="ebudn2" COPASIkey="ModelValue_20"/>
    <SBMLMap SBMLid="ebudn3" COPASIkey="ModelValue_19"/>
    <SBMLMap SBMLid="ec1b2" COPASIkey="ModelValue_18"/>
    <SBMLMap SBMLid="ec1b5" COPASIkey="ModelValue_17"/>
    <SBMLMap SBMLid="ec1k2" COPASIkey="ModelValue_16"/>
    <SBMLMap SBMLid="ec1n2" COPASIkey="ModelValue_15"/>
    <SBMLMap SBMLid="ec1n3" COPASIkey="ModelValue_14"/>
    <SBMLMap SBMLid="ef6b2" COPASIkey="ModelValue_13"/>
    <SBMLMap SBMLid="ef6b5" COPASIkey="ModelValue_12"/>
    <SBMLMap SBMLid="ef6k2" COPASIkey="ModelValue_11"/>
    <SBMLMap SBMLid="ef6n2" COPASIkey="ModelValue_10"/>
    <SBMLMap SBMLid="ef6n3" COPASIkey="ModelValue_9"/>
    <SBMLMap SBMLid="eicdhb2" COPASIkey="ModelValue_8"/>
    <SBMLMap SBMLid="eicdhb5" COPASIkey="ModelValue_7"/>
    <SBMLMap SBMLid="eicdhn2" COPASIkey="ModelValue_6"/>
    <SBMLMap SBMLid="eicdhn3" COPASIkey="ModelValue_5"/>
    <SBMLMap SBMLid="eorib2" COPASIkey="ModelValue_4"/>
    <SBMLMap SBMLid="eorib5" COPASIkey="ModelValue_3"/>
    <SBMLMap SBMLid="esbfb5" COPASIkey="ModelValue_2"/>
    <SBMLMap SBMLid="esbfn2" COPASIkey="ModelValue_1"/>
    <SBMLMap SBMLid="esbfn3" COPASIkey="ModelValue_0"/>
    <SBMLMap SBMLid="inactivation_1" COPASIkey="Reaction_78"/>
    <SBMLMap SBMLid="inactivation_2" COPASIkey="Reaction_80"/>
    <SBMLMap SBMLid="ka15_p" COPASIkey="ModelValue_46"/>
    <SBMLMap SBMLid="ka15_p_p" COPASIkey="ModelValue_47"/>
    <SBMLMap SBMLid="ka15p" COPASIkey="ModelValue_48"/>
    <SBMLMap SBMLid="ka20_p" COPASIkey="ModelValue_49"/>
    <SBMLMap SBMLid="ka20_p_p" COPASIkey="ModelValue_50"/>
    <SBMLMap SBMLid="kacdh_p" COPASIkey="ModelValue_51"/>
    <SBMLMap SBMLid="kacdh_p_p" COPASIkey="ModelValue_52"/>
    <SBMLMap SBMLid="kaiep" COPASIkey="ModelValue_53"/>
    <SBMLMap SBMLid="kamcm" COPASIkey="ModelValue_54"/>
    <SBMLMap SBMLid="kasb2" COPASIkey="ModelValue_55"/>
    <SBMLMap SBMLid="kasb5" COPASIkey="ModelValue_56"/>
    <SBMLMap SBMLid="kasbf" COPASIkey="ModelValue_57"/>
    <SBMLMap SBMLid="kasesp" COPASIkey="ModelValue_58"/>
    <SBMLMap SBMLid="kasf2" COPASIkey="ModelValue_59"/>
    <SBMLMap SBMLid="kasf5" COPASIkey="ModelValue_60"/>
    <SBMLMap SBMLid="kasrent" COPASIkey="ModelValue_61"/>
    <SBMLMap SBMLid="kasrentp" COPASIkey="ModelValue_62"/>
    <SBMLMap SBMLid="kaswi" COPASIkey="ModelValue_63"/>
    <SBMLMap SBMLid="kd14" COPASIkey="ModelValue_64"/>
    <SBMLMap SBMLid="kd1c1" COPASIkey="ModelValue_65"/>
    <SBMLMap SBMLid="kd1f6" COPASIkey="ModelValue_66"/>
    <SBMLMap SBMLid="kd1pds_p" COPASIkey="ModelValue_67"/>
    <SBMLMap SBMLid="kd20" COPASIkey="ModelValue_68"/>
    <SBMLMap SBMLid="kd2c1" COPASIkey="ModelValue_69"/>
    <SBMLMap SBMLid="kd2f6" COPASIkey="ModelValue_70"/>
    <SBMLMap SBMLid="kd2pds_p_p" COPASIkey="ModelValue_71"/>
    <SBMLMap SBMLid="kd3c1" COPASIkey="ModelValue_72"/>
    <SBMLMap SBMLid="kd3f6" COPASIkey="ModelValue_73"/>
    <SBMLMap SBMLid="kd3pds_p_p" COPASIkey="ModelValue_74"/>
    <SBMLMap SBMLid="kdb2_p" COPASIkey="ModelValue_75"/>
    <SBMLMap SBMLid="kdb2_p_p" COPASIkey="ModelValue_76"/>
    <SBMLMap SBMLid="kdb2p" COPASIkey="ModelValue_77"/>
    <SBMLMap SBMLid="kdb5_p" COPASIkey="ModelValue_78"/>
    <SBMLMap SBMLid="kdb5_p_p" COPASIkey="ModelValue_79"/>
    <SBMLMap SBMLid="kdbud" COPASIkey="ModelValue_80"/>
    <SBMLMap SBMLid="kdcdh" COPASIkey="ModelValue_81"/>
    <SBMLMap SBMLid="kdib2" COPASIkey="ModelValue_82"/>
    <SBMLMap SBMLid="kdib5" COPASIkey="ModelValue_83"/>
    <SBMLMap SBMLid="kdiesp" COPASIkey="ModelValue_84"/>
    <SBMLMap SBMLid="kdif2" COPASIkey="ModelValue_85"/>
    <SBMLMap SBMLid="kdif5" COPASIkey="ModelValue_86"/>
    <SBMLMap SBMLid="kdirent" COPASIkey="ModelValue_87"/>
    <SBMLMap SBMLid="kdirentp" COPASIkey="ModelValue_88"/>
    <SBMLMap SBMLid="kdn2" COPASIkey="ModelValue_89"/>
    <SBMLMap SBMLid="kdnet" COPASIkey="ModelValue_90"/>
    <SBMLMap SBMLid="kdori" COPASIkey="ModelValue_91"/>
    <SBMLMap SBMLid="kdppx_p" COPASIkey="ModelValue_92"/>
    <SBMLMap SBMLid="kdppx_p_p" COPASIkey="ModelValue_93"/>
    <SBMLMap SBMLid="kdspn" COPASIkey="ModelValue_94"/>
    <SBMLMap SBMLid="kdswi" COPASIkey="ModelValue_95"/>
    <SBMLMap SBMLid="ki15" COPASIkey="ModelValue_98"/>
    <SBMLMap SBMLid="kicdh_p" COPASIkey="ModelValue_99"/>
    <SBMLMap SBMLid="kicdh_p_p" COPASIkey="ModelValue_100"/>
    <SBMLMap SBMLid="kiiep" COPASIkey="ModelValue_101"/>
    <SBMLMap SBMLid="kimcm" COPASIkey="ModelValue_102"/>
    <SBMLMap SBMLid="kisbf_p" COPASIkey="ModelValue_103"/>
    <SBMLMap SBMLid="kisbf_p_p" COPASIkey="ModelValue_104"/>
    <SBMLMap SBMLid="kiswi" COPASIkey="ModelValue_105"/>
    <SBMLMap SBMLid="kkpnet_p" COPASIkey="ModelValue_106"/>
    <SBMLMap SBMLid="kkpnet_p_p" COPASIkey="ModelValue_107"/>
    <SBMLMap SBMLid="kppc1" COPASIkey="ModelValue_108"/>
    <SBMLMap SBMLid="kppf6" COPASIkey="ModelValue_109"/>
    <SBMLMap SBMLid="kppnet_p" COPASIkey="ModelValue_110"/>
    <SBMLMap SBMLid="kppnet_p_p" COPASIkey="ModelValue_111"/>
    <SBMLMap SBMLid="ks14" COPASIkey="ModelValue_112"/>
    <SBMLMap SBMLid="ks1pds_p_p" COPASIkey="ModelValue_113"/>
    <SBMLMap SBMLid="ks20_p" COPASIkey="ModelValue_114"/>
    <SBMLMap SBMLid="ks20_p_p" COPASIkey="ModelValue_115"/>
    <SBMLMap SBMLid="ks2pds_p_p" COPASIkey="ModelValue_116"/>
    <SBMLMap SBMLid="ksb2_p" COPASIkey="ModelValue_117"/>
    <SBMLMap SBMLid="ksb2_p_p" COPASIkey="ModelValue_118"/>
    <SBMLMap SBMLid="ksb5_p" COPASIkey="ModelValue_119"/>
    <SBMLMap SBMLid="ksb5_p_p" COPASIkey="ModelValue_120"/>
    <SBMLMap SBMLid="ksbud" COPASIkey="ModelValue_121"/>
    <SBMLMap SBMLid="ksc1_p" COPASIkey="ModelValue_122"/>
    <SBMLMap SBMLid="ksc1_p_p" COPASIkey="ModelValue_123"/>
    <SBMLMap SBMLid="kscdh" COPASIkey="ModelValue_124"/>
    <SBMLMap SBMLid="ksf6_p" COPASIkey="ModelValue_125"/>
    <SBMLMap SBMLid="ksf6_p_p" COPASIkey="ModelValue_126"/>
    <SBMLMap SBMLid="ksf6_p_p_p" COPASIkey="ModelValue_127"/>
    <SBMLMap SBMLid="ksn2_p" COPASIkey="ModelValue_128"/>
    <SBMLMap SBMLid="ksn2_p_p" COPASIkey="ModelValue_129"/>
    <SBMLMap SBMLid="ksnet" COPASIkey="ModelValue_130"/>
    <SBMLMap SBMLid="ksori" COPASIkey="ModelValue_131"/>
    <SBMLMap SBMLid="kspds_p" COPASIkey="ModelValue_132"/>
    <SBMLMap SBMLid="ksppx" COPASIkey="ModelValue_133"/>
    <SBMLMap SBMLid="ksspn" COPASIkey="ModelValue_134"/>
    <SBMLMap SBMLid="ksswi_p" COPASIkey="ModelValue_135"/>
    <SBMLMap SBMLid="ksswi_p_p" COPASIkey="ModelValue_136"/>
    <SBMLMap SBMLid="lte1h" COPASIkey="ModelValue_137"/>
    <SBMLMap SBMLid="lte1l" COPASIkey="ModelValue_138"/>
    <SBMLMap SBMLid="mad2h" COPASIkey="ModelValue_139"/>
    <SBMLMap SBMLid="mad2l" COPASIkey="ModelValue_140"/>
    <SBMLMap SBMLid="mdt" COPASIkey="ModelValue_141"/>
    <SBMLMap SBMLid="mu" COPASIkey="ModelValue_144"/>
    <SBMLMap SBMLid="parameter_1" COPASIkey="ModelValue_163"/>
  </SBMLReference>
</COPASI>
