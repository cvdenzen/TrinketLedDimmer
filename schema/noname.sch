EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "noname.sch"
Date "15 may 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATTINY85-P IC?
U 1 1 53752E2B
P 5050 3550
F 0 "IC?" H 4000 3950 60  0000 C CNN
F 1 "ATTINY85-P" H 5900 3150 60  0000 C CNN
F 2 "DIP8" H 4000 3150 60  0001 C CNN
F 3 "" H 5050 3550 60  0000 C CNN
	1    5050 3550
	1    0    0    -1  
$EndComp
$Comp
L IRF7309IPBF Q?
U 1 1 53752E93
P 2600 3250
F 0 "Q?" H 2600 3102 40  0000 R CNN
F 1 "IRF7309IPBF" H 2600 3399 40  0000 R CNN
F 2 "SO8" H 2421 3351 29  0000 C CNN
F 3 "~" H 2600 3250 60  0000 C CNN
	1    2600 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3700 2400 3700
Wire Wire Line
	2400 3700 2400 3300
$Comp
L IRF7309IPBF Q?
U 1 1 53752F5C
P 1700 4500
F 0 "Q?" H 1700 4352 40  0000 R CNN
F 1 "IRF7309IPBF" H 1700 4649 40  0000 R CNN
F 2 "SO8" H 1521 4601 29  0000 C CNN
F 3 "~" H 1700 4500 60  0000 C CNN
	1    1700 4500
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53753193
P 2700 3950
F 0 "R?" V 2780 3950 40  0000 C CNN
F 1 "R" V 2707 3951 40  0000 C CNN
F 2 "~" V 2630 3950 30  0000 C CNN
F 3 "~" H 2700 3950 30  0000 C CNN
	1    2700 3950
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW?
U 1 1 5375321D
P 3400 3500
F 0 "SW?" H 3550 3610 50  0000 C CNN
F 1 "SW_PUSH" H 3400 3420 50  0000 C CNN
F 2 "~" H 3400 3500 60  0000 C CNN
F 3 "~" H 3400 3500 60  0000 C CNN
	1    3400 3500
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW?
U 1 1 53753232
P 3400 3300
F 0 "SW?" H 3550 3410 50  0000 C CNN
F 1 "SW_PUSH" H 3400 3220 50  0000 C CNN
F 2 "~" H 3400 3300 60  0000 C CNN
F 3 "~" H 3400 3300 60  0000 C CNN
	1    3400 3300
	1    0    0    -1  
$EndComp
Text Notes 3250 3250 0    60   ~ 0
light2\n
Text Notes 1250 4650 0    60   ~ 0
light2
Wire Wire Line
	3700 3400 1500 3400
Wire Wire Line
	1500 3400 1500 4550
Text Notes 2800 4100 0    60   ~ 0
100k
$Comp
L R R?
U 1 1 53753325
P 1850 3650
F 0 "R?" V 1930 3650 40  0000 C CNN
F 1 "R" V 1857 3651 40  0000 C CNN
F 2 "~" V 1780 3650 30  0000 C CNN
F 3 "~" H 1850 3650 30  0000 C CNN
	1    1850 3650
	1    0    0    -1  
$EndComp
Text Notes 1900 3600 0    60   ~ 0
100k
$EndSCHEMATC
