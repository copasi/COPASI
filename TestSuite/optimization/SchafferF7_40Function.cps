<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.38 (Build 268) (http://www.copasi.org) at 2022-12-14T14:56:14Z -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="38" versionDevel="268" copasiSourcesModified="0">
  <Model key="Model_0" name="Schaffer F7(40) function" simulationType="time" timeUnit="s" volumeUnit="ml" areaUnit="m²" lengthUnit="m" quantityUnit="mmol" type="deterministic" avogadroConstant="6.0221417899999999e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2012-08-31T17:02:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <dcterms:creator>
      <rdf:Description>
        <vCard:EMAIL>pmendes@uchc.edu</vCard:EMAIL>
        <vCard:N>
          <rdf:Description>
            <vCard:Family>Mendes</vCard:Family>
            <vCard:Given>Pedro</vCard:Given>
          </rdf:Description>
        </vCard:N>
        <vCard:ORG>
          <rdf:Description>
            <vCard:Orgname>University of Connecticut School of Medicine</vCard:Orgname>
          </rdf:Description>
        </vCard:ORG>
      </rdf:Description>
    </dcterms:creator>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml"><h1>Schaffer F7(40) function</h1>
<p>Part of a set of benchmark functions for global optimisation</p>
<ul>
 <li>variables: 40</li>
 <li>interval: [-100,100] (all variables)</li>
 <li>global minimum: (0,...,0)</li>
 <li>minimum value: 0</li>
</ul>
<p>f(x<sub>1</sub>,x<sub>2</sub>)=  
( 1/39 *
  SUM(i=1,39)
    ( 1 + 
      sin(50*
        (sqrt(x<sub>i</sub><sup>2</sup>+x<sub>i+1</sub><sup>2</sup>))<sup>0.2</sup>)
    *
    sqrt( sqrt(x<sub>i</sub><sup>2</sup>+x<sub>i+1</sub><sup>2</sup>) )
)<sup>2</sup>
</p><hr />
<p>The Schaffer F7 function is difficult because to reach the global minimum concentric barriers need to be overcome. which are higher closer to the minimum. There are local minima everywhere in the search space. This function is a good test for escaping local minima. This is the 40-dimensional version of the function.</p>
<p>Defined in: Schaffer, J.D. (1985) <i>Some experiments in machine learning using vector evaluated genetic algorithms</i> PhD Thesis, Vanderbilt University, Nashville, TN (USA).</p>
<p style="font-size:small"><b>CC0 1.0 Universal</b>: To the extent possible under law, all copyright and related or neighbouring rights to this encoded model have been dedicated to the public domain worldwide. You can copy, modify, distribute and perform the work, even for commercial purposes, all without asking permission. Please refer to <a href="http://creativecommons.org/publicdomain/zero/1.0/" title="Creative Commons CC0">CC0 Public Domain Dedication</a> for more information.</p>
</body>
    </Comment>
    <ListOfModelValues>
      <ModelValue key="ModelValue_4" name="x1" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_4">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2012-08-31T17:29:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_7" name="x2" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_7">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2012-08-31T17:02:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_6" name="Schaffer F7(40) function" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_6">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2012-08-31T17:02:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (1/39*((1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x1],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x2],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x1],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x2],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x2],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x3],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x2],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x3],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x3],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x4],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x3],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x4],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x4],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x5],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x4],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x5],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x5],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x6],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x5],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x6],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x6],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x7],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x6],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x7],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x7],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x8],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x7],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x8],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x8],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x9],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x8],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x9],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x9],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x10],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x9],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x10],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x10],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x11],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x10],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x11],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x11],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x12],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x11],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x12],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x12],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x13],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x12],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x13],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x13],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x14],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x13],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x14],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x14],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x15],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x14],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x15],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x15],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x16],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x15],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x16],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x16],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x17],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x16],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x17],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x17],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x18],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x17],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x18],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x18],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x19],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x18],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x19],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x19],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x20],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x19],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x20],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x20],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x21],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x20],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x21],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x21],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x22],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x21],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x22],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x22],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x23],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x22],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x23],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x23],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x24],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x23],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x24],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x24],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x25],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x24],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x25],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x25],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x26],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x25],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x26],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x26],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x27],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x26],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x27],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x27],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x28],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x27],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x28],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x28],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x29],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x28],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x29],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x29],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x30],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x29],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x30],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x30],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x31],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x30],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x31],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x31],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x32],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x31],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x32],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x32],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x33],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x32],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x33],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x33],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x34],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x33],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x34],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x34],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x35],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x34],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x35],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x35],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x36],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x35],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x36],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x36],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x37],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x36],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x37],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x37],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x38],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x37],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x38],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x38],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x39],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x38],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x39],Reference=InitialValue>^2))+(1+sin(50*sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x39],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x40],Reference=InitialValue>^2)^0.2)^2)*sqrt(sqrt(&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x39],Reference=InitialValue>^2+&lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[x40],Reference=InitialValue>^2))))^2
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_8" name="x3" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_8">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_11" name="x4" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_11">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_12" name="x5" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_12">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_13" name="x6" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_13">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_14" name="x7" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_14">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_15" name="x8" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_15">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_16" name="x9" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_16">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_17" name="x10" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_17">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_18" name="x11" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_18">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_19" name="x12" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_19">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_20" name="x13" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_20">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_21" name="x14" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_21">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_22" name="x15" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_22">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_23" name="x16" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_23">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_24" name="x17" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_24">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_25" name="x18" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_25">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_26" name="x19" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_26">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_27" name="x20" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_27">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_28" name="x21" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_28">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_29" name="x22" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_29">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_30" name="x23" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_30">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_31" name="x24" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_31">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_32" name="x25" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_32">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_33" name="x26" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_33">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_34" name="x27" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_34">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_35" name="x28" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_35">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_36" name="x29" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_36">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_37" name="x30" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_37">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_38" name="x31" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_38">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_39" name="x32" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_39">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_40" name="x33" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_40">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_41" name="x34" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_41">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_42" name="x35" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_42">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_43" name="x36" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_43">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_44" name="x37" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_44">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_45" name="x38" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_45">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_46" name="x39" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_46">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_47" name="x40" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_47">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
    </ListOfModelValues>
    <ListOfModelParameterSets activeSet="ModelParameterSet_0">
      <ModelParameterSet key="ModelParameterSet_0" name="Initial State">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelParameterSet_0">
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x1]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x2]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[Schaffer F7(40) function]" value="0" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x3]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x4]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x5]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x6]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x7]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x8]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x9]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x10]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x11]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x12]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x13]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x14]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x15]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x16]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x17]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x18]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x19]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x20]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x21]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x22]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x23]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x24]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x25]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x26]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x27]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x28]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x29]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x30]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x31]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x32]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x33]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x34]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x35]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x36]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x37]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x38]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x39]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x40]" value="0" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_0"/>
      <StateTemplateVariable objectReference="ModelValue_6"/>
      <StateTemplateVariable objectReference="ModelValue_4"/>
      <StateTemplateVariable objectReference="ModelValue_7"/>
      <StateTemplateVariable objectReference="ModelValue_8"/>
      <StateTemplateVariable objectReference="ModelValue_11"/>
      <StateTemplateVariable objectReference="ModelValue_12"/>
      <StateTemplateVariable objectReference="ModelValue_13"/>
      <StateTemplateVariable objectReference="ModelValue_14"/>
      <StateTemplateVariable objectReference="ModelValue_15"/>
      <StateTemplateVariable objectReference="ModelValue_16"/>
      <StateTemplateVariable objectReference="ModelValue_17"/>
      <StateTemplateVariable objectReference="ModelValue_18"/>
      <StateTemplateVariable objectReference="ModelValue_19"/>
      <StateTemplateVariable objectReference="ModelValue_20"/>
      <StateTemplateVariable objectReference="ModelValue_21"/>
      <StateTemplateVariable objectReference="ModelValue_22"/>
      <StateTemplateVariable objectReference="ModelValue_23"/>
      <StateTemplateVariable objectReference="ModelValue_24"/>
      <StateTemplateVariable objectReference="ModelValue_25"/>
      <StateTemplateVariable objectReference="ModelValue_26"/>
      <StateTemplateVariable objectReference="ModelValue_27"/>
      <StateTemplateVariable objectReference="ModelValue_28"/>
      <StateTemplateVariable objectReference="ModelValue_29"/>
      <StateTemplateVariable objectReference="ModelValue_30"/>
      <StateTemplateVariable objectReference="ModelValue_31"/>
      <StateTemplateVariable objectReference="ModelValue_32"/>
      <StateTemplateVariable objectReference="ModelValue_33"/>
      <StateTemplateVariable objectReference="ModelValue_34"/>
      <StateTemplateVariable objectReference="ModelValue_35"/>
      <StateTemplateVariable objectReference="ModelValue_36"/>
      <StateTemplateVariable objectReference="ModelValue_37"/>
      <StateTemplateVariable objectReference="ModelValue_38"/>
      <StateTemplateVariable objectReference="ModelValue_39"/>
      <StateTemplateVariable objectReference="ModelValue_40"/>
      <StateTemplateVariable objectReference="ModelValue_41"/>
      <StateTemplateVariable objectReference="ModelValue_42"/>
      <StateTemplateVariable objectReference="ModelValue_43"/>
      <StateTemplateVariable objectReference="ModelValue_44"/>
      <StateTemplateVariable objectReference="ModelValue_45"/>
      <StateTemplateVariable objectReference="ModelValue_46"/>
      <StateTemplateVariable objectReference="ModelValue_47"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_0" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_7" target="" append="1" confirmOverwrite="0"/>
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
        <Parameter name="Target Criterion" type="string" value="Distance and Rate"/>
      </Method>
    </Task>
    <Task key="Task_10" name="Time-Course" type="timeCourse" scheduled="false" updateModel="false">
      <Report reference="Report_23" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="1"/>
        <Parameter name="StepSize" type="float" value="1"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
        <Parameter name="Use Values" type="bool" value="0"/>
        <Parameter name="Values" type="string" value=""/>
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
    <Task key="Task_4" name="Scan" type="scan" scheduled="true" updateModel="false">
      <Report reference="Report_8" target="SchafferF7_40Function.txt" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="4"/>
        <ParameterGroup name="ScanItems">
          <ParameterGroup name="ScanItem">
            <Parameter name="Maximum" type="float" value="100"/>
            <Parameter name="Minimum" type="float" value="-100"/>
            <Parameter name="Number of steps" type="unsignedInteger" value="500"/>
            <Parameter name="Object" type="cn" value=""/>
            <Parameter name="Type" type="unsignedInteger" value="0"/>
            <Parameter name="log" type="bool" value="0"/>
          </ParameterGroup>
        </ParameterGroup>
        <Parameter name="Output in subtask" type="bool" value="0"/>
        <Parameter name="Adjust initial conditions" type="bool" value="0"/>
        <Parameter name="Continue on Error" type="bool" value="0"/>
      </Problem>
      <Method name="Scan Framework" type="ScanFramework">
      </Method>
    </Task>
    <Task key="Task_14" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_6" target="" append="1" confirmOverwrite="0"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_13" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_5" target="" append="0" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Subtask" type="cn" value="CN=Root,Vector=TaskList[Time-Course]"/>
        <ParameterText name="ObjectiveExpression" type="expression">
          &lt;CN=Root,Model=Schaffer F7(40) function,Vector=Values[Schaffer F7(40) function],Reference=InitialValue>
        </ParameterText>
        <Parameter name="Maximize" type="bool" value="0"/>
        <Parameter name="Randomize Start Values" type="bool" value="1"/>
        <Parameter name="Calculate Statistics" type="bool" value="0"/>
        <ParameterGroup name="OptimizationItemList">
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x1],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="5.0609269113935271"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x2],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="0.59780538618135015"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x3],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="69.209673674992658"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x4],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="9.9987063303640848"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x5],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="15.55761372612991"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x6],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="13.800799395823841"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x7],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="12.81006525464335"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x8],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="37.442996055814909"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x9],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="11.58858888077234"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x10],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="90.402913811149986"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x11],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="20.07848578069683"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x12],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-13.19435579068127"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x13],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="58.535021626715732"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x14],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="33.728819606763608"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x15],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-32.986458737759037"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x16],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="50.714289572650479"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x17],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-15.3049242300225"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x18],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-13.05223277015771"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x19],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="74.723101035988492"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x20],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-8.0615535425210751"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x21],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-42.196117311502753"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x22],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-61.540223888393562"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x23],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="41.816122401438747"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x24],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-83.481243511416039"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x25],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-48.748172033025909"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x26],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-18.385255935688011"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x27],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-50.046111728149853"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x28],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-62.816724827241814"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x29],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-23.486252225916441"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x30],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="14.97090663439988"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x31],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="43.889314574468173"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x32],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="32.976278735386892"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x33],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="48.892501311953872"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x34],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-7.3966156166787931"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x35],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-22.366554128921599"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x36],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="30.453183550322631"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x37],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-35.249035434911768"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x38],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="71.987612047604117"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x39],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-11.29558816417252"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x40],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="40.852533612819741"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
        </ParameterGroup>
      </Problem>
      <Method name="Genetic Algorithm" type="GeneticAlgorithm">
        <Parameter name="Log Verbosity" type="unsignedInteger" value="0"/>
        <Parameter name="Number of Generations" type="unsignedInteger" value="200"/>
        <Parameter name="Population Size" type="unsignedInteger" value="20"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
        <Parameter name="Mutation Variance" type="float" value="0.10000000000000001"/>
        <Parameter name="Stop after # Stalled Generations" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_8" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_4" target="" append="1" confirmOverwrite="0"/>
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
        <Parameter name="Use Time Sens" type="bool" value="0"/>
        <Parameter name="Time-Sens" type="cn" value=""/>
        <ParameterGroup name="Experiment Set">
        </ParameterGroup>
        <ParameterGroup name="Validation Set">
          <Parameter name="Weight" type="unsignedFloat" value="1"/>
          <Parameter name="Threshold" type="unsignedInteger" value="5"/>
        </ParameterGroup>
      </Problem>
      <Method name="Evolutionary Programming" type="EvolutionaryProgram">
        <Parameter name="Log Verbosity" type="unsignedInteger" value="0"/>
        <Parameter name="Number of Generations" type="unsignedInteger" value="200"/>
        <Parameter name="Population Size" type="unsignedInteger" value="20"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
        <Parameter name="Stop after # Stalled Generations" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_7" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_3" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_0"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1.0000000000000001e-09"/>
        <Parameter name="Use Reder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
      </Method>
    </Task>
    <Task key="Task_6" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_2" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_5" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_1" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_2" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_0" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_12" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Report reference="Report_12" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_9" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_22" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_0"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
    <Task key="Task_15" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
        <Parameter name="Use Values" type="bool" value="0"/>
        <Parameter name="Values" type="string" value=""/>
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
        <Parameter name="LimitTime" type="bool" value="1"/>
        <Parameter name="TimeLimit" type="float" value="100"/>
      </Problem>
      <Method name="Cross Section Finder" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_11" name="Time-Course Sensitivities" type="timeSensitivities" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="100"/>
        <Parameter name="StepSize" type="float" value="0.01"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
        <Parameter name="Use Values" type="bool" value="0"/>
        <Parameter name="Values" type="string" value=""/>
        <ParameterGroup name="ListOfParameters">
        </ParameterGroup>
        <ParameterGroup name="ListOfTargets">
        </ParameterGroup>
      </Problem>
      <Method name="LSODA Sensitivities" type="Sensitivities(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_8" name="Optimization profile" taskType="scan" separator="&#x09;" precision="12">
      <Comment>
        This table outputs time and the target function of the optimization.
      </Comment>
      <Header>
        <Object cn="String=&#x0a;Schaffer F7(40) function&#x0a;\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=&#x0a;"/>
        <Object cn="String=time"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="String=CPU time"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="String=Optimum"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="String=Feval"/>
      </Header>
      <Body>
        <Object cn="CN=Root,Timer=Wall Clock Time"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,Timer=CPU Time"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Value"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations"/>
      </Body>
    </Report>
    <Report key="Report_7" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_6" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_5" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_4" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_3" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_2" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <Report key="Report_1" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_0" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_22" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <Report key="Report_23" name="Time-Course" taskType="timeCourse" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Time-Course],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Time-Course],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_12" name="Moieties" taskType="moieties" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Header>
        <Object cn="CN=Root,Vector=TaskList[Moieties],Object=Description"/>
      </Header>
      <Footer>
        <Object cn="String=&#x0a;"/>
        <Object cn="CN=Root,Vector=TaskList[Moieties],Object=Result"/>
      </Footer>
    </Report>
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="Progress of Optimization" type="Plot2D" active="1" taskTypes="">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="1"/>
      <ListOfPlotItems>
        <PlotItem name="target function" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations"/>
            <ChannelSpec cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Value"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
    <PlotSpecification name="Create New" type="Plot2D" active="1" taskTypes="">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="Values[y].InitialValue/Values[f].InitialValue|Values[x].InitialValue" type="Spectogram">
          <Parameter name="logZ" type="bool" value="0"/>
          <Parameter name="bilinear" type="bool" value="1"/>
          <Parameter name="contours" type="string" value=""/>
          <Parameter name="maxZ" type="string" value=""/>
          <Parameter name="colorMap" type="string" value="Default"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x1],Reference=InitialValue"/>
            <ChannelSpec cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x2],Reference=InitialValue"/>
            <ChannelSpec cn="CN=Root,Model=Schaffer F7(40) function,Vector=Values[Schaffer F7(40) function],Reference=InitialValue"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
  </ListOfPlots>
  <GUI>
  </GUI>
  <ListOfUnitDefinitions>
    <UnitDefinition key="Unit_1" name="meter" symbol="m">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_0">
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        m
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_5" name="second" symbol="s">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_4">
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        s
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_13" name="Avogadro" symbol="Avogadro">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_12">
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Avogadro
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_17" name="item" symbol="#">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_16">
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        #
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_35" name="liter" symbol="l">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_34">
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        0.001*m^3
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_41" name="mole" symbol="mol">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_40">
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Avogadro*#
      </Expression>
    </UnitDefinition>
  </ListOfUnitDefinitions>
</COPASI>
