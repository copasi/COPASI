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
  <Model key="Model_0" name="NoName" timeUnit="s" volumeUnit="ml" quantityUnit="mMol" stateVariable="StateVariable_246">
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
        
      </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="compartment" stateVariable="StateVariable_247"/>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="me" compartment="Compartment_0" status="variable" stateVariable="StateVariable_248"/>
      <Metabolite key="Metabolite_1" name="dsfg" compartment="Compartment_0" status="variable" stateVariable="StateVariable_249"/>
      <Metabolite key="Metabolite_2" name="a" compartment="Compartment_0" status="variable" stateVariable="StateVariable_250"/>
      <Metabolite key="Metabolite_3" name="b" compartment="Compartment_0" status="variable" stateVariable="StateVariable_251"/>
      <Metabolite key="Metabolite_7" name="c" compartment="Compartment_0" status="variable" stateVariable="StateVariable_252"/>
      <Metabolite key="Metabolite_10" name="d" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_253"/>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="reaction" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_68" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_68"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="reaction_1" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_69" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="Parameter_69"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <StateTemplate>
      <StateTemplateVariable key="StateVariable_246" objectReference="Model_0"/>
      <StateTemplateVariable key="StateVariable_247" objectReference="Compartment_0"/>
      <StateTemplateVariable key="StateVariable_248" objectReference="Metabolite_0"/>
      <StateTemplateVariable key="StateVariable_249" objectReference="Metabolite_1"/>
      <StateTemplateVariable key="StateVariable_250" objectReference="Metabolite_2"/>
      <StateTemplateVariable key="StateVariable_251" objectReference="Metabolite_3"/>
      <StateTemplateVariable key="StateVariable_252" objectReference="Metabolite_7"/>
      <StateTemplateVariable key="StateVariable_253" objectReference="Metabolite_10"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 1 6.02214e+20 6.02214e+20 6.02214e+20 6.02214e+20 6.02214e+19 6.02214e+19
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task name="Stead-State" type="SteadyState">
      <Report target="" append="1">
      </Report>
      <Problem>
        <InitialState type="SteadyState">
        </InitialState>
        <Parameter name="JacobianRequested" type="float" value="0x8485ed8">
        </Parameter>
        <ParameterGroup name="JacobianRequested">
        </ParameterGroup>
      </Problem>
      <Method name="Newton.UseNewton" type="SteadyState">
        <Parameter name="Newton.UseNewton" type="SteadyState" value="0x8485f98">
        </Parameter>
      </Method>
    </Task>
    <Task name="Time-Course" type="TimeCourse">
      <Report target="" append="1">
      </Report>
      <Problem>
        <InitialState type="TimeCourse">
        </InitialState>
        <Parameter name="StepSize" type="unsignedFloat" value="0x8485978">
        </Parameter>
        <ParameterGroup name="StepSize">
        </ParameterGroup>
      </Problem>
      <Method name="LSODA.AbsoluteTolerance" type="TimeCourse">
        <Parameter name="LSODA.AbsoluteTolerance" type="TimeCourse" value="0x84870d0">
        </Parameter>
      </Method>
    </Task>
  </ListOfTasks>
</COPASI>
