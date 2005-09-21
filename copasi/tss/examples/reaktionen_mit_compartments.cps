<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.0 Debug 13++ (http://www.copasi.org) at 2005-08-30 11:26:59 UTC -->
<COPASI xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://calvin.bioinformatics.vt.edu/copasi/schema/copasi.xsd" versionMajor="0" versionMinor="1">
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
    <Function key="Function_14" name="Mass action (reversible)" type="MassAction" positive="true">
      <MathML>
        <Text>
          k1*PRODUCT&lt;substrate_i&gt;-k2*PRODUCT&lt;product_j&gt;
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_77" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_78" name="substrate" order="1" role="substrate" minOccurs="1" maxOccurs="unbounded"/>
        <ParameterDescription key="FunctionParameter_79" name="k2" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_80" name="product" order="3" role="product" minOccurs="1" maxOccurs="unbounded"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_30" name="Specific activation (rev)" type="PreDefined" positive="true">
      <MathML>
        <Text>
          (Vf*substrate/Kms-Vr*product/Kmp)*Activator/(Ka+(1+substrate/Kms+product/Kmp)*Activator)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_213" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_214" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_215" name="Activator" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_216" name="Kms" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_217" name="Kmp" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_218" name="Vf" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_219" name="Vr" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_220" name="Ka" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_37" name="function_with_volume" type="UserDefined" positive="true">
      <MathML>
        <Text>
          Subs*k1*v

        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_441" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_439" name="Subs" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_444" name="v" order="2" role="volume"/>
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
  <Model key="Model_1" name="New Model" timeUnit="s" volumeUnit="ml" quantityUnit="mMol" stateVariable="StateVariable_59">
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
        
      </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_1" name="c1" stateVariable="StateVariable_60"/>
      <Compartment key="Compartment_0" name="c2" stateVariable="StateVariable_61"/>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_24" name="B" compartment="Compartment_1" status="variable" stateVariable="StateVariable_62"/>
      <Metabolite key="Metabolite_17" name="C" compartment="Compartment_1" status="variable" stateVariable="StateVariable_63"/>
      <Metabolite key="Metabolite_20" name="D" compartment="Compartment_1" status="variable" stateVariable="StateVariable_64"/>
      <Metabolite key="Metabolite_21" name="E" compartment="Compartment_1" status="variable" stateVariable="StateVariable_65"/>
      <Metabolite key="Metabolite_14" name="F" compartment="Compartment_1" status="variable" stateVariable="StateVariable_66"/>
      <Metabolite key="Metabolite_11" name="G" compartment="Compartment_1" status="variable" stateVariable="StateVariable_67"/>
      <Metabolite key="Metabolite_8" name="H" compartment="Compartment_1" status="variable" stateVariable="StateVariable_68"/>
      <Metabolite key="Metabolite_23" name="A" compartment="Compartment_0" status="variable" stateVariable="StateVariable_69"/>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_13" name="r_2_compartments" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_109" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="r_1_compartment" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_110" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_110"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="r_1_comp_revers" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_111" name="k1" value="0.1"/>
          <Constant key="Parameter_112" name="k2" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_77">
              <SourceParameter reference="Parameter_111"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Parameter_112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="r_2_comps_revers" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_117" name="k1" value="0.1"/>
          <Constant key="Parameter_113" name="k2" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_77">
              <SourceParameter reference="Parameter_117"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Parameter_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="r_with_function" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_114" name="Km" value="0.1"/>
          <Constant key="Parameter_118" name="V" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_118"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="r_with_function_modifier" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_119" name="Kms" value="0.1"/>
          <Constant key="Parameter_120" name="Kmp" value="0.1"/>
          <Constant key="Parameter_121" name="Vf" value="0.1"/>
          <Constant key="Parameter_122" name="Vr" value="0.1"/>
          <Constant key="Parameter_123" name="Ka" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_30">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_213">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_214">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_215">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_216">
              <SourceParameter reference="Parameter_119"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_217">
              <SourceParameter reference="Parameter_120"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_218">
              <SourceParameter reference="Parameter_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_219">
              <SourceParameter reference="Parameter_122"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_220">
              <SourceParameter reference="Parameter_123"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="r_with_volume" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_0" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_37">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_441">
              <SourceParameter reference="Parameter_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_439">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_444">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="r_with_volume_2" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_1" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_37">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_441">
              <SourceParameter reference="Parameter_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_439">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_444">
              <SourceParameter reference="Compartment_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <StateTemplate>
      <StateTemplateVariable key="StateVariable_59" objectReference="Model_1"/>
      <StateTemplateVariable key="StateVariable_60" objectReference="Compartment_1"/>
      <StateTemplateVariable key="StateVariable_61" objectReference="Compartment_0"/>
      <StateTemplateVariable key="StateVariable_62" objectReference="Metabolite_24"/>
      <StateTemplateVariable key="StateVariable_63" objectReference="Metabolite_17"/>
      <StateTemplateVariable key="StateVariable_64" objectReference="Metabolite_20"/>
      <StateTemplateVariable key="StateVariable_65" objectReference="Metabolite_21"/>
      <StateTemplateVariable key="StateVariable_66" objectReference="Metabolite_14"/>
      <StateTemplateVariable key="StateVariable_67" objectReference="Metabolite_11"/>
      <StateTemplateVariable key="StateVariable_68" objectReference="Metabolite_8"/>
      <StateTemplateVariable key="StateVariable_69" objectReference="Metabolite_23"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 1 1 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_6" name="Steady-State" type="steadyState" scheduled="false">
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="Deterministic(LSODA)">
        <Parameter name="Newton.UseNewton" type="bool" value="1"/>
        <Parameter name="Newton.UseIntegration" type="bool" value="1"/>
        <Parameter name="Newton.UseBackIntegration" type="bool" value="1"/>
        <Parameter name="Newton.acceptNegativeConcentrations" type="bool" value="0"/>
        <Parameter name="Newton.IterationLimit" type="unsignedInteger" value="50"/>
        <Parameter name="Newton.DerivationFactor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Newton.Resolution" type="unsignedFloat" value="1e-09"/>
        <Parameter name="Newton.LSODA.RelativeTolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Newton.LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Newton.LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="Newton.LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="Newton.LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_7" name="Time-Course" type="timeCourse" scheduled="false">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="StartTime" type="float" value="0"/>
        <Parameter name="EndTime" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Stochastic">
        <Parameter name="LSODA.RelativeTolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_8" name="Scan" type="scan" scheduled="false">
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="1"/>
        <ParameterGroup name="ScanItems">
        </ParameterGroup>
        <Parameter name="Output in subtask" type="bool" value="1"/>
        <Parameter name="Adjust initial conditions" type="bool" value="0"/>
      </Problem>
      <Method name="Scan Framework" type="TimeScaleSeparationMethod">
      </Method>
    </Task>
    <Task key="Task_9" name="Optimization" type="optimization" scheduled="false">
      <Problem>
        <ParameterGroup name="OptimizationItemList">
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
        </ParameterGroup>
        <Parameter name="Steady-State" type="key" value=""/>
        <Parameter name="Time-Course" type="key" value=""/>
        <Parameter name="ObjectiveFunction" type="key" value=""/>
        <Parameter name="Maximize" type="bool" value="0"/>
      </Problem>
      <Method name="Random Search" type="RandomSearch">
        <Parameter name="Number of Iterations" type="unsignedInteger" value="100000"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_10" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false">
      <Problem>
        <Parameter name="SteadyStateRequested" type="bool" value="1"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="ScanFramework">
        <Parameter name="MCA.ModulationFactor" type="unsignedFloat" value="1e-09"/>
      </Method>
    </Task>
    <Task key="Task_0" name="Time scale separation" type="timeScaleSeparation" scheduled="false">
      <Problem>
      </Problem>
      <Method name="Time scale separation Method" type="">
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_2" name="Steady-State" taskType="steadyState" separator="&#x09;">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_3" name="Optimization" taskType="optimization" separator="&#x09;">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Simulation Counter"/>
        <Object cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Value"/>
        <Object cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Parameters"/>
      </Table>
    </Report>
  </ListOfReports>
  <GUI>
  </GUI>
</COPASI>
