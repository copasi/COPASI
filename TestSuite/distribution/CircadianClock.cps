<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI (http://www.copasi.org) -->
<COPASI xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://calvin.bioinformatics.vt.edu/copasi/schema/copasi.xsd">
  <ListOfFunctions>
    <Function key="Function_13" name="Mass action (irreversible)" type="MassAction" positive="false">
      <MathML>
        <Text>
          k1*PRODUCT&lt;substrate_i&gt;
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_75" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_76" name="substrate" order="1" role="substrate" minOccurs="1" maxOccurs="unbounded"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_37" name="Transcription" type="UserDefined" positive="false">
      <MathML>
        <Text>
          V*K^n/(K^n+modifier^n)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_263" name="V" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_264" name="K" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_265" name="n" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_266" name="modifier" order="3" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_38" name="linear activation" type="UserDefined" positive="false">
      <MathML>
        <Text>
          k*modifier
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_267" name="k" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_268" name="modifier" order="1" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_8" name="Henri-Michaelis-Menten (irreversible)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate/(Km+substrate)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_44" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_45" name="Km" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_46" name="V" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_0" name="Circadian Clock" timeUnit="h" volumeUnit="l" quantityUnit="nMol" stateVariable="StateVariable_11">
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
        This is a model of the Drosophila circadian clock based on the PER and TIM genes, as published in Leloup J.-C. &amp; Goldbeter A. (1999) &quot;Chaos and birhythmicity in a model of circadian oscillations of the PER and TIM proteins in Drosophila&quot; J. Theor. Biol. 198, 445-459
      </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_1" name="cell" stateVariable="StateVariable_12"/>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_6" name="P0" compartment="Compartment_1" status="variable" stateVariable="StateVariable_13"/>
      <Metabolite key="Metabolite_7" name="Mt" compartment="Compartment_1" status="variable" stateVariable="StateVariable_14"/>
      <Metabolite key="Metabolite_8" name="Mp" compartment="Compartment_1" status="variable" stateVariable="StateVariable_15"/>
      <Metabolite key="Metabolite_9" name="T0" compartment="Compartment_1" status="variable" stateVariable="StateVariable_16"/>
      <Metabolite key="Metabolite_10" name="P1" compartment="Compartment_1" status="variable" stateVariable="StateVariable_17"/>
      <Metabolite key="Metabolite_11" name="P2" compartment="Compartment_1" status="variable" stateVariable="StateVariable_18"/>
      <Metabolite key="Metabolite_12" name="T1" compartment="Compartment_1" status="variable" stateVariable="StateVariable_19"/>
      <Metabolite key="Metabolite_13" name="T2" compartment="Compartment_1" status="variable" stateVariable="StateVariable_20"/>
      <Metabolite key="Metabolite_14" name="C" compartment="Compartment_1" status="variable" stateVariable="StateVariable_21"/>
      <Metabolite key="Metabolite_15" name="Cn" compartment="Compartment_1" status="variable" stateVariable="StateVariable_22"/>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_4" name="sP" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_74" name="k" value="0.9"/>
        </ListOfConstants>
        <KineticLaw function="Function_38">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_267">
              <SourceParameter reference="Parameter_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="Mp transcription" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_73" name="V" value="1"/>
          <Constant key="Parameter_72" name="K" value="0.9"/>
          <Constant key="Parameter_71" name="n" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_37">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_263">
              <SourceParameter reference="Parameter_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="Parameter_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="Parameter_71"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="Mp degradation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_70" name="Km" value="0.2"/>
          <Constant key="Parameter_69" name="V" value="0.7"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_70"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_69"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="Mt transcription" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_68" name="V" value="1"/>
          <Constant key="Parameter_67" name="K" value="0.9"/>
          <Constant key="Parameter_66" name="n" value="4"/>
        </ListOfConstants>
        <KineticLaw function="Function_37">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_263">
              <SourceParameter reference="Parameter_68"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="Parameter_67"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="Parameter_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="Mt degradation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_65" name="Km" value="0.2"/>
          <Constant key="Parameter_64" name="V" value="0.7"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_64"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="sT" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_63" name="k" value="0.9"/>
        </ListOfConstants>
        <KineticLaw function="Function_38">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_267">
              <SourceParameter reference="Parameter_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="1P" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_62" name="Km" value="2"/>
          <Constant key="Parameter_61" name="V" value="8"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_61"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="2P" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_60" name="Km" value="2"/>
          <Constant key="Parameter_59" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_60"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_59"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="3P" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_58" name="Km" value="2"/>
          <Constant key="Parameter_57" name="V" value="8"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_58"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_57"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="4P" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_56" name="Km" value="2"/>
          <Constant key="Parameter_55" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_56"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_55"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="1T" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_54" name="Km" value="2"/>
          <Constant key="Parameter_53" name="V" value="8"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_53"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="2T" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_52" name="Km" value="2"/>
          <Constant key="Parameter_51" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_51"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="3T" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_50" name="Km" value="2"/>
          <Constant key="Parameter_108" name="V" value="8"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_108"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="4T" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_109" name="Km" value="2"/>
          <Constant key="Parameter_110" name="V" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_110"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="dP" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_111" name="Km" value="0.2"/>
          <Constant key="Parameter_112" name="V" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_111"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_112"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="dT" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_113" name="Km" value="0.2"/>
          <Constant key="Parameter_114" name="V" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_114"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="Mt dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_115" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="Mp dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_116" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="P0 dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_117" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_117"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="P1 dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_118" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_118"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="P2 dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_119" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_119"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="T0 dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_120" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_120"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="T1 dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_121" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="T2 dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_122" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_122"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="C dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_123" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_123"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="Cn dilution" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_124" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_124"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="T2 degradation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_125" name="Km" value="0.2"/>
          <Constant key="Parameter_126" name="V" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_125"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_126"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="P2 degradation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_127" name="Km" value="0.2"/>
          <Constant key="Parameter_128" name="V" value="2"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_127"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_128"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_32" name="PT binding (forward)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_129" name="k1" value="1.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_129"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_11"/>
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_33" name="PT binding (backward)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_130" name="k1" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_130"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_34" name="C transport (forward)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_131" name="k1" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_131"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="C transport (backward)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_132" name="k1" value="0.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_132"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <StateTemplate>
      <StateTemplateVariable key="StateVariable_11" objectReference="Model_0"/>
      <StateTemplateVariable key="StateVariable_12" objectReference="Compartment_1"/>
      <StateTemplateVariable key="StateVariable_13" objectReference="Metabolite_6"/>
      <StateTemplateVariable key="StateVariable_14" objectReference="Metabolite_7"/>
      <StateTemplateVariable key="StateVariable_15" objectReference="Metabolite_8"/>
      <StateTemplateVariable key="StateVariable_16" objectReference="Metabolite_9"/>
      <StateTemplateVariable key="StateVariable_17" objectReference="Metabolite_10"/>
      <StateTemplateVariable key="StateVariable_18" objectReference="Metabolite_11"/>
      <StateTemplateVariable key="StateVariable_19" objectReference="Metabolite_12"/>
      <StateTemplateVariable key="StateVariable_20" objectReference="Metabolite_13"/>
      <StateTemplateVariable key="StateVariable_21" objectReference="Metabolite_14"/>
      <StateTemplateVariable key="StateVariable_22" objectReference="Metabolite_15"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 1 6.02214e+013 5.5316e+014 5.5316e+014 1.41869e+014 1.18191e+014 2.74839e+013 1.18191e+014 2.74839e+013 6.02214e+013 3.68354e+014
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task name="Steady-State" type="steadyState">
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Newton.UseNewton" type="bool" value="1"/>
        <Parameter name="Newton.UseIntegration" type="bool" value="1"/>
        <Parameter name="Newton.UseBackIntegration" type="bool" value="0"/>
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
    <Task name="Time-Course" type="timeCourse">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="960"/>
        <Parameter name="StepSize" type="float" value="0.1"/>
        <Parameter name="StartTime" type="float" value="0"/>
        <Parameter name="EndTime" type="float" value="96"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="LSODA.RelativeTolerance" type="unsignedFloat" value="1e-006"/>
        <Parameter name="LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-012"/>
        <Parameter name="LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task name="Metabolic Control Analysis" type="metabolicControlAnalysis">
      <Problem>
        <Parameter name="SteadyStateRequested" type="bool" value="1"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="MCA.ModulationFactor" type="unsignedFloat" value="1e-009"/>
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfPlots>
    <PlotSpecification name="Time Course" type="Plot2D" active="Curve2D">
      <ListOfPlotItems>
        <PlotItem name="P0" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[P0],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Mt" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[Mt],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Mp" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[Mp],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="T0" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[T0],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="P1" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[P1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="P2" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[P2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="T1" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[T1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="T2" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[T2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="C" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[C],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Cn" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Circadian Clock,Vector=Compartments[cell],Vector=Metabolites[Cn],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
</COPASI>
