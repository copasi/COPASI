

SOURCES = copasi.xml \
          copasi_GUI.xml \
          copasi_commandLine.xml \
          copasi_fileFormats.xml \
          copasi_methods.xml 

   
IMAGES = Compartments_01.png \
         Compartments_02.png \
         Compartments_03.png \
         Compartments_04.png \
         ElementaryModesTask_01.png \
         Functions_01.png \
         Functions_02.png \
         General_01.png \
         Layout_01.png \
         MCATask_01.png \
         MCATask_02.png \
         MCATask_03.png \
         MassConservationTask_01.png \
         MassConservationTask_02.png \
         Metabolites_01.png \
         Metabolites_02.png \
         Platforms_01.png \
         PlotWindow_01.png \
         Plots_01.png \
         Plots_02.png \
         Plots_03.png \
         Plots_04.png \
         Plots_05.png \
         Plots_06.png \
         Reactions_01.png \
         Reactions_02.png \
         Reports_01.png \
         Reports_02.png \
         Reports_03.png \
         Reports_04.png \
         Reports_05.png \
         Sliders_01.png \
         Sliders_02.png \
         Sliders_03.png \
         SteadyStateTask_01.png \
         SteadyStateTask_02.png \
         TimeCourseTask_01.png \
         TimeCourseTask_02.png \
         TimeCourseTask_03.png \
         Wizard_01.png 

PDF_STYLESHEET=/usr/share/xml/docbook/stylesheet/db2latex/latex/docbook.xsl

HTML_STYLESHEET=/usr/share/xml/docbook/stylesheet/nwalsh/html/profile-docbook.xsl
  
XSLTPROC=/usr/bin/xsltproc

JAVA=/usr/bin/java

PDFLATEX=/usr/bin/pdflatex

.PHONY: clean

copasi.tex: $(SOURCES)
    $(XSLTPROC) --output $@ $(PDF_STYLESHEET) $<

copasi.pdf: copasi.tex $(IMAGES)
    $(PDFLATEX) $@
    
copasi.html: $(SOURCES) $(IMAGES)
    $(XSLTPROC) --output $@ $(HTML_STYLESHEET) $<

clean:
    rm -f copasi.pdf
    rm -f copasi.html
    rm -f copasi.out
    rm -f copasi.idx
    rm -f copasi.log
    rm -f copasi.aux
