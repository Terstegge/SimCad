EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L pspice:OPAMP U1
U 1 1 603773B5
P 5575 1850
F 0 "U1" H 5675 2000 50  0000 L CNN
F 1 "OPAMP" H 5575 2100 50  0000 L CNN
F 2 "" H 5575 1850 50  0001 C CNN
F 3 "~" H 5575 1850 50  0001 C CNN
	1    5575 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5275 1950 5100 1950
Wire Wire Line
	5100 1950 5100 2450
Wire Wire Line
	5100 2450 6000 2450
Wire Wire Line
	6000 2450 6000 1850
Wire Wire Line
	6000 1850 5875 1850
Connection ~ 6000 1850
Text Label 4175 1750 0    50   ~ 0
Voltage_Follower_IN
Text Label 7025 1850 2    50   ~ 0
Voltage_Follower_OUT
Wire Wire Line
	6000 1850 7025 1850
Wire Wire Line
	4175 1750 5275 1750
$Comp
L power:-5V #PWR03
U 1 1 627381AD
P 5475 2150
F 0 "#PWR03" H 5475 2250 50  0001 C CNN
F 1 "-5V" H 5490 2323 50  0000 C CNN
F 2 "" H 5475 2150 50  0001 C CNN
F 3 "" H 5475 2150 50  0001 C CNN
	1    5475 2150
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 62738536
P 5475 1550
F 0 "#PWR02" H 5475 1400 50  0001 C CNN
F 1 "+5V" H 5490 1723 50  0000 C CNN
F 2 "" H 5475 1550 50  0001 C CNN
F 3 "" H 5475 1550 50  0001 C CNN
	1    5475 1550
	1    0    0    -1  
$EndComp
$Comp
L pspice:OPAMP U2
U 1 1 6273C68E
P 5575 3475
F 0 "U2" H 5675 3625 50  0000 L CNN
F 1 "OPAMP" H 5575 3725 50  0000 L CNN
F 2 "" H 5575 3475 50  0001 C CNN
F 3 "~" H 5575 3475 50  0001 C CNN
	1    5575 3475
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 6273CFC1
P 6000 3775
F 0 "R3" H 6075 3775 50  0000 L CNN
F 1 "1k" V 6000 3725 50  0000 L CNN
F 2 "" V 5930 3775 50  0001 C CNN
F 3 "~" H 6000 3775 50  0001 C CNN
	1    6000 3775
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 6273D3DD
P 6000 4275
F 0 "R4" H 6075 4275 50  0000 L CNN
F 1 "1k" V 6000 4225 50  0000 L CNN
F 2 "" V 5930 4275 50  0001 C CNN
F 3 "~" H 6000 4275 50  0001 C CNN
	1    6000 4275
	1    0    0    -1  
$EndComp
Text Label 4175 3375 0    50   ~ 0
Non_Inv_Ampl_IN
Text Label 7025 3475 2    50   ~ 0
Non_Inv_Ampl_OUT
$Comp
L power:+5V #PWR04
U 1 1 6274204B
P 5475 3175
F 0 "#PWR04" H 5475 3025 50  0001 C CNN
F 1 "+5V" H 5490 3348 50  0000 C CNN
F 2 "" H 5475 3175 50  0001 C CNN
F 3 "" H 5475 3175 50  0001 C CNN
	1    5475 3175
	1    0    0    -1  
$EndComp
$Comp
L power:-5V #PWR05
U 1 1 6274251B
P 5475 3775
F 0 "#PWR05" H 5475 3875 50  0001 C CNN
F 1 "-5V" H 5490 3948 50  0000 C CNN
F 2 "" H 5475 3775 50  0001 C CNN
F 3 "" H 5475 3775 50  0001 C CNN
	1    5475 3775
	-1   0    0    1   
$EndComp
Wire Wire Line
	5875 3475 6000 3475
Wire Wire Line
	6000 3475 6000 3625
Connection ~ 6000 3475
Wire Wire Line
	6000 3475 7025 3475
Wire Wire Line
	6000 4125 6000 4025
Wire Wire Line
	6000 4025 5100 4025
Wire Wire Line
	5100 4025 5100 3575
Wire Wire Line
	5100 3575 5275 3575
Connection ~ 6000 4025
Wire Wire Line
	6000 4025 6000 3925
Wire Wire Line
	4175 3375 5275 3375
$Comp
L pspice:OPAMP U3
U 1 1 627544A5
P 5575 5700
F 0 "U3" H 5675 5850 50  0000 L CNN
F 1 "OPAMP" H 5575 5950 50  0000 L CNN
F 2 "" H 5575 5700 50  0001 C CNN
F 3 "~" H 5575 5700 50  0001 C CNN
	1    5575 5700
	1    0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 627544AB
P 4850 5600
F 0 "R1" V 4750 5575 50  0000 L CNN
F 1 "1k" V 4850 5550 50  0000 L CNN
F 2 "" V 4780 5600 50  0001 C CNN
F 3 "~" H 4850 5600 50  0001 C CNN
	1    4850 5600
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 627544B1
P 5600 5075
F 0 "R2" V 5500 5025 50  0000 L CNN
F 1 "2k" V 5600 5025 50  0000 L CNN
F 2 "" V 5530 5075 50  0001 C CNN
F 3 "~" H 5600 5075 50  0001 C CNN
	1    5600 5075
	0    1    1    0   
$EndComp
Text Label 4175 5600 0    50   ~ 0
Inv_Ampl_IN
Text Label 7025 5700 2    50   ~ 0
Inv_Ampl_OUT
$Comp
L power:+5V #PWR07
U 1 1 627544B9
P 5475 6000
F 0 "#PWR07" H 5475 5850 50  0001 C CNN
F 1 "+5V" H 5490 6173 50  0000 C CNN
F 2 "" H 5475 6000 50  0001 C CNN
F 3 "" H 5475 6000 50  0001 C CNN
	1    5475 6000
	-1   0    0    1   
$EndComp
$Comp
L power:-5V #PWR06
U 1 1 627544BF
P 5475 5400
F 0 "#PWR06" H 5475 5500 50  0001 C CNN
F 1 "-5V" H 5490 5573 50  0000 C CNN
F 2 "" H 5475 5400 50  0001 C CNN
F 3 "" H 5475 5400 50  0001 C CNN
	1    5475 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5875 5700 6000 5700
Connection ~ 6000 5700
Wire Wire Line
	6000 5700 7025 5700
Wire Wire Line
	5100 5800 5275 5800
Wire Wire Line
	5100 6000 5100 5800
Wire Wire Line
	6000 5700 6000 5075
Wire Wire Line
	6000 5075 5750 5075
Wire Wire Line
	5450 5075 5100 5075
Wire Wire Line
	5100 5075 5100 5600
Wire Wire Line
	5100 5600 5275 5600
Wire Wire Line
	4175 5600 4700 5600
Wire Wire Line
	5000 5600 5100 5600
Connection ~ 5100 5600
$Comp
L power:GND #PWR0101
U 1 1 6277681D
P 6000 4425
F 0 "#PWR0101" H 6000 4175 50  0001 C CNN
F 1 "GND" H 6005 4252 50  0000 C CNN
F 2 "" H 6000 4425 50  0001 C CNN
F 3 "" H 6000 4425 50  0001 C CNN
	1    6000 4425
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 627773F5
P 5100 6000
F 0 "#PWR?" H 5100 5750 50  0001 C CNN
F 1 "GND" H 5105 5827 50  0000 C CNN
F 2 "" H 5100 6000 50  0001 C CNN
F 3 "" H 5100 6000 50  0001 C CNN
	1    5100 6000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
