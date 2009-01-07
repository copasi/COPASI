<?xml version="1.0"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns="http://www.w3.org/1999/xhtml" version="1.0">
  <!-- This needs to be adjusted to point to xhtml/chunk.xsl -->
  <!-- <xsl:import href="/usr/share/xml/docbook/stylesheet/nwalsh/xhtml/profile-docbook.xsl"/> -->
  <!-- <xsl:import href="/sw/share/xml/xsl/docbook-xsl/xhtml/profile-docbook.xsl"/> -->
  <!-- <xsl:import href="/usr/share/xml/docbook/xsl-stylesheets-1.72.0/xhtml/chunk.xsl"/> -->
  <xsl:import href="/sw/share/xml/xsl/docbook-xsl/xhtml/chunk.xsl"/>
  
  <!-- ==================================================================== -->
  
  <xsl:template name="header.navigation">
    <xsl:param name="prev" select="/foo"/>
    <xsl:param name="next" select="/foo"/>
    <xsl:param name="nav.context"/>
    
    <xsl:call-template name="copasi.navigation">
      <xsl:with-param name="prev" select="$prev"/>
      <xsl:with-param name="next" select="$next"/>
    </xsl:call-template>
  </xsl:template>
  
  <xsl:template name="footer.navigation">
    <xsl:param name="prev" select="/foo"/>
    <xsl:param name="next" select="/foo"/>
    <xsl:param name="nav.context"/>
    
    <xsl:call-template name="copasi.navigation">
      <xsl:with-param name="prev" select="$prev"/>
      <xsl:with-param name="next" select="$next"/>
    </xsl:call-template>
  </xsl:template>
  
  <xsl:template name="copasi.navigation">
    <xsl:param name="prev" select="/foo"/>
    <xsl:param name="next" select="/foo"/>
    
    <xsl:variable name="up" select="parent::*"/>
    <xsl:variable name="current" select="."/>
    
    <div class="tocnav">
      <table width="100%">
        <tr>
          <td>
            <!-- hierarchy -->
            <xsl:call-template name="copasi.hierarchy"/>
          </td>
        </tr>
        <tr>
          <td>
            <table width="100%">
              <tr>
                <td width="33%">
                  <!-- previous -->
                  <xsl:if test="count($prev)&gt;0">
                    <a class="tocnavlink">
                    <xsl:attribute name="href">
                      <xsl:call-template name="href.target">
                        <xsl:with-param name="object" select="$prev"/>
                      </xsl:call-template>
                    </xsl:attribute>
  					        &lt;&lt;
                    <xsl:apply-templates select="$prev" mode="object.title.markup"/>
  							  </a>
                  </xsl:if>
                </td>
                <td align="center" width="33%">
                  <!-- up -->
                  <xsl:if test="count($up)&gt;0">
                    <a class="tocnavlink">
                      <xsl:attribute name="href">
                        <xsl:call-template name="href.target">
                          <xsl:with-param name="object" select="$up"/>
                        </xsl:call-template>
                      </xsl:attribute>
                      <xsl:apply-templates select="$up" mode="object.title.markup"/>
                    </a>
                  </xsl:if>
                </td>
                <td align="right" width="33%">
                  <!-- next -->
                  <xsl:if test="count($next)&gt;0">
                    <a class="tocnavlink">
                    <xsl:attribute name="href">
                      <xsl:call-template name="href.target">
                        <xsl:with-param name="object" select="$next"/>
                      </xsl:call-template>
                    </xsl:attribute>
                    <xsl:apply-templates select="$next" mode="object.title.markup"/>
  					        &gt;&gt;
  							  </a>
                  </xsl:if>
                </td>
              </tr>
            </table>
          </td>
        </tr>
      </table>
    </div>
  </xsl:template>
  
  <xsl:template name="copasi.hierarchy">
    <xsl:for-each select="ancestor::*">
      <a>
        <xsl:attribute name="href">
          <xsl:call-template name="href.target">
            <xsl:with-param name="object" select="."/>
          </xsl:call-template>
        </xsl:attribute>
        <xsl:apply-templates select="." mode="object.title.markup"/>
      </a>
      -&gt;
    </xsl:for-each>
    
    <a>
      <xsl:attribute name="href">
        <xsl:call-template name="href.target">
          <xsl:with-param name="object" select="."/>
        </xsl:call-template>
      </xsl:attribute>
      <xsl:apply-templates select="." mode="object.title.markup"/>
    </a>
  </xsl:template>

<!-- Fixes for problems in the docbook xsl distribution -->  
  <xsl:template match="equation" mode="label.markup">
    <xsl:variable name="pchap"
                  select="ancestor::chapter
                          |ancestor::appendix
                          |ancestor::article[ancestor::book]"/>
  
    <xsl:variable name="prefix">
      <xsl:if test="count($pchap) &gt; 0">
        <xsl:apply-templates select="$pchap" mode="label.markup"/>
      </xsl:if>
    </xsl:variable>
  
    <xsl:choose>
      <xsl:when test="@label">
        <xsl:value-of select="@label"/>
      </xsl:when>
      <xsl:otherwise>
        <xsl:choose>
          <xsl:when test="count($pchap)>0">
            <xsl:if test="$prefix != ''">
              <xsl:apply-templates select="$pchap" mode="label.markup"/>
              <xsl:apply-templates select="$pchap" mode="intralabel.punctuation"/>
            </xsl:if>
            <xsl:number format="1" from="chapter|appendix" level="any"/>
          </xsl:when>
          <xsl:otherwise>
            <xsl:number format="1" from="book|article" level="any"/>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  
  <xsl:template match="citation">
    <!-- todo: integrate with bibliography collection -->
    <xsl:variable name="targets" select="(//biblioentry | //bibliomixed)[abbrev=string(current())]"/>
    <xsl:variable name="target" select="$targets[1]"/>
  
    <xsl:choose>
      <!-- try automatic linking based on match to abbrev -->
      <xsl:when test="$target and not(xref) and not(link)">
  
        <xsl:text>[</xsl:text>
        <a>
          <xsl:attribute name="href">
            <xsl:call-template name="href.target">
              <xsl:with-param name="object" select="$target"/>
            </xsl:call-template>
          </xsl:attribute>
  
	  	  <xsl:choose>
	  	    <xsl:when test="$bibliography.numbered != 0">
	  	      <xsl:apply-templates select="$target" mode="citation"/>
	  	    </xsl:when>
	  	    <xsl:otherwise>
        	  <xsl:call-template name="inline.charseq"/>
	  	    </xsl:otherwise>
	  	  </xsl:choose>
        </a>
        <xsl:text>]</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>[</xsl:text>
        <xsl:call-template name="inline.charseq"/>
        <xsl:text>]</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <!-- ==================================================================== -->
  
  <xsl:param name="html.ext" select="'.html'"/>
  <!-- <xsl:param name="use.extensions" select="1" /> -->
  <!-- <xsl:param name="tablecolumns.extension" select="1" /> -->
  <!-- <xsl:param name="graphicsize.extension" select="1" /> -->
  <xsl:param name="ignore.image.scaling" select="1"/>
  <xsl:param name="default.image.width" select="500"/>
  <!-- <xsl:param name="nominal.image.width" select="50" /> -->
  <xsl:param name="l10n.gentext.language" select="'en'"/>
  <xsl:param name="citerefentry.link" select="1"/>
  <xsl:param name="section.autolabel" select="1"/>
  <xsl:param name="generate.toc">
    appendix  toc,title
    article/appendix  nop
    article   toc,title
    book      toc,title,figure,table,example
    chapter   toc,title
    part      toc,title
    preface   toc,title
    qandadiv  toc
    qandaset  toc
    reference toc,title
    sect1     toc
    sect2     toc
    sect3     toc
    sect4     toc
    sect5     toc
    section   toc
    set       toc,title
  </xsl:param>
</xsl:stylesheet>

