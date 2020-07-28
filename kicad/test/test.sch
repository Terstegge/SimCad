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
L 74xx:74LS161 U1
U 1 1 5F5A7CD8
P 6150 3700
F 0 "U1" H 5900 4350 50  0000 C CNN
F 1 "74LS161" H 6400 4350 50  0000 C CNN
F 2 "" H 6150 3700 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS161" H 6150 3700 50  0001 C CNN
	1    6150 3700
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR01
U 1 1 5F5A8B7E
P 6150 2900
F 0 "#PWR01" H 6150 2750 50  0001 C CNN
F 1 "VCC" H 6165 3073 50  0000 C CNN
F 2 "" H 6150 2900 50  0001 C CNN
F 3 "" H 6150 2900 50  0001 C CNN
	1    6150 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5F5A93B8
P 6150 4500
F 0 "#PWR02" H 6150 4250 50  0001 C CNN
F 1 "GND" H 6155 4327 50  0000 C CNN
F 2 "" H 6150 4500 50  0001 C CNN
F 3 "" H 6150 4500 50  0001 C CNN
	1    6150 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 3200 7000 3200
Wire Wire Line
	6650 3300 7000 3300
Wire Wire Line
	6650 3400 7000 3400
Wire Wire Line
	6650 3500 7000 3500
Wire Wire Line
	6650 3700 7000 3700
Text Label 7000 3200 2    50   ~ 0
Q0
Text Label 7000 3300 2    50   ~ 0
Q1
Text Label 7000 3400 2    50   ~ 0
Q2
Text Label 7000 3500 2    50   ~ 0
Q3
Text Label 7000 3700 2    50   ~ 0
RCO
Wire Wire Line
	5650 3200 5350 3200
Wire Wire Line
	5650 3300 5350 3300
Wire Wire Line
	5650 3400 5350 3400
Wire Wire Line
	5650 3500 5350 3500
Text Label 5350 3200 0    50   ~ 0
D0
Text Label 5350 3300 0    50   ~ 0
D1
Text Label 5350 3400 0    50   ~ 0
D2
Text Label 5350 3500 0    50   ~ 0
D3
Text Label 5350 4000 0    50   ~ 0
CLK
Wire Wire Line
	5350 4000 5650 4000
Wire Wire Line
	5650 4200 5350 4200
Text Label 5350 4200 0    50   ~ 0
~CLR
Text Label 5350 3700 0    50   ~ 0
~LOAD
Wire Wire Line
	5350 3700 5650 3700
Text Label 5350 3800 0    50   ~ 0
EP
Text Label 5350 3900 0    50   ~ 0
ET
Wire Wire Line
	5350 3800 5650 3800
Wire Wire Line
	5350 3900 5650 3900
$EndSCHEMATC
