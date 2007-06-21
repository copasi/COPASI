<?xml version='1.0' ?>
<xsl:stylesheet  
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!--
<xsl:import href="/usr/share/xml/docbook/stylesheet/nwalsh/xhtml/profile-docbook.xsl"/>
-->
<!--
<xsl:import href="/sw/share/xml/xsl/docbook-xsl/xhtml/profile-docbook.xsl"/>
-->

<xsl:import href="/usr/share/sgml/docbook/xsl-stylesheets-1.69.1-5/xhtml/chunk.xsl"/>

<xsl:param name="html.ext" select="'.xhtml'"/>
<!-- <xsl:param name="use.extensions" select="1" />
<xsl:param name="tablecolumns.extension" select="1" />
<xsl:param name="graphicsize.extension" select="1" /> -->
<xsl:param name="ignore.image.scaling" select="1" />
<xsl:param name="default.image.width" select="50" />
<xsl:param name="nominal.image.width" select="50" />
<xsl:param name="l10n.gentext.language" select="'en'" />
</xsl:stylesheet>

