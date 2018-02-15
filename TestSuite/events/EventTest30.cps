<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.23.172+ (Debug) (http://www.copasi.org) at 2018-02-15 14:59:12 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="23" versionDevel="172" copasiSourcesModified="1">
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
    <Function key="Function_40" name="Catalytic activation (irrev)_1" type="UserDefined" reversible="false">
      <Expression>
        IKKb_active_phosphorylation_vmax*s14*TNFa_TNFR1_EL/((IKKb_active_phosphorylation_kM+s14)*(IKKb_active_phosphorylation_kA+TNFa_TNFR1_EL))
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_264" name="IKKb_active_phosphorylation_kA" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_263" name="IKKb_active_phosphorylation_kM" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_262" name="IKKb_active_phosphorylation_vmax" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_261" name="TNFa_TNFR1_EL" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_250" name="s14" order="4" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_41" name="Henri-Michaelis-Menten (irreversible)_1" type="UserDefined" reversible="false">
      <Expression>
        IkBa_phosphorylation_vmax*IkBa_cytoplasm/(IkBa_phosphorylation_kM+IkBa_cytoplasm)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_269" name="IkBa_cytoplasm" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_268" name="IkBa_phosphorylation_kM" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_267" name="IkBa_phosphorylation_vmax" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_42" name="Henri-Michaelis-Menten (irreversible)_2" type="UserDefined" reversible="false">
      <Expression>
        IkBa_translation_vmax*IkBa_mRNA_cytoplasm/(IkBa_translation_Km+IkBa_mRNA_cytoplasm)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_270" name="IkBa_mRNA_cytoplasm" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_265" name="IkBa_translation_Km" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_266" name="IkBa_translation_vmax" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_43" name="Henri-Michaelis-Menten (irreversible)_3" type="UserDefined" reversible="false">
      <Expression>
        JNK_active_phosphorylation_vmax*JNK/(JNK_active_phoshorylation_Km+JNK)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_273" name="JNK" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_272" name="JNK_active_phoshorylation_Km" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_271" name="JNK_active_phosphorylation_vmax" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_44" name="Henri-Michaelis-Menten (irreversible)_4" type="UserDefined" reversible="false">
      <Expression>
        MSK1_activation_vmax*MSK1/(MSK1_activation_kM+MSK1)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_276" name="MSK1" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_275" name="MSK1_activation_kM" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_274" name="MSK1_activation_vmax" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_45" name="Henri-Michaelis-Menten (irreversible)_5" type="UserDefined" reversible="false">
      <Expression>
        p38_active_phosphorylation_vmax*p38/(p38_active_phoshorylation_Km+p38)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_279" name="p38" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_278" name="p38_active_phoshorylation_Km" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_277" name="p38_active_phosphorylation_vmax" order="2" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_46" name="Henri-Michaelis-Menten (irreversible)_6" type="UserDefined" reversible="false">
      <Expression>
        p65_P_MSK1_phosphrylation_vmax*s8/(p65_P_MSK1_phosphrylation_kM+s8)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_282" name="p65_P_MSK1_phosphrylation_kM" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_281" name="p65_P_MSK1_phosphrylation_vmax" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_280" name="s8" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_47" name="Henri-Michaelis-Menten (irreversible)_7" type="UserDefined" reversible="false">
      <Expression>
        p65_MSK1_phosphrylation_vmax*p65_nucleus/(p65_MSK1_phosphorylation_kM+p65_nucleus)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_285" name="p65_MSK1_phosphorylation_kM" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_284" name="p65_MSK1_phosphrylation_vmax" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_283" name="p65_nucleus" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_48" name="activated Transcription [1]_1" type="UserDefined" reversible="false">
      <Expression>
        IkBa_transcription_initiation_kbasal+IkBa_transcription_kA2_p65_P*s8+IkBa_transcription_kA_p65*p65_nucleus+IkBa_transcription_kA3_p65_2P*p65_2P
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_288" name="IkBa_transcription_initiation_kbasal" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_287" name="IkBa_transcription_kA2_p65_P" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_286" name="IkBa_transcription_kA3_p65_2P" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_289" name="IkBa_transcription_kA_p65" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_290" name="p65_2P" order="4" role="modifier"/>
        <ParameterDescription key="FunctionParameter_291" name="p65_nucleus" order="5" role="modifier"/>
        <ParameterDescription key="FunctionParameter_292" name="s8" order="6" role="modifier"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_49" name="Henri-Michaelis-Menten (irreversible)_8" type="UserDefined" reversible="false">
      <Expression>
        IkBa_p65_phosphorylation_vmax*s19/(IkBa_p65_phosphorylation_kM+s19)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_299" name="IkBa_p65_phosphorylation_kM" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_298" name="IkBa_p65_phosphorylation_vmax" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_297" name="s19" order="2" role="substrate"/>
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
      <Compartment key="Compartment_0" name="EL" simulationType="fixed" dimensionality="3" addNoise="false">
      </Compartment>
      <Compartment key="Compartment_1" name="nucleus" simulationType="fixed" dimensionality="3" addNoise="false">
      </Compartment>
      <Compartment key="Compartment_2" name="cytoplasm" simulationType="fixed" dimensionality="3" addNoise="false">
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="LPS" simulationType="reactions" compartment="Compartment_0" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_1" name="TNFR1" simulationType="reactions" compartment="Compartment_0" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_2" name="TNFa:TNFR1" simulationType="reactions" compartment="Compartment_0" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_3" name="TNFa" simulationType="fixed" compartment="Compartment_0" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_4" name="IkBa_mRNA" simulationType="reactions" compartment="Compartment_1" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_5" name="IkBa_pre_mRNA_1" simulationType="reactions" compartment="Compartment_1" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_6" name="IkBa_pre_mRNA_2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_7" name="MSK1" simulationType="reactions" compartment="Compartment_1" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_8" name="MSK1_P" simulationType="reactions" compartment="Compartment_1" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_9" name="p65_2P" simulationType="reactions" compartment="Compartment_1" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_10" name="p65-IkBa" simulationType="reactions" compartment="Compartment_1" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_11" name="p65" simulationType="reactions" compartment="Compartment_1" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_12" name="IkBa" simulationType="reactions" compartment="Compartment_1" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_13" name="p65_P" simulationType="reactions" compartment="Compartment_1" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_14" name="IkBa" simulationType="reactions" compartment="Compartment_2" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_15" name="IkBa_mRNA" simulationType="reactions" compartment="Compartment_2" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_16" name="JNK" simulationType="reactions" compartment="Compartment_2" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_17" name="JNK_P" simulationType="reactions" compartment="Compartment_2" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_18" name="TNFR1" simulationType="reactions" compartment="Compartment_2" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_19" name="TNFa:TNFR1" simulationType="reactions" compartment="Compartment_2" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_20" name="p38" simulationType="reactions" compartment="Compartment_2" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_21" name="p38_P" simulationType="reactions" compartment="Compartment_2" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_22" name="p65" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_22">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2018-02-14T14:08:09Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_23" name="p65_mRNA" simulationType="fixed" compartment="Compartment_2" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_24" name="IKKb" simulationType="reactions" compartment="Compartment_2" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_25" name="IKKb_p" simulationType="reactions" compartment="Compartment_2" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_26" name="p65-IkBa" simulationType="reactions" compartment="Compartment_2" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_27" name="p65_P" simulationType="reactions" compartment="Compartment_2" addNoise="false">
      </Metabolite>
      <Metabolite key="Metabolite_28" name="IkBa_p" simulationType="reactions" compartment="Compartment_2" addNoise="false">
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_0" name="IKKb_active_phosphorylation_kA" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_1" name="IKKb_active_phosphorylation_kM" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_2" name="IKKb_active_phosphorylation_vmax" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_3" name="IKKb_basal_phosphoylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_4" name="IKKb_dephopshorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_5" name="IkBa_deg_complex_cyt_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_6" name="IkBa_deg_complex_nuc_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_7" name="IkBa_deg_cyt_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_8" name="IkBa_deg_nuc_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_9" name="IkBa_mRNA_deg_cyt_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_10" name="IkBa_mRNA_deg_nuc_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_11" name="IkBa_mRNA_transport_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_12" name="IkBa_nuclear_export_k" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_nuclear_import_k],Reference=Value>*0.5
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_13" name="IkBa_nuclear_import_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_14" name="IkBa:p65_association_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_15" name="IkBa:p65_dissociation_k" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_association_k],Reference=Value>*0.003
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_16" name="IkBa:p65_nuclear_export_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_17" name="IkBa:p65_nuclear_import_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_18" name="IkBa:p65_phosphorylation_kM" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_19" name="IkBa:p65_phosphorylation_kcat" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_20" name="IkBa:p65_phosphorylation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_phosphorylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IKKb_p],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_21" name="IkBa_p_active_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_22" name="IkBa_phosphorylation_kM" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_23" name="IkBa_phosphorylation_kcat" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[IkBa:p65_phosphorylation_kcat],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_24" name="IkBa_phosphorylation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[IkBa_phosphorylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IKKb_p],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_25" name="IkBa_transcription_elongation_kbasal" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_26" name="IkBa_transcription_initiation_kbasal" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_27" name="IkBa_transcription_kA2_p65_P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_28" name="IkBa_transcription_kA3_p65_2P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_29" name="IkBa_transcription_kA_p65" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_30" name="IkBa_translation_Km" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_31" name="IkBa_translation_vmax" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_32" name="JNK_active_phoshorylation_Km" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_33" name="JNK_active_phosphorylation_kcat" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_34" name="JNK_active_phosphorylation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[JNK_active_phosphorylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[TNFa:TNFR1],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_35" name="JNK_basal_phosphorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_36" name="JNK_dephosphorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_37" name="LPS_LSEC_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_38" name="LPS_MC_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_39" name="MSK1_activation_kM" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_40" name="MSK1_activation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[MSK1_phosphorylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p38_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_41" name="MSK1_dephosphorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_42" name="MSK1_phosphorylation_kcat" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_43" name="TNFa_LSEC_transcription_elongation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_44" name="TNFa_LSEC_transcription_initiation_kA_LPS" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_45" name="TNFa_LSEC_transcription_initiation_kbasal" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_46" name="TNFa_LSEC_transcription_initiation_vA_LPS" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_47" name="TNFa_LSEC_translation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_48" name="TNFa_MC_transcription_elongation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_49" name="TNFa_MC_transcription_initiation_kA_LPS" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_50" name="TNFa_MC_transcription_initiation_kbasal" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_51" name="TNFa_MC_transcription_initiation_vA_LPS" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_52" name="TNFa_MC_translation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_53" name="TNFa_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_54" name="TNFa_mRNA_LSEC_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_55" name="TNFa_mRNA_MC_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_56" name="k_IkBa" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_57" name="k_IkBa_P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_58" name="k_IkBa_mRNA" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_59" name="k_JNK_P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_60" name="k_MSK_P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_61" name="k_TNFR1_outer_membrane2vessicle_shuttle" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_62" name="k_TNFR1_vessicle2outer_membrane_shuttle" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_63" name="k_TNFa:TNFR1_association" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_64" name="k_TNFa:TNFR1_dissociation" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_TNFa:TNFR1_association],Reference=Value>*1.9e-005
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_65" name="k_TNFa:TNFR1_internalisation" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_66" name="k_TNFa_internal_degradation" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_67" name="k_p38_P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_68" name="k_p65" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_69" name="k_p65_P" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_70" name="p38_active_phoshorylation_Km" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_71" name="p38_active_phosphorylation_kcat" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_72" name="p38_active_phosphorylation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p38_active_phosphorylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[TNFa:TNFR1],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_73" name="p38_basal_phosphorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_74" name="p38_dephosphorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_75" name="p65_2P_dephosphorylation" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p65_P_dephosphorylation_k],Reference=Value>*1
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_76" name="p65_MSK1_phosphorylation_kM" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_77" name="p65_MSK1_phosphrylation_kcat" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_78" name="p65_MSK1_phosphrylation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p65_MSK1_phosphrylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[MSK1_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_79" name="p65_P_MSK1_phosphrylation_kM" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p65_MSK1_phosphorylation_kM],Reference=Value>*1
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_80" name="p65_P_MSK1_phosphrylation_kcat" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p65_MSK1_phosphrylation_kcat],Reference=Value>*1
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_81" name="p65_P_MSK1_phosphrylation_vmax" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p65_P_MSK1_phosphrylation_kcat],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[MSK1_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_82" name="p65_P_dephosphorylation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_83" name="p65_degradation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_84" name="p65_nuclear_export_k" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[p65_nuclear_import_k],Reference=Value>*0.02
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_85" name="p65_nuclear_import_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_86" name="p65_translation_k" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_87" name="scaled_IkBa" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_IkBa],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_88" name="scaled_IkBa_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_IkBa_P],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa_P],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_89" name="scaled_IkBa_mRNA" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_IkBa_mRNA],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_IkBa_mRNA],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_90" name="scaled_JNK_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_JNK_P],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_JNK_P],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_91" name="scaled_MSK_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_MSK_P],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_MSK_P],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_92" name="scaled_p38_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_p38_P],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_p38_P],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_93" name="scaled_p65" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_p65],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_p65],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_94" name="scaled_p65_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Values[k_p65_P],Reference=Value>*&lt;CN=Root,Model=beuke1,Vector=Values[unscaled_p65_P],Reference=Value>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_95" name="unscaled_IkBa" simulationType="assignment" addNoise="false">
        <Expression>
          (&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65-IkBa],Reference=Concentration>)*&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Reference=Volume>+(&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa_p],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65-IkBa],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa],Reference=Concentration>)*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_96" name="unscaled_IkBa_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa_p],Reference=Concentration>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_97" name="unscaled_IkBa_mRNA" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[IkBa_mRNA],Reference=Concentration>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>+&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Reference=Volume>*&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[IkBa_mRNA],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_98" name="unscaled_JNK_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[JNK_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_99" name="unscaled_MSK_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Reference=Volume>*&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[MSK1_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_100" name="unscaled_p38_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p38_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_101" name="unscaled_p65" simulationType="assignment" addNoise="false">
        <Expression>
          (&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65_P],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65-IkBa],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Concentration>)*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>+&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Reference=Volume>*(&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65_P],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65-IkBa],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65_2P],Reference=Concentration>)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_102" name="unscaled_p65_P" simulationType="assignment" addNoise="false">
        <Expression>
          &lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Reference=Volume>*&lt;CN=Root,Model=beuke1,Vector=Compartments[nucleus],Vector=Metabolites[p65_P],Reference=Concentration>+&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Reference=Volume>*&lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65_P],Reference=Concentration>
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_103" name="min" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_104" name="max" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_105" name="amp" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_105">
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
      <ModelValue key="ModelValue_106" name="time1" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_107" name="period" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_108" name="avg" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_109" name="int" simulationType="ode" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_109">
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
      <ModelValue key="ModelValue_110" name="sign" simulationType="fixed" addNoise="false">
      </ModelValue>
      <ModelValue key="ModelValue_111" name="counter" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_111">
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
      <Reaction key="Reaction_0" name="Complex_association_c" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5144" name="k1" value="0.0380804"/>
          <Constant key="Parameter_5146" name="k2" value="0.000114241"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_14"/>
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="Complex_degradation_IkBa_c" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5147" name="k1" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="Complex_degradation_IkBa_n" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5141" name="k1" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="Complex_degradation_p65_c" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5143" name="k1" value="1.59425e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_83"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="Complex_degradation_p65_n" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5142" name="k1" value="1.59425e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_83"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="Complex_nuclear_shuttle" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5145" name="k1" value="0.0001"/>
          <Constant key="Parameter_5148" name="k2" value="0.002"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="IKK_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_2" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_5139" name="IKKb_active_phosphorylation_kA" value="0.225847"/>
          <Constant key="Parameter_5137" name="IKKb_active_phosphorylation_kM" value="5.99993"/>
          <Constant key="Parameter_5136" name="IKKb_active_phosphorylation_vmax" value="214.511"/>
        </ListOfConstants>
        <KineticLaw function="Function_40" unitType="ConcentrationPerTime" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_263">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_261">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_250">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="IkBa_degradation_c" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5140" name="k1" value="9.79808e-06"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="IkBa_degradation_n" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5138" name="k1" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="IkBa_mRNA_degradation_c" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5113" name="k1" value="4.9291e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="IkBa_mRNA_degradation_n" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5111" name="k1" value="5e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="IkBa_mRNA_transport" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5110" name="k1" value="0.0001"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="IkBa_nuclear_shuttle" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5114" name="k1" value="0.005"/>
          <Constant key="Parameter_5112" name="k2" value="0.0025"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="IkBa_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5116" name="IkBa_phosphorylation_kM" value="0.117842"/>
          <Constant key="Parameter_5131" name="IkBa_phosphorylation_vmax" value="0.000221972"/>
        </ListOfConstants>
        <KineticLaw function="Function_41" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="ModelValue_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_267">
              <SourceParameter reference="ModelValue_24"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="IkBa_transcription_elongation_1" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5119" name="k1" value="7.9497e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="IkBa_transcription_elongation_2" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5133" name="k1" value="7.9497e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="IkBa_translation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5134" name="IkBa_translation_Km" value="3.69291"/>
          <Constant key="Parameter_5128" name="IkBa_translation_vmax" value="0.00120941"/>
        </ListOfConstants>
        <KineticLaw function="Function_42" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="ModelValue_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="ModelValue_31"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="JNK_active_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5115" name="JNK_active_phoshorylation_Km" value="0.00163613"/>
          <Constant key="Parameter_5123" name="JNK_active_phosphorylation_vmax" value="0"/>
        </ListOfConstants>
        <KineticLaw function="Function_43" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_272">
              <SourceParameter reference="ModelValue_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_271">
              <SourceParameter reference="ModelValue_34"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="JNK_basal_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5130" name="k1" value="2.59046e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="JNK_dephosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5117" name="k1" value="0.000710823"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="LPS_LSEC_degradation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5129" name="k1" value="0.000221889"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[EL]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="LPS_MC_degradation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5122" name="k1" value="0.000115242"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[EL]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="MSK1_activation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5126" name="MSK1_activation_kM" value="0.332175"/>
          <Constant key="Parameter_5121" name="MSK1_activation_vmax" value="0.000293323"/>
        </ListOfConstants>
        <KineticLaw function="Function_44" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_276">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="ModelValue_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="ModelValue_40"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="MSK1_deactivation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5125" name="k1" value="0.01"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="TNFR1_shuttle" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5124" name="k1" value="0.0004"/>
          <Constant key="Parameter_5127" name="k2" value="1.8e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_61"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="TNFa:TNFR1_association" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5132" name="k1" value="16.833"/>
          <Constant key="Parameter_5118" name="k2" value="0.000319827"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[EL]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_3"/>
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="TNFa:TNFR1_internalisation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5120" name="k1" value="0.000924"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="TNFa degradation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5135" name="k1" value="0.000171417"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[EL]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_53"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="TNFa_internal_degradation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5149" name="k1" value="6.14429e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="basal_IKKb_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5150" name="k1" value="8.60727e-08"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="p38_active_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5156" name="p38_active_phoshorylation_Km" value="2.56473"/>
          <Constant key="Parameter_5155" name="p38_active_phosphorylation_vmax" value="0"/>
        </ListOfConstants>
        <KineticLaw function="Function_45" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_279">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="ModelValue_70"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="p38_basal_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5157" name="k1" value="0.00025146"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_32" name="p38_dephosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5152" name="k1" value="0.000531555"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_33" name="p65_2P_degradation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5151" name="k1" value="1.59425e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_83"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_34" name="p65_2P_dephosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5154" name="k1" value="0.000892996"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_75"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="p65_P_degradation_c" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5153" name="k1" value="1.59425e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_83"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_36" name="p65_P_degradation_n" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5158" name="k1" value="1.59425e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_83"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_37" name="p65_P_dephosphorylation_c" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5162" name="k1" value="0.000892996"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_82"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_38" name="p65_P_dephosphorylation_n" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5160" name="k1" value="0.000892996"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_82"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_39" name="p65_P_phosphorylation_MSK1" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_5159" name="p65_P_MSK1_phosphrylation_kM" value="0.843653"/>
          <Constant key="Parameter_5163" name="p65_P_MSK1_phosphrylation_vmax" value="0.00102741"/>
        </ListOfConstants>
        <KineticLaw function="Function_46" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="ModelValue_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_281">
              <SourceParameter reference="ModelValue_81"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_40" name="p65_nuclear_shuttle" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5161" name="k1" value="0.0005"/>
          <Constant key="Parameter_5165" name="k2" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_85"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_84"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_41" name="p65_phosphorylation_MSK1" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_5167" name="p65_MSK1_phosphorylation_kM" value="0.843653"/>
          <Constant key="Parameter_5168" name="p65_MSK1_phosphrylation_vmax" value="0.00102741"/>
        </ListOfConstants>
        <KineticLaw function="Function_47" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_285">
              <SourceParameter reference="ModelValue_76"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="ModelValue_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_283">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_42" name="p65_translation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5164" name="k1" value="1.75863e-06"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_86"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_43" name="IkBa_transcription_initiation" reversible="false" fast="false" addNoise="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_9" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_11" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_5166" name="IkBa_transcription_initiation_kbasal" value="1e-06"/>
          <Constant key="Parameter_5171" name="IkBa_transcription_kA2_p65_P" value="0.0001"/>
          <Constant key="Parameter_5172" name="IkBa_transcription_kA3_p65_2P" value="0.0001"/>
          <Constant key="Parameter_5173" name="IkBa_transcription_kA_p65" value="0.232624"/>
        </ListOfConstants>
        <KineticLaw function="Function_48" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_288">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_287">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_286">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_289">
              <SourceParameter reference="ModelValue_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_290">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_291">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_292">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_44" name="IkBa_p_active_degradation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfConstants>
          <Constant key="Parameter_5169" name="k1" value="0.00374704"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_45" name="Complex_phosphorylation" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5170" name="IkBa_p65_phosphorylation_kM" value="0.599893"/>
          <Constant key="Parameter_5174" name="IkBa_p65_phosphorylation_vmax" value="0.000221972"/>
        </ListOfConstants>
        <KineticLaw function="Function_49" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_299">
              <SourceParameter reference="ModelValue_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_298">
              <SourceParameter reference="ModelValue_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_297">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_46" name="dephosphorylation IKK" reversible="false" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5176" name="k1" value="0.00212692"/>
        </ListOfConstants>
        <KineticLaw function="Function_13" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_47" name="Complex_association_n" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5175" name="k1" value="0.0380804"/>
          <Constant key="Parameter_5177" name="k2" value="0.000114241"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default" scalingCompartment="CN=Root,Model=beuke1,Vector=Compartments[nucleus]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_12"/>
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_48" name="p65_P_nuclear_shuttle" reversible="true" fast="false" addNoise="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5178" name="k1" value="0.0005"/>
          <Constant key="Parameter_5179" name="k2" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_14" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="ModelValue_85"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="ModelValue_84"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="Metabolite_13"/>
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
          <Assignment targetKey="ModelValue_103">
            <Expression>
              &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Concentration>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_110">
            <Expression>
              -&lt;CN=Root,Model=beuke1,Vector=Values[sign],Reference=Value>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_111">
            <Expression>
              &lt;CN=Root,Model=beuke1,Vector=Values[counter],Reference=Value>+1
            </Expression>
          </Assignment>
        </ListOfAssignments>
      </Event>
      <Event key="Event_1" name="max" fireAtInitialTime="0" persistentTrigger="0">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Event_1">
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
          <Assignment targetKey="ModelValue_104">
            <Expression>
              &lt;CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65],Reference=Concentration>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_106">
            <Expression>
              &lt;CN=Root,Model=beuke1,Reference=Time>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_107">
            <Expression>
              &lt;CN=Root,Model=beuke1,Reference=Time>-&lt;CN=Root,Model=beuke1,Vector=Values[time1],Reference=Value>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_108">
            <Expression>
              &lt;CN=Root,Model=beuke1,Vector=Values[int],Reference=Value>/&lt;CN=Root,Model=beuke1,Vector=Values[period],Reference=Value>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_109">
            <Expression>
              0
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_110">
            <Expression>
              -&lt;CN=Root,Model=beuke1,Vector=Values[sign],Reference=Value>
            </Expression>
          </Assignment>
          <Assignment targetKey="ModelValue_111">
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
      <StateTemplateVariable objectReference="ModelValue_109"/>
      <StateTemplateVariable objectReference="Metabolite_11"/>
      <StateTemplateVariable objectReference="Metabolite_14"/>
      <StateTemplateVariable objectReference="Metabolite_22"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_26"/>
      <StateTemplateVariable objectReference="Metabolite_12"/>
      <StateTemplateVariable objectReference="Metabolite_27"/>
      <StateTemplateVariable objectReference="Metabolite_4"/>
      <StateTemplateVariable objectReference="Metabolite_16"/>
      <StateTemplateVariable objectReference="Metabolite_20"/>
      <StateTemplateVariable objectReference="Metabolite_24"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_28"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_0"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_10"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Metabolite_6"/>
      <StateTemplateVariable objectReference="Metabolite_2"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="Metabolite_18"/>
      <StateTemplateVariable objectReference="Metabolite_8"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="ModelValue_12"/>
      <StateTemplateVariable objectReference="ModelValue_15"/>
      <StateTemplateVariable objectReference="ModelValue_20"/>
      <StateTemplateVariable objectReference="ModelValue_23"/>
      <StateTemplateVariable objectReference="ModelValue_24"/>
      <StateTemplateVariable objectReference="ModelValue_34"/>
      <StateTemplateVariable objectReference="ModelValue_40"/>
      <StateTemplateVariable objectReference="ModelValue_64"/>
      <StateTemplateVariable objectReference="ModelValue_72"/>
      <StateTemplateVariable objectReference="ModelValue_75"/>
      <StateTemplateVariable objectReference="ModelValue_78"/>
      <StateTemplateVariable objectReference="ModelValue_79"/>
      <StateTemplateVariable objectReference="ModelValue_80"/>
      <StateTemplateVariable objectReference="ModelValue_81"/>
      <StateTemplateVariable objectReference="ModelValue_84"/>
      <StateTemplateVariable objectReference="ModelValue_87"/>
      <StateTemplateVariable objectReference="ModelValue_88"/>
      <StateTemplateVariable objectReference="ModelValue_89"/>
      <StateTemplateVariable objectReference="ModelValue_90"/>
      <StateTemplateVariable objectReference="ModelValue_91"/>
      <StateTemplateVariable objectReference="ModelValue_92"/>
      <StateTemplateVariable objectReference="ModelValue_93"/>
      <StateTemplateVariable objectReference="ModelValue_94"/>
      <StateTemplateVariable objectReference="ModelValue_95"/>
      <StateTemplateVariable objectReference="ModelValue_96"/>
      <StateTemplateVariable objectReference="ModelValue_97"/>
      <StateTemplateVariable objectReference="ModelValue_98"/>
      <StateTemplateVariable objectReference="ModelValue_99"/>
      <StateTemplateVariable objectReference="ModelValue_100"/>
      <StateTemplateVariable objectReference="ModelValue_101"/>
      <StateTemplateVariable objectReference="ModelValue_102"/>
      <StateTemplateVariable objectReference="ModelValue_105"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="Compartment_0"/>
      <StateTemplateVariable objectReference="Compartment_1"/>
      <StateTemplateVariable objectReference="Compartment_2"/>
      <StateTemplateVariable objectReference="ModelValue_0"/>
      <StateTemplateVariable objectReference="ModelValue_1"/>
      <StateTemplateVariable objectReference="ModelValue_2"/>
      <StateTemplateVariable objectReference="ModelValue_3"/>
      <StateTemplateVariable objectReference="ModelValue_4"/>
      <StateTemplateVariable objectReference="ModelValue_5"/>
      <StateTemplateVariable objectReference="ModelValue_6"/>
      <StateTemplateVariable objectReference="ModelValue_7"/>
      <StateTemplateVariable objectReference="ModelValue_8"/>
      <StateTemplateVariable objectReference="ModelValue_9"/>
      <StateTemplateVariable objectReference="ModelValue_10"/>
      <StateTemplateVariable objectReference="ModelValue_11"/>
      <StateTemplateVariable objectReference="ModelValue_13"/>
      <StateTemplateVariable objectReference="ModelValue_14"/>
      <StateTemplateVariable objectReference="ModelValue_16"/>
      <StateTemplateVariable objectReference="ModelValue_17"/>
      <StateTemplateVariable objectReference="ModelValue_18"/>
      <StateTemplateVariable objectReference="ModelValue_19"/>
      <StateTemplateVariable objectReference="ModelValue_21"/>
      <StateTemplateVariable objectReference="ModelValue_22"/>
      <StateTemplateVariable objectReference="ModelValue_25"/>
      <StateTemplateVariable objectReference="ModelValue_26"/>
      <StateTemplateVariable objectReference="ModelValue_27"/>
      <StateTemplateVariable objectReference="ModelValue_28"/>
      <StateTemplateVariable objectReference="ModelValue_29"/>
      <StateTemplateVariable objectReference="ModelValue_30"/>
      <StateTemplateVariable objectReference="ModelValue_31"/>
      <StateTemplateVariable objectReference="ModelValue_32"/>
      <StateTemplateVariable objectReference="ModelValue_33"/>
      <StateTemplateVariable objectReference="ModelValue_35"/>
      <StateTemplateVariable objectReference="ModelValue_36"/>
      <StateTemplateVariable objectReference="ModelValue_37"/>
      <StateTemplateVariable objectReference="ModelValue_38"/>
      <StateTemplateVariable objectReference="ModelValue_39"/>
      <StateTemplateVariable objectReference="ModelValue_41"/>
      <StateTemplateVariable objectReference="ModelValue_42"/>
      <StateTemplateVariable objectReference="ModelValue_43"/>
      <StateTemplateVariable objectReference="ModelValue_44"/>
      <StateTemplateVariable objectReference="ModelValue_45"/>
      <StateTemplateVariable objectReference="ModelValue_46"/>
      <StateTemplateVariable objectReference="ModelValue_47"/>
      <StateTemplateVariable objectReference="ModelValue_48"/>
      <StateTemplateVariable objectReference="ModelValue_49"/>
      <StateTemplateVariable objectReference="ModelValue_50"/>
      <StateTemplateVariable objectReference="ModelValue_51"/>
      <StateTemplateVariable objectReference="ModelValue_52"/>
      <StateTemplateVariable objectReference="ModelValue_53"/>
      <StateTemplateVariable objectReference="ModelValue_54"/>
      <StateTemplateVariable objectReference="ModelValue_55"/>
      <StateTemplateVariable objectReference="ModelValue_56"/>
      <StateTemplateVariable objectReference="ModelValue_57"/>
      <StateTemplateVariable objectReference="ModelValue_58"/>
      <StateTemplateVariable objectReference="ModelValue_59"/>
      <StateTemplateVariable objectReference="ModelValue_60"/>
      <StateTemplateVariable objectReference="ModelValue_61"/>
      <StateTemplateVariable objectReference="ModelValue_62"/>
      <StateTemplateVariable objectReference="ModelValue_63"/>
      <StateTemplateVariable objectReference="ModelValue_65"/>
      <StateTemplateVariable objectReference="ModelValue_66"/>
      <StateTemplateVariable objectReference="ModelValue_67"/>
      <StateTemplateVariable objectReference="ModelValue_68"/>
      <StateTemplateVariable objectReference="ModelValue_69"/>
      <StateTemplateVariable objectReference="ModelValue_70"/>
      <StateTemplateVariable objectReference="ModelValue_71"/>
      <StateTemplateVariable objectReference="ModelValue_73"/>
      <StateTemplateVariable objectReference="ModelValue_74"/>
      <StateTemplateVariable objectReference="ModelValue_76"/>
      <StateTemplateVariable objectReference="ModelValue_77"/>
      <StateTemplateVariable objectReference="ModelValue_82"/>
      <StateTemplateVariable objectReference="ModelValue_83"/>
      <StateTemplateVariable objectReference="ModelValue_85"/>
      <StateTemplateVariable objectReference="ModelValue_86"/>
      <StateTemplateVariable objectReference="ModelValue_103"/>
      <StateTemplateVariable objectReference="ModelValue_104"/>
      <StateTemplateVariable objectReference="ModelValue_106"/>
      <StateTemplateVariable objectReference="ModelValue_107"/>
      <StateTemplateVariable objectReference="ModelValue_108"/>
      <StateTemplateVariable objectReference="ModelValue_110"/>
      <StateTemplateVariable objectReference="ModelValue_111"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 7131.4437299996334 3611387.4722043518 2318.7564433152638 83411.493122878295 348205.76605032221 444478.39400965557 27112.892084477469 16.741821099107149 7553510.5629981197 5314621.6602560114 2348541.369331039 102415.9970892102 505973.20938342536 1915.894621127193 0 7798673.6180500006 926214.74297503615 7212745.4386496814 428562.47568196338 10257237.8075299 926214.74297503615 0 93.928768960989473 275273.76400187978 432.74067697274342 13824.709350325529 2514162.666743997 0.0025000000000000001 0.0001142412732544542 0.00022197169318651728 18.500918641635661 0.00022197169318651728 0 0.0002933226422510503 0.00031982700000000001 0 0.00089299602995035509 0.0010274126244695619 0.84365297237173797 0.035803860144060298 0.0010274126244695619 1.0000000000000001e-05 1.285674999999997 0.49124019999999791 0.3644160000000003 0.68185023999999872 0.65134631200000026 0.82302954400000106 1.6984982995744289e-07 0.55988479999999918 8.8649644985023138e-06 8.4018813742249228e-07 1.7032568987969644e-05 4.5710276111230481e-07 2.2956466042167914e-08 4.1748646153082307e-06 1.6591419781269655e-06 1.8353002812203092e-07 0 917.49835381634625 7828784.3269999996 2.5900000000000002e-06 7.9999999999999996e-07 1.2999999999999999e-05 0.22584699999999999 5.9999253986099763 214.511 8.6072734027274997e-08 0.002126924084237061 1.0000000000000001e-05 1.00000000002221e-05 9.7980800000000006e-06 1.0000000000000001e-05 4.9291e-05 5.0000000000000002e-05 0.0001 0.0050000000000000001 0.038080424418151397 0.000100000000000222 0.0019999999999997802 0.59989342964577941 18.500918641635661 0.00374704364447229 0.117842 7.9497024021163017e-05 9.9999999999999995e-07 0.000100000000000222 0.000100000000000222 0.23262432287335619 3.6929099999999999 0.00120941 0.0016361306255064201 11501.848605491499 2.5904620308721599e-05 0.00071082263811762803 0.000221888641398861 0.000115242287512479 0.332175 0.0099999999999997799 0.00091336958216119905 1.0000000002220399e-06 1.0937545446161601 0 1.22913885610405e-05 2.1819503787823699e-05 1.0000000002220399e-06 0.83406985346583096 0 5.97504797065566e-06 2.1894167810831798e-06 0.000171416922199217 0.58439602675956803 0.050715716095883802 145028.78158363799 584678.80956640502 21395.245793948801 1491678.2351977001 28373108.944711499 1.8e-05 0.00040000000000000002 16.832999999999998 0.00092400000000000002 6.1442899999999994e-05 197139.21763645901 0.102372088824604 3050644.1138216699 2.5647334845410801 549341.56606688304 0.00025145997620859502 0.00053155456244858516 0.84365297237173797 0.035803860144060298 0.00089299602995035509 1.5942540684736069e-05 0.00050000000000000001 1.758629979014617e-06 0 0 0 0 0 9.9999999999999995e-08 0 
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
      <Report reference="Report_18" target="EventTest30.1.txt" append="0" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="1000"/>
        <Parameter name="StepSize" type="float" value="1000"/>
        <Parameter name="Duration" type="float" value="1000000"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="0"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="1"/>
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
      <Report reference="Report_4" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_3" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_2" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_1" target="" append="1" confirmOverwrite="1"/>
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
    <Report key="Report_18" name="Time, Concentrations, Volumes, and Global Quantity Values" taskType="timeCourse" separator="&#x09;" precision="6">
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
    <PlotSpecification name="plot_2" type="Plot2D" active="0" taskTypes="">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="[IKKb]|Time" type="Curve2D">
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
        <PlotItem name="[IKKb_p]|Time" type="Curve2D">
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
        <PlotItem name="[IkBa_mRNA{cytoplasm}]|Time" type="Curve2D">
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
        <PlotItem name="[IkBa_mRNA{nucleus}]|Time" type="Curve2D">
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
        <PlotItem name="[IkBa_p]|Time" type="Curve2D">
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
        <PlotItem name="[IkBa_pre_mRNA_1]|Time" type="Curve2D">
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
        <PlotItem name="[IkBa_pre_mRNA_2]|Time" type="Curve2D">
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
        <PlotItem name="[IkBa{cytoplasm}]|Time" type="Curve2D">
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
        <PlotItem name="[IkBa{nucleus}]|Time" type="Curve2D">
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
        <PlotItem name="[JNK]|Time" type="Curve2D">
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
        <PlotItem name="[JNK_P]|Time" type="Curve2D">
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
        <PlotItem name="[LPS]|Time" type="Curve2D">
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
        <PlotItem name="[MSK1]|Time" type="Curve2D">
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
        <PlotItem name="[MSK1_P]|Time" type="Curve2D">
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
        <PlotItem name="[TNFR1{EL}]|Time" type="Curve2D">
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
        <PlotItem name="[TNFR1{cytoplasm}]|Time" type="Curve2D">
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
        <PlotItem name="[TNFa:TNFR1{EL}]|Time" type="Curve2D">
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
        <PlotItem name="[TNFa:TNFR1{cytoplasm}]|Time" type="Curve2D">
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
        <PlotItem name="[TNFa]|Time" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[EL],Vector=Metabolites[TNFa],Reference=Concentration"/>
          </ListOfChannels>
        </PlotItem>
        <PlotItem name="[p38]|Time" type="Curve2D">
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
        <PlotItem name="[p38_P]|Time" type="Curve2D">
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
        <PlotItem name="[p65-IkBa{cytoplasm}]|Time" type="Curve2D">
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
        <PlotItem name="[p65-IkBa{nucleus}]|Time" type="Curve2D">
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
        <PlotItem name="[p65_2P]|Time" type="Curve2D">
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
        <PlotItem name="[p65_P{cytoplasm}]|Time" type="Curve2D">
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
        <PlotItem name="[p65_P{nucleus}]|Time" type="Curve2D">
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
        <PlotItem name="[p65_mRNA]|Time" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=beuke1,Reference=Time"/>
            <ChannelSpec cn="CN=Root,Model=beuke1,Vector=Compartments[cytoplasm],Vector=Metabolites[p65_mRNA],Reference=Concentration"/>
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
        <PlotItem name="[p65{nucleus}]|Time" type="Curve2D">
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
  </ListOfPlots>
  <GUI>
  </GUI>
  <SBMLReference file="beuke1.xml">
    <SBMLMap SBMLid="Complex_association_c" COPASIkey="Reaction_0"/>
    <SBMLMap SBMLid="Complex_degradation_IkBa_c" COPASIkey="Reaction_1"/>
    <SBMLMap SBMLid="Complex_degradation_IkBa_n" COPASIkey="Reaction_2"/>
    <SBMLMap SBMLid="Complex_degradation_p65_c" COPASIkey="Reaction_3"/>
    <SBMLMap SBMLid="Complex_degradation_p65_n" COPASIkey="Reaction_4"/>
    <SBMLMap SBMLid="Complex_nuclear_shuttle" COPASIkey="Reaction_5"/>
    <SBMLMap SBMLid="EL" COPASIkey="Compartment_0"/>
    <SBMLMap SBMLid="IKK_phosphorylation" COPASIkey="Reaction_6"/>
    <SBMLMap SBMLid="IKKb_active_phosphorylation_kA" COPASIkey="ModelValue_0"/>
    <SBMLMap SBMLid="IKKb_active_phosphorylation_kM" COPASIkey="ModelValue_1"/>
    <SBMLMap SBMLid="IKKb_active_phosphorylation_vmax" COPASIkey="ModelValue_2"/>
    <SBMLMap SBMLid="IKKb_basal_phosphoylation_k" COPASIkey="ModelValue_3"/>
    <SBMLMap SBMLid="IKKb_dephopshorylation_k" COPASIkey="ModelValue_4"/>
    <SBMLMap SBMLid="IkBa_cytoplasm" COPASIkey="Metabolite_14"/>
    <SBMLMap SBMLid="IkBa_deg_complex_cyt_k" COPASIkey="ModelValue_5"/>
    <SBMLMap SBMLid="IkBa_deg_complex_nuc_k" COPASIkey="ModelValue_6"/>
    <SBMLMap SBMLid="IkBa_deg_cyt_k" COPASIkey="ModelValue_7"/>
    <SBMLMap SBMLid="IkBa_deg_nuc_k" COPASIkey="ModelValue_8"/>
    <SBMLMap SBMLid="IkBa_degradation_c" COPASIkey="Reaction_7"/>
    <SBMLMap SBMLid="IkBa_degradation_n" COPASIkey="Reaction_8"/>
    <SBMLMap SBMLid="IkBa_mRNA_cytoplasm" COPASIkey="Metabolite_15"/>
    <SBMLMap SBMLid="IkBa_mRNA_deg_cyt_k" COPASIkey="ModelValue_9"/>
    <SBMLMap SBMLid="IkBa_mRNA_deg_nuc_k" COPASIkey="ModelValue_10"/>
    <SBMLMap SBMLid="IkBa_mRNA_degradation_c" COPASIkey="Reaction_9"/>
    <SBMLMap SBMLid="IkBa_mRNA_degradation_n" COPASIkey="Reaction_10"/>
    <SBMLMap SBMLid="IkBa_mRNA_nucleus" COPASIkey="Metabolite_4"/>
    <SBMLMap SBMLid="IkBa_mRNA_transport" COPASIkey="Reaction_11"/>
    <SBMLMap SBMLid="IkBa_mRNA_transport_k" COPASIkey="ModelValue_11"/>
    <SBMLMap SBMLid="IkBa_nuclear_export_k" COPASIkey="ModelValue_12"/>
    <SBMLMap SBMLid="IkBa_nuclear_import_k" COPASIkey="ModelValue_13"/>
    <SBMLMap SBMLid="IkBa_nuclear_shuttle" COPASIkey="Reaction_12"/>
    <SBMLMap SBMLid="IkBa_p65_association_k" COPASIkey="ModelValue_14"/>
    <SBMLMap SBMLid="IkBa_p65_dissociation_k" COPASIkey="ModelValue_15"/>
    <SBMLMap SBMLid="IkBa_p65_nuclear_export_k" COPASIkey="ModelValue_16"/>
    <SBMLMap SBMLid="IkBa_p65_nuclear_import_k" COPASIkey="ModelValue_17"/>
    <SBMLMap SBMLid="IkBa_p65_phosphorylation_kM" COPASIkey="ModelValue_18"/>
    <SBMLMap SBMLid="IkBa_p65_phosphorylation_kcat" COPASIkey="ModelValue_19"/>
    <SBMLMap SBMLid="IkBa_p65_phosphorylation_vmax" COPASIkey="ModelValue_20"/>
    <SBMLMap SBMLid="IkBa_p_active_degradation_k" COPASIkey="ModelValue_21"/>
    <SBMLMap SBMLid="IkBa_phosphorylation" COPASIkey="Reaction_13"/>
    <SBMLMap SBMLid="IkBa_phosphorylation_kM" COPASIkey="ModelValue_22"/>
    <SBMLMap SBMLid="IkBa_phosphorylation_kcat" COPASIkey="ModelValue_23"/>
    <SBMLMap SBMLid="IkBa_phosphorylation_vmax" COPASIkey="ModelValue_24"/>
    <SBMLMap SBMLid="IkBa_pre_mRNA_1" COPASIkey="Metabolite_5"/>
    <SBMLMap SBMLid="IkBa_pre_mRNA_2" COPASIkey="Metabolite_6"/>
    <SBMLMap SBMLid="IkBa_transcription_elongation_1" COPASIkey="Reaction_14"/>
    <SBMLMap SBMLid="IkBa_transcription_elongation_2" COPASIkey="Reaction_15"/>
    <SBMLMap SBMLid="IkBa_transcription_elongation_kbasal" COPASIkey="ModelValue_25"/>
    <SBMLMap SBMLid="IkBa_transcription_initiation_kbasal" COPASIkey="ModelValue_26"/>
    <SBMLMap SBMLid="IkBa_transcription_kA2_p65_P" COPASIkey="ModelValue_27"/>
    <SBMLMap SBMLid="IkBa_transcription_kA3_p65_2P" COPASIkey="ModelValue_28"/>
    <SBMLMap SBMLid="IkBa_transcription_kA_p65" COPASIkey="ModelValue_29"/>
    <SBMLMap SBMLid="IkBa_translation" COPASIkey="Reaction_16"/>
    <SBMLMap SBMLid="IkBa_translation_Km" COPASIkey="ModelValue_30"/>
    <SBMLMap SBMLid="IkBa_translation_vmax" COPASIkey="ModelValue_31"/>
    <SBMLMap SBMLid="JNK" COPASIkey="Metabolite_16"/>
    <SBMLMap SBMLid="JNK_P" COPASIkey="Metabolite_17"/>
    <SBMLMap SBMLid="JNK_active_phoshorylation_Km" COPASIkey="ModelValue_32"/>
    <SBMLMap SBMLid="JNK_active_phosphorylation" COPASIkey="Reaction_17"/>
    <SBMLMap SBMLid="JNK_active_phosphorylation_kcat" COPASIkey="ModelValue_33"/>
    <SBMLMap SBMLid="JNK_active_phosphorylation_vmax" COPASIkey="ModelValue_34"/>
    <SBMLMap SBMLid="JNK_basal_phosphorylation" COPASIkey="Reaction_18"/>
    <SBMLMap SBMLid="JNK_basal_phosphorylation_k" COPASIkey="ModelValue_35"/>
    <SBMLMap SBMLid="JNK_dephosphorylation" COPASIkey="Reaction_19"/>
    <SBMLMap SBMLid="JNK_dephosphorylation_k" COPASIkey="ModelValue_36"/>
    <SBMLMap SBMLid="LPS" COPASIkey="Metabolite_0"/>
    <SBMLMap SBMLid="LPS_LSEC_degradation" COPASIkey="Reaction_20"/>
    <SBMLMap SBMLid="LPS_LSEC_degradation_k" COPASIkey="ModelValue_37"/>
    <SBMLMap SBMLid="LPS_MC_degradation" COPASIkey="Reaction_21"/>
    <SBMLMap SBMLid="LPS_MC_degradation_k" COPASIkey="ModelValue_38"/>
    <SBMLMap SBMLid="MSK1" COPASIkey="Metabolite_7"/>
    <SBMLMap SBMLid="MSK1_P" COPASIkey="Metabolite_8"/>
    <SBMLMap SBMLid="MSK1_activation" COPASIkey="Reaction_22"/>
    <SBMLMap SBMLid="MSK1_activation_kM" COPASIkey="ModelValue_39"/>
    <SBMLMap SBMLid="MSK1_activation_vmax" COPASIkey="ModelValue_40"/>
    <SBMLMap SBMLid="MSK1_deactivation" COPASIkey="Reaction_23"/>
    <SBMLMap SBMLid="MSK1_dephosphorylation_k" COPASIkey="ModelValue_41"/>
    <SBMLMap SBMLid="MSK1_phosphorylation_kcat" COPASIkey="ModelValue_42"/>
    <SBMLMap SBMLid="TNFR1_EL" COPASIkey="Metabolite_1"/>
    <SBMLMap SBMLid="TNFR1_cytoplasm" COPASIkey="Metabolite_18"/>
    <SBMLMap SBMLid="TNFR1_shuttle" COPASIkey="Reaction_24"/>
    <SBMLMap SBMLid="TNFa_LSEC_transcription_elongation_k" COPASIkey="ModelValue_43"/>
    <SBMLMap SBMLid="TNFa_LSEC_transcription_initiation_kA_LPS" COPASIkey="ModelValue_44"/>
    <SBMLMap SBMLid="TNFa_LSEC_transcription_initiation_kbasal" COPASIkey="ModelValue_45"/>
    <SBMLMap SBMLid="TNFa_LSEC_transcription_initiation_vA_LPS" COPASIkey="ModelValue_46"/>
    <SBMLMap SBMLid="TNFa_LSEC_translation_k" COPASIkey="ModelValue_47"/>
    <SBMLMap SBMLid="TNFa_MC_transcription_elongation_k" COPASIkey="ModelValue_48"/>
    <SBMLMap SBMLid="TNFa_MC_transcription_initiation_kA_LPS" COPASIkey="ModelValue_49"/>
    <SBMLMap SBMLid="TNFa_MC_transcription_initiation_kbasal" COPASIkey="ModelValue_50"/>
    <SBMLMap SBMLid="TNFa_MC_transcription_initiation_vA_LPS" COPASIkey="ModelValue_51"/>
    <SBMLMap SBMLid="TNFa_MC_translation_k" COPASIkey="ModelValue_52"/>
    <SBMLMap SBMLid="TNFa_TNFR1_EL" COPASIkey="Metabolite_2"/>
    <SBMLMap SBMLid="TNFa_TNFR1_association" COPASIkey="Reaction_25"/>
    <SBMLMap SBMLid="TNFa_TNFR1_cytoplasm" COPASIkey="Metabolite_19"/>
    <SBMLMap SBMLid="TNFa_TNFR1_internalisation" COPASIkey="Reaction_26"/>
    <SBMLMap SBMLid="TNFa_degradation" COPASIkey="Reaction_27"/>
    <SBMLMap SBMLid="TNFa_degradation_k" COPASIkey="ModelValue_53"/>
    <SBMLMap SBMLid="TNFa_internal_degradation" COPASIkey="Reaction_28"/>
    <SBMLMap SBMLid="TNFa_mRNA_LSEC_degradation_k" COPASIkey="ModelValue_54"/>
    <SBMLMap SBMLid="TNFa_mRNA_MC_degradation_k" COPASIkey="ModelValue_55"/>
    <SBMLMap SBMLid="basal_IKKb_phosphorylation" COPASIkey="Reaction_29"/>
    <SBMLMap SBMLid="c1" COPASIkey="Compartment_1"/>
    <SBMLMap SBMLid="default" COPASIkey="Compartment_2"/>
    <SBMLMap SBMLid="k_IkBa" COPASIkey="ModelValue_56"/>
    <SBMLMap SBMLid="k_IkBa_P" COPASIkey="ModelValue_57"/>
    <SBMLMap SBMLid="k_IkBa_mRNA" COPASIkey="ModelValue_58"/>
    <SBMLMap SBMLid="k_JNK_P" COPASIkey="ModelValue_59"/>
    <SBMLMap SBMLid="k_MSK_P" COPASIkey="ModelValue_60"/>
    <SBMLMap SBMLid="k_TNFR1_outer_membrane2vessicle_shuttle" COPASIkey="ModelValue_61"/>
    <SBMLMap SBMLid="k_TNFR1_vessicle2outer_membrane_shuttle" COPASIkey="ModelValue_62"/>
    <SBMLMap SBMLid="k_TNFa_TNFR1_association" COPASIkey="ModelValue_63"/>
    <SBMLMap SBMLid="k_TNFa_TNFR1_dissociation" COPASIkey="ModelValue_64"/>
    <SBMLMap SBMLid="k_TNFa_TNFR1_internalisation" COPASIkey="ModelValue_65"/>
    <SBMLMap SBMLid="k_TNFa_internal_degradation" COPASIkey="ModelValue_66"/>
    <SBMLMap SBMLid="k_p38_P" COPASIkey="ModelValue_67"/>
    <SBMLMap SBMLid="k_p65" COPASIkey="ModelValue_68"/>
    <SBMLMap SBMLid="k_p65_P" COPASIkey="ModelValue_69"/>
    <SBMLMap SBMLid="p38" COPASIkey="Metabolite_20"/>
    <SBMLMap SBMLid="p38_P" COPASIkey="Metabolite_21"/>
    <SBMLMap SBMLid="p38_active_phoshorylation_Km" COPASIkey="ModelValue_70"/>
    <SBMLMap SBMLid="p38_active_phosphorylation" COPASIkey="Reaction_30"/>
    <SBMLMap SBMLid="p38_active_phosphorylation_kcat" COPASIkey="ModelValue_71"/>
    <SBMLMap SBMLid="p38_active_phosphorylation_vmax" COPASIkey="ModelValue_72"/>
    <SBMLMap SBMLid="p38_basal_phosphorylation" COPASIkey="Reaction_31"/>
    <SBMLMap SBMLid="p38_basal_phosphorylation_k" COPASIkey="ModelValue_73"/>
    <SBMLMap SBMLid="p38_dephosphorylation" COPASIkey="Reaction_32"/>
    <SBMLMap SBMLid="p38_dephosphorylation_k" COPASIkey="ModelValue_74"/>
    <SBMLMap SBMLid="p65_2P" COPASIkey="Metabolite_9"/>
    <SBMLMap SBMLid="p65_2P_degradation" COPASIkey="Reaction_33"/>
    <SBMLMap SBMLid="p65_2P_dephosphorylation" COPASIkey="ModelValue_75"/>
    <SBMLMap SBMLid="p65_2P_dephosphorylation_0" COPASIkey="Reaction_34"/>
    <SBMLMap SBMLid="p65_IkBa_nucleus" COPASIkey="Metabolite_10"/>
    <SBMLMap SBMLid="p65_MSK1_phosphorylation_kM" COPASIkey="ModelValue_76"/>
    <SBMLMap SBMLid="p65_MSK1_phosphrylation_kcat" COPASIkey="ModelValue_77"/>
    <SBMLMap SBMLid="p65_MSK1_phosphrylation_vmax" COPASIkey="ModelValue_78"/>
    <SBMLMap SBMLid="p65_P_MSK1_phosphrylation_kM" COPASIkey="ModelValue_79"/>
    <SBMLMap SBMLid="p65_P_MSK1_phosphrylation_kcat" COPASIkey="ModelValue_80"/>
    <SBMLMap SBMLid="p65_P_MSK1_phosphrylation_vmax" COPASIkey="ModelValue_81"/>
    <SBMLMap SBMLid="p65_P_degradation_c" COPASIkey="Reaction_35"/>
    <SBMLMap SBMLid="p65_P_degradation_n" COPASIkey="Reaction_36"/>
    <SBMLMap SBMLid="p65_P_dephosphorylation_c" COPASIkey="Reaction_37"/>
    <SBMLMap SBMLid="p65_P_dephosphorylation_k" COPASIkey="ModelValue_82"/>
    <SBMLMap SBMLid="p65_P_dephosphorylation_n" COPASIkey="Reaction_38"/>
    <SBMLMap SBMLid="p65_P_phosphorylation_MSK1" COPASIkey="Reaction_39"/>
    <SBMLMap SBMLid="p65_cytoplasm" COPASIkey="Metabolite_22"/>
    <SBMLMap SBMLid="p65_degradation_k" COPASIkey="ModelValue_83"/>
    <SBMLMap SBMLid="p65_mRNA" COPASIkey="Metabolite_23"/>
    <SBMLMap SBMLid="p65_nuclear_export_k" COPASIkey="ModelValue_84"/>
    <SBMLMap SBMLid="p65_nuclear_import_k" COPASIkey="ModelValue_85"/>
    <SBMLMap SBMLid="p65_nuclear_shuttle" COPASIkey="Reaction_40"/>
    <SBMLMap SBMLid="p65_nucleus" COPASIkey="Metabolite_11"/>
    <SBMLMap SBMLid="p65_phosphorylation_MSK1" COPASIkey="Reaction_41"/>
    <SBMLMap SBMLid="p65_translation" COPASIkey="Reaction_42"/>
    <SBMLMap SBMLid="p65_translation_k" COPASIkey="ModelValue_86"/>
    <SBMLMap SBMLid="re10" COPASIkey="Reaction_43"/>
    <SBMLMap SBMLid="re14" COPASIkey="Reaction_44"/>
    <SBMLMap SBMLid="re15" COPASIkey="Reaction_45"/>
    <SBMLMap SBMLid="re17" COPASIkey="Reaction_46"/>
    <SBMLMap SBMLid="re19" COPASIkey="Reaction_47"/>
    <SBMLMap SBMLid="re3" COPASIkey="Reaction_48"/>
    <SBMLMap SBMLid="s11" COPASIkey="Metabolite_12"/>
    <SBMLMap SBMLid="s14" COPASIkey="Metabolite_24"/>
    <SBMLMap SBMLid="s15" COPASIkey="Metabolite_25"/>
    <SBMLMap SBMLid="s16" COPASIkey="Metabolite_3"/>
    <SBMLMap SBMLid="s19" COPASIkey="Metabolite_26"/>
    <SBMLMap SBMLid="s3" COPASIkey="Metabolite_27"/>
    <SBMLMap SBMLid="s5" COPASIkey="Metabolite_28"/>
    <SBMLMap SBMLid="s8" COPASIkey="Metabolite_13"/>
    <SBMLMap SBMLid="scaled_IkBa" COPASIkey="ModelValue_87"/>
    <SBMLMap SBMLid="scaled_IkBa_P" COPASIkey="ModelValue_88"/>
    <SBMLMap SBMLid="scaled_IkBa_mRNA" COPASIkey="ModelValue_89"/>
    <SBMLMap SBMLid="scaled_JNK_P" COPASIkey="ModelValue_90"/>
    <SBMLMap SBMLid="scaled_MSK_P" COPASIkey="ModelValue_91"/>
    <SBMLMap SBMLid="scaled_p38_P" COPASIkey="ModelValue_92"/>
    <SBMLMap SBMLid="scaled_p65" COPASIkey="ModelValue_93"/>
    <SBMLMap SBMLid="scaled_p65_P" COPASIkey="ModelValue_94"/>
    <SBMLMap SBMLid="unscaled_IkBa" COPASIkey="ModelValue_95"/>
    <SBMLMap SBMLid="unscaled_IkBa_P" COPASIkey="ModelValue_96"/>
    <SBMLMap SBMLid="unscaled_IkBa_mRNA" COPASIkey="ModelValue_97"/>
    <SBMLMap SBMLid="unscaled_JNK_P" COPASIkey="ModelValue_98"/>
    <SBMLMap SBMLid="unscaled_MSK_P" COPASIkey="ModelValue_99"/>
    <SBMLMap SBMLid="unscaled_p38_P" COPASIkey="ModelValue_100"/>
    <SBMLMap SBMLid="unscaled_p65" COPASIkey="ModelValue_101"/>
    <SBMLMap SBMLid="unscaled_p65_P" COPASIkey="ModelValue_102"/>
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
