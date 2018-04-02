<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.23 (Build 178) (http://www.copasi.org) at 2018-03-30 20:43:02 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="23" versionDevel="178" copasiSourcesModified="0">
  <ListOfFunctions>
    <Function key="Function_13" name="Mass action (irreversible)" type="MassAction" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
   <rdf:Description rdf:about="#Function_13">
   <CopasiMT:is rdf:resource="urn:miriam:obo.sbo:SBO:0000041" />
   </rdf:Description>
   </rdf:RDF>
      </MiriamAnnotation>
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
<b>Mass action rate law for first order irreversible reactions</b>
<p>
Reaction scheme where the products are created from the reactants and the change of a product quantity is proportional to the product of reactant activities. The reaction scheme does not include any reverse process that creates the reactants from the products. The change of a product quantity is proportional to the quantity of one reactant.
</p>
</body>
      </Comment>
      <Expression>
        k1*PRODUCT&lt;substrate_i>
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_80" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_81" name="substrate" order="1" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_14" name="Mass action (reversible)" type="MassAction" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
   <rdf:Description rdf:about="#Function_14">
   <CopasiMT:is rdf:resource="urn:miriam:obo.sbo:SBO:0000042" />
   </rdf:Description>
   </rdf:RDF>
      </MiriamAnnotation>
      <Comment>
        <body xmlns="http://www.w3.org/1999/xhtml">
<b>Mass action rate law for reversible reactions</b>
<p>
Reaction scheme where the products are created from the reactants and the change of a product quantity is proportional to the product of reactant activities. The reaction scheme does include a reverse process that creates the reactants from the products.
</p>
</body>
      </Comment>
      <Expression>
        k1*PRODUCT&lt;substrate_i>-k2*PRODUCT&lt;product_j>
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_69" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_68" name="substrate" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_78" name="k2" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_79" name="product" order="3" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_49" name="Catalytic activation (irrev)_1" type="UserDefined" reversible="false">
      <Expression>
        IKKb_active_phosphorylation_vmax*s14*TNFa_TNFR1_EL/((IKKb_active_phosphorylation_kM+s14)*(IKKb_active_phosphorylation_kA+TNFa_TNFR1_EL))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_388" name="IKKb_active_phosphorylation_kA" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_387" name="IKKb_active_phosphorylation_kM" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_386" name="IKKb_active_phosphorylation_vmax" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_385" name="TNFa_TNFR1_EL" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_384" name="s14" order="4" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_50" name="Henri-Michaelis-Menten (irreversible)_1" type="UserDefined" reversible="false">
      <Expression>
        IkBa_phosphorylation_vmax*IkBa_cytoplasm/(IkBa_phosphorylation_kM+IkBa_cytoplasm)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_379" name="IkBa_cytoplasm" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_380" name="IkBa_phosphorylation_kM" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_381" name="IkBa_phosphorylation_vmax" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_51" name="Henri-Michaelis-Menten (irreversible)_2" type="UserDefined" reversible="false">
      <Expression>
        IkBa_translation_vmax*IkBa_mRNA_cytoplasm/(IkBa_translation_Km+IkBa_mRNA_cytoplasm)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_378" name="IkBa_mRNA_cytoplasm" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_383" name="IkBa_translation_Km" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_382" name="IkBa_translation_vmax" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_52" name="Henri-Michaelis-Menten (irreversible)_3" type="UserDefined" reversible="false">
      <Expression>
        JNK_active_phosphorylation_vmax*JNK/(JNK_active_phoshorylation_Km+JNK)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_375" name="JNK" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_376" name="JNK_active_phoshorylation_Km" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_377" name="JNK_active_phosphorylation_vmax" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_53" name="Henri-Michaelis-Menten (irreversible)_4" type="UserDefined" reversible="false">
      <Expression>
        MSK1_activation_vmax*MSK1/(MSK1_activation_kM+MSK1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_372" name="MSK1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_373" name="MSK1_activation_kM" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_374" name="MSK1_activation_vmax" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_54" name="Henri-Michaelis-Menten (irreversible)_5" type="UserDefined" reversible="false">
      <Expression>
        p38_active_phosphorylation_vmax*p38/(p38_active_phoshorylation_Km+p38)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_369" name="p38" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_370" name="p38_active_phoshorylation_Km" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_371" name="p38_active_phosphorylation_vmax" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_55" name="Henri-Michaelis-Menten (irreversible)_6" type="UserDefined" reversible="false">
      <Expression>
        p65_P_MSK1_phosphrylation_vmax*s8/(p65_P_MSK1_phosphrylation_kM+s8)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_366" name="p65_P_MSK1_phosphrylation_kM" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_367" name="p65_P_MSK1_phosphrylation_vmax" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_368" name="s8" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_56" name="Henri-Michaelis-Menten (irreversible)_7" type="UserDefined" reversible="false">
      <Expression>
        p65_MSK1_phosphrylation_vmax*p65_nucleus/(p65_MSK1_phosphorylation_kM+p65_nucleus)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_363" name="p65_MSK1_phosphorylation_kM" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_364" name="p65_MSK1_phosphrylation_vmax" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_365" name="p65_nucleus" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_57" name="activated Transcription [1]_1" type="UserDefined" reversible="false">
      <Expression>
        IkBa_transcription_initiation_kbasal+IkBa_transcription_kA2_p65_P*s8+IkBa_transcription_kA_p65*p65_nucleus+IkBa_transcription_kA3_p65_2P*p65_2P
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_360" name="IkBa_transcription_initiation_kbasal" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_361" name="IkBa_transcription_kA2_p65_P" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_362" name="IkBa_transcription_kA3_p65_2P" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_359" name="IkBa_transcription_kA_p65" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_358" name="p65_2P" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_357" name="p65_nucleus" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_356" name="s8" order="6" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_58" name="Henri-Michaelis-Menten (irreversible)_8" type="UserDefined" reversible="false">
      <Expression>
        IkBa_p65_phosphorylation_vmax*s19/(IkBa_p65_phosphorylation_kM+s19)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_349" name="IkBa_p65_phosphorylation_kM" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_350" name="IkBa_p65_phosphorylation_vmax" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_351" name="s19" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_0" name="beuke1" simulationType="time" timeUnit="s" volumeUnit="µl" areaUnit="m²" lengthUnit="m" quantityUnit="pmol" type="deterministic" avogadroConstant="6.0221417899999999e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Model_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-27T14:23:57Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <ListOfCompartments>
      <Compartment key="Compartment_3" name="EL" simulationType="fixed" dimensionality="3" addNoise="false">
      </Compartment>
      <Compartment key="Compartment_4" name="nucleus" simulationType="fixed" dimensionality="3" addNoise="false">
      </Compartment>
      <Compartment key="Compartment_5" name="cytoplasm" simulationType="fixed" dimensionality="3" addNoise="false">
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_41" name="LPS" simulationType="reactions" compartment="Compartment_3" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_45" name="TNFR1" simulationType="reactions" compartment="Compartment_3" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_50" name="TNFa:TNFR1" simulationType="reactions" compartment="Compartment_3" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_52" name="TNFa" simulationType="fixed" compartment="Compartment_3" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_49" name="IkBa_mRNA" simulationType="reactions" compartment="Compartment_4" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_47" name="IkBa_pre_mRNA_1" simulationType="reactions" compartment="Compartment_4" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_29" name="IkBa_pre_mRNA_2" simulationType="reactions" compartment="Compartment_4" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_30" name="MSK1" simulationType="reactions" compartment="Compartment_4" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_31" name="MSK1_P" simulationType="reactions" compartment="Compartment_4" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_32" name="p65_2P" simulationType="reactions" compartment="Compartment_4" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_33" name="p65-IkBa" simulationType="reactions" compartment="Compartment_4" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_34" name="p65" simulationType="reactions" compartment="Compartment_4" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_35" name="IkBa" simulationType="reactions" compartment="Compartment_4" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_36" name="p65_P" simulationType="reactions" compartment="Compartment_4" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_37" name="IkBa" simulationType="reactions" compartment="Compartment_5" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_38" name="IkBa_mRNA" simulationType="reactions" compartment="Compartment_5" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_39" name="JNK" simulationType="reactions" compartment="Compartment_5" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_40" name="JNK_P" simulationType="reactions" compartment="Compartment_5" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_42" name="TNFR1" simulationType="reactions" compartment="Compartment_5" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_48" name="TNFa:TNFR1" simulationType="reactions" compartment="Compartment_5" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_51" name="p38" simulationType="reactions" compartment="Compartment_5" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_46" name="p38_P" simulationType="reactions" compartment="Compartment_5" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_44" name="p65" simulationType="reactions" compartment="Compartment_5" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-14T14:08:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_43" name="p65_mRNA" simulationType="fixed" compartment="Compartment_5" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_63" name="IKKb" simulationType="reactions" compartment="Compartment_5" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_62" name="IKKb_p" simulationType="reactions" compartment="Compartment_5" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_61" name="p65-IkBa" simulationType="reactions" compartment="Compartment_5" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_60" name="p65_P" simulationType="reactions" compartment="Compartment_5" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_59" name="IkBa_p" simulationType="reactions" compartment="Compartment_5" addNoise="false">
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_108" name="IKKb_active_phosphorylation_kA" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_109" name="IKKb_active_phosphorylation_kM" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_110" name="IKKb_active_phosphorylation_vmax" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_111" name="IKKb_basal_phosphoylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_112" name="IKKb_dephopshorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_8" name="IkBa_deg_complex_cyt_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_7" name="IkBa_deg_complex_nuc_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_114" name="IkBa_deg_cyt_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_115" name="IkBa_deg_nuc_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_116" name="IkBa_mRNA_deg_cyt_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_117" name="IkBa_mRNA_deg_nuc_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_118" name="IkBa_mRNA_transport_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_119" name="IkBa_nuclear_export_k" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_nuclear_import_k],Reference=Value>*0.5
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_120" name="IkBa_nuclear_import_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_121" name="IkBa:p65_association_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_122" name="IkBa:p65_dissociation_k" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_association_k],Reference=Value>*0.003
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_123" name="IkBa:p65_nuclear_export_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_124" name="IkBa:p65_nuclear_import_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_125" name="IkBa:p65_phosphorylation_kM" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_126" name="IkBa:p65_phosphorylation_kcat" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_127" name="IkBa:p65_phosphorylation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_phosphorylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IKKb_p],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_128" name="IkBa_p_active_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_129" name="IkBa_phosphorylation_kM" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_130" name="IkBa_phosphorylation_kcat" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_phosphorylation_kcat],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_131" name="IkBa_phosphorylation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_phosphorylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IKKb_p],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_132" name="IkBa_transcription_elongation_kbasal" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_133" name="IkBa_transcription_initiation_kbasal" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_134" name="IkBa_transcription_kA2_p65_P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_135" name="IkBa_transcription_kA3_p65_2P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_136" name="IkBa_transcription_kA_p65" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_137" name="IkBa_translation_Km" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_138" name="IkBa_translation_vmax" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_139" name="JNK_active_phoshorylation_Km" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_140" name="JNK_active_phosphorylation_kcat" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_141" name="JNK_active_phosphorylation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[JNK_active_phosphorylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[TNFa:TNFR1],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_142" name="JNK_basal_phosphorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_143" name="JNK_dephosphorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_144" name="LPS_LSEC_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_145" name="LPS_MC_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_146" name="MSK1_activation_kM" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_147" name="MSK1_activation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[MSK1_phosphorylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p38_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_148" name="MSK1_dephosphorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_149" name="MSK1_phosphorylation_kcat" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_150" name="TNFa_LSEC_transcription_elongation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_151" name="TNFa_LSEC_transcription_initiation_kA_LPS" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_152" name="TNFa_LSEC_transcription_initiation_kbasal" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_153" name="TNFa_LSEC_transcription_initiation_vA_LPS" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_154" name="TNFa_LSEC_translation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_155" name="TNFa_MC_transcription_elongation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_156" name="TNFa_MC_transcription_initiation_kA_LPS" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_157" name="TNFa_MC_transcription_initiation_kbasal" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_158" name="TNFa_MC_transcription_initiation_vA_LPS" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_159" name="TNFa_MC_translation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_160" name="TNFa_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_161" name="TNFa_mRNA_LSEC_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_162" name="TNFa_mRNA_MC_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_163" name="k_IkBa" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_164" name="k_IkBa_P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_165" name="k_IkBa_mRNA" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_166" name="k_JNK_P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_167" name="k_MSK_P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_168" name="k_TNFR1_outer_membrane2vessicle_shuttle" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_169" name="k_TNFR1_vessicle2outer_membrane_shuttle" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_170" name="k_TNFa:TNFR1_association" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_171" name="k_TNFa:TNFR1_dissociation" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_TNFa:TNFR1_association],Reference=Value>*1.9e-005
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_172" name="k_TNFa:TNFR1_internalisation" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_173" name="k_TNFa_internal_degradation" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_174" name="k_p38_P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_175" name="k_p65" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_176" name="k_p65_P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_177" name="p38_active_phoshorylation_Km" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_178" name="p38_active_phosphorylation_kcat" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_179" name="p38_active_phosphorylation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p38_active_phosphorylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[TNFa:TNFR1],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_180" name="p38_basal_phosphorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_181" name="p38_dephosphorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_182" name="p65_2P_dephosphorylation" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p65_P_dephosphorylation_k],Reference=Value>*1
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_183" name="p65_MSK1_phosphorylation_kM" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_184" name="p65_MSK1_phosphrylation_kcat" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_185" name="p65_MSK1_phosphrylation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p65_MSK1_phosphrylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[MSK1_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_186" name="p65_P_MSK1_phosphrylation_kM" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p65_MSK1_phosphorylation_kM],Reference=Value>*1
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_187" name="p65_P_MSK1_phosphrylation_kcat" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p65_MSK1_phosphrylation_kcat],Reference=Value>*1
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_188" name="p65_P_MSK1_phosphrylation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p65_P_MSK1_phosphrylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[MSK1_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_189" name="p65_P_dephosphorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_190" name="p65_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_191" name="p65_nuclear_export_k" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p65_nuclear_import_k],Reference=Value>*0.02
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_192" name="p65_nuclear_import_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_193" name="p65_translation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_194" name="scaled_IkBa" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_IkBa],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_195" name="scaled_IkBa_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_IkBa_P],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa_P],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_196" name="scaled_IkBa_mRNA" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_IkBa_mRNA],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa_mRNA],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_197" name="scaled_JNK_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_JNK_P],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_JNK_P],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_198" name="scaled_MSK_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_MSK_P],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_MSK_P],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_199" name="scaled_p38_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_p38_P],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_p38_P],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_200" name="scaled_p65" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_p65],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_p65],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_201" name="scaled_p65_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_p65_P],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_p65_P],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_202" name="unscaled_IkBa" simulationType="assignment" addNoise="false">
        <Expression>
          (&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65-IkBa],Reference=Concentration>)*&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Reference=Volume>+(&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa_p],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65-IkBa],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa],Reference=Concentration>)*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_203" name="unscaled_IkBa_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa_p],Reference=Concentration>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_204" name="unscaled_IkBa_mRNA" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa_mRNA],Reference=Concentration>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>+&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Reference=Volume>*&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa_mRNA],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_205" name="unscaled_JNK_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[JNK_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_206" name="unscaled_MSK_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Reference=Volume>*&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[MSK1_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_207" name="unscaled_p38_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p38_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_208" name="unscaled_p65" simulationType="assignment" addNoise="false">
        <Expression>
          (&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65_P],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65-IkBa],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Concentration>)*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>+&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Reference=Volume>*(&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65_P],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65-IkBa],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65_2P],Reference=Concentration>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_209" name="unscaled_p65_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Reference=Volume>*&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65_P],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_210" name="min" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_211" name="max" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_212" name="amp" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_212">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-30T16:12:21Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[max],Reference=Value>-&lt;CN=Root,Model=beuke1,Vector=Values[min],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_213" name="time1" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_214" name="period" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_215" name="avg" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_216" name="int" simulationType="ode" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_216">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-31T14:19:51Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_217" name="sign" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_218" name="counter" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_218">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-14T14:14:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_49" name="Complex_association_c" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7626" name="k1" value="0.0380804"/>
          <Constant key="Parameter_7712" name="k2" value="0.000114241"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_37"/>
              <SourceParameter reference="Metabolite_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_122"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_61"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_50" name="Complex_degradation_IkBa_c" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7714" name="k1" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_61"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_51" name="Complex_degradation_IkBa_n" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7715" name="k1" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_52" name="Complex_degradation_p65_c" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7709" name="k1" value="1.59425e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_190"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_61"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_53" name="Complex_degradation_p65_n" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7710" name="k1" value="1.59425e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_190"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_54" name="Complex_nuclear_shuttle" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7713" name="k1" value="0.0001"/>
          <Constant key="Parameter_7705" name="k2" value="0.002"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_123"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_124"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_61"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_55" name="IKK_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_50" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7704" name="IKKb_active_phosphorylation_kA" value="0.225847"/>
          <Constant key="Parameter_7711" name="IKKb_active_phosphorylation_kM" value="5.99993"/>
          <Constant key="Parameter_7707" name="IKKb_active_phosphorylation_vmax" value="214.511"/>
        </ListOfConstants>
        <KineticLaw function="Function_49" unitType="ConcentrationPerTime" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_388">
              <SourceParameter reference="ModelValue_108"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_387">
              <SourceParameter reference="ModelValue_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_386">
              <SourceParameter reference="ModelValue_110"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_385">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_384">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_56" name="IkBa_degradation_c" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7708" name="k1" value="9.79808e-06"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_114"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_57" name="IkBa_degradation_n" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7706" name="k1" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_58" name="IkBa_mRNA_degradation_c" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7702" name="k1" value="4.9291e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_116"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_59" name="IkBa_mRNA_degradation_n" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7700" name="k1" value="5e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_117"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_49"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_60" name="IkBa_mRNA_transport" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7703" name="k1" value="0.0001"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_118"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_49"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_61" name="IkBa_nuclear_shuttle" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7697" name="k1" value="0.005"/>
          <Constant key="Parameter_7696" name="k2" value="0.0025"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_120"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_119"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_62" name="IkBa_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_59" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7701" name="IkBa_phosphorylation_kM" value="0.117842"/>
          <Constant key="Parameter_7639" name="IkBa_phosphorylation_vmax" value="0.000221972"/>
        </ListOfConstants>
        <KineticLaw function="Function_50" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_379">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_380">
              <SourceParameter reference="ModelValue_129"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_381">
              <SourceParameter reference="ModelValue_131"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_63" name="IkBa_transcription_elongation_1" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_47" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7698" name="k1" value="7.9497e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_132"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_47"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_64" name="IkBa_transcription_elongation_2" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7699" name="k1" value="7.9497e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_132"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_65" name="IkBa_translation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_37" stoichiometry="1"/>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7649" name="IkBa_translation_Km" value="3.69291"/>
          <Constant key="Parameter_7692" name="IkBa_translation_vmax" value="0.00120941"/>
        </ListOfConstants>
        <KineticLaw function="Function_51" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_378">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_383">
              <SourceParameter reference="ModelValue_137"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_382">
              <SourceParameter reference="ModelValue_138"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_66" name="JNK_active_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7690" name="JNK_active_phoshorylation_Km" value="0.00163613"/>
          <Constant key="Parameter_7686" name="JNK_active_phosphorylation_vmax" value="0"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_375">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_376">
              <SourceParameter reference="ModelValue_139"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_377">
              <SourceParameter reference="ModelValue_141"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_67" name="JNK_basal_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7691" name="k1" value="2.59046e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_142"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_68" name="JNK_dephosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7687" name="k1" value="0.000710823"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_143"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_40"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_69" name="LPS_LSEC_degradation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7682" name="k1" value="0.000221889"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[EL]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_144"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_70" name="LPS_MC_degradation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7688" name="k1" value="0.000115242"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[EL]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_145"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_71" name="MSK1_activation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7693" name="MSK1_activation_kM" value="0.332175"/>
          <Constant key="Parameter_7654" name="MSK1_activation_vmax" value="0.000293323"/>
        </ListOfConstants>
        <KineticLaw function="Function_53" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_372">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_373">
              <SourceParameter reference="ModelValue_146"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_374">
              <SourceParameter reference="ModelValue_147"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_72" name="MSK1_deactivation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7683" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_148"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_73" name="TNFR1_shuttle" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7617" name="k1" value="0.0004"/>
          <Constant key="Parameter_7620" name="k2" value="1.8e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_169"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_168"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_74" name="TNFa:TNFR1_association" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_52" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7614" name="k1" value="16.833"/>
          <Constant key="Parameter_7684" name="k2" value="0.000319827"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[EL]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_170"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_52"/>
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_171"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_75" name="TNFa:TNFR1_internalisation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7689" name="k1" value="0.000924"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_172"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_76" name="TNFa degradation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7619" name="k1" value="0.000171417"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[EL]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_160"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_77" name="TNFa_internal_degradation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7674" name="k1" value="6.14429e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_173"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_78" name="basal_IKKb_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7677" name="k1" value="8.60727e-08"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_111"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_79" name="p38_active_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7675" name="p38_active_phoshorylation_Km" value="2.56473"/>
          <Constant key="Parameter_7621" name="p38_active_phosphorylation_vmax" value="0"/>
        </ListOfConstants>
        <KineticLaw function="Function_54" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_369">
              <SourceParameter reference="Metabolite_51"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_370">
              <SourceParameter reference="ModelValue_177"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_371">
              <SourceParameter reference="ModelValue_179"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_99" name="p38_basal_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7681" name="k1" value="0.00025146"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_180"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_51"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_98" name="p38_dephosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7670" name="k1" value="0.000531555"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_181"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_46"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_97" name="p65_2P_degradation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7678" name="k1" value="1.59425e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_190"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_96" name="p65_2P_dephosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7680" name="k1" value="0.000892996"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_182"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_95" name="p65_P_degradation_c" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_60" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7685" name="k1" value="1.59425e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_190"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_60"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_94" name="p65_P_degradation_n" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7676" name="k1" value="1.59425e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_190"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_93" name="p65_P_dephosphorylation_c" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7668" name="k1" value="0.000892996"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_189"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_92" name="p65_P_dephosphorylation_n" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_60" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7679" name="k1" value="0.000892996"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_189"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_60"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_91" name="p65_P_phosphorylation_MSK1" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7663" name="p65_P_MSK1_phosphrylation_kM" value="0.843653"/>
          <Constant key="Parameter_7664" name="p65_P_MSK1_phosphrylation_vmax" value="0.00102741"/>
        </ListOfConstants>
        <KineticLaw function="Function_55" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_366">
              <SourceParameter reference="ModelValue_186"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_367">
              <SourceParameter reference="ModelValue_188"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_368">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_90" name="p65_nuclear_shuttle" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_44" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7662" name="k1" value="0.0005"/>
          <Constant key="Parameter_7671" name="k2" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_192"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_191"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_89" name="p65_phosphorylation_MSK1" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7672" name="p65_MSK1_phosphorylation_kM" value="0.843653"/>
          <Constant key="Parameter_7667" name="p65_MSK1_phosphrylation_vmax" value="0.00102741"/>
        </ListOfConstants>
        <KineticLaw function="Function_56" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_363">
              <SourceParameter reference="ModelValue_183"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_364">
              <SourceParameter reference="ModelValue_185"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_365">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_88" name="p65_translation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
          <Product metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7673" name="k1" value="1.75863e-06"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_193"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_87" name="IkBa_transcription_initiation" reversible="false" fast="false" addNoise="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_47" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_32" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_7665" name="IkBa_transcription_initiation_kbasal" value="1e-06"/>
          <Constant key="Parameter_7669" name="IkBa_transcription_kA2_p65_P" value="0.0001"/>
          <Constant key="Parameter_7666" name="IkBa_transcription_kA3_p65_2P" value="0.0001"/>
          <Constant key="Parameter_7660" name="IkBa_transcription_kA_p65" value="0.232624"/>
        </ListOfConstants>
        <KineticLaw function="Function_57" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_360">
              <SourceParameter reference="ModelValue_133"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_361">
              <SourceParameter reference="ModelValue_134"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_362">
              <SourceParameter reference="ModelValue_135"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_359">
              <SourceParameter reference="ModelValue_136"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_358">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_357">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_356">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_86" name="IkBa_p_active_degradation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_59" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_7658" name="k1" value="0.00374704"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_128"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_59"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_85" name="Complex_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_59" stoichiometry="1"/>
          <Product metabolite="Metabolite_60" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7659" name="IkBa_p65_phosphorylation_kM" value="0.599893"/>
          <Constant key="Parameter_7618" name="IkBa_p65_phosphorylation_vmax" value="0.000221972"/>
        </ListOfConstants>
        <KineticLaw function="Function_58" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_349">
              <SourceParameter reference="ModelValue_125"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_350">
              <SourceParameter reference="ModelValue_127"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_351">
              <SourceParameter reference="Metabolite_61"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_84" name="dephosphorylation IKK" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7625" name="k1" value="0.00212692"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_62"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_83" name="Complex_association_n" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_35" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7661" name="k1" value="0.0380804"/>
          <Constant key="Parameter_7368" name="k2" value="0.000114241"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_35"/>
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_122"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_82" name="p65_P_nuclear_shuttle" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_60" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_7369" name="k1" value="0.0005"/>
          <Constant key="Parameter_7315" name="k2" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_192"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_60"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_191"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfEvents>
      <Event key="Event_0" name="min" fireAtInitialTime="0" persistentTrigger="0">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-30T16:13:45Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <TriggerExpression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Rate> > 0
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="ModelValue_210">
            <Expression>
              &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Concentration>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_217">
            <Expression>
              -&lt;CN=Root,Model=beuke1,Vector=Values[sign],Reference=Value>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_218">
            <Expression>
              &lt;CN=Root,Model=beuke1,Vector=Values[counter],Reference=Value>+1
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_3" name="max" fireAtInitialTime="0" persistentTrigger="0">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_3">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2017-03-30T16:14:34Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
        <TriggerExpression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Rate> &lt; 0
        </TriggerExpression>
        <ListOfAssignments>
          <Assignment targetKey="ModelValue_211">
            <Expression>
              &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Concentration>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_213">
            <Expression>
              &lt;CN=Root,Model=beuke1,Reference=Time>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_214">
            <Expression>
              &lt;CN=Root,Model=beuke1,Reference=Time>-&lt;CN=Root,Model=beuke1,Vector=Values[time1],Reference=Value>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_215">
            <Expression>
              &lt;CN=Root,Model=beuke1,Vector=Values[int],Reference=Value>/&lt;CN=Root,Model=beuke1,Vector=Values[period],Reference=Value>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_216">
            <Expression>
              0
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_217">
            <Expression>
              -&lt;CN=Root,Model=beuke1,Vector=Values[sign],Reference=Value>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_218">
            <Expression>
              &lt;CN=Root,Model=beuke1,Vector=Values[counter],Reference=Value>+1
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
    </ListOfEvents>
    <ListOfModelParameterSets activeSet="ModelParameterSet_0">
      <ModelParameterSet key="ModelParameterSet_0" name="Initial State">
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=beuke1" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[EL]" value="2.5900000000000002e-06" type="Compartment" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus]" value="7.9999999999999996e-07" type="Compartment" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]" value="1.2999999999999999e-05" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[LPS]" value="7798673.6180500006" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[TNFR1]" value="1915.894621127193" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[TNFa:TNFR1]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[TNFa]" value="917.49835381634625" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa_mRNA]" value="16.741821099107149" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa_pre_mRNA_1]" value="926214.74297503615" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa_pre_mRNA_2]" value="926214.74297503615" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[MSK1]" value="7212745.4386496814" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[MSK1_P]" value="13824.709350325529" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65_2P]" value="102415.9970892102" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65-IkBa]" value="428562.47568196338" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65]" value="7131.4437299996334" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa]" value="444478.39400965557" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65_P]" value="83411.493122878295" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa]" value="3611387.4722043518" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa_mRNA]" value="10257237.8075299" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[JNK]" value="7553510.5629981197" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[JNK_P]" value="275273.76400187978" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[TNFR1]" value="432.74067697274342" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[TNFa:TNFR1]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p38]" value="5314621.6602560114" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p38_P]" value="2514162.666743997" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65]" value="2318.7564433152638" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65_mRNA]" value="7828784.3269999996" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IKKb]" value="2348541.369331039" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IKKb_p]" value="93.928768960989473" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65-IkBa]" value="348205.76605032221" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65_P]" value="27112.892084477469" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa_p]" value="505973.20938342536" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IKKb_active_phosphorylation_kA]" value="0.22584699999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IKKb_active_phosphorylation_kM]" value="5.9999253986099763" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IKKb_active_phosphorylation_vmax]" value="214.511" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IKKb_basal_phosphoylation_k]" value="8.6072734027274997e-08" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IKKb_dephopshorylation_k]" value="0.002126924084237061" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_deg_complex_cyt_k]" value="1.0000000000000001e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_deg_complex_nuc_k]" value="1.00000000002221e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_deg_cyt_k]" value="9.7980800000000006e-06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_deg_nuc_k]" value="1.0000000000000001e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_mRNA_deg_cyt_k]" value="4.9291e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_mRNA_deg_nuc_k]" value="5.0000000000000002e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_mRNA_transport_k]" value="0.0001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_nuclear_export_k]" value="0.0025000000000000001" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_nuclear_import_k]" value="0.0050000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa:p65_association_k]" value="0.038080424418151397" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa:p65_dissociation_k]" value="0.0001142412732544542" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa:p65_nuclear_export_k]" value="0.000100000000000222" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa:p65_nuclear_import_k]" value="0.0019999999999997802" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa:p65_phosphorylation_kM]" value="0.59989342964577941" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa:p65_phosphorylation_kcat]" value="18.500918641635661" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa:p65_phosphorylation_vmax]" value="0.00022197169318651728" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_p_active_degradation_k]" value="0.00374704364447229" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_phosphorylation_kM]" value="0.117842" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_phosphorylation_kcat]" value="18.500918641635661" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_phosphorylation_vmax]" value="0.00022197169318651728" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_transcription_elongation_kbasal]" value="7.9497024021163017e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_transcription_initiation_kbasal]" value="9.9999999999999995e-07" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_transcription_kA2_p65_P]" value="0.000100000000000222" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_transcription_kA3_p65_2P]" value="0.000100000000000222" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_transcription_kA_p65]" value="0.23262432287335619" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_translation_Km]" value="3.6929099999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[IkBa_translation_vmax]" value="0.00120941" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[JNK_active_phoshorylation_Km]" value="0.0016361306255064201" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[JNK_active_phosphorylation_kcat]" value="11501.848605491499" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[JNK_active_phosphorylation_vmax]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[JNK_basal_phosphorylation_k]" value="2.5904620308721599e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[JNK_dephosphorylation_k]" value="0.00071082263811762803" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[LPS_LSEC_degradation_k]" value="0.000221888641398861" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[LPS_MC_degradation_k]" value="0.000115242287512479" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[MSK1_activation_kM]" value="0.332175" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[MSK1_activation_vmax]" value="0.0002933226422510503" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[MSK1_dephosphorylation_k]" value="0.0099999999999997799" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[MSK1_phosphorylation_kcat]" value="0.00091336958216119905" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[TNFa_LSEC_transcription_elongation_k]" value="1.0000000002220399e-06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[TNFa_LSEC_transcription_initiation_kA_LPS]" value="1.0937545446161601" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[TNFa_LSEC_transcription_initiation_kbasal]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[TNFa_LSEC_transcription_initiation_vA_LPS]" value="1.22913885610405e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[TNFa_LSEC_translation_k]" value="2.1819503787823699e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[TNFa_MC_transcription_elongation_k]" value="1.0000000002220399e-06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[TNFa_MC_transcription_initiation_kA_LPS]" value="0.83406985346583096" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[TNFa_MC_transcription_initiation_kbasal]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[TNFa_MC_transcription_initiation_vA_LPS]" value="5.97504797065566e-06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[TNFa_MC_translation_k]" value="2.1894167810831798e-06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[TNFa_degradation_k]" value="0.000171416922199217" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[TNFa_mRNA_LSEC_degradation_k]" value="0.58439602675956803" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[TNFa_mRNA_MC_degradation_k]" value="0.050715716095883802" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_IkBa]" value="145028.78158363799" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_IkBa_P]" value="584678.80956640502" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_IkBa_mRNA]" value="21395.245793948801" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_JNK_P]" value="1491678.2351977001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_MSK_P]" value="28373108.944711499" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_TNFR1_outer_membrane2vessicle_shuttle]" value="1.8e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_TNFR1_vessicle2outer_membrane_shuttle]" value="0.00040000000000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_TNFa:TNFR1_association]" value="16.832999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_TNFa:TNFR1_dissociation]" value="0.00031982700000000001" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_TNFa:TNFR1_internalisation]" value="0.00092400000000000002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_TNFa_internal_degradation]" value="6.1442899999999994e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_p38_P]" value="197139.21763645901" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_p65]" value="0.102372088824604" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[k_p65_P]" value="3050644.1138216699" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p38_active_phoshorylation_Km]" value="2.5647334845410801" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p38_active_phosphorylation_kcat]" value="549341.56606688304" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p38_active_phosphorylation_vmax]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p38_basal_phosphorylation_k]" value="0.00025145997620859502" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p38_dephosphorylation_k]" value="0.00053155456244858516" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p65_2P_dephosphorylation]" value="0.00089299602995035509" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p65_MSK1_phosphorylation_kM]" value="0.84365297237173797" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p65_MSK1_phosphrylation_kcat]" value="0.035803860144060298" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p65_MSK1_phosphrylation_vmax]" value="0.0010274126244695619" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p65_P_MSK1_phosphrylation_kM]" value="0.84365297237173797" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p65_P_MSK1_phosphrylation_kcat]" value="0.035803860144060298" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p65_P_MSK1_phosphrylation_vmax]" value="0.0010274126244695619" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p65_P_dephosphorylation_k]" value="0.00089299602995035509" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p65_degradation_k]" value="1.5942540684736069e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p65_nuclear_export_k]" value="1.0000000000000001e-05" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p65_nuclear_import_k]" value="0.00050000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[p65_translation_k]" value="1.758629979014617e-06" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[scaled_IkBa]" value="1.285674999999997" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[scaled_IkBa_P]" value="0.49124019999999791" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[scaled_IkBa_mRNA]" value="0.3644160000000003" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[scaled_JNK_P]" value="0.68185023999999872" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[scaled_MSK_P]" value="0.65134631200000026" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[scaled_p38_P]" value="0.82302954400000106" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[scaled_p65]" value="1.6984982995744289e-07" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[scaled_p65_P]" value="0.55988479999999918" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa]" value="8.8649644985023138e-06" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa_P]" value="8.4018813742249228e-07" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa_mRNA]" value="1.7032568987969644e-05" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[unscaled_JNK_P]" value="4.5710276111230481e-07" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[unscaled_MSK_P]" value="2.2956466042167914e-08" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[unscaled_p38_P]" value="4.1748646153082307e-06" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[unscaled_p65]" value="1.6591419781269655e-06" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[unscaled_p65_P]" value="1.8353002812203092e-07" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[min]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[max]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[amp]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[time1]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[period]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[avg]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[int]" value="0" type="ModelValue" simulationType="ode"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[sign]" value="9.9999999999999995e-08" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=beuke1,Vector=Values[counter]" value="0" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_association_c]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_association_c],ParameterGroup=Parameters,Parameter=k1" value="0.038080424418151397" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_association_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_association_c],ParameterGroup=Parameters,Parameter=k2" value="0.0001142412732544542" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_dissociation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_degradation_IkBa_c]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_degradation_IkBa_c],ParameterGroup=Parameters,Parameter=k1" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_deg_complex_cyt_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_degradation_IkBa_n]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_degradation_IkBa_n],ParameterGroup=Parameters,Parameter=k1" value="1.00000000002221e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_deg_complex_nuc_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_degradation_p65_c]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_degradation_p65_c],ParameterGroup=Parameters,Parameter=k1" value="1.5942540684736069e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_degradation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_degradation_p65_n]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_degradation_p65_n],ParameterGroup=Parameters,Parameter=k1" value="1.5942540684736069e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_degradation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_nuclear_shuttle]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_nuclear_shuttle],ParameterGroup=Parameters,Parameter=k1" value="0.000100000000000222" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_nuclear_export_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_nuclear_shuttle],ParameterGroup=Parameters,Parameter=k2" value="0.0019999999999997802" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_nuclear_import_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[IKK_phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IKK_phosphorylation],ParameterGroup=Parameters,Parameter=IKKb_active_phosphorylation_kA" value="0.22584699999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IKKb_active_phosphorylation_kA],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IKK_phosphorylation],ParameterGroup=Parameters,Parameter=IKKb_active_phosphorylation_kM" value="5.9999253986099763" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IKKb_active_phosphorylation_kM],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IKK_phosphorylation],ParameterGroup=Parameters,Parameter=IKKb_active_phosphorylation_vmax" value="214.511" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IKKb_active_phosphorylation_vmax],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_degradation_c]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_degradation_c],ParameterGroup=Parameters,Parameter=k1" value="9.7980800000000006e-06" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_deg_cyt_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_degradation_n]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_degradation_n],ParameterGroup=Parameters,Parameter=k1" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_deg_nuc_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_mRNA_degradation_c]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_mRNA_degradation_c],ParameterGroup=Parameters,Parameter=k1" value="4.9291e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_mRNA_deg_cyt_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_mRNA_degradation_n]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_mRNA_degradation_n],ParameterGroup=Parameters,Parameter=k1" value="5.0000000000000002e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_mRNA_deg_nuc_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_mRNA_transport]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_mRNA_transport],ParameterGroup=Parameters,Parameter=k1" value="0.0001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_mRNA_transport_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_nuclear_shuttle]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_nuclear_shuttle],ParameterGroup=Parameters,Parameter=k1" value="0.0050000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_nuclear_import_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_nuclear_shuttle],ParameterGroup=Parameters,Parameter=k2" value="0.0025000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_nuclear_export_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_phosphorylation],ParameterGroup=Parameters,Parameter=IkBa_phosphorylation_kM" value="0.117842" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_phosphorylation_kM],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_phosphorylation],ParameterGroup=Parameters,Parameter=IkBa_phosphorylation_vmax" value="0.00022197169318651728" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_phosphorylation_vmax],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_transcription_elongation_1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_transcription_elongation_1],ParameterGroup=Parameters,Parameter=k1" value="7.9497024021163017e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_transcription_elongation_kbasal],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_transcription_elongation_2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_transcription_elongation_2],ParameterGroup=Parameters,Parameter=k1" value="7.9497024021163017e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_transcription_elongation_kbasal],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_translation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_translation],ParameterGroup=Parameters,Parameter=IkBa_translation_Km" value="3.6929099999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_translation_Km],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_translation],ParameterGroup=Parameters,Parameter=IkBa_translation_vmax" value="0.00120941" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_translation_vmax],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[JNK_active_phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[JNK_active_phosphorylation],ParameterGroup=Parameters,Parameter=JNK_active_phoshorylation_Km" value="0.0016361306255064201" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[JNK_active_phoshorylation_Km],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[JNK_active_phosphorylation],ParameterGroup=Parameters,Parameter=JNK_active_phosphorylation_vmax" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[JNK_active_phosphorylation_vmax],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[JNK_basal_phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[JNK_basal_phosphorylation],ParameterGroup=Parameters,Parameter=k1" value="2.5904620308721599e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[JNK_basal_phosphorylation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[JNK_dephosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[JNK_dephosphorylation],ParameterGroup=Parameters,Parameter=k1" value="0.00071082263811762803" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[JNK_dephosphorylation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[LPS_LSEC_degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[LPS_LSEC_degradation],ParameterGroup=Parameters,Parameter=k1" value="0.000221888641398861" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[LPS_LSEC_degradation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[LPS_MC_degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[LPS_MC_degradation],ParameterGroup=Parameters,Parameter=k1" value="0.000115242287512479" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[LPS_MC_degradation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[MSK1_activation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[MSK1_activation],ParameterGroup=Parameters,Parameter=MSK1_activation_kM" value="0.332175" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[MSK1_activation_kM],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[MSK1_activation],ParameterGroup=Parameters,Parameter=MSK1_activation_vmax" value="0.0002933226422510503" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[MSK1_activation_vmax],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[MSK1_deactivation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[MSK1_deactivation],ParameterGroup=Parameters,Parameter=k1" value="0.0099999999999997799" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[MSK1_dephosphorylation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[TNFR1_shuttle]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[TNFR1_shuttle],ParameterGroup=Parameters,Parameter=k1" value="0.00040000000000000002" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[k_TNFR1_vessicle2outer_membrane_shuttle],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[TNFR1_shuttle],ParameterGroup=Parameters,Parameter=k2" value="1.8e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[k_TNFR1_outer_membrane2vessicle_shuttle],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[TNFa:TNFR1_association]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[TNFa:TNFR1_association],ParameterGroup=Parameters,Parameter=k1" value="16.832999999999998" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[k_TNFa:TNFR1_association],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[TNFa:TNFR1_association],ParameterGroup=Parameters,Parameter=k2" value="0.00031982700000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[k_TNFa:TNFR1_dissociation],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[TNFa:TNFR1_internalisation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[TNFa:TNFR1_internalisation],ParameterGroup=Parameters,Parameter=k1" value="0.00092400000000000002" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[k_TNFa:TNFR1_internalisation],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[TNFa degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[TNFa degradation],ParameterGroup=Parameters,Parameter=k1" value="0.000171416922199217" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[TNFa_degradation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[TNFa_internal_degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[TNFa_internal_degradation],ParameterGroup=Parameters,Parameter=k1" value="6.1442899999999994e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[k_TNFa_internal_degradation],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[basal_IKKb_phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[basal_IKKb_phosphorylation],ParameterGroup=Parameters,Parameter=k1" value="8.6072734027274997e-08" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IKKb_basal_phosphoylation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p38_active_phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p38_active_phosphorylation],ParameterGroup=Parameters,Parameter=p38_active_phoshorylation_Km" value="2.5647334845410801" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p38_active_phoshorylation_Km],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p38_active_phosphorylation],ParameterGroup=Parameters,Parameter=p38_active_phosphorylation_vmax" value="0" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p38_active_phosphorylation_vmax],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p38_basal_phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p38_basal_phosphorylation],ParameterGroup=Parameters,Parameter=k1" value="0.00025145997620859502" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p38_basal_phosphorylation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p38_dephosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p38_dephosphorylation],ParameterGroup=Parameters,Parameter=k1" value="0.00053155456244858516" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p38_dephosphorylation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p65_2P_degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_2P_degradation],ParameterGroup=Parameters,Parameter=k1" value="1.5942540684736069e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_degradation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p65_2P_dephosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_2P_dephosphorylation],ParameterGroup=Parameters,Parameter=k1" value="0.00089299602995035509" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_2P_dephosphorylation],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_degradation_c]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_degradation_c],ParameterGroup=Parameters,Parameter=k1" value="1.5942540684736069e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_degradation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_degradation_n]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_degradation_n],ParameterGroup=Parameters,Parameter=k1" value="1.5942540684736069e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_degradation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_dephosphorylation_c]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_dephosphorylation_c],ParameterGroup=Parameters,Parameter=k1" value="0.00089299602995035509" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_P_dephosphorylation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_dephosphorylation_n]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_dephosphorylation_n],ParameterGroup=Parameters,Parameter=k1" value="0.00089299602995035509" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_P_dephosphorylation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_phosphorylation_MSK1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_phosphorylation_MSK1],ParameterGroup=Parameters,Parameter=p65_P_MSK1_phosphrylation_kM" value="0.84365297237173797" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_P_MSK1_phosphrylation_kM],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_phosphorylation_MSK1],ParameterGroup=Parameters,Parameter=p65_P_MSK1_phosphrylation_vmax" value="0.0010274126244695619" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_P_MSK1_phosphrylation_vmax],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p65_nuclear_shuttle]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_nuclear_shuttle],ParameterGroup=Parameters,Parameter=k1" value="0.00050000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_nuclear_import_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_nuclear_shuttle],ParameterGroup=Parameters,Parameter=k2" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_nuclear_export_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p65_phosphorylation_MSK1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_phosphorylation_MSK1],ParameterGroup=Parameters,Parameter=p65_MSK1_phosphorylation_kM" value="0.84365297237173797" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_MSK1_phosphorylation_kM],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_phosphorylation_MSK1],ParameterGroup=Parameters,Parameter=p65_MSK1_phosphrylation_vmax" value="0.0010274126244695619" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_MSK1_phosphrylation_vmax],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p65_translation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_translation],ParameterGroup=Parameters,Parameter=k1" value="1.758629979014617e-06" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_translation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_transcription_initiation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_transcription_initiation],ParameterGroup=Parameters,Parameter=IkBa_transcription_initiation_kbasal" value="9.9999999999999995e-07" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_transcription_initiation_kbasal],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_transcription_initiation],ParameterGroup=Parameters,Parameter=IkBa_transcription_kA2_p65_P" value="0.000100000000000222" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_transcription_kA2_p65_P],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_transcription_initiation],ParameterGroup=Parameters,Parameter=IkBa_transcription_kA3_p65_2P" value="0.000100000000000222" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_transcription_kA3_p65_2P],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_transcription_initiation],ParameterGroup=Parameters,Parameter=IkBa_transcription_kA_p65" value="0.23262432287335619" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_transcription_kA_p65],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_p_active_degradation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[IkBa_p_active_degradation],ParameterGroup=Parameters,Parameter=k1" value="0.00374704364447229" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_p_active_degradation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_phosphorylation]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_phosphorylation],ParameterGroup=Parameters,Parameter=IkBa_p65_phosphorylation_kM" value="0.59989342964577941" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_phosphorylation_kM],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_phosphorylation],ParameterGroup=Parameters,Parameter=IkBa_p65_phosphorylation_vmax" value="0.00022197169318651728" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_phosphorylation_vmax],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[dephosphorylation IKK]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[dephosphorylation IKK],ParameterGroup=Parameters,Parameter=k1" value="0.002126924084237061" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IKKb_dephopshorylation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_association_n]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_association_n],ParameterGroup=Parameters,Parameter=k1" value="0.038080424418151397" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_association_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[Complex_association_n],ParameterGroup=Parameters,Parameter=k2" value="0.0001142412732544542" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_dissociation_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_nuclear_shuttle]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_nuclear_shuttle],ParameterGroup=Parameters,Parameter=k1" value="0.00050000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_nuclear_import_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=beuke1,Vector=Reactions[p65_P_nuclear_shuttle],ParameterGroup=Parameters,Parameter=k2" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=beuke1,Vector=Values[p65_nuclear_export_k],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_0"/>
      <StateTemplateVariable objectReference="ModelValue_216"/>
      <StateTemplateVariable objectReference="Metabolite_34"/>
      <StateTemplateVariable objectReference="Metabolite_37"/>
      <StateTemplateVariable objectReference="Metabolite_44"/>
      <StateTemplateVariable objectReference="Metabolite_36"/>
      <StateTemplateVariable objectReference="Metabolite_61"/>
      <StateTemplateVariable objectReference="Metabolite_35"/>
      <StateTemplateVariable objectReference="Metabolite_60"/>
      <StateTemplateVariable objectReference="Metabolite_49"/>
      <StateTemplateVariable objectReference="Metabolite_39"/>
      <StateTemplateVariable objectReference="Metabolite_51"/>
      <StateTemplateVariable objectReference="Metabolite_63"/>
      <StateTemplateVariable objectReference="Metabolite_32"/>
      <StateTemplateVariable objectReference="Metabolite_59"/>
      <StateTemplateVariable objectReference="Metabolite_45"/>
      <StateTemplateVariable objectReference="Metabolite_48"/>
      <StateTemplateVariable objectReference="Metabolite_41"/>
      <StateTemplateVariable objectReference="Metabolite_47"/>
      <StateTemplateVariable objectReference="Metabolite_30"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_38"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_50"/>
      <StateTemplateVariable objectReference="Metabolite_40"/>
      <StateTemplateVariable objectReference="Metabolite_42"/>
      <StateTemplateVariable objectReference="Metabolite_31"/>
      <StateTemplateVariable objectReference="Metabolite_46"/>
      <StateTemplateVariable objectReference="Metabolite_62"/>
      <StateTemplateVariable objectReference="ModelValue_119"/>
      <StateTemplateVariable objectReference="ModelValue_122"/>
      <StateTemplateVariable objectReference="ModelValue_127"/>
      <StateTemplateVariable objectReference="ModelValue_130"/>
      <StateTemplateVariable objectReference="ModelValue_131"/>
      <StateTemplateVariable objectReference="ModelValue_141"/>
      <StateTemplateVariable objectReference="ModelValue_147"/>
      <StateTemplateVariable objectReference="ModelValue_171"/>
      <StateTemplateVariable objectReference="ModelValue_179"/>
      <StateTemplateVariable objectReference="ModelValue_182"/>
      <StateTemplateVariable objectReference="ModelValue_185"/>
      <StateTemplateVariable objectReference="ModelValue_186"/>
      <StateTemplateVariable objectReference="ModelValue_187"/>
      <StateTemplateVariable objectReference="ModelValue_188"/>
      <StateTemplateVariable objectReference="ModelValue_191"/>
      <StateTemplateVariable objectReference="ModelValue_194"/>
      <StateTemplateVariable objectReference="ModelValue_195"/>
      <StateTemplateVariable objectReference="ModelValue_196"/>
      <StateTemplateVariable objectReference="ModelValue_197"/>
      <StateTemplateVariable objectReference="ModelValue_198"/>
      <StateTemplateVariable objectReference="ModelValue_199"/>
      <StateTemplateVariable objectReference="ModelValue_200"/>
      <StateTemplateVariable objectReference="ModelValue_201"/>
      <StateTemplateVariable objectReference="ModelValue_202"/>
      <StateTemplateVariable objectReference="ModelValue_203"/>
      <StateTemplateVariable objectReference="ModelValue_204"/>
      <StateTemplateVariable objectReference="ModelValue_205"/>
      <StateTemplateVariable objectReference="ModelValue_206"/>
      <StateTemplateVariable objectReference="ModelValue_207"/>
      <StateTemplateVariable objectReference="ModelValue_208"/>
      <StateTemplateVariable objectReference="ModelValue_209"/>
      <StateTemplateVariable objectReference="ModelValue_212"/>
      <StateTemplateVariable objectReference="Metabolite_52"/>
      <StateTemplateVariable objectReference="Metabolite_43"/>
      <StateTemplateVariable objectReference="Compartment_3"/>
      <StateTemplateVariable objectReference="Compartment_4"/>
      <StateTemplateVariable objectReference="Compartment_5"/>
      <StateTemplateVariable objectReference="ModelValue_108"/>
      <StateTemplateVariable objectReference="ModelValue_109"/>
      <StateTemplateVariable objectReference="ModelValue_110"/>
      <StateTemplateVariable objectReference="ModelValue_111"/>
      <StateTemplateVariable objectReference="ModelValue_112"/>
      <StateTemplateVariable objectReference="ModelValue_8"/>
      <StateTemplateVariable objectReference="ModelValue_7"/>
      <StateTemplateVariable objectReference="ModelValue_114"/>
      <StateTemplateVariable objectReference="ModelValue_115"/>
      <StateTemplateVariable objectReference="ModelValue_116"/>
      <StateTemplateVariable objectReference="ModelValue_117"/>
      <StateTemplateVariable objectReference="ModelValue_118"/>
      <StateTemplateVariable objectReference="ModelValue_120"/>
      <StateTemplateVariable objectReference="ModelValue_121"/>
      <StateTemplateVariable objectReference="ModelValue_123"/>
      <StateTemplateVariable objectReference="ModelValue_124"/>
      <StateTemplateVariable objectReference="ModelValue_125"/>
      <StateTemplateVariable objectReference="ModelValue_126"/>
      <StateTemplateVariable objectReference="ModelValue_128"/>
      <StateTemplateVariable objectReference="ModelValue_129"/>
      <StateTemplateVariable objectReference="ModelValue_132"/>
      <StateTemplateVariable objectReference="ModelValue_133"/>
      <StateTemplateVariable objectReference="ModelValue_134"/>
      <StateTemplateVariable objectReference="ModelValue_135"/>
      <StateTemplateVariable objectReference="ModelValue_136"/>
      <StateTemplateVariable objectReference="ModelValue_137"/>
      <StateTemplateVariable objectReference="ModelValue_138"/>
      <StateTemplateVariable objectReference="ModelValue_139"/>
      <StateTemplateVariable objectReference="ModelValue_140"/>
      <StateTemplateVariable objectReference="ModelValue_142"/>
      <StateTemplateVariable objectReference="ModelValue_143"/>
      <StateTemplateVariable objectReference="ModelValue_144"/>
      <StateTemplateVariable objectReference="ModelValue_145"/>
      <StateTemplateVariable objectReference="ModelValue_146"/>
      <StateTemplateVariable objectReference="ModelValue_148"/>
      <StateTemplateVariable objectReference="ModelValue_149"/>
      <StateTemplateVariable objectReference="ModelValue_150"/>
      <StateTemplateVariable objectReference="ModelValue_151"/>
      <StateTemplateVariable objectReference="ModelValue_152"/>
      <StateTemplateVariable objectReference="ModelValue_153"/>
      <StateTemplateVariable objectReference="ModelValue_154"/>
      <StateTemplateVariable objectReference="ModelValue_155"/>
      <StateTemplateVariable objectReference="ModelValue_156"/>
      <StateTemplateVariable objectReference="ModelValue_157"/>
      <StateTemplateVariable objectReference="ModelValue_158"/>
      <StateTemplateVariable objectReference="ModelValue_159"/>
      <StateTemplateVariable objectReference="ModelValue_160"/>
      <StateTemplateVariable objectReference="ModelValue_161"/>
      <StateTemplateVariable objectReference="ModelValue_162"/>
      <StateTemplateVariable objectReference="ModelValue_163"/>
      <StateTemplateVariable objectReference="ModelValue_164"/>
      <StateTemplateVariable objectReference="ModelValue_165"/>
      <StateTemplateVariable objectReference="ModelValue_166"/>
      <StateTemplateVariable objectReference="ModelValue_167"/>
      <StateTemplateVariable objectReference="ModelValue_168"/>
      <StateTemplateVariable objectReference="ModelValue_169"/>
      <StateTemplateVariable objectReference="ModelValue_170"/>
      <StateTemplateVariable objectReference="ModelValue_172"/>
      <StateTemplateVariable objectReference="ModelValue_173"/>
      <StateTemplateVariable objectReference="ModelValue_174"/>
      <StateTemplateVariable objectReference="ModelValue_175"/>
      <StateTemplateVariable objectReference="ModelValue_176"/>
      <StateTemplateVariable objectReference="ModelValue_177"/>
      <StateTemplateVariable objectReference="ModelValue_178"/>
      <StateTemplateVariable objectReference="ModelValue_180"/>
      <StateTemplateVariable objectReference="ModelValue_181"/>
      <StateTemplateVariable objectReference="ModelValue_183"/>
      <StateTemplateVariable objectReference="ModelValue_184"/>
      <StateTemplateVariable objectReference="ModelValue_189"/>
      <StateTemplateVariable objectReference="ModelValue_190"/>
      <StateTemplateVariable objectReference="ModelValue_192"/>
      <StateTemplateVariable objectReference="ModelValue_193"/>
      <StateTemplateVariable objectReference="ModelValue_210"/>
      <StateTemplateVariable objectReference="ModelValue_211"/>
      <StateTemplateVariable objectReference="ModelValue_213"/>
      <StateTemplateVariable objectReference="ModelValue_214"/>
      <StateTemplateVariable objectReference="ModelValue_215"/>
      <StateTemplateVariable objectReference="ModelValue_217"/>
      <StateTemplateVariable objectReference="ModelValue_218"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 7131.4437299996334 3611387.4722043518 2318.7564433152638 83411.493122878295 348205.76605032221 444478.39400965557 27112.892084477469 16.741821099107149 7553510.5629981197 5314621.6602560114 2348541.369331039 102415.9970892102 505973.20938342536 1915.894621127193 0 7798673.6180500006 926214.74297503615 7212745.4386496814 428562.47568196338 10257237.8075299 926214.74297503615 0 275273.76400187978 432.74067697274342 13824.709350325529 2514162.666743997 93.928768960989473 0.0025000000000000001 0.0001142412732544542 0.00022197169318651728 18.500918641635661 0.00022197169318651728 0 0.0002933226422510503 0.00031982700000000001 0 0.00089299602995035509 0.0010274126244695619 0.84365297237173797 0.035803860144060298 0.0010274126244695619 1.0000000000000001e-05 1.285674999999997 0.49124019999999791 0.3644160000000003 0.68185023999999872 0.65134631200000026 0.82302954400000106 1.6984982995744289e-07 0.55988479999999918 8.8649644985023138e-06 8.4018813742249228e-07 1.7032568987969644e-05 4.5710276111230481e-07 2.2956466042167914e-08 4.1748646153082307e-06 1.6591419781269655e-06 1.8353002812203092e-07 0 917.49835381634625 7828784.3269999996 2.5900000000000002e-06 7.9999999999999996e-07 1.2999999999999999e-05 0.22584699999999999 5.9999253986099763 214.511 8.6072734027274997e-08 0.002126924084237061 1.0000000000000001e-05 1.00000000002221e-05 9.7980800000000006e-06 1.0000000000000001e-05 4.9291e-05 5.0000000000000002e-05 0.0001 0.0050000000000000001 0.038080424418151397 0.000100000000000222 0.0019999999999997802 0.59989342964577941 18.500918641635661 0.00374704364447229 0.117842 7.9497024021163017e-05 9.9999999999999995e-07 0.000100000000000222 0.000100000000000222 0.23262432287335619 3.6929099999999999 0.00120941 0.0016361306255064201 11501.848605491499 2.5904620308721599e-05 0.00071082263811762803 0.000221888641398861 0.000115242287512479 0.332175 0.0099999999999997799 0.00091336958216119905 1.0000000002220399e-06 1.0937545446161601 0 1.22913885610405e-05 2.1819503787823699e-05 1.0000000002220399e-06 0.83406985346583096 0 5.97504797065566e-06 2.1894167810831798e-06 0.000171416922199217 0.58439602675956803 0.050715716095883802 145028.78158363799 584678.80956640502 21395.245793948801 1491678.2351977001 28373108.944711499 1.8e-05 0.00040000000000000002 16.832999999999998 0.00092400000000000002 6.1442899999999994e-05 197139.21763645901 0.102372088824604 3050644.1138216699 2.5647334845410801 549341.56606688304 0.00025145997620859502 0.00053155456244858516 0.84365297237173797 0.035803860144060298 0.00089299602995035509 1.5942540684736069e-05 0.00050000000000000001 1.758629979014617e-06 0 0 0 0 0 9.9999999999999995e-08 0 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_12" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_10" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Resolution" type="unsignedFloat" value="1.0000000000000001e-09"/>
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
      <Report reference="Report_2" target="EventTest30.1.txt" append="0" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="200"/>
        <Parameter name="StepSize" type="float" value="5000"/>
        <Parameter name="Duration" type="float" value="1000000"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="0"/>
        <Parameter name="OutputStartTime" type="float" value="10000"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="1"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-08"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
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
      <Report reference="Report_19" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_8" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_9" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Subtask" type="cn" value="CN=Root,Vector=TaskList[Steady-State]"/>
        <ParameterText name="ObjectiveExpression" type="expression">
          &lt;CN=Root,Vector=TaskList[Steady-State],Eigen Values=Eigenvalues of reduced system Jacobian,Reference=Maximum real part of complex eigenvalue>
        </ParameterText>
        <Parameter name="Maximize" type="bool" value="1"/>
        <Parameter name="Randomize Start Values" type="bool" value="0"/>
        <Parameter name="Calculate Statistics" type="bool" value="1"/>
        <ParameterGroup name="OptimizationItemList">
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="9.79808e-006"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=beuke1,Vector=Values[IkBa_deg_cyt_k],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="9.7980800000000006e-06"/>
            <Parameter name="UpperBound" type="cn" value="1.46971e-005"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="3.28606e-005"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=beuke1,Vector=Values[IkBa_mRNA_deg_cyt_k],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="4.9291e-05"/>
            <Parameter name="UpperBound" type="cn" value="4.9291e-005"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="0.117842"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=beuke1,Vector=Values[IkBa_phosphorylation_kM],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="0.117842"/>
            <Parameter name="UpperBound" type="cn" value="0.176763"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="7.9497e-005"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=beuke1,Vector=Values[IkBa_transcription_elongation_kbasal],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="7.9497024021163017e-05"/>
            <Parameter name="UpperBound" type="cn" value="0.000119245"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="0.000806272"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=beuke1,Vector=Values[IkBa_translation_vmax],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="0.00120941"/>
            <Parameter name="UpperBound" type="cn" value="0.00120941"/>
          </ParameterGroup>
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
        </ParameterGroup>
      </Problem>
      <Method name="Particle Swarm" type="ParticleSwarm">
        <Parameter name="Iteration Limit" type="unsignedInteger" value="500"/>
        <Parameter name="Swarm Size" type="unsignedInteger" value="50"/>
        <Parameter name="Std. Deviation" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
        <Parameter name="#LogVerbosity" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_7" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_8" target="" append="1" confirmOverwrite="1"/>
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
          <Parameter name="Weight" type="unsignedFloat" value="1"/>
          <Parameter name="Threshold" type="unsignedInteger" value="5"/>
        </ParameterGroup>
      </Problem>
      <Method name="Evolutionary Programming" type="EvolutionaryProgram">
        <Parameter name="Number of Generations" type="unsignedInteger" value="200"/>
        <Parameter name="Population Size" type="unsignedInteger" value="20"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
        <Parameter name="#LogVerbosity" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_6" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_7" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_12"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1.0000000000000001e-09"/>
        <Parameter name="Use Reder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
      </Method>
    </Task>
    <Task key="Task_5" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_6" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="ExponentNumber" type="unsignedInteger" value="3"/>
        <Parameter name="DivergenceRequested" type="bool" value="1"/>
        <Parameter name="TransientTime" type="float" value="0"/>
      </Problem>
      <Method name="Wolf Method" type="WolfMethod">
        <Parameter name="Orthonormalization Interval" type="unsignedFloat" value="1"/>
        <Parameter name="Overall time" type="unsignedFloat" value="1000"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_4" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_5" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="ILDM (LSODA,Deuflhard)" type="TimeScaleSeparation(ILDM,Deuflhard)">
        <Parameter name="Deuflhard Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
      </Method>
    </Task>
    <Task key="Task_3" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_4" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="SubtaskType" type="unsignedInteger" value="1"/>
        <ParameterGroup name="TargetFunctions">
          <Parameter name="SingleObject" type="cn" value=""/>
          <Parameter name="ObjectListType" type="unsignedInteger" value="45"/>
        </ParameterGroup>
        <ParameterGroup name="ListOfVariables">
          <ParameterGroup name="Variables">
            <Parameter name="SingleObject" type="cn" value=""/>
            <Parameter name="ObjectListType" type="unsignedInteger" value="41"/>
          </ParameterGroup>
          <ParameterGroup name="Variables">
            <Parameter name="SingleObject" type="cn" value=""/>
            <Parameter name="ObjectListType" type="unsignedInteger" value="0"/>
          </ParameterGroup>
        </ParameterGroup>
      </Problem>
      <Method name="Sensitivities Method" type="SensitivitiesMethod">
        <Parameter name="Delta factor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Delta minimum" type="unsignedFloat" value="9.9999999999999998e-13"/>
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
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
        <Parameter name="LimitCrossings" type="bool" value="0"/>
        <Parameter name="NumCrossingsLimit" type="unsignedInteger" value="0"/>
        <Parameter name="LimitOutTime" type="bool" value="0"/>
        <Parameter name="LimitOutCrossings" type="bool" value="0"/>
        <Parameter name="PositiveDirection" type="bool" value="1"/>
        <Parameter name="NumOutCrossingsLimit" type="unsignedInteger" value="0"/>
        <Parameter name="LimitUntilConvergence" type="bool" value="0"/>
        <Parameter name="ConvergenceTolerance" type="float" value="9.9999999999999995e-07"/>
        <Parameter name="Threshold" type="float" value="0"/>
        <Parameter name="DelayOutputUntilConvergence" type="bool" value="0"/>
        <Parameter name="OutputConvergenceTolerance" type="float" value="9.9999999999999995e-07"/>
        <ParameterText name="TriggerExpression" type="expression">
          
        </ParameterText>
        <Parameter name="SingleVariable" type="cn" value=""/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_13" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_3" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_12"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_10" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_19" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_9" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_8" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_7" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_6" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <Report key="Report_5" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_4" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_3" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <Report key="Report_2" name="Time, Concentrations, Volumes, and Global Quantity Values" taskType="timeCourse" separator="&#x09;" precision="6">
      <Comment>
        A table of time, variable species concentrations, variable compartment volumes, and variable global quantity values.
      </Comment>
      <Table printTitle="1">
        <Object cn="CN=Root,Model=beuke1,Reference=Time"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[LPS],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[TNFR1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[TNFa:TNFR1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa_mRNA],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa_pre_mRNA_1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa_pre_mRNA_2],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[MSK1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[MSK1_P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65_2P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65-IkBa],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65_P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa_mRNA],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[JNK],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[JNK_P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[TNFR1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[TNFa:TNFR1],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p38],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p38_P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IKKb],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IKKb_p],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65-IkBa],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65_P],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa_p],Reference=Concentration"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[IkBa_nuclear_export_k],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[IkBa:p65_dissociation_k],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[IkBa:p65_phosphorylation_vmax],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[IkBa_phosphorylation_kcat],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[IkBa_phosphorylation_vmax],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[JNK_active_phosphorylation_vmax],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[MSK1_activation_vmax],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[k_TNFa:TNFR1_dissociation],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[p38_active_phosphorylation_vmax],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[p65_2P_dephosphorylation],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[p65_MSK1_phosphrylation_vmax],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[p65_P_MSK1_phosphrylation_kM],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[p65_P_MSK1_phosphrylation_kcat],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[p65_P_MSK1_phosphrylation_vmax],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[p65_nuclear_export_k],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[scaled_IkBa],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[scaled_IkBa_P],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[scaled_IkBa_mRNA],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[scaled_JNK_P],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[scaled_MSK_P],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[scaled_p38_P],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[scaled_p65],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[scaled_p65_P],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa_P],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa_mRNA],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[unscaled_JNK_P],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[unscaled_MSK_P],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[unscaled_p38_P],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[unscaled_p65],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[unscaled_p65_P],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[min],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[max],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[amp],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[time1],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[period],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[avg],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[int],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[sign],Reference=Value"/>
        <Object cn="CN=Root,Model=beuke1,Vector=Values[counter],Reference=Value"/>
      </Table>
    </Report>
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="plot_1" type="Plot2D" active="1" taskTypes="">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="Values[amp]|Time" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[amp],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[avg]|Time" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[avg],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[max]|Time" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[max],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[min]|Time" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[min],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[period]|Time" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[period],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[p65{cytoplasm}]|Time" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="p65{cytoplasm}.Rate|Time" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Rate"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
    <PlotSpecification name="plot" type="Plot2D" active="1" taskTypes="">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="Values[counter]|Time" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[counter],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[sign]|Time" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[sign],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="p65{cytoplasm}.Rate|Time" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Rate"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
    <PlotSpecification name="Concentrations, Volumes, and Global Quantity Values" type="Plot2D" active="0" taskTypes="">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="Values[IkBa:p65_dissociation_k]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[IkBa:p65_dissociation_k],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[IkBa:p65_phosphorylation_vmax]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[IkBa:p65_phosphorylation_vmax],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[IkBa_nuclear_export_k]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[IkBa_nuclear_export_k],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[IkBa_phosphorylation_kcat]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[IkBa_phosphorylation_kcat],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[IkBa_phosphorylation_vmax]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[IkBa_phosphorylation_vmax],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[JNK_active_phosphorylation_vmax]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[JNK_active_phosphorylation_vmax],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[MSK1_activation_vmax]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[MSK1_activation_vmax],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[amp]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[amp],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[avg]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[avg],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[counter]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[counter],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[int]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[int],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[k_TNFa:TNFR1_dissociation]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[k_TNFa:TNFR1_dissociation],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[max]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[max],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[min]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[min],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[p38_active_phosphorylation_vmax]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[p38_active_phosphorylation_vmax],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[p65_2P_dephosphorylation]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[p65_2P_dephosphorylation],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[p65_MSK1_phosphrylation_vmax]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[p65_MSK1_phosphrylation_vmax],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[p65_P_MSK1_phosphrylation_kM]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[p65_P_MSK1_phosphrylation_kM],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[p65_P_MSK1_phosphrylation_kcat]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[p65_P_MSK1_phosphrylation_kcat],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[p65_P_MSK1_phosphrylation_vmax]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[p65_P_MSK1_phosphrylation_vmax],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[p65_nuclear_export_k]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[p65_nuclear_export_k],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[period]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[period],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[scaled_IkBa]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[scaled_IkBa],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[scaled_IkBa_P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[scaled_IkBa_P],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[scaled_IkBa_mRNA]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[scaled_IkBa_mRNA],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[scaled_JNK_P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[scaled_JNK_P],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[scaled_MSK_P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[scaled_MSK_P],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[scaled_p38_P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[scaled_p38_P],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[scaled_p65]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[scaled_p65],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[scaled_p65_P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[scaled_p65_P],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[sign]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[sign],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[time1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[time1],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[unscaled_IkBa]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[unscaled_IkBa_P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa_P],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[unscaled_IkBa_mRNA]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa_mRNA],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[unscaled_JNK_P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[unscaled_JNK_P],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[unscaled_MSK_P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[unscaled_MSK_P],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[unscaled_p38_P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[unscaled_p38_P],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[unscaled_p65]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[unscaled_p65],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="Values[unscaled_p65_P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Values[unscaled_p65_P],Reference=Value"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IKKb]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IKKb],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IKKb_p]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IKKb_p],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBa_mRNA{cytoplasm}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa_mRNA],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBa_mRNA{nucleus}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa_mRNA],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBa_p]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa_p],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBa_pre_mRNA_1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa_pre_mRNA_1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBa_pre_mRNA_2]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa_pre_mRNA_2],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBa{cytoplasm}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[IkBa{nucleus}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[JNK]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[JNK],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[JNK_P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[JNK_P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[LPS]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[LPS],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[MSK1]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[MSK1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[MSK1_P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[MSK1_P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[TNFR1{EL}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[TNFR1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[TNFR1{cytoplasm}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[TNFR1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[TNFa:TNFR1{EL}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[TNFa:TNFR1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[TNFa:TNFR1{cytoplasm}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[TNFa:TNFR1],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[p38]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p38],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[p38_P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p38_P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[p65-IkBa{cytoplasm}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65-IkBa],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[p65-IkBa{nucleus}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65-IkBa],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[p65_2P]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65_2P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[p65_P{cytoplasm}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65_P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[p65_P{nucleus}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65_P],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[p65{cytoplasm}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[p65{nucleus}]" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
  </GUI>
  <SBMLReference file="beuke1.xml">
    <SBMLMap SBMLid="Complex_association_c" COPASIkey="Reaction_49"/>
    <SBMLMap SBMLid="Complex_degradation_IkBa_c" COPASIkey="Reaction_50"/>
    <SBMLMap SBMLid="Complex_degradation_IkBa_n" COPASIkey="Reaction_51"/>
    <SBMLMap SBMLid="Complex_degradation_p65_c" COPASIkey="Reaction_52"/>
    <SBMLMap SBMLid="Complex_degradation_p65_n" COPASIkey="Reaction_53"/>
    <SBMLMap SBMLid="Complex_nuclear_shuttle" COPASIkey="Reaction_54"/>
    <SBMLMap SBMLid="EL" COPASIkey="Compartment_3"/>
    <SBMLMap SBMLid="IKK_phosphorylation" COPASIkey="Reaction_55"/>
    <SBMLMap SBMLid="IKKb_active_phosphorylation_kA" COPASIkey="ModelValue_108"/>
    <SBMLMap SBMLid="IKKb_active_phosphorylation_kM" COPASIkey="ModelValue_109"/>
    <SBMLMap SBMLid="IKKb_active_phosphorylation_vmax" COPASIkey="ModelValue_110"/>
    <SBMLMap SBMLid="IKKb_basal_phosphoylation_k" COPASIkey="ModelValue_111"/>
    <SBMLMap SBMLid="IKKb_dephopshorylation_k" COPASIkey="ModelValue_112"/>
    <SBMLMap SBMLid="IkBa_cytoplasm" COPASIkey="Metabolite_37"/>
    <SBMLMap SBMLid="IkBa_deg_complex_cyt_k" COPASIkey="ModelValue_8"/>
    <SBMLMap SBMLid="IkBa_deg_complex_nuc_k" COPASIkey="ModelValue_7"/>
    <SBMLMap SBMLid="IkBa_deg_cyt_k" COPASIkey="ModelValue_114"/>
    <SBMLMap SBMLid="IkBa_deg_nuc_k" COPASIkey="ModelValue_115"/>
    <SBMLMap SBMLid="IkBa_degradation_c" COPASIkey="Reaction_56"/>
    <SBMLMap SBMLid="IkBa_degradation_n" COPASIkey="Reaction_57"/>
    <SBMLMap SBMLid="IkBa_mRNA_cytoplasm" COPASIkey="Metabolite_38"/>
    <SBMLMap SBMLid="IkBa_mRNA_deg_cyt_k" COPASIkey="ModelValue_116"/>
    <SBMLMap SBMLid="IkBa_mRNA_deg_nuc_k" COPASIkey="ModelValue_117"/>
    <SBMLMap SBMLid="IkBa_mRNA_degradation_c" COPASIkey="Reaction_58"/>
    <SBMLMap SBMLid="IkBa_mRNA_degradation_n" COPASIkey="Reaction_59"/>
    <SBMLMap SBMLid="IkBa_mRNA_nucleus" COPASIkey="Metabolite_49"/>
    <SBMLMap SBMLid="IkBa_mRNA_transport" COPASIkey="Reaction_60"/>
    <SBMLMap SBMLid="IkBa_mRNA_transport_k" COPASIkey="ModelValue_118"/>
    <SBMLMap SBMLid="IkBa_nuclear_export_k" COPASIkey="ModelValue_119"/>
    <SBMLMap SBMLid="IkBa_nuclear_import_k" COPASIkey="ModelValue_120"/>
    <SBMLMap SBMLid="IkBa_nuclear_shuttle" COPASIkey="Reaction_61"/>
    <SBMLMap SBMLid="IkBa_p65_association_k" COPASIkey="ModelValue_121"/>
    <SBMLMap SBMLid="IkBa_p65_dissociation_k" COPASIkey="ModelValue_122"/>
    <SBMLMap SBMLid="IkBa_p65_nuclear_export_k" COPASIkey="ModelValue_123"/>
    <SBMLMap SBMLid="IkBa_p65_nuclear_import_k" COPASIkey="ModelValue_124"/>
    <SBMLMap SBMLid="IkBa_p65_phosphorylation_kM" COPASIkey="ModelValue_125"/>
    <SBMLMap SBMLid="IkBa_p65_phosphorylation_kcat" COPASIkey="ModelValue_126"/>
    <SBMLMap SBMLid="IkBa_p65_phosphorylation_vmax" COPASIkey="ModelValue_127"/>
    <SBMLMap SBMLid="IkBa_p_active_degradation_k" COPASIkey="ModelValue_128"/>
    <SBMLMap SBMLid="IkBa_phosphorylation" COPASIkey="Reaction_62"/>
    <SBMLMap SBMLid="IkBa_phosphorylation_kM" COPASIkey="ModelValue_129"/>
    <SBMLMap SBMLid="IkBa_phosphorylation_kcat" COPASIkey="ModelValue_130"/>
    <SBMLMap SBMLid="IkBa_phosphorylation_vmax" COPASIkey="ModelValue_131"/>
    <SBMLMap SBMLid="IkBa_pre_mRNA_1" COPASIkey="Metabolite_47"/>
    <SBMLMap SBMLid="IkBa_pre_mRNA_2" COPASIkey="Metabolite_29"/>
    <SBMLMap SBMLid="IkBa_transcription_elongation_1" COPASIkey="Reaction_63"/>
    <SBMLMap SBMLid="IkBa_transcription_elongation_2" COPASIkey="Reaction_64"/>
    <SBMLMap SBMLid="IkBa_transcription_elongation_kbasal" COPASIkey="ModelValue_132"/>
    <SBMLMap SBMLid="IkBa_transcription_initiation_kbasal" COPASIkey="ModelValue_133"/>
    <SBMLMap SBMLid="IkBa_transcription_kA2_p65_P" COPASIkey="ModelValue_134"/>
    <SBMLMap SBMLid="IkBa_transcription_kA3_p65_2P" COPASIkey="ModelValue_135"/>
    <SBMLMap SBMLid="IkBa_transcription_kA_p65" COPASIkey="ModelValue_136"/>
    <SBMLMap SBMLid="IkBa_translation" COPASIkey="Reaction_65"/>
    <SBMLMap SBMLid="IkBa_translation_Km" COPASIkey="ModelValue_137"/>
    <SBMLMap SBMLid="IkBa_translation_vmax" COPASIkey="ModelValue_138"/>
    <SBMLMap SBMLid="JNK" COPASIkey="Metabolite_39"/>
    <SBMLMap SBMLid="JNK_P" COPASIkey="Metabolite_40"/>
    <SBMLMap SBMLid="JNK_active_phoshorylation_Km" COPASIkey="ModelValue_139"/>
    <SBMLMap SBMLid="JNK_active_phosphorylation" COPASIkey="Reaction_66"/>
    <SBMLMap SBMLid="JNK_active_phosphorylation_kcat" COPASIkey="ModelValue_140"/>
    <SBMLMap SBMLid="JNK_active_phosphorylation_vmax" COPASIkey="ModelValue_141"/>
    <SBMLMap SBMLid="JNK_basal_phosphorylation" COPASIkey="Reaction_67"/>
    <SBMLMap SBMLid="JNK_basal_phosphorylation_k" COPASIkey="ModelValue_142"/>
    <SBMLMap SBMLid="JNK_dephosphorylation" COPASIkey="Reaction_68"/>
    <SBMLMap SBMLid="JNK_dephosphorylation_k" COPASIkey="ModelValue_143"/>
    <SBMLMap SBMLid="LPS" COPASIkey="Metabolite_41"/>
    <SBMLMap SBMLid="LPS_LSEC_degradation" COPASIkey="Reaction_69"/>
    <SBMLMap SBMLid="LPS_LSEC_degradation_k" COPASIkey="ModelValue_144"/>
    <SBMLMap SBMLid="LPS_MC_degradation" COPASIkey="Reaction_70"/>
    <SBMLMap SBMLid="LPS_MC_degradation_k" COPASIkey="ModelValue_145"/>
    <SBMLMap SBMLid="MSK1" COPASIkey="Metabolite_30"/>
    <SBMLMap SBMLid="MSK1_P" COPASIkey="Metabolite_31"/>
    <SBMLMap SBMLid="MSK1_activation" COPASIkey="Reaction_71"/>
    <SBMLMap SBMLid="MSK1_activation_kM" COPASIkey="ModelValue_146"/>
    <SBMLMap SBMLid="MSK1_activation_vmax" COPASIkey="ModelValue_147"/>
    <SBMLMap SBMLid="MSK1_deactivation" COPASIkey="Reaction_72"/>
    <SBMLMap SBMLid="MSK1_dephosphorylation_k" COPASIkey="ModelValue_148"/>
    <SBMLMap SBMLid="MSK1_phosphorylation_kcat" COPASIkey="ModelValue_149"/>
    <SBMLMap SBMLid="TNFR1_EL" COPASIkey="Metabolite_45"/>
    <SBMLMap SBMLid="TNFR1_cytoplasm" COPASIkey="Metabolite_42"/>
    <SBMLMap SBMLid="TNFR1_shuttle" COPASIkey="Reaction_73"/>
    <SBMLMap SBMLid="TNFa_LSEC_transcription_elongation_k" COPASIkey="ModelValue_150"/>
    <SBMLMap SBMLid="TNFa_LSEC_transcription_initiation_kA_LPS" COPASIkey="ModelValue_151"/>
    <SBMLMap SBMLid="TNFa_LSEC_transcription_initiation_kbasal" COPASIkey="ModelValue_152"/>
    <SBMLMap SBMLid="TNFa_LSEC_transcription_initiation_vA_LPS" COPASIkey="ModelValue_153"/>
    <SBMLMap SBMLid="TNFa_LSEC_translation_k" COPASIkey="ModelValue_154"/>
    <SBMLMap SBMLid="TNFa_MC_transcription_elongation_k" COPASIkey="ModelValue_155"/>
    <SBMLMap SBMLid="TNFa_MC_transcription_initiation_kA_LPS" COPASIkey="ModelValue_156"/>
    <SBMLMap SBMLid="TNFa_MC_transcription_initiation_kbasal" COPASIkey="ModelValue_157"/>
    <SBMLMap SBMLid="TNFa_MC_transcription_initiation_vA_LPS" COPASIkey="ModelValue_158"/>
    <SBMLMap SBMLid="TNFa_MC_translation_k" COPASIkey="ModelValue_159"/>
    <SBMLMap SBMLid="TNFa_TNFR1_EL" COPASIkey="Metabolite_50"/>
    <SBMLMap SBMLid="TNFa_TNFR1_association" COPASIkey="Reaction_74"/>
    <SBMLMap SBMLid="TNFa_TNFR1_cytoplasm" COPASIkey="Metabolite_48"/>
    <SBMLMap SBMLid="TNFa_TNFR1_internalisation" COPASIkey="Reaction_75"/>
    <SBMLMap SBMLid="TNFa_degradation" COPASIkey="Reaction_76"/>
    <SBMLMap SBMLid="TNFa_degradation_k" COPASIkey="ModelValue_160"/>
    <SBMLMap SBMLid="TNFa_internal_degradation" COPASIkey="Reaction_77"/>
    <SBMLMap SBMLid="TNFa_mRNA_LSEC_degradation_k" COPASIkey="ModelValue_161"/>
    <SBMLMap SBMLid="TNFa_mRNA_MC_degradation_k" COPASIkey="ModelValue_162"/>
    <SBMLMap SBMLid="basal_IKKb_phosphorylation" COPASIkey="Reaction_78"/>
    <SBMLMap SBMLid="c1" COPASIkey="Compartment_4"/>
    <SBMLMap SBMLid="default" COPASIkey="Compartment_5"/>
    <SBMLMap SBMLid="k_IkBa" COPASIkey="ModelValue_163"/>
    <SBMLMap SBMLid="k_IkBa_P" COPASIkey="ModelValue_164"/>
    <SBMLMap SBMLid="k_IkBa_mRNA" COPASIkey="ModelValue_165"/>
    <SBMLMap SBMLid="k_JNK_P" COPASIkey="ModelValue_166"/>
    <SBMLMap SBMLid="k_MSK_P" COPASIkey="ModelValue_167"/>
    <SBMLMap SBMLid="k_TNFR1_outer_membrane2vessicle_shuttle" COPASIkey="ModelValue_168"/>
    <SBMLMap SBMLid="k_TNFR1_vessicle2outer_membrane_shuttle" COPASIkey="ModelValue_169"/>
    <SBMLMap SBMLid="k_TNFa_TNFR1_association" COPASIkey="ModelValue_170"/>
    <SBMLMap SBMLid="k_TNFa_TNFR1_dissociation" COPASIkey="ModelValue_171"/>
    <SBMLMap SBMLid="k_TNFa_TNFR1_internalisation" COPASIkey="ModelValue_172"/>
    <SBMLMap SBMLid="k_TNFa_internal_degradation" COPASIkey="ModelValue_173"/>
    <SBMLMap SBMLid="k_p38_P" COPASIkey="ModelValue_174"/>
    <SBMLMap SBMLid="k_p65" COPASIkey="ModelValue_175"/>
    <SBMLMap SBMLid="k_p65_P" COPASIkey="ModelValue_176"/>
    <SBMLMap SBMLid="p38" COPASIkey="Metabolite_51"/>
    <SBMLMap SBMLid="p38_P" COPASIkey="Metabolite_46"/>
    <SBMLMap SBMLid="p38_active_phoshorylation_Km" COPASIkey="ModelValue_177"/>
    <SBMLMap SBMLid="p38_active_phosphorylation" COPASIkey="Reaction_79"/>
    <SBMLMap SBMLid="p38_active_phosphorylation_kcat" COPASIkey="ModelValue_178"/>
    <SBMLMap SBMLid="p38_active_phosphorylation_vmax" COPASIkey="ModelValue_179"/>
    <SBMLMap SBMLid="p38_basal_phosphorylation" COPASIkey="Reaction_99"/>
    <SBMLMap SBMLid="p38_basal_phosphorylation_k" COPASIkey="ModelValue_180"/>
    <SBMLMap SBMLid="p38_dephosphorylation" COPASIkey="Reaction_98"/>
    <SBMLMap SBMLid="p38_dephosphorylation_k" COPASIkey="ModelValue_181"/>
    <SBMLMap SBMLid="p65_2P" COPASIkey="Metabolite_32"/>
    <SBMLMap SBMLid="p65_2P_degradation" COPASIkey="Reaction_97"/>
    <SBMLMap SBMLid="p65_2P_dephosphorylation" COPASIkey="ModelValue_182"/>
    <SBMLMap SBMLid="p65_2P_dephosphorylation_0" COPASIkey="Reaction_96"/>
    <SBMLMap SBMLid="p65_IkBa_nucleus" COPASIkey="Metabolite_33"/>
    <SBMLMap SBMLid="p65_MSK1_phosphorylation_kM" COPASIkey="ModelValue_183"/>
    <SBMLMap SBMLid="p65_MSK1_phosphrylation_kcat" COPASIkey="ModelValue_184"/>
    <SBMLMap SBMLid="p65_MSK1_phosphrylation_vmax" COPASIkey="ModelValue_185"/>
    <SBMLMap SBMLid="p65_P_MSK1_phosphrylation_kM" COPASIkey="ModelValue_186"/>
    <SBMLMap SBMLid="p65_P_MSK1_phosphrylation_kcat" COPASIkey="ModelValue_187"/>
    <SBMLMap SBMLid="p65_P_MSK1_phosphrylation_vmax" COPASIkey="ModelValue_188"/>
    <SBMLMap SBMLid="p65_P_degradation_c" COPASIkey="Reaction_95"/>
    <SBMLMap SBMLid="p65_P_degradation_n" COPASIkey="Reaction_94"/>
    <SBMLMap SBMLid="p65_P_dephosphorylation_c" COPASIkey="Reaction_93"/>
    <SBMLMap SBMLid="p65_P_dephosphorylation_k" COPASIkey="ModelValue_189"/>
    <SBMLMap SBMLid="p65_P_dephosphorylation_n" COPASIkey="Reaction_92"/>
    <SBMLMap SBMLid="p65_P_phosphorylation_MSK1" COPASIkey="Reaction_91"/>
    <SBMLMap SBMLid="p65_cytoplasm" COPASIkey="Metabolite_44"/>
    <SBMLMap SBMLid="p65_degradation_k" COPASIkey="ModelValue_190"/>
    <SBMLMap SBMLid="p65_mRNA" COPASIkey="Metabolite_43"/>
    <SBMLMap SBMLid="p65_nuclear_export_k" COPASIkey="ModelValue_191"/>
    <SBMLMap SBMLid="p65_nuclear_import_k" COPASIkey="ModelValue_192"/>
    <SBMLMap SBMLid="p65_nuclear_shuttle" COPASIkey="Reaction_90"/>
    <SBMLMap SBMLid="p65_nucleus" COPASIkey="Metabolite_34"/>
    <SBMLMap SBMLid="p65_phosphorylation_MSK1" COPASIkey="Reaction_89"/>
    <SBMLMap SBMLid="p65_translation" COPASIkey="Reaction_88"/>
    <SBMLMap SBMLid="p65_translation_k" COPASIkey="ModelValue_193"/>
    <SBMLMap SBMLid="re10" COPASIkey="Reaction_87"/>
    <SBMLMap SBMLid="re14" COPASIkey="Reaction_86"/>
    <SBMLMap SBMLid="re15" COPASIkey="Reaction_85"/>
    <SBMLMap SBMLid="re17" COPASIkey="Reaction_84"/>
    <SBMLMap SBMLid="re19" COPASIkey="Reaction_83"/>
    <SBMLMap SBMLid="re3" COPASIkey="Reaction_82"/>
    <SBMLMap SBMLid="s11" COPASIkey="Metabolite_35"/>
    <SBMLMap SBMLid="s14" COPASIkey="Metabolite_63"/>
    <SBMLMap SBMLid="s15" COPASIkey="Metabolite_62"/>
    <SBMLMap SBMLid="s16" COPASIkey="Metabolite_52"/>
    <SBMLMap SBMLid="s19" COPASIkey="Metabolite_61"/>
    <SBMLMap SBMLid="s3" COPASIkey="Metabolite_60"/>
    <SBMLMap SBMLid="s5" COPASIkey="Metabolite_59"/>
    <SBMLMap SBMLid="s8" COPASIkey="Metabolite_36"/>
    <SBMLMap SBMLid="scaled_IkBa" COPASIkey="ModelValue_194"/>
    <SBMLMap SBMLid="scaled_IkBa_P" COPASIkey="ModelValue_195"/>
    <SBMLMap SBMLid="scaled_IkBa_mRNA" COPASIkey="ModelValue_196"/>
    <SBMLMap SBMLid="scaled_JNK_P" COPASIkey="ModelValue_197"/>
    <SBMLMap SBMLid="scaled_MSK_P" COPASIkey="ModelValue_198"/>
    <SBMLMap SBMLid="scaled_p38_P" COPASIkey="ModelValue_199"/>
    <SBMLMap SBMLid="scaled_p65" COPASIkey="ModelValue_200"/>
    <SBMLMap SBMLid="scaled_p65_P" COPASIkey="ModelValue_201"/>
    <SBMLMap SBMLid="unscaled_IkBa" COPASIkey="ModelValue_202"/>
    <SBMLMap SBMLid="unscaled_IkBa_P" COPASIkey="ModelValue_203"/>
    <SBMLMap SBMLid="unscaled_IkBa_mRNA" COPASIkey="ModelValue_204"/>
    <SBMLMap SBMLid="unscaled_JNK_P" COPASIkey="ModelValue_205"/>
    <SBMLMap SBMLid="unscaled_MSK_P" COPASIkey="ModelValue_206"/>
    <SBMLMap SBMLid="unscaled_p38_P" COPASIkey="ModelValue_207"/>
    <SBMLMap SBMLid="unscaled_p65" COPASIkey="ModelValue_208"/>
    <SBMLMap SBMLid="unscaled_p65_P" COPASIkey="ModelValue_209"/>
  </SBMLReference>
  <ListOfUnitDefinitions>
    <UnitDefinition key="Unit_0" name="meter" symbol="m">
      <Expression>
        m
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_2" name="second" symbol="s">
      <Expression>
        s
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_6" name="Avogadro" symbol="Avogadro">
      <Expression>
        Avogadro
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_8" name="item" symbol="#">
      <Expression>
        #
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_17" name="liter" symbol="l">
      <Expression>
        0.001*m^3
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_20" name="mole" symbol="mol">
      <Expression>
        Avogadro*#
      </Expression>
    </UnitDefinition>
  </ListOfUnitDefinitions>
</COPASI>
