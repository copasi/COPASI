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
  </ListOfFunctions>
  <Model key="Model_1" name="The Brusselator" timeUnit="s" volumeUnit="ml" quantityUnit="mMol" stateVariable="StateVariable_2">
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
        The famous Brusselator model in which a chemical species X catalyses
its own formation. In a certain region of parameter space the Brusselator
can function in a limit cycle regime around an unstable steady state.

Run this simulation and then check the report file to see how Gepasi can find an unstable steady state, and calculate the eigenvalues of the Jacobian matrix.
      </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="compartment" stateVariable="StateVariable_3"/>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="X" compartment="Compartment_0" status="variable" stateVariable="StateVariable_4"/>
      <Metabolite key="Metabolite_1" name="Y" compartment="Compartment_0" status="variable" stateVariable="StateVariable_5"/>
      <Metabolite key="Metabolite_5" name="E" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_6"/>
      <Metabolite key="Metabolite_4" name="D" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_7"/>
      <Metabolite key="Metabolite_3" name="B" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_8"/>
      <Metabolite key="Metabolite_2" name="A" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_9"/>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="R1" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_79" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_2"/>
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
          <Constant key="Parameter_80" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
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
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_81" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_81"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_0"/>
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="R4" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_82" name="k1" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_82"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <StateTemplate>
      <StateTemplateVariable key="StateVariable_2" objectReference="Model_1"/>
      <StateTemplateVariable key="StateVariable_3" objectReference="Compartment_0"/>
      <StateTemplateVariable key="StateVariable_4" objectReference="Metabolite_0"/>
      <StateTemplateVariable key="StateVariable_5" objectReference="Metabolite_1"/>
      <StateTemplateVariable key="StateVariable_6" objectReference="Metabolite_5"/>
      <StateTemplateVariable key="StateVariable_7" objectReference="Metabolite_4"/>
      <StateTemplateVariable key="StateVariable_8" objectReference="Metabolite_3"/>
      <StateTemplateVariable key="StateVariable_9" objectReference="Metabolite_2"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 1 1.80664e+021 1.80664e+021 0 0 1.80664e+021 3.01107e+020
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task name="Steady-State" type="steadyState">
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Newton.UseNewton" type="bool" value="0"/>
        <Parameter name="Newton.UseIntegration" type="bool" value="0"/>
        <Parameter name="Newton.UseBackIntegration" type="bool" value="0"/>
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
    <Task name="Time-Course" type="timeCourse">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="200"/>
        <Parameter name="StepSize" type="float" value="0.5"/>
        <Parameter name="StartTime" type="float" value="0"/>
        <Parameter name="EndTime" type="float" value="100"/>
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
    <PlotSpecification name="ConcentrationPlot" type="Plot2D" active="Curve2D">
      <ListOfPlotItems>
        <PlotItem name="X" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[X],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Y" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[Y],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="E" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[E],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="D" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[D],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="B" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[B],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="A" type="Curve2D">
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
</COPASI>
