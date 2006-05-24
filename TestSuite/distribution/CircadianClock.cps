<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.0 (Build 18) (http://www.copasi.org) at 2006-05-24 15:28:48 UTC -->
<COPASI xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://www.copasi.org/static/schema.xsd" versionMajor="0" versionMinor="1">
  <ListOfFunctions>
    <Function key="Function_13" name="Mass action (irreversible)" type="MassAction" positive="false">
      <MathML>
        <Text>
          k1*PRODUCT&lt;substrate_i&gt;
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_81" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_79" name="substrate" order="1" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_38" name="Objective Function" type="Expression">
      <MathML>
        <Text>
          
        </Text>
      </MathML>
    </Function>
    <Function key="Function_39" name="Transcription" type="UserDefined" positive="false">
      <MathML>
        <Text>
          V*K^n/(K^n+modifier^n)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_260" name="V" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_243" name="K" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_250" name="n" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_261" name="modifier" order="3" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_40" name="linear activation" type="UserDefined" positive="false">
      <MathML>
        <Text>
          k*modifier
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_262" name="k" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_246" name="modifier" order="1" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_8" name="Henri-Michaelis-Menten (irreversible)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate/(Km+substrate)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_45" name="V" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_41" name="substrate" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_30" name="Km" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_1" name="Circadian Clock" timeUnit="h" volumeUnit="l" quantityUnit="nMol" type="deterministic">
    <Comment>
      <html xmlns="http://www.w3.org/1999/xhtml"><head><meta name="qrichtext" content="1" /></head><body style="font-size:8pt;font-family:MS Shell Dlg">
<p>This is a model of the Drosophila circadian clock based on the PER and TIM genes, as published in Leloup J.-C. &amp; Goldbeter A. (1999) &quot;Chaos and birhythmicity in a model of circadian oscillations of the PER and TIM proteins in Drosophila&quot; J. Theor. Biol. 198, 445-459 </p>
</body></html>

    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="cell"/>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="P0" compartment="Compartment_0" status="variable"/>
      <Metabolite key="Metabolite_1" name="Mt" compartment="Compartment_0" status="variable"/>
      <Metabolite key="Metabolite_2" name="Mp" compartment="Compartment_0" status="variable"/>
      <Metabolite key="Metabolite_3" name="T0" compartment="Compartment_0" status="variable"/>
      <Metabolite key="Metabolite_4" name="P1" compartment="Compartment_0" status="variable"/>
      <Metabolite key="Metabolite_5" name="P2" compartment="Compartment_0" status="variable"/>
      <Metabolite key="Metabolite_6" name="T1" compartment="Compartment_0" status="variable"/>
      <Metabolite key="Metabolite_7" name="T2" compartment="Compartment_0" status="variable"/>
      <Metabolite key="Metabolite_8" name="C" compartment="Compartment_0" status="variable"/>
      <Metabolite key="Metabolite_9" name="Cn" compartment="Compartment_0" status="variable"/>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="sP" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_75" name="k" value="0.9"/>
        </ListOfConstants>
        <KineticLaw function="Function_40">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="Parameter_75"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_246">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="Mp transcription" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_74" name="V" value="1"/>
          <Constant key="Parameter_73" name="K" value="0.9"/>
          <Constant key="Parameter_72" name="n" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_39">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_260">
              <SourceParameter reference="Parameter_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_243">
              <SourceParameter reference="Parameter_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_250">
              <SourceParameter reference="Parameter_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_261">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="Mp degradation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_71" name="Km" value="0.2"/>
          <Constant key="Parameter_70" name="V" value="0.7"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_70"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_71"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="Mt transcription" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_61" name="V" value="1"/>
          <Constant key="Parameter_62" name="K" value="0.9"/>
          <Constant key="Parameter_65" name="n" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_39">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_260">
              <SourceParameter reference="Parameter_61"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_243">
              <SourceParameter reference="Parameter_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_250">
              <SourceParameter reference="Parameter_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_261">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="Mt degradation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_66" name="Km" value="0.2"/>
          <Constant key="Parameter_67" name="V" value="0.7"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_67"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_66"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="sT" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_68" name="k" value="0.9"/>
        </ListOfConstants>
        <KineticLaw function="Function_40">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="Parameter_68"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_246">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="1P" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_76" name="Km" value="2"/>
          <Constant key="Parameter_77" name="V" value="8"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_76"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="2P" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_78" name="Km" value="2"/>
          <Constant key="Parameter_79" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_78"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="3P" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_80" name="Km" value="2"/>
          <Constant key="Parameter_81" name="V" value="8"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_81"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_80"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="4P" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_93" name="Km" value="2"/>
          <Constant key="Parameter_92" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_92"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_93"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="1T" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_91" name="Km" value="2"/>
          <Constant key="Parameter_90" name="V" value="8"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_90"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_91"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="2T" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_89" name="Km" value="2"/>
          <Constant key="Parameter_88" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_88"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_89"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="3T" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_98" name="Km" value="2"/>
          <Constant key="Parameter_99" name="V" value="8"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_98"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="4T" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_100" name="Km" value="2"/>
          <Constant key="Parameter_101" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_100"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="dP" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_102" name="Km" value="0.2"/>
          <Constant key="Parameter_103" name="V" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_102"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="dT" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_104" name="Km" value="0.2"/>
          <Constant key="Parameter_105" name="V" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_105"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_104"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="Mt dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_106" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_106"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="Mp dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_107" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_107"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="P0 dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_108" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="P1 dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_109" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="P2 dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_110" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_110"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="T0 dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_111" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_111"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="T1 dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_112" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="T2 dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_113" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="C dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_114" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="Cn dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_115" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="T2 degradation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_116" name="Km" value="0.2"/>
          <Constant key="Parameter_117" name="V" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_117"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_116"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="P2 degradation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_118" name="Km" value="0.2"/>
          <Constant key="Parameter_119" name="V" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_119"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Parameter_118"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="PT binding (forward)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_120" name="k1" value="1.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_120"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_5"/>
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="PT binding (backward)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_121" name="k1" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="C transport (forward)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_122" name="k1" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_122"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="C transport (backward)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_123" name="k1" value="0.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_123"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_1"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_4"/>
      <StateTemplateVariable objectReference="Metabolite_6"/>
      <StateTemplateVariable objectReference="Metabolite_8"/>
      <StateTemplateVariable objectReference="Metabolite_0"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_2"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Compartment_0"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 27483900000000 27483900000000 118191000000000 118191000000000 60221400000000 60221400000000 141869000000000 553160000000000 553160000000000 368354000000000 1
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_7" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Use Newton" type="bool" value="1"/>
        <Parameter name="Use Integration" type="bool" value="1"/>
        <Parameter name="Use Back Integration" type="bool" value="0"/>
        <Parameter name="Accept Negative Concentrations" type="bool" value="0"/>
        <Parameter name="Iteration Limit" type="unsignedInteger" value="50"/>
        <Parameter name="Derivation Factor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Resolution" type="unsignedFloat" value="1e-009"/>
      </Method>
    </Task>
    <Task key="Task_8" name="Time-Course" type="timeCourse" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="960"/>
        <Parameter name="StepSize" type="float" value="0.1"/>
        <Parameter name="Duration" type="float" value="96"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="1"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-006"/>
        <Parameter name="Use Default Absolute Tolerance" type="bool" value="1"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-012"/>
        <Parameter name="Adams Max Order" type="unsignedInteger" value="12"/>
        <Parameter name="BDF Max Order" type="unsignedInteger" value="5"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_9" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_7"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1e-009"/>
      </Method>
    </Task>
    <Task key="Task_10" name="Scan" type="scan" scheduled="false" updateModel="false">
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
    <Task key="Task_11" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="Steady-State" type="key" value=""/>
        <Parameter name="Time-Course" type="key" value="Task_8"/>
        <Parameter name="ObjectiveFunction" type="key" value="Function_38"/>
        <Parameter name="Maximize" type="bool" value="0"/>
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
    <Task key="Task_12" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_7"/>
        <Parameter name="Time-Course" type="key" value="Task_8"/>
        <ParameterGroup name="OptimizationItemList">
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
        </ParameterGroup>
        <ParameterGroup name="Experiment Set">
        </ParameterGroup>
      </Problem>
      <Method name="Evolutionary Program" type="EvolutionaryProgram">
        <Parameter name="Number of Generations" type="unsignedInteger" value="200"/>
        <Parameter name="Population Size" type="unsignedInteger" value="20"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_13" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="ExponentNumber" type="unsignedInteger" value="3"/>
        <Parameter name="DivergenceRequested" type="bool" value="1"/>
        <Parameter name="TransientTime" type="float" value="0"/>
      </Problem>
      <Method name="Wolf Method" type="WolfMethod">
        <Parameter name="Orthonormalize Intervall" type="unsignedFloat" value="1"/>
        <Parameter name="Overall time" type="unsignedFloat" value="1000"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-006"/>
        <Parameter name="Use Default Absolute Tolerance" type="bool" value="1"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e+009"/>
        <Parameter name="Adams Max Order" type="unsignedInteger" value="12"/>
        <Parameter name="BDF Max Order" type="unsignedInteger" value="5"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_4" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_5" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_6" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_7" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="Time Course" type="Plot2D" active="0">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="P0" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[P0],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Mt" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[Mt],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Mp" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[Mp],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="T0" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[T0],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="P1" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[P1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="P2" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[P2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="T1" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[T1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="T2" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[T2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="C" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[C],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Cn" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[Cn],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
  </GUI>
</COPASI>
