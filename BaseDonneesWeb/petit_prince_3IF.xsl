<?xml version="1.0" encoding="UTF-8"?>

<!-- New document created with EditiX at Fri Apr 08 15:21:12 CEST 2016 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output method="text"/>
	<xsl:template match="/">
	<html>
		<head>
			<title>
				<xsl:value-of  select ="//titre"/>
				<xsl:text> de </xsl:text>
				<xsl:value-of  select ="//auteur"/>
			</title>
		</head>
		<body style="background-color:white;">
			<xsl:apply-templates/>
			<h3> Fin du texte </h3>
			<hr/>
		</body>
	</html>

	<!--
		Template permettant la mise en forme des titres de notre document. 
	-->
	</xsl:template>
	<xsl:template match="titre">
		<h1 style="text-align:center; color:blue;">
			<xsl:apply-templates/>
		</h1>
	</xsl:template>
	
	<!--
		Template permettant la mise en forme des auteurs de notre document. 
	-->
	<xsl:template match="/texte/entete/infos/auteur">
		<h2 style="text-align:center; color:black; font-style: italic;">
			<br/>
				<xsl:apply-templates/>
			<br/>
		</h2>
	</xsl:template>
	

	<!--
	Template permettant de faire l'entête du documents.
		- Titre
		- Auteurs du documents
		- Informations concernant le TP
	-->
	<xsl:template match="infos">
		<table cellspacing="50" align="center">
			<tbody>
				<tr>
					<td>
						<img src="images/prince.png"/>
					</td>
					<td>
						<blockquote style="color:darkgreen;">
							<!--  Partie Titre-->
							<xsl:apply-templates select="titre"/>
							<!--  Partie Auteur -->
							<xsl:apply-templates select="/texte/entete/infos/auteur"/>
							<!--  Partie Date -->
							<xsl:text> But du Tp du </xsl:text>
							<xsl:apply-templates select="//date"/>
							<xsl:text> : </xsl:text>
							<!--  Partie But -->
							<xsl:apply-templates select="//but"/>
							<br/>
							
							<!--
								Nous cherchons à affiner le résultat en fonction, de plusieurs paramétres:
									- Premierement en fonction du nombre d'étudiant travaillant sur le projet.- Deuxiement en fonction des différents binomes des personnes
									  travaillant sur le projet.
							-->
							<xsl:text>Auteurs : </xsl:text>
							<xsl:for-each select="//mise_en_forme_par/auteur">
								<xsl:apply-templates select="."/>
							</xsl:for-each>
							
							<!--  Partie Mail -->
							<br/> 
							<xsl:text> Email du responsable : </xsl:text>
							<xsl:apply-templates select="//email"/>
						</blockquote>
					</td>
				</tr>
			</tbody>
		</table>
		<hr/>
		<h3> Début du texte </h3>
		</xsl:template>

	<!-- 
		Template à appliquer sur les sources.
		Permettant de ne pas les afficher.
	-->
	<xsl:template match="lien">
	</xsl:template> 

	<!-- 
		Template permettant de définir le mise en forme de la date.
	-->
	<xsl:template match="//date">
		<xsl:apply-templates/>
	</xsl:template> 

	<!-- 
		Template permettant de définir le mise en forme du but.
	-->
	<xsl:template match="//but">
		<xsl:apply-templates/>
	</xsl:template> 

	<!-- 
		Template permettant de définir le mise en forme du mail.
	-->
	<xsl:template match="//email">
		<xsl:apply-templates/>
	</xsl:template> 

	<!-- 
		Template permettant de définir le mise en forme de l'auteur.
	-->
	<xsl:template match="//mise_en_forme_par/auteur">	
		<xsl:apply-templates/>
		<xsl:if test="count(/texte/entete/infos/mise_en_forme_par/auteur [not( preceding::auteur/@NoBinome = @NoBinome )]/@NoBinome) > 1">
			<xsl:apply-templates select="./@NoBinome"/>
		</xsl:if>
		<xsl:text> et </xsl:text>
	</xsl:template> 

	<!-- 
		Template permettant de définir le mise en forme de l'auteur.
		Si l'auteur est en derniere possition nous n'affichons pas le et séparant les auteurs.
	-->
	<xsl:template match="//mise_en_forme_par/auteur[position() = last()]">	
		<xsl:apply-templates/>
		<xsl:apply-templates select="./@NoBinome"/>
	</xsl:template> 

	<!-- 
		Template permettant de définir le mise en forme du numéro de binome.
	-->
	<xsl:template match="//mise_en_forme_par/auteur/@NoBinome">
		<xsl:text> (</xsl:text>		
		<xsl:value-of  select ="."/>
		<xsl:text>) </xsl:text>	
	</xsl:template> 


	<!--
	Template permettant la mise en page des images dans le document
	-->
	<xsl:template match="image">
		<div align="center">
			<img>
				<xsl:attribute name="src">
				<xsl:value-of select="@chemin"/>
				</xsl:attribute>
			</img>
		</div>
	</xsl:template> 
	

	<!--
	Template permettant la mise en page des paragraphes dans dans le document
	-->
	<xsl:template match="paragr">
			<p>
				<xsl:apply-templates select="phrase"/>
			</p>
	</xsl:template> 
	

	<!--
	Template permettant la mise en couleur des phrases hongroises. 
	 -->
	<xsl:template match="phrase[@langue='hu']">
		<span style=" color:brown;font-style: italic;">
			<xsl:apply-templates/>
		</span>
	</xsl:template> 

	<!--
	Template permettant la mise en forme des dialogues. 
		- Les dialogues sont encadrés avec des tableaux. 
		- Les phrases hongroise sont en marrons. 
	-->
	<xsl:template match="paragr[@type='dialogue']">
	<!--
		On creer un tableau qui contient deux tableaux dans lequel on affiche
		les différents dialogues.
	-->
		<table width = "90%" align = "center" >
			<tbody>
				<tr>
					<td width="45%">
						<!-- Table discussion française.  -->
						<table border = "1" width = "100%" cellpadding ="10" >
							<tbody>
								<xsl:for-each select="./phrase[@langue='fr']">
									<tr>
										<td width = "50">
											<img src="images/{@locuteur}.png"/>
										</td>
										<td >
											<xsl:apply-templates select="."/>
										</td>
									</tr>
								</xsl:for-each>
							</tbody>
						</table>
					</td>

					<!-- Ligne vide afin de respecter l'espace.  -->
					<td> </td>

					<!-- Table discussion hongroise.  -->
					<td width="45%">
						<table border = "1" width = "100%" cellpadding ="10" >
							<tbody>
								<xsl:for-each select="./phrase[@langue='hu']">
									<tr>
										<td width = "50">
											<img src="images/{@locuteur}.png"/>
										</td>
										<td>
											<xsl:apply-templates select="."/>
										</td>
									</tr>
								</xsl:for-each>
							</tbody>
						</table>
					</td>
				</tr>
			</tbody>
		</table>
	</xsl:template> 

	<!--
	Template permettant la mise en forme des phrases contenant le mot mouton. 
	 -->
	<xsl:template match="phrase[@langue='fr'][contains(text(),'mouton')]">
		<span style="font-size: 24; font-weight: bold;">
			<xsl:apply-templates/>
			<img src="images/moutonDessin.png"/>
		</span>
	</xsl:template> 
	
	
</xsl:stylesheet>


