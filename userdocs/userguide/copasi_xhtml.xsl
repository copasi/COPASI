<?xml version="1.0"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns="http://www.w3.org/1999/xhtml" version="1.0">
  <!-- This needs to be adjusted to point to xhtml/chunk.xsl -->
  <!-- <xsl:import href="/usr/share/xml/docbook/stylesheet/nwalsh/xhtml/profile-docbook.xsl"/> -->
  <!-- <xsl:import href="/sw/share/xml/xsl/docbook-xsl/xhtml/profile-docbook.xsl"/> -->
  <!-- <xsl:import href="/usr/share/xml/docbook/xsl-stylesheets-1.72.0/xhtml/chunk.xsl"/> -->
  <xsl:import href="/home/usr/src/docbook-xsl-1.73.2/xhtml/chunk.xsl"/>
  
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
</xsl:stylesheet>