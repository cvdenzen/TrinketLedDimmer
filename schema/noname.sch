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
LIBS:noname-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "noname.sch"
Date "17 may 2014"
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
P 5250 1750
F 0 "IC?" H 4200 2150 60  0000 C CNN
F 1 "ATTINY85-P" H 6100 1350 60  0000 C CNN
F 2 "DIP8" H 4200 1350 60  0001 C CNN
F 3 "" H 5250 1750 60  0000 C CNN
	1    5250 1750
	1    0    0    -1  
$EndComp
$Comp
L IRF7309IPBF Q?
U 1 1 53752E93
P 7900 3250
F 0 "Q?" H 7900 3102 40  0000 R CNN
F 1 "IRLML0030TRPbF" H 7900 3399 40  0000 R CNN
F 2 "SO8" H 7721 3351 29  0000 C CNN
F 3 "~" H 7900 3250 60  0000 C CNN
	1    7900 3250
	1    0    0    -1  
$EndComp
$Comp
L IRF7309IPBF Q?
U 1 1 53752F5C
P 7900 4250
F 0 "Q?" H 7900 4102 40  0000 R CNN
F 1 "IRLML0030TRPbF" H 7900 4399 40  0000 R CNN
F 2 "SO8" H 7721 4351 29  0000 C CNN
F 3 "~" H 7900 4250 60  0000 C CNN
	1    7900 4250
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 53753193
P 7500 4650
F 0 "R4" V 7580 4650 40  0000 C CNN
F 1 "100k" V 7507 4651 40  0000 C CNN
F 2 "~" V 7430 4650 30  0000 C CNN
F 3 "~" H 7500 4650 30  0000 C CNN
	1    7500 4650
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 5375321D
P 2500 1700
F 0 "SW1" H 2650 1810 50  0000 C CNN
F 1 "SW_PUSH" H 2500 1620 50  0000 C CNN
F 2 "~" H 2500 1700 60  0000 C CNN
F 3 "~" H 2500 1700 60  0000 C CNN
	1    2500 1700
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 53753232
P 2500 2100
F 0 "SW2" H 2650 2210 50  0000 C CNN
F 1 "SW_PUSH" H 2500 2020 50  0000 C CNN
F 2 "~" H 2500 2100 60  0000 C CNN
F 3 "~" H 2500 2100 60  0000 C CNN
	1    2500 2100
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 53753325
P 6700 4650
F 0 "R3" V 6780 4650 40  0000 C CNN
F 1 "100k" V 6707 4651 40  0000 C CNN
F 2 "~" V 6630 4650 30  0000 C CNN
F 3 "~" H 6700 4650 30  0000 C CNN
	1    6700 4650
	1    0    0    -1  
$EndComp
Text Notes 6750 5950 0    60   ~ 0
Dimmer pin layout change:\nDate 20140517\nFunction   Pin           Comments\nButton1    PB2\nButton2    PB4           With 1k resistor in series to avoid short circuit at boot time\nLight1     PB0=OC1A(inv) Inverted, software must handle this\nLight2     PB3=OC1B(inv) Inverted, software must handle this
Text Notes 8400 4300 0    60   ~ 0
light2\n
Text Notes 2450 1450 0    60   ~ 0
light1\n
$Comp
L R R1
U 1 1 53772E95
P 3050 1700
F 0 "R1" V 3130 1700 40  0000 C CNN
F 1 "1k" V 3057 1701 40  0000 C CNN
F 2 "~" V 2980 1700 30  0000 C CNN
F 3 "~" H 3050 1700 30  0000 C CNN
	1    3050 1700
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 53772EA2
P 3050 2100
F 0 "R2" V 3130 2100 40  0000 C CNN
F 1 "1k" V 3057 2101 40  0000 C CNN
F 2 "~" V 2980 2100 30  0000 C CNN
F 3 "~" H 3050 2100 30  0000 C CNN
	1    3050 2100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3300 1700 3900 1700
Wire Wire Line
	3300 2100 3300 1900
Wire Wire Line
	3300 1900 3900 1900
Wire Wire Line
	7700 3200 7700 3300
Wire Wire Line
	3900 1500 3700 1500
Wire Wire Line
	3700 1500 3700 3300
Wire Wire Line
	3700 3300 7700 3300
Wire Wire Line
	3900 1800 3750 1800
Wire Wire Line
	3750 1800 3750 4300
Wire Wire Line
	3750 4300 7700 4300
Wire Wire Line
	6700 4400 6700 3300
Connection ~ 6700 3300
Wire Wire Line
	7500 4400 7500 4300
Connection ~ 7500 4300
Wire Wire Line
	8000 3450 6800 3450
Wire Wire Line
	6800 2000 6800 5000
Wire Wire Line
	6800 2000 6600 2000
Wire Wire Line
	6700 4900 6700 5000
Wire Wire Line
	2200 5000 8000 5000
Wire Wire Line
	7500 5000 7500 4900
Wire Wire Line
	8000 5000 8000 4450
Connection ~ 7500 5000
Wire Wire Line
	2200 1700 2200 5000
Connection ~ 6700 5000
Connection ~ 2200 2100
Text Notes 8300 3250 0    60   ~ 0
Light1
$EndSCHEMATC
