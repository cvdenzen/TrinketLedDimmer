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
Date "22 may 2014"
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
L R R4
U 1 1 53753193
P 7000 4650
F 0 "R4" V 7080 4650 40  0000 C CNN
F 1 "100k" V 7007 4651 40  0000 C CNN
F 2 "~" V 6930 4650 30  0000 C CNN
F 3 "~" H 7000 4650 30  0000 C CNN
	1    7000 4650
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
	3900 1500 3700 1500
Wire Wire Line
	3900 1800 3750 1800
Wire Wire Line
	3750 1800 3750 4300
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
	8000 5000 8000 4450
Wire Wire Line
	2200 1700 2200 5000
Connection ~ 6700 5000
Connection ~ 2200 2100
Text Notes 8300 3250 0    60   ~ 0
Light1
$Comp
L IRLML0030TRPBF Q?
U 1 1 53774EA5
P 7900 3150
F 0 "Q?" H 7900 3002 40  0000 R CNN
F 1 "IRLML0030TRPBF" H 7900 3299 40  0000 R CNN
F 2 "SOT-23" H 7721 3251 29  0000 C CNN
F 3 "~" H 7900 3150 60  0000 C CNN
	1    7900 3150
	1    0    0    -1  
$EndComp
$Comp
L IRLML0030TRPBF Q?
U 1 1 53774EB4
P 7900 4250
F 0 "Q?" H 7900 4102 40  0000 R CNN
F 1 "IRLML0030TRPBF" H 7900 4399 40  0000 R CNN
F 2 "SOT-23" H 7721 4351 29  0000 C CNN
F 3 "~" H 7900 4250 60  0000 C CNN
	1    7900 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3450 8000 3350
Wire Notes Line
	7100 2200 7400 2200
Wire Notes Line
	7400 2200 7400 2650
Wire Notes Line
	7400 2650 7100 2650
Wire Notes Line
	7100 2650 7100 2200
Wire Notes Line
	7100 2300 7050 2300
Wire Notes Line
	7050 2300 7050 2350
Wire Notes Line
	7050 2350 7100 2350
Wire Notes Line
	7100 2550 7050 2550
Wire Notes Line
	7050 2550 7050 2500
Wire Notes Line
	7050 2500 7100 2500
Wire Notes Line
	7400 2400 7450 2400
Wire Notes Line
	7450 2400 7450 2450
Wire Notes Line
	7450 2450 7400 2450
Text Notes 6950 2300 0    60   ~ 0
1
Text Notes 6950 2550 0    60   ~ 0
2
Text Notes 7500 2400 0    60   ~ 0
3
Text Notes 7000 2100 0    60   ~ 0
SOT-23
Connection ~ 6800 5000
Connection ~ 6700 4400
Connection ~ 6700 4900
Connection ~ 7700 4300
Connection ~ 8000 4450
Connection ~ 6800 3450
Connection ~ 7700 3200
Connection ~ 8000 3350
Connection ~ 6600 2000
Connection ~ 3900 1900
Connection ~ 3900 1800
Connection ~ 3900 1700
Connection ~ 3900 1500
Connection ~ 3300 1700
Connection ~ 3300 2100
Connection ~ 2800 2100
Connection ~ 2800 1700
Connection ~ 2200 1700
$Comp
L R R5
U 1 1 537E6BFB
P 7450 3200
F 0 "R5" V 7530 3200 40  0000 C CNN
F 1 "22k" V 7457 3201 40  0000 C CNN
F 2 "~" V 7380 3200 30  0000 C CNN
F 3 "~" H 7450 3200 30  0000 C CNN
	1    7450 3200
	0    -1   -1   0   
$EndComp
$Comp
L R R6
U 1 1 537E6C0A
P 7450 4300
F 0 "R6" V 7530 4300 40  0000 C CNN
F 1 "22k" V 7457 4301 40  0000 C CNN
F 2 "~" V 7380 4300 30  0000 C CNN
F 3 "~" H 7450 4300 30  0000 C CNN
	1    7450 4300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7200 3200 3700 3200
Connection ~ 3700 3200
Wire Wire Line
	3700 3200 3700 1500
Wire Wire Line
	6700 4400 6700 3200
Connection ~ 6700 3200
Wire Wire Line
	7000 4900 7000 5000
Connection ~ 7000 5000
Wire Wire Line
	7000 4400 7000 4300
Connection ~ 7000 4300
Wire Wire Line
	3750 4300 7200 4300
Connection ~ 7200 4300
Connection ~ 7000 4400
Connection ~ 7000 4900
Connection ~ 7200 3200
$EndSCHEMATC
