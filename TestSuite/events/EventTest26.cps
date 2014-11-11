<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.14 (Build 89+) (http://www.copasi.org) at 2014-11-11 17:36:19 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="14" versionDevel="89" copasiSourcesModified="1">
  <Model key="Model_16" name="vascular part of the Bold response as modelled by Aubert 2002" simulationType="time" timeUnit="s" volumeUnit="ml" areaUnit="m²" lengthUnit="m" quantityUnit="mmol" type="deterministic" avogadroConstant="6.02214179e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Model_16">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T11:57:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <ListOfCompartments>
      <Compartment key="Compartment_17" name="Venous balloon" simulationType="ode" dimensionality="3">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_17">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:07:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F_in],Reference=Value&gt;-&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F_out],Reference=Value&gt;
        </Expression>
      </Compartment>
    </ListOfCompartments>
    <ListOfModelValues>
      <ModelValue key="ModelValue_222" name="F0" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_222">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T11:57:59Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_223" name="is_rising" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_223">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:00:20Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_191" name="is_falling" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_191">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:00:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_190" name="is_maximum" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_190">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:00:22Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_189" name="slope_up" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_189">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T11:59:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[maximum],Reference=InitialValue&gt;/&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[t_on],Reference=InitialValue&gt;*&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_188" name="alpha_F_in" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_188">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:25:46Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_187" name="maximum" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_187">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:01:28Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F0],Reference=InitialValue&gt;*&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[alpha_F_in],Reference=InitialValue&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_186" name="t_on" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_186">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:27:07Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_185" name="t_end" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_185">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:27:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_184" name="slope_down" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_184">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:04:11Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[maximum],Reference=Value&gt;*(&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[t_on],Reference=Value&gt;+&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[t_end],Reference=Value&gt;-&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time&gt;)/&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[t_on],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_183" name="F_in" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_183">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:08:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F0],Reference=Value&gt;+&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[is_rising],Reference=Value&gt;*&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[slope_up],Reference=Value&gt;+&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[is_maximum],Reference=Value&gt;*&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[maximum],Reference=Value&gt;+&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[is_falling],Reference=Value&gt;*&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[slope_down],Reference=Value&gt;
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_182" name="F_out" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_182">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:10:02Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F0],Reference=Value&gt;*((&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Compartments[Venous balloon],Reference=Volume&gt;/&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Compartments[Venous balloon],Reference=InitialVolume&gt;)^2+(&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Compartments[Venous balloon],Reference=Volume&gt;/&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Compartments[Venous balloon],Reference=InitialVolume&gt;)^(-0.5)*35*(1/&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Compartments[Venous balloon],Reference=InitialVolume&gt;)*&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F_in],Reference=Value&gt;)/(1+&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F0],Reference=Value&gt;*(&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Compartments[Venous balloon],Reference=Volume&gt;/&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Compartments[Venous balloon],Reference=InitialVolume&gt;)^(-0.5)*35*(1/&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Compartments[Venous balloon],Reference=InitialVolume&gt;))
        </Expression>
      </ModelValue>
    </ListOfModelValues>
    <ListOfEvents>
      <Event key="Event_1" name="from increase to stable" fireAtInitialTime="0" persistentTrigger="0">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:13:31Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <TriggerExpression>
          &lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time&gt; == &lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[t_on],Reference=InitialValue&gt;
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="ModelValue_190">
            <Expression>
              1
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_223">
            <Expression>
              0
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_5" name="from decrease to at_rest" fireAtInitialTime="0" persistentTrigger="0">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_5">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:15:30Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <TriggerExpression>
          &lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time&gt; == &lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[t_end],Reference=InitialValue&gt;+&lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[t_on],Reference=InitialValue&gt;
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="ModelValue_191">
            <Expression>
              0
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_0" name="from stable to decrease (end of stimulation)" fireAtInitialTime="0" persistentTrigger="0">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-11-04T12:16:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <TriggerExpression>
          &lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time&gt; == &lt;CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[t_end],Reference=InitialValue&gt;
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="ModelValue_190">
            <Expression>
              0
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_191">
            <Expression>
              1
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
    </ListOfEvents>
    <ListOfModelParameterSets activeSet="ModelParameterSet_0">
      <ModelParameterSet key="ModelParameterSet_0" name="Initial State">
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Compartments[Venous balloon]" value="0.0237" type="Compartment" simulationType="ode"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F0]" value="0.012" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[is_rising]" value="1" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[is_falling]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[is_maximum]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[slope_up]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[alpha_F_in]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[maximum]" value="0.006" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[t_on]" value="5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[t_end]" value="360" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[slope_down]" value="0.438" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F_in]" value="0.012" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F_out]" value="0.012" type="ModelValue" simulationType="assignment"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_16"/>
      <StateTemplateVariable objectReference="Compartment_17"/>
      <StateTemplateVariable objectReference="ModelValue_189"/>
      <StateTemplateVariable objectReference="ModelValue_187"/>
      <StateTemplateVariable objectReference="ModelValue_184"/>
      <StateTemplateVariable objectReference="ModelValue_183"/>
      <StateTemplateVariable objectReference="ModelValue_182"/>
      <StateTemplateVariable objectReference="ModelValue_222"/>
      <StateTemplateVariable objectReference="ModelValue_223"/>
      <StateTemplateVariable objectReference="ModelValue_191"/>
      <StateTemplateVariable objectReference="ModelValue_190"/>
      <StateTemplateVariable objectReference="ModelValue_188"/>
      <StateTemplateVariable objectReference="ModelValue_186"/>
      <StateTemplateVariable objectReference="ModelValue_185"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0.0237 0 0.006 0.438 0.012 0.012 0.012 1 0 0 0.5 5 360 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_12" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_8" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Resolution" type="unsignedFloat" value="1e-09"/>
        <Parameter name="Derivation Factor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Use Newton" type="bool" value="1"/>
        <Parameter name="Use Integration" type="bool" value="1"/>
        <Parameter name="Use Back Integration" type="bool" value="1"/>
        <Parameter name="Accept Negative Concentrations" type="bool" value="0"/>
        <Parameter name="Iteration Limit" type="unsignedInteger" value="50"/>
        <Parameter name="Maximum duration for forward integration" type="unsignedFloat" value="1000000000"/>
        <Parameter name="Maximum duration for backward integration" type="unsignedFloat" value="1000000"/>
      </Method>
    </Task>
    <Task key="Task_11" name="Time-Course" type="timeCourse" scheduled="true" updateModel="false">
      <Report reference="Report_18" target="EventTest26.1.txt" append="0" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="400"/>
        <Parameter name="StepSize" type="float" value="1.5"/>
        <Parameter name="Duration" type="float" value="600"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
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
    <Task key="Task_9" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_7" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_8" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_6" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Subtask" type="cn" value="CN=Root,Vector=TaskList[Steady-State]"/>
        <ParameterText name="ObjectiveExpression" type="expression">
          
        </ParameterText>
        <Parameter name="Maximize" type="bool" value="0"/>
        <Parameter name="Randomize Start Values" type="bool" value="0"/>
        <Parameter name="Calculate Statistics" type="bool" value="1"/>
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
    <Task key="Task_7" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_5" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Maximize" type="bool" value="0"/>
        <Parameter name="Randomize Start Values" type="bool" value="0"/>
        <Parameter name="Calculate Statistics" type="bool" value="1"/>
        <ParameterGroup name="OptimizationItemList">
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
        </ParameterGroup>
        <Parameter name="Steady-State" type="cn" value="CN=Root,Vector=TaskList[Steady-State]"/>
        <Parameter name="Time-Course" type="cn" value="CN=Root,Vector=TaskList[Time-Course]"/>
        <Parameter name="Create Parameter Sets" type="bool" value="0"/>
        <ParameterGroup name="Experiment Set">
        </ParameterGroup>
        <ParameterGroup name="Validation Set">
          <Parameter name="Threshold" type="unsignedInteger" value="5"/>
          <Parameter name="Weight" type="unsignedFloat" value="1"/>
        </ParameterGroup>
      </Problem>
      <Method name="Evolutionary Programming" type="EvolutionaryProgram">
        <Parameter name="Number of Generations" type="unsignedInteger" value="200"/>
        <Parameter name="Population Size" type="unsignedInteger" value="20"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_6" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_4" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_12"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1e-09"/>
      </Method>
    </Task>
    <Task key="Task_5" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_3" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="ExponentNumber" type="unsignedInteger" value="3"/>
        <Parameter name="DivergenceRequested" type="bool" value="1"/>
        <Parameter name="TransientTime" type="float" value="0"/>
      </Problem>
      <Method name="Wolf Method" type="WolfMethod">
        <Parameter name="Orthonormalization Interval" type="unsignedFloat" value="1"/>
        <Parameter name="Overall time" type="unsignedFloat" value="1000"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_4" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_2" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="ILDM (LSODA,Deuflhard)" type="TimeScaleSeparation(ILDM,Deuflhard)">
        <Parameter name="Deuflhard Tolerance" type="unsignedFloat" value="1e-06"/>
      </Method>
    </Task>
    <Task key="Task_3" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_1" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="SubtaskType" type="unsignedInteger" value="1"/>
        <ParameterGroup name="TargetFunctions">
          <Parameter name="SingleObject" type="cn" value=""/>
          <Parameter name="ObjectListType" type="unsignedInteger" value="7"/>
        </ParameterGroup>
        <ParameterGroup name="ListOfVariables">
          <ParameterGroup name="Variables">
            <Parameter name="SingleObject" type="cn" value=""/>
            <Parameter name="ObjectListType" type="unsignedInteger" value="41"/>
          </ParameterGroup>
        </ParameterGroup>
      </Problem>
      <Method name="Sensitivities Method" type="SensitivitiesMethod">
        <Parameter name="Delta factor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Delta minimum" type="unsignedFloat" value="1e-12"/>
      </Method>
    </Task>
    <Task key="Task_2" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_1" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
        <Parameter name="LimitCrossings" type="bool" value="0"/>
        <Parameter name="NumCrossingsLimit" type="unsignedInteger" value="0"/>
        <Parameter name="LimitOutTime" type="bool" value="0"/>
        <Parameter name="LimitOutCrossings" type="bool" value="0"/>
        <Parameter name="PositiveDirection" type="bool" value="1"/>
        <Parameter name="NumOutCrossingsLimit" type="unsignedInteger" value="0"/>
        <Parameter name="LimitUntilConvergence" type="bool" value="0"/>
        <Parameter name="ConvergenceTolerance" type="float" value="1e-06"/>
        <Parameter name="Threshold" type="float" value="0"/>
        <Parameter name="DelayOutputUntilConvergence" type="bool" value="0"/>
        <Parameter name="OutputConvergenceTolerance" type="float" value="1e-06"/>
        <ParameterText name="TriggerExpression" type="expression">
          
        </ParameterText>
        <Parameter name="SingleVariable" type="cn" value=""/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_13" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_0" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_12"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_8" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_7" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_6" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
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
    <Report key="Report_5" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
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
    <Report key="Report_4" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_3" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_2" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Time Scale Separation Analysis],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Time Scale Separation Analysis],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_1" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Sensitivities],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Sensitivities],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_0" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Linear Noise Approximation],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Linear Noise Approximation],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_18" name="Time, Concentrations, Volumes, and Global Quantity Values" taskType="timeCourse" separator="&#x09;" precision="7">
      <Comment>
        A table of time, variable species concentrations, variable compartment volumes, and variable global quantity values.
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time"/>
        <Object cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Compartments[Venous balloon],Reference=Volume"/>
        <Object cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[is_rising],Reference=Value"/>
        <Object cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[is_falling],Reference=Value"/>
        <Object cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[is_maximum],Reference=Value"/>
        <Object cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[slope_up],Reference=Value"/>
        <Object cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[maximum],Reference=Value"/>
        <Object cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[slope_down],Reference=Value"/>
        <Object cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F_in],Reference=Value"/>
        <Object cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F_out],Reference=Value"/>
      </Table>
    </Report>
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="Concentrations, Volumes, and Global Quantity Values" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="Compartments[Venous balloon].Volume" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Compartments[Venous balloon],Reference=Volume"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[is_rising]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[is_rising],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[is_falling]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[is_falling],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[is_maximum]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[is_maximum],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[slope_up]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[slope_up],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[maximum]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[maximum],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[slope_down]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[slope_down],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[F_in]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F_in],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[F_out]" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=vascular part of the Bold response as modelled by Aubert 2002,Vector=Values[F_out],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
  </GUI>
  <SBMLReference file="VascularPartOfBoldResponseAubert2002_false.xml">
    <SBMLMap SBMLid="F0" COPASIkey="ModelValue_222"/>
    <SBMLMap SBMLid="F_in" COPASIkey="ModelValue_183"/>
    <SBMLMap SBMLid="F_out" COPASIkey="ModelValue_182"/>
    <SBMLMap SBMLid="Venous_balloon" COPASIkey="Compartment_17"/>
    <SBMLMap SBMLid="alpha_F_in" COPASIkey="ModelValue_188"/>
    <SBMLMap SBMLid="is_falling" COPASIkey="ModelValue_191"/>
    <SBMLMap SBMLid="is_maximum" COPASIkey="ModelValue_190"/>
    <SBMLMap SBMLid="is_rising" COPASIkey="ModelValue_223"/>
    <SBMLMap SBMLid="maximum" COPASIkey="ModelValue_187"/>
    <SBMLMap SBMLid="slope_down" COPASIkey="ModelValue_184"/>
    <SBMLMap SBMLid="slope_up" COPASIkey="ModelValue_189"/>
    <SBMLMap SBMLid="t_end" COPASIkey="ModelValue_185"/>
    <SBMLMap SBMLid="t_on" COPASIkey="ModelValue_186"/>
  </SBMLReference>
</COPASI>
