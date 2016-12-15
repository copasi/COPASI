<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.18 (Build 136) (http://www.copasi.org) at 2016-12-14 21:03:15 UTC -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="18" versionDevel="136" copasiSourcesModified="0">
  <Model key="Model_9" name="Schaffer F7(40) function" simulationType="time" timeUnit="s" volumeUnit="ml" areaUnit="m²" lengthUnit="m" quantityUnit="mmol" type="deterministic" avogadroConstant="6.02214179e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Model_9">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2012-08-31T17:02:03Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
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
</body>
    </Comment>
    <ListOfModelValues>
      <ModelValue key="ModelValue_0" name="x1" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_0">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2012-08-31T17:29:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>

        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_1" name="x2" simulationType="fixed">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_1">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2012-08-31T17:02:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_2" name="Schaffer F7(40) function" simulationType="assignment">
        <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_2">
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
      <ModelValue key="ModelValue_6" name="x3" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_7" name="x4" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_8" name="x5" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_9" name="x6" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_10" name="x7" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_11" name="x8" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_12" name="x9" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_13" name="x10" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_14" name="x11" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_15" name="x12" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_16" name="x13" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_17" name="x14" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_18" name="x15" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_19" name="x16" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_20" name="x17" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_21" name="x18" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_22" name="x19" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_23" name="x20" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_3" name="x21" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_4" name="x22" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_5" name="x23" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_24" name="x24" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_25" name="x25" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_26" name="x26" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_27" name="x27" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_28" name="x28" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_29" name="x29" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_30" name="x30" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_31" name="x31" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_32" name="x32" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_33" name="x33" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_34" name="x34" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_35" name="x35" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_36" name="x36" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_37" name="x37" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_38" name="x38" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_39" name="x39" simulationType="fixed">
      </ModelValue>
      <ModelValue key="ModelValue_40" name="x40" simulationType="fixed">
      </ModelValue>
    </ListOfModelValues>
    <ListOfModelParameterSets activeSet="ModelParameterSet_1">
      <ModelParameterSet key="ModelParameterSet_1" name="Initial State">
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
      <StateTemplateVariable objectReference="Model_9"/>
      <StateTemplateVariable objectReference="ModelValue_2"/>
      <StateTemplateVariable objectReference="ModelValue_0"/>
      <StateTemplateVariable objectReference="ModelValue_1"/>
      <StateTemplateVariable objectReference="ModelValue_6"/>
      <StateTemplateVariable objectReference="ModelValue_7"/>
      <StateTemplateVariable objectReference="ModelValue_8"/>
      <StateTemplateVariable objectReference="ModelValue_9"/>
      <StateTemplateVariable objectReference="ModelValue_10"/>
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
      <StateTemplateVariable objectReference="ModelValue_3"/>
      <StateTemplateVariable objectReference="ModelValue_4"/>
      <StateTemplateVariable objectReference="ModelValue_5"/>
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
    </StateTemplate>
    <InitialState type="initialState">
      0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_14" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_15" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_25" name="Time-Course" type="timeCourse" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="AutomaticStepSize" type="bool" value="0"/>
        <Parameter name="StepNumber" type="unsignedInteger" value="1"/>
        <Parameter name="StepSize" type="float" value="1"/>
        <Parameter name="Duration" type="float" value="1"/>
        <Parameter name="TimeSeriesRequested" type="bool" value="1"/>
        <Parameter name="OutputStartTime" type="float" value="0"/>
        <Parameter name="Output Event" type="bool" value="0"/>
        <Parameter name="Start in Steady State" type="bool" value="0"/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
    <Task key="Task_24" name="Scan" type="scan" scheduled="true" updateModel="false">
      <Report reference="Report_16" target="SchafferF7_40Function.txt" append="1" confirmOverwrite="0"/>
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
      </Problem>
      <Method name="Scan Framework" type="ScanFramework">
      </Method>
    </Task>
    <Task key="Task_23" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_14" target="" append="1" confirmOverwrite="0"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_22" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_13" target="" append="0" confirmOverwrite="0"/>
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
            <Parameter name="StartValue" type="float" value="5.060926911393527"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x2],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="0.5978053861813502"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x3],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="69.20967367499266"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x4],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="9.998706330364085"/>
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
            <Parameter name="StartValue" type="float" value="13.80079939582384"/>
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
            <Parameter name="StartValue" type="float" value="37.44299605581491"/>
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
            <Parameter name="StartValue" type="float" value="90.40291381114999"/>
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
            <Parameter name="StartValue" type="float" value="58.53502162671573"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x14],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="33.72881960676361"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x15],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-32.98645873775904"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x16],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="50.71428957265048"/>
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
            <Parameter name="StartValue" type="float" value="74.72310103598849"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x20],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-8.061553542521075"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x21],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-42.19611731150275"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x22],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-61.54022388839356"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x23],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="41.81612240143875"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x24],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-83.48124351141604"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x25],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-48.74817203302591"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x26],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-18.38525593568801"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x27],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-50.04611172814985"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x28],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-62.81672482724181"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x29],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-23.48625222591644"/>
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
            <Parameter name="StartValue" type="float" value="43.88931457446817"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x32],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="32.97627873538689"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x33],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="48.89250131195387"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x34],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-7.396615616678793"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x35],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-22.3665541289216"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x36],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="30.45318355032263"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x37],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-35.24903543491177"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-100"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Schaffer F7(40) function,Vector=Values[x38],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="71.98761204760412"/>
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
            <Parameter name="StartValue" type="float" value="40.85253361281974"/>
            <Parameter name="UpperBound" type="cn" value="100"/>
          </ParameterGroup>
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
        </ParameterGroup>
      </Problem>
      <Method name="Genetic Algorithm" type="GeneticAlgorithm">
        <Parameter name="Number of Generations" type="unsignedInteger" value="200"/>
        <Parameter name="Population Size" type="unsignedInteger" value="20"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_21" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_12" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_20" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_11" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_14"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1e-09"/>
        <Parameter name="Use Reder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
      </Method>
    </Task>
    <Task key="Task_19" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_10" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_18" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_9" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_17" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_18" target="" append="1" confirmOverwrite="0"/>
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
        <Parameter name="Delta minimum" type="unsignedFloat" value="1e-12"/>
      </Method>
    </Task>
    <Task key="Task_16" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_15" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_19" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_14"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
    <Task key="Task_26" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
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
        <Parameter name="ConvergenceTolerance" type="float" value="1e-06"/>
        <Parameter name="Threshold" type="float" value="0"/>
        <Parameter name="DelayOutputUntilConvergence" type="bool" value="0"/>
        <Parameter name="OutputConvergenceTolerance" type="float" value="1e-06"/>
        <ParameterText name="TriggerExpression" type="expression">
          
        </ParameterText>
        <Parameter name="SingleVariable" type="cn" value=""/>
        <Parameter name="Continue on Simultaneous Events" type="bool" value="0"/>
        <Parameter name="LimitTime" type="bool" value="1"/>
        <Parameter name="TimeLimit" type="float" value="100"/>
      </Problem>
      <Method name="Cross Section Finder" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="1e-06"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="1e-12"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
      </Method>
    </Task>
  </ListOfTasks>
  <ListOfReports>
    <Report key="Report_16" name="Optimization profile" taskType="scan" separator="&#x09;" precision="12">
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
    <Report key="Report_15" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_14" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_13" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_12" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_11" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_10" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <Report key="Report_9" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_18" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_19" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="Progress of Optimization" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="1"/>
      <ListOfPlotItems>
        <PlotItem name="target function" type="Curve2D">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line type" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="0"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations"/>
            <ChannelSpec cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Value"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
    <PlotSpecification name="Create New" type="Plot2D" active="1">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="Values[y].InitialValue/Values[f].InitialValue|Values[x].InitialValue" type="Spectogram">
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <Parameter name="bilinear" type="bool" value="1"/>
          <Parameter name="colorMap" type="string" value="Default"/>
          <Parameter name="contours" type="string" value=""/>
          <Parameter name="logZ" type="bool" value="0"/>
          <Parameter name="maxZ" type="string" value=""/>
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
  </ListOfUnitDefinitions>
</COPASI>
