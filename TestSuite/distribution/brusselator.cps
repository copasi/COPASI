<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.0 Debug 17++ (http://www.copasi.org) at 2006-01-04 16:39:24 UTC -->
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
  </ListOfFunctions>
  <Model key="Model_1" name="The Brusselator" timeUnit="s" volumeUnit="ml" quantityUnit="mMol" stateVariable="StateVariable_3">
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
        The famous Brusselator model in which a chemical species X catalyses
its own formation. In a certain region of parameter space the Brusselator
can function in a limit cycle regime around an unstable steady state.

Run this simulation and then check the report file to see how Gepasi can find an unstable steady state, and calculate the eigenvalues of the Jacobian matrix.
      </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="compartment" stateVariable="StateVariable_4"/>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="X" compartment="Compartment_0" status="variable" stateVariable="StateVariable_5"/>
      <Metabolite key="Metabolite_1" name="Y" compartment="Compartment_0" status="variable" stateVariable="StateVariable_6"/>
      <Metabolite key="Metabolite_5" name="A" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_7"/>
      <Metabolite key="Metabolite_4" name="B" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_8"/>
      <Metabolite key="Metabolite_3" name="D" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_9"/>
      <Metabolite key="Metabolite_2" name="E" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_10"/>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="R1" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_44" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="R2" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="2"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="3"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_45" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Metabolite_0"/>
              <SourceParameter reference="Metabolite_0"/>
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="R3" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_46" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Metabolite_0"/>
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="R4" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_47" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Metabolite_0"/>
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
      <StateTemplateVariable key="StateVariable_7" objectReference="Metabolite_5"/>
      <StateTemplateVariable key="StateVariable_8" objectReference="Metabolite_4"/>
      <StateTemplateVariable key="StateVariable_9" objectReference="Metabolite_3"/>
      <StateTemplateVariable key="StateVariable_10" objectReference="Metabolite_2"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 1 1.80664e+021 1.80664e+021 3.01107e+020 1.80664e+021 0 0
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
        <Parameter name="Newton.UseIntegration" type="bool" value="0"/>
        <Parameter name="Newton.UseBackIntegration" type="bool" value="0"/>
        <Parameter name="Newton.acceptNegativeConcentrations" type="bool" value="0"/>
        <Parameter name="Newton.IterationLimit" type="unsignedInteger" value="50"/>
        <Parameter name="Newton.DerivationFactor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Newton.Resolution" type="unsignedFloat" value="1e-009"/>
        <Parameter name="Newton.LSODA.RelativeTolerance" type="unsignedFloat" value="1e-006"/>
        <Parameter name="Newton.LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-012"/>
        <Parameter name="Newton.LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="Newton.LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="Newton.LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_7" name="Time-Course" type="timeCourse" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="200"/>
        <Parameter name="StepSize" type="float" value="0.5"/>
        <Parameter name="Duration" type="float" value="100"/>
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
    <PlotSpecification name="ConcentrationPlot" type="Plot2D" active="0">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="X" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[X],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Y" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[Y],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="E" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[E],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="D" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[D],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="B" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[B],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="A" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
  </GUI>
</COPASI>
