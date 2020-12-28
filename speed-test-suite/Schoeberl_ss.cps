<?xml version="1.0" encoding="UTF-8"?>
<!-- generated with COPASI 4.30 (Build 236) (http://www.copasi.org) at 2020-12-28T15:19:48Z -->
<?oxygen RNGSchema="http://www.copasi.org/static/schema/CopasiML.rng" type="xml"?>
<COPASI xmlns="http://www.copasi.org/static/schema" versionMajor="4" versionMinor="30" versionDevel="236" copasiSourcesModified="0">
  <ListOfFunctions>
    <Function key="Function_40" name="Function for v5" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Function_40">
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2014-09-30T13:30:10Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
  </rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k5*(x7*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_264" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_263" name="k5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_262" name="x7" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_41" name="Function for v1" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_41">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k1*(x1*c1)*(x2*c1)-kr1*(x3*c2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_265" name="c1" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_250" name="c2" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_261" name="k1" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_266" name="kr1" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_267" name="x1" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_268" name="x2" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_269" name="x3" order="6" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_42" name="Function for v2" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_42">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k2*(x3*c2)*(x3*c2)-kr2*(x4*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_276" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_275" name="k2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_274" name="kr2" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_273" name="x3" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_272" name="x4" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_43" name="Function for v3" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_43">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k3*(x4*c2)-kr3*(x5*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_279" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_278" name="k3" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_277" name="kr3" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_270" name="x4" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_271" name="x5" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_44" name="Function for v4" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_44">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k4*(x23*c2)*(x12*c2)-kr4*(x7*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_284" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_283" name="k4" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_282" name="kr4" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_281" name="x12" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_280" name="x23" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_285" name="x7" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_45" name="Function for v6" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_45">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k6*(x2*c1)-kr6*(x6*c2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_291" name="c1" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_290" name="c2" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_289" name="k6" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_288" name="kr6" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_287" name="x2" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_286" name="x6" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_46" name="Function for v7" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_46">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k7*(x5*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_297" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_296" name="k7" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_295" name="x5" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_47" name="Function for v8" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_47">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k8*(x5*c2)*(x14*c2)-kr8*(x15*c3)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_292" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_293" name="c3" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_294" name="k8" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_298" name="kr8" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_299" name="x14" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_300" name="x15" order="5" role="product"/>
        <ParameterDescription key="FunctionParameter_301" name="x5" order="6" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_48" name="Function for v9" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_48">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k7*(x23*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_308" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_307" name="k7" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_306" name="x23" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_49" name="Function for v10" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_49">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k10*(x6*c2)*(x16*c2)-kr10*(x10*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_303" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_304" name="k10" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_305" name="kr10" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_302" name="x10" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_309" name="x16" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_310" name="x6" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_50" name="Function for v11" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_50">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k2*(x10*c2)*(x10*c2)-kr2*(x11*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_316" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_315" name="k2" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_314" name="kr2" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_313" name="x10" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_312" name="x11" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_51" name="Function for v12" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_51">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k3*(x11*c2)-kr3*(x8*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_320" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_319" name="k3" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_318" name="kr3" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_317" name="x11" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_311" name="x8" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_52" name="Function for v13" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_52">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k13/c1
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_325" name="c1" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_324" name="k13" order="1" role="constant"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_53" name="Function for v14" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_53">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k14*(x8*c2)*(x14*c2)-kr14*(x17*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_322" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_323" name="k14" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_321" name="kr14" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_326" name="x14" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_327" name="x17" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_328" name="x8" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_54" name="Function for v15" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_54">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k15*(x9*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_334" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_333" name="k15" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_332" name="x9" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_55" name="Function for v16" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_55">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k16*(x22*c2)*(x15*c3)-kr16*(x23*c2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_329" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_330" name="c3" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_331" name="k16" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_335" name="kr16" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_336" name="x15" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_337" name="x22" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_338" name="x23" order="6" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_56" name="Function for v17" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_56">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k17*(x24*c2)*(x23*c2)-kr17*(x25*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_345" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_344" name="k17" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_343" name="kr17" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_342" name="x23" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_341" name="x24" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_340" name="x25" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_57" name="Function for v18" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_57">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k18*(x26*c2)*(x25*c2)-kr18*(x27*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_350" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_349" name="k18" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_348" name="kr18" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_347" name="x25" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_346" name="x26" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_339" name="x27" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_58" name="Function for v19" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_58">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k19*(x27*c2)-kr19*(x28*c2)*(x25*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_356" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_355" name="k19" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_354" name="kr19" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_353" name="x25" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_352" name="x27" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_351" name="x28" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_59" name="Function for v20" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_59">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k20*(x25*c2)*(x43*c2)-kr20*(x29*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_362" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_361" name="k20" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_360" name="kr20" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_359" name="x25" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_358" name="x29" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_357" name="x43" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_60" name="Function for v21" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_60">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k21*(x29*c2)-kr21*(x25*c2)*(x26*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_368" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_367" name="k21" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_366" name="kr21" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_365" name="x25" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_364" name="x26" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_363" name="x29" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_61" name="Function for v22" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_61">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k22*(x31*c2)*(x15*c3)-kr22*(x32*c2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_374" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_373" name="c3" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_372" name="k22" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_371" name="kr22" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_370" name="x15" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_369" name="x31" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_375" name="x32" order="6" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_62" name="Function for v23" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_62">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k23*(x32*c2)-kr23*(x33*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_382" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_381" name="k23" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_380" name="kr23" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_379" name="x32" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_378" name="x33" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_63" name="Function for v24" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_63">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k24*(x22*c2)*(x33*c2)-kr24*(x34*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_385" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_384" name="k24" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_383" name="kr24" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_376" name="x22" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_377" name="x33" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_386" name="x34" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_64" name="Function for v25" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_64">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k25*(x24*c2)*(x34*c2)-kr25*(x35*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_392" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_391" name="k25" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_390" name="kr25" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_389" name="x24" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_388" name="x34" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_387" name="x35" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_65" name="Function for v26" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_65">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k18*(x26*c2)*(x35*c2)-kr18*(x36*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_398" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_397" name="k18" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_396" name="kr18" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_395" name="x26" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_394" name="x35" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_393" name="x36" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_66" name="Function for v27" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_66">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k19*(x36*c2)-kr19*(x35*c2)*(x28*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_404" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_403" name="k19" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_402" name="kr19" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_401" name="x28" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_400" name="x35" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_399" name="x36" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_67" name="Function for v28" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_67">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k28*(x28*c2)*(x41*c2)-kr28*(x42*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_410" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_409" name="k28" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_408" name="kr28" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_407" name="x28" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_406" name="x41" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_405" name="x42" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_68" name="Function for v29" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_68">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k29*(x42*c2)-kr29*(x43*c2)*(x45*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_416" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_415" name="k29" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_414" name="kr29" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_413" name="x42" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_412" name="x43" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_411" name="x45" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_69" name="Function for v30" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_69">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k20*(x35*c2)*(x43*c2)-kr20*(x37*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_422" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_421" name="k20" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_420" name="kr20" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_419" name="x35" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_418" name="x37" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_417" name="x43" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_70" name="Function for v31" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_70">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k21*(x37*c2)-kr21*(x35*c2)*(x26*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_428" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_427" name="k21" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_426" name="kr21" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_425" name="x26" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_424" name="x35" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_423" name="x37" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_71" name="Function for v32" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_71">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k32*(x35*c2)-kr32*(x15*c3)*(x38*c2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_434" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_433" name="c3" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_432" name="k32" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_431" name="kr32" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_430" name="x15" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_429" name="x35" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_435" name="x38" order="6" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_72" name="Function for v33" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_72">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k33*(x38*c2)-kr33*(x40*c2)*(x30*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_442" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_441" name="k33" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_440" name="kr33" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_439" name="x30" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_438" name="x38" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_437" name="x40" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_73" name="Function for v34" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_73">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k34*(x25*c2)-kr34*(x15*c3)*(x30*c2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_447" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_446" name="c3" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_445" name="k34" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_444" name="kr34" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_443" name="x15" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_436" name="x25" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_448" name="x30" order="6" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_74" name="Function for v35" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_74">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k35*(x30*c2)-kr35*(x24*c2)*(x22*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_455" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_454" name="k35" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_453" name="kr35" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_452" name="x22" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_451" name="x24" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_450" name="x30" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_75" name="Function for v36" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_75">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        Vm36*(x40*c2)/(Km36+x40*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_460" name="Km36" order="0" role="constant"/>
        <ParameterDescription key="FunctionParameter_459" name="Vm36" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_458" name="c2" order="2" role="volume"/>
        <ParameterDescription key="FunctionParameter_457" name="x40" order="3" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_76" name="Function for v37" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_76">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k37*(x33*c2)-kr37*(x15*c3)*(x40*c2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_462" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_461" name="c3" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_449" name="k37" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_456" name="kr37" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_463" name="x15" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_464" name="x33" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_465" name="x40" order="6" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_77" name="Function for v38" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_77">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k24*(x22*c2)*(x40*c2)-kr24*(x39*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_472" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_471" name="k24" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_470" name="kr24" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_469" name="x22" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_468" name="x39" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_467" name="x40" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_78" name="Function for v39" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_78">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k37*(x34*c2)-kr37*(x15*c3)*(x39*c2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_477" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_476" name="c3" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_475" name="k37" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_474" name="kr37" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_473" name="x15" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_466" name="x34" order="5" role="substrate"/>
        <ParameterDescription key="FunctionParameter_478" name="x39" order="6" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_79" name="Function for v40" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_79">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k40*(x24*c2)*(x39*c2)-kr40*(x38*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_485" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_484" name="k40" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_483" name="kr40" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_482" name="x24" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_481" name="x38" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_480" name="x39" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_80" name="Function for v41" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_80">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k41*(x30*c2)*(x33*c2)-kr41*(x35*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_490" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_489" name="k41" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_488" name="kr41" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_487" name="x30" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_486" name="x33" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_479" name="x35" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_81" name="Function for v42" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_81">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k42*(x44*c2)*(x45*c2)-kr42*(x46*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_496" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_495" name="k42" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_494" name="kr42" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_493" name="x44" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_492" name="x45" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_491" name="x46" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_82" name="Function for v43" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_82">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k43*(x46*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_502" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_501" name="k43" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_500" name="x46" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_83" name="Function for v44" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_83">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k44*(x47*c2)*(x45*c2)-kr44*(x48*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_497" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_498" name="k44" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_499" name="kr44" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_503" name="x45" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_504" name="x47" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_505" name="x48" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_84" name="Function for v45" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_84">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k45*(x48*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_511" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_510" name="k45" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_509" name="x48" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_85" name="Function for v46" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_85">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k44*(x49*c2)*(x45*c2)-kr44*(x50*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_506" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_507" name="k44" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_508" name="kr44" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_512" name="x45" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_513" name="x49" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_514" name="x50" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_86" name="Function for v47" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_86">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k47*(x50*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_520" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_519" name="k47" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_518" name="x50" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_87" name="Function for v48" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_87">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k48*(x51*c2)*(x53*c2)-kr48*(x52*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_515" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_516" name="k48" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_517" name="kr48" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_521" name="x51" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_522" name="x52" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_523" name="x53" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_88" name="Function for v49" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_88">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k49*(x52*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_529" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_528" name="k49" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_527" name="x52" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_89" name="Function for v50" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_89">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k50*(x53*c2)*(x49*c2)-kr50*(x54*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_524" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_525" name="k50" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_526" name="kr50" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_530" name="x49" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_531" name="x53" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_532" name="x54" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_90" name="Function for v51" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_90">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k49*(x54*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_538" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_537" name="k49" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_536" name="x54" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_91" name="Function for v52" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_91">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k52*(x55*c2)*(x51*c2)-kr52*(x56*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_533" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_534" name="k52" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_535" name="kr52" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_539" name="x51" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_540" name="x55" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_541" name="x56" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_92" name="Function for v53" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_92">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k53*(x56*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_547" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_546" name="k53" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_545" name="x56" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_93" name="Function for v54" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_93">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k52*(x51*c2)*(x57*c2)-kr52*(x58*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_542" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_543" name="k52" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_544" name="kr52" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_548" name="x51" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_549" name="x57" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_550" name="x58" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_94" name="Function for v55" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_94">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k55*(x58*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_556" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_555" name="k55" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_554" name="x58" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_95" name="Function for v56" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_95">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k56*(x59*c2)*(x60*c2)-kr56*(x61*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_551" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_552" name="k56" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_553" name="kr56" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_557" name="x59" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_558" name="x60" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_559" name="x61" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_96" name="Function for v57" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_96">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k57*(x61*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_565" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_564" name="k57" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_563" name="x61" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_97" name="Function for v58" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_97">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k58*(x60*c2)*(x57*c2)-kr58*(x62*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_560" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_561" name="k58" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_562" name="kr58" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_566" name="x57" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_567" name="x60" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_568" name="x62" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_98" name="Function for v59" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_98">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k59*(x62*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_574" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_573" name="k59" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_572" name="x62" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_99" name="Function for v60" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_99">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k60*(x6*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_569" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_570" name="k60" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_571" name="x6" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_100" name="Function for v61" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_100">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k61*(x16*c2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_577" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_576" name="k61" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_575" name="x16" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_101" name="Function for v62" type="UserDefined" reversible="false">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_101">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k60*(x8*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_580" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_579" name="k60" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_578" name="x8" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_102" name="Function for v63" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_102">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k16*(x17*c2)*(x22*c2)-kr16*(x18*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_583" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_582" name="k16" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_581" name="kr16" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_584" name="x17" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_585" name="x18" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_586" name="x22" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_103" name="Function for v64" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_103">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k17*(x24*c2)*(x18*c2)-kr17*(x19*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_592" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_591" name="k17" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_590" name="kr17" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_589" name="x18" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_588" name="x19" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_587" name="x24" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_104" name="Function for v65" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_104">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k18*(x26*c2)*(x19*c2)-kr18*(x20*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_598" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_597" name="k18" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_596" name="kr18" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_595" name="x19" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_594" name="x20" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_593" name="x26" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_105" name="Function for v66" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_105">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k19*(x20*c2)-kr19*(x69*c2)*(x19*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_604" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_603" name="k19" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_602" name="kr19" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_601" name="x19" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_600" name="x20" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_599" name="x69" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_106" name="Function for v67" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_106">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k20*(x71*c2)*(x19*c2)-kr20*(x21*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_610" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_609" name="k20" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_608" name="kr20" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_607" name="x19" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_606" name="x21" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_605" name="x71" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_107" name="Function for v68" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_107">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k21*(x21*c2)-kr21*(x19*c2)*(x26*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_616" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_615" name="k21" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_614" name="kr21" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_613" name="x19" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_612" name="x21" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_611" name="x26" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_108" name="Function for v69" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_108">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k22*(x31*c2)*(x17*c2)-kr22*(x63*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_622" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_621" name="k22" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_620" name="kr22" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_619" name="x17" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_618" name="x31" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_617" name="x63" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_109" name="Function for v70" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_109">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k23*(x63*c2)-kr23*(x64*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_628" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_627" name="k23" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_626" name="kr23" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_625" name="x63" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_624" name="x64" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_110" name="Function for v71" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_110">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k24*(x22*c2)*(x64*c2)-kr24*(x65*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_632" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_631" name="k24" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_630" name="kr24" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_629" name="x22" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_623" name="x64" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_633" name="x65" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_111" name="Function for v72" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_111">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k25*(x24*c2)*(x65*c2)-kr25*(x66*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_639" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_638" name="k25" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_637" name="kr25" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_636" name="x24" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_635" name="x65" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_634" name="x66" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_112" name="Function for v73" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_112">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k18*(x26*c2)*(x66*c2)-kr18*(x67*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_645" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_644" name="k18" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_643" name="kr18" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_642" name="x26" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_641" name="x66" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_640" name="x67" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_113" name="Function for v74" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_113">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k19*(x67*c2)-kr19*(x66*c2)*(x69*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_651" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_650" name="k19" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_649" name="kr19" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_648" name="x66" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_647" name="x67" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_646" name="x69" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_114" name="Function for v75" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_114">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k28*(x69*c2)*(x41*c2)-kr28*(x70*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_657" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_656" name="k28" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_655" name="kr28" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_654" name="x41" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_653" name="x69" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_652" name="x70" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_115" name="Function for v76" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_115">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k29*(x70*c2)-kr29*(x71*c2)*(x72*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_663" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_662" name="k29" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_661" name="kr29" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_660" name="x70" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_659" name="x71" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_658" name="x72" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_116" name="Function for v77" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_116">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k20*(x71*c2)*(x66*c2)-kr20*(x68*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_669" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_668" name="k20" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_667" name="kr20" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_666" name="x66" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_665" name="x68" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_664" name="x71" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_117" name="Function for v78" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_117">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k21*(x68*c2)-kr21*(x66*c2)*(x26*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_675" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_674" name="k21" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_673" name="kr21" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_672" name="x26" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_671" name="x66" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_670" name="x68" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_118" name="Function for v79" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_118">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k32*(x66*c2)-kr32*(x17*c2)*(x38*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_681" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_680" name="k32" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_679" name="kr32" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_678" name="x17" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_677" name="x38" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_676" name="x66" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_119" name="Function for v80" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_119">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k34*(x19*c2)-kr34*(x17*c2)*(x30*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_687" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_686" name="k34" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_685" name="kr34" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_684" name="x17" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_683" name="x19" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_682" name="x30" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_120" name="Function for v81" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_120">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k37*(x64*c2)-kr37*(x17*c2)*(x40*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_693" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_692" name="k37" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_691" name="kr37" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_690" name="x17" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_689" name="x40" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_688" name="x64" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_121" name="Function for v82" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_121">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k37*(x65*c2)-kr37*(x17*c2)*(x39*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_699" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_698" name="k37" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_697" name="kr37" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_696" name="x17" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_695" name="x39" order="4" role="product"/>
        <ParameterDescription key="FunctionParameter_694" name="x65" order="5" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_122" name="Function for v83" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_122">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k41*(x30*c2)*(x64*c2)-kr41*(x66*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_705" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_704" name="k41" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_703" name="kr41" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_702" name="x30" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_701" name="x64" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_700" name="x66" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_123" name="Function for v84" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_123">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k42*(x44*c2)*(x72*c2)-kr42*(x73*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_711" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_710" name="k42" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_709" name="kr42" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_708" name="x44" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_707" name="x72" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_706" name="x73" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_124" name="Function for v85" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_124">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k43*(x73*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_717" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_716" name="k43" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_715" name="x73" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_125" name="Function for v86" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_125">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k44*(x47*c2)*(x72*c2)-kr44*(x74*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_712" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_713" name="k44" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_714" name="kr44" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_718" name="x47" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_719" name="x72" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_720" name="x74" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_126" name="Function for v87" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_126">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k45*(x74*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_726" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_725" name="k45" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_724" name="x74" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_127" name="Function for v88" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_127">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k44*(x72*c2)*(x75*c2)-kr44*(x76*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_721" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_722" name="k44" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_723" name="kr44" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_727" name="x72" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_728" name="x75" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_729" name="x76" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_128" name="Function for v89" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_128">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k47*(x76*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_735" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_734" name="k47" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_733" name="x76" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_129" name="Function for v90" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_129">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k48*(x77*c2)*(x53*c2)-kr48*(x78*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_730" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_731" name="k48" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_732" name="kr48" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_736" name="x53" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_737" name="x77" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_738" name="x78" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_130" name="Function for v91" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_130">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k49*(x78*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_744" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_743" name="k49" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_742" name="x78" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_131" name="Function for v92" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_131">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k50*(x53*c2)*(x75*c2)-kr50*(x79*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_739" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_740" name="k50" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_741" name="kr50" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_745" name="x53" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_746" name="x75" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_747" name="x79" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_132" name="Function for v93" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_132">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k49*(x79*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_753" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_752" name="k49" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_751" name="x79" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_133" name="Function for v94" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_133">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k52*(x55*c2)*(x77*c2)-kr52*(x80*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_748" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_749" name="k52" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_750" name="kr52" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_754" name="x55" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_755" name="x77" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_756" name="x80" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_134" name="Function for v95" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_134">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k53*(x80*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_762" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_761" name="k53" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_760" name="x80" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_135" name="Function for v96" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_135">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k52*(x77*c2)*(x81*c2)-kr52*(x82*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_757" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_758" name="k52" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_759" name="kr52" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_763" name="x77" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_764" name="x81" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_765" name="x82" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_136" name="Function for v97" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_136">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k55*(x82*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_771" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_770" name="k55" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_769" name="x82" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_137" name="Function for v98" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_137">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k56*(x83*c2)*(x60*c2)-kr56*(x84*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_766" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_767" name="k56" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_768" name="kr56" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_772" name="x60" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_773" name="x83" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_774" name="x84" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_138" name="Function for v99" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_138">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k57*(x84*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_780" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_779" name="k57" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_778" name="x84" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_139" name="Function for v100" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_139">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k58*(x60*c2)*(x81*c2)-kr58*(x85*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_775" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_776" name="k58" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_777" name="kr58" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_781" name="x60" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_782" name="x81" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_783" name="x85" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_140" name="Function for v101" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_140">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k59*(x85*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_789" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_788" name="k59" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_787" name="x85" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_141" name="Function for v102" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_141">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k6*(x15*c3)-kr6*(x17*c2)
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_784" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_785" name="c3" order="1" role="volume"/>
        <ParameterDescription key="FunctionParameter_786" name="k6" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_790" name="kr6" order="3" role="constant"/>
        <ParameterDescription key="FunctionParameter_791" name="x15" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_792" name="x17" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_142" name="Function for v103" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_142">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k6*(x32*c2)-kr6*(x63*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_798" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_797" name="k6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_796" name="kr6" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_795" name="x32" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_794" name="x63" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_143" name="Function for v104" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_143">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k6*(x33*c2)-kr6*(x64*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_802" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_801" name="k6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_800" name="kr6" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_799" name="x33" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_793" name="x64" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_144" name="Function for v105" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_144">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k6*(x25*c2)-kr6*(x19*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_807" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_806" name="k6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_805" name="kr6" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_804" name="x19" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_803" name="x25" order="4" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_145" name="Function for v106" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_145">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k4*(x25*c2)*(x12*c2)-kr4*(x88*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_812" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_811" name="k4" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_810" name="kr4" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_809" name="x12" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_808" name="x25" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_813" name="x88" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_146" name="Function for v107" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_146">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k5*(x88*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_819" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_818" name="k5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_817" name="x88" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_147" name="Function for v108" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_147">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k6*(x27*c2)-kr6*(x20*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_814" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_815" name="k6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_816" name="kr6" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_820" name="x20" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_821" name="x27" order="4" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_148" name="Function for v109" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_148">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k4*(x27*c2)*(x12*c2)-kr4*(x89*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_826" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_825" name="k4" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_824" name="kr4" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_823" name="x12" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_822" name="x27" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_827" name="x89" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_149" name="Function for v110" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_149">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k5*(x89*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_833" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_832" name="k5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_831" name="x89" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_150" name="Function for v111" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_150">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k6*(x29*c2)-kr6*(x21*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_828" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_829" name="k6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_830" name="kr6" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_834" name="x21" order="3" role="product"/>
        <ParameterDescription key="FunctionParameter_835" name="x29" order="4" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_151" name="Function for v112" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_151">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k4*(x29*c2)*(x12*c2)-kr4*(x90*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_840" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_839" name="k4" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_838" name="kr4" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_837" name="x12" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_836" name="x29" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_841" name="x90" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_152" name="Function for v113" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_152">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k5*(x90*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_847" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_846" name="k5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_845" name="x90" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_153" name="Function for v114" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_153">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k6*(x34*c2)-kr6*(x65*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_842" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_843" name="k6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_844" name="kr6" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_848" name="x34" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_849" name="x65" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_154" name="Function for v115" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_154">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k4*(x34*c2)*(x12*c2)-kr4*(x91*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_854" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_853" name="k4" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_852" name="kr4" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_851" name="x12" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_850" name="x34" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_855" name="x91" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_155" name="Function for v116" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_155">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k5*(x91*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_861" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_860" name="k5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_859" name="x91" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_156" name="Function for v117" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_156">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k6*(x35*c2)-kr6*(x66*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_856" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_857" name="k6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_858" name="kr6" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_862" name="x35" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_863" name="x66" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_157" name="Function for v118" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_157">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k4*(x35*c2)*(x12*c2)-kr4*(x92*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_868" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_867" name="k4" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_866" name="kr4" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_865" name="x12" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_864" name="x35" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_869" name="x92" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_158" name="Function for v119" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_158">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k5*(x92*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_875" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_874" name="k5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_873" name="x92" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_159" name="Function for v120" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_159">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k6*(x36*c2)-kr6*(x67*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_870" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_871" name="k6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_872" name="kr6" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_876" name="x36" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_877" name="x67" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_160" name="Function for v121" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_160">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k4*(x36*c2)*(x12*c2)-kr4*(x93*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_882" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_881" name="k4" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_880" name="kr4" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_879" name="x12" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_878" name="x36" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_883" name="x93" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_161" name="Function for v122" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_161">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k5*(x93*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_889" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_888" name="k5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_887" name="x93" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_162" name="Function for v123" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_162">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k6*(x37*c2)-kr6*(x68*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_884" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_885" name="k6" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_886" name="kr6" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_890" name="x37" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_891" name="x68" order="4" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_163" name="Function for v124" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_163">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        (k4*(x37*c2)*(x12*c2)-kr4*(x94*c2))/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_896" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_895" name="k4" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_894" name="kr4" order="2" role="constant"/>
        <ParameterDescription key="FunctionParameter_893" name="x12" order="3" role="substrate"/>
        <ParameterDescription key="FunctionParameter_892" name="x37" order="4" role="substrate"/>
        <ParameterDescription key="FunctionParameter_897" name="x94" order="5" role="product"/>
      </ListOfParameterDescriptions>
    </Function>
    <Function key="Function_164" name="Function for v125" type="UserDefined" reversible="true">
      <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Function_164">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        k5*(x94*c2)/c2
      </Expression>
      <ListOfParameterDescriptions>
        <ParameterDescription key="FunctionParameter_903" name="c2" order="0" role="volume"/>
        <ParameterDescription key="FunctionParameter_902" name="k5" order="1" role="constant"/>
        <ParameterDescription key="FunctionParameter_901" name="x94" order="2" role="substrate"/>
      </ListOfParameterDescriptions>
    </Function>
  </ListOfFunctions>
  <Model key="Model_0" name="Schoeberl2002 - EGF MAPK" simulationType="time" timeUnit="min" volumeUnit="pl" areaUnit="m²" lengthUnit="m" quantityUnit="#" type="deterministic" avogadroConstant="6.0221417899999999e+23">
    <MiriamAnnotation>
<rdf:RDF
   xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <rdf:Description rdf:about="#Model_0">
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="http://identifiers.org/pubmed/11923843"/>
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <dcterms:created>
      <rdf:Description>
        <dcterms:W3CDTF>2005-08-15T06:36:38Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:created>
    <dcterms:creator>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>klau@mshri.on.ca</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Lau</vCard:Family>
                <vCard:Given>Ken</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>Mt. Sinai Hospital/ Univ. of Toronto</vCard:Orgname>
              </rdf:Description>
            </vCard:ORG>
          </rdf:Description>
        </rdf:li>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>schoeber@MIT.EDU</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Schoeberl</vCard:Family>
                <vCard:Given>Birgit</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>MIT</vCard:Orgname>
              </rdf:Description>
            </vCard:ORG>
          </rdf:Description>
        </rdf:li>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>lenov@ebi.ac.uk</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Le Novère</vCard:Family>
                <vCard:Given>Nicolas</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>EMBL-EBI</vCard:Orgname>
              </rdf:Description>
            </vCard:ORG>
          </rdf:Description>
        </rdf:li>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>raim@tbi.univie.ac.at</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Machne</vCard:Family>
                <vCard:Given>Rainer</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>University of Vienna</vCard:Orgname>
              </rdf:Description>
            </vCard:ORG>
          </rdf:Description>
        </rdf:li>
        <rdf:li>
          <rdf:Description>
            <vCard:EMAIL>lukas@ebi.ac.uk</vCard:EMAIL>
            <vCard:N>
              <rdf:Description>
                <vCard:Family>Endler</vCard:Family>
                <vCard:Given>Lukas</vCard:Given>
              </rdf:Description>
            </vCard:N>
            <vCard:ORG>
              <rdf:Description>
                <vCard:Orgname>EMBL-EBI</vCard:Orgname>
              </rdf:Description>
            </vCard:ORG>
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:creator>
    <dcterms:modified>
      <rdf:Description>
        <dcterms:W3CDTF>2014-06-09T13:13:54Z</dcterms:W3CDTF>
      </rdf:Description>
    </dcterms:modified>
    <CopasiMT:hasVersion>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0000165"/>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0007265"/>
      </rdf:Bag>
    </CopasiMT:hasVersion>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/biomodels.db/MODEL6617455076"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/biomodels.db/BIOMD0000000019"/>
      </rdf:Bag>
    </CopasiMT:is>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0007173"/>
        <rdf:li rdf:resource="http://identifiers.org/reactome/REACT_9417.3"/>
      </rdf:Bag>
    </CopasiMT:isVersionOf>
    <CopasiMT:occursIn>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/taxonomy/9606"/>
      </rdf:Bag>
    </CopasiMT:occursIn>
  </rdf:Description>
</rdf:RDF>

    </MiriamAnnotation>
    <Comment>
      <body xmlns="http://www.w3.org/1999/xhtml">
    <div class="dc:title">
	  Schoeberl2002 - EGF MAPK
	</div>
    <div class="dc:description">
      <p>Computational model that offers an integrated quantitative, dynamic, and topological representation of intracellular signal networks, based on known components of epidermal growth factor (EGF) receptor signal pathways.</p>
    </div>
    <div class="dc:provenance">
      <p>The initial model was constructed by Ken Lau from the <a href="http://web.mit.edu/dllaz/egf_pap/">MATLAB source code</a>.</p>
  </div>
  <div class="dc:bibliographicCitation">
    <p>This model is described in the article:</p>
    <div class="bibo:title">
      <a href="http://identifiers.org/pubmed/11923843" title="Access to this publication">Computational modeling of the dynamics of the MAP kinase cascade activated by surface and internalized EGF receptors.</a>
    </div>
    <div class="bibo:authorList">Schoeberl B, Eichler-Jonsson C, Gilles ED, Müller G</div>
    <div class="bibo:Journal">Nat. Biotechnol. 2002 Apr; 20(4): 370-375</div>
    <p>Abstract:</p>
    <div class="bibo:abstract">
      <p>We present a computational model that offers an integrated quantitative, dynamic, and topological representation of intracellular signal networks, based on known components of epidermal growth factor (EGF) receptor signal pathways. The model provides insight into signal-response relationships between the binding of EGF to its receptor at the cell surface and the activation of downstream proteins in the signaling cascade. It shows that EGF-induced responses are remarkably stable over a 100-fold range of ligand concentration and that the critical parameter in determining signal efficacy is the initial velocity of receptor activation. The predictions of the model agree well with experimental analysis of the effect of EGF on two downstream responses, phosphorylation of ERK-1/2 and expression of the target gene, c-fos.</p>
    </div>
  </div>
  <div class="bm:curation">
    <p>This model does <b>not</b> exactly reproduce the results given in the original publication. It has, though, the same reaction graph and gives very similar time courses for the conditions depicted in the article.</p>
</div><div class="bm:modification">
  <p>Several corrections were applied to the parameters described in the paper's supplementary materials. Some parameter names were replaced by the corresponding identical ones: k(r)26 by k(r)18, k(r)27 by k(r)19, k(r)30 by k(r)20, k(r)38 by k(r)24, k(r)39 by k(r)37, k(r)46 by k(r)44, k51 by k49, k(r)54 by k(r)52 and k62 by k62. In particular the parameter values described in the column "remark" of supplementary table 1 override the values explicitely written in the numerical columns:</p>
  <table>
    <tr>
      <th>name</th>
      <th>in suppl. value used</th>
      <th>in model value used</th>
      <th>remarks</th>
    </tr>
    <tr>
      <td>kr16</td>
      <td>0.055</td>
      <td>0.275</td>
      <td />
    </tr>
    <tr>
      <td>k30</td>
      <td>7.9e6</td>
      <td>2.1e6</td>
      <td>as k20</td>
    </tr>
    <tr>
      <td>kr30</td>
      <td>0.3</td>
      <td>0.4</td>
      <td>as kr24</td>
    </tr>
    <tr>
      <td>k38</td>
      <td>3e7</td>
      <td>1e7</td>
      <td>as k20</td>
    </tr>
    <tr>
      <td>kr38</td>
      <td>0.055</td>
      <td>0.55</td>
      <td>as kr24</td>
    </tr>
    <tr>
      <td>k52</td>
      <td>1.1e5</td>
      <td>5.34e7</td>
      <td />
    </tr>
  </table>
  <p>k5 was used for v116, v119, v122 and v125 in addition of v107, v110 and v113 as listed in the legend of supplementary figure 2. k5 is calculated using th eformula from the matlab file not given in the supplements.</p>
  <p>All rate constants were rescaled to minutes (k[min] = 60*k[sec]) and all second order rate constants additionally to molecules/cell with a cell volume of 1 picolitre (k[molecs/cell] = k[M]/(Vc*Na), with Vc=1e-12 l and Na = 6e23).</p>
  <p>The association constant of internalized EGF was rescaled to molecules/endosome using an endosomal volume of 4.3 al (= 4.3*10 <sup>-18</sup> litre).</p><p>The extracellular EGF concentration was converted to molecules per picolitre with a MW of 6045 Da.</p><table>
  <tr>
    <th>[ng/ml]</th>
    <th>[numb/pl]</th>
  </tr>
  <tr>
    <td>50</td>
    <td>4962</td>
  </tr>
  <tr>
    <td>0.5</td>
    <td>49.6</td>
  </tr>
  <tr>
    <td>0.125</td>
    <td>12.4</td>
  </tr>
</table><p>With the initial conditions given in the paper, the results could not be reproduced at all. Therefore the initial conditions used in the MATLAB file were adopted for SHC (1.01 * 10 <sup>5</sup> instead of 1.01 * 10      <sup>6</sup> ) and Ras_GDP. (7.2 * 10 <sup>4</sup> instead of 1.14 * 10 <sup>7</sup> )</p>
</div><div class="dc:publisher">
  <p>This model is hosted on <a href="http://www.ebi.ac.uk/biomodels/">BioModels Database</a> and identified by: <a href="http://identifiers.org/biomodels.db/BIOMD0000000019">BIOMD0000000019</a>.</p><p>To cite BioModels Database, please use: <a href="http://identifiers.org/pubmed/20587024" title="Latest BioModels Database publication">BioModels Database: An enhanced, curated and annotated resource for published quantitative kinetic models</a>.</p>
</div><div class="dc:license">
  <p>To the extent possible under law, all copyright and related or neighbouring rights to this encoded model have been dedicated to the public domain worldwide. Please refer to <a href="http://creativecommons.org/publicdomain/zero/1.0/" title="Access to: CC0 1.0 Universal (CC0 1.0), Public Domain Dedication">CC0 Public Domain Dedication</a> for more information.</p>
</div>
</body>
    </Comment>
    <ListOfUnsupportedAnnotations>
      <UnsupportedAnnotation name="http://www.sys-bio.org/sbml">
<jd:header xmlns:jd="http://www.sys-bio.org/sbml">
  <jd:VersionHeader SBMLVersion="1.0" />
  <jd:ModelHeader Author="Schoeberl et al." ModelTitle="Computational modeling of the dynamics of the MAP kinase cascade activated by surface and internalized EGF receptors." ModelVersion="0.0" />
</jd:header>
      </UnsupportedAnnotation>
    </ListOfUnsupportedAnnotations>
    <ListOfCompartments>
      <Compartment key="Compartment_0" name="extracellular volume" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_0">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0005615" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
      <Compartment key="Compartment_1" name="cytoplasm" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_1">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0005737" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
      <Compartment key="Compartment_2" name="endosomal volume" simulationType="fixed" dimensionality="3" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Compartment_2">
    <CopasiMT:is>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0005768" />
      </rdf:Bag>
    </CopasiMT:is>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Compartment>
    </ListOfCompartments>
    <ListOfMetabolites>
      <Metabolite key="Metabolite_0" name="EGF" simulationType="fixed" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_0">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Comment>
          <p xmlns="http://www.w3.org/1999/xhtml">
        4962 molecules correspond roughly to 50 ng/ml, concentration used throughout the article (MW~6045 Da, vol=1e-12l)</p>
        </Comment>
      </Metabolite>
      <Metabolite key="Metabolite_1" name="EGFR" simulationType="reactions" compartment="Compartment_0" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_1">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_2" name="EGF-EGFR" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_2">
    <CopasiMT:hasVersion>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P00533" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P01133" />
      </rdf:Bag>
    </CopasiMT:hasVersion>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/reactome/REACT_9893" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_3" name="EGF-EGFR^2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_3">
    <CopasiMT:hasVersion>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P00533" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P01133" />
      </rdf:Bag>
    </CopasiMT:hasVersion>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/reactome/REACT_9820" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_4" name="EGF-EGFR*^2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_4">
    <CopasiMT:hasVersion>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P00533" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P01133" />
      </rdf:Bag>
    </CopasiMT:hasVersion>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/kegg.compound/C00562" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_5" name="EGFRi" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_5">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P00533" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_6" name="EGF-EGFR*^2-GAP-Grb2-Prot" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_6">
    <CopasiMT:hasVersion>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0030119" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P00533" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P01133" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P20936" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P62993" />
      </rdf:Bag>
    </CopasiMT:hasVersion>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_7" name="EGF-EGFRi*^2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_7">
    <CopasiMT:hasVersion>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P00533" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P01133" />
      </rdf:Bag>
    </CopasiMT:hasVersion>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_8" name="Proti" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_8">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0030119" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_9" name="EGF-EGFRi" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_9">
    <CopasiMT:hasVersion>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P00533" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P01133" />
      </rdf:Bag>
    </CopasiMT:hasVersion>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_10" name="EGF-EGFRi^2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_10">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_11" name="Prot" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_11">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_12" name="GAP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_12">
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="http://identifiers.org/omim/139150" />
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/interpro/IPR001936" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P20936" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_13" name="EGFi" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_13">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_14" name="EGF-EGFRi*^2-GAP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_14">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_15" name="EGF-EGFRi*^2-GAP-Grb2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_15">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_16" name="EGF-EGFRi*^2-GAP-Grb2-Sos" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_16">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_17" name="EGF-EGFRi*^2-GAP-Grb2-Sos-Ras-GDP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_17">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_18" name="EGF-EGFRi*^2-GAP-Grb2-Sos-Ras-GTP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_18">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_19" name="Grb2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_19">
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="http://identifiers.org/omim/108355" />
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P62993" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_20" name="EGF-EGFR*^2-GAP-Grb2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_20">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_21" name="Sos" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_21">
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="http://identifiers.org/omim/182530" />
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/uniprot/Q07889" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_22" name="EGF-EGFR*^2-GAP-Grb2-Sos" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_22">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_23" name="Ras-GDP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_23">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/chebi/CHEBI:17552" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P01112" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_24" name="EGF-EGFR*^2-GAP-Grb2-Sos-Ras-GDP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_24">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_25" name="Ras-GTP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_25">
    <CopasiMT:hasPart>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/chebi/CHEBI:15996" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P01112" />
      </rdf:Bag>
    </CopasiMT:hasPart>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_26" name="EGF-EGFR*^2-GAP-Grb2-Sos-Ras-GTP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_26">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_27" name="Grb2-Sos" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_27">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_28" name="Shc" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_28">
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="http://identifiers.org/omim/605217" />
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P98077" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_29" name="EGF-EGFR*^2-GAP-Shc" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_29">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_30" name="EGF-EGFR*^2-GAP-Shc*" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_30">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_31" name="EGF-EGFR*^2-GAP-Shc*-Grb2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_31">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_32" name="EGF-EGFR*^2-GAP-Shc*-Grb2-Sos" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_32">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_33" name="EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GDP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_33">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_34" name="EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GTP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_34">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_35" name="Shc*-Grb2-Sos" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_35">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_36" name="Shc*-Grb2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_36">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_37" name="Shc*" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_37">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_38" name="Raf" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_38">
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="http://identifiers.org/omim/164760" />
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P04049" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_39" name="Raf-Ras-GTP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_39">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_40" name="Ras-GTP*" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_40">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_41" name="Phosphotase1" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_41">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_42" name="Raf*" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_42">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_43" name="Raf*-P'ase" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_43">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_44" name="MEK" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_44">
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="http://identifiers.org/omim/176872" />
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/uniprot/A4QPA9" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/Q02750" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_45" name="MEK-Raf*" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_45">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_46" name="MEK-P" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_46">
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="http://identifiers.org/omim/176872" />
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/kegg.compound/C00562" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/A4QPA9" />
        <rdf:li rdf:resource="http://identifiers.org/uniprot/Q02750" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_47" name="MEK-P-Raf*" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_47">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_48" name="MEK-PP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_48">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_49" name="MEK-PP-P'ase2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_49">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_50" name="Phosphatase2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_50">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_51" name="MEK-P-P'ase2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_51">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_52" name="ERK" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Metabolite_52">
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="http://identifiers.org/omim/176948" />
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/uniprot/P28482" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_53" name="ERK-MEK-PP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_53">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_54" name="ERK-P" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_54">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_55" name="ERK-P-MEK-PP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_55">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_56" name="ERK-PP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_56">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_57" name="Phosphotase3" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_57">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_58" name="ERK-PP-P'ase3" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_58">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_59" name="ERK-P-P'ase3" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_59">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_60" name="EGF-EGFRi*^2-GAP-Shc" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_60">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_61" name="EGF-EGFRi*^2-GAP-Shc*" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_61">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_62" name="EGF-EGFRi*^2-GAP-Shc*-Grb2" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_62">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_63" name="EGF-EGFRi*^2-GAP-Shc*-Grb2-Sos" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_63">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_64" name="EGF-EGFRi*^2-GAP-Shc*-Grb2-Sos-Ras-GDP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_64">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_65" name="EGF-EGFRi*^2-GAP-Shc*-Grb2-Sos-Ras-GTP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_65">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_66" name="Rasi-GTP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_66">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_67" name="Rafi-Rasi-GTP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_67">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_68" name="Rasi-GTP*" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_68">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_69" name="Rafi*" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_69">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_70" name="Rafi*-P'ase" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_70">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_71" name="MEKi-Rafi*" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_71">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_72" name="MEKi-P" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_72">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_73" name="MEKi-P-Rafi*" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_73">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_74" name="MEKi-PP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_74">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_75" name="MEKi-PP-P'ase2i" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_75">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_76" name="MEKi-P-P'ase2i" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_76">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_77" name="ERKi-MEKi-PP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_77">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_78" name="ERKi-P" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_78">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_79" name="ERKi-P-MEKi-PP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_79">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_80" name="ERKi-PP" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_80">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_81" name="ERKi-PP-P'ase3i" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_81">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_82" name="ERKi-P-P'ase3i" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_82">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_83" name="EGFRideg" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_83">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_84" name="EGF-EGFRi*^2deg" simulationType="fixed" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_84">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_85" name="EGF-EGFR*^2-GAP-Grb2-Sos-Prot" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_85">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_86" name="EGF-EGFR*^2-GAP-Grb2-Sos-Ras-GDP-Prot" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_86">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_87" name="EGF-EGFR*^2-GAP-Grb2-Sos-Ras-GTP-Prot" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_87">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_88" name="EGF-EGFR*^2-GAP-Shc*-Grb2-Prot" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_88">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_89" name="EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Prot" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_89">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_90" name="EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GDP-Prot" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_90">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_91" name="EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GTP-Prot" simulationType="reactions" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_91">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_92" name="t_Raf*" simulationType="assignment" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_92">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Raf*],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Raf*-P'ase],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEK-Raf*],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEK-P-Raf*],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Rafi*],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Rafi*-P'ase],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEKi-Rafi*],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEKi-P-Rafi*],Reference=ParticleNumber>)/&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Reference=Volume>
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_93" name="t_Ras_GTP" simulationType="assignment" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_93">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Raf-Ras-GTP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Ras-GTP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Rafi-Rasi-GTP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Rasi-GTP],Reference=ParticleNumber>)/&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Reference=Volume>
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_94" name="t_MEK_PP" simulationType="assignment" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_94">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEK-PP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEKi-PP],Reference=ParticleNumber>)/&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Reference=Volume>
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_95" name="t_ERK_PP" simulationType="assignment" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_95">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERK-PP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERKi-PP],Reference=ParticleNumber>)/&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Reference=Volume>
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_96" name="t_SHC_P_t" simulationType="assignment" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_96">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GDP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GTP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Shc*-Grb2-Sos],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Shc*-Grb2],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Shc*],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Prot],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Prot],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GDP-Prot],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GTP-Prot],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*-Grb2],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*-Grb2-Sos],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*-Grb2-Sos-Ras-GDP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*-Grb2-Sos-Ras-GTP],Reference=ParticleNumber>)/&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Reference=Volume>
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_97" name="t_EGF_EGFR*" simulationType="assignment" compartment="Compartment_1" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_97">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          (&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Prot],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[endosomal volume],Vector=Metabolites[EGF-EGFR*^2-GAP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Sos],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Sos-Ras-GDP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Sos-Ras-GTP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GDP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GTP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Sos-Prot],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Sos-Ras-GDP-Prot],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Sos-Ras-GTP-Prot],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Prot],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Prot],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GDP-Prot],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GTP-Prot],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi^2],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Grb2],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Grb2-Sos],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Grb2-Sos-Ras-GDP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Grb2-Sos-Ras-GTP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*-Grb2],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*-Grb2-Sos],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*-Grb2-Sos-Ras-GDP],Reference=ParticleNumber>+&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*-Grb2-Sos-Ras-GTP],Reference=ParticleNumber>)/&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Reference=Volume>
        </Expression>
      </Metabolite>
      <Metabolite key="Metabolite_98" name="EGFideg" simulationType="fixed" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_98">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
      <Metabolite key="Metabolite_99" name="EGF-EGFR*^2-GAP" simulationType="reactions" compartment="Compartment_2" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Metabolite_99">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </Metabolite>
    </ListOfMetabolites>
    <ListOfModelValues>
      <ModelValue key="ModelValue_0" name="k1" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_0">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_1" name="kr1" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_1">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_2" name="kr2" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_2">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_3" name="k2" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_3">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_4" name="k3" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_4">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_5" name="kr3" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_5">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_6" name="k4" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_6">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_7" name="kr4" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_7">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_8" name="k5" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_8">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          if(&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[C_internalization],Reference=Value> lt 3100,1.55,if(&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[C_internalization],Reference=Value> gt 100000,0.2,&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[C_internalization],Reference=Value>*-1.35e-05+1.55))
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_9" name="k6" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_9">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_10" name="kr6" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_10">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_11" name="k7" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_11">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_12" name="k8" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_12">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_13" name="kr8" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_13">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_14" name="k10" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_14">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_15" name="kr10" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_15">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_16" name="kr11" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_16">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_17" name="k11" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_17">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_18" name="kr12" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_18">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_19" name="k12" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_19">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_20" name="k13" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_20">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_21" name="k14" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_21">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_22" name="kr14" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_22">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_23" name="k15" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_23">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_24" name="kr16" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_24">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_25" name="k16" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_25">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_26" name="kr17" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_26">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_27" name="k17" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_27">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_28" name="kr18" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_28">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_29" name="k18" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_29">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_30" name="kr19" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_30">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_31" name="k19" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_31">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_32" name="kr20" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_32">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_33" name="k20" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_33">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_34" name="k21" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_34">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_35" name="kr21" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_35">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_36" name="k22" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_36">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_37" name="kr22" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_37">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_38" name="k23" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_38">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_39" name="kr23" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_39">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_40" name="k24" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_40">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_41" name="kr24" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_41">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_42" name="kr25" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_42">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_43" name="k25" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_43">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_44" name="k28" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_44">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_45" name="kr28" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_45">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_46" name="k29" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_46">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_47" name="kr29" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_47">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_48" name="kr32" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_48">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_49" name="k32" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_49">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_50" name="k33" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_50">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_51" name="kr33" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_51">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_52" name="k34" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_52">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_53" name="kr34" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_53">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_54" name="k35" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_54">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_55" name="kr35" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_55">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_56" name="Vm36" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_56">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_57" name="Km36" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_57">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_58" name="k37" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_58">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_59" name="kr37" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_59">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_60" name="k40" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_60">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_61" name="kr40" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_61">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_62" name="kr41" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_62">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_63" name="k41" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_63">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_64" name="k42" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_64">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_65" name="kr42" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_65">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_66" name="k43" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_66">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_67" name="kr44" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_67">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_68" name="k44" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_68">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_69" name="k45" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_69">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_70" name="k47" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_70">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_71" name="kr48" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_71">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_72" name="k48" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_72">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_73" name="k49" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_73">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_74" name="kr50" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_74">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_75" name="k50" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_75">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_76" name="k52" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_76">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_77" name="kr52" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_77">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_78" name="k53" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_78">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_79" name="k55" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_79">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_80" name="kr56" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_80">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_81" name="k56" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_81">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_82" name="k57" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_82">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_83" name="kr58" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_83">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_84" name="k58" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_84">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_85" name="k59" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_85">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_86" name="k60" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_86">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_87" name="k61" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_87">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
      <ModelValue key="ModelValue_88" name="C_internalization" simulationType="assignment" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_88">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <Expression>
          &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[total_Receptors],Reference=Value>/(&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr1],Reference=Value>/(&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k1],Reference=Value>*&lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[extracellular volume],Vector=Metabolites[EGF],Reference=ParticleNumber>)+1)
        </Expression>
      </ModelValue>
      <ModelValue key="ModelValue_89" name="total_Receptors" simulationType="fixed" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelValue_89">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
      </ModelValue>
    </ListOfModelValues>
    <ListOfReactions>
      <Reaction key="Reaction_0" name="v1" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_0">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0005154" />
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0048408" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/reactome/REACT_9481" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_0" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_2" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5019" name="k1" value="0.003"/>
          <Constant key="Parameter_5018" name="kr1" value="0.228"/>
        </ListOfConstants>
        <KineticLaw function="Function_41" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_265">
              <SourceParameter reference="Compartment_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_250">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_261">
              <SourceParameter reference="ModelValue_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_266">
              <SourceParameter reference="ModelValue_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_267">
              <SourceParameter reference="Metabolite_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_268">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_269">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_1" name="v2" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_1">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0007171" />
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0046983" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/reactome/REACT_9397" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_2" stoichiometry="2"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5022" name="k2" value="0.001"/>
          <Constant key="Parameter_5020" name="kr2" value="6"/>
        </ListOfConstants>
        <KineticLaw function="Function_42" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_276">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_275">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_274">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_273">
              <SourceParameter reference="Metabolite_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_272">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_2" name="v3" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_2">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0004713" />
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0007171" />
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0046777" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/reactome/REACT_9388" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_3" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5023" name="k3" value="60"/>
          <Constant key="Parameter_5024" name="kr3" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_43" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_279">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_278">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_277">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_270">
              <SourceParameter reference="Metabolite_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_271">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_3" name="v4" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_3">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5028" name="k4" value="1.038e-05"/>
          <Constant key="Parameter_5030" name="kr4" value="0.0996"/>
        </ListOfConstants>
        <KineticLaw function="Function_44" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_284">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_283">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_282">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_281">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_280">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_285">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_4" name="v5" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_4">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_6" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5031" name="k5" value="0.885183"/>
        </ListOfConstants>
        <KineticLaw function="Function_40" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_264">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_263">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_262">
              <SourceParameter reference="Metabolite_6"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_5" name="v6" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_5">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0031623" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5025" name="k6" value="0.003"/>
          <Constant key="Parameter_5027" name="kr6" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_45" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_291">
              <SourceParameter reference="Compartment_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_290">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_289">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_288">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_287">
              <SourceParameter reference="Metabolite_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_286">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_6" name="v7" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_6">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0031623" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5026" name="k7" value="0.003"/>
        </ListOfConstants>
        <KineticLaw function="Function_46" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_297">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_296">
              <SourceParameter reference="ModelValue_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_295">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_7" name="v8" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_7">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_4" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_99" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5029" name="k8" value="0.0001"/>
          <Constant key="Parameter_5032" name="kr8" value="12"/>
        </ListOfConstants>
        <KineticLaw function="Function_47" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_292">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_293">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_294">
              <SourceParameter reference="ModelValue_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_298">
              <SourceParameter reference="ModelValue_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_299">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_300">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_301">
              <SourceParameter reference="Metabolite_4"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_8" name="v9" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_8">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5033" name="k7" value="0.003"/>
        </ListOfConstants>
        <KineticLaw function="Function_48" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_308">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_307">
              <SourceParameter reference="ModelValue_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_306">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_9" name="v10" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_9">
    <CopasiMT:isVersionOf>
      <rdf:Bag>
        <rdf:li rdf:resource="http://identifiers.org/go/GO:0031623" />
      </rdf:Bag>
    </CopasiMT:isVersionOf>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_9" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5067" name="k10" value="3.25581"/>
          <Constant key="Parameter_5068" name="kr10" value="0.66"/>
        </ListOfConstants>
        <KineticLaw function="Function_49" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_303">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_304">
              <SourceParameter reference="ModelValue_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_305">
              <SourceParameter reference="ModelValue_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_302">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_309">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_310">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_10" name="v11" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_10">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_9" stoichiometry="2"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5072" name="k2" value="0.001"/>
          <Constant key="Parameter_5074" name="kr2" value="6"/>
        </ListOfConstants>
        <KineticLaw function="Function_50" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_316">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_315">
              <SourceParameter reference="ModelValue_3"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_314">
              <SourceParameter reference="ModelValue_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_313">
              <SourceParameter reference="Metabolite_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_312">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_11" name="v12" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_11">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_10" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5075" name="k3" value="60"/>
          <Constant key="Parameter_5069" name="kr3" value="0.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_51" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_320">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_319">
              <SourceParameter reference="ModelValue_4"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_318">
              <SourceParameter reference="ModelValue_5"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_317">
              <SourceParameter reference="Metabolite_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_311">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_12" name="v13" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_12">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfProducts>
          <Product metabolite="Metabolite_1" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5071" name="k13" value="130.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_52" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[extracellular volume]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_325">
              <SourceParameter reference="Compartment_0"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_324">
              <SourceParameter reference="ModelValue_20"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_13" name="v14" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_13">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_12" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5070" name="k14" value="0.0001"/>
          <Constant key="Parameter_5073" name="kr14" value="12"/>
        </ListOfConstants>
        <KineticLaw function="Function_53" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_322">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_323">
              <SourceParameter reference="ModelValue_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_321">
              <SourceParameter reference="ModelValue_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_326">
              <SourceParameter reference="Metabolite_12"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_327">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_328">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_14" name="v15" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_14">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5076" name="k15" value="600000"/>
        </ListOfConstants>
        <KineticLaw function="Function_54" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_334">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_333">
              <SourceParameter reference="ModelValue_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_332">
              <SourceParameter reference="Metabolite_8"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_15" name="v16" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_15">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_99" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5065" name="k16" value="0.001"/>
          <Constant key="Parameter_5063" name="kr16" value="16.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_55" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_329">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_330">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_331">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_335">
              <SourceParameter reference="ModelValue_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_336">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_337">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_338">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_16" name="v17" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_16">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_20" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5062" name="k17" value="0.001"/>
          <Constant key="Parameter_5066" name="kr17" value="3.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_56" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_345">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_344">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_343">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_342">
              <SourceParameter reference="Metabolite_20"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_341">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_340">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_17" name="v18" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_17">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5064" name="k18" value="0.0015"/>
          <Constant key="Parameter_5037" name="kr18" value="78"/>
        </ListOfConstants>
        <KineticLaw function="Function_57" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_350">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_349">
              <SourceParameter reference="ModelValue_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_348">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_347">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_346">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_339">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_18" name="v19" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_18">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5035" name="k19" value="30"/>
          <Constant key="Parameter_5034" name="kr19" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_58" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_356">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_355">
              <SourceParameter reference="ModelValue_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_354">
              <SourceParameter reference="ModelValue_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_353">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_352">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_351">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_19" name="v20" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_19">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5038" name="k20" value="0.00021"/>
          <Constant key="Parameter_5036" name="kr20" value="24"/>
        </ListOfConstants>
        <KineticLaw function="Function_59" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_362">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_361">
              <SourceParameter reference="ModelValue_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_360">
              <SourceParameter reference="ModelValue_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_359">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_358">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_357">
              <SourceParameter reference="Metabolite_40"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_20" name="v21" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_20">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_22" stoichiometry="1"/>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5052" name="k21" value="1.38"/>
          <Constant key="Parameter_5053" name="kr21" value="2.2e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_60" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_368">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_367">
              <SourceParameter reference="ModelValue_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_366">
              <SourceParameter reference="ModelValue_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_365">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_364">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_363">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_21" name="v22" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_21">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_99" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5040" name="k22" value="0.0021"/>
          <Constant key="Parameter_5057" name="kr22" value="6"/>
        </ListOfConstants>
        <KineticLaw function="Function_61" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_374">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_373">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_372">
              <SourceParameter reference="ModelValue_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_371">
              <SourceParameter reference="ModelValue_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_370">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_369">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_375">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_22" name="v23" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_22">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5043" name="k23" value="360"/>
          <Constant key="Parameter_5059" name="kr23" value="36"/>
        </ListOfConstants>
        <KineticLaw function="Function_62" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_382">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_381">
              <SourceParameter reference="ModelValue_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_380">
              <SourceParameter reference="ModelValue_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_379">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_378">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_23" name="v24" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_23">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5060" name="k24" value="0.001"/>
          <Constant key="Parameter_5054" name="kr24" value="33"/>
        </ListOfConstants>
        <KineticLaw function="Function_63" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_385">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_384">
              <SourceParameter reference="ModelValue_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_383">
              <SourceParameter reference="ModelValue_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_376">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_377">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_386">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_24" name="v25" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_24">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5039" name="k25" value="0.001"/>
          <Constant key="Parameter_5047" name="kr25" value="1.284"/>
        </ListOfConstants>
        <KineticLaw function="Function_64" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_392">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_391">
              <SourceParameter reference="ModelValue_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_390">
              <SourceParameter reference="ModelValue_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_389">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_388">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_387">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_25" name="v26" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_25">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5056" name="k18" value="0.0015"/>
          <Constant key="Parameter_5041" name="kr18" value="78"/>
        </ListOfConstants>
        <KineticLaw function="Function_65" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_398">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_397">
              <SourceParameter reference="ModelValue_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_396">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_395">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_394">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_393">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_26" name="v27" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_26">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
          <Product metabolite="Metabolite_25" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5055" name="k19" value="30"/>
          <Constant key="Parameter_5046" name="kr19" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_66" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_404">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_403">
              <SourceParameter reference="ModelValue_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_402">
              <SourceParameter reference="ModelValue_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_401">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_400">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_399">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_27" name="v28" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_27">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_25" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5050" name="k28" value="0.0001"/>
          <Constant key="Parameter_5045" name="kr28" value="0.318"/>
        </ListOfConstants>
        <KineticLaw function="Function_67" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_410">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_409">
              <SourceParameter reference="ModelValue_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_408">
              <SourceParameter reference="ModelValue_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_407">
              <SourceParameter reference="Metabolite_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_406">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_405">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_28" name="v29" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_28">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_39" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_40" stoichiometry="1"/>
          <Product metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5049" name="k29" value="60"/>
          <Constant key="Parameter_5048" name="kr29" value="7e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_68" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_416">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_415">
              <SourceParameter reference="ModelValue_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_414">
              <SourceParameter reference="ModelValue_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_413">
              <SourceParameter reference="Metabolite_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_412">
              <SourceParameter reference="Metabolite_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_411">
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_29" name="v30" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_29">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_40" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5051" name="k20" value="0.00021"/>
          <Constant key="Parameter_5058" name="kr20" value="24"/>
        </ListOfConstants>
        <KineticLaw function="Function_69" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_422">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_421">
              <SourceParameter reference="ModelValue_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_420">
              <SourceParameter reference="ModelValue_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_419">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_418">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_417">
              <SourceParameter reference="Metabolite_40"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_30" name="v31" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_30">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5042" name="k21" value="1.38"/>
          <Constant key="Parameter_5044" name="kr21" value="2.2e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_70" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_428">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_427">
              <SourceParameter reference="ModelValue_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_426">
              <SourceParameter reference="ModelValue_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_425">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_424">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_423">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_31" name="v32" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_31">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_99" stoichiometry="1"/>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5061" name="k32" value="6"/>
          <Constant key="Parameter_5077" name="kr32" value="2.4e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_71" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_434">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_433">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_432">
              <SourceParameter reference="ModelValue_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_431">
              <SourceParameter reference="ModelValue_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_430">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_429">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_435">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_32" name="v33" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_32">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_37" stoichiometry="1"/>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5078" name="k33" value="12"/>
          <Constant key="Parameter_5084" name="kr33" value="0.0021"/>
        </ListOfConstants>
        <KineticLaw function="Function_72" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_442">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_441">
              <SourceParameter reference="ModelValue_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_440">
              <SourceParameter reference="ModelValue_51"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_439">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_438">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_437">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_33" name="v34" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_33">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_99" stoichiometry="1"/>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5083" name="k34" value="1.8"/>
          <Constant key="Parameter_5085" name="kr34" value="0.00045"/>
        </ListOfConstants>
        <KineticLaw function="Function_73" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_447">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_446">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_445">
              <SourceParameter reference="ModelValue_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_444">
              <SourceParameter reference="ModelValue_53"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_443">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_436">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_448">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_34" name="v35" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_34">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_21" stoichiometry="1"/>
          <Product metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5080" name="k35" value="0.09"/>
          <Constant key="Parameter_5079" name="kr35" value="0.00045"/>
        </ListOfConstants>
        <KineticLaw function="Function_74" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_455">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_454">
              <SourceParameter reference="ModelValue_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_453">
              <SourceParameter reference="ModelValue_55"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_452">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_451">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_450">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_35" name="v36" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_35">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_28" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5082" name="Km36" value="2e+14"/>
          <Constant key="Parameter_5081" name="Vm36" value="61200"/>
        </ListOfConstants>
        <KineticLaw function="Function_75" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_460">
              <SourceParameter reference="ModelValue_57"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_459">
              <SourceParameter reference="ModelValue_56"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_458">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_457">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_36" name="v37" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_36">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_99" stoichiometry="1"/>
          <Product metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5086" name="k37" value="18"/>
          <Constant key="Parameter_5090" name="kr37" value="9e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_76" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_462">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_461">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_449">
              <SourceParameter reference="ModelValue_58"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_456">
              <SourceParameter reference="ModelValue_59"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_463">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_464">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_465">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_37" name="v38" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_37">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5088" name="k24" value="0.001"/>
          <Constant key="Parameter_5087" name="kr24" value="33"/>
        </ListOfConstants>
        <KineticLaw function="Function_77" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_472">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_471">
              <SourceParameter reference="ModelValue_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_470">
              <SourceParameter reference="ModelValue_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_469">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_468">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_467">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_38" name="v39" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_38">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_99" stoichiometry="1"/>
          <Product metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5091" name="k37" value="18"/>
          <Constant key="Parameter_5089" name="kr37" value="9e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_78" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_477">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_476">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_475">
              <SourceParameter reference="ModelValue_58"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_474">
              <SourceParameter reference="ModelValue_59"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_473">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_466">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_478">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_39" name="v40" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_39">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5093" name="k40" value="0.003"/>
          <Constant key="Parameter_5095" name="kr40" value="3.84"/>
        </ListOfConstants>
        <KineticLaw function="Function_79" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_485">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_484">
              <SourceParameter reference="ModelValue_60"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_483">
              <SourceParameter reference="ModelValue_61"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_482">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_481">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_480">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_40" name="v41" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_40">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5096" name="k41" value="0.003"/>
          <Constant key="Parameter_5092" name="kr41" value="2.574"/>
        </ListOfConstants>
        <KineticLaw function="Function_80" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_490">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_489">
              <SourceParameter reference="ModelValue_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_488">
              <SourceParameter reference="ModelValue_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_487">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_486">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_479">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_41" name="v42" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_41">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5094" name="k42" value="0.0071"/>
          <Constant key="Parameter_5099" name="kr42" value="12"/>
        </ListOfConstants>
        <KineticLaw function="Function_81" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_496">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_495">
              <SourceParameter reference="ModelValue_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_494">
              <SourceParameter reference="ModelValue_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_493">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_492">
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_491">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_42" name="v43" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_42">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_43" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
          <Product metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5100" name="k43" value="60"/>
        </ListOfConstants>
        <KineticLaw function="Function_82" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_502">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_501">
              <SourceParameter reference="ModelValue_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_500">
              <SourceParameter reference="Metabolite_43"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_43" name="v44" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_43">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_44" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5101" name="k44" value="0.00111"/>
          <Constant key="Parameter_5097" name="kr44" value="1.0998"/>
        </ListOfConstants>
        <KineticLaw function="Function_83" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_497">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_498">
              <SourceParameter reference="ModelValue_68"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_499">
              <SourceParameter reference="ModelValue_67"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_503">
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_504">
              <SourceParameter reference="Metabolite_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_505">
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_44" name="v45" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_44">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_45" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_46" stoichiometry="1"/>
          <Product metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5098" name="k45" value="210"/>
        </ListOfConstants>
        <KineticLaw function="Function_84" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_511">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_510">
              <SourceParameter reference="ModelValue_69"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_509">
              <SourceParameter reference="Metabolite_45"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_45" name="v46" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_45">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_46" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_47" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5102" name="k44" value="0.00111"/>
          <Constant key="Parameter_5104" name="kr44" value="1.0998"/>
        </ListOfConstants>
        <KineticLaw function="Function_85" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_506">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_507">
              <SourceParameter reference="ModelValue_68"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_508">
              <SourceParameter reference="ModelValue_67"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_512">
              <SourceParameter reference="Metabolite_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_513">
              <SourceParameter reference="Metabolite_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_514">
              <SourceParameter reference="Metabolite_47"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_46" name="v47" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_46">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_47" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
          <Product metabolite="Metabolite_42" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5103" name="k47" value="174"/>
        </ListOfConstants>
        <KineticLaw function="Function_86" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_520">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_519">
              <SourceParameter reference="ModelValue_70"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_518">
              <SourceParameter reference="Metabolite_47"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_47" name="v48" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_47">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_48" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5105" name="k48" value="0.00143"/>
          <Constant key="Parameter_5106" name="kr48" value="48"/>
        </ListOfConstants>
        <KineticLaw function="Function_87" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_515">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_516">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_517">
              <SourceParameter reference="ModelValue_71"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_521">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_522">
              <SourceParameter reference="Metabolite_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_523">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_48" name="v49" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_48">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_49" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_46" stoichiometry="1"/>
          <Product metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5107" name="k49" value="3.48"/>
        </ListOfConstants>
        <KineticLaw function="Function_88" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_529">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_528">
              <SourceParameter reference="ModelValue_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_527">
              <SourceParameter reference="Metabolite_49"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_49" name="v50" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_49">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_50" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_46" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5108" name="k50" value="2.5e-05"/>
          <Constant key="Parameter_5109" name="kr50" value="30"/>
        </ListOfConstants>
        <KineticLaw function="Function_89" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_524">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_525">
              <SourceParameter reference="ModelValue_75"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_526">
              <SourceParameter reference="ModelValue_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_530">
              <SourceParameter reference="Metabolite_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_531">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_532">
              <SourceParameter reference="Metabolite_51"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_50" name="v51" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_50">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_51" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
          <Product metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5110" name="k49" value="3.48"/>
        </ListOfConstants>
        <KineticLaw function="Function_90" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_538">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_537">
              <SourceParameter reference="ModelValue_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_536">
              <SourceParameter reference="Metabolite_51"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_51" name="v52" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_51">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_52" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5119" name="k52" value="0.00534"/>
          <Constant key="Parameter_5118" name="kr52" value="1.98"/>
        </ListOfConstants>
        <KineticLaw function="Function_91" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_533">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_534">
              <SourceParameter reference="ModelValue_76"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_535">
              <SourceParameter reference="ModelValue_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_539">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_540">
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_541">
              <SourceParameter reference="Metabolite_53"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_52" name="v53" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_52">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_53" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
          <Product metabolite="Metabolite_54" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5117" name="k53" value="960"/>
        </ListOfConstants>
        <KineticLaw function="Function_92" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_547">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_546">
              <SourceParameter reference="ModelValue_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_545">
              <SourceParameter reference="Metabolite_53"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_53" name="v54" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_53">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_48" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_54" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5116" name="k52" value="0.00534"/>
          <Constant key="Parameter_5112" name="kr52" value="1.98"/>
        </ListOfConstants>
        <KineticLaw function="Function_93" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_542">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_543">
              <SourceParameter reference="ModelValue_76"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_544">
              <SourceParameter reference="ModelValue_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_548">
              <SourceParameter reference="Metabolite_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_549">
              <SourceParameter reference="Metabolite_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_550">
              <SourceParameter reference="Metabolite_55"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_54" name="v55" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_54">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_55" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_56" stoichiometry="1"/>
          <Product metabolite="Metabolite_48" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5111" name="k55" value="342"/>
        </ListOfConstants>
        <KineticLaw function="Function_94" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_556">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_555">
              <SourceParameter reference="ModelValue_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_554">
              <SourceParameter reference="Metabolite_55"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_55" name="v56" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_55">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_56" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_58" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5114" name="k56" value="0.00145"/>
          <Constant key="Parameter_5113" name="kr56" value="36"/>
        </ListOfConstants>
        <KineticLaw function="Function_95" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_551">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_552">
              <SourceParameter reference="ModelValue_81"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_553">
              <SourceParameter reference="ModelValue_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_557">
              <SourceParameter reference="Metabolite_56"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_558">
              <SourceParameter reference="Metabolite_57"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_559">
              <SourceParameter reference="Metabolite_58"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_56" name="v57" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_56">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_58" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_54" stoichiometry="1"/>
          <Product metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5124" name="k57" value="16.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_96" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_565">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_564">
              <SourceParameter reference="ModelValue_82"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_563">
              <SourceParameter reference="Metabolite_58"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_57" name="v58" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_57">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_57" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_54" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_59" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5121" name="k58" value="0.0005"/>
          <Constant key="Parameter_5122" name="kr58" value="30"/>
        </ListOfConstants>
        <KineticLaw function="Function_97" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_560">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_561">
              <SourceParameter reference="ModelValue_84"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_562">
              <SourceParameter reference="ModelValue_83"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_566">
              <SourceParameter reference="Metabolite_54"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_567">
              <SourceParameter reference="Metabolite_57"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_568">
              <SourceParameter reference="Metabolite_59"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_58" name="v59" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_58">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_59" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_52" stoichiometry="1"/>
          <Product metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5123" name="k59" value="18"/>
        </ListOfConstants>
        <KineticLaw function="Function_98" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_574">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_573">
              <SourceParameter reference="ModelValue_85"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_572">
              <SourceParameter reference="Metabolite_59"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_59" name="v60" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_59">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_5" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_83" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5115" name="k60" value="0.04002"/>
        </ListOfConstants>
        <KineticLaw function="Function_99" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_569">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_570">
              <SourceParameter reference="ModelValue_86"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_571">
              <SourceParameter reference="Metabolite_5"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_60" name="v61" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_60">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_13" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_98" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5120" name="k61" value="0.01002"/>
        </ListOfConstants>
        <KineticLaw function="Function_100" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_577">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_576">
              <SourceParameter reference="ModelValue_87"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_575">
              <SourceParameter reference="Metabolite_13"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_61" name="v62" reversible="false" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_61">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_7" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_84" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5125" name="k60" value="0.04002"/>
        </ListOfConstants>
        <KineticLaw function="Function_101" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_580">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_579">
              <SourceParameter reference="ModelValue_86"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_578">
              <SourceParameter reference="Metabolite_7"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_62" name="v63" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_62">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5126" name="k16" value="0.001"/>
          <Constant key="Parameter_5127" name="kr16" value="16.5"/>
        </ListOfConstants>
        <KineticLaw function="Function_102" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_583">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_582">
              <SourceParameter reference="ModelValue_25"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_581">
              <SourceParameter reference="ModelValue_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_584">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_585">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_586">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_63" name="v64" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_63">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_15" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5128" name="k17" value="0.001"/>
          <Constant key="Parameter_5133" name="kr17" value="3.6"/>
        </ListOfConstants>
        <KineticLaw function="Function_103" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_592">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_591">
              <SourceParameter reference="ModelValue_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_590">
              <SourceParameter reference="ModelValue_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_589">
              <SourceParameter reference="Metabolite_15"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_588">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_587">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_64" name="v65" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_64">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5130" name="k18" value="0.0015"/>
          <Constant key="Parameter_5132" name="kr18" value="78"/>
        </ListOfConstants>
        <KineticLaw function="Function_104" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_598">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_597">
              <SourceParameter reference="ModelValue_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_596">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_595">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_594">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_593">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_65" name="v66" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_65">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_66" stoichiometry="1"/>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5131" name="k19" value="30"/>
          <Constant key="Parameter_5129" name="kr19" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_105" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_604">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_603">
              <SourceParameter reference="ModelValue_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_602">
              <SourceParameter reference="ModelValue_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_601">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_600">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_599">
              <SourceParameter reference="Metabolite_66"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_66" name="v67" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_66">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_68" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5137" name="k20" value="0.00021"/>
          <Constant key="Parameter_5136" name="kr20" value="24"/>
        </ListOfConstants>
        <KineticLaw function="Function_106" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_610">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_609">
              <SourceParameter reference="ModelValue_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_608">
              <SourceParameter reference="ModelValue_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_607">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_606">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_605">
              <SourceParameter reference="Metabolite_68"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_67" name="v68" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_67">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5134" name="k21" value="1.38"/>
          <Constant key="Parameter_5135" name="kr21" value="2.2e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_107" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_616">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_615">
              <SourceParameter reference="ModelValue_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_614">
              <SourceParameter reference="ModelValue_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_613">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_612">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_611">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_68" name="v69" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_68">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_28" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_60" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5197" name="k22" value="0.0021"/>
          <Constant key="Parameter_5156" name="kr22" value="6"/>
        </ListOfConstants>
        <KineticLaw function="Function_108" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_622">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_621">
              <SourceParameter reference="ModelValue_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_620">
              <SourceParameter reference="ModelValue_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_619">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_618">
              <SourceParameter reference="Metabolite_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_617">
              <SourceParameter reference="Metabolite_60"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_69" name="v70" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_69">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_60" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5138" name="k23" value="360"/>
          <Constant key="Parameter_5195" name="kr23" value="36"/>
        </ListOfConstants>
        <KineticLaw function="Function_109" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_628">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_627">
              <SourceParameter reference="ModelValue_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_626">
              <SourceParameter reference="ModelValue_39"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_625">
              <SourceParameter reference="Metabolite_60"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_624">
              <SourceParameter reference="Metabolite_61"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_70" name="v71" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_70">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_19" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5200" name="k24" value="0.001"/>
          <Constant key="Parameter_5194" name="kr24" value="33"/>
        </ListOfConstants>
        <KineticLaw function="Function_110" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_632">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_631">
              <SourceParameter reference="ModelValue_40"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_630">
              <SourceParameter reference="ModelValue_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_629">
              <SourceParameter reference="Metabolite_19"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_623">
              <SourceParameter reference="Metabolite_61"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_633">
              <SourceParameter reference="Metabolite_62"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_71" name="v72" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_71">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_21" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5196" name="k25" value="0.001"/>
          <Constant key="Parameter_5142" name="kr25" value="1.284"/>
        </ListOfConstants>
        <KineticLaw function="Function_111" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_639">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_638">
              <SourceParameter reference="ModelValue_43"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_637">
              <SourceParameter reference="ModelValue_42"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_636">
              <SourceParameter reference="Metabolite_21"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_635">
              <SourceParameter reference="Metabolite_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_634">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_72" name="v73" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_72">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_23" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_64" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5144" name="k18" value="0.0015"/>
          <Constant key="Parameter_5145" name="kr18" value="78"/>
        </ListOfConstants>
        <KineticLaw function="Function_112" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_645">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_644">
              <SourceParameter reference="ModelValue_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_643">
              <SourceParameter reference="ModelValue_28"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_642">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_641">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_640">
              <SourceParameter reference="Metabolite_64"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_73" name="v74" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_73">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_64" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_63" stoichiometry="1"/>
          <Product metabolite="Metabolite_66" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5139" name="k19" value="30"/>
          <Constant key="Parameter_5141" name="kr19" value="1e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_113" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_651">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_650">
              <SourceParameter reference="ModelValue_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_649">
              <SourceParameter reference="ModelValue_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_648">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_647">
              <SourceParameter reference="Metabolite_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_646">
              <SourceParameter reference="Metabolite_66"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_74" name="v75" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_74">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_66" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_38" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_67" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5140" name="k28" value="0.0001"/>
          <Constant key="Parameter_5143" name="kr28" value="0.318"/>
        </ListOfConstants>
        <KineticLaw function="Function_114" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_657">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_656">
              <SourceParameter reference="ModelValue_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_655">
              <SourceParameter reference="ModelValue_45"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_654">
              <SourceParameter reference="Metabolite_38"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_653">
              <SourceParameter reference="Metabolite_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_652">
              <SourceParameter reference="Metabolite_67"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_75" name="v76" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_75">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_67" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_68" stoichiometry="1"/>
          <Product metabolite="Metabolite_69" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5146" name="k29" value="60"/>
          <Constant key="Parameter_5155" name="kr29" value="7e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_115" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_663">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_662">
              <SourceParameter reference="ModelValue_46"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_661">
              <SourceParameter reference="ModelValue_47"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_660">
              <SourceParameter reference="Metabolite_67"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_659">
              <SourceParameter reference="Metabolite_68"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_658">
              <SourceParameter reference="Metabolite_69"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_76" name="v77" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_76">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_68" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_65" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5159" name="k20" value="0.00021"/>
          <Constant key="Parameter_5152" name="kr20" value="24"/>
        </ListOfConstants>
        <KineticLaw function="Function_116" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_669">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_668">
              <SourceParameter reference="ModelValue_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_667">
              <SourceParameter reference="ModelValue_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_666">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_665">
              <SourceParameter reference="Metabolite_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_664">
              <SourceParameter reference="Metabolite_68"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_77" name="v78" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_77">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_65" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_63" stoichiometry="1"/>
          <Product metabolite="Metabolite_23" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5147" name="k21" value="1.38"/>
          <Constant key="Parameter_5153" name="kr21" value="2.2e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_117" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_675">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_674">
              <SourceParameter reference="ModelValue_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_673">
              <SourceParameter reference="ModelValue_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_672">
              <SourceParameter reference="Metabolite_23"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_671">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_670">
              <SourceParameter reference="Metabolite_65"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_78" name="v79" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_78">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
          <Product metabolite="Metabolite_35" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5149" name="k32" value="6"/>
          <Constant key="Parameter_5148" name="kr32" value="2.4e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_118" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_681">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_680">
              <SourceParameter reference="ModelValue_49"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_679">
              <SourceParameter reference="ModelValue_48"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_678">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_677">
              <SourceParameter reference="Metabolite_35"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_676">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_79" name="v80" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_79">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
          <Product metabolite="Metabolite_27" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5150" name="k34" value="1.8"/>
          <Constant key="Parameter_5154" name="kr34" value="0.00045"/>
        </ListOfConstants>
        <KineticLaw function="Function_119" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_687">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_686">
              <SourceParameter reference="ModelValue_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_685">
              <SourceParameter reference="ModelValue_53"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_684">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_683">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_682">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_80" name="v81" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_80">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
          <Product metabolite="Metabolite_37" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5151" name="k37" value="18"/>
          <Constant key="Parameter_5004" name="kr37" value="9e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_120" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_693">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_692">
              <SourceParameter reference="ModelValue_58"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_691">
              <SourceParameter reference="ModelValue_59"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_690">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_689">
              <SourceParameter reference="Metabolite_37"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_688">
              <SourceParameter reference="Metabolite_61"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_81" name="v82" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_81">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
          <Product metabolite="Metabolite_36" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5013" name="k37" value="18"/>
          <Constant key="Parameter_5008" name="kr37" value="9e-05"/>
        </ListOfConstants>
        <KineticLaw function="Function_121" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_699">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_698">
              <SourceParameter reference="ModelValue_58"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_697">
              <SourceParameter reference="ModelValue_59"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_696">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_695">
              <SourceParameter reference="Metabolite_36"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_694">
              <SourceParameter reference="Metabolite_62"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_82" name="v83" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_82">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_27" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5011" name="k41" value="0.003"/>
          <Constant key="Parameter_5003" name="kr41" value="2.574"/>
        </ListOfConstants>
        <KineticLaw function="Function_122" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_705">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_704">
              <SourceParameter reference="ModelValue_63"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_703">
              <SourceParameter reference="ModelValue_62"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_702">
              <SourceParameter reference="Metabolite_27"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_701">
              <SourceParameter reference="Metabolite_61"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_700">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_83" name="v84" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_83">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_41" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_69" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_70" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5007" name="k42" value="0.0071"/>
          <Constant key="Parameter_5006" name="kr42" value="12"/>
        </ListOfConstants>
        <KineticLaw function="Function_123" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_711">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_710">
              <SourceParameter reference="ModelValue_64"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_709">
              <SourceParameter reference="ModelValue_65"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_708">
              <SourceParameter reference="Metabolite_41"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_707">
              <SourceParameter reference="Metabolite_69"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_706">
              <SourceParameter reference="Metabolite_70"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_84" name="v85" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_84">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_70" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_38" stoichiometry="1"/>
          <Product metabolite="Metabolite_41" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5015" name="k43" value="60"/>
        </ListOfConstants>
        <KineticLaw function="Function_124" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_717">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_716">
              <SourceParameter reference="ModelValue_66"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_715">
              <SourceParameter reference="Metabolite_70"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_85" name="v86" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_85">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_44" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_69" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_71" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5012" name="k44" value="0.00111"/>
          <Constant key="Parameter_5010" name="kr44" value="1.0998"/>
        </ListOfConstants>
        <KineticLaw function="Function_125" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_712">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_713">
              <SourceParameter reference="ModelValue_68"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_714">
              <SourceParameter reference="ModelValue_67"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_718">
              <SourceParameter reference="Metabolite_44"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_719">
              <SourceParameter reference="Metabolite_69"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_720">
              <SourceParameter reference="Metabolite_71"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_86" name="v87" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_86">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_71" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_72" stoichiometry="1"/>
          <Product metabolite="Metabolite_69" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5009" name="k45" value="210"/>
        </ListOfConstants>
        <KineticLaw function="Function_126" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_726">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_725">
              <SourceParameter reference="ModelValue_69"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_724">
              <SourceParameter reference="Metabolite_71"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_87" name="v88" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_87">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_69" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_72" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_73" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5014" name="k44" value="0.00111"/>
          <Constant key="Parameter_5017" name="kr44" value="1.0998"/>
        </ListOfConstants>
        <KineticLaw function="Function_127" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_721">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_722">
              <SourceParameter reference="ModelValue_68"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_723">
              <SourceParameter reference="ModelValue_67"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_727">
              <SourceParameter reference="Metabolite_69"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_728">
              <SourceParameter reference="Metabolite_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_729">
              <SourceParameter reference="Metabolite_73"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_88" name="v89" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_88">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_73" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_69" stoichiometry="1"/>
          <Product metabolite="Metabolite_74" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5005" name="k47" value="174"/>
        </ListOfConstants>
        <KineticLaw function="Function_128" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_735">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_734">
              <SourceParameter reference="ModelValue_70"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_733">
              <SourceParameter reference="Metabolite_73"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_89" name="v90" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_89">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_74" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_75" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5016" name="k48" value="0.00143"/>
          <Constant key="Parameter_5192" name="kr48" value="48"/>
        </ListOfConstants>
        <KineticLaw function="Function_129" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_730">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_731">
              <SourceParameter reference="ModelValue_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_732">
              <SourceParameter reference="ModelValue_71"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_736">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_737">
              <SourceParameter reference="Metabolite_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_738">
              <SourceParameter reference="Metabolite_75"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_90" name="v91" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_90">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_75" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_72" stoichiometry="1"/>
          <Product metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_5193" name="k49" value="3.48"/>
        </ListOfConstants>
        <KineticLaw function="Function_130" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_744">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_743">
              <SourceParameter reference="ModelValue_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_742">
              <SourceParameter reference="Metabolite_75"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_91" name="v92" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_91">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_50" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_72" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_76" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4840" name="k50" value="2.5e-05"/>
          <Constant key="Parameter_4839" name="kr50" value="30"/>
        </ListOfConstants>
        <KineticLaw function="Function_131" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_739">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_740">
              <SourceParameter reference="ModelValue_75"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_741">
              <SourceParameter reference="ModelValue_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_745">
              <SourceParameter reference="Metabolite_50"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_746">
              <SourceParameter reference="Metabolite_72"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_747">
              <SourceParameter reference="Metabolite_76"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_92" name="v93" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_92">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_76" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_44" stoichiometry="1"/>
          <Product metabolite="Metabolite_50" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4838" name="k49" value="3.48"/>
        </ListOfConstants>
        <KineticLaw function="Function_132" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_753">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_752">
              <SourceParameter reference="ModelValue_73"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_751">
              <SourceParameter reference="Metabolite_76"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_93" name="v94" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_93">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_52" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_74" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4837" name="k52" value="0.00534"/>
          <Constant key="Parameter_4836" name="kr52" value="1.98"/>
        </ListOfConstants>
        <KineticLaw function="Function_133" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_748">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_749">
              <SourceParameter reference="ModelValue_76"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_750">
              <SourceParameter reference="ModelValue_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_754">
              <SourceParameter reference="Metabolite_52"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_755">
              <SourceParameter reference="Metabolite_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_756">
              <SourceParameter reference="Metabolite_77"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_94" name="v95" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_94">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_77" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_78" stoichiometry="1"/>
          <Product metabolite="Metabolite_74" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4835" name="k53" value="960"/>
        </ListOfConstants>
        <KineticLaw function="Function_134" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_762">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_761">
              <SourceParameter reference="ModelValue_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_760">
              <SourceParameter reference="Metabolite_77"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_95" name="v96" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_95">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_74" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_78" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4834" name="k52" value="0.00534"/>
          <Constant key="Parameter_4833" name="kr52" value="1.98"/>
        </ListOfConstants>
        <KineticLaw function="Function_135" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_757">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_758">
              <SourceParameter reference="ModelValue_76"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_759">
              <SourceParameter reference="ModelValue_77"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_763">
              <SourceParameter reference="Metabolite_74"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_764">
              <SourceParameter reference="Metabolite_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_765">
              <SourceParameter reference="Metabolite_79"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_96" name="v97" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_96">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_79" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_80" stoichiometry="1"/>
          <Product metabolite="Metabolite_74" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4832" name="k55" value="342"/>
        </ListOfConstants>
        <KineticLaw function="Function_136" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_771">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_770">
              <SourceParameter reference="ModelValue_79"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_769">
              <SourceParameter reference="Metabolite_79"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_97" name="v98" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_97">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_80" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_81" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4831" name="k56" value="0.00145"/>
          <Constant key="Parameter_4830" name="kr56" value="36"/>
        </ListOfConstants>
        <KineticLaw function="Function_137" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_766">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_767">
              <SourceParameter reference="ModelValue_81"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_768">
              <SourceParameter reference="ModelValue_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_772">
              <SourceParameter reference="Metabolite_57"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_773">
              <SourceParameter reference="Metabolite_80"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_774">
              <SourceParameter reference="Metabolite_81"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_98" name="v99" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_98">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_81" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_78" stoichiometry="1"/>
          <Product metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4829" name="k57" value="16.2"/>
        </ListOfConstants>
        <KineticLaw function="Function_138" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_780">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_779">
              <SourceParameter reference="ModelValue_82"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_778">
              <SourceParameter reference="Metabolite_81"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_99" name="v100" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_99">
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="http://identifiers.org/omim/164760" />
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_57" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_78" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_82" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4828" name="k58" value="0.0005"/>
          <Constant key="Parameter_4827" name="kr58" value="30"/>
        </ListOfConstants>
        <KineticLaw function="Function_139" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_775">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_776">
              <SourceParameter reference="ModelValue_84"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_777">
              <SourceParameter reference="ModelValue_83"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_781">
              <SourceParameter reference="Metabolite_57"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_782">
              <SourceParameter reference="Metabolite_78"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_783">
              <SourceParameter reference="Metabolite_82"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_100" name="v101" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:CopasiMT="http://www.copasi.org/RDF/MiriamTerms#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="#Reaction_100">
    <dcterms:bibliographicCitation>
      <rdf:Bag>
        <rdf:li>
          <rdf:Description>
            <CopasiMT:isDescribedBy rdf:resource="http://identifiers.org/omim/164760" />
          </rdf:Description>
        </rdf:li>
      </rdf:Bag>
    </dcterms:bibliographicCitation>
  </rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_82" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_52" stoichiometry="1"/>
          <Product metabolite="Metabolite_57" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4826" name="k59" value="18"/>
        </ListOfConstants>
        <KineticLaw function="Function_140" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_789">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_788">
              <SourceParameter reference="ModelValue_85"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_787">
              <SourceParameter reference="Metabolite_82"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_101" name="v102" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_101">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_99" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_14" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4825" name="k6" value="0.003"/>
          <Constant key="Parameter_4824" name="kr6" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_141" unitType="Default">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_784">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_785">
              <SourceParameter reference="Compartment_2"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_786">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_790">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_791">
              <SourceParameter reference="Metabolite_99"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_792">
              <SourceParameter reference="Metabolite_14"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_102" name="v103" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_102">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_29" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_60" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4823" name="k6" value="0.003"/>
          <Constant key="Parameter_4822" name="kr6" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_142" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_798">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_797">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_796">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_795">
              <SourceParameter reference="Metabolite_29"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_794">
              <SourceParameter reference="Metabolite_60"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_103" name="v104" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_103">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_30" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_61" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4821" name="k6" value="0.003"/>
          <Constant key="Parameter_4820" name="kr6" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_143" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_802">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_801">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_800">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_799">
              <SourceParameter reference="Metabolite_30"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_793">
              <SourceParameter reference="Metabolite_61"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_104" name="v105" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_104">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4819" name="k6" value="0.003"/>
          <Constant key="Parameter_4818" name="kr6" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_144" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_807">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_806">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_805">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_804">
              <SourceParameter reference="Metabolite_16"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_803">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_105" name="v106" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_105">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_22" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_85" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4817" name="k4" value="1.038e-05"/>
          <Constant key="Parameter_4816" name="kr4" value="0.0996"/>
        </ListOfConstants>
        <KineticLaw function="Function_145" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_812">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_811">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_810">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_809">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_808">
              <SourceParameter reference="Metabolite_22"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_813">
              <SourceParameter reference="Metabolite_85"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_106" name="v107" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_106">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_85" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
          <Product metabolite="Metabolite_16" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4815" name="k5" value="0.885183"/>
        </ListOfConstants>
        <KineticLaw function="Function_146" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_819">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_818">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_817">
              <SourceParameter reference="Metabolite_85"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_107" name="v108" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_107">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_24" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4814" name="k6" value="0.003"/>
          <Constant key="Parameter_4813" name="kr6" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_147" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_814">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_815">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_816">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_820">
              <SourceParameter reference="Metabolite_17"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_821">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_108" name="v109" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_108">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_24" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_86" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4812" name="k4" value="1.038e-05"/>
          <Constant key="Parameter_4811" name="kr4" value="0.0996"/>
        </ListOfConstants>
        <KineticLaw function="Function_148" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_826">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_825">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_824">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_823">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_822">
              <SourceParameter reference="Metabolite_24"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_827">
              <SourceParameter reference="Metabolite_86"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_109" name="v110" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_109">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_86" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
          <Product metabolite="Metabolite_17" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4810" name="k5" value="0.885183"/>
        </ListOfConstants>
        <KineticLaw function="Function_149" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_833">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_832">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_831">
              <SourceParameter reference="Metabolite_86"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_110" name="v111" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_110">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4809" name="k6" value="0.003"/>
          <Constant key="Parameter_4808" name="kr6" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_150" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_828">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_829">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_830">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_834">
              <SourceParameter reference="Metabolite_18"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_835">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_111" name="v112" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_111">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_26" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_87" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4807" name="k4" value="1.038e-05"/>
          <Constant key="Parameter_4806" name="kr4" value="0.0996"/>
        </ListOfConstants>
        <KineticLaw function="Function_151" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_840">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_839">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_838">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_837">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_836">
              <SourceParameter reference="Metabolite_26"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_841">
              <SourceParameter reference="Metabolite_87"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_112" name="v113" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_112">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_87" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
          <Product metabolite="Metabolite_18" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4805" name="k5" value="0.885183"/>
        </ListOfConstants>
        <KineticLaw function="Function_152" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_847">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_846">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_845">
              <SourceParameter reference="Metabolite_87"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_113" name="v114" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_113">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4804" name="k6" value="0.003"/>
          <Constant key="Parameter_4803" name="kr6" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_153" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_842">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_843">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_844">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_848">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_849">
              <SourceParameter reference="Metabolite_62"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_114" name="v115" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_114">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_31" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_88" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4802" name="k4" value="1.038e-05"/>
          <Constant key="Parameter_4801" name="kr4" value="0.0996"/>
        </ListOfConstants>
        <KineticLaw function="Function_154" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_854">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_853">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_852">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_851">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_850">
              <SourceParameter reference="Metabolite_31"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_855">
              <SourceParameter reference="Metabolite_88"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_115" name="v116" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_115">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_88" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
          <Product metabolite="Metabolite_62" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4800" name="k5" value="0.885183"/>
        </ListOfConstants>
        <KineticLaw function="Function_155" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_861">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_860">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_859">
              <SourceParameter reference="Metabolite_88"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_116" name="v117" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_116">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4799" name="k6" value="0.003"/>
          <Constant key="Parameter_4798" name="kr6" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_156" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_856">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_857">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_858">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_862">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_863">
              <SourceParameter reference="Metabolite_63"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_117" name="v118" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_117">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_32" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_89" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4797" name="k4" value="1.038e-05"/>
          <Constant key="Parameter_4796" name="kr4" value="0.0996"/>
        </ListOfConstants>
        <KineticLaw function="Function_157" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_868">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_867">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_866">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_865">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_864">
              <SourceParameter reference="Metabolite_32"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_869">
              <SourceParameter reference="Metabolite_89"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_118" name="v119" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_118">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_89" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
          <Product metabolite="Metabolite_63" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4795" name="k5" value="0.885183"/>
        </ListOfConstants>
        <KineticLaw function="Function_158" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_875">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_874">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_873">
              <SourceParameter reference="Metabolite_89"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_119" name="v120" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_119">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_64" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4794" name="k6" value="0.003"/>
          <Constant key="Parameter_4793" name="kr6" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_159" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_870">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_871">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_872">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_876">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_877">
              <SourceParameter reference="Metabolite_64"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_120" name="v121" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_120">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_33" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_90" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4792" name="k4" value="1.038e-05"/>
          <Constant key="Parameter_4791" name="kr4" value="0.0996"/>
        </ListOfConstants>
        <KineticLaw function="Function_160" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_882">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_881">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_880">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_879">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_878">
              <SourceParameter reference="Metabolite_33"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_883">
              <SourceParameter reference="Metabolite_90"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_121" name="v122" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_121">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_90" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
          <Product metabolite="Metabolite_64" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4790" name="k5" value="0.885183"/>
        </ListOfConstants>
        <KineticLaw function="Function_161" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_889">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_888">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_887">
              <SourceParameter reference="Metabolite_90"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_122" name="v123" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_122">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_34" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_65" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4789" name="k6" value="0.003"/>
          <Constant key="Parameter_4788" name="kr6" value="0.3"/>
        </ListOfConstants>
        <KineticLaw function="Function_162" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_884">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_885">
              <SourceParameter reference="ModelValue_9"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_886">
              <SourceParameter reference="ModelValue_10"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_890">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_891">
              <SourceParameter reference="Metabolite_65"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_123" name="v124" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_123">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_34" stoichiometry="1"/>
          <Substrate metabolite="Metabolite_11" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_91" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4787" name="k4" value="1.038e-05"/>
          <Constant key="Parameter_4786" name="kr4" value="0.0996"/>
        </ListOfConstants>
        <KineticLaw function="Function_163" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_896">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_895">
              <SourceParameter reference="ModelValue_6"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_894">
              <SourceParameter reference="ModelValue_7"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_893">
              <SourceParameter reference="Metabolite_11"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_892">
              <SourceParameter reference="Metabolite_34"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_897">
              <SourceParameter reference="Metabolite_91"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
      <Reaction key="Reaction_124" name="v125" reversible="true" fast="false" addNoise="false">
        <MiriamAnnotation>
<rdf:RDF xmlns:dcterms="http://purl.org/dc/terms/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Reaction_124">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T12:13:32Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ListOfSubstrates>
          <Substrate metabolite="Metabolite_91" stoichiometry="1"/>
        </ListOfSubstrates>
        <ListOfProducts>
          <Product metabolite="Metabolite_65" stoichiometry="1"/>
          <Product metabolite="Metabolite_8" stoichiometry="1"/>
        </ListOfProducts>
        <ListOfConstants>
          <Constant key="Parameter_4785" name="k5" value="0.885183"/>
        </ListOfConstants>
        <KineticLaw function="Function_164" unitType="Default" scalingCompartment="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]">
          <ListOfCallParameters>
            <CallParameter functionParameter="FunctionParameter_903">
              <SourceParameter reference="Compartment_1"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_902">
              <SourceParameter reference="ModelValue_8"/>
            </CallParameter>
            <CallParameter functionParameter="FunctionParameter_901">
              <SourceParameter reference="Metabolite_91"/>
            </CallParameter>
          </ListOfCallParameters>
        </KineticLaw>
      </Reaction>
    </ListOfReactions>
    <ListOfModelParameterSets activeSet="ModelParameterSet_0">
      <ModelParameterSet key="ModelParameterSet_0" name="Initial State">
        <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#ModelParameterSet_0">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T15:18:10Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
        </MiriamAnnotation>
        <ModelParameterGroup cn="String=Initial Time" type="Group">
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK" value="0" type="Model" simulationType="time"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Compartment Sizes" type="Group">
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[extracellular volume]" value="1" type="Compartment" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm]" value="1" type="Compartment" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[endosomal volume]" value="4.3000000000000003e-06" type="Compartment" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Species Values" type="Group">
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[extracellular volume],Vector=Metabolites[EGF]" value="4962" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[extracellular volume],Vector=Metabolites[EGFR]" value="50000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR^2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGFRi]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Prot]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Proti]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi^2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Prot]" value="81000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[GAP]" value="12000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGFi]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Grb2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Grb2-Sos]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Grb2-Sos-Ras-GDP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Grb2-Sos-Ras-GTP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Grb2]" value="11000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Sos]" value="26300" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Sos]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Ras-GDP]" value="72000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Sos-Ras-GDP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Ras-GTP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Sos-Ras-GTP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Grb2-Sos]" value="40000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Shc]" value="101000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GDP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GTP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Shc*-Grb2-Sos]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Shc*-Grb2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Shc*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Raf]" value="40000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Raf-Ras-GTP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Ras-GTP*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Phosphotase1]" value="40000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Raf*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Raf*-P'ase]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEK]" value="22000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEK-Raf*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEK-P]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEK-P-Raf*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEK-PP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEK-PP-P'ase2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Phosphatase2]" value="40000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEK-P-P'ase2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERK]" value="21000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERK-MEK-PP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERK-P]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERK-P-MEK-PP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERK-PP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Phosphotase3]" value="10000000" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERK-PP-P'ase3]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERK-P-P'ase3]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*-Grb2]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*-Grb2-Sos]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*-Grb2-Sos-Ras-GDP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2-GAP-Shc*-Grb2-Sos-Ras-GTP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Rasi-GTP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Rafi-Rasi-GTP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Rasi-GTP*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Rafi*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[Rafi*-P'ase]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEKi-Rafi*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEKi-P]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEKi-P-Rafi*]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEKi-PP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEKi-PP-P'ase2i]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[MEKi-P-P'ase2i]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERKi-MEKi-PP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERKi-P]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERKi-P-MEKi-PP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERKi-PP]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERKi-PP-P'ase3i]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[ERKi-P-P'ase3i]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGFRideg]" value="0" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFRi*^2deg]" value="0" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Sos-Prot]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Sos-Ras-GDP-Prot]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Grb2-Sos-Ras-GTP-Prot]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Prot]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Prot]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GDP-Prot]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[EGF-EGFR*^2-GAP-Shc*-Grb2-Sos-Ras-GTP-Prot]" value="0" type="Species" simulationType="reactions"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[t_Raf*]" value="0" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[t_Ras_GTP]" value="0" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[t_MEK_PP]" value="0" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[t_ERK_PP]" value="0" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[t_SHC_P_t]" value="0" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[cytoplasm],Vector=Metabolites[t_EGF_EGFR*]" value="0" type="Species" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[endosomal volume],Vector=Metabolites[EGFideg]" value="0" type="Species" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Compartments[endosomal volume],Vector=Metabolites[EGF-EGFR*^2-GAP]" value="0" type="Species" simulationType="reactions"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Initial Global Quantities" type="Group">
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k1]" value="0.0030000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr1]" value="0.22800000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr2]" value="6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k2]" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k3]" value="60" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr3]" value="0.59999999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k4]" value="1.0380000000000001e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr4]" value="0.099599999999999994" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k5]" value="0.88518261214767779" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k6]" value="0.0030000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr6]" value="0.29999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k7]" value="0.0030000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k8]" value="0.0001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr8]" value="12" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k10]" value="3.2558099999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr10]" value="0.66000000000000003" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr11]" value="6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k11]" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr12]" value="0.59999999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k12]" value="60" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k13]" value="130.19999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k14]" value="0.0001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr14]" value="12" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k15]" value="600000" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr16]" value="16.5" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k16]" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr17]" value="3.6000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k17]" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr18]" value="78" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k18]" value="0.0015" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr19]" value="1.0000000000000001e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k19]" value="30" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr20]" value="24" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k20]" value="0.00021000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k21]" value="1.3799999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr21]" value="2.1999999999999999e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k22]" value="0.0020999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr22]" value="6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k23]" value="360" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr23]" value="36" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k24]" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr24]" value="33" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr25]" value="1.284" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k25]" value="0.001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k28]" value="0.0001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr28]" value="0.318" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k29]" value="60" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr29]" value="6.9999999999999994e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr32]" value="2.4000000000000001e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k32]" value="6" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k33]" value="12" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr33]" value="0.0020999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k34]" value="1.8" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr34]" value="0.00044999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k35]" value="0.089999999999999997" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr35]" value="0.00044999999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[Vm36]" value="61200" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[Km36]" value="200000000000000" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k37]" value="18" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr37]" value="9.0000000000000006e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k40]" value="0.0030000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr40]" value="3.8399999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr41]" value="2.5739999999999998" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k41]" value="0.0030000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k42]" value="0.0071000000000000004" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr42]" value="12" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k43]" value="60" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr44]" value="1.0998000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k44]" value="0.0011100000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k45]" value="210" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k47]" value="174" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr48]" value="48" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k48]" value="0.0014300000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k49]" value="3.48" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr50]" value="30" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k50]" value="2.5000000000000001e-05" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k52]" value="0.0053400000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr52]" value="1.98" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k53]" value="960" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k55]" value="342" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr56]" value="36" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k56]" value="0.0014499999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k57]" value="16.199999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr58]" value="30" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k58]" value="0.00050000000000000001" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k59]" value="18" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k60]" value="0.04002" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k61]" value="0.010019999999999999" type="ModelValue" simulationType="fixed"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[C_internalization]" value="49245.732433505356" type="ModelValue" simulationType="assignment"/>
          <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[total_Receptors]" value="50000" type="ModelValue" simulationType="fixed"/>
        </ModelParameterGroup>
        <ModelParameterGroup cn="String=Kinetic Parameters" type="Group">
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v1]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v1],ParameterGroup=Parameters,Parameter=k1" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v1],ParameterGroup=Parameters,Parameter=kr1" value="0.22800000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr1],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v2]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v2],ParameterGroup=Parameters,Parameter=k2" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v2],ParameterGroup=Parameters,Parameter=kr2" value="6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v3]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v3],ParameterGroup=Parameters,Parameter=k3" value="60" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v3],ParameterGroup=Parameters,Parameter=kr3" value="0.59999999999999998" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v4]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v4],ParameterGroup=Parameters,Parameter=k4" value="1.0380000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v4],ParameterGroup=Parameters,Parameter=kr4" value="0.099599999999999994" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v5]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v5],ParameterGroup=Parameters,Parameter=k5" value="0.88518261214767779" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k5],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v6]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v6],ParameterGroup=Parameters,Parameter=k6" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v6],ParameterGroup=Parameters,Parameter=kr6" value="0.29999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v7]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v7],ParameterGroup=Parameters,Parameter=k7" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k7],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v8]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v8],ParameterGroup=Parameters,Parameter=k8" value="0.0001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k8],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v8],ParameterGroup=Parameters,Parameter=kr8" value="12" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr8],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v9]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v9],ParameterGroup=Parameters,Parameter=k7" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k7],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v10]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v10],ParameterGroup=Parameters,Parameter=k10" value="3.2558099999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k10],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v10],ParameterGroup=Parameters,Parameter=kr10" value="0.66000000000000003" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr10],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v11]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v11],ParameterGroup=Parameters,Parameter=k2" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v11],ParameterGroup=Parameters,Parameter=kr2" value="6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr2],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v12]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v12],ParameterGroup=Parameters,Parameter=k3" value="60" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v12],ParameterGroup=Parameters,Parameter=kr3" value="0.59999999999999998" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr3],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v13]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v13],ParameterGroup=Parameters,Parameter=k13" value="130.19999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k13],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v14]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v14],ParameterGroup=Parameters,Parameter=k14" value="0.0001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k14],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v14],ParameterGroup=Parameters,Parameter=kr14" value="12" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr14],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v15]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v15],ParameterGroup=Parameters,Parameter=k15" value="600000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k15],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v16]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v16],ParameterGroup=Parameters,Parameter=k16" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k16],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v16],ParameterGroup=Parameters,Parameter=kr16" value="16.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr16],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v17]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v17],ParameterGroup=Parameters,Parameter=k17" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k17],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v17],ParameterGroup=Parameters,Parameter=kr17" value="3.6000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr17],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v18]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v18],ParameterGroup=Parameters,Parameter=k18" value="0.0015" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k18],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v18],ParameterGroup=Parameters,Parameter=kr18" value="78" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr18],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v19]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v19],ParameterGroup=Parameters,Parameter=k19" value="30" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k19],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v19],ParameterGroup=Parameters,Parameter=kr19" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr19],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v20]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v20],ParameterGroup=Parameters,Parameter=k20" value="0.00021000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k20],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v20],ParameterGroup=Parameters,Parameter=kr20" value="24" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr20],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v21]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v21],ParameterGroup=Parameters,Parameter=k21" value="1.3799999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k21],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v21],ParameterGroup=Parameters,Parameter=kr21" value="2.1999999999999999e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr21],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v22]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v22],ParameterGroup=Parameters,Parameter=k22" value="0.0020999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k22],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v22],ParameterGroup=Parameters,Parameter=kr22" value="6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr22],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v23]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v23],ParameterGroup=Parameters,Parameter=k23" value="360" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k23],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v23],ParameterGroup=Parameters,Parameter=kr23" value="36" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr23],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v24]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v24],ParameterGroup=Parameters,Parameter=k24" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k24],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v24],ParameterGroup=Parameters,Parameter=kr24" value="33" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr24],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v25]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v25],ParameterGroup=Parameters,Parameter=k25" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k25],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v25],ParameterGroup=Parameters,Parameter=kr25" value="1.284" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr25],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v26]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v26],ParameterGroup=Parameters,Parameter=k18" value="0.0015" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k18],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v26],ParameterGroup=Parameters,Parameter=kr18" value="78" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr18],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v27]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v27],ParameterGroup=Parameters,Parameter=k19" value="30" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k19],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v27],ParameterGroup=Parameters,Parameter=kr19" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr19],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v28]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v28],ParameterGroup=Parameters,Parameter=k28" value="0.0001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k28],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v28],ParameterGroup=Parameters,Parameter=kr28" value="0.318" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr28],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v29]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v29],ParameterGroup=Parameters,Parameter=k29" value="60" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k29],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v29],ParameterGroup=Parameters,Parameter=kr29" value="6.9999999999999994e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr29],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v30]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v30],ParameterGroup=Parameters,Parameter=k20" value="0.00021000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k20],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v30],ParameterGroup=Parameters,Parameter=kr20" value="24" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr20],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v31]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v31],ParameterGroup=Parameters,Parameter=k21" value="1.3799999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k21],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v31],ParameterGroup=Parameters,Parameter=kr21" value="2.1999999999999999e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr21],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v32]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v32],ParameterGroup=Parameters,Parameter=k32" value="6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k32],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v32],ParameterGroup=Parameters,Parameter=kr32" value="2.4000000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr32],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v33]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v33],ParameterGroup=Parameters,Parameter=k33" value="12" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k33],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v33],ParameterGroup=Parameters,Parameter=kr33" value="0.0020999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr33],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v34]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v34],ParameterGroup=Parameters,Parameter=k34" value="1.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k34],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v34],ParameterGroup=Parameters,Parameter=kr34" value="0.00044999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr34],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v35]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v35],ParameterGroup=Parameters,Parameter=k35" value="0.089999999999999997" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k35],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v35],ParameterGroup=Parameters,Parameter=kr35" value="0.00044999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr35],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v36]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v36],ParameterGroup=Parameters,Parameter=Km36" value="200000000000000" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[Km36],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v36],ParameterGroup=Parameters,Parameter=Vm36" value="61200" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[Vm36],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v37]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v37],ParameterGroup=Parameters,Parameter=k37" value="18" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k37],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v37],ParameterGroup=Parameters,Parameter=kr37" value="9.0000000000000006e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr37],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v38]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v38],ParameterGroup=Parameters,Parameter=k24" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k24],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v38],ParameterGroup=Parameters,Parameter=kr24" value="33" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr24],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v39]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v39],ParameterGroup=Parameters,Parameter=k37" value="18" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k37],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v39],ParameterGroup=Parameters,Parameter=kr37" value="9.0000000000000006e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr37],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v40]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v40],ParameterGroup=Parameters,Parameter=k40" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k40],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v40],ParameterGroup=Parameters,Parameter=kr40" value="3.8399999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr40],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v41]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v41],ParameterGroup=Parameters,Parameter=k41" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k41],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v41],ParameterGroup=Parameters,Parameter=kr41" value="2.5739999999999998" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr41],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v42]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v42],ParameterGroup=Parameters,Parameter=k42" value="0.0071000000000000004" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k42],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v42],ParameterGroup=Parameters,Parameter=kr42" value="12" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr42],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v43]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v43],ParameterGroup=Parameters,Parameter=k43" value="60" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k43],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v44]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v44],ParameterGroup=Parameters,Parameter=k44" value="0.0011100000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k44],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v44],ParameterGroup=Parameters,Parameter=kr44" value="1.0998000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr44],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v45]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v45],ParameterGroup=Parameters,Parameter=k45" value="210" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k45],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v46]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v46],ParameterGroup=Parameters,Parameter=k44" value="0.0011100000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k44],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v46],ParameterGroup=Parameters,Parameter=kr44" value="1.0998000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr44],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v47]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v47],ParameterGroup=Parameters,Parameter=k47" value="174" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k47],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v48]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v48],ParameterGroup=Parameters,Parameter=k48" value="0.0014300000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k48],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v48],ParameterGroup=Parameters,Parameter=kr48" value="48" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr48],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v49]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v49],ParameterGroup=Parameters,Parameter=k49" value="3.48" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k49],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v50]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v50],ParameterGroup=Parameters,Parameter=k50" value="2.5000000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k50],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v50],ParameterGroup=Parameters,Parameter=kr50" value="30" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr50],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v51]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v51],ParameterGroup=Parameters,Parameter=k49" value="3.48" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k49],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v52]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v52],ParameterGroup=Parameters,Parameter=k52" value="0.0053400000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k52],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v52],ParameterGroup=Parameters,Parameter=kr52" value="1.98" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr52],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v53]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v53],ParameterGroup=Parameters,Parameter=k53" value="960" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k53],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v54]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v54],ParameterGroup=Parameters,Parameter=k52" value="0.0053400000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k52],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v54],ParameterGroup=Parameters,Parameter=kr52" value="1.98" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr52],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v55]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v55],ParameterGroup=Parameters,Parameter=k55" value="342" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k55],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v56]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v56],ParameterGroup=Parameters,Parameter=k56" value="0.0014499999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k56],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v56],ParameterGroup=Parameters,Parameter=kr56" value="36" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr56],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v57]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v57],ParameterGroup=Parameters,Parameter=k57" value="16.199999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k57],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v58]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v58],ParameterGroup=Parameters,Parameter=k58" value="0.00050000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k58],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v58],ParameterGroup=Parameters,Parameter=kr58" value="30" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr58],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v59]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v59],ParameterGroup=Parameters,Parameter=k59" value="18" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k59],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v60]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v60],ParameterGroup=Parameters,Parameter=k60" value="0.04002" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k60],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v61]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v61],ParameterGroup=Parameters,Parameter=k61" value="0.010019999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k61],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v62]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v62],ParameterGroup=Parameters,Parameter=k60" value="0.04002" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k60],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v63]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v63],ParameterGroup=Parameters,Parameter=k16" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k16],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v63],ParameterGroup=Parameters,Parameter=kr16" value="16.5" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr16],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v64]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v64],ParameterGroup=Parameters,Parameter=k17" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k17],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v64],ParameterGroup=Parameters,Parameter=kr17" value="3.6000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr17],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v65]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v65],ParameterGroup=Parameters,Parameter=k18" value="0.0015" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k18],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v65],ParameterGroup=Parameters,Parameter=kr18" value="78" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr18],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v66]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v66],ParameterGroup=Parameters,Parameter=k19" value="30" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k19],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v66],ParameterGroup=Parameters,Parameter=kr19" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr19],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v67]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v67],ParameterGroup=Parameters,Parameter=k20" value="0.00021000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k20],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v67],ParameterGroup=Parameters,Parameter=kr20" value="24" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr20],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v68]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v68],ParameterGroup=Parameters,Parameter=k21" value="1.3799999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k21],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v68],ParameterGroup=Parameters,Parameter=kr21" value="2.1999999999999999e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr21],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v69]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v69],ParameterGroup=Parameters,Parameter=k22" value="0.0020999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k22],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v69],ParameterGroup=Parameters,Parameter=kr22" value="6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr22],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v70]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v70],ParameterGroup=Parameters,Parameter=k23" value="360" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k23],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v70],ParameterGroup=Parameters,Parameter=kr23" value="36" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr23],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v71]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v71],ParameterGroup=Parameters,Parameter=k24" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k24],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v71],ParameterGroup=Parameters,Parameter=kr24" value="33" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr24],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v72]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v72],ParameterGroup=Parameters,Parameter=k25" value="0.001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k25],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v72],ParameterGroup=Parameters,Parameter=kr25" value="1.284" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr25],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v73]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v73],ParameterGroup=Parameters,Parameter=k18" value="0.0015" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k18],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v73],ParameterGroup=Parameters,Parameter=kr18" value="78" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr18],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v74]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v74],ParameterGroup=Parameters,Parameter=k19" value="30" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k19],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v74],ParameterGroup=Parameters,Parameter=kr19" value="1.0000000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr19],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v75]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v75],ParameterGroup=Parameters,Parameter=k28" value="0.0001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k28],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v75],ParameterGroup=Parameters,Parameter=kr28" value="0.318" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr28],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v76]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v76],ParameterGroup=Parameters,Parameter=k29" value="60" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k29],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v76],ParameterGroup=Parameters,Parameter=kr29" value="6.9999999999999994e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr29],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v77]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v77],ParameterGroup=Parameters,Parameter=k20" value="0.00021000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k20],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v77],ParameterGroup=Parameters,Parameter=kr20" value="24" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr20],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v78]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v78],ParameterGroup=Parameters,Parameter=k21" value="1.3799999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k21],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v78],ParameterGroup=Parameters,Parameter=kr21" value="2.1999999999999999e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr21],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v79]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v79],ParameterGroup=Parameters,Parameter=k32" value="6" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k32],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v79],ParameterGroup=Parameters,Parameter=kr32" value="2.4000000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr32],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v80]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v80],ParameterGroup=Parameters,Parameter=k34" value="1.8" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k34],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v80],ParameterGroup=Parameters,Parameter=kr34" value="0.00044999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr34],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v81]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v81],ParameterGroup=Parameters,Parameter=k37" value="18" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k37],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v81],ParameterGroup=Parameters,Parameter=kr37" value="9.0000000000000006e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr37],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v82]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v82],ParameterGroup=Parameters,Parameter=k37" value="18" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k37],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v82],ParameterGroup=Parameters,Parameter=kr37" value="9.0000000000000006e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr37],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v83]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v83],ParameterGroup=Parameters,Parameter=k41" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k41],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v83],ParameterGroup=Parameters,Parameter=kr41" value="2.5739999999999998" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr41],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v84]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v84],ParameterGroup=Parameters,Parameter=k42" value="0.0071000000000000004" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k42],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v84],ParameterGroup=Parameters,Parameter=kr42" value="12" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr42],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v85]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v85],ParameterGroup=Parameters,Parameter=k43" value="60" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k43],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v86]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v86],ParameterGroup=Parameters,Parameter=k44" value="0.0011100000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k44],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v86],ParameterGroup=Parameters,Parameter=kr44" value="1.0998000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr44],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v87]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v87],ParameterGroup=Parameters,Parameter=k45" value="210" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k45],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v88]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v88],ParameterGroup=Parameters,Parameter=k44" value="0.0011100000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k44],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v88],ParameterGroup=Parameters,Parameter=kr44" value="1.0998000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr44],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v89]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v89],ParameterGroup=Parameters,Parameter=k47" value="174" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k47],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v90]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v90],ParameterGroup=Parameters,Parameter=k48" value="0.0014300000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k48],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v90],ParameterGroup=Parameters,Parameter=kr48" value="48" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr48],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v91]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v91],ParameterGroup=Parameters,Parameter=k49" value="3.48" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k49],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v92]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v92],ParameterGroup=Parameters,Parameter=k50" value="2.5000000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k50],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v92],ParameterGroup=Parameters,Parameter=kr50" value="30" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr50],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v93]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v93],ParameterGroup=Parameters,Parameter=k49" value="3.48" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k49],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v94]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v94],ParameterGroup=Parameters,Parameter=k52" value="0.0053400000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k52],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v94],ParameterGroup=Parameters,Parameter=kr52" value="1.98" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr52],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v95]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v95],ParameterGroup=Parameters,Parameter=k53" value="960" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k53],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v96]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v96],ParameterGroup=Parameters,Parameter=k52" value="0.0053400000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k52],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v96],ParameterGroup=Parameters,Parameter=kr52" value="1.98" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr52],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v97]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v97],ParameterGroup=Parameters,Parameter=k55" value="342" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k55],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v98]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v98],ParameterGroup=Parameters,Parameter=k56" value="0.0014499999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k56],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v98],ParameterGroup=Parameters,Parameter=kr56" value="36" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr56],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v99]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v99],ParameterGroup=Parameters,Parameter=k57" value="16.199999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k57],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v100]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v100],ParameterGroup=Parameters,Parameter=k58" value="0.00050000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k58],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v100],ParameterGroup=Parameters,Parameter=kr58" value="30" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr58],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v101]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v101],ParameterGroup=Parameters,Parameter=k59" value="18" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k59],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v102]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v102],ParameterGroup=Parameters,Parameter=k6" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v102],ParameterGroup=Parameters,Parameter=kr6" value="0.29999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v103]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v103],ParameterGroup=Parameters,Parameter=k6" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v103],ParameterGroup=Parameters,Parameter=kr6" value="0.29999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v104]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v104],ParameterGroup=Parameters,Parameter=k6" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v104],ParameterGroup=Parameters,Parameter=kr6" value="0.29999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v105]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v105],ParameterGroup=Parameters,Parameter=k6" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v105],ParameterGroup=Parameters,Parameter=kr6" value="0.29999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v106]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v106],ParameterGroup=Parameters,Parameter=k4" value="1.0380000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v106],ParameterGroup=Parameters,Parameter=kr4" value="0.099599999999999994" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v107]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v107],ParameterGroup=Parameters,Parameter=k5" value="0.88518261214767779" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k5],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v108]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v108],ParameterGroup=Parameters,Parameter=k6" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v108],ParameterGroup=Parameters,Parameter=kr6" value="0.29999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v109]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v109],ParameterGroup=Parameters,Parameter=k4" value="1.0380000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v109],ParameterGroup=Parameters,Parameter=kr4" value="0.099599999999999994" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v110]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v110],ParameterGroup=Parameters,Parameter=k5" value="0.88518261214767779" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k5],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v111]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v111],ParameterGroup=Parameters,Parameter=k6" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v111],ParameterGroup=Parameters,Parameter=kr6" value="0.29999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v112]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v112],ParameterGroup=Parameters,Parameter=k4" value="1.0380000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v112],ParameterGroup=Parameters,Parameter=kr4" value="0.099599999999999994" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v113]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v113],ParameterGroup=Parameters,Parameter=k5" value="0.88518261214767779" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k5],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v114]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v114],ParameterGroup=Parameters,Parameter=k6" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v114],ParameterGroup=Parameters,Parameter=kr6" value="0.29999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v115]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v115],ParameterGroup=Parameters,Parameter=k4" value="1.0380000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v115],ParameterGroup=Parameters,Parameter=kr4" value="0.099599999999999994" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v116]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v116],ParameterGroup=Parameters,Parameter=k5" value="0.88518261214767779" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k5],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v117]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v117],ParameterGroup=Parameters,Parameter=k6" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v117],ParameterGroup=Parameters,Parameter=kr6" value="0.29999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v118]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v118],ParameterGroup=Parameters,Parameter=k4" value="1.0380000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v118],ParameterGroup=Parameters,Parameter=kr4" value="0.099599999999999994" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v119]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v119],ParameterGroup=Parameters,Parameter=k5" value="0.88518261214767779" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k5],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v120]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v120],ParameterGroup=Parameters,Parameter=k6" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v120],ParameterGroup=Parameters,Parameter=kr6" value="0.29999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v121]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v121],ParameterGroup=Parameters,Parameter=k4" value="1.0380000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v121],ParameterGroup=Parameters,Parameter=kr4" value="0.099599999999999994" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v122]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v122],ParameterGroup=Parameters,Parameter=k5" value="0.88518261214767779" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k5],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v123]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v123],ParameterGroup=Parameters,Parameter=k6" value="0.0030000000000000001" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v123],ParameterGroup=Parameters,Parameter=kr6" value="0.29999999999999999" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr6],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v124]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v124],ParameterGroup=Parameters,Parameter=k4" value="1.0380000000000001e-05" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v124],ParameterGroup=Parameters,Parameter=kr4" value="0.099599999999999994" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[kr4],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
          <ModelParameterGroup cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v125]" type="Reaction">
            <ModelParameter cn="CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Reactions[v125],ParameterGroup=Parameters,Parameter=k5" value="0.88518261214767779" type="ReactionParameter" simulationType="assignment">
              <InitialExpression>
                &lt;CN=Root,Model=Schoeberl2002 - EGF MAPK,Vector=Values[k5],Reference=InitialValue>
              </InitialExpression>
            </ModelParameter>
          </ModelParameterGroup>
        </ModelParameterGroup>
      </ModelParameterSet>
    </ListOfModelParameterSets>
    <StateTemplate>
      <StateTemplateVariable objectReference="Model_0"/>
      <StateTemplateVariable objectReference="Metabolite_8"/>
      <StateTemplateVariable objectReference="Metabolite_32"/>
      <StateTemplateVariable objectReference="Metabolite_11"/>
      <StateTemplateVariable objectReference="Metabolite_63"/>
      <StateTemplateVariable objectReference="Metabolite_50"/>
      <StateTemplateVariable objectReference="Metabolite_57"/>
      <StateTemplateVariable objectReference="Metabolite_16"/>
      <StateTemplateVariable objectReference="Metabolite_99"/>
      <StateTemplateVariable objectReference="Metabolite_14"/>
      <StateTemplateVariable objectReference="Metabolite_22"/>
      <StateTemplateVariable objectReference="Metabolite_42"/>
      <StateTemplateVariable objectReference="Metabolite_69"/>
      <StateTemplateVariable objectReference="Metabolite_48"/>
      <StateTemplateVariable objectReference="Metabolite_74"/>
      <StateTemplateVariable objectReference="Metabolite_19"/>
      <StateTemplateVariable objectReference="Metabolite_23"/>
      <StateTemplateVariable objectReference="Metabolite_2"/>
      <StateTemplateVariable objectReference="Metabolite_9"/>
      <StateTemplateVariable objectReference="Metabolite_21"/>
      <StateTemplateVariable objectReference="Metabolite_37"/>
      <StateTemplateVariable objectReference="Metabolite_31"/>
      <StateTemplateVariable objectReference="Metabolite_27"/>
      <StateTemplateVariable objectReference="Metabolite_38"/>
      <StateTemplateVariable objectReference="Metabolite_7"/>
      <StateTemplateVariable objectReference="Metabolite_61"/>
      <StateTemplateVariable objectReference="Metabolite_62"/>
      <StateTemplateVariable objectReference="Metabolite_33"/>
      <StateTemplateVariable objectReference="Metabolite_65"/>
      <StateTemplateVariable objectReference="Metabolite_17"/>
      <StateTemplateVariable objectReference="Metabolite_26"/>
      <StateTemplateVariable objectReference="Metabolite_52"/>
      <StateTemplateVariable objectReference="Metabolite_44"/>
      <StateTemplateVariable objectReference="Metabolite_15"/>
      <StateTemplateVariable objectReference="Metabolite_29"/>
      <StateTemplateVariable objectReference="Metabolite_5"/>
      <StateTemplateVariable objectReference="Metabolite_34"/>
      <StateTemplateVariable objectReference="Metabolite_41"/>
      <StateTemplateVariable objectReference="Metabolite_4"/>
      <StateTemplateVariable objectReference="Metabolite_54"/>
      <StateTemplateVariable objectReference="Metabolite_1"/>
      <StateTemplateVariable objectReference="Metabolite_24"/>
      <StateTemplateVariable objectReference="Metabolite_72"/>
      <StateTemplateVariable objectReference="Metabolite_78"/>
      <StateTemplateVariable objectReference="Metabolite_64"/>
      <StateTemplateVariable objectReference="Metabolite_68"/>
      <StateTemplateVariable objectReference="Metabolite_40"/>
      <StateTemplateVariable objectReference="Metabolite_60"/>
      <StateTemplateVariable objectReference="Metabolite_25"/>
      <StateTemplateVariable objectReference="Metabolite_46"/>
      <StateTemplateVariable objectReference="Metabolite_20"/>
      <StateTemplateVariable objectReference="Metabolite_13"/>
      <StateTemplateVariable objectReference="Metabolite_66"/>
      <StateTemplateVariable objectReference="Metabolite_28"/>
      <StateTemplateVariable objectReference="Metabolite_35"/>
      <StateTemplateVariable objectReference="Metabolite_58"/>
      <StateTemplateVariable objectReference="Metabolite_76"/>
      <StateTemplateVariable objectReference="Metabolite_82"/>
      <StateTemplateVariable objectReference="Metabolite_87"/>
      <StateTemplateVariable objectReference="Metabolite_79"/>
      <StateTemplateVariable objectReference="Metabolite_51"/>
      <StateTemplateVariable objectReference="Metabolite_55"/>
      <StateTemplateVariable objectReference="Metabolite_47"/>
      <StateTemplateVariable objectReference="Metabolite_73"/>
      <StateTemplateVariable objectReference="Metabolite_88"/>
      <StateTemplateVariable objectReference="Metabolite_85"/>
      <StateTemplateVariable objectReference="Metabolite_43"/>
      <StateTemplateVariable objectReference="Metabolite_12"/>
      <StateTemplateVariable objectReference="Metabolite_90"/>
      <StateTemplateVariable objectReference="Metabolite_10"/>
      <StateTemplateVariable objectReference="Metabolite_59"/>
      <StateTemplateVariable objectReference="Metabolite_86"/>
      <StateTemplateVariable objectReference="Metabolite_39"/>
      <StateTemplateVariable objectReference="Metabolite_75"/>
      <StateTemplateVariable objectReference="Metabolite_3"/>
      <StateTemplateVariable objectReference="Metabolite_71"/>
      <StateTemplateVariable objectReference="Metabolite_56"/>
      <StateTemplateVariable objectReference="Metabolite_53"/>
      <StateTemplateVariable objectReference="Metabolite_89"/>
      <StateTemplateVariable objectReference="Metabolite_80"/>
      <StateTemplateVariable objectReference="Metabolite_67"/>
      <StateTemplateVariable objectReference="Metabolite_18"/>
      <StateTemplateVariable objectReference="Metabolite_30"/>
      <StateTemplateVariable objectReference="Metabolite_91"/>
      <StateTemplateVariable objectReference="Metabolite_36"/>
      <StateTemplateVariable objectReference="Metabolite_77"/>
      <StateTemplateVariable objectReference="Metabolite_6"/>
      <StateTemplateVariable objectReference="Metabolite_45"/>
      <StateTemplateVariable objectReference="Metabolite_70"/>
      <StateTemplateVariable objectReference="Metabolite_49"/>
      <StateTemplateVariable objectReference="Metabolite_81"/>
      <StateTemplateVariable objectReference="Metabolite_92"/>
      <StateTemplateVariable objectReference="Metabolite_93"/>
      <StateTemplateVariable objectReference="Metabolite_94"/>
      <StateTemplateVariable objectReference="Metabolite_95"/>
      <StateTemplateVariable objectReference="Metabolite_96"/>
      <StateTemplateVariable objectReference="Metabolite_97"/>
      <StateTemplateVariable objectReference="ModelValue_8"/>
      <StateTemplateVariable objectReference="ModelValue_88"/>
      <StateTemplateVariable objectReference="Metabolite_0"/>
      <StateTemplateVariable objectReference="Metabolite_83"/>
      <StateTemplateVariable objectReference="Metabolite_84"/>
      <StateTemplateVariable objectReference="Metabolite_98"/>
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
      <StateTemplateVariable objectReference="ModelValue_64"/>
      <StateTemplateVariable objectReference="ModelValue_65"/>
      <StateTemplateVariable objectReference="ModelValue_66"/>
      <StateTemplateVariable objectReference="ModelValue_67"/>
      <StateTemplateVariable objectReference="ModelValue_68"/>
      <StateTemplateVariable objectReference="ModelValue_69"/>
      <StateTemplateVariable objectReference="ModelValue_70"/>
      <StateTemplateVariable objectReference="ModelValue_71"/>
      <StateTemplateVariable objectReference="ModelValue_72"/>
      <StateTemplateVariable objectReference="ModelValue_73"/>
      <StateTemplateVariable objectReference="ModelValue_74"/>
      <StateTemplateVariable objectReference="ModelValue_75"/>
      <StateTemplateVariable objectReference="ModelValue_76"/>
      <StateTemplateVariable objectReference="ModelValue_77"/>
      <StateTemplateVariable objectReference="ModelValue_78"/>
      <StateTemplateVariable objectReference="ModelValue_79"/>
      <StateTemplateVariable objectReference="ModelValue_80"/>
      <StateTemplateVariable objectReference="ModelValue_81"/>
      <StateTemplateVariable objectReference="ModelValue_82"/>
      <StateTemplateVariable objectReference="ModelValue_83"/>
      <StateTemplateVariable objectReference="ModelValue_84"/>
      <StateTemplateVariable objectReference="ModelValue_85"/>
      <StateTemplateVariable objectReference="ModelValue_86"/>
      <StateTemplateVariable objectReference="ModelValue_87"/>
      <StateTemplateVariable objectReference="ModelValue_89"/>
    </StateTemplate>
    <InitialState type="initialState">
      0 0 0 81000 0 40000 10000000 0 0 0 0 0 0 0 0 11000 72000 0 0 26300 0 0 40000 40000 0 0 0 0 0 0 0 21000000 22000000 0 0 0 0 40000 0 0 50000 0 0 0 0 0 0 0 0 0 0 0 0 101000 0 0 0 0 0 0 0 0 0 0 0 0 0 12000 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.88518261214767779 49245.732433505356 4962 0 0 0 1 1 4.3000000000000003e-06 0.0030000000000000001 0.22800000000000001 6 0.001 60 0.59999999999999998 1.0380000000000001e-05 0.099599999999999994 0.0030000000000000001 0.29999999999999999 0.0030000000000000001 0.0001 12 3.2558099999999999 0.66000000000000003 6 0.001 0.59999999999999998 60 130.19999999999999 0.0001 12 600000 16.5 0.001 3.6000000000000001 0.001 78 0.0015 1.0000000000000001e-05 30 24 0.00021000000000000001 1.3799999999999999 2.1999999999999999e-05 0.0020999999999999999 6 360 36 0.001 33 1.284 0.001 0.0001 0.318 60 6.9999999999999994e-05 2.4000000000000001e-05 6 12 0.0020999999999999999 1.8 0.00044999999999999999 0.089999999999999997 0.00044999999999999999 61200 200000000000000 18 9.0000000000000006e-05 0.0030000000000000001 3.8399999999999999 2.5739999999999998 0.0030000000000000001 0.0071000000000000004 12 60 1.0998000000000001 0.0011100000000000001 210 174 48 0.0014300000000000001 3.48 30 2.5000000000000001e-05 0.0053400000000000001 1.98 960 342 36 0.0014499999999999999 16.199999999999999 30 0.00050000000000000001 18 0.04002 0.010019999999999999 50000 
    </InitialState>
  </Model>
  <ListOfTasks>
    <Task key="Task_13" name="Steady-State" type="steadyState" scheduled="true" updateModel="false">
      <Report reference="Report_22" target="Schoeberl_ss.out" append="1" confirmOverwrite="0"/>
      <Problem>
        <Parameter name="JacobianRequested" type="bool" value="1"/>
        <Parameter name="StabilityAnalysisRequested" type="bool" value="1"/>
      </Problem>
      <Method name="Enhanced Newton" type="EnhancedNewton">
        <Parameter name="Resolution" type="unsignedFloat" value="9.9999999999999995e-08"/>
        <Parameter name="Derivation Factor" type="unsignedFloat" value="0.001"/>
        <Parameter name="Use Newton" type="bool" value="1"/>
        <Parameter name="Use Integration" type="bool" value="1"/>
        <Parameter name="Use Back Integration" type="bool" value="0"/>
        <Parameter name="Accept Negative Concentrations" type="bool" value="0"/>
        <Parameter name="Iteration Limit" type="unsignedInteger" value="50"/>
        <Parameter name="Maximum duration for forward integration" type="unsignedFloat" value="1000000000"/>
        <Parameter name="Maximum duration for backward integration" type="unsignedFloat" value="1000000"/>
        <Parameter name="Target Criterion" type="string" value="Distance"/>
      </Method>
    </Task>
    <Task key="Task_12" name="Time-Course" type="timeCourse" scheduled="false" updateModel="false">
      <Report reference="Report_1" target="" append="1" confirmOverwrite="1"/>
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
        <Parameter name="Continue on Simultaneous Events" type="bool" value="1"/>
      </Problem>
      <Method name="Deterministic (LSODA)" type="Deterministic(LSODA)">
        <Parameter name="Integrate Reduced Model" type="bool" value="0"/>
        <Parameter name="Relative Tolerance" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Absolute Tolerance" type="unsignedFloat" value="9.9999999999999998e-13"/>
        <Parameter name="Max Internal Steps" type="unsignedInteger" value="10000"/>
        <Parameter name="Max Internal Step Size" type="unsignedFloat" value="0"/>
      </Method>
    </Task>
    <Task key="Task_11" name="Scan" type="scan" scheduled="false" updateModel="false">
      <Problem>
        <Parameter name="Subtask" type="unsignedInteger" value="1"/>
        <ParameterGroup name="ScanItems">
        </ParameterGroup>
        <Parameter name="Output in subtask" type="bool" value="1"/>
        <Parameter name="Adjust initial conditions" type="bool" value="0"/>
        <Parameter name="Continue on Error" type="bool" value="0"/>
      </Problem>
      <Method name="Scan Framework" type="ScanFramework">
      </Method>
    </Task>
    <Task key="Task_10" name="Elementary Flux Modes" type="fluxMode" scheduled="false" updateModel="false">
      <Report reference="Report_9" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="EFM Algorithm" type="EFMAlgorithm">
      </Method>
    </Task>
    <Task key="Task_9" name="Optimization" type="optimization" scheduled="false" updateModel="false">
      <Report reference="Report_8" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Subtask" type="cn" value="CN=Root,Vector=TaskList[Steady-State]"/>
        <ParameterText name="ObjectiveExpression" type="expression">
          
        </ParameterText>
        <Parameter name="Maximize" type="bool" value="0"/>
        <Parameter name="Randomize Start Values" type="bool" value="0"/>
        <Parameter name="Calculate Statistics" type="bool" value="0"/>
        <ParameterGroup name="OptimizationItemList">
        </ParameterGroup>
        <ParameterGroup name="OptimizationConstraintList">
        </ParameterGroup>
      </Problem>
      <Method name="Particle Swarm" type="ParticleSwarm">
        <Parameter name="Log Verbosity" type="unsignedInteger" value="0"/>
        <Parameter name="Iteration Limit" type="unsignedInteger" value="50"/>
        <Parameter name="Swarm Size" type="unsignedInteger" value="10"/>
        <Parameter name="Std. Deviation" type="unsignedFloat" value="9.9999999999999995e-07"/>
        <Parameter name="Random Number Generator" type="unsignedInteger" value="1"/>
        <Parameter name="Seed" type="unsignedInteger" value="0"/>
        <Parameter name="Stop after # Stalled Iterations" type="unsignedInteger" value="0"/>
      </Method>
    </Task>
    <Task key="Task_8" name="Parameter Estimation" type="parameterFitting" scheduled="false" updateModel="false">
      <Report reference="Report_7" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_6" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_13"/>
      </Problem>
      <Method name="MCA Method (Reder)" type="MCAMethod(Reder)">
        <Parameter name="Modulation Factor" type="unsignedFloat" value="1.0000000000000001e-09"/>
        <Parameter name="Use Reder" type="bool" value="1"/>
        <Parameter name="Use Smallbone" type="bool" value="1"/>
      </Method>
    </Task>
    <Task key="Task_6" name="Lyapunov Exponents" type="lyapunovExponents" scheduled="false" updateModel="false">
      <Report reference="Report_5" target="" append="1" confirmOverwrite="1"/>
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
      <Report reference="Report_4" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_4" name="Sensitivities" type="sensitivities" scheduled="false" updateModel="false">
      <Report reference="Report_3" target="" append="1" confirmOverwrite="1"/>
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
    <Task key="Task_3" name="Moieties" type="moieties" scheduled="false" updateModel="false">
      <Report reference="Report_0" target="" append="1" confirmOverwrite="1"/>
      <Problem>
      </Problem>
      <Method name="Householder Reduction" type="Householder">
      </Method>
    </Task>
    <Task key="Task_2" name="Cross Section" type="crosssection" scheduled="false" updateModel="false">
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
        <Parameter name="ConvergenceTolerance" type="float" value="0"/>
        <Parameter name="Threshold" type="float" value="0"/>
        <Parameter name="DelayOutputUntilConvergence" type="bool" value="0"/>
        <Parameter name="OutputConvergenceTolerance" type="float" value="0"/>
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
    <Task key="Task_1" name="Linear Noise Approximation" type="linearNoiseApproximation" scheduled="false" updateModel="false">
      <Report reference="Report_2" target="" append="1" confirmOverwrite="1"/>
      <Problem>
        <Parameter name="Steady-State" type="key" value="Task_13"/>
      </Problem>
      <Method name="Linear Noise Approximation" type="LinearNoiseApproximation">
      </Method>
    </Task>
    <Task key="Task_14" name="Time-Course Sensitivities" type="timeSensitivities" scheduled="false" updateModel="false">
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
    <Report key="Report_10" name="Steady-State" taskType="steadyState" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Steady-State]"/>
      </Footer>
    </Report>
    <Report key="Report_9" name="Elementary Flux Modes" taskType="fluxMode" separator="&#x09;" precision="6">
      <Comment>
        Automatically generated report.
      </Comment>
      <Footer>
        <Object cn="CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"/>
      </Footer>
    </Report>
    <Report key="Report_8" name="Optimization" taskType="optimization" separator="&#x09;" precision="6">
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
    <Report key="Report_7" name="Parameter Estimation" taskType="parameterFitting" separator="&#x09;" precision="6">
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
    <Report key="Report_6" name="Metabolic Control Analysis" taskType="metabolicControlAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_5" name="Lyapunov Exponents" taskType="lyapunovExponents" separator="&#x09;" precision="6">
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
    <Report key="Report_4" name="Time Scale Separation Analysis" taskType="timeScaleSeparationAnalysis" separator="&#x09;" precision="6">
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
    <Report key="Report_3" name="Sensitivities" taskType="sensitivities" separator="&#x09;" precision="6">
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
    <Report key="Report_2" name="Linear Noise Approximation" taskType="linearNoiseApproximation" separator="&#x09;" precision="6">
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
    <Report key="Report_1" name="Time-Course" taskType="timeCourse" separator="&#x09;" precision="6">
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
    <Report key="Report_0" name="Moieties" taskType="moieties" separator="&#x09;" precision="6">
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
    <Report key="Report_22" name="Speed test" taskType="steadyState" separator="&#x09;" precision="8">
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
<dcterms:W3CDTF>2020-12-28T15:18:04Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2020-12-28T15:18:04Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        s
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
<dcterms:W3CDTF>2020-12-28T15:18:04Z</dcterms:W3CDTF>
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
<dcterms:W3CDTF>2020-12-28T15:18:04Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        0.001*m^3
      </Expression>
    </UnitDefinition>
    <UnitDefinition key="Unit_65" name="minute" symbol="min">
      <MiriamAnnotation>
<rdf:RDF
xmlns:dcterms="http://purl.org/dc/terms/"
xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<rdf:Description rdf:about="#Unit_64">
<dcterms:created>
<rdf:Description>
<dcterms:W3CDTF>2020-12-28T15:18:04Z</dcterms:W3CDTF>
</rdf:Description>
</dcterms:created>
</rdf:Description>
</rdf:RDF>
      </MiriamAnnotation>
      <Expression>
        60*s
      </Expression>
    </UnitDefinition>
  </ListOfUnitDefinitions>
</COPASI>
