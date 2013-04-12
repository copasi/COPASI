<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.0 Debug 13++ (http://www.copasi.org) at 2005-08-12 19:37:26 UTC -->
<COPASI xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://calvin.bioinformatics.vt.edu/copasi/schema/copasi.xsd" versionMajor="0" versionMinor="1">
  <ListOfFunctions>
    <Function key="Function_37" name="function_4_R" type="UserDefined" positive="true">
      <MathML>
        <Text>
          &quot;f  \&quot;\\&quot;(S1)/c
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_270" name="S1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_275" name="c" order="1" role="volume"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_41" name="f  &quot;\" type="UserDefined" positive="true">
      <MathML>
        <Text>
          0.5*P
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_269" name="P" order="0" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_0" name="Call Node Test" timeUnit="s" volumeUnit="l" quantityUnit="Mol" stateVariable="StateVariable_10">
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
        This is a test case for a function using a call node.

The called function name is not an ID and it contains spaces as well as the character &quot; and \ which must be escaped.
      </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_1" name="c" stateVariable="StateVariable_11" sbmlid="c"/>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_3" name="S1" compartment="Compartment_1" status="variable" stateVariable="StateVariable_12" sbmlid="S1"/>
      <Metabolite key="Metabolite_4" name="S2" compartment="Compartment_1" status="variable" stateVariable="StateVariable_13" sbmlid="S2"/>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_1" name="R" reversible="true" sbmlid="R">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <KineticLaw function="Function_37">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <StateTemplate>
      <StateTemplateVariable key="StateVariable_10" objectReference="Model_0"/>
      <StateTemplateVariable key="StateVariable_11" objectReference="Compartment_1"/>
      <StateTemplateVariable key="StateVariable_12" objectReference="Metabolite_3"/>
      <StateTemplateVariable key="StateVariable_13" objectReference="Metabolite_4"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 1 9.03321e+008 9.03321e+008
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_0" name="Time-Course" type="timeCourse" scheduled="true">
      <Report reference="Report_0" target="testout.CSV" append="0"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="50"/>
        <Parameter name="StepSize" type="float" value="1"/>
        <Parameter name="StartTime" type="float" value="0"/>
        <Parameter name="EndTime" type="float" value="50"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Stochastic">
        <Parameter name="LSODA.RelativeTolerance" type="unsignedFloat" value="1e-006"/>
        <Parameter name="LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-012"/>
        <Parameter name="LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_1" name="Steady-State" type="steadyState" scheduled="false">
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
        <Parameter name="Newton.Resolution" type="unsignedFloat" value="1e-009"/>
        <Parameter name="Newton.LSODA.RelativeTolerance" type="unsignedFloat" value="1e-006"/>
        <Parameter name="Newton.LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-012"/>
        <Parameter name="Newton.LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="Newton.LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="Newton.LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_2" name="Scan" type="scan" scheduled="false">
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
    <Task key="Task_3" name="Optimization" type="optimization" scheduled="false">
      <Problem>
        <ParameterGroup name="OptimizationItemList">
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
        </ParameterGroup>
        <Parameter name="Steady-State" type="key" value=""/>
        <Parameter name="Time-Course" type="key" value="Task_0"/>
        <Parameter name="ObjectiveFunction" type="key" value="Function_42"/>
        <Parameter name="Maximize" type="bool" value="0"/>
      </Problem>
      <Method name="Random Search" type="RandomSearch">
        <Parameter name="Number of Iterations" type="unsignedInteger" value="100000"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_4" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false">
      <Problem>
        <Parameter name="SteadyStateRequested" type="bool" value="1"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="ScanFramework">
        <Parameter name="MCA.ModulationFactor" type="unsignedFloat" value="1e-009"/>
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_0" name="ReportDefinition_0" taskType="timeCourse" separator="&#x09;">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          
        </body>
      </Comment>
      <Table printTitle="0">
        <Object cn="CN=Root,Model=Call Node Test,Reference=Time"/>
        <Object cn="CN=Root,Model=Call Node Test,Vector=Compartments[c],Vector=Metabolites[S1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=Call Node Test,Vector=Compartments[c],Vector=Metabolites[S2],Reference=Concentration"/>
      </Table>
    </Report>
    <Report key="Report_1" name="Steady-State" taskType="steadyState" separator="&#x09;">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Body>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Body>
    </Report>
    <Report key="Report_4" name="Optimization" taskType="optimization" separator="&#x09;">
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
  <ListOfPlots>
    <PlotSpecification name="ConcentrationPlot" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="[S1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Call Node Test,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Call Node Test,Vector=Compartments[c],Vector=Metabolites[S1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[S2]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Call Node Test,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Call Node Test,Vector=Compartments[c],Vector=Metabolites[S2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
  </GUI>
</COPASI>
