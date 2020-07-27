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
L 74xx:74LS138 U1
U 1 1 5F23C86A
P 5850 3650
F 0 "U1" H 5600 4100 50  0000 C CNN
F 1 "74LS138" H 6100 4100 50  0000 C CNN
F 2 "" H 5850 3650 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS138" H 5850 3650 50  0001 C CNN
	1    5850 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3350 6600 3350
Wire Wire Line
	6350 3450 6600 3450
Wire Wire Line
	6350 3550 6600 3550
Wire Wire Line
	6350 3650 6600 3650
Wire Wire Line
	6350 3750 6600 3750
Wire Wire Line
	6350 3850 6600 3850
Wire Wire Line
	6350 3950 6600 3950
Wire Wire Line
	6350 4050 6600 4050
Text Label 6600 3350 0    50   ~ 0
O0
Text Label 6600 3450 0    50   ~ 0
O1
Text Label 6600 3550 0    50   ~ 0
O2
Text Label 6600 3650 0    50   ~ 0
O3
Text Label 6600 3750 0    50   ~ 0
O4
Text Label 6600 3850 0    50   ~ 0
O5
Text Label 6600 3950 0    50   ~ 0
O6
Text Label 6600 4050 0    50   ~ 0
O7
Wire Wire Line
	5350 3350 4950 3350
Wire Wire Line
	5350 3450 4950 3450
Wire Wire Line
	5350 3550 4950 3550
Text Label 4950 3350 0    50   ~ 0
A0
Text Label 4950 3450 0    50   ~ 0
A1
Text Label 4950 3550 0    50   ~ 0
A2
Wire Wire Line
	5350 3850 4950 3850
Wire Wire Line
	5350 3950 4950 3950
Wire Wire Line
	5350 4050 4950 4050
Text Label 4950 3850 0    50   ~ 0
E3
Text Label 4950 3950 0    50   ~ 0
E2n
Text Label 4950 4050 0    50   ~ 0
E1n
$Comp
L power:VCC #PWR0101
U 1 1 5F2459E4
P 5850 3050
F 0 "#PWR0101" H 5850 2900 50  0001 C CNN
F 1 "VCC" H 5865 3223 50  0000 C CNN
F 2 "" H 5850 3050 50  0001 C CNN
F 3 "" H 5850 3050 50  0001 C CNN
	1    5850 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5F246D93
P 5850 4350
F 0 "#PWR0102" H 5850 4100 50  0001 C CNN
F 1 "GND" H 5855 4177 50  0000 C CNN
F 2 "" H 5850 4350 50  0001 C CNN
F 3 "" H 5850 4350 50  0001 C CNN
	1    5850 4350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
