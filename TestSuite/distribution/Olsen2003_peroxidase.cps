<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.1 (Build 19 Feature Preview) (http://www.copasi.org) at 2006-10-03 16:42:37 UTC -->
<COPASI xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://www.copasi.org/static/schema.xsd" versionMajor="1" versionMinor="0" versionDevel="19">
  <ListOfFunctions>
    <Function key="Function_40" name="Objective Function" type="Expression">
      <MathML>
        <Text>
          
        </Text>
      </MathML>
    </Function>
    <Function key="Function_41" name="function_4_v1" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k1*NADH*O2
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_260" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_243" name="NADH" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_250" name="O2" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_42" name="function_4_v2" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k2*H2O2*per3
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_254" name="k2" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_258" name="H2O2" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_262" name="per3" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_43" name="function_4_v3" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k3*coI*ArH
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_263" name="k3" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_246" name="coI" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_265" name="ArH" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_44" name="function_4_v4" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k4*coII*ArH
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_266" name="k4" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_261" name="coII" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_268" name="ArH" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_45" name="function_4_v5" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k5*NADrad*O2
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_269" name="k5" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_264" name="NADrad" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_271" name="O2" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_46" name="function_4_v6" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k6*super*per3
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_272" name="k6" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_267" name="super" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_274" name="per3" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_47" name="function_4_v7" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k7*super*super
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_275" name="k7" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_270" name="super" order="1" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_48" name="function_4_v8" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k8*coIII*NADrad
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_276" name="k8" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_277" name="coIII" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_279" name="NADrad" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_49" name="function_4_v9" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k9*NADrad*NADrad
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_280" name="k9" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_273" name="NADrad" order="1" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_50" name="function_4_v10" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k10*per3*NADrad
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_281" name="k10" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_282" name="per3" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_284" name="NADrad" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_51" name="function_4_v11" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k11*per2*O2
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_285" name="k11" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_278" name="per2" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_287" name="O2" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_52" name="function_4_v12" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k12
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_288" name="k12" order="0" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_53" name="function_4_v131" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k13f*O2g
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_286" name="k13f" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_289" name="O2g" order="1" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_54" name="function_4_v132" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k13b*O2
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_290" name="k13b" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_291" name="O2" order="1" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_55" name="function_4_v14" type="UserDefined" reversible="true">
      <MathML>
        <Text>
          k14*Ar*NADH
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_292" name="k14" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_293" name="Ar" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_295" name="NADH" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_1" name="Olsen2003_peroxidase" timeUnit="s" volumeUnit="l" quantityUnit="µmol" type="deterministic">
    <Comment>
      <html xmlns="http://www.w3.org/1999/xhtml"><head><meta name="qrichtext" content="1" /></head><body style="font-size:8pt;font-family:MS Shell Dlg">
<p style="margin-top:18px"><span style="font-size:16pt;font-weight:600">Model of peroxidase oscillations</span></p>
<p>Model from Olsen LF, Hauser MJ, Kummer U. (2003) &quot;Mechanism of protection of peroxidase activity by oscillatory dynamics.&quot;<span style="font-style:italic">Eur. J. Biochem.</span> <span style="font-weight:600">270</span>, 2796-804. It was first deposited in <span style="font-style:italic">JWS</span> and then in <span style="font-style:italic">BioModels</span>, finally it was imported into COPASI using the SBML import facility.</p>
<p><span style="font-weight:600">Notes of the BioModels curators:</span> </p>
<p>The current model reproduce the figure 7, panel B of the paper. Note that there is a typo in the figure. The ordinates represent the concentration of peroxyde, as stated in the legend, and not of oxygen. The model has been tested in COPASI (http://www.copasi.org/, build 13).</p>
<p><span style="font-weight:600">Notes of the original version of the SBML file:</span> </p>
<p><a href="http://www.sbml.org/"><span style="font-family:Arial;font-weight:600">SBML</span></a><span style="font-family:Arial;font-weight:600"> level 2 code generated for the JWS Online project by Jacky Snoep using </span><a href="http://pysces.sourceforge.net/"><span style="font-family:Arial;font-weight:600">PySCeS</span></a><span style="font-family:Arial;font-weight:600"> <br /></span>Run this model online at <a href="http://jjj.biochem.sun.ac.za/">http://jjj.biochem.sun.ac.za</a> <br />To cite JWS Online please refer to: Olivier, B.G. and Snoep, J.L. (2004) <a href="http://bioinformatics.oupjournals.org/cgi/content/abstract/20/13/2143">Web-based modelling using JWS Online</a>, Bioinformatics, 20:2143-2144 </p>
</body></html>

    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="compartment"/>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="NADH" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_1" name="O2" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_2" name="H2O2" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_3" name="per3" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_4" name="coI" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_5" name="ArH" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_6" name="coII" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_7" name="Ar" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_8" name="NADrad" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_9" name="super" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_10" name="coIII" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_11" name="per2" compartment="Compartment_0" status="reactions"/>
      <Metabolite key="Metabolite_12" name="NAD2" compartment="Compartment_0" status="fixed"/>
      <Metabolite key="Metabolite_13" name="NAD" compartment="Compartment_0" status="fixed"/>
      <Metabolite key="Metabolite_14" name="O2g" compartment="Compartment_0" status="fixed"/>
      <Metabolite key="Metabolite_15" name="NADHres" compartment="Compartment_0" status="fixed"/>
    </ListOfMetabolites>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="v1" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_74" name="k1" value="3e-006"/>
        </ListOfConstants>
        <KineticLaw function="Function_41">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_260">
              <SourceParameter reference="Parameter_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_243">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_250">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="v2" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_73" name="k2" value="18"/>
        </ListOfConstants>
        <KineticLaw function="Function_42">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_254">
              <SourceParameter reference="Parameter_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_258">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="v3" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_72" name="k3" value="0.15"/>
        </ListOfConstants>
        <KineticLaw function="Function_43">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_263">
              <SourceParameter reference="Parameter_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_246">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="v4" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_71" name="k4" value="0.0052"/>
        </ListOfConstants>
        <KineticLaw function="Function_44">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="Parameter_71"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_261">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="v5" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_70" name="k5" value="20"/>
        </ListOfConstants>
        <KineticLaw function="Function_45">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="Parameter_70"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_271">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="v6" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_69" name="k6" value="17"/>
        </ListOfConstants>
        <KineticLaw function="Function_46">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_272">
              <SourceParameter reference="Parameter_69"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_267">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="v7" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="2"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_60" name="k7" value="20"/>
        </ListOfConstants>
        <KineticLaw function="Function_47">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="Parameter_60"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="v8" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_61" name="k8" value="40"/>
        </ListOfConstants>
        <KineticLaw function="Function_48">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_276">
              <SourceParameter reference="Parameter_61"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_279">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="v9" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="2"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_64" name="k9" value="60"/>
        </ListOfConstants>
        <KineticLaw function="Function_49">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="Parameter_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="v10" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_65" name="k10" value="1.8"/>
        </ListOfConstants>
        <KineticLaw function="Function_50">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_281">
              <SourceParameter reference="Parameter_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="v11" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_66" name="k11" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_51">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_285">
              <SourceParameter reference="Parameter_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_287">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="v12" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_67" name="k12" value="0.08"/>
        </ListOfConstants>
        <KineticLaw function="Function_52">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_288">
              <SourceParameter reference="Parameter_67"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="v131" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_75" name="k13f" value="0.006"/>
        </ListOfConstants>
        <KineticLaw function="Function_53">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_286">
              <SourceParameter reference="Parameter_75"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_289">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="v132" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_76" name="k13b" value="0.006"/>
        </ListOfConstants>
        <KineticLaw function="Function_54">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_290">
              <SourceParameter reference="Parameter_76"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_291">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="v14" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_77" name="k14" value="0.7"/>
        </ListOfConstants>
        <KineticLaw function="Function_55">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_292">
              <SourceParameter reference="Parameter_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_293">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_295">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_1"/>
      <StateTemplateVariable objectReference="Metabolite_8"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_4"/>
      <StateTemplateVariable objectReference="Metabolite_0"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_10"/>
      <StateTemplateVariable objectReference="Metabolite_6"/>
      <StateTemplateVariable objectReference="Metabolite_2"/>
      <StateTemplateVariable objectReference="Metabolite_11"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_12"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_14"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Compartment_0"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 0 0 8.4309981e+017 0 0 0 0 0 0 0 3.01107075e+020 0 0 7.2265698e+018 0 1
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_8" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
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
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="5000"/>
        <Parameter name="StepSize" type="float" value="10"/>
        <Parameter name="Duration" type="float" value="50000"/>
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
      <Method name="Evolutionary Programming" type="EvolutionaryProgram">
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
      <Report reference="Report_9" target="" append="1"/>
      <Problem>
        <Parameter name="ExponentNumber" type="unsignedInteger" value="3"/>
        <Parameter name="DivergenceRequested" type="bool" value="1"/>
        <Parameter name="TransientTime" type="float" value="0"/>
      </Problem>
      <Method name="Wolf Method" type="WolfMethod">
        <Parameter name="Orthonormalization Interval" type="unsignedFloat" value="1"/>
        <Parameter name="Overall time" type="unsignedFloat" value="50000"/>
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
        <body xmlns="http://www.w3.org/1999/xhtml">
          Automatically generated report.
        </body>
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
    <Report key="Report_9" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <PlotSpecification name="Concentrations plot" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="[NADH]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Vector=Compartments[compartment],Vector=Metabolites[NADH],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[O2]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Vector=Compartments[compartment],Vector=Metabolites[O2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[H2O2]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Vector=Compartments[compartment],Vector=Metabolites[H2O2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[per3]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Vector=Compartments[compartment],Vector=Metabolites[per3],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[coI]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Vector=Compartments[compartment],Vector=Metabolites[coI],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[coII]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Vector=Compartments[compartment],Vector=Metabolites[coII],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[Ar]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Vector=Compartments[compartment],Vector=Metabolites[Ar],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[NADrad]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Vector=Compartments[compartment],Vector=Metabolites[NADrad],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[super]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Vector=Compartments[compartment],Vector=Metabolites[super],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[coIII]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Vector=Compartments[compartment],Vector=Metabolites[coIII],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[per2]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Vector=Compartments[compartment],Vector=Metabolites[per2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
    <PlotSpecification name="Phase space" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="orbit" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Vector=Compartments[compartment],Vector=Metabolites[NADH],Reference=Concentration"/>
            <ChannelSpec cn="CN=Root,Model=Olsen2003_peroxidase,Vector=Compartments[compartment],Vector=Metabolites[O2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
  </GUI>
  <SBMLReference file="BIOMD0000000046.xml">
    <SBMLMap SBMLid="Ar" COPASIkey="Metabolite_7"/>
    <SBMLMap SBMLid="ArH" COPASIkey="Metabolite_5"/>
    <SBMLMap SBMLid="H2O2" COPASIkey="Metabolite_2"/>
    <SBMLMap SBMLid="NAD" COPASIkey="Metabolite_13"/>
    <SBMLMap SBMLid="NAD2" COPASIkey="Metabolite_12"/>
    <SBMLMap SBMLid="NADH" COPASIkey="Metabolite_0"/>
    <SBMLMap SBMLid="NADHres" COPASIkey="Metabolite_15"/>
    <SBMLMap SBMLid="NADrad" COPASIkey="Metabolite_8"/>
    <SBMLMap SBMLid="O2" COPASIkey="Metabolite_1"/>
    <SBMLMap SBMLid="O2g" COPASIkey="Metabolite_14"/>
    <SBMLMap SBMLid="coI" COPASIkey="Metabolite_4"/>
    <SBMLMap SBMLid="coII" COPASIkey="Metabolite_6"/>
    <SBMLMap SBMLid="coIII" COPASIkey="Metabolite_10"/>
    <SBMLMap SBMLid="compartment" COPASIkey="Compartment_0"/>
    <SBMLMap SBMLid="per2" COPASIkey="Metabolite_11"/>
    <SBMLMap SBMLid="per3" COPASIkey="Metabolite_3"/>
    <SBMLMap SBMLid="super" COPASIkey="Metabolite_9"/>
    <SBMLMap SBMLid="v1" COPASIkey="Reaction_0"/>
    <SBMLMap SBMLid="v10" COPASIkey="Reaction_9"/>
    <SBMLMap SBMLid="v11" COPASIkey="Reaction_10"/>
    <SBMLMap SBMLid="v12" COPASIkey="Reaction_11"/>
    <SBMLMap SBMLid="v131" COPASIkey="Reaction_12"/>
    <SBMLMap SBMLid="v132" COPASIkey="Reaction_13"/>
    <SBMLMap SBMLid="v14" COPASIkey="Reaction_14"/>
    <SBMLMap SBMLid="v2" COPASIkey="Reaction_1"/>
    <SBMLMap SBMLid="v3" COPASIkey="Reaction_2"/>
    <SBMLMap SBMLid="v4" COPASIkey="Reaction_3"/>
    <SBMLMap SBMLid="v5" COPASIkey="Reaction_4"/>
    <SBMLMap SBMLid="v6" COPASIkey="Reaction_5"/>
    <SBMLMap SBMLid="v7" COPASIkey="Reaction_6"/>
    <SBMLMap SBMLid="v8" COPASIkey="Reaction_7"/>
    <SBMLMap SBMLid="v9" COPASIkey="Reaction_8"/>
  </SBMLReference>
</COPASI>
