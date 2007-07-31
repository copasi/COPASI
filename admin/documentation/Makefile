# The following variables need to be adjusted to suit your installation
# od dblatex:

# The dblatex installation directory
DBLATEX_PATH=/home/usr

# These should be correct after DBLATEX_PATH
DBLATEX=$(DBLATEX_PATH)/bin/dblatex
DBLATEX_TEXINPUTS=$(DBLATEX_PATH)/share/dblatex/latex//:$(TEXINPUTS)
DBLATEX_SGML_CATALOG_FILES=$(SGML_CATALOG_FILES):/etc/xml/catalog

# dblatex environment for COPASI
COPASI_DBLATEX=dblatex
COPASI_TEXINPUTS=.:$(COPASI_DBLATEX):$(DBLATEX_TEXINPUTS):$(TEXINPUTS)

# xhtml environment for COPASI

COPASI_XHTML=dblatex/copasi_xhtml.xsl

.PHONY: CodeGuidelines.pdf \
	Redistribution.pdf \
	SBMLReaction.pdf

CodeGuidelines: CodeGuidelines.pdf CodeGuidelines.xhtml

CodeGuidelines_SOURCES = CodeGuidelines.xml CodeGuidelines_main.xml  

CodeGuidelines_IMAGES =

CodeGuidelines.tex: $(CodeGuidelines_SOURCES)
	SGML_CATALOG_FILES=$(DBLATEX_SGML_CATALOG_FILES) $(DBLATEX) -p $(COPASI_DBLATEX)/copasi.xsl -t tex CodeGuidelines.xml

CodeGuidelines.pdf: CodeGuidelines.tex \
		    $(CodeGuidelines_IMAGES)
	TEXINPUTS=$(COPASI_TEXINPUTS) pdflatex $<
#	TEXINPUTS=$(COPASI_TEXINPUTS) pdflatex $<
#	TEXINPUTS=$(COPASI_TEXINPUTS) pdflatex $<

CodeGuidelines.clean:
	-rm CodeGuidelines.aux CodeGuidelines.cb CodeGuidelines.glo \
	CodeGuidelines.idx CodeGuidelines.log CodeGuidelines.out \
	CodeGuidelines.pdf CodeGuidelines.tex CodeGuidelines.toc
	-rm -rf CodeGuidelines.xhtml

CodeGuidelines.xhtml: $(CodeGuidelines_SOURCES) \
	$(CodeGuidelines_IMAGES) \
	$(COPASI_XHTML)
	@[ -d $@ ] || mkdir $@
	touch $@
	(cd $@; \
	xsltproc ../$(COPASI_XHTML) ../CodeGuidelines.xml; \
	cd ..)



Redistribution: Redistribution.pdf

Redistribution_SOURCES = Redistribution.xml Redistribution_main.xml  

Redistribution_IMAGES =

Redistribution.tex: $(Redistribution_SOURCES)
	SGML_CATALOG_FILES=$(DBLATEX_SGML_CATALOG_FILES) $(DBLATEX) -p $(COPASI_DBLATEX)/copasi.xsl --style $(COPASI_DBLATEX)/copasi.sty -t tex Redistribution.xml

Redistribution.pdf: Redistribution.tex \
		    $(Redistribution_IMAGES)
	TEXINPUTS=$(COPASI_TEXINPUTS) pdflatex $<

SBMLReaction: SBMLReaction.pdf

SBMLReaction_SOURCES = SBMLReaction.tex

SBMLReaction.pdf: $(SBMLReaction_SOURCES)
	TEXINPUTS=$(COPASI_TEXINPUTS) pdflatex $<
