<?xml version="1.0" encoding="UTF-8"?>

<!-- New document created with EditiX at Fri Apr 08 15:21:12 CEST 2016 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="html"/>
    <!--
        Template permettant la mise en forme des titres de notre document. 
    -->
 
    <xsl:template match="/">
        <xsl:apply-templates select="."/>   
    </xsl:template>

    <xsl:template match="envent">   
    </xsl:template>

    <xsl:template match="event[title = 'Workaholics']">
        <ul>
            <li><xsl:apply-templates select="title"/></li> 
            <li><xsl:apply-templates select="dtstart"/></li> 
            <li><xsl:apply-templates select="summary"/></li>
            <li><xsl:apply-templates select="url"/></li>
            <li><xsl:apply-templates select="description"/></li>
        </ul>
    </xsl:template>

    <xsl:template match="title">
        <xsl:text> titre :</xsl:text>
        <xsl:apply-templates/>
    </xsl:template>

    <!--
        Template permettant la mise en forme des résumés. 
    -->
    <xsl:template match="summary">
        <xsl:text> résumé :</xsl:text>
        <xsl:apply-templates/>
    </xsl:template>

    <!--
        Template permettant la mise en forme des urls. 
    -->

    <xsl:template match="url">
        <xsl:text> url :</xsl:text>
        <xsl:apply-templates/>
    </xsl:template>

     <!--
        Template permettant la mise en forme des descition. 
    -->
    <xsl:template match="description">
        <xsl:text> description :</xsl:text>
        <xsl:apply-templates/>
    </xsl:template>

    <!--
        Template permettant la mise en forme des descition. 
        Contenu à modifier. 
    -->
    <xsl:template match="dtstart">
        <xsl:text> début le : </xsl:text>
        <xsl:value-of select="substring('onsdqcoinezxzedqsc',4,6)"/>
        <xsl:value-of select="substring('onsdqcoizednzedqsc',4,6)"/>
        <xsl:value-of select="substring('onsdqcoinxzzedqsc',4,6)"/>
      <xsl:value-of select="substring('onsdqcoinzexzdqsc',4,6)"/>
        <xsl:text> de </xsl:text>
        <xsl:value-of select="substring('onsdqcoixnzedqsc',4,6)"/>
    </xsl:template>



</xsl:stylesheet>


