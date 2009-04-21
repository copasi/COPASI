<xsl:stylesheet
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:xhtml="http://www.w3.org/1999/xhtml"
  version="1.0">

  <!--
$Id: xh2latex.xsl,v 1.2 2009/04/21 16:22:02 shoops Exp $

cribbed heavily from
XSLT from XHTML+MathML to LATEX
Eitan M. Gurari July 19, 2000
http://www.cse.ohio-state.edu/~gurari/docs/mml-00/xhm2latex.html#x1-20001

see also

Beginner's LaTeX Tutorial
http://www.csclub.uwaterloo.ca/u/sjbmann/tutorial.html
-->

  <xsl:output
    method="text" />

  <xsl:param
    name="Bib"
    select="&quot;bibdata&quot;" />
  <xsl:param
    name="Status"
    select="&quot;prepub&quot;" />

  <xsl:template
    match="xhtml:html">


    <!-- @@ docStyle is lightly tested; undocumented -->
    <xsl:variable
      name="docClass"
      select="xhtml:head/xhtml:link[@rel=&quot;documentclass&quot;]/@title" />
    <xsl:if
      test="$docClass">
      <xsl:text> \documentclass{</xsl:text>
      <xsl:value-of
        select="$docClass" />
      <xsl:text>}&#10;</xsl:text>
    </xsl:if>

    <xsl:variable
      name="docStyle"
      select="xhtml:head/xhtml:link[@rel=&quot;documentstyle&quot;]/@title" />
    <xsl:if
      test="$docStyle">
      <xsl:text> \documentstyle{</xsl:text>
      <xsl:value-of
        select="$docStyle" />
      <xsl:text>}&#10;</xsl:text>
    </xsl:if>

    <xsl:for-each
      select="xhtml:head/xhtml:link[@rel=&quot;usepackage&quot;]">
      <xsl:text>  \usepackage</xsl:text>
      <xsl:value-of
        select="@title" />
      <xsl:text>&#10;</xsl:text>
    </xsl:for-each>

    <!--
  \DeclareGraphicsRule{.gif}{eps}{}{}
  -->

    <xsl:apply-templates
      select="/descendant::xhtml:div[contains(@class, 'latex-preamble')]"
      mode="latex" />

    <xsl:text>
\begin{document}
        </xsl:text>

    <xsl:apply-templates
      select="/descendant::xhtml:div[contains(@class, 'latex-frontmatter')]"
      mode="latex" />

    <xsl:variable
      name="bibStyle"
      select="xhtml:head/xhtml:link[@rel=&quot;bibliographystyle&quot;]/@title" />
    <xsl:if
      test="$bibStyle">
      <xsl:text> \bibliographystyle{</xsl:text>
      <xsl:value-of
        select="$bibStyle" />
      <xsl:text>}&#10;</xsl:text>
    </xsl:if>

    <xsl:apply-templates
      select="xhtml:body" />

    <xsl:text>\end{document}
  </xsl:text>
  </xsl:template>


  <!-- suppress online-only material -->
  <xsl:template
    match="*[contains(@class, 'online')]|*[contains(@class, 'toc')]">
    <!-- noop -->
  </xsl:template>

  <xsl:template
    match="*[contains(@class, 'online')]|*[contains(@class, 'toc')]"
    mode="maketitle">
    <!-- noop -->
  </xsl:template>

  <!-- frontmatter: title page -->
  <xsl:template
    match="xhtml:div[@class='maketitle']">
    <xsl:apply-templates
      mode="maketitle" />
    <!-- what on earth does this \label thing do? -->
    <xsl:text>\maketitle
\label{firstpage}
  </xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:div[@class='date']"
    mode="maketitle"> </xsl:template>

  <xsl:template
    match="xhtml:h1"
    mode="maketitle">
    <xsl:text>\title{</xsl:text>
    <xsl:apply-templates />
    <xsl:text>}&#10;</xsl:text>
  </xsl:template>

  <xsl:template
    match="*[@class='subtitle']"
    mode="maketitle">
    <xsl:text>\subtitle{</xsl:text>
    <xsl:apply-templates />
    <xsl:text>}&#10;</xsl:text>
  </xsl:template>

  <!-- WWW2006 style author markup, ala
 http://www.acm.org/sigs/pubs/proceed/sigfaq.htm#a17 -->
  <xsl:template
    match="xhtml:table[contains(@class, &quot;author&quot;)]"
    mode="maketitle">
    <xsl:text>\numberofauthors{</xsl:text>
    <xsl:value-of
      select="count(xhtml:tr/xhtml:td)" />
    <xsl:text>}&#10;</xsl:text>

    <xsl:text>\author{&#10;</xsl:text>

    <xsl:for-each
      select="xhtml:tr/xhtml:td">
      <xsl:text>\alignauthor </xsl:text>

      <xsl:apply-templates
        mode="maketitle" />

      <xsl:text>&#10;</xsl:text>
    </xsl:for-each>
    <xsl:text>}&#10;</xsl:text>
  </xsl:template>

  <xsl:template
    match="*[@class=&quot;affaddr&quot;]"
    mode="maketitle">
    <xsl:text>\\&#10; \affaddr{</xsl:text>
    <xsl:value-of
      select="normalize-space(.)" />
    <xsl:text>}</xsl:text>
  </xsl:template>

  <xsl:template
    match="*[@class=&quot;email&quot;]"
    mode="maketitle">
    <xsl:text>\email{</xsl:text>
    <xsl:apply-templates />
    <xsl:text>}</xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:br"
    mode="maketitle">
    <xsl:text> \\&#10;</xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:a"
    mode="maketitle">
    <xsl:apply-templates />
  </xsl:template>

  <xsl:template
    match="text()"
    mode="maketitle">
    <xsl:apply-templates />
  </xsl:template>

  <xsl:template
    match="xhtml:address"
    mode="maketitle">
    <xsl:text>\author</xsl:text>

    <!-- should add a test for this -->
    <xsl:if
      test=".//xhtml:a/@title">
      <xsl:text>[</xsl:text>
      <xsl:value-of
        select=".//xhtml:a/@title" />
      <xsl:text>]</xsl:text>
    </xsl:if>
    <xsl:text>{</xsl:text>
    <xsl:for-each
      select="xhtml:a[contains(@rel, &quot;author&quot;)]">
      <xsl:value-of
        select="." />
      <xsl:if
        test="following-sibling::xhtml:a[contains(@rel, &quot;author&quot;)]">
        <xsl:text> \and </xsl:text>
      </xsl:if>
    </xsl:for-each>

    <xsl:for-each
      select="*[contains(@class, &quot;vcard&quot;)]">
      <xsl:apply-templates
        mode="author" />
      <xsl:if
        test="following-sibling::*[contains(@class, &quot;vcard&quot;)]">
        <xsl:text> \and </xsl:text>
      </xsl:if>
    </xsl:for-each>

    <xsl:for-each
      select="*[@class=&quot;thanks&quot;]">
      <xsl:text>\thanks{</xsl:text>
      <xsl:apply-templates />
      <xsl:text>}</xsl:text>
    </xsl:for-each>

    <xsl:text>}
  </xsl:text>

    <xsl:if
      test="xhtml:a[@rel=&quot;institute&quot;]">
      <xsl:text>\institute{</xsl:text>
      <xsl:for-each
        select="xhtml:a[@rel=&quot;institute&quot;]">
        <xsl:value-of
          select="." />
        <xsl:if
          test="following-sibling::xhtml:a[@rel=&quot;institute&quot;]">
          <xsl:text> \and </xsl:text>
        </xsl:if>
      </xsl:for-each>
      <xsl:text>}
    </xsl:text>
    </xsl:if>
  </xsl:template>

  <xsl:template
    match="xhtml:br"
    mode="author">
    <xsl:text>\\&#10;</xsl:text>
  </xsl:template>
  <xsl:template
    match="text()"
    mode="author">
    <xsl:value-of
      select="normalize-space(.)" />
  </xsl:template>


  <!-- abstract -->
  <xsl:template
    match="xhtml:div[@class='abstract']">
    <xsl:text>
    \begin{abstract}
  </xsl:text>
    <xsl:apply-templates />

    <xsl:variable
      name="Address"
      select="normalize-space(//xhtml:address)" />

    <xsl:variable
      name="RCSDate">
      <xsl:value-of
        select="normalize-space(substring-before(substring-after(
     $Address,
     concat(&quot;$&quot;, &quot;Date:&quot;)), &quot;$&quot;))" />
    </xsl:variable>

    <xsl:variable
      name="Revision">
      <xsl:value-of
        select="substring-before(substring-after(
     $Address,
     concat(&quot;$&quot;, &quot;Revision:&quot;)), &quot;$&quot;)" />
    </xsl:variable>

    <xsl:if
      test="$Status=&quot;prepub&quot; and $RCSDate">

      <!-- convert yyyy/mm/dd hh:mm:ss to yyyy-mm-ddThh:mm:ssZ -->
      <xsl:variable
        name="ISODate">
        <xsl:value-of
          select=" concat(translate($RCSDate, &quot;/ &quot;, &quot;-T&quot;), &quot;Z&quot;)" />
      </xsl:variable>

      <xsl:text>\par{\bf PRE-PUBLICATION DRAFT </xsl:text>
      <xsl:value-of
        select="$Revision" />
      <xsl:text> of </xsl:text>
      <xsl:value-of
        select="$ISODate" />
      <xsl:text>. DO NOT CIRCULATE.}</xsl:text>
    </xsl:if>

    <xsl:text>\end{abstract}
  </xsl:text>
  </xsl:template>

  <!-- suppress redundant heading -->
  <xsl:template
    match="xhtml:h4[normalize-space()='Abstract']">
    <!-- noop -->
  </xsl:template>
  <xsl:template
    match="xhtml:h3[normalize-space()='Abstract']">
    <!-- noop -->
  </xsl:template>
  <xsl:template
    match="xhtml:h2[normalize-space()='Abstract']">
    <!-- noop -->
  </xsl:template>

  <xsl:template
    match="xhtml:div[@class=&quot;terms&quot;]">
    <xsl:text>\terms{</xsl:text>
    <xsl:apply-templates />
    <xsl:text>}
  </xsl:text>
  </xsl:template>
  <xsl:template
    match="xhtml:div[@class=&quot;keywords&quot;]">
    <xsl:text>\begin{keywords}</xsl:text>
    <xsl:apply-templates />
    <xsl:text>\end{keywords}
  </xsl:text>
  </xsl:template>

  <!-- body sections -->
  <xsl:template match="xhtml:h1">
    <!-- Do nothing -->
  </xsl:template>
  
  <xsl:template
    match="xhtml:h2">
    <xsl:text>\chapter{</xsl:text>
    <xsl:apply-templates />
    <xsl:text>}
    </xsl:text>
    
    <xsl:call-template
      name="fetch-label">
      <xsl:with-param name="counter">
        <xsl:value-of select="count(./preceding::xhtml:div[contains(@class, 'wikitext')])"/>
      </xsl:with-param>
      <xsl:with-param name="heading" select="./text()"/>
    </xsl:call-template>
  </xsl:template>


  <xsl:template
    match="xhtml:h3">
    <xsl:text>\section{</xsl:text>
    <xsl:apply-templates />
    <xsl:text>}
  </xsl:text>
    <xsl:call-template
      name="fetch-label">
      <xsl:with-param name="counter">
        <xsl:value-of select="count(./preceding::xhtml:div[contains(@class, 'wikitext')])"/>
      </xsl:with-param>
      <xsl:with-param name="heading" select="./text()"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template
    match="xhtml:h4">
    <xsl:text>\subsection{</xsl:text>
    <xsl:apply-templates />
    <xsl:text>}
  </xsl:text>
    <xsl:call-template
      name="fetch-label">
      <xsl:with-param name="counter">
        <xsl:value-of select="count(./preceding::xhtml:div[contains(@class, 'wikitext')])"/>
      </xsl:with-param>
      <xsl:with-param name="heading" select="./text()"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template
    match="xhtml:h5">
    <xsl:text>\subsubsection{</xsl:text>
    <xsl:apply-templates />
    <xsl:text>}
    </xsl:text>
    <xsl:call-template
      name="section-label" />
  </xsl:template>
  
  <!-- section labels. -->
  <xsl:template
    name="section-label">
    <xsl:variable
      name="label"
      select="../@id" />
    <!--xsl:message>
    section-label: <xsl:value-of select="$label"/>
    <xsl:value-of select="position()"/>
    <xsl:value-of select="."/>
  </xsl:message-->

    <xsl:if
      test="$label">
      <xsl:text>\label{</xsl:text>
      <xsl:value-of
        select="$label" />
      <xsl:text>}&#10;</xsl:text>
    </xsl:if>
  </xsl:template>


  <!-- lists -->
  <xsl:template
    match="xhtml:ul">
    <xsl:text>\begin{itemize}
  </xsl:text>
    <xsl:for-each
      select="xhtml:li">
      <xsl:text>\item </xsl:text>
      <xsl:apply-templates />
    </xsl:for-each>
    <xsl:text>
    \end{itemize}
  </xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:ol">
    <xsl:text>\begin{enumerate}
  </xsl:text>
    <xsl:for-each
      select="xhtml:li">
      <xsl:text>\item </xsl:text>
      <xsl:apply-templates />
    </xsl:for-each>
    <xsl:text>
    \end{enumerate}
  </xsl:text>
  </xsl:template>

  <xsl:template match="xhtml:div[@class='caution']">
    <xsl:text>
      \begin{DBKadmonition}{warning}{Caution}
    </xsl:text>
    <xsl:apply-templates />
    <xsl:text>
      \end{DBKadmonition}
    </xsl:text>
  </xsl:template>
  
  <xsl:template match="xhtml:div[@class='errorbox']">
    <xsl:text>
      \begin{DBKadmonition}{\empty}{Message}
    </xsl:text>
    <xsl:apply-templates />
    <xsl:text>
      \end{DBKadmonition}
    </xsl:text>
  </xsl:template>
  
  <xsl:template match="xhtml:div[@class='img']" priority="1">
    <xsl:text>\begin{minipage}[c]{\linewidth}
    \begin{center}\imgexists{</xsl:text>
    <xsl:value-of select="./descendant::xhtml:img/@src" />
    <xsl:text>}{{\centering \imgevalsize{</xsl:text>
    <xsl:value-of select="./descendant::xhtml:img/@src" />
    <xsl:text>}{\includegraphics[scale=0.5]{</xsl:text>
    <xsl:value-of select="./descendant::xhtml:img/@src" />
    <xsl:text>}}}}{</xsl:text>
    <xsl:value-of select="./descendant::xhtml:td[@class='mini']/text()" />
    <xsl:text>}
      
      {\slshape </xsl:text>
    <xsl:value-of select="./descendant::xhtml:td[@class='mini']/text()" />
    <xsl:text>}\end{center}\end{minipage}</xsl:text>
  </xsl:template>
  
  <xsl:template match="xhtml:img[@class='latex-equation']">
    <xsl:value-of select="@alt"/>
    <xsl:text> </xsl:text>
  </xsl:template>
  
  <xsl:template match="xhtml:div[@class='bibliography']">
    <xsl:apply-templates mode="bibliography" />  
  </xsl:template>
  
  <xsl:template match="xhtml:dl" mode='bibliography'>
    <xsl:text>\bibitem[</xsl:text>
    <xsl:value-of select="./xhtml:dt/xhtml:a/@id"/>
    <xsl:text>]{</xsl:text>
    <xsl:value-of select="./xhtml:dt/xhtml:a/@id"/>
    <xsl:text>}\label{</xsl:text>
    <xsl:value-of select="./xhtml:dt/xhtml:a/@id"/>
    <xsl:text>}\hyperlabel{</xsl:text>
    <xsl:value-of select="./xhtml:dt/xhtml:a/@id"/>
    <xsl:text>}</xsl:text>
    <xsl:apply-templates select="./xhtml:dd" />
  </xsl:template>
  
  <xsl:template
    match="xhtml:dl">
    <xsl:text>\begin{description}
    </xsl:text>
    <xsl:for-each
      select="*">
      <xsl:if
        test="local-name() = &quot;dt&quot;">
        <xsl:text>\item[</xsl:text>
      </xsl:if>
      <xsl:apply-templates />
      
      <xsl:if
        test="local-name() = &quot;dt&quot;">
        <xsl:text>] </xsl:text>
      </xsl:if>
    </xsl:for-each>
    <xsl:text>
      \end{description}
    </xsl:text>
  </xsl:template>

  <xsl:template name="table-preamble">
    <xsl:param name="columns" />
    <xsl:text>
      \begingroup%
      \setlength{\newtblsparewidth}{\linewidth</xsl:text>
      <xsl:for-each select="$columns">
        <xsl:text>-2\tabcolsep</xsl:text>
      </xsl:for-each>
      <xsl:text>}%
      \setlength{\newtblstarfactor}{\newtblsparewidth / \real{100}}%
      \begin{tabular}{</xsl:text>
    
    <!-- for each column -->
    <xsl:for-each select="$columns">
      <xsl:text>l</xsl:text>
    </xsl:for-each>
    
    <xsl:text>}\hline</xsl:text>
  </xsl:template>

  <xsl:template name="table-row">
    <xsl:param name="columnWidth" />
    <xsl:param name="previous" />
    <xsl:param name="last" />
    
    <xsl:if test="number($last) > number($previous)" >
      <xsl:variable name="current" select="$previous + 1" />
      <xsl:if test="number($current) > 1">
        <xsl:call-template name="table-row-preamble">
          <xsl:with-param name="previous" select="0" />
          <xsl:with-param name="last" select="count(./descendant::xhtml:tr[number($current)]/xhtml:td)" />
        </xsl:call-template>
      </xsl:if>

      <xsl:variable name="format">
        <xsl:choose>
          <xsl:when test="$current = 1">
            <select>\bfseries\cellcolor[gray]{.9}</select>
          </xsl:when>
          <xsl:when test="$current mod 2 = 0">
            <select></select>
          </xsl:when>
          <xsl:otherwise>
            <select>\cellcolor[gray]{.97}</select>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:variable>
      
      <xsl:call-template name="table-cell">
        <xsl:with-param name="columnWidth" select="$columnWidth" />
        <xsl:with-param name="format" select="$format" />
        <xsl:with-param name="row" select="./descendant::xhtml:tr[number($current)]" />
        <xsl:with-param name="previous" select="0" />
        <xsl:with-param name="last" select="count(./descendant::xhtml:tr[number($current)]/xhtml:td)" />
      </xsl:call-template>
      
      <xsl:text>\tabularnewline
      </xsl:text>
      
      <xsl:call-template name="table-row" >
        <xsl:with-param name="columnWidth" select="$columnWidth" />
        <xsl:with-param name="previous" select="$current" />
        <xsl:with-param name="last" select="$last" />
      </xsl:call-template>
    </xsl:if>
    
  </xsl:template>
  
  <xsl:template name="table-row-preamble">
    <xsl:param name="previous" />
    <xsl:param name="last" />
    
    <xsl:if test="number($last) > number($previous)">
      <xsl:variable name="current" select="number($previous) + 1" />
      <xsl:text>\cline{</xsl:text>
      <xsl:value-of select="$current"/>
      <xsl:text>-</xsl:text>
      <xsl:value-of select="$current"/>
      <xsl:text>}</xsl:text>
      
      <xsl:call-template name="table-row-preamble">
        <xsl:with-param name="previous" select="$current" />
        <xsl:with-param name="last" select="$last" />
      </xsl:call-template>
      
    </xsl:if>
  </xsl:template>

  <xsl:template name="table-cell">
    <xsl:param name="columnWidth" />
    <xsl:param name="format" />
    <xsl:param name="row" />
    <xsl:param name="previous" />
    <xsl:param name="last" />
    
    <xsl:if test="number($last) > number($previous)">
      <xsl:variable name="current" select="number($previous) + 1" />
      
      <xsl:if test="$current != 1">
        <xsl:text>&amp;</xsl:text>
      </xsl:if>
      
      <xsl:text>\multicolumn{1}{</xsl:text>
      
      <xsl:if test="$current = 1">
        <xsl:text>|</xsl:text>
      </xsl:if>

      <xsl:variable name="percent" select="string($columnWidth[$current]/@width)" />
      <xsl:if test="$percent != ''">
        <xsl:text>m{</xsl:text>
        <xsl:value-of select="substring($percent, 1, string-length($percent) - 1)"/>
        <xsl:text>\newtblstarfactor}</xsl:text>
      </xsl:if>

      <xsl:text>|}</xsl:text>

      <xsl:text>{\raggedright</xsl:text>
      <xsl:value-of select="$format"/>
      <xsl:text>%
      </xsl:text>

      <xsl:apply-templates select="$row/xhtml:td[$current]" />

      <xsl:text>%
      }</xsl:text>
      
      <xsl:call-template name="table-cell" >
        <xsl:with-param name="columnWidth" select="$columnWidth" />
        <xsl:with-param name="format" select="$format" />
        <xsl:with-param name="row" select="$row" />
        <xsl:with-param name="previous" select="$current" />
        <xsl:with-param name="last" select="$last" />
      </xsl:call-template>
      
    </xsl:if>
  </xsl:template>

  <xsl:template match="xhtml:table[@class='normal']">
    <xsl:text>\begin{minipage}[c]{\linewidth}
      \begin{center}</xsl:text>
    <xsl:call-template name="table-preamble">
      <xsl:with-param name="columns" select="./descendant::xhtml:td[@class='heading']"></xsl:with-param>
    </xsl:call-template>
    
    <xsl:variable name="columnWidth" select="xhtml:colgroup/xhtml:col" />

    <xsl:call-template name="table-row">
      <xsl:with-param name="columnWidth" select="$columnWidth" />
      <xsl:with-param name="previous" select="0" />
      <xsl:with-param name="last" select="count(./descendant::xhtml:tr)" />
    </xsl:call-template>

    <xsl:text>\hline
    \end{tabular}\endgroup%
    \vspace{4pt}
    
    {\slshape </xsl:text>
    <xsl:apply-templates select="xhtml:caption"/>
    <xsl:text>}\end{center}\end{minipage}</xsl:text>
      
  </xsl:template>

  <!-- tables -->
  <xsl:template
    match="xhtml:table[@border='1']">
    <xsl:text>\begin{center}</xsl:text>
    <xsl:text>\begin{tabular}{|</xsl:text>
    <xsl:for-each
      select="xhtml:tr[1]/*">
      <xsl:text>c|</xsl:text>
    </xsl:for-each>
    <xsl:text>}&#10;</xsl:text>

    <xsl:for-each
      select="xhtml:tr">
      <xsl:text>\hline&#10;</xsl:text>
      <xsl:for-each
        select="*">
        <xsl:if
          test="name() = 'th'">{\bf </xsl:if>
        <xsl:apply-templates />
        <xsl:if
          test="name() = 'th'">}</xsl:if>
        <xsl:if
          test="position() != last()">
          <xsl:text> &amp; </xsl:text>
        </xsl:if>
      </xsl:for-each>
      <xsl:text> \\&#10;</xsl:text>
    </xsl:for-each>
    <xsl:text>\hline&#10;</xsl:text>

    <xsl:text>\end{tabular}&#10;</xsl:text>
    <xsl:text>\end{center}&#10;</xsl:text>
  </xsl:template>

  <!-- ol, img code untested -->
  <xsl:template
    match="xhtml:ol[@class='enumerate1']">
    <xsl:text>\begin{enumerate}</xsl:text>
    <xsl:for-each
      select="xhtml:li">
      <xsl:text>\item </xsl:text>
      <xsl:apply-templates />
    </xsl:for-each>
    <xsl:text>\end{enumerate}</xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:img[@class='graphics'
	      or @class='includegraphics']">
    <xsl:text>\includegraphics[width=</xsl:text>
    <xsl:value-of
      select="@width" />
    <xsl:text>,height=</xsl:text>
    <xsl:value-of
      select="@height" />
    <xsl:text>]{</xsl:text>
    <xsl:value-of
      select="@src" />
    <xsl:text>}</xsl:text>
  </xsl:template>


  <!-- blockquote -->
  <xsl:template
    match="xhtml:blockquote">
    <xsl:text>
    \begin{quote}
  </xsl:text>
    <xsl:apply-templates />
    <xsl:text>
    \end{quote}
  </xsl:text>
  </xsl:template>

  <!-- equasion -->
  <xsl:template
    match="xhtml:p[@class='eqn-display']">
    <xsl:text>
    \begin{equation}
  </xsl:text>
    <xsl:apply-templates
      mode="math" />
    <xsl:text>
    \end{equation}
  </xsl:text>
  </xsl:template>

  <!-- example, definition -->
  <xsl:template
    match="xhtml:pre[@class=&quot;definition&quot;]">
    <xsl:text>\begin{</xsl:text>
    <xsl:value-of
      select="@class" />
    <xsl:text>}</xsl:text>
    <xsl:text>\begin{verbatim}</xsl:text>
    <xsl:text>&#10;</xsl:text>
    <xsl:text>&#10;</xsl:text>
    <xsl:apply-templates
      mode="verbatim" />
    <xsl:text>\end{verbatim}</xsl:text>
    <xsl:text>\end{</xsl:text>
    <xsl:value-of
      select="@class" />
    <xsl:text>}</xsl:text>
    <xsl:text>&#10;</xsl:text>
  </xsl:template>

  <!-- misc pre/verbatim -->
  <xsl:template
    match="xhtml:pre">
    <xsl:text>\begin{verbatim}</xsl:text>
    <xsl:apply-templates
      mode="verbatim" />
    <xsl:text>\end{verbatim}</xsl:text>
  </xsl:template>


  <!-- paragraphs -->

  <xsl:template
    match="xhtml:p">
    <xsl:text>&#10;</xsl:text>
    <xsl:text>\par </xsl:text>
    <xsl:apply-templates />
  </xsl:template>

  <xsl:template
    match="xhtml:p[@class='nopar']">
    <xsl:text>\empty </xsl:text>
    <xsl:apply-templates />
    <xsl:text>\empty </xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:p[@class=&quot;proposition&quot; or @class=&quot;definition&quot;]">
    <xsl:text>\begin{</xsl:text>
    <xsl:value-of
      select="@class" />
    <xsl:text>}</xsl:text>
    <xsl:text>&#10;</xsl:text>
    <xsl:apply-templates />
    <xsl:text>\end{</xsl:text>
    <xsl:value-of
      select="@class" />
    <xsl:text>}</xsl:text>
    <xsl:text>&#10;</xsl:text>
  </xsl:template>


  <!-- footnotes -->
  <xsl:template
    match="*[@class=&quot;footnote&quot;]">
    <xsl:text>\footnote{</xsl:text>
    <xsl:apply-templates />
    <xsl:text>}</xsl:text>
  </xsl:template>

  <!-- phrase markup -->

  <xsl:template
    match="xhtml:em|xhtml:dfn">
    <xsl:text>{\em </xsl:text>
    <xsl:apply-templates />
    <xsl:text>}</xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:code">
    <xsl:text>{\tt </xsl:text>
    <xsl:apply-templates />
    <xsl:text>}</xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:tt">
    <xsl:text>{\tt </xsl:text>
    <xsl:apply-templates />
    <xsl:text>}</xsl:text>
  </xsl:template>

  <xsl:template
    match="*[@class=&quot;url&quot;]">
    <xsl:text>\url{ </xsl:text>
    <xsl:apply-templates />
    <xsl:text>}</xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:i">
    <xsl:text>{\it </xsl:text>
    <xsl:apply-templates />
    <xsl:text>}</xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:b">
    <xsl:text>{\bf </xsl:text>
    <xsl:apply-templates />
    <xsl:text>}</xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:q">
    <xsl:text>``</xsl:text>
    <xsl:apply-templates />
    <xsl:text>''</xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:samp">
    <!-- pass-thru, for \Sigma -->
    <xsl:text>$</xsl:text>
    <xsl:value-of
      select="." />
    <xsl:text>$</xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:samp"
    mode="math">
    <!-- pass-thru, for \Sigma -->
    <xsl:value-of
      select="." />
  </xsl:template>


  <!-- citation links -->
  <xsl:template
    match="xhtml:a[starts-with(., &quot;[&quot;)]">
    <xsl:text>\cite{</xsl:text>
    <xsl:value-of
      select="substring-after(@href,'#')" />
    <xsl:text>}</xsl:text>
  </xsl:template>

  <!-- section/figure references -->
  <xsl:template
    match="xhtml:a[@rel=&quot;ref&quot;]">
    <xsl:text>\ref{</xsl:text>
    <xsl:value-of
      select="substring-after(@href,'#')" />
    <xsl:text>}</xsl:text>
  </xsl:template>

  <!-- wierd phrase markup. @@not tested -->
  <xsl:template
    match="xhtml:span[@class='cmtt-10']">
    <xsl:text>{\tt </xsl:text>
    <xsl:apply-templates />
    <xsl:text>}</xsl:text>
  </xsl:template>
  <xsl:template
    match="xhtml:span[@class='cmti-10']">
    <xsl:text>{\it </xsl:text>
    <xsl:apply-templates />
    <xsl:text>}</xsl:text>
  </xsl:template>


    <!-- 
  per latex tutorial, the following need escaping: # $ % & ~ _ ^ \ { }
  -->

  <xsl:template name="escape-string">
    <xsl:param name="string" />
    <xsl:call-template
      name="esc">
      <xsl:with-param
        name="c"
        select="&quot;#&quot;" />
      <xsl:with-param
        name="s">
        <xsl:call-template
          name="esc">
          <xsl:with-param
            name="c"
            select="&quot;$&quot;" />
          <xsl:with-param
            name="s">
            <xsl:call-template
              name="esc">
              <xsl:with-param
                name="c"
                select="&quot;%&quot;" />
              <xsl:with-param
                name="s">
                <xsl:call-template
                  name="esc">
                  <xsl:with-param
                    name="c"
                    select="&quot;&amp;&quot;" />
                  <xsl:with-param
                    name="s">
                    <xsl:call-template
                      name="esc">
                      <xsl:with-param
                        name="c"
                        select="&quot;~&quot;" />
                      <xsl:with-param
                        name="s">
                        <xsl:call-template
                          name="esc">
                          <xsl:with-param
                            name="c"
                            select="&quot;_&quot;" />
                          <xsl:with-param
                            name="s">
                            <xsl:call-template
                              name="esc">
                              <xsl:with-param
                                name="c"
                                select="&quot;^&quot;" />
                              <xsl:with-param
                                name="s">
                                <xsl:call-template
                                  name="esc">
                                  <xsl:with-param
                                    name="c"
                                    select="&quot;{&quot;" />
                                  <xsl:with-param
                                    name="s">
                                    <xsl:call-template
                                      name="esc">
                                      <xsl:with-param
                                        name="c"
                                        select="&quot;}&quot;" />
                                      <xsl:with-param
                                        name="s">
                                        <xsl:call-template
                                          name="esc">
                                          <xsl:with-param
                                            name="c"
                                            select="&quot;\&quot;" />
                                          <xsl:with-param
                                            name="s"
                                            select="$string" />
                                        </xsl:call-template>
                                      </xsl:with-param>
                                    </xsl:call-template>
                                  </xsl:with-param>
                                </xsl:call-template>
                              </xsl:with-param>
                            </xsl:call-template>
                          </xsl:with-param>
                        </xsl:call-template>
                      </xsl:with-param>
                    </xsl:call-template>
                  </xsl:with-param>
                </xsl:call-template>
              </xsl:with-param>
            </xsl:call-template>
          </xsl:with-param>
        </xsl:call-template>
      </xsl:with-param>
    </xsl:call-template>
  </xsl:template>

  <xsl:template
    name="esc">
    <xsl:param
      name="s" />
    <xsl:param
      name="c" />

    <xsl:choose>
      <xsl:when
        test="contains($s, $c)">
        <xsl:value-of
          select="substring-before($s, $c)" />
        <xsl:text>\</xsl:text>

        <xsl:choose>
          <xsl:when
            test="$c = &quot;\&quot;">
            <xsl:text>textbackslash </xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:value-of
              select="$c" />
          </xsl:otherwise>
        </xsl:choose>

        <xsl:call-template
          name="esc">
          <xsl:with-param
            name="c"
            select="$c" />
          <xsl:with-param
            name="s"
            select="substring-after($s, $c)" />
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of
          select="$s" />
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>


  <!-- bibliography -->
  <xsl:template
    match="xhtml:h2[normalize-space()='References']">
    <!-- noop. suppress redundant heading -->
  </xsl:template>

  <xsl:template
    match="xhtml:dl[@class='bib']">
    <xsl:text>\bibliography{</xsl:text>
    <xsl:value-of
      select="$Bib" />
    <xsl:text>}</xsl:text>

    <!-- the content of this dl is handled by xh2bib.xsl -->
  </xsl:template>
  <xsl:template
    match="xhtml:ul[@class='bibliography']">
    <xsl:text>\bibliography{</xsl:text>
    <xsl:value-of
      select="$Bib" />
    <xsl:text>}</xsl:text>

    <!-- the content of this dl is handled by xh2bib.xsl -->
  </xsl:template>


  <xsl:template
    match="xhtml:div[@class=&quot;figure&quot;]">
    <!-- dunno what [tb] is for, exactly @@-->
    <xsl:text>\begin{figure}[tb]&#10;</xsl:text>

    <xsl:for-each
      select="xhtml:object">
      <xsl:text>\centerline{\epsfig{file=</xsl:text>
      <xsl:value-of
        select="@data" />
      <xsl:text>, height=</xsl:text>
      <xsl:value-of
        select="@height" />
      <xsl:text>}}&#10;</xsl:text>
    </xsl:for-each>

    <xsl:apply-templates />
    <xsl:text>\end{figure}&#10;</xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:p[@class=&quot;caption&quot;]">
    <xsl:text>\caption{</xsl:text>
    <xsl:apply-templates />
    <xsl:text>}</xsl:text>
    <xsl:call-template
      name="section-label" />
  </xsl:template>


  <xsl:template
    match="xhtml:td[@class='figure']">
    <xsl:text>\begin{figure}</xsl:text>
    <xsl:apply-templates />
    <xsl:text>\end{figure}</xsl:text>
  </xsl:template>

  <xsl:template
    match="xhtml:div[@class='caption']">
    <xsl:apply-templates
      select="xhtml:table"
      mode="caption" />
  </xsl:template>

  <xsl:template
    match="xhtml:table"
    mode="caption">
    <xsl:apply-templates
      select="xhtml:tr"
      mode="caption" />
  </xsl:template>

  <xsl:template
    match="xhtml:tr"
    mode="caption">
    <xsl:apply-templates
      select="xhtml:td[2]"
      mode="caption" />
  </xsl:template>

  <xsl:template
    match="xhtml:td"
    mode="caption">
    <xsl:text>\caption{</xsl:text>
    <xsl:apply-templates />
    <xsl:text>}</xsl:text>
  </xsl:template>


  <!-- @@hmm... links? untested -->
  <xsl:template
    match="xhtml:a">
    <xsl:choose>
      <xsl:when test="@href != ''">
        <xsl:text>\href{</xsl:text>
        <xsl:value-of select="@href" />
        <xsl:text>}{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>\label{</xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>}\hyperlabel{</xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>}</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>


  <xsl:template match="xhtml:a[@class='wiki']">
    
    <xsl:choose>
      <xsl:when test="@title='OD.Bibliography'">
        <xsl:variable name="precedingNode" select="./preceding::node()[1]" />
        <xsl:variable name="precedingA" select="(./preceding::xhtml:a[@class='wiki' and @title='OD.Bibliography'][1] | /xhtml:html)[last()]" />
        <xsl:variable name="precedingText" select="./preceding::text()[1]" />

        <xsl:if test="$precedingNode != $precedingA and ($precedingNode != $precedingText or string-length($precedingText) > 1)">
          <xsl:text>\cite{</xsl:text>
        </xsl:if>
        
        <xsl:variable name="url" select="./@href" />
        <xsl:variable name="label" select="substring-after($url, '#')"/>
        <xsl:value-of select="$label" />
        
        <xsl:variable name="followingNode" select="./following::node()[1]" />
        <xsl:variable name="followingA" select="(./following::xhtml:a[@class='wiki' and @title='OD.Bibliography'][1] | /xhtml:html)[last()]" />
        <xsl:variable name="followingText" select="./following::text()[1]" />
        
        <xsl:if test="$followingNode != $followingA and ($followingNode != $followingText or string-length($followingText) > 1)">
          <xsl:text>}</xsl:text>
        </xsl:if>
      </xsl:when>
      <xsl:when test="starts-with(./@title, 'OD.')">
        <xsl:variable name="url" select="./@href" />
        <xsl:variable name="label" select="substring-after($url, 'tiki-index.php?page=')"/>
        <xsl:text>\hyperlink{</xsl:text>
        <xsl:value-of select="$label" />
        <xsl:text>}{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>\href{</xsl:text>
        <xsl:value-of select="@href" />
        <xsl:text>}{</xsl:text>
        <xsl:apply-templates />
        <xsl:text>}</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
 
  
  <xsl:template
    mode="ref"
    match="comment()[starts-with(.,'tex4ht:ref:')]">
    <xsl:value-of
      select="substring-after(.,'tex4ht:ref:')" />
  </xsl:template>

  <xsl:template
    match="comment()[starts-with(.,'tex4ht:label?:')]">
    <xsl:text>\label{\empty </xsl:text>
    <xsl:value-of
      select="substring-after(.,'tex4ht:label?:')" />
    <xsl:text>}</xsl:text>
  </xsl:template>

  <xsl:template
    match="text()"
    mode="latex">
    <xsl:value-of
      select="." />
  </xsl:template>

  <xsl:template
    match="xhtml:div[contains(@class, 'latex-')]">
    <!-- Do Nothing -->
  </xsl:template>
  
  <xsl:template
    match="xhtml:div[@class = 'latex']">
    <xsl:apply-templates mode="latex" />
  </xsl:template>
  
  <xsl:template match="xhtml:div[@align='center']">
    <xsl:text>\begin{center}</xsl:text>
    <xsl:apply-templates/>
    <xsl:text>\end{center}</xsl:text>
  </xsl:template>
  
  <xsl:template
    match="text()[contains(., 'Table of contents:')]">
    <!-- Do Nothing -->
  </xsl:template>

  <!-- text -->
  <xsl:template
    match="text()">
    <xsl:variable name="before" select="starts-with(., ']')" />
    <xsl:variable name="after" select="contains(substring(., string-length(.) - 1), '[')" />
    
    <xsl:choose>
      <!-- ]...[ -->
      <xsl:when test="boolean($before) and boolean($after)">
        <xsl:choose>
          <!-- <a>]...[ -->
          <xsl:when test="./preceding-sibling::node() = ./preceding-sibling::xhtml:a[@class='wiki']">
            <xsl:choose>
              <!-- <a>]...[<a> -->
              <xsl:when test="./following-sibling::node() = ./following-sibling::xhtml:a[@class='wiki']">
                <xsl:call-template name="escape-string">
                  <xsl:with-param name="string" select="substring(., 2, string-length(.) - 2)" />
                </xsl:call-template>  
              </xsl:when>
              <!-- <a>]...[ -->
              <xsl:otherwise>
                <xsl:call-template name="escape-string">
                  <xsl:with-param name="string" select="substring(., 2)" />
                </xsl:call-template>  
              </xsl:otherwise>
            </xsl:choose>
          </xsl:when>
          <!-- ]...[<a> -->
          <xsl:when test="./following-sibling::node() = ./following-sibling::xhtml:a[@class='wiki']">
            <xsl:call-template name="escape-string">
              <xsl:with-param name="string" select="substring(., 1, string-length(.) - 1)" />
            </xsl:call-template>  
          </xsl:when>
          <!-- ]...[ -->
          <xsl:otherwise>
            <xsl:call-template name="escape-string">
              <xsl:with-param name="string" select="." />
            </xsl:call-template>  
          </xsl:otherwise>
        </xsl:choose>
      </xsl:when>
      <!-- ]... -->
      <xsl:when test="boolean($before)">
        <xsl:choose>
          <!-- <a>]... -->
          <xsl:when test="./preceding-sibling::node() = ./preceding-sibling::xhtml:a[@class='wiki']">
            <xsl:call-template name="escape-string">
              <xsl:with-param name="string" select="substring(., 2)" />
            </xsl:call-template>  
          </xsl:when>
          <!-- ]... -->
          <xsl:otherwise>
            <xsl:call-template name="escape-string">
              <xsl:with-param name="string" select="." />
            </xsl:call-template>  
          </xsl:otherwise>
        </xsl:choose>
      </xsl:when>
      <!-- ...[ -->
      <xsl:when test="boolean($after)">
        <xsl:choose>
          <!-- ...[<a> -->
          <xsl:when test="./following-sibling::node() = ./following-sibling::xhtml:a[@class='wiki']">
            <xsl:call-template name="escape-string">
              <xsl:with-param name="string" select="substring(., 1, string-length(.) - 1)" />
            </xsl:call-template>  
          </xsl:when>
          <!-- ...[ -->
          <xsl:otherwise>
            <xsl:call-template name="escape-string">
              <xsl:with-param name="string" select="." />
            </xsl:call-template>  
          </xsl:otherwise>
        </xsl:choose>
      </xsl:when>
      <!-- ... -->
      <xsl:otherwise>
        <xsl:call-template name="escape-string">
          <xsl:with-param name="string" select="." />
        </xsl:call-template>  
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  
  
  <xsl:template
    name="fetch-label">
    <xsl:param name="counter" />
    <xsl:param name="heading" />
    
    <xsl:variable name="title" select="/descendant::xhtml:h1/following-sibling::xhtml:ul/descendant::xhtml:a[number($counter)]/text()" />
    <xsl:variable name="url" select="/descendant::xhtml:h1/following-sibling::xhtml:ul/descendant::xhtml:a[number($counter)]/@href" />
    <xsl:variable name="label" select="substring-after(substring-before($url, '&amp;structure='), 'tiki-index.php?page=')"/>
      
    <xsl:if
      test="$label and normalize-space($heading) = normalize-space($title)">
      <xsl:text>\label{</xsl:text>
      <xsl:value-of
        select="$label" />
      <xsl:text>}\hyperlabel{</xsl:text>
      <xsl:value-of select="$label" />
      <xsl:text>}&#10;</xsl:text>
    </xsl:if>
     
    <xsl:text></xsl:text>
  </xsl:template>

  <xsl:template match="xhtml:script">
    <!-- ignored -->
  </xsl:template>
  
  <xsl:template match="xhtml:noscript">
    <!-- ignored -->
  </xsl:template>
  
</xsl:stylesheet>
