<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:strip-space elements="*" />

<xsl:output 
	method="xml"
	media-type="application/xhtml+xml; charset=iso-8859-1"
	version="1.0"
	encoding="iso-8859-1"
	standalone="no"
	omit-xml-declaration="no"
	doctype-public="-//W3C//DTD XHTML 1.1//EN" 
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"
	indent="no" />

<xsl:template match="link">
	<a href="{./@href}"><xsl:value-of select="." /></a>
</xsl:template>

<xsl:template match="image">
	<xsl:choose>
		<xsl:when test="./@href">
			<xsl:element name="a">
				<xsl:attribute name="class">menu-titre2</xsl:attribute>
				<xsl:attribute name="href"><xsl:value-of select="./@href" /></xsl:attribute>
				<xsl:element name="img">
					<xsl:attribute name="src"><xsl:value-of select="@file" /></xsl:attribute>
					<xsl:attribute name="alt"><xsl:value-of select="@file" /></xsl:attribute>
				</xsl:element>
			</xsl:element>
		</xsl:when>
		<xsl:otherwise>
			<xsl:element name="img">
				<xsl:attribute name="src"><xsl:value-of select="@file" /></xsl:attribute>
				<xsl:attribute name="alt"><xsl:value-of select="@file" /></xsl:attribute>
			</xsl:element>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<xsl:template match="list">
	<xsl:value-of select="./@nom" /><br />
	<xsl:apply-templates select="./element"/>
	<br />
</xsl:template>

<xsl:template match="element">
	<xsl:apply-templates /><br />
</xsl:template>

<xsl:template match="paragraph">
	<div class="paragraph"><xsl:text /><xsl:apply-templates /><xsl:text /></div><br />
</xsl:template>

<xsl:template match="source">
	<xsl:value-of select="./@type"/> : <a href="{./@adresse}"><xsl:value-of select="."/></a><br />
</xsl:template>

</xsl:stylesheet>
