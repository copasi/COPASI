<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.0 Debug 17++ (http://www.copasi.org) at 2006-01-04 16:39:48 UTC -->
<COPASI xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://calvin.bioinformatics.vt.edu/copasi/schema/copasi.xsd" versionMajor="0" versionMinor="1">
  <ListOfFunctions>
    <Function key="Function_13" name="Mass action (irreversible)" type="MassAction" positive="false">
      <MathML>
        <Text>
          k1*PRODUCT&lt;substrate_i&gt;
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_81" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_80" name="substrate" order="1" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_37" name="Objective Function" type="Expression">
      <MathML>
        <Text>
          
        </Text>
      </MathML>
    </Function>
    <Function key="Function_38" name="linear activation" type="UserDefined" positive="false">
      <MathML>
        <Text>
          k*modifier
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_260" name="k" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_259" name="modifier" order="1" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_39" name="Transcription" type="UserDefined" positive="false">
      <MathML>
        <Text>
          V*K^n/(K^n+modifier^n)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_257" name="V" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_258" name="K" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_249" name="n" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_250" name="modifier" order="3" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_8" name="Henri-Michaelis-Menten (irreversible)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate/(Km+substrate)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_47" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_46" name="Km" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_45" name="V" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_1" name="Circadian Clock" timeUnit="h" volumeUnit="l" quantityUnit="nMol" stateVariable="StateVariable_3">
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
        This is a model of the Drosophila circadian clock based on the PER and TIM genes, as published in Leloup J.-C. &amp; Goldbeter A. (1999) &quot;Chaos and birhythmicity in a model of circadian oscillations of the PER and TIM proteins in Drosophila&quot; J. Theor. Biol. 198, 445-459
      </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="cell" stateVariable="StateVariable_4"/>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="P0" compartment="Compartment_0" status="variable" stateVariable="StateVariable_5"/>
      <Metabolite key="Metabolite_1" name="Mt" compartment="Compartment_0" status="variable" stateVariable="StateVariable_6"/>
      <Metabolite key="Metabolite_2" name="Mp" compartment="Compartment_0" status="variable" stateVariable="StateVariable_7"/>
      <Metabolite key="Metabolite_3" name="T0" compartment="Compartment_0" status="variable" stateVariable="StateVariable_8"/>
      <Metabolite key="Metabolite_4" name="P1" compartment="Compartment_0" status="variable" stateVariable="StateVariable_9"/>
      <Metabolite key="Metabolite_5" name="P2" compartment="Compartment_0" status="variable" stateVariable="StateVariable_10"/>
      <Metabolite key="Metabolite_6" name="T1" compartment="Compartment_0" status="variable" stateVariable="StateVariable_11"/>
      <Metabolite key="Metabolite_7" name="T2" compartment="Compartment_0" status="variable" stateVariable="StateVariable_12"/>
      <Metabolite key="Metabolite_8" name="C" compartment="Compartment_0" status="variable" stateVariable="StateVariable_13"/>
      <Metabolite key="Metabolite_9" name="Cn" compartment="Compartment_0" status="variable" stateVariable="StateVariable_14"/>
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
          <Constant key="Parameter_44" name="k" value="0.9"/>
        </ListOfConstants>
        <KineticLaw function="Function_38">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_260">
              <SourceParameter reference="Parameter_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_259">
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
          <Constant key="Parameter_45" name="V" value="1"/>
          <Constant key="Parameter_46" name="K" value="0.9"/>
          <Constant key="Parameter_47" name="n" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_39">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_257">
              <SourceParameter reference="Parameter_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="Parameter_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_249">
              <SourceParameter reference="Parameter_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_250">
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
          <Constant key="Parameter_48" name="Km" value="0.2"/>
          <Constant key="Parameter_49" name="V" value="0.7"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_49"/>
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
          <Constant key="Parameter_50" name="V" value="1"/>
          <Constant key="Parameter_51" name="K" value="0.9"/>
          <Constant key="Parameter_52" name="n" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_39">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_257">
              <SourceParameter reference="Parameter_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="Parameter_51"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_249">
              <SourceParameter reference="Parameter_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_250">
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
          <Constant key="Parameter_53" name="Km" value="0.2"/>
          <Constant key="Parameter_54" name="V" value="0.7"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_53"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_54"/>
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
          <Constant key="Parameter_55" name="k" value="0.9"/>
        </ListOfConstants>
        <KineticLaw function="Function_38">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_260">
              <SourceParameter reference="Parameter_55"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_259">
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
          <Constant key="Parameter_56" name="Km" value="2"/>
          <Constant key="Parameter_57" name="V" value="8"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_56"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_57"/>
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
          <Constant key="Parameter_58" name="Km" value="2"/>
          <Constant key="Parameter_59" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_58"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_59"/>
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
          <Constant key="Parameter_60" name="Km" value="2"/>
          <Constant key="Parameter_61" name="V" value="8"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_60"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_61"/>
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
          <Constant key="Parameter_62" name="Km" value="2"/>
          <Constant key="Parameter_63" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_63"/>
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
          <Constant key="Parameter_64" name="Km" value="2"/>
          <Constant key="Parameter_65" name="V" value="8"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_65"/>
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
          <Constant key="Parameter_66" name="Km" value="2"/>
          <Constant key="Parameter_67" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_67"/>
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
          <Constant key="Parameter_68" name="Km" value="2"/>
          <Constant key="Parameter_69" name="V" value="8"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_68"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_69"/>
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
          <Constant key="Parameter_70" name="Km" value="2"/>
          <Constant key="Parameter_71" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_70"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_71"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="dP" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_72" name="Km" value="0.2"/>
          <Constant key="Parameter_73" name="V" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_73"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="dT" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_74" name="Km" value="0.2"/>
          <Constant key="Parameter_75" name="V" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_75"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="Mt dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_76" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_76"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
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
          <Constant key="Parameter_77" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
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
          <Constant key="Parameter_78" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
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
          <Constant key="Parameter_79" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
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
          <Constant key="Parameter_80" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
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
          <Constant key="Parameter_81" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_81"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
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
          <Constant key="Parameter_82" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_82"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
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
          <Constant key="Parameter_83" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_83"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
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
          <Constant key="Parameter_84" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_84"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
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
          <Constant key="Parameter_85" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_85"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
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
          <Constant key="Parameter_86" name="Km" value="0.2"/>
          <Constant key="Parameter_87" name="V" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_86"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_87"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="P2 degradation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_88" name="Km" value="0.2"/>
          <Constant key="Parameter_89" name="V" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_88"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_89"/>
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
          <Constant key="Parameter_90" name="k1" value="1.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_90"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
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
          <Constant key="Parameter_91" name="k1" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_91"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
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
          <Constant key="Parameter_92" name="k1" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_92"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
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
          <Constant key="Parameter_93" name="k1" value="0.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_93"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <StateTemplate>
      <StateTemplateVariable key="StateVariable_3" objectReference="Model_1"/>
      <StateTemplateVariable key="StateVariable_4" objectReference="Compartment_0"/>
      <StateTemplateVariable key="StateVariable_5" objectReference="Metabolite_0"/>
      <StateTemplateVariable key="StateVariable_6" objectReference="Metabolite_1"/>
      <StateTemplateVariable key="StateVariable_7" objectReference="Metabolite_2"/>
      <StateTemplateVariable key="StateVariable_8" objectReference="Metabolite_3"/>
      <StateTemplateVariable key="StateVariable_9" objectReference="Metabolite_4"/>
      <StateTemplateVariable key="StateVariable_10" objectReference="Metabolite_5"/>
      <StateTemplateVariable key="StateVariable_11" objectReference="Metabolite_6"/>
      <StateTemplateVariable key="StateVariable_12" objectReference="Metabolite_7"/>
      <StateTemplateVariable key="StateVariable_13" objectReference="Metabolite_8"/>
      <StateTemplateVariable key="StateVariable_14" objectReference="Metabolite_9"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 1 60221400000000 553160000000000 553160000000000 141869000000000 118191000000000 27483900000000 118191000000000 27483900000000 60221400000000 368354000000000
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_6" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Newton.UseNewton" type="bool" value="1"/>
        <Parameter name="Newton.UseIntegration" type="bool" value="1"/>
        <Parameter name="Newton.UseBackIntegration" type="bool" value="0"/>
        <Parameter name="Newton.acceptNegativeConcentrations" type="bool" value="0"/>
        <Parameter name="Newton.IterationLimit" type="unsignedInteger" value="50"/>
        <Parameter name="Newton.DerivationFactor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Newton.Resolution" type="unsignedFloat" value="1e-009"/>
        <Parameter name="Newton.LSODA.RelativeTolerance" type="unsignedFloat" value="1e-012"/>
        <Parameter name="Newton.LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-006"/>
        <Parameter name="Newton.LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="Newton.LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="Newton.LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_7" name="Time-Course" type="timeCourse" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="960"/>
        <Parameter name="StepSize" type="float" value="0.1"/>
        <Parameter name="Duration" type="float" value="96"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="1"/>
        <Parameter name="LSODA.RelativeTolerance" type="unsignedFloat" value="1e-006"/>
        <Parameter name="Use Default Absolute Tolerance" type="bool" value="1"/>
        <Parameter name="LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-012"/>
        <Parameter name="LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_8" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_6"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="MCA.ModulationFactor" type="unsignedFloat" value="1e-009"/>
      </Method>
    </Task>
    <Task key="Task_9" name="Scan" type="scan" scheduled="false" updateModel="false">
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
    <Task key="Task_10" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="Steady-State" type="key" value=""/>
        <Parameter name="Time-Course" type="key" value="Task_7"/>
        <Parameter name="ObjectiveFunction" type="key" value="Function_37"/>
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
    <Task key="Task_11" name="Parameter Fitting" type="parameterFitting" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_6"/>
        <Parameter name="Time-Course" type="key" value="Task_7"/>
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
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_3" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_4" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Optimization],Object=Description"/>
        <Object cn="String=\[Simulation Counter\]"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="String=\[Best Value\]"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="String=\[Best Parameters\]"/>
      </Header>
      <Body>
        <Object cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Simulation Counter"/>
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
    <Report key="Report_5" name="Parameter Fitting" taskType="parameterFitting" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Parameter Fitting],Object=Description"/>
        <Object cn="String=\[Simulation Counter\]"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="String=\[Best Value\]"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="String=\[Best Parameters\]"/>
      </Header>
      <Body>
        <Object cn="CN=Root,Vector=TaskList[Parameter Fitting],Problem=Parameter Fitting,Reference=Simulation Counter"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,Vector=TaskList[Parameter Fitting],Problem=Parameter Fitting,Reference=Best Value"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,Vector=TaskList[Parameter Fitting],Problem=Parameter Fitting,Reference=Best Parameters"/>
      </Body>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Parameter Fitting],Object=Result"/>
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
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[P0],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Mt" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[Mt],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Mp" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[Mp],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="T0" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[T0],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="P1" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[P1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="P2" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[P2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="T1" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[T1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="T2" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[T2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="C" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[C],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Cn" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
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
