<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI (http://www.copasi.org) -->
<COPASI xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://calvin.bioinformatics.vt.edu/copasi/schema/copasi.xsd">
  <ListOfFunctions>
    <Function key="Function_37" name="Linear Activation" type="UserDefined" positive="false">
      <MathML>
        <Text>
          Activator*k
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_255" name="Activator" order="0" role="modifier"/>
        <ParameterDescription key="FunctionParameter_256" name="k" order="1" role="constant"/>
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
        <ParameterDescription key="FunctionParameter_259" name="V" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_260" name="Km" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_6" name="Constant flux (irreversible)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          v
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_42" name="v" order="0" role="constant"/>
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
  <Model key="Model_1" name="Kummer calcium model" timeUnit="s" volumeUnit="ml" quantityUnit="nMol" stateVariable="StateVariable_2">
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
        Simplified (3-variable) calcium oscillation model
Kummer et al. (2000) Biophys. J. 79, 1188-1195
      </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="compartment" stateVariable="StateVariable_3"/>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="a" compartment="Compartment_0" status="variable" stateVariable="StateVariable_4"/>
      <Metabolite key="Metabolite_1" name="b" compartment="Compartment_0" status="variable" stateVariable="StateVariable_5"/>
      <Metabolite key="Metabolite_2" name="c" compartment="Compartment_0" status="variable" stateVariable="StateVariable_6"/>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="R1" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_55" name="v" value="0.212"/>
        </ListOfConstants>
        <KineticLaw function="Function_6">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_42">
              <SourceParameter reference="Parameter_55"/>
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
          <Constant key="Parameter_56" name="k" value="2.9"/>
        </ListOfConstants>
        <KineticLaw function="Function_37">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_255">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_256">
              <SourceParameter reference="Parameter_56"/>
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
          <Constant key="Parameter_57" name="V" value="1"/>
          <Constant key="Parameter_58" name="Km" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_38">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_257">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_259">
              <SourceParameter reference="Parameter_57"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_260">
              <SourceParameter reference="Parameter_58"/>
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
          <Constant key="Parameter_59" name="V" value="1"/>
          <Constant key="Parameter_60" name="Km" value="1"/>
        </ListOfConstants>
        <KineticLaw function="Function_38">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_257">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_259">
              <SourceParameter reference="Parameter_59"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_260">
              <SourceParameter reference="Parameter_60"/>
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
          <Constant key="Parameter_61" name="k" value="1.24"/>
        </ListOfConstants>
        <KineticLaw function="Function_37">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_255">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_256">
              <SourceParameter reference="Parameter_61"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="R6" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_62" name="Km" value="29.09"/>
          <Constant key="Parameter_63" name="V" value="32.24"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_63"/>
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
          <Constant key="Parameter_64" name="k" value="13.58"/>
        </ListOfConstants>
        <KineticLaw function="Function_37">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_255">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_256">
              <SourceParameter reference="Parameter_64"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="R8" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_65" name="Km" value="0.16"/>
          <Constant key="Parameter_66" name="V" value="153"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="Parameter_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="Parameter_66"/>
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
      <StateTemplateVariable key="StateVariable_6" objectReference="Metabolite_2"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 5e-14 0.301107 0.301107 0.301107
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
    <Task name="Time-Course" type="timeCourse">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="1000"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="StartTime" type="float" value="0"/>
        <Parameter name="EndTime" type="float" value="10"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="LSODA.RelativeTolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task name="Scan" type="scan">
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="0"/>
        <ParameterGroup name="ScanItems" type="group">
          <ParameterGroup name="ScanItem" type="group">
            <Parameter name="Number of steps" type="unsignedInteger" value="5"/>
            <Parameter name="Type" type="unsignedInteger" value="1"/>
            <Parameter name="Object" type="string" value="CN=Root,Model=Kummer calcium model,Vector=Reactions[R1],ParameterGroup=Parameters,Parameter=v"/>
            <Parameter name="Minimum" type="float" value="0.34"/>
            <Parameter name="Maximum" type="float" value="0.78"/>
          </ParameterGroup>
          <ParameterGroup name="ScanItem" type="group">
            <Parameter name="Number of steps" type="unsignedInteger" value="3"/>
            <Parameter name="Type" type="unsignedInteger" value="0"/>
            <Parameter name="Object" type="string" value=""/>
          </ParameterGroup>
        </ParameterGroup>
        <Parameter name="Output in subtask" type="bool" value="0"/>
        <Parameter name="Adjust initial conditions" type="bool" value="1"/>
      </Problem>
      <Method name="Scan Framework" type="ScanFramework">
        <Parameter name="Random Number Generator" type="string" value="Mersenne Twister"/>
        <Parameter name="Random Number Seed" type="integer" value="0"/>
      </Method>
    </Task>
    <Task name="Metabolic Control Analysis" type="metabolicControlAnalysis">
      <Problem>
        <Parameter name="SteadyStateRequested" type="bool" value="1"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="MCA.ModulationFactor" type="unsignedFloat" value="1e-09"/>
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfPlots>
    <PlotSpecification name="ConcentrationPlot" type="Plot2D" active="Curve2D">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="[a]" type="Curve2D">
          <Parameter name="withLines" type="bool" value="1"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Kummer calcium model,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Kummer calcium model,Vector=Compartments[compartment],Vector=Metabolites[a],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[b]" type="Curve2D">
          <Parameter name="withLines" type="bool" value="1"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Kummer calcium model,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Kummer calcium model,Vector=Compartments[compartment],Vector=Metabolites[b],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[c]" type="Curve2D">
          <Parameter name="withLines" type="bool" value="1"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Kummer calcium model,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Kummer calcium model,Vector=Compartments[compartment],Vector=Metabolites[c],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
</COPASI>
