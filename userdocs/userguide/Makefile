

SOURCES = copasi.xml \
          copasi_GUI.xml \
          copasi_commandLine.xml \
          copasi_fileFormats.xml \
          copasi_methods.xml 

   
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

# I would prefer to use the xhtml stylesheet because the MathML are not allowed in normal HTML.
# Most browsers seem to render it anyway.
# The XHTML output does not make a whitespace after tags which looks very ugly. Maybe this will be fixed in later
# versions of the XHTML stylesheet (or we can fix it if we know enough about docbook.)
HTML_STYLESHEET=/usr/share/xml/docbook/stylesheet/nwalsh/html/profile-docbook.xsl

XHTML_STYLESHEET=copasi_xhtml.xsl

PDF_STYLESHEET=/usr/share/xml/docbook/stylesheet/db2latex/latex/docbook.xsl

JAVA=/usr/lib/j2sdk1.5-sun/bin/java

SAXON_JAR=/usr/share/java/saxon-6.5.3.jar

SAXON_EXTENSIONS_JAR=/usr/share/java/docbook-xsl-saxon651.jar

XSLTPROC=$(JAVA) -classpath $(SAXON_JAR):$(SAXON_EXTENSIONS_JAR) com.icl.saxon.StyleSheet  


PDFLATEX=/usr/bin/pdflatex

.PHONY: clean

copasi.tex: $(SOURCES)
	$(XSLTPROC) -o $@ $< $(PDF_STYLESHEET) 

copasi.pdf: copasi.tex $(IMAGES)
	$(PDFLATEX) $<
	$(PDFLATEX) $<
	$(PDFLATEX) $<
    
copasi.html: $(SOURCES) $(IMAGES)
	$(XSLTPROC) -o $@ $< $(HTML_STYLESHEET) 

copasi.xhtml: $(SOURCES) $(IMAGES)
	$(XSLTPROC) -o $@ $< $(XHTML_STYLESHEET) 


clean:
	rm -f copasi.pdf
	rm -f copasi.html
	rm -f copasi.out
	rm -f copasi.idx
	rm -f copasi.log
	rm -f copasi.aux
	rm -f copasi.glo
