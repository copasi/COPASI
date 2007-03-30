# The following variables need to be adjusted to suit your installation
# od dblatex:

# The dblatex installation directory
DBLATEX_PATH=/usr/local/dblatex

# These should be correct after DBLATEX_PATH
DBLATEX=$(DBLATEX_PATH)/bin/dblatex
DBLATEX_TEXINPUTS=$(DBLATEX_PATH)/share/dblatex/latex//:$(TEXINPUTS)
DBLATEX_SGML_CATALOG_FILES=$(SGML_CATALOG_FILES):/etc/xml/catalog

SOURCES = copasi.xml \
	copasi_GUI.xml \
	copasi_commandLine.xml \
	copasi_fileFormats.xml \
	copasi_methods.xml \
	copasi_errorMessages.xml \
	copasi_bibliography.xml \
	copasi_model.xml

IMAGES = images/Compartments_01.png \
         images/Compartments_02.png \
         images/Compartments_03.png \
         images/Compartments_04.png \
         images/ElementaryModesTask_01.png \
         images/Functions_01.png \
         images/Functions_02.png \
         images/General_01.png \
         images/Layout_01.png \
         images/MCATask_01.png \
         images/MCATask_02.png \
         images/MCATask_03.png \
         images/MassConservationTask_01.png \
         images/MassConservationTask_02.png \
         images/Metabolites_01.png \
         images/Metabolites_02.png \
         images/ParameterEstimation_01.png \
         images/ParameterEstimation_02.png \
         images/ParameterEstimation_05.png \
         images/Platforms_01.png \
         images/PlotWindow_01.png \
         images/Plots_01.png \
         images/Plots_02.png \
         images/Plots_03.png \
         images/Plots_04.png \
         images/Plots_05.png \
         images/Plots_06.png \
         images/Reactions_01.png \
         images/Reactions_02.png \
         images/Reports_01.png \
         images/Reports_02.png \
         images/Reports_03.png \
         images/Reports_04.png \
         images/Reports_05.png \
         images/Sliders_01.png \
         images/Sliders_02.png \
         images/Sliders_03.png \
         images/SteadyStateTask_01.png \
         images/SteadyStateTask_02.png \
         images/TimeCourseTask_01.png \
         images/TimeCourseTask_02.png \
         images/TimeCourseTask_03.png \
         images/Wizard_01.png \
	 figures/caution.eps \
	 figures/caution.pdf \
	 figures/important.eps \
	 figures/important.pdf \
	 figures/note.eps \
	 figures/note.pdf \
	 figures/tip.eps \
	 figures/tip.pdf \
	 figures/warning.eps \
	 figures/warning.pdf

COPASI_DBLATEX=../../admin/documentation/dblatex
COPASI_TEXINPUTS=.:$(COPASI_DBLATEX):$(DBLATEX_TEXINPUTS):$(TEXINPUTS)

.PHONY: clean all

all: copasi.pdf copasi.xhtml 

copasi.tex: $(SOURCES)
	SGML_CATALOG_FILES=$(DBLATEX_SGML_CATALOG_FILES) $(DBLATEX) -p $(COPASI_DBLATEX)/copasi.xsl --style $(COPASI_DBLATEX)/copasi.sty -t tex copasi.xml

copasi.pdf: copasi.tex $(IMAGES)
	TEXINPUTS=$(COPASI_TEXINPUTS) pdflatex $< 
	TEXINPUTS=$(COPASI_TEXINPUTS) pdflatex $<
	TEXINPUTS=$(COPASI_TEXINPUTS) pdflatex $<

copasi.xhtml: $(SOURCES) $(IMAGES) copasi_xhtml.xsl
	[ -d $@ ] || mkdir $@
	[ -d $@/images ] || cp -r images $@/
	(cd $@; \
	xsltproc ../copasi_xhtml.xsl ../copasi.xml; \
	cd ..)

clean:
	-rm -f copasi.tex
	-rm -f copasi.pdf
	-rm -f copasi.html
	-rm -f copasi.out
	-rm -f copasi.idx
	-rm -f copasi.log
	-rm -f copasi.aux
	-rm -f copasi.glo
	-rm -f fotex.log
	-rm -rf copasi.xhtml

