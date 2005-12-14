<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.0 Build 15 (http://www.copasi.org) at 2005-11-08 14:00:43 UTC -->
<COPASI xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://calvin.bioinformatics.vt.edu/copasi/schema/copasi.xsd" versionMajor="0" versionMinor="1">
  <ListOfFunctions>
    <Function key="Function_37" name="Linear Activation" type="UserDefined" positive="false">
      <MathML>
        <Text>
          Activator*k
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_260" name="Activator" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_259" name="k" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_38" name="Irr Michaelis-Menten (enzyme)" type="UserDefined" positive="false">
      <MathML>
        <Text>
          V*E*S/(Km+S)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_257" name="S" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_258" name="E" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_249" name="V" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_250" name="Km" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_6" name="Constant flux (irreversible)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          v
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_49" name="v" order="0" role="constant"/>
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
  <Model key="Model_1" name="Kummer calcium model" timeUnit="s" volumeUnit="ml" quantityUnit="mMol" stateVariable="StateVariable_3">
    <Comment>
<body xmlns="http://www.w3.org/1999/xhtml">
        Simplified (3-variable) calcium oscillation model
Kummer et al. (2000) Biophys. J. 79, 1188-1195
      </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="compartment" stateVariable="StateVariable_4"/>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="a" compartment="Compartment_0" status="variable" stateVariable="StateVariable_5"/>
      <Metabolite key="Metabolite_1" name="b" compartment="Compartment_0" status="variable" stateVariable="StateVariable_6"/>
      <Metabolite key="Metabolite_2" name="c" compartment="Compartment_0" status="variable" stateVariable="StateVariable_7"/>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="R1" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_37" name="v" value="0.212"/>
        </ListOfConstants>
        <KineticLaw function="Function_6">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="Parameter_37"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="R2" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_38" name="k" value="2.9"/>
        </ListOfConstants>
        <KineticLaw function="Function_37">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_260">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_259">
              <SourceParameter reference="Parameter_38"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="R3" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_39" name="V" value="1.52"/>
          <Constant key="Parameter_40" name="Km" value="0.19"/>
        </ListOfConstants>
        <KineticLaw function="Function_38">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_257">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_249">
              <SourceParameter reference="Parameter_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_250">
              <SourceParameter reference="Parameter_40"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="R4" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_41" name="V" value="4.88"/>
          <Constant key="Parameter_42" name="Km" value="1.18"/>
        </ListOfConstants>
        <KineticLaw function="Function_38">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_257">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_249">
              <SourceParameter reference="Parameter_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_250">
              <SourceParameter reference="Parameter_42"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="R5" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_43" name="k" value="1.24"/>
        </ListOfConstants>
        <KineticLaw function="Function_37">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_260">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_259">
              <SourceParameter reference="Parameter_43"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="R6" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_44" name="Km" value="29.09"/>
          <Constant key="Parameter_45" name="V" value="32.24"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_45"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="R7" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_46" name="k" value="13.58"/>
        </ListOfConstants>
        <KineticLaw function="Function_37">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_260">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_259">
              <SourceParameter reference="Parameter_46"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="R8" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_47" name="Km" value="0.16"/>
          <Constant key="Parameter_48" name="V" value="153"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_48"/>
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
    </StateTemplate>
    <InitialState type="initialState">
      0 1e-18 4817.71 4817.71 4817.71
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_5" name="Steady-State" type="steadyState" scheduled="true">
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Newton.UseNewton" type="bool" value="0"/>
        <Parameter name="Newton.UseIntegration" type="bool" value="0"/>
        <Parameter name="Newton.UseBackIntegration" type="bool" value="1"/>
        <Parameter name="Newton.acceptNegativeConcentrations" type="bool" value="0"/>
        <Parameter name="Newton.IterationLimit" type="unsignedInteger" value="50"/>
        <Parameter name="Newton.DerivationFactor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Newton.Resolution" type="unsignedFloat" value="1e-09"/>
        <Parameter name="Newton.LSODA.RelativeTolerance" type="unsignedFloat" value="1e-08"/>
        <Parameter name="Newton.LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-14"/>
        <Parameter name="Newton.LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="Newton.LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="Newton.LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_6" name="Time-Course" type="timeCourse" scheduled="true">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="20000"/>
        <Parameter name="StepSize" type="float" value="0.005"/>
        <Parameter name="StartTime" type="float" value="0"/>
        <Parameter name="EndTime" type="float" value="100"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="LSODA.RelativeTolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_7" name="Scan" type="scan" scheduled="false">
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
    <Task key="Task_8" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false">
      <Problem>
        <Parameter name="SteadyStateRequested" type="bool" value="1"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="MCA.ModulationFactor" type="unsignedFloat" value="1e-09"/>
      </Method>
    </Task>
    <Task key="Task_0" name="Optimization" type="optimization" scheduled="false">
      <Problem>
        <Parameter name="Steady-State" type="key" value=""/>
        <Parameter name="Time-Course" type="key" value=""/>
        <Parameter name="ObjectiveFunction" type="key" value=""/>
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
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_1" name="Steady-State" taskType="steadyState" separator="&#x09;">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_0" name="Optimization" taskType="optimization" separator="&#x09;">
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
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="Particle numbers plot" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="a.ParticleNumber" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Kummer calcium model,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Kummer calcium model,Vector=Compartments[compartment],Vector=Metabolites[a],Reference=ParticleNumber"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="b.ParticleNumber" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Kummer calcium model,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Kummer calcium model,Vector=Compartments[compartment],Vector=Metabolites[b],Reference=ParticleNumber"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="c.ParticleNumber" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Kummer calcium model,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Kummer calcium model,Vector=Compartments[compartment],Vector=Metabolites[c],Reference=ParticleNumber"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
  </GUI>
</COPASI>
