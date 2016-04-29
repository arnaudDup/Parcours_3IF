<?xml version="1.0" encoding="UTF-8"?>

<!-- New document created with EditiX at Fri Apr 08 15:21:12 CEST 2016 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="html"/>

    <!--
        Template permettant la mise en forme des titres de notre document. 
    -->
    <xsl:template match="/">
	<xsl:for-each select="//event">
	<xsl:sort select ="title"/>
        <ul id = "listeInformations" class="media-list">	
            <li>
                <div id = "informations" class="media-body">
                    <h4 class="media-heading title"> <xsl:apply-templates select="title"/> </h4>
                    <div> <xsl:apply-templates select="dtstart" /> </div>
                    <!-- voir comment on peut mettre href avec l'URL -->
                    <div>
                       <a><xsl:apply-templates select="summary"/></a>
                    </div>
                    <div> <xsl:apply-templates select="url"/> </div>
                    <div> <xsl:apply-templates select="description"/> </div>
                </div>
            </li>
        </ul>
	</xsl:for-each>
    </xsl:template>


    <xsl:template match="title">
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
        <xsl:apply-templates/>
    </xsl:template>

     <!--
        Template permettant la mise en forme des descition. 
    -->
    <xsl:template match="description">
        <xsl:apply-templates/>
    </xsl:template>

    <!--
        Template permettant la mise en forme des descition. 
        Contenu à modifier. 
    -->
    <xsl:template match="dtstart">
        <xsl:text> début le : </xsl:text>
          <!-- Nous récupérons le contenu des deux chaine que nous voulons traiter -->
        <xsl:variable name="begin" select='.' />
        <xsl:variable name="end" select='../dtend'/>

        <xsl:value-of select="substring($begin,7,2)"/>
        <xsl:text> - </xsl:text>
        <xsl:value-of select="substring($begin,5,2)"/>
        <xsl:text> - </xsl:text>
        <xsl:value-of select="substring($begin,0,5)"/>
        <xsl:text> de </xsl:text>
        <xsl:value-of select="substring($begin,10,2)"/>
        <xsl:text>h</xsl:text>
        <xsl:value-of select="substring($begin,12,2)"/>
         <xsl:text> à </xsl:text>
        <xsl:value-of select="substring($end,10,2)"/>
        <xsl:text>h</xsl:text>
        <xsl:value-of select="substring($end,10,2)"/>

    </xsl:template>



</xsl:stylesheet>


