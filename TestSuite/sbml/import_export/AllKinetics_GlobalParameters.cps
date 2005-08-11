<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.0 Debug 13++ (http://www.copasi.org) at 2005-08-11 13:53:31 UTC -->
<COPASI xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://calvin.bioinformatics.vt.edu/copasi/schema/copasi.xsd" versionMajor="0" versionMinor="1">
  <ListOfFunctions>
    <Function key="Function_0" name="Allosteric inhibition (MWC)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate*(Ks+substrate)^(n-1)/(L*(Ks*(1+Inhibitor/Ki))^n+(Ks+substrate)^n)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_0" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_1" name="Inhibitor" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_2" name="V" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_3" name="Ks" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_4" name="n" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_5" name="L" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_6" name="Ki" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_1" name="Allosteric inhibition (empirical)" type="PreDefined" positive="true">
      <MathML>
        <Text>
          (Vf*substrate/Kms-Vr*product/Kmp)/(1+substrate/Kms+product/Kmp+(Inhibitor/Ki)^n)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_7" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_8" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_9" name="Inhibitor" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_10" name="Vf" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_11" name="Vr" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_12" name="Kms" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_13" name="Kmp" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_14" name="n" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_15" name="Ki" order="8" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_10" name="Hyperbolic modifier (irrev)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate*(1+b*Modifier/(a*Kd))/(Km*(1+Modifier/Kd)+substrate*(1+Modifier/(a*Kd)))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_51" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_52" name="Modifier" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_53" name="Km" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_54" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_55" name="Kd" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_56" name="a" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_57" name="b" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_11" name="Hyperbolic modifier (rev)" type="PreDefined" positive="true">
      <MathML>
        <Text>
          (Vf*substrate/Kms-Vr*product/Kmp)*(1+b*Modifier/(a*Kd))/(1+Modifier/Kd+(substrate/Kms+product/Kmp)*(1+Modifier/(a*Kd)))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_58" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_59" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_60" name="Modifier" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_61" name="Kms" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_62" name="Kmp" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_63" name="Vf" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_64" name="Vr" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_65" name="Kd" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_66" name="a" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_67" name="b" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_12" name="Iso Uni Uni" type="PreDefined" positive="true">
      <MathML>
        <Text>
          Vf*(substrate-product/Keq)/(substrate*(1+product/Kii)+Kms*(1+product/Kmp))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_68" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_69" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_70" name="Kms" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_71" name="Kmp" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_72" name="Kii" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_73" name="Vf" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_74" name="Keq" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
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
    <Function key="Function_14" name="Mass action (reversible)" type="MassAction" positive="true">
      <MathML>
        <Text>
          k1*PRODUCT&lt;substrate_i&gt;-k2*PRODUCT&lt;product_j&gt;
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_77" name="k1" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_78" name="substrate" order="1" role="substrate" minOccurs="1" maxOccurs="unbounded"/>
        <ParameterDescription key="FunctionParameter_79" name="k2" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_80" name="product" order="3" role="product" minOccurs="1" maxOccurs="unbounded"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_15" name="Mixed activation (irrev)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate*Activator/(Kms*(Kas+Activator)+substrate*(Kac+Activator))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_81" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_82" name="Activator" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_83" name="Kms" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_84" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_85" name="Kas" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_86" name="Kac" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_16" name="Mixed activation (rev)" type="PreDefined" positive="true">
      <MathML>
        <Text>
          (Vf*substrate/Kms-Vr*product/Kmp)*Activator/(Kas+Activator+(substrate/Kms+product/Kmp)*(Kac+Activator))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_87" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_88" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_89" name="Activator" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_90" name="Kms" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_91" name="Kmp" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_92" name="Vf" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_93" name="Vr" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_94" name="Kas" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_95" name="Kac" order="8" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_17" name="Mixed inhibition (irr)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate/(Km*(1+Inhibitor/Kis)+substrate*(1+Inhibitor/Kic))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_96" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_97" name="Inhibitor" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_98" name="Km" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_99" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_100" name="Kis" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_101" name="Kic" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_18" name="Mixed inhibition (rev)" type="PreDefined" positive="true">
      <MathML>
        <Text>
          (Vf*substrate/Kms-Vr*product/Kmp)/(1+Inhibitor/Kis+(substrate/Kms+product/Kmp)*(1+Inhibitor/Kic))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_102" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_103" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_104" name="Inhibitor" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_105" name="Kms" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_106" name="Kmp" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_107" name="Vf" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_108" name="Vr" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_109" name="Kis" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_110" name="Kic" order="8" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_19" name="Noncompetitive inhibition (irr)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate/((Km+substrate)*(1+Inhibitor/Ki))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_111" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_112" name="Inhibitor" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_113" name="Km" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_114" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_115" name="Ki" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_2" name="Catalytic activation (irrev)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate*Activator/((Kms+substrate)*(Ka+Activator))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_16" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_17" name="Activator" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_18" name="Kms" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_19" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_20" name="Ka" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_20" name="Noncompetitive inhibition (rev)" type="PreDefined" positive="true">
      <MathML>
        <Text>
          (Vf*substrate/Kms-Vr*product/Kmp)/((1+substrate/Kms+product/Kmp)*(1+Inhibitor/Ki))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_116" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_117" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_118" name="Inhibitor" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_119" name="Kms" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_120" name="Kmp" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_121" name="Vf" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_122" name="Vr" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_123" name="Ki" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_21" name="Ordered Bi Bi" type="PreDefined" positive="true">
      <MathML>
        <Text>
          Vf*(substratea*substrateb-productp*productq/Keq)/(substratea*substrateb*(1+productp/Kip)+Kma*substrateb+Kmb*(substratea+Kia)+Vf/(Vr*Keq)*(Kmq*productp*(1+substratea/Kia)+productq*(Kmp*(1+Kia*substrateb/(Kma*Kmb))+productp*(1+substrateb/Kib))))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_124" name="substratea" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_125" name="substrateb" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_126" name="productp" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_127" name="productq" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_128" name="Keq" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_129" name="Vf" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_130" name="Vr" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_131" name="Kma" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_132" name="Kmb" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_133" name="Kmp" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_134" name="Kmq" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_135" name="Kia" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_136" name="Kib" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_137" name="Kip" order="13" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_22" name="Ordered Bi Uni" type="PreDefined" positive="true">
      <MathML>
        <Text>
          Vf*(substratea*substrateb-product/Keq)/(substratea*substrateb+Kma*substrateb+Kmb*substratea+Vf/(Vr*Keq)*(Kmp+product*(1+substratea/Kia)))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_138" name="substratea" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_139" name="substrateb" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_140" name="product" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_141" name="Kma" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_142" name="Kmb" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_143" name="Kmp" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_144" name="Kia" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_145" name="Keq" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_146" name="Vf" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_147" name="Vr" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_23" name="Ordered Uni Bi" type="PreDefined" positive="true">
      <MathML>
        <Text>
          Vf*(substrate-productp*productq/Keq)/(Kms+substrate*(1+productp/Kip)+Vf/(Vr*Keq)*(Kmq*productp+Kmp*productq+productp*productq))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_148" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_149" name="productp" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_150" name="productq" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_151" name="Kms" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_152" name="Kmq" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_153" name="Kmp" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_154" name="Kip" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_155" name="Keq" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_156" name="Vf" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_157" name="Vr" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_24" name="Ping Pong Bi Bi" type="PreDefined" positive="true">
      <MathML>
        <Text>
          Vf*(substratea*substrateb-productp*productq/Keq)/(substratea*substrateb*(1+productq/Kiq)+Kma*substrateb+Kmb*substratea+Vf/(Vr*Keq)*(Kmq*productp*(1+substratea/Kia)+productq*(Kmp+productp)))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_158" name="substratea" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_159" name="substrateb" order="1" role="substrate"/>
        <ParameterDescription key="FunctionParameter_160" name="productp" order="2" role="product"/>
        <ParameterDescription key="FunctionParameter_161" name="productq" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_162" name="Keq" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_163" name="Vf" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_164" name="Vr" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_165" name="Kma" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_166" name="Kmb" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_167" name="Kmp" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_168" name="Kmq" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_169" name="Kia" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_170" name="Kiq" order="12" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_25" name="Reversible Hill 1 modifier" type="PreDefined" positive="true">
      <MathML>
        <Text>
          Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/((1+(Modifier/Mhalve)^h)/(1+alpha*(Modifier/Mhalve)^h)+(substrate/Shalve+product/Phalve)^h)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_171" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_172" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_173" name="Modifier" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_174" name="Keq" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_175" name="Vf" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_176" name="Shalve" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_177" name="Phalve" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_178" name="h" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_179" name="Mhalve" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_180" name="alpha" order="9" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_26" name="Reversible Hill 2 modifiers" type="PreDefined" positive="true">
      <MathML>
        <Text>
          Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/((1+(ModifierA/MAhalve)^h+(ModifierB/MBhalve)^h)/(1+alphaA*(ModifierA/MAhalve)^h+alphaB*(ModifierB/MBhalve)^h+alphaA*alphaB*alphaAB*(ModifierA/MAhalve)^h*(ModifierB/MBhalve)^h)+(substrate/Shalve+product/Phalve)^h)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_181" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_182" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_183" name="ModifierA" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_184" name="ModifierB" order="3" role="modifier"/>
        <ParameterDescription key="FunctionParameter_185" name="Keq" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_186" name="Vf" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_187" name="Shalve" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_188" name="Phalve" order="7" role="constant"/>
        <ParameterDescription key="FunctionParameter_189" name="h" order="8" role="constant"/>
        <ParameterDescription key="FunctionParameter_190" name="MAhalve" order="9" role="constant"/>
        <ParameterDescription key="FunctionParameter_191" name="alphaA" order="10" role="constant"/>
        <ParameterDescription key="FunctionParameter_192" name="MBhalve" order="11" role="constant"/>
        <ParameterDescription key="FunctionParameter_193" name="alphaB" order="12" role="constant"/>
        <ParameterDescription key="FunctionParameter_194" name="alphaAB" order="13" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_27" name="Reversible Hill" type="PreDefined" positive="true">
      <MathML>
        <Text>
          Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/(1+(substrate/Shalve+product/Phalve)^h)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_195" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_196" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_197" name="Keq" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_198" name="Vf" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_199" name="Shalve" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_200" name="Phalve" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_201" name="h" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_28" name="Reversible Michaelis-Menten" type="PreDefined" positive="true">
      <MathML>
        <Text>
          (Vf*substrate/Kms-Vr*product/Kmp)/(1+substrate/Kms+product/Kmp)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_202" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_203" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_204" name="Kms" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_205" name="Kmp" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_206" name="Vf" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_207" name="Vr" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_29" name="Specific activation (irrev)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate*Activator/(Kms*Ka+(Kms+substrate)*Activator)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_208" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_209" name="Activator" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_210" name="Kms" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_211" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_212" name="Ka" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_3" name="Catalytic activation (rev)" type="PreDefined" positive="true">
      <MathML>
        <Text>
          (Vf*substrate/Kms-Vr*product/Kmp)*Activator/((1+substrate/Kms+product/Kmp)*(Ka+Activator))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_21" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_22" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_23" name="Activator" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_24" name="Kms" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_25" name="Kmp" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_26" name="Vf" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_27" name="Vr" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_28" name="Ka" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_30" name="Specific activation (rev)" type="PreDefined" positive="true">
      <MathML>
        <Text>
          (Vf*substrate/Kms-Vr*product/Kmp)*Activator/(Ka+(1+substrate/Kms+product/Kmp)*Activator)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_213" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_214" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_215" name="Activator" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_216" name="Kms" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_217" name="Kmp" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_218" name="Vf" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_219" name="Vr" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_220" name="Ka" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_31" name="Substrate activation (irr)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*(substrate/Ksa)^2/(1+substrate/Ksc+substrate/Ksa+(substrate/Ksa)^2)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_221" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_222" name="V" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_223" name="Ksc" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_224" name="Ksa" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_32" name="Substrate inhibition (irr)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate/(Km+substrate+Km*(substrate/Ki)^2)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_225" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_226" name="Km" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_227" name="V" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_228" name="Ki" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_33" name="Substrate inhibition (rev)" type="PreDefined" positive="true">
      <MathML>
        <Text>
          (Vf*substrate/Kms-Vr*product/Kmp)/(1+substrate/Kms+product/Kmp+(substrate/Ki)^2)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_229" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_230" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_231" name="Kms" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_232" name="Kmp" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_233" name="Vf" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_234" name="Vr" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_235" name="Ki" order="6" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_34" name="Uncompetitive inhibition (irr)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate/(Km+substrate*(1+Inhibitor/Ki))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_236" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_237" name="Inhibitor" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_238" name="Km" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_239" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_240" name="Ki" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_35" name="Uncompetitive inhibition (rev)" type="PreDefined" positive="true">
      <MathML>
        <Text>
          (Vf*substrate/Kms-Vr*product/Kmp)/(1+(substrate/Kms+product/Kmp)*(1+Inhibitor/Ki))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_241" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_242" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_243" name="Inhibitor" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_244" name="Kms" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_245" name="Kmp" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_246" name="Vf" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_247" name="Vr" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_248" name="Ki" order="7" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_36" name="Uni Uni" type="PreDefined" positive="true">
      <MathML>
        <Text>
          Vf*(substrate-product/Keq)/(substrate+Kms*(1+product/Kmp))
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_249" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_250" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_251" name="Kms" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_252" name="Kmp" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_253" name="Vf" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_254" name="Keq" order="5" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_4" name="Competitive inhibition (irr)" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate/(Km+substrate+Km*Inhibitor/Ki)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_29" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_30" name="Inhibitor" order="1" role="modifier"/>
        <ParameterDescription key="FunctionParameter_31" name="Km" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_32" name="V" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_33" name="Ki" order="4" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_5" name="Competitive inhibition (rev)" type="PreDefined" positive="true">
      <MathML>
        <Text>
          (Vf*substrate/Kms-Vr*product/Kmp)/(1+substrate/Kms+product/Kmp+Inhibitor/Ki)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_34" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_35" name="product" order="1" role="product"/>
        <ParameterDescription key="FunctionParameter_36" name="Inhibitor" order="2" role="modifier"/>
        <ParameterDescription key="FunctionParameter_37" name="Kms" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_38" name="Kmp" order="4" role="constant"/>
        <ParameterDescription key="FunctionParameter_39" name="Vf" order="5" role="constant"/>
        <ParameterDescription key="FunctionParameter_40" name="Vr" order="6" role="constant"/>
        <ParameterDescription key="FunctionParameter_41" name="Ki" order="7" role="constant"/>
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
    <Function key="Function_7" name="Constant flux (reversible)" type="PreDefined" positive="true">
      <MathML>
        <Text>
          v
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_43" name="v" order="0" role="constant"/>
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
    <Function key="Function_9" name="Hill Cooperativity" type="PreDefined" positive="false">
      <MathML>
        <Text>
          V*substrate^h/(Shalve^h+substrate^h)
        </Text>
      </MathML>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_47" name="substrate" order="0" role="substrate"/>
        <ParameterDescription key="FunctionParameter_48" name="Shalve" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_49" name="V" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_50" name="h" order="3" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_0" name="New Model" timeUnit="s" volumeUnit="ml" quantityUnit="mMol" stateVariable="StateVariable_456">
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
        
      </body>
    </Comment>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="compartment" stateVariable="StateVariable_457"/>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_1" name="P1" compartment="Compartment_0" status="variable" stateVariable="StateVariable_458"/>
      <Metabolite key="Metabolite_3" name="S1" compartment="Compartment_0" status="variable" stateVariable="StateVariable_459"/>
      <Metabolite key="Metabolite_7" name="P2" compartment="Compartment_0" status="variable" stateVariable="StateVariable_460"/>
      <Metabolite key="Metabolite_10" name="S2" compartment="Compartment_0" status="variable" stateVariable="StateVariable_461"/>
      <Metabolite key="Metabolite_16" name="P3" compartment="Compartment_0" status="variable" stateVariable="StateVariable_462"/>
      <Metabolite key="Metabolite_19" name="S3" compartment="Compartment_0" status="variable" stateVariable="StateVariable_463"/>
      <Metabolite key="Metabolite_22" name="P4" compartment="Compartment_0" status="variable" stateVariable="StateVariable_464"/>
      <Metabolite key="Metabolite_25" name="S4" compartment="Compartment_0" status="variable" stateVariable="StateVariable_465"/>
      <Metabolite key="Metabolite_28" name="P5" compartment="Compartment_0" status="variable" stateVariable="StateVariable_466"/>
      <Metabolite key="Metabolite_31" name="S5" compartment="Compartment_0" status="variable" stateVariable="StateVariable_467"/>
      <Metabolite key="Metabolite_37" name="P6" compartment="Compartment_0" status="variable" stateVariable="StateVariable_468"/>
      <Metabolite key="Metabolite_40" name="S6" compartment="Compartment_0" status="variable" stateVariable="StateVariable_469"/>
      <Metabolite key="Metabolite_46" name="P10" compartment="Compartment_0" status="variable" stateVariable="StateVariable_470"/>
      <Metabolite key="Metabolite_49" name="S10" compartment="Compartment_0" status="variable" stateVariable="StateVariable_471"/>
      <Metabolite key="Metabolite_55" name="P11" compartment="Compartment_0" status="variable" stateVariable="StateVariable_472"/>
      <Metabolite key="Metabolite_58" name="S11" compartment="Compartment_0" status="variable" stateVariable="StateVariable_473"/>
      <Metabolite key="Metabolite_61" name="P12" compartment="Compartment_0" status="variable" stateVariable="StateVariable_474"/>
      <Metabolite key="Metabolite_64" name="S12" compartment="Compartment_0" status="variable" stateVariable="StateVariable_475"/>
      <Metabolite key="Metabolite_70" name="P13" compartment="Compartment_0" status="variable" stateVariable="StateVariable_476"/>
      <Metabolite key="Metabolite_73" name="S13" compartment="Compartment_0" status="variable" stateVariable="StateVariable_477"/>
      <Metabolite key="Metabolite_76" name="P14" compartment="Compartment_0" status="variable" stateVariable="StateVariable_478"/>
      <Metabolite key="Metabolite_79" name="S14" compartment="Compartment_0" status="variable" stateVariable="StateVariable_479"/>
      <Metabolite key="Metabolite_82" name="P15" compartment="Compartment_0" status="variable" stateVariable="StateVariable_480"/>
      <Metabolite key="Metabolite_85" name="S15" compartment="Compartment_0" status="variable" stateVariable="StateVariable_481"/>
      <Metabolite key="Metabolite_91" name="P16" compartment="Compartment_0" status="variable" stateVariable="StateVariable_482"/>
      <Metabolite key="Metabolite_94" name="S16" compartment="Compartment_0" status="variable" stateVariable="StateVariable_483"/>
      <Metabolite key="Metabolite_103" name="P18" compartment="Compartment_0" status="variable" stateVariable="StateVariable_484"/>
      <Metabolite key="Metabolite_106" name="S18" compartment="Compartment_0" status="variable" stateVariable="StateVariable_485"/>
      <Metabolite key="Metabolite_112" name="P19" compartment="Compartment_0" status="variable" stateVariable="StateVariable_486"/>
      <Metabolite key="Metabolite_115" name="S19" compartment="Compartment_0" status="variable" stateVariable="StateVariable_487"/>
      <Metabolite key="Metabolite_121" name="P20" compartment="Compartment_0" status="variable" stateVariable="StateVariable_488"/>
      <Metabolite key="Metabolite_124" name="S20" compartment="Compartment_0" status="variable" stateVariable="StateVariable_489"/>
      <Metabolite key="Metabolite_127" name="P21" compartment="Compartment_0" status="variable" stateVariable="StateVariable_490"/>
      <Metabolite key="Metabolite_133" name="P22" compartment="Compartment_0" status="variable" stateVariable="StateVariable_491"/>
      <Metabolite key="Metabolite_136" name="S22" compartment="Compartment_0" status="variable" stateVariable="StateVariable_492"/>
      <Metabolite key="Metabolite_139" name="P23" compartment="Compartment_0" status="variable" stateVariable="StateVariable_493"/>
      <Metabolite key="Metabolite_142" name="S23" compartment="Compartment_0" status="variable" stateVariable="StateVariable_494"/>
      <Metabolite key="Metabolite_148" name="P27" compartment="Compartment_0" status="variable" stateVariable="StateVariable_495"/>
      <Metabolite key="Metabolite_151" name="S27" compartment="Compartment_0" status="variable" stateVariable="StateVariable_496"/>
      <Metabolite key="Metabolite_157" name="P28" compartment="Compartment_0" status="variable" stateVariable="StateVariable_497"/>
      <Metabolite key="Metabolite_160" name="S28" compartment="Compartment_0" status="variable" stateVariable="StateVariable_498"/>
      <Metabolite key="Metabolite_166" name="P29" compartment="Compartment_0" status="variable" stateVariable="StateVariable_499"/>
      <Metabolite key="Metabolite_169" name="S29" compartment="Compartment_0" status="variable" stateVariable="StateVariable_500"/>
      <Metabolite key="Metabolite_172" name="P30" compartment="Compartment_0" status="variable" stateVariable="StateVariable_501"/>
      <Metabolite key="Metabolite_175" name="P31" compartment="Compartment_0" status="variable" stateVariable="StateVariable_502"/>
      <Metabolite key="Metabolite_178" name="S30" compartment="Compartment_0" status="variable" stateVariable="StateVariable_503"/>
      <Metabolite key="Metabolite_181" name="S31" compartment="Compartment_0" status="variable" stateVariable="StateVariable_504"/>
      <Metabolite key="Metabolite_184" name="P32" compartment="Compartment_0" status="variable" stateVariable="StateVariable_505"/>
      <Metabolite key="Metabolite_187" name="S32" compartment="Compartment_0" status="variable" stateVariable="StateVariable_506"/>
      <Metabolite key="Metabolite_190" name="S33" compartment="Compartment_0" status="variable" stateVariable="StateVariable_507"/>
      <Metabolite key="Metabolite_193" name="P34" compartment="Compartment_0" status="variable" stateVariable="StateVariable_508"/>
      <Metabolite key="Metabolite_196" name="P35" compartment="Compartment_0" status="variable" stateVariable="StateVariable_509"/>
      <Metabolite key="Metabolite_199" name="S34" compartment="Compartment_0" status="variable" stateVariable="StateVariable_510"/>
      <Metabolite key="Metabolite_202" name="P36" compartment="Compartment_0" status="variable" stateVariable="StateVariable_511"/>
      <Metabolite key="Metabolite_205" name="P37" compartment="Compartment_0" status="variable" stateVariable="StateVariable_512"/>
      <Metabolite key="Metabolite_208" name="S36" compartment="Compartment_0" status="variable" stateVariable="StateVariable_513"/>
      <Metabolite key="Metabolite_211" name="S37" compartment="Compartment_0" status="variable" stateVariable="StateVariable_514"/>
      <Metabolite key="Metabolite_217" name="P38" compartment="Compartment_0" status="variable" stateVariable="StateVariable_515"/>
      <Metabolite key="Metabolite_220" name="S38" compartment="Compartment_0" status="variable" stateVariable="StateVariable_516"/>
      <Metabolite key="Metabolite_232" name="P39" compartment="Compartment_0" status="variable" stateVariable="StateVariable_517"/>
      <Metabolite key="Metabolite_235" name="S39" compartment="Compartment_0" status="variable" stateVariable="StateVariable_518"/>
      <Metabolite key="Metabolite_238" name="P41" compartment="Compartment_0" status="variable" stateVariable="StateVariable_519"/>
      <Metabolite key="Metabolite_241" name="S41" compartment="Compartment_0" status="variable" stateVariable="StateVariable_520"/>
      <Metabolite key="Metabolite_244" name="P42" compartment="Compartment_0" status="variable" stateVariable="StateVariable_521"/>
      <Metabolite key="Metabolite_247" name="S42" compartment="Compartment_0" status="variable" stateVariable="StateVariable_522"/>
      <Metabolite key="Metabolite_253" name="P43" compartment="Compartment_0" status="variable" stateVariable="StateVariable_523"/>
      <Metabolite key="Metabolite_256" name="S43" compartment="Compartment_0" status="variable" stateVariable="StateVariable_524"/>
      <Metabolite key="Metabolite_259" name="P44" compartment="Compartment_0" status="variable" stateVariable="StateVariable_525"/>
      <Metabolite key="Metabolite_262" name="S44" compartment="Compartment_0" status="variable" stateVariable="StateVariable_526"/>
      <Metabolite key="Metabolite_268" name="P45" compartment="Compartment_0" status="variable" stateVariable="StateVariable_527"/>
      <Metabolite key="Metabolite_271" name="S45" compartment="Compartment_0" status="variable" stateVariable="StateVariable_528"/>
      <Metabolite key="Metabolite_274" name="P46" compartment="Compartment_0" status="variable" stateVariable="StateVariable_529"/>
      <Metabolite key="Metabolite_277" name="S46" compartment="Compartment_0" status="variable" stateVariable="StateVariable_530"/>
      <Metabolite key="Metabolite_280" name="P7" compartment="Compartment_0" status="variable" stateVariable="StateVariable_531"/>
      <Metabolite key="Metabolite_283" name="A1" compartment="Compartment_0" status="variable" stateVariable="StateVariable_532"/>
      <Metabolite key="Metabolite_286" name="A2" compartment="Compartment_0" status="variable" stateVariable="StateVariable_533"/>
      <Metabolite key="Metabolite_289" name="A3" compartment="Compartment_0" status="variable" stateVariable="StateVariable_534"/>
      <Metabolite key="Metabolite_292" name="B1" compartment="Compartment_0" status="variable" stateVariable="StateVariable_535"/>
      <Metabolite key="Metabolite_295" name="C1" compartment="Compartment_0" status="variable" stateVariable="StateVariable_536"/>
      <Metabolite key="Metabolite_298" name="C2" compartment="Compartment_0" status="variable" stateVariable="StateVariable_537"/>
      <Metabolite key="Metabolite_301" name="D1" compartment="Compartment_0" status="variable" stateVariable="StateVariable_538"/>
      <Metabolite key="Metabolite_304" name="D2" compartment="Compartment_0" status="variable" stateVariable="StateVariable_539"/>
      <Metabolite key="Metabolite_307" name="D3" compartment="Compartment_0" status="variable" stateVariable="StateVariable_540"/>
      <Metabolite key="Metabolite_97" name="P17" compartment="Compartment_0" status="variable" stateVariable="StateVariable_541"/>
      <Metabolite key="Metabolite_265" name="M45" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_542"/>
      <Metabolite key="Metabolite_250" name="M42" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_543"/>
      <Metabolite key="Metabolite_229" name="M40" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_544"/>
      <Metabolite key="Metabolite_226" name="M39" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_545"/>
      <Metabolite key="Metabolite_223" name="," compartment="Compartment_0" status="fixed" stateVariable="StateVariable_546"/>
      <Metabolite key="Metabolite_214" name="M38" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_547"/>
      <Metabolite key="Metabolite_163" name="M29" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_548"/>
      <Metabolite key="Metabolite_154" name="M28" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_549"/>
      <Metabolite key="Metabolite_145" name="M27" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_550"/>
      <Metabolite key="Metabolite_130" name="M22" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_551"/>
      <Metabolite key="Metabolite_118" name="M20" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_552"/>
      <Metabolite key="Metabolite_109" name="M19" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_553"/>
      <Metabolite key="Metabolite_100" name="M18" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_554"/>
      <Metabolite key="Metabolite_88" name="M16" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_555"/>
      <Metabolite key="Metabolite_67" name="M13" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_556"/>
      <Metabolite key="Metabolite_52" name="M11" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_557"/>
      <Metabolite key="Metabolite_43" name="M10" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_558"/>
      <Metabolite key="Metabolite_34" name="M6" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_559"/>
      <Metabolite key="Metabolite_13" name="M3" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_560"/>
      <Metabolite key="Metabolite_4" name="M2" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_561"/>
      <Metabolite key="Metabolite_0" name="M1" compartment="Compartment_0" status="fixed" stateVariable="StateVariable_562"/>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_0" name="K1" status="fixed" stateVariable="StateVariable_563"/>
      <ModelValue key="ModelValue_1" name="K2" status="fixed" stateVariable="StateVariable_564"/>
      <ModelValue key="ModelValue_2" name="K3" status="fixed" stateVariable="StateVariable_565"/>
      <ModelValue key="ModelValue_3" name="K4" status="fixed" stateVariable="StateVariable_566"/>
      <ModelValue key="ModelValue_4" name="K5" status="fixed" stateVariable="StateVariable_567"/>
      <ModelValue key="ModelValue_5" name="K6" status="fixed" stateVariable="StateVariable_568"/>
      <ModelValue key="ModelValue_6" name="K7" status="fixed" stateVariable="StateVariable_569"/>
      <ModelValue key="ModelValue_7" name="K8" status="fixed" stateVariable="StateVariable_570"/>
      <ModelValue key="ModelValue_8" name="K9" status="fixed" stateVariable="StateVariable_571"/>
      <ModelValue key="ModelValue_9" name="K10" status="fixed" stateVariable="StateVariable_572"/>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="reaction" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_0" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_93" name="V" value="0.1"/>
          <Constant key="Parameter_94" name="Ks" value="0.1"/>
          <Constant key="Parameter_95" name="n" value="0.1"/>
          <Constant key="Parameter_96" name="L" value="0.1"/>
          <Constant key="Parameter_97" name="Ki" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_0">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_0">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_1">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_2">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_3">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_4">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_5">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_6">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="reaction_1" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_37" name="Kms" value="0.1"/>
          <Constant key="Parameter_98" name="V" value="0.1"/>
          <Constant key="Parameter_99" name="Ka" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_2">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_16">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_17">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_18">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_19">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_20">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="reaction_2" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_38" name="Km" value="0.1"/>
          <Constant key="Parameter_100" name="V" value="0.1"/>
          <Constant key="Parameter_101" name="Ki" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_4">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_29">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_30">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_31">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_32">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_33">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="reaction_3" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_40" name="Km" value="0.1"/>
          <Constant key="Parameter_102" name="V" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_8">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_44">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_45">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_46">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="reaction_4" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_39" name="Shalve" value="0.1"/>
          <Constant key="Parameter_103" name="V" value="0.1"/>
          <Constant key="Parameter_104" name="h" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_9">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_47">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_48">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_49">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_50">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="reaction_5" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_41" name="Km" value="0.1"/>
          <Constant key="Parameter_105" name="V" value="0.1"/>
          <Constant key="Parameter_106" name="Kd" value="0.1"/>
          <Constant key="Parameter_107" name="a" value="0.1"/>
          <Constant key="Parameter_108" name="b" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_10">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_51">
              <SourceParameter reference="Metabolite_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_52">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_53">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_54">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_55">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_56">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_57">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="reaction_6" reversible="false">
        <ListOfProducts>
          <Product metabolite="Metabolite_280" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_92" name="v" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_6">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_42">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="reaction_7" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_42" name="Kms" value="0.1"/>
          <Constant key="Parameter_109" name="V" value="0.1"/>
          <Constant key="Parameter_110" name="Kas" value="0.1"/>
          <Constant key="Parameter_111" name="Kac" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_15">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_81">
              <SourceParameter reference="Metabolite_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_82">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_83">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_84">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_85">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_86">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="reaction_8" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_58" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_52" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_43" name="Km" value="0.1"/>
          <Constant key="Parameter_112" name="V" value="0.1"/>
          <Constant key="Parameter_113" name="Kis" value="0.1"/>
          <Constant key="Parameter_114" name="Kic" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_17">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_96">
              <SourceParameter reference="Metabolite_58"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_97">
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_98">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_99">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_100">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_101">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="reaction_9" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_64" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_44" name="Km" value="0.1"/>
          <Constant key="Parameter_115" name="V" value="0.1"/>
          <Constant key="Parameter_116" name="Ki" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_19">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_111">
              <SourceParameter reference="Metabolite_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_112">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_113">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_114">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_115">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="reaction_10" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_73" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_70" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_67" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_45" name="Kms" value="0.1"/>
          <Constant key="Parameter_117" name="V" value="0.1"/>
          <Constant key="Parameter_118" name="Ka" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_29">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_208">
              <SourceParameter reference="Metabolite_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_209">
              <SourceParameter reference="Metabolite_67"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_210">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_211">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_212">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="reaction_11" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_76" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_46" name="V" value="0.1"/>
          <Constant key="Parameter_119" name="Ksc" value="0.1"/>
          <Constant key="Parameter_120" name="Ksa" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_31">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_221">
              <SourceParameter reference="Metabolite_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_222">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_223">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_224">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="reaction_12" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_85" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_82" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_47" name="Km" value="0.1"/>
          <Constant key="Parameter_121" name="V" value="0.1"/>
          <Constant key="Parameter_122" name="Ki" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_32">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_225">
              <SourceParameter reference="Metabolite_85"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_226">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_227">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_228">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="reaction_13" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_94" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_91" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_88" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_48" name="Km" value="0.1"/>
          <Constant key="Parameter_123" name="V" value="0.1"/>
          <Constant key="Parameter_124" name="Ki" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_34">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_236">
              <SourceParameter reference="Metabolite_94"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_237">
              <SourceParameter reference="Metabolite_88"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_238">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_239">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_240">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="reaction_14" reversible="false">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_283" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_286" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_289" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_292" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_49" name="k1" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_13">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_75">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_76">
              <SourceParameter reference="Metabolite_283"/>
              <SourceParameter reference="Metabolite_286"/>
              <SourceParameter reference="Metabolite_289"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="reaction_15" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_106" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_103" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_100" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_50" name="Vf" value="0.1"/>
          <Constant key="Parameter_125" name="Vr" value="0.1"/>
          <Constant key="Parameter_126" name="Kms" value="0.1"/>
          <Constant key="Parameter_127" name="Kmp" value="0.1"/>
          <Constant key="Parameter_128" name="n" value="0.1"/>
          <Constant key="Parameter_129" name="Ki" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_1">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_7">
              <SourceParameter reference="Metabolite_106"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_8">
              <SourceParameter reference="Metabolite_103"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_9">
              <SourceParameter reference="Metabolite_100"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_10">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_11">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_12">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_13">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_14">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_15">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="reaction_16" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_115" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_112" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_109" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_51" name="Kms" value="0.1"/>
          <Constant key="Parameter_52" name="Kmp" value="0.1"/>
          <Constant key="Parameter_130" name="Vf" value="0.1"/>
          <Constant key="Parameter_131" name="Vr" value="0.1"/>
          <Constant key="Parameter_132" name="Ka" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_3">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_21">
              <SourceParameter reference="Metabolite_115"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_22">
              <SourceParameter reference="Metabolite_112"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_23">
              <SourceParameter reference="Metabolite_109"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_24">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_25">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_26">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_27">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_28">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="reaction_17" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_124" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_121" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_118" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_53" name="Kms" value="0.1"/>
          <Constant key="Parameter_54" name="Kmp" value="0.1"/>
          <Constant key="Parameter_133" name="Vf" value="0.1"/>
          <Constant key="Parameter_134" name="Vr" value="0.1"/>
          <Constant key="Parameter_135" name="Ki" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_5">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_34">
              <SourceParameter reference="Metabolite_124"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_35">
              <SourceParameter reference="Metabolite_121"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_36">
              <SourceParameter reference="Metabolite_118"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_37">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_38">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_39">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_40">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_41">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="reaction_18" reversible="true">
        <ListOfProducts>
          <Product metabolite="Metabolite_127" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_57" name="v" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_7">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_43">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="reaction_19" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_136" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_133" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_130" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_55" name="Kms" value="0.1"/>
          <Constant key="Parameter_56" name="Kmp" value="0.1"/>
          <Constant key="Parameter_136" name="Vf" value="0.1"/>
          <Constant key="Parameter_137" name="Vr" value="0.1"/>
          <Constant key="Parameter_138" name="Kd" value="0.1"/>
          <Constant key="Parameter_139" name="a" value="0.1"/>
          <Constant key="Parameter_140" name="b" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_11">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_58">
              <SourceParameter reference="Metabolite_136"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_59">
              <SourceParameter reference="Metabolite_133"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_60">
              <SourceParameter reference="Metabolite_130"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_61">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_62">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_63">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_64">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_65">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_66">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_67">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="reaction_20" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_142" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_139" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_58" name="Kms" value="0.1"/>
          <Constant key="Parameter_59" name="Kmp" value="0.1"/>
          <Constant key="Parameter_141" name="Kii" value="0.1"/>
          <Constant key="Parameter_142" name="Vf" value="0.1"/>
          <Constant key="Parameter_143" name="Keq" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_12">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_68">
              <SourceParameter reference="Metabolite_142"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_69">
              <SourceParameter reference="Metabolite_139"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_70">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_71">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_72">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_73">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_74">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="reaction_21" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_295" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_298" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_301" stoichiometry="1"/>
          <Product metabolite="Metabolite_304" stoichiometry="1"/>
          <Product metabolite="Metabolite_307" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_90" name="k1" value="0.1"/>
          <Constant key="Parameter_91" name="k2" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_14">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_77">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_78">
              <SourceParameter reference="Metabolite_295"/>
              <SourceParameter reference="Metabolite_298"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_79">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_80">
              <SourceParameter reference="Metabolite_301"/>
              <SourceParameter reference="Metabolite_304"/>
              <SourceParameter reference="Metabolite_307"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="reaction_22" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_151" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_148" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_145" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_60" name="Kms" value="0.1"/>
          <Constant key="Parameter_61" name="Kmp" value="0.1"/>
          <Constant key="Parameter_144" name="Vf" value="0.1"/>
          <Constant key="Parameter_145" name="Vr" value="0.1"/>
          <Constant key="Parameter_146" name="Kas" value="0.1"/>
          <Constant key="Parameter_147" name="Kac" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_16">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_87">
              <SourceParameter reference="Metabolite_151"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_88">
              <SourceParameter reference="Metabolite_148"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_89">
              <SourceParameter reference="Metabolite_145"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_90">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_91">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_92">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_93">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_94">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_95">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="reaction_23" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_160" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_157" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_154" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_62" name="Kms" value="0.1"/>
          <Constant key="Parameter_63" name="Kmp" value="0.1"/>
          <Constant key="Parameter_148" name="Vf" value="0.1"/>
          <Constant key="Parameter_149" name="Vr" value="0.1"/>
          <Constant key="Parameter_150" name="Kis" value="0.1"/>
          <Constant key="Parameter_151" name="Kic" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_18">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_102">
              <SourceParameter reference="Metabolite_160"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_103">
              <SourceParameter reference="Metabolite_157"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_104">
              <SourceParameter reference="Metabolite_154"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_105">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_106">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_107">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_108">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_109">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_110">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="reaction_24" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_169" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_166" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_163" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_64" name="Kms" value="0.1"/>
          <Constant key="Parameter_65" name="Kmp" value="0.1"/>
          <Constant key="Parameter_152" name="Vf" value="0.1"/>
          <Constant key="Parameter_153" name="Vr" value="0.1"/>
          <Constant key="Parameter_154" name="Ki" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_20">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_116">
              <SourceParameter reference="Metabolite_169"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_117">
              <SourceParameter reference="Metabolite_166"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_118">
              <SourceParameter reference="Metabolite_163"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_119">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_120">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_121">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_122">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_123">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="reaction_25" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_178" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_181" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_172" stoichiometry="1"/>
          <Product metabolite="Metabolite_175" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_66" name="Keq" value="0.1"/>
          <Constant key="Parameter_67" name="Vf" value="0.1"/>
          <Constant key="Parameter_155" name="Vr" value="0.1"/>
          <Constant key="Parameter_156" name="Kma" value="0.1"/>
          <Constant key="Parameter_157" name="Kmb" value="0.1"/>
          <Constant key="Parameter_158" name="Kmp" value="0.1"/>
          <Constant key="Parameter_159" name="Kmq" value="0.1"/>
          <Constant key="Parameter_160" name="Kia" value="0.1"/>
          <Constant key="Parameter_161" name="Kib" value="0.1"/>
          <Constant key="Parameter_162" name="Kip" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_21">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_124">
              <SourceParameter reference="Metabolite_178"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_125">
              <SourceParameter reference="Metabolite_181"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_126">
              <SourceParameter reference="Metabolite_172"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_127">
              <SourceParameter reference="Metabolite_175"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_128">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_129">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_130">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_131">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_132">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_133">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_134">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_135">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_136">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_137">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="reaction_26" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_187" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_190" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_184" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_68" name="Kma" value="0.1"/>
          <Constant key="Parameter_69" name="Kmb" value="0.1"/>
          <Constant key="Parameter_163" name="Kmp" value="0.1"/>
          <Constant key="Parameter_164" name="Kia" value="0.1"/>
          <Constant key="Parameter_165" name="Keq" value="0.1"/>
          <Constant key="Parameter_166" name="Vf" value="0.1"/>
          <Constant key="Parameter_167" name="Vr" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_22">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_138">
              <SourceParameter reference="Metabolite_187"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_139">
              <SourceParameter reference="Metabolite_190"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_140">
              <SourceParameter reference="Metabolite_184"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_141">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_142">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_143">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_144">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_145">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_146">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_147">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="reaction_27" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_199" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_193" stoichiometry="1"/>
          <Product metabolite="Metabolite_196" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_70" name="Kms" value="0.1"/>
          <Constant key="Parameter_71" name="Kmq" value="0.1"/>
          <Constant key="Parameter_168" name="Kmp" value="0.1"/>
          <Constant key="Parameter_169" name="Kip" value="0.1"/>
          <Constant key="Parameter_170" name="Keq" value="0.1"/>
          <Constant key="Parameter_171" name="Vf" value="0.1"/>
          <Constant key="Parameter_172" name="Vr" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_23">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_148">
              <SourceParameter reference="Metabolite_199"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_149">
              <SourceParameter reference="Metabolite_193"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_150">
              <SourceParameter reference="Metabolite_196"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_151">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_152">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_153">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_154">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_155">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_156">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_157">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="reaction_28" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_208" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_211" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_202" stoichiometry="1"/>
          <Product metabolite="Metabolite_205" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_72" name="Keq" value="0.1"/>
          <Constant key="Parameter_73" name="Vf" value="0.1"/>
          <Constant key="Parameter_173" name="Vr" value="0.1"/>
          <Constant key="Parameter_174" name="Kma" value="0.1"/>
          <Constant key="Parameter_175" name="Kmb" value="0.1"/>
          <Constant key="Parameter_176" name="Kmp" value="0.1"/>
          <Constant key="Parameter_177" name="Kmq" value="0.1"/>
          <Constant key="Parameter_178" name="Kia" value="0.1"/>
          <Constant key="Parameter_179" name="Kiq" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_24">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_158">
              <SourceParameter reference="Metabolite_208"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_159">
              <SourceParameter reference="Metabolite_211"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_160">
              <SourceParameter reference="Metabolite_202"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_161">
              <SourceParameter reference="Metabolite_205"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_162">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_163">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_164">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_165">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_166">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_167">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_168">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_169">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_170">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="reaction_29" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_220" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_217" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_214" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_74" name="Keq" value="0.1"/>
          <Constant key="Parameter_75" name="Vf" value="0.1"/>
          <Constant key="Parameter_180" name="Shalve" value="0.1"/>
          <Constant key="Parameter_181" name="Phalve" value="0.1"/>
          <Constant key="Parameter_182" name="h" value="0.1"/>
          <Constant key="Parameter_183" name="Mhalve" value="0.1"/>
          <Constant key="Parameter_184" name="alpha" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_25">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_171">
              <SourceParameter reference="Metabolite_220"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_172">
              <SourceParameter reference="Metabolite_217"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_173">
              <SourceParameter reference="Metabolite_214"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_174">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_175">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_176">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_177">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_178">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_179">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_180">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="reaction_30" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_235" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_232" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_226" stoichiometry="1"/>
          <Modifier metabolite="Metabolite_229" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_76" name="Keq" value="0.1"/>
          <Constant key="Parameter_77" name="Vf" value="0.1"/>
          <Constant key="Parameter_185" name="Shalve" value="0.1"/>
          <Constant key="Parameter_186" name="Phalve" value="0.1"/>
          <Constant key="Parameter_187" name="h" value="0.1"/>
          <Constant key="Parameter_188" name="MAhalve" value="0.1"/>
          <Constant key="Parameter_189" name="alphaA" value="0.1"/>
          <Constant key="Parameter_190" name="MBhalve" value="0.1"/>
          <Constant key="Parameter_191" name="alphaB" value="0.1"/>
          <Constant key="Parameter_192" name="alphaAB" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_26">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_181">
              <SourceParameter reference="Metabolite_235"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_182">
              <SourceParameter reference="Metabolite_232"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_183">
              <SourceParameter reference="Metabolite_226"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_184">
              <SourceParameter reference="Metabolite_229"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_185">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_186">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_187">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_188">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_189">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_190">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_191">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_192">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_193">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_194">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="reaction_31" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_241" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_238" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_78" name="Keq" value="0.1"/>
          <Constant key="Parameter_79" name="Vf" value="0.1"/>
          <Constant key="Parameter_193" name="Shalve" value="0.1"/>
          <Constant key="Parameter_194" name="Phalve" value="0.1"/>
          <Constant key="Parameter_195" name="h" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_27">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_195">
              <SourceParameter reference="Metabolite_241"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_196">
              <SourceParameter reference="Metabolite_238"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_197">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_198">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_199">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_200">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_201">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_32" name="reaction_32" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_247" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_244" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_80" name="Kms" value="0.1"/>
          <Constant key="Parameter_81" name="Kmp" value="0.1"/>
          <Constant key="Parameter_196" name="Vf" value="0.1"/>
          <Constant key="Parameter_197" name="Vr" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_28">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_202">
              <SourceParameter reference="Metabolite_247"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_203">
              <SourceParameter reference="Metabolite_244"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_204">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_205">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_206">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_207">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_33" name="reaction_33" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_256" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_253" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_250" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_82" name="Kms" value="0.1"/>
          <Constant key="Parameter_83" name="Kmp" value="0.1"/>
          <Constant key="Parameter_198" name="Vf" value="0.1"/>
          <Constant key="Parameter_199" name="Vr" value="0.1"/>
          <Constant key="Parameter_200" name="Ka" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_30">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_213">
              <SourceParameter reference="Metabolite_256"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_214">
              <SourceParameter reference="Metabolite_253"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_215">
              <SourceParameter reference="Metabolite_250"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_216">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_217">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_218">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_219">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_220">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_34" name="reaction_34" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_262" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_259" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_84" name="Kms" value="0.1"/>
          <Constant key="Parameter_85" name="Kmp" value="0.1"/>
          <Constant key="Parameter_201" name="Vf" value="0.1"/>
          <Constant key="Parameter_202" name="Vr" value="0.1"/>
          <Constant key="Parameter_203" name="Ki" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_33">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_229">
              <SourceParameter reference="Metabolite_262"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_230">
              <SourceParameter reference="Metabolite_259"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_231">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_232">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_233">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_234">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_235">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="reaction_35" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_271" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_268" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfModifiers>
          <Modifier metabolite="Metabolite_265" stoichiometry="1"/>
        </ListOfModifiers>
        <ListOfConstants>
          <Constant key="Parameter_86" name="Kms" value="0.1"/>
          <Constant key="Parameter_87" name="Kmp" value="0.1"/>
          <Constant key="Parameter_204" name="Vf" value="0.1"/>
          <Constant key="Parameter_205" name="Vr" value="0.1"/>
          <Constant key="Parameter_206" name="Ki" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_35">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_241">
              <SourceParameter reference="Metabolite_271"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_242">
              <SourceParameter reference="Metabolite_268"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_243">
              <SourceParameter reference="Metabolite_265"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_244">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_245">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_246">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_247">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_248">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_36" name="reaction_36" reversible="true">
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_277" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_274" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_88" name="Kms" value="0.1"/>
          <Constant key="Parameter_89" name="Kmp" value="0.1"/>
          <Constant key="Parameter_207" name="Vf" value="0.1"/>
          <Constant key="Parameter_208" name="Keq" value="0.1"/>
        </ListOfConstants>
        <KineticLaw function="Function_36">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_249">
              <SourceParameter reference="Metabolite_277"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_250">
              <SourceParameter reference="Metabolite_274"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_251">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_252">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_253">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_254">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <StateTemplate>
      <StateTemplateVariable key="StateVariable_456" objectReference="Model_0"/>
      <StateTemplateVariable key="StateVariable_457" objectReference="Compartment_0"/>
      <StateTemplateVariable key="StateVariable_458" objectReference="Metabolite_1"/>
      <StateTemplateVariable key="StateVariable_459" objectReference="Metabolite_3"/>
      <StateTemplateVariable key="StateVariable_460" objectReference="Metabolite_7"/>
      <StateTemplateVariable key="StateVariable_461" objectReference="Metabolite_10"/>
      <StateTemplateVariable key="StateVariable_462" objectReference="Metabolite_16"/>
      <StateTemplateVariable key="StateVariable_463" objectReference="Metabolite_19"/>
      <StateTemplateVariable key="StateVariable_464" objectReference="Metabolite_22"/>
      <StateTemplateVariable key="StateVariable_465" objectReference="Metabolite_25"/>
      <StateTemplateVariable key="StateVariable_466" objectReference="Metabolite_28"/>
      <StateTemplateVariable key="StateVariable_467" objectReference="Metabolite_31"/>
      <StateTemplateVariable key="StateVariable_468" objectReference="Metabolite_37"/>
      <StateTemplateVariable key="StateVariable_469" objectReference="Metabolite_40"/>
      <StateTemplateVariable key="StateVariable_470" objectReference="Metabolite_46"/>
      <StateTemplateVariable key="StateVariable_471" objectReference="Metabolite_49"/>
      <StateTemplateVariable key="StateVariable_472" objectReference="Metabolite_55"/>
      <StateTemplateVariable key="StateVariable_473" objectReference="Metabolite_58"/>
      <StateTemplateVariable key="StateVariable_474" objectReference="Metabolite_61"/>
      <StateTemplateVariable key="StateVariable_475" objectReference="Metabolite_64"/>
      <StateTemplateVariable key="StateVariable_476" objectReference="Metabolite_70"/>
      <StateTemplateVariable key="StateVariable_477" objectReference="Metabolite_73"/>
      <StateTemplateVariable key="StateVariable_478" objectReference="Metabolite_76"/>
      <StateTemplateVariable key="StateVariable_479" objectReference="Metabolite_79"/>
      <StateTemplateVariable key="StateVariable_480" objectReference="Metabolite_82"/>
      <StateTemplateVariable key="StateVariable_481" objectReference="Metabolite_85"/>
      <StateTemplateVariable key="StateVariable_482" objectReference="Metabolite_91"/>
      <StateTemplateVariable key="StateVariable_483" objectReference="Metabolite_94"/>
      <StateTemplateVariable key="StateVariable_484" objectReference="Metabolite_103"/>
      <StateTemplateVariable key="StateVariable_485" objectReference="Metabolite_106"/>
      <StateTemplateVariable key="StateVariable_486" objectReference="Metabolite_112"/>
      <StateTemplateVariable key="StateVariable_487" objectReference="Metabolite_115"/>
      <StateTemplateVariable key="StateVariable_488" objectReference="Metabolite_121"/>
      <StateTemplateVariable key="StateVariable_489" objectReference="Metabolite_124"/>
      <StateTemplateVariable key="StateVariable_490" objectReference="Metabolite_127"/>
      <StateTemplateVariable key="StateVariable_491" objectReference="Metabolite_133"/>
      <StateTemplateVariable key="StateVariable_492" objectReference="Metabolite_136"/>
      <StateTemplateVariable key="StateVariable_493" objectReference="Metabolite_139"/>
      <StateTemplateVariable key="StateVariable_494" objectReference="Metabolite_142"/>
      <StateTemplateVariable key="StateVariable_495" objectReference="Metabolite_148"/>
      <StateTemplateVariable key="StateVariable_496" objectReference="Metabolite_151"/>
      <StateTemplateVariable key="StateVariable_497" objectReference="Metabolite_157"/>
      <StateTemplateVariable key="StateVariable_498" objectReference="Metabolite_160"/>
      <StateTemplateVariable key="StateVariable_499" objectReference="Metabolite_166"/>
      <StateTemplateVariable key="StateVariable_500" objectReference="Metabolite_169"/>
      <StateTemplateVariable key="StateVariable_501" objectReference="Metabolite_172"/>
      <StateTemplateVariable key="StateVariable_502" objectReference="Metabolite_175"/>
      <StateTemplateVariable key="StateVariable_503" objectReference="Metabolite_178"/>
      <StateTemplateVariable key="StateVariable_504" objectReference="Metabolite_181"/>
      <StateTemplateVariable key="StateVariable_505" objectReference="Metabolite_184"/>
      <StateTemplateVariable key="StateVariable_506" objectReference="Metabolite_187"/>
      <StateTemplateVariable key="StateVariable_507" objectReference="Metabolite_190"/>
      <StateTemplateVariable key="StateVariable_508" objectReference="Metabolite_193"/>
      <StateTemplateVariable key="StateVariable_509" objectReference="Metabolite_196"/>
      <StateTemplateVariable key="StateVariable_510" objectReference="Metabolite_199"/>
      <StateTemplateVariable key="StateVariable_511" objectReference="Metabolite_202"/>
      <StateTemplateVariable key="StateVariable_512" objectReference="Metabolite_205"/>
      <StateTemplateVariable key="StateVariable_513" objectReference="Metabolite_208"/>
      <StateTemplateVariable key="StateVariable_514" objectReference="Metabolite_211"/>
      <StateTemplateVariable key="StateVariable_515" objectReference="Metabolite_217"/>
      <StateTemplateVariable key="StateVariable_516" objectReference="Metabolite_220"/>
      <StateTemplateVariable key="StateVariable_517" objectReference="Metabolite_232"/>
      <StateTemplateVariable key="StateVariable_518" objectReference="Metabolite_235"/>
      <StateTemplateVariable key="StateVariable_519" objectReference="Metabolite_238"/>
      <StateTemplateVariable key="StateVariable_520" objectReference="Metabolite_241"/>
      <StateTemplateVariable key="StateVariable_521" objectReference="Metabolite_244"/>
      <StateTemplateVariable key="StateVariable_522" objectReference="Metabolite_247"/>
      <StateTemplateVariable key="StateVariable_523" objectReference="Metabolite_253"/>
      <StateTemplateVariable key="StateVariable_524" objectReference="Metabolite_256"/>
      <StateTemplateVariable key="StateVariable_525" objectReference="Metabolite_259"/>
      <StateTemplateVariable key="StateVariable_526" objectReference="Metabolite_262"/>
      <StateTemplateVariable key="StateVariable_527" objectReference="Metabolite_268"/>
      <StateTemplateVariable key="StateVariable_528" objectReference="Metabolite_271"/>
      <StateTemplateVariable key="StateVariable_529" objectReference="Metabolite_274"/>
      <StateTemplateVariable key="StateVariable_530" objectReference="Metabolite_277"/>
      <StateTemplateVariable key="StateVariable_531" objectReference="Metabolite_280"/>
      <StateTemplateVariable key="StateVariable_532" objectReference="Metabolite_283"/>
      <StateTemplateVariable key="StateVariable_533" objectReference="Metabolite_286"/>
      <StateTemplateVariable key="StateVariable_534" objectReference="Metabolite_289"/>
      <StateTemplateVariable key="StateVariable_535" objectReference="Metabolite_292"/>
      <StateTemplateVariable key="StateVariable_536" objectReference="Metabolite_295"/>
      <StateTemplateVariable key="StateVariable_537" objectReference="Metabolite_298"/>
      <StateTemplateVariable key="StateVariable_538" objectReference="Metabolite_301"/>
      <StateTemplateVariable key="StateVariable_539" objectReference="Metabolite_304"/>
      <StateTemplateVariable key="StateVariable_540" objectReference="Metabolite_307"/>
      <StateTemplateVariable key="StateVariable_541" objectReference="Metabolite_97"/>
      <StateTemplateVariable key="StateVariable_542" objectReference="Metabolite_265"/>
      <StateTemplateVariable key="StateVariable_543" objectReference="Metabolite_250"/>
      <StateTemplateVariable key="StateVariable_544" objectReference="Metabolite_229"/>
      <StateTemplateVariable key="StateVariable_545" objectReference="Metabolite_226"/>
      <StateTemplateVariable key="StateVariable_546" objectReference="Metabolite_223"/>
      <StateTemplateVariable key="StateVariable_547" objectReference="Metabolite_214"/>
      <StateTemplateVariable key="StateVariable_548" objectReference="Metabolite_163"/>
      <StateTemplateVariable key="StateVariable_549" objectReference="Metabolite_154"/>
      <StateTemplateVariable key="StateVariable_550" objectReference="Metabolite_145"/>
      <StateTemplateVariable key="StateVariable_551" objectReference="Metabolite_130"/>
      <StateTemplateVariable key="StateVariable_552" objectReference="Metabolite_118"/>
      <StateTemplateVariable key="StateVariable_553" objectReference="Metabolite_109"/>
      <StateTemplateVariable key="StateVariable_554" objectReference="Metabolite_100"/>
      <StateTemplateVariable key="StateVariable_555" objectReference="Metabolite_88"/>
      <StateTemplateVariable key="StateVariable_556" objectReference="Metabolite_67"/>
      <StateTemplateVariable key="StateVariable_557" objectReference="Metabolite_52"/>
      <StateTemplateVariable key="StateVariable_558" objectReference="Metabolite_43"/>
      <StateTemplateVariable key="StateVariable_559" objectReference="Metabolite_34"/>
      <StateTemplateVariable key="StateVariable_560" objectReference="Metabolite_13"/>
      <StateTemplateVariable key="StateVariable_561" objectReference="Metabolite_4"/>
      <StateTemplateVariable key="StateVariable_562" objectReference="Metabolite_0"/>
      <StateTemplateVariable key="StateVariable_563" objectReference="ModelValue_0"/>
      <StateTemplateVariable key="StateVariable_564" objectReference="ModelValue_1"/>
      <StateTemplateVariable key="StateVariable_565" objectReference="ModelValue_2"/>
      <StateTemplateVariable key="StateVariable_566" objectReference="ModelValue_3"/>
      <StateTemplateVariable key="StateVariable_567" objectReference="ModelValue_4"/>
      <StateTemplateVariable key="StateVariable_568" objectReference="ModelValue_5"/>
      <StateTemplateVariable key="StateVariable_569" objectReference="ModelValue_6"/>
      <StateTemplateVariable key="StateVariable_570" objectReference="ModelValue_7"/>
      <StateTemplateVariable key="StateVariable_571" objectReference="ModelValue_8"/>
      <StateTemplateVariable key="StateVariable_572" objectReference="ModelValue_9"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 1 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 6.02214e+19 1 2 3 4 5 6 7 8 9 10
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_4" name="Steady-State" type="steadyState" scheduled="false">
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
        <Parameter name="Newton.Resolution" type="unsignedFloat" value="1e-09"/>
        <Parameter name="Newton.LSODA.RelativeTolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Newton.LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Newton.LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="Newton.LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="Newton.LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_3" name="Time-Course" type="timeCourse" scheduled="false">
      <Problem>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="StartTime" type="float" value="0"/>
        <Parameter name="EndTime" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Stochastic">
        <Parameter name="LSODA.RelativeTolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="LSODA.AbsoluteTolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="LSODA.AdamsMaxOrder" type="unsignedInteger" value="12"/>
        <Parameter name="LSODA.BDFMaxOrder" type="unsignedInteger" value="5"/>
        <Parameter name="LSODA.MaxStepsInternal" type="unsignedInteger" value="10000"/>
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
    <Task key="Task_1" name="Optimization" type="optimization" scheduled="false">
      <Problem>
        <ParameterGroup name="OptimizationItemList">
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
        </ParameterGroup>
        <Parameter name="Steady-State" type="key" value=""/>
        <Parameter name="Time-Course" type="key" value=""/>
        <Parameter name="ObjectiveFunction" type="key" value=""/>
        <Parameter name="Maximize" type="bool" value="0"/>
      </Problem>
      <Method name="Random Search" type="RandomSearch">
        <Parameter name="Number of Iterations" type="unsignedInteger" value="100000"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_0" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false">
      <Problem>
        <Parameter name="SteadyStateRequested" type="bool" value="1"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="ScanFramework">
        <Parameter name="MCA.ModulationFactor" type="unsignedFloat" value="1e-09"/>
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
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
    <Report key="Report_0" name="Optimization" taskType="optimization" separator="&#x09;">
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
  <GUI>
  </GUI>
</COPASI>
