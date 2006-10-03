<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.1 (Build 19 Feature Preview) (http://www.copasi.org) at 2006-10-03 16:42:32 UTC -->
<COPASI xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://www.copasi.org/static/schema.xsd" versionMajor="1" versionMinor="0" versionDevel="19">
  <ListOfFunctions>
    <Function key="Function_13" name="Mass action (irreversible)" type="MassAction" reversible="false">
      <MathML>
        <Text>
          k1*PRODUCT&lt;substrate_i&gt;
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_81" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_79" name="substrate" order="1" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_40" name="Objective Function" type="Expression">
      <MathML>
        <Text>
          
        </Text>
      </MathML>
    </Function>
  </ListOfFunctions>
  <Model key="Model_1" name="NF-kB signaling" timeUnit="s" volumeUnit="ml" quantityUnit="µmol" type="deterministic">
    <Comment>
      <html xmlns="http://www.w3.org/1999/xhtml"><head><meta name="qrichtext" content="1" /></head><body style="font-size:8pt;font-family:MS Shell Dlg">
<p style="margin-top:18px"><span style="font-size:16pt;font-weight:600">Model of oscillating NF-kappaB signaling </span></p>
<p>This is a model of the NF-kappaB signaling pathway oscillations, as published by Nelson <span style="font-style:italic">et al.</span> (2004), following the one of Hoffman <span style="font-style:italic">et al.</span> (2002).</p>
<p style="margin-top:16px"><span style="font-size:12pt;font-weight:600">References</span></p>
<ul type="disc"><li>NELSON, D.E., IHEKWABA, A.E., et al.(2004). Oscillations in NF-kappaB signaling control the dynamics of gene expression. <span style="font-style:italic">Science</span> 306, 704-708.</li>
<li>HOFFMANN, A., LEVCHENKO, A., SCOTT, M. L. &amp; BALTIMORE, D. (2002). The IkappaB-NF-kappaB signaling module: temporal control and selective gene activation. <span style="font-style:italic">Science</span> 298, 1241-1245. </li>
<li>CHEN, L. F., FISCHLE, W., VERDIN, E. &amp; GREENE, W. C. (2001). Duration of nuclear NF-kappa B action regulated by reversible acetylation. <span style="font-style:italic">Science</span> 293, 1653-1657.</li>
<li>JENSEN, L. E. &amp; WHITEHEAD, A. S. (1998). Regulation of serum amyloid A protein expression during the acute-phase response. <span style="font-style:italic">Biochem J</span> 334, 489-503. </li>
<div></div></ul>
</body></html>

    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="compartment"/>
      <Compartment key="Compartment_1" name="cytoplasm"/>
      <Compartment key="Compartment_2" name="nucleus"/>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="IkBa" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_1" name="NF-kB" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_2" name="IkBa-NF-kB" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_3" name="IkBb" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_4" name="IkBb-NF-kB" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_5" name="IkBe" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_6" name="IkBe-NF-kB" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_7" name="IKKIkBa" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_8" name="IKKIkBa-NF-kB" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_9" name="IKK" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_10" name="IKKIkBb" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_11" name="IKKIkBb-NF-kB" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_12" name="IKKIkBe" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_13" name="IKKIkBe-NF-kB" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_14" name="NF-kBn" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_15" name="IkBan" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_16" name="IkBan-NF-kBn" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_17" name="IkBbn" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_18" name="IkBbn-NF-kBn" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_19" name="IkBen" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_20" name="IkBen-NF-kBn" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_21" name="IkBa-t" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_22" name="IkBb-t" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_23" name="IkBe-t" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_24" name="sink" compartment="Compartment_0" status="fixed"/>
      <Metabolite key="Metabolite_25" name="source" compartment="Compartment_0" status="fixed"/>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="IkBaNF-kB association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_74" name="k1" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_0"/>
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="IkBa-NF-kB dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_73" name="k1" value="0.0005"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="IkBb-NF-kB association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_72" name="k1" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_3"/>
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="IkBb-NF-kB dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_71" name="k1" value="0.0005"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_71"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="IkBe-NF-kB association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_70" name="k1" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_70"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_5"/>
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="IkBe-NF-kB dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_69" name="k1" value="0.0005"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_69"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="IKKIkBa-NF-kB association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_60" name="k1" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_60"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_7"/>
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="IKKIkBa-NF-kB dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_61" name="k1" value="0.0005"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_61"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="IKKIkBa-NF-kB catalysis" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_64" name="k1" value="0.0204"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="IKKIkBb-NF-kB association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_65" name="k1" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_10"/>
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="IKKIkBb-NF-kB dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_66" name="k1" value="0.0005"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="IKKIkBb-NF-kB catalysis" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_67" name="k1" value="0.0075"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_67"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="IKKIkBe-NF-kB association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_75" name="k1" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_75"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_12"/>
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="IKKIkBe-NF-kB dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_76" name="k1" value="0.0005"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_76"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="IKKIkBe-NF-kB catalysis" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_77" name="k1" value="0.011"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="IkBa constituitive degradation (complexed to NF-kB)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_78" name="k1" value="2.25e-005"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="IkBb constituitive degradation (complexed to NF-kB)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_79" name="k1" value="2.25e-005"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="IkBe constituitive degradation (complexed to NF-kB)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_80" name="k1" value="2.25e-005"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="NF-kB nuclear import" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_92" name="k1" value="0.09"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_92"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="NF-kB nuclear export" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_91" name="k1" value="8e-005"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_91"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="IkBa-NF-kB nuclear association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_90" name="k1" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_90"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_15"/>
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="IkBa-NF-kB nuclear dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_89" name="k1" value="0.0005"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_89"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="IkBb-NF-kB nuclear association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_88" name="k1" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_88"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_17"/>
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="IkBb-NF-kB nuclear dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_87" name="k1" value="0.0005"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_87"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="IkBe-NF-kB nuclear association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_97" name="k1" value="0.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_97"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_19"/>
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="IkBe-NF-kB nuclear dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_98" name="k1" value="0.0005"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_98"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="constituitive IkBa mRNA synthesis" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_99" name="k1" value="1.54e-006"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="IkBa Inducible mRNA synthesis" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="2"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
          <Product metabolite="Metabolite_14" stoichiometry="2"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_100" name="k1" value="0.0165"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_100"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_14"/>
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="IkBa mRNA degradation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_101" name="k1" value="0.00028"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_101"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="constituitive IkBb mRNA synthesis" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_102" name="k1" value="1.78e-007"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_102"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="IkBb mRNA degradation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_103" name="k1" value="0.00028"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="constituitive IkBe mRNA synthesis" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_104" name="k1" value="1.27e-007"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_104"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_32" name="IkBe mRNA degradation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_105" name="k1" value="0.00028"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_105"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_33" name="IKKIkBa association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_106" name="k1" value="0.0225"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_106"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_9"/>
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_34" name="IKKIkBa dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_107" name="k1" value="0.00125"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_107"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="IkBa translation rate" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_108" name="k1" value="0.00408"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_36" name="constitutive IkBa degradation (free)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_109" name="k1" value="0.000113"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_37" name="IkBa nuclear import" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_110" name="k1" value="0.0003"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_110"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_38" name="IkBa nuclear export" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_111" name="k1" value="0.0002"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_111"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_39" name="IKKIkBb association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_112" name="k1" value="0.006"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_9"/>
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_40" name="IKKIkBb dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_113" name="k1" value="0.00175"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_113"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_41" name="IkBb translation rate" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_114" name="k1" value="0.00408"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_42" name="constitutive IkBb degradation (free)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_115" name="k1" value="0.000113"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_43" name="IkBb nuclear import" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_116" name="k1" value="0.00015"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_44" name="IkBb nuclear export" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_117" name="k1" value="0.0001"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_117"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_45" name="IKKIkBe association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_118" name="k1" value="0.009"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_118"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_9"/>
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_46" name="IKKIkBe dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_119" name="k1" value="0.00175"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_119"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_47" name="IkBe translation rate" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_120" name="k1" value="0.00408"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_120"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_48" name="constitutive IkBe degradation (free)" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_121" name="k1" value="0.000113"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_49" name="IkBe nuclear import" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_122" name="k1" value="0.00015"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_122"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_50" name="IkBe nuclear export" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_123" name="k1" value="0.0001"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_123"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_51" name="IKK-IkBaNF-kB association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_124" name="k1" value="0.185"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_124"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_9"/>
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_52" name="IKK-IkBaNF-kB dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_125" name="k1" value="0.00125"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_125"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_53" name="IkBa-NF-kB nuclear export" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_126" name="k1" value="0.0138"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_126"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_54" name="IKK-IkBbNF-kB association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_127" name="k1" value="0.048"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_127"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_9"/>
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_55" name="IKK-IkBbNF-kB dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_128" name="k1" value="0.00175"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_128"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_56" name="IkBb-NF-kB nuclear export" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_129" name="k1" value="0.0052"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_129"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_57" name="IKK-IkBeNF-kB association" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_130" name="k1" value="0.07"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_130"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_9"/>
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_58" name="IKK-IkBeNF-kB dissociation" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_131" name="k1" value="0.00175"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_131"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_59" name="IkBe-NF-kB nuclear export" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_132" name="k1" value="0.0052"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_132"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_60" name="slow adaptation " reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_133" name="k1" value="0.00012"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_133"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_61" name="IKKIkBa catalysis" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_134" name="k1" value="0.00407"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_134"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_62" name="IKKIkBb catalysis" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_135" name="k1" value="0.0015"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_135"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_63" name="IKKIkBe catalysis" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_136" name="k1" value="0.0022"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Parameter_136"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_1"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_14"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_0"/>
      <StateTemplateVariable objectReference="Metabolite_4"/>
      <StateTemplateVariable objectReference="Metabolite_2"/>
      <StateTemplateVariable objectReference="Metabolite_6"/>
      <StateTemplateVariable objectReference="Metabolite_10"/>
      <StateTemplateVariable objectReference="Metabolite_8"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="Metabolite_12"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_22"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_18"/>
      <StateTemplateVariable objectReference="Metabolite_16"/>
      <StateTemplateVariable objectReference="Metabolite_20"/>
      <StateTemplateVariable objectReference="Metabolite_11"/>
      <StateTemplateVariable objectReference="Metabolite_24"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Compartment_0"/>
      <StateTemplateVariable objectReference="Compartment_1"/>
      <StateTemplateVariable objectReference="Compartment_2"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 151003436170486.9 6.0221415e+016 130693678930243.6 1.302896374584551e+016 9295946043384088 1.142181436469596e+017 5001281570759049 5.018415300625578e+016 3568330109474252 0 0 3313802111159244 0 1.135765465584134e+017 9939445415584982 7091626785276905 382836138214284.7 273147132321427.9 0 0 189175715302730.4 861803796660524.4 134973684513639.8 0 0 6.0221415e+017 1 1 1
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_8" name="Steady-State" type="steadyState" scheduled="true" updateModel="false">
      <Report reference="Report_6" target="" append="1"/>
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Use Newton" type="bool" value="1"/>
        <Parameter name="Use Integration" type="bool" value="1"/>
        <Parameter name="Use Back Integration" type="bool" value="1"/>
        <Parameter name="Accept Negative Concentrations" type="bool" value="0"/>
        <Parameter name="Iteration Limit" type="unsignedInteger" value="50"/>
        <Parameter name="Derivation Factor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Resolution" type="unsignedFloat" value="1e-009"/>
      </Method>
    </Task>
    <Task key="Task_9" name="Time-Course" type="timeCourse" scheduled="true" updateModel="false">
      <Report reference="Report_11" target="NF-kappaB-trajectory.txt" append="0"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="200"/>
        <Parameter name="StepSize" type="float" value="108"/>
        <Parameter name="Duration" type="float" value="21600"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="1"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-006"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-012"/>
        <Parameter name="Adams Max Order" type="unsignedInteger" value="12"/>
        <Parameter name="BDF Max Order" type="unsignedInteger" value="5"/>
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
    <Task key="Task_11" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_7" target="" append="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value=""/>
        <Parameter name="Time-Course" type="key" value="Task_9"/>
        <Parameter name="ObjectiveFunction" type="key" value="Function_40"/>
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
    <Task key="Task_12" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_8" target="" append="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_8"/>
        <Parameter name="Time-Course" type="key" value="Task_9"/>
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
    <Task key="Task_13" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_1" target="" append="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_8"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1e-009"/>
      </Method>
    </Task>
    <Task key="Task_14" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_10" target="" append="1"/>
      <Problem>
        <Parameter name="ExponentNumber" type="unsignedInteger" value="3"/>
        <Parameter name="DivergenceRequested" type="bool" value="1"/>
        <Parameter name="TransientTime" type="float" value="0"/>
      </Problem>
      <Method name="Wolf Method" type="WolfMethod">
        <Parameter name="Orthonormalization Interval" type="unsignedFloat" value="1"/>
        <Parameter name="Overall time" type="unsignedFloat" value="1000"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-006"/>
        <Parameter name="Use Default Absolute Tolerance" type="bool" value="1"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="602214"/>
        <Parameter name="Adams Max Order" type="unsignedInteger" value="12"/>
        <Parameter name="BDF Max Order" type="unsignedInteger" value="5"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_0" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_0" target="" append="1"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_6" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        <html xmlns="http://www.w3.org/1999/xhtml"><head><meta name="qrichtext" content="1"></meta></head><body style="font-size:8pt;font-family:MS Shell Dlg">
<p>Automatically generated report. </p>
</body></html>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_7" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
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
    <Report key="Report_8" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
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
    <Report key="Report_9" name="report" taskType="timeCourse" separator="comma" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          HOFFMANN, A., LEVCHENKO, A., SCOTT, M. L. &amp; BALTIMORE, D. (2002). The IkappaB-NF-kappaB signaling module: temporal control and selective gene activation. Science 298, 1241-5.
        </body>
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Timer=Wall Clock Time"/>
        <Object cn="CN=Root,Timer=CPU Time"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Reference=Initial Time"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBa],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBa-NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBb],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBb-NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBe],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBe-NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBa],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBa-NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKK],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBb],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBb-NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBe],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBe-NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[NF-kBn],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBan],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBan-NF-kBn],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBbn],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBbn-NF-kBn],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBen],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBen-NF-kBn],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBa-t],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBb-t],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBe-t],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[source],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[sink],Reference=Concentration"/>
      </Table>
    </Report>
    <Report key="Report_10" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_11" name="Table of concentrations and fluxes with time" taskType="timeCourse" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          A table of the concentrations of the variable metabolites, the fluxes of all reactions, and time. Fluxes are in concentration/time unit.
        </body>
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBa],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBa-NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBb],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBb-NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBe],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBe-NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBa],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBa-NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKK],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBb],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBb-NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBe],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBe-NF-kB],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[NF-kBn],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBan],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBan-NF-kBn],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBbn],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBbn-NF-kBn],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBen],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBen-NF-kBn],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBa-t],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBb-t],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBe-t],Reference=Concentration"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBaNF-kB association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBa-NF-kB dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBb-NF-kB association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBb-NF-kB dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBe-NF-kB association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBe-NF-kB dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBa-NF-kB association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBa-NF-kB dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBa-NF-kB catalysis],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBb-NF-kB association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBb-NF-kB dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBb-NF-kB catalysis],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBe-NF-kB association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBe-NF-kB dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBe-NF-kB catalysis],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBa constituitive degradation (complexed to NF-kB)],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBb constituitive degradation (complexed to NF-kB)],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBe constituitive degradation (complexed to NF-kB)],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[NF-kB nuclear import],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[NF-kB nuclear export],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBa-NF-kB nuclear association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBa-NF-kB nuclear dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBb-NF-kB nuclear association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBb-NF-kB nuclear dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBe-NF-kB nuclear association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBe-NF-kB nuclear dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[constituitive IkBa mRNA synthesis],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBa Inducible mRNA synthesis],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBa mRNA degradation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[constituitive IkBb mRNA synthesis],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBb mRNA degradation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[constituitive IkBe mRNA synthesis],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBe mRNA degradation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBa association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBa dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBa translation rate],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[constitutive IkBa degradation (free)],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBa nuclear import],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBa nuclear export],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBb association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBb dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBb translation rate],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[constitutive IkBb degradation (free)],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBb nuclear import],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBb nuclear export],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBe association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBe dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBe translation rate],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[constitutive IkBe degradation (free)],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBe nuclear import],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBe nuclear export],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKK-IkBaNF-kB association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKK-IkBaNF-kB dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBa-NF-kB nuclear export],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKK-IkBbNF-kB association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKK-IkBbNF-kB dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBb-NF-kB nuclear export],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKK-IkBeNF-kB association],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKK-IkBeNF-kB dissociation],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IkBe-NF-kB nuclear export],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[slow adaptation ],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBa catalysis],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBb catalysis],Reference=Flux"/>
        <Object cn="CN=Root,Model=NF-kB signaling,Vector=Reactions[IKKIkBe catalysis],Reference=Flux"/>
      </Table>
    </Report>
    <Report key="Report_0" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_1" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Result"/>
      </Footer>
    </Report>
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="Trajectory" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="[IkBa]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBa],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[NF-kB]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[NF-kB],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBa-NF-kB]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBa-NF-kB],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBb]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBb],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBb-NF-kB]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBb-NF-kB],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBe]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBe],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBe-NF-kB]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBe-NF-kB],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IKKIkBa]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBa],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IKKIkBa-NF-kB]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBa-NF-kB],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IKK]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKK],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IKKIkBb]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBb],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IKKIkBb-NF-kB]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBb-NF-kB],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IKKIkBe]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBe],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IKKIkBe-NF-kB]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IKKIkBe-NF-kB],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[NF-kBn]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[NF-kBn],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBan]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBan],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBan-NF-kBn]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBan-NF-kBn],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBbn]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBbn],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBbn-NF-kBn]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBbn-NF-kBn],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBen]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBen],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBen-NF-kBn]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBen-NF-kBn],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBa-t]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBa-t],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBb-t]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBb-t],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBe-t]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBe-t],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
    <PlotSpecification name="phase-space diagram" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="[IkBa-t] versus [IkBa]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBa],Reference=Concentration"/>
            <ChannelSpec cn="CN=Root,Model=NF-kB signaling,Vector=Compartments[compartment],Vector=Metabolites[IkBa-t],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
  </GUI>
</COPASI>
