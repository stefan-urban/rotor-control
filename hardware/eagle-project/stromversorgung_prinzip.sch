<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="6" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="relay">
<description>&lt;b&gt;Relays&lt;/b&gt;&lt;p&gt;
&lt;ul&gt;
&lt;li&gt;Eichhoff
&lt;li&gt;Finder
&lt;li&gt;Fujitsu
&lt;li&gt;HAMLIN
&lt;li&gt;OMRON
&lt;li&gt;Matsushita
&lt;li&gt;NAiS
&lt;li&gt;Siemens
&lt;li&gt;Schrack
&lt;/ul&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="REED">
<description>&lt;b&gt;RELAY&lt;/b&gt;&lt;p&gt;
reed, 1 x norm. open with polarity, grid 5.08</description>
<wire x1="-20.32" y1="5.08" x2="0" y2="5.08" width="0.254" layer="21"/>
<wire x1="0" y1="5.08" x2="0" y2="0" width="0.254" layer="21"/>
<wire x1="0" y1="0" x2="-20.32" y2="0" width="0.254" layer="21"/>
<wire x1="-20.32" y1="0" x2="-20.32" y2="1.27" width="0.254" layer="21"/>
<wire x1="-20.32" y1="1.27" x2="-20.32" y2="3.81" width="0.254" layer="21"/>
<wire x1="-20.32" y1="3.81" x2="-20.32" y2="5.08" width="0.254" layer="21"/>
<wire x1="-20.32" y1="3.81" x2="-19.05" y2="2.54" width="0.254" layer="21"/>
<wire x1="-19.05" y1="2.54" x2="-20.32" y2="1.27" width="0.254" layer="21"/>
<wire x1="-10.795" y1="3.81" x2="-9.525" y2="3.81" width="0.254" layer="21"/>
<wire x1="-9.525" y1="3.81" x2="-9.525" y2="3.175" width="0.254" layer="21"/>
<wire x1="-9.525" y1="3.175" x2="-9.525" y2="2.54" width="0.254" layer="21"/>
<wire x1="-9.525" y1="2.54" x2="-9.525" y2="1.27" width="0.254" layer="21"/>
<wire x1="-9.525" y1="1.27" x2="-10.795" y2="1.27" width="0.254" layer="21"/>
<wire x1="-10.795" y1="1.27" x2="-10.795" y2="1.905" width="0.254" layer="21"/>
<wire x1="-10.795" y1="1.905" x2="-10.795" y2="2.54" width="0.254" layer="21"/>
<wire x1="-10.795" y1="2.54" x2="-10.795" y2="3.81" width="0.254" layer="21"/>
<wire x1="-10.795" y1="1.905" x2="-9.525" y2="3.175" width="0.254" layer="21"/>
<wire x1="-10.795" y1="2.54" x2="-11.43" y2="2.54" width="0.254" layer="21"/>
<wire x1="-9.525" y1="2.54" x2="-8.89" y2="2.54" width="0.254" layer="21"/>
<wire x1="-17.78" y1="3.81" x2="-17.78" y2="4.445" width="0.254" layer="21"/>
<wire x1="-17.78" y1="4.445" x2="-16.51" y2="4.445" width="0.254" layer="21"/>
<wire x1="-14.605" y1="4.445" x2="-2.54" y2="4.445" width="0.254" layer="21"/>
<wire x1="-2.54" y1="4.445" x2="-2.54" y2="3.81" width="0.254" layer="21"/>
<wire x1="-16.51" y1="4.445" x2="-14.605" y2="3.81" width="0.254" layer="21"/>
<circle x="-11.43" y="1.651" radius="0.127" width="0.254" layer="21"/>
<pad name="7" x="-2.54" y="2.54" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="-7.62" y="2.54" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-12.7" y="2.54" drill="0.8128" shape="long" rot="R90"/>
<pad name="1" x="-17.78" y="2.54" drill="0.8128" shape="long" rot="R90"/>
<text x="-19.685" y="0.635" size="0.4064" layer="48">Günther 3570.1331..</text>
<text x="-19.685" y="5.715" size="1.27" layer="25">&gt;NAME</text>
<text x="-12.7" y="5.715" size="1.27" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="K-D-SIL">
<wire x1="-3.81" y1="2.54" x2="1.27" y2="2.54" width="0.254" layer="94"/>
<wire x1="1.27" y1="2.54" x2="3.81" y2="2.54" width="0.254" layer="94"/>
<wire x1="3.81" y1="2.54" x2="3.81" y2="-2.54" width="0.254" layer="94"/>
<wire x1="3.81" y1="-2.54" x2="-1.27" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-1.27" y1="-2.54" x2="-3.81" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-3.81" y1="-2.54" x2="-3.81" y2="2.54" width="0.254" layer="94"/>
<wire x1="-1.27" y1="-2.54" x2="1.27" y2="2.54" width="0.254" layer="94"/>
<wire x1="-3.175" y1="0.635" x2="-2.54" y2="0.635" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0.635" x2="-3.175" y2="-0.635" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0.635" x2="-1.905" y2="-0.635" width="0.254" layer="94"/>
<wire x1="-3.175" y1="-0.635" x2="-2.54" y2="-0.635" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.635" x2="-1.905" y2="-0.635" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="1.27" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.635" x2="-2.54" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-1.905" y1="0.635" x2="-2.54" y2="0.635" width="0.254" layer="94"/>
<text x="5.715" y="0" size="1.778" layer="95">&gt;PART</text>
<text x="5.715" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="3" x="0" y="5.08" visible="pad" length="short" direction="pas" rot="R270"/>
<pin name="5" x="0" y="-5.08" visible="pad" length="short" direction="pas" rot="R90"/>
</symbol>
<symbol name="S-SIL">
<wire x1="0" y1="2.54" x2="0" y2="5.3975" width="0.4064" layer="94"/>
<wire x1="0" y1="-5.3975" x2="0" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="0" y1="-2.54" x2="-2.54" y2="2.54" width="0.4064" layer="94"/>
<circle x="0" y="-2.54" radius="0.3175" width="0.254" layer="94"/>
<text x="3.175" y="1.905" size="1.778" layer="95">&gt;PART</text>
<text x="3.175" y="-0.635" size="1.778" layer="96">&gt;VALUE</text>
<pin name="S" x="0" y="7.62" visible="pad" length="short" direction="pas" rot="R270"/>
<pin name="P" x="0" y="-7.62" visible="pad" length="short" direction="pas" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="35701331" prefix="K">
<description>&lt;b&gt;RELAY&lt;/b&gt;&lt;p&gt;
reed, 1 x norm. open with polarity</description>
<gates>
<gate name="1" symbol="K-D-SIL" x="0" y="0" addlevel="must"/>
<gate name="2" symbol="S-SIL" x="17.78" y="0" addlevel="always"/>
</gates>
<devices>
<device name="" package="REED">
<connects>
<connect gate="1" pin="3" pad="3"/>
<connect gate="1" pin="5" pad="5"/>
<connect gate="2" pin="P" pad="1"/>
<connect gate="2" pin="S" pad="7"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="transistor-fet">
<description>&lt;b&gt;Field Effect Transistors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;&lt;p&gt;
&lt;p&gt;
Symbols changed according to IEC617&lt;p&gt; 
All types, packages and assignment to symbols and pins checked&lt;p&gt;
Package outlines partly checked&lt;p&gt;
&lt;p&gt;
JFET = junction FET&lt;p&gt;
IGBT-x = insulated gate bipolar transistor&lt;p&gt;
x=N: NPN; x=P: PNP&lt;p&gt;
IGFET-mc-nnn; (IGFET=insulated gate field effect transistor)&lt;P&gt;
m=D: depletion mode (Verdr&amp;auml;ngungstyp)&lt;p&gt;
m=E: enhancement mode (Anreicherungstyp)&lt;p&gt;
c: N=N-channel; P=P-Channel&lt;p&gt;
GDSB: gate, drain, source, bulk&lt;p&gt;
&lt;p&gt;
by R. Vogg  15.March.2002</description>
<packages>
<package name="TO220">
<description>&lt;b&gt;TO 220 horizontal&lt;/b&gt;</description>
<wire x1="-5.207" y1="-1.27" x2="5.207" y2="-1.27" width="0.127" layer="21"/>
<wire x1="5.207" y1="14.605" x2="-5.207" y2="14.605" width="0.127" layer="21"/>
<wire x1="5.207" y1="-1.27" x2="5.207" y2="11.176" width="0.127" layer="21"/>
<wire x1="5.207" y1="11.176" x2="4.318" y2="11.176" width="0.127" layer="21"/>
<wire x1="4.318" y1="11.176" x2="4.318" y2="12.7" width="0.127" layer="21"/>
<wire x1="4.318" y1="12.7" x2="5.207" y2="12.7" width="0.127" layer="21"/>
<wire x1="5.207" y1="12.7" x2="5.207" y2="14.605" width="0.127" layer="21"/>
<wire x1="-5.207" y1="-1.27" x2="-5.207" y2="11.176" width="0.127" layer="21"/>
<wire x1="-5.207" y1="11.176" x2="-4.318" y2="11.176" width="0.127" layer="21"/>
<wire x1="-4.318" y1="11.176" x2="-4.318" y2="12.7" width="0.127" layer="21"/>
<wire x1="-4.318" y1="12.7" x2="-5.207" y2="12.7" width="0.127" layer="21"/>
<wire x1="-5.207" y1="12.7" x2="-5.207" y2="14.605" width="0.127" layer="21"/>
<wire x1="-4.572" y1="-0.635" x2="4.572" y2="-0.635" width="0.0508" layer="21"/>
<wire x1="4.572" y1="7.62" x2="4.572" y2="-0.635" width="0.0508" layer="21"/>
<wire x1="4.572" y1="7.62" x2="-4.572" y2="7.62" width="0.0508" layer="21"/>
<wire x1="-4.572" y1="-0.635" x2="-4.572" y2="7.62" width="0.0508" layer="21"/>
<circle x="0" y="11.176" radius="1.8034" width="0.127" layer="21"/>
<circle x="0" y="11.176" radius="4.191" width="0" layer="42"/>
<circle x="0" y="11.176" radius="4.191" width="0" layer="43"/>
<pad name="1" x="-2.54" y="-6.35" drill="1.1176" shape="long" rot="R90"/>
<pad name="2" x="0" y="-6.35" drill="1.1176" shape="long" rot="R90"/>
<pad name="3" x="2.54" y="-6.35" drill="1.1176" shape="long" rot="R90"/>
<text x="-3.81" y="5.207" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.937" y="2.54" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="-4.445" y="7.874" size="0.9906" layer="21" ratio="12">A17,5mm</text>
<text x="-3.175" y="0" size="1.27" layer="51" ratio="10">1</text>
<text x="-0.635" y="0" size="1.27" layer="51" ratio="10">2</text>
<text x="1.905" y="0" size="1.27" layer="51" ratio="10">3</text>
<rectangle x1="2.159" y1="-4.699" x2="2.921" y2="-4.064" layer="21"/>
<rectangle x1="-0.381" y1="-4.699" x2="0.381" y2="-4.064" layer="21"/>
<rectangle x1="-2.921" y1="-4.699" x2="-2.159" y2="-4.064" layer="21"/>
<rectangle x1="-3.175" y1="-4.064" x2="-1.905" y2="-1.27" layer="21"/>
<rectangle x1="-0.635" y1="-4.064" x2="0.635" y2="-1.27" layer="21"/>
<rectangle x1="1.905" y1="-4.064" x2="3.175" y2="-1.27" layer="21"/>
<rectangle x1="-2.921" y1="-6.604" x2="-2.159" y2="-4.699" layer="51"/>
<rectangle x1="-0.381" y1="-6.604" x2="0.381" y2="-4.699" layer="51"/>
<rectangle x1="2.159" y1="-6.604" x2="2.921" y2="-4.699" layer="51"/>
<hole x="0" y="11.176" drill="3.302"/>
</package>
</packages>
<symbols>
<symbol name="IGFET-EN-GDS">
<wire x1="-2.54" y1="-2.54" x2="-1.2192" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="0.762" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="-0.762" width="0.254" layer="94"/>
<wire x1="0" y1="3.683" x2="0" y2="1.397" width="0.254" layer="94"/>
<wire x1="1.905" y1="0.635" x2="0.635" y2="0" width="0.254" layer="94"/>
<wire x1="1.905" y1="-0.635" x2="0.635" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="0.635" y2="0" width="0.1524" layer="94"/>
<wire x1="0.635" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-1.397" x2="0" y2="-3.683" width="0.254" layer="94"/>
<wire x1="-1.143" y1="2.54" x2="-1.143" y2="-2.54" width="0.254" layer="94"/>
<text x="-11.43" y="0" size="1.778" layer="96">&gt;VALUE</text>
<text x="-11.43" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<pin name="D" x="5.08" y="2.54" visible="off" length="middle" direction="pas" rot="R180"/>
<pin name="S" x="5.08" y="-2.54" visible="off" length="middle" direction="pas" rot="R180"/>
<pin name="G" x="-5.08" y="-2.54" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="BUZ21" prefix="Q">
<description>&lt;b&gt;N-Channel Enhancement MOSFET&lt;/b&gt; 100V; 19A; 0,1Ohm</description>
<gates>
<gate name="G$1" symbol="IGFET-EN-GDS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TO220">
<connects>
<connect gate="G$1" pin="D" pad="2"/>
<connect gate="G$1" pin="G" pad="1"/>
<connect gate="G$1" pin="S" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
<symbol name="+5V">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="+5V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+5V" prefix="P+">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="+5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="K1" library="relay" deviceset="35701331" device=""/>
<part name="Q1" library="transistor-fet" deviceset="BUZ21" device=""/>
<part name="GND1" library="supply1" deviceset="GND" device=""/>
<part name="P+1" library="supply1" deviceset="+5V" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<wire x1="55.88" y1="45.72" x2="55.88" y2="104.14" width="0.1524" layer="97" style="longdash"/>
<wire x1="55.88" y1="104.14" x2="127" y2="104.14" width="0.1524" layer="97" style="longdash"/>
<wire x1="127" y1="104.14" x2="127" y2="45.72" width="0.1524" layer="97" style="longdash"/>
<wire x1="127" y1="45.72" x2="55.88" y2="45.72" width="0.1524" layer="97" style="longdash"/>
<wire x1="48.26" y1="33.02" x2="48.26" y2="104.14" width="0.1524" layer="97" style="longdash"/>
<wire x1="-7.62" y1="104.14" x2="48.26" y2="104.14" width="0.1524" layer="97" style="longdash"/>
<wire x1="-7.62" y1="33.02" x2="48.26" y2="33.02" width="0.1524" layer="97" style="longdash"/>
<wire x1="-7.62" y1="33.02" x2="-7.62" y2="104.14" width="0.1524" layer="97" style="longdash"/>
<wire x1="58.42" y1="81.28" x2="106.68" y2="81.28" width="0.1524" layer="97"/>
<wire x1="106.68" y1="81.28" x2="106.68" y2="60.96" width="0.1524" layer="97"/>
<wire x1="106.68" y1="60.96" x2="58.42" y2="60.96" width="0.1524" layer="97"/>
<wire x1="58.42" y1="60.96" x2="58.42" y2="81.28" width="0.1524" layer="97"/>
<text x="-5.08" y="101.6" size="2.54" layer="97" align="top-left">BeagleBone Black
Aufsteckplatine</text>
<text x="58.42" y="101.6" size="2.54" layer="97" align="top-left">Steckdosenleiste</text>
<text x="134.62" y="86.36" size="1.778" layer="97" align="center-left">Anschluss
Yaesu G-2800DXC</text>
<text x="134.62" y="55.88" size="1.778" layer="97" align="center-left">Anschluss
Create ERC5-A</text>
<text x="91.44" y="36.83" size="1.778" layer="97" align="top-center">230V-Versorgungsspannung</text>
</plain>
<instances>
<instance part="K1" gate="1" x="66.04" y="71.12"/>
<instance part="K1" gate="2" x="88.9" y="71.12"/>
<instance part="Q1" gate="G$1" x="33.02" y="50.8"/>
<instance part="GND1" gate="1" x="40.64" y="40.64"/>
<instance part="P+1" gate="1" x="38.1" y="91.44"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="Q1" gate="G$1" pin="S"/>
<wire x1="38.1" y1="48.26" x2="40.64" y2="48.26" width="0.1524" layer="91"/>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="40.64" y1="48.26" x2="40.64" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="Q1" gate="G$1" pin="D"/>
<wire x1="38.1" y1="53.34" x2="66.04" y2="53.34" width="0.1524" layer="91"/>
<pinref part="K1" gate="1" pin="5"/>
<wire x1="66.04" y1="53.34" x2="66.04" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="P+1" gate="1" pin="+5V"/>
<wire x1="38.1" y1="88.9" x2="38.1" y2="83.82" width="0.1524" layer="91"/>
<pinref part="K1" gate="1" pin="3"/>
<wire x1="38.1" y1="83.82" x2="66.04" y2="83.82" width="0.1524" layer="91"/>
<wire x1="66.04" y1="83.82" x2="66.04" y2="76.2" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SCHALTSIGNAL" class="0">
<segment>
<pinref part="Q1" gate="G$1" pin="G"/>
<wire x1="27.94" y1="48.26" x2="-2.54" y2="48.26" width="0.1524" layer="91"/>
<label x="-2.54" y="48.26" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="K1" gate="2" pin="P"/>
<wire x1="88.9" y1="63.5" x2="88.9" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<wire x1="93.98" y1="38.1" x2="93.98" y2="53.34" width="0.1524" layer="91"/>
<wire x1="93.98" y1="53.34" x2="116.84" y2="53.34" width="0.1524" layer="91"/>
<wire x1="116.84" y1="53.34" x2="132.08" y2="53.34" width="0.1524" layer="91"/>
<wire x1="116.84" y1="53.34" x2="116.84" y2="83.82" width="0.1524" layer="91"/>
<junction x="116.84" y="53.34"/>
<wire x1="116.84" y1="83.82" x2="132.08" y2="83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="K1" gate="2" pin="S"/>
<wire x1="88.9" y1="78.74" x2="88.9" y2="88.9" width="0.1524" layer="91"/>
<wire x1="88.9" y1="88.9" x2="111.76" y2="88.9" width="0.1524" layer="91"/>
<wire x1="111.76" y1="88.9" x2="132.08" y2="88.9" width="0.1524" layer="91"/>
<wire x1="111.76" y1="88.9" x2="111.76" y2="58.42" width="0.1524" layer="91"/>
<junction x="111.76" y="88.9"/>
<wire x1="111.76" y1="58.42" x2="132.08" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
