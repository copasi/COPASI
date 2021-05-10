<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.29 (Build 228) (http://www.copasi.org) at 2021-01-03T18:56:24Z -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="29" versionDevel="228" copasiSourcesModified="0">
  <Model key="Model_1" name="Weierstrass function" simulationType="time" timeUnit="s" volumeUnit="ml" areaUnit="m²" lengthUnit="m" quantityUnit="mmol" type="deterministic" avogadroConstant="6.0221417899999999e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_1">
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
            <vCard:Orgname>University of Connecticut</vCard:Orgname>
          </rdf:Description>
        </vCard:ORG>
      </rdf:Description>
    </dcterms:creator>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml"><h1>Weierstrass function</h1>
<p>Part of a set of benchmark functions for global optimisation</p>
<ul>
 <li>variables: 2</li>
 <li>interval: [-0.5,0.5] (all variables)</li>
 <li>global minimum: (0,0)</li>
 <li>minimum value: 4</li>
</ul>
<p>f(x<sub>1</sub>,x<sub>2</sub>)=- SUM(i=1,2)( 
SUM(k=0,20)(a<sup>k</sup> cos( 2 &amp;amp;amp;pi; b<sup>k</sup> (x<sub>1</sub> + 0.5) ) )
- 2 * SUM(k=0,20)( a<sup>k</sup> cos( &amp;amp;amp;pi; b<sup>k</sup>) )
)
</p>
<p>with a=0.5 and b=3</p>
<hr />
<p>The Weierstrass function is highly rugged and moderately repetitive. It has several global minima (but only one in the domain considered here). The function has a near-fractal structure. Weierstrass developed this function and it was the first function shown to be continuous everywhere and differentiable nowhere. This function is a good test for rugged and repetitive landscapes. Since it is non-differentiable, it cannot be used with gradient-based algorithms.</p>
<p>Defined in: Mishra, S.K. (2006) Some new test functions for global optimization and performance of repulsive particle swarm method. <i>Munich Personal RePEc Archive</i> paper 2718 (<a href="http://mpra.ub.uni-muenchen.de/2718/">http://mpra.ub.uni-muenchen.de/2718/</a>).</p>
</body>
    </Comment>
    <ListOfModelValues>
      <ModelValue key="ModelValue_28" name="x1" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_28">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2012-08-31T17:29:26Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_44" name="x2" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_44">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2012-08-31T17:02:24Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_45" name="Weierstrass function" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#ModelValue_45">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2012-08-31T17:02:23Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          cos(2*pi*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^2*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^2*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^3*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^3*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^4*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^4*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^5*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^5*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^6*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^6*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^7*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^7*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^8*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^8*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^9*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^9*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^10*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^10*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^11*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^11*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^12*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^12*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^13*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^13*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^14*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^14*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^15*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^15*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^16*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^16*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^17*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^17*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^18*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^18*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^19*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^19*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^20*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^20*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))-2*(cos(pi)+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>)+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^2*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^2)+0.5^3*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^3)+0.5^4*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^4)+0.5^5*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^5)+0.5^6*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^6)+0.5^7*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^7)+0.5^8*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^8)+0.5^9*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^9)+0.5^10*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^10)+0.5^11*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^11)+0.5^12*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^12)+0.5^13*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^13)+0.5^14*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^14)+0.5^15*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^15)+0.5^16*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^16)+0.5^17*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^17)+0.5^18*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^18)+0.5^19*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^19)+0.5^20*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^20))+cos(2*pi*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^2*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^2*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^3*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^3*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^4*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^4*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^5*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^5*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^6*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^6*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^7*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^7*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^8*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^8*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^9*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^9*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^10*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^10*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^11*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^11*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^12*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^12*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^13*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^13*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^14*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^14*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^15*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^15*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^16*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^16*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^17*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^17*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^18*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^18*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^19*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^19*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue>+0.5))+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^20*cos(2*pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^20*(&lt;CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue>+0.5))-2*(cos(pi)+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>)+&lt;CN=Root,Model=Weierstrass function,Vector=Values[a],Reference=InitialValue>^2*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^2)+0.5^3*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^3)+0.5^4*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^4)+0.5^5*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^5)+0.5^6*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^6)+0.5^7*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^7)+0.5^8*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^8)+0.5^9*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^9)+0.5^10*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^10)+0.5^11*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^11)+0.5^12*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^12)+0.5^13*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^13)+0.5^14*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^14)+0.5^15*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^15)+0.5^16*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^16)+0.5^17*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^17)+0.5^18*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^18)+0.5^19*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^19)+0.5^20*cos(pi*&lt;CN=Root,Model=Weierstrass function,Vector=Values[b],Reference=InitialValue>^20))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_46" name="a" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_46">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-03T14:29:18Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_47" name="b" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_47">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-03T14:29:18Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
    </ListOfModelValues>
    <ListOfModelParameterSets activeSet="ModelParameterSet_1">
      <ModelParameterSet key="ModelParameterSet_1" name="Initial State">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelParameterSet_1">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-03T18:49:46Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Weierstrass function" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Weierstrass function,Vector=Values[x1]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weierstrass function,Vector=Values[x2]" value="0" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weierstrass function,Vector=Values[Weierstrass function]" value="3.9999980926513672" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Weierstrass function,Vector=Values[a]" value="0.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Weierstrass function,Vector=Values[b]" value="3" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_1"/>
      <StateTemplateVariable objectReference="ModelValue_45"/>
      <StateTemplateVariable objectReference="ModelValue_28"/>
      <StateTemplateVariable objectReference="ModelValue_44"/>
      <StateTemplateVariable objectReference="ModelValue_46"/>
      <StateTemplateVariable objectReference="ModelValue_47"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 3.9999980926513672 0 0 0.5 3 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_15" name="Steady-State" type="steadyState" scheduled="false" updateModel="false">
      <Report reference="Report_22" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_27" name="Time-Course" type="timeCourse" scheduled="false" updateModel="false">
      <Report reference="Report_13" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_26" name="Scan" type="scan" scheduled="true" updateModel="false">
      <Report reference="Report_25" target="Weierstrass_opt-sres.out" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="4"/>
        <ParameterGroup name="ScanItems">
          <ParameterGroup name="ScanItem">
            <Parameter name="Maximum" type="float" value="10"/>
            <Parameter name="Minimum" type="float" value="-10"/>
            <Parameter name="Number of steps" type="unsignedInteger" value="100"/>
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
    <Task key="Task_25" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_21" target="" append="1" confirmOverwrite="0"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_24" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_20" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Subtask" type="cn" value="CN=Root,Vector=TaskList[Time-Course]"/>
        <ParameterText name="ObjectiveExpression" type="expression">
          &lt;CN=Root,Model=Weierstrass function,Vector=Values[Weierstrass function],Reference=InitialValue>
        </ParameterText>
        <Parameter name="Maximize" type="bool" value="0"/>
        <Parameter name="Randomize Start Values" type="bool" value="1"/>
        <Parameter name="Calculate Statistics" type="bool" value="0"/>
        <ParameterGroup name="OptimizationItemList">
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-0.5"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="0.2963957255232138"/>
            <Parameter name="UpperBound" type="cn" value="0.5"/>
          </ParameterGroup>
          <ParameterGroup name="OptimizationItem">
            <Parameter name="LowerBound" type="cn" value="-0.5"/>
            <Parameter name="ObjectCN" type="cn" value="CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=InitialValue"/>
            <Parameter name="StartValue" type="float" value="-0.48349252878303933"/>
            <Parameter name="UpperBound" type="cn" value="0.5"/>
          </ParameterGroup>
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
        </ParameterGroup>
      </Problem>
      <Method name="Evolution Strategy (SRES)" type="EvolutionaryStrategySR">
        <Parameter name="Log Verbosity" type="unsignedInteger" value="0"/>
        <Parameter name="Number of Generations" type="unsignedInteger" value="150"/>
        <Parameter name="Population Size" type="unsignedInteger" value="20"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
        <Parameter name="Pf" type="float" value="0.47499999999999998"/>
        <Parameter name="Stop after # Stalled Generations" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_23" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_19" target="" append="1" confirmOverwrite="0"/>
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
      <Method name="Genetic Algorithm" type="GeneticAlgorithm">
        <Parameter name="Log Verbosity" type="unsignedInteger" value="0"/>
        <Parameter name="Number of Generations" type="unsignedInteger" value="500"/>
        <Parameter name="Population Size" type="unsignedInteger" value="20"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
        <Parameter name="Mutation Variance" type="float" value="0.10000000000000001"/>
        <Parameter name="Stop after # Stalled Generations" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_22" name="Metabolic Control Analysis" type="metabolicControlAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_18" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_15"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1.0000000000000001e-09"/>
        <Parameter name="Use Reder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
      </Method>
    </Task>
    <Task key="Task_21" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_17" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_20" name="Time Scale Separation Analysis" type="timeScaleSeparationAnalysis" scheduled="false" updateModel="false">
      <Report reference="Report_16" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_19" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_15" target="" append="1" confirmOverwrite="0"/>
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
    <Task key="Task_18" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Report reference="Report_10" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_17" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_14" target="" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_15"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
    <Task key="Task_16" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
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
    <Task key="Task_28" name="Time-Course Sensitivities" type="timeSensitivities" scheduled="false" updateModel="false">
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
    <Report key="Report_24" name="Optimization profile" taskType="scan" separator="&#x09;" precision="12">
      <Comment>
        This table outputs time and the target function of the optimization.
      </Comment>
      <Header>
        <Object cn="String=&#x0a;Weierstrass Function&#x0a;\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=\=&#x0a;"/>
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
    <Report key="Report_22" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_21" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_20" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_19" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_18" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_17" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <Report key="Report_16" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_15" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_14" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <Report key="Report_13" name="Time-Course" taskType="timeCourse" separator="&#x09;" precision="6">
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
    <Report key="Report_10" name="Moieties" taskType="moieties" separator="&#x09;" precision="6">
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
    <Report key="Report_25" name="Speed test (scan)" taskType="scan" separator="&#x09;" precision="8">
      <Comment>
      </Comment>
      <Header>
        <Object cn="CN=Root,CN=Information,String=COPASI Version"/>
        <Object cn="Separator=&#x09;"/>
        <Object cn="CN=Root,CN=Information,Timer=Current Date/Time"/>
      </Header>
      <Footer>
        <Object cn="CN=Root,Timer=CPU Time"/>
      </Footer>
    </Report>
  </ListOfReports>
  <ListOfPlots>
    <PlotSpecification name="Progress of Optimization" type="Plot2D" active="1" taskTypes="">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="1"/>
      <ListOfPlotItems>
        <PlotItem name="target function" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="2"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="1"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations"/>
            <ChannelSpec cn="CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Value"/>
          </ListOfChannels>
        </PlotItem>
      </ListOfPlotItems>
    </PlotSpecification>
    <PlotSpecification name="minima estimates" type="Plot2D" active="1" taskTypes="">
      <Parameter name="log X" type="bool" value="0"/>
      <Parameter name="log Y" type="bool" value="0"/>
      <ListOfPlotItems>
        <PlotItem name="best value" type="Curve2D">
          <Parameter name="Line type" type="unsignedInteger" value="2"/>
          <Parameter name="Line subtype" type="unsignedInteger" value="0"/>
          <Parameter name="Line width" type="unsignedFloat" value="1"/>
          <Parameter name="Symbol subtype" type="unsignedInteger" value="1"/>
          <Parameter name="Color" type="string" value="auto"/>
          <Parameter name="Recording Activity" type="string" value="during"/>
          <ListOfChannels>
            <ChannelSpec cn="CN=Root,Model=Weierstrass function,Vector=Values[x1],Reference=Value"/>
            <ChannelSpec cn="CN=Root,Model=Weierstrass function,Vector=Values[x2],Reference=Value"/>
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
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-03T14:10:41Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
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
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-03T14:10:41Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
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
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-03T14:10:41Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
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
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-03T14:10:41Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
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
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-03T14:10:41Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
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
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2021-01-03T14:10:41Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Avogadro*#
      </Expression>
    </UnitDefinition>
  </ListOfUnitDefinitions>
</COPASI>
