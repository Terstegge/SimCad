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
L power:VCC #PWR01
U 1 1 6270F4CD
P 4750 2950
F 0 "#PWR01" H 4750 2800 50  0001 C CNN
F 1 "VCC" H 4765 3123 50  0000 C CNN
F 2 "" H 4750 2950 50  0001 C CNN
F 3 "" H 4750 2950 50  0001 C CNN
	1    4750 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 6271186D
P 4750 4400
F 0 "#PWR02" H 4750 4150 50  0001 C CNN
F 1 "GND" H 4755 4227 50  0000 C CNN
F 2 "" H 4750 4400 50  0001 C CNN
F 3 "" H 4750 4400 50  0001 C CNN
	1    4750 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 62718AC9
P 6275 3575
F 0 "D2" V 6300 3450 50  0000 R CNN
F 1 "LED" V 6200 3450 50  0000 R CNN
F 2 "" H 6275 3575 50  0001 C CNN
F 3 "~" H 6275 3575 50  0001 C CNN
	1    6275 3575
	0    -1   -1   0   
$EndComp
$Comp
L Transistor_BJT:BC107 Q2
U 1 1 62DBCEC0
P 6175 4050
F 0 "Q2" H 6366 4096 50  0000 L CNN
F 1 "BC107" H 6366 4005 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-18-3" H 6375 3975 50  0001 L CIN
F 3 "http://www.b-kainka.de/Daten/Transistor/BC108.pdf" H 6175 4050 50  0001 L CNN
	1    6175 4050
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC107 Q1
U 1 1 62DCA089
P 4850 4050
F 0 "Q1" H 5041 4096 50  0000 L CNN
F 1 "BC107" H 5041 4005 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-18-3" H 5050 3975 50  0001 L CIN
F 3 "http://www.b-kainka.de/Daten/Transistor/BC108.pdf" H 4850 4050 50  0001 L CNN
	1    4850 4050
	-1   0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 62DCAB38
P 4750 3600
F 0 "D1" V 4800 3375 50  0000 L CNN
F 1 "LED" V 4700 3375 50  0000 L CNN
F 2 "" H 4750 3600 50  0001 C CNN
F 3 "~" H 4750 3600 50  0001 C CNN
	1    4750 3600
	0    1    -1   0   
$EndComp
$Comp
L Device:CP C1
U 1 1 62DD4B6E
P 5175 3800
F 0 "C1" V 5430 3800 50  0000 C CNN
F 1 "100uF" V 5339 3800 50  0000 C CNN
F 2 "" H 5213 3650 50  0001 C CNN
F 3 "~" H 5175 3800 50  0001 C CNN
	1    5175 3800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R4
U 1 1 62DE1815
P 6275 3200
F 0 "R4" H 6350 3200 50  0000 L CNN
F 1 "1k" V 6275 3150 50  0000 L CNN
F 2 "" V 6205 3200 50  0001 C CNN
F 3 "~" H 6275 3200 50  0001 C CNN
	1    6275 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 3050 4750 2950
Wire Wire Line
	4750 2950 5425 2950
Wire Wire Line
	6275 2950 6275 3050
Wire Wire Line
	6275 4400 6275 4250
Connection ~ 4750 4400
Wire Wire Line
	4750 4400 6275 4400
Wire Wire Line
	5425 3225 5425 2950
Connection ~ 5425 2950
Wire Wire Line
	5425 2950 5625 2950
Wire Wire Line
	5625 3225 5625 2950
Connection ~ 5625 2950
Wire Wire Line
	5625 2950 6275 2950
Wire Wire Line
	5325 3800 5425 3800
Wire Wire Line
	5425 3800 5425 3525
Wire Wire Line
	5625 3525 5625 3800
Wire Wire Line
	5625 3800 5725 3800
Wire Wire Line
	6025 3800 6275 3800
Wire Wire Line
	6275 3800 6275 3725
Wire Wire Line
	6275 3850 6275 3800
Connection ~ 6275 3800
Wire Wire Line
	4750 3850 4750 3800
Wire Wire Line
	5025 3800 4750 3800
Connection ~ 4750 3800
Wire Wire Line
	4750 3800 4750 3750
Wire Wire Line
	4750 3450 4750 3350
Wire Wire Line
	6275 3425 6275 3350
Wire Wire Line
	5050 4050 5425 4050
Wire Wire Line
	5425 4050 5625 3800
Connection ~ 5625 3800
Wire Wire Line
	5975 4050 5625 4050
Wire Wire Line
	5625 4050 5425 3800
Connection ~ 5425 3800
Connection ~ 4750 2950
Wire Wire Line
	4750 4250 4750 4400
$Comp
L Device:R R1
U 1 1 6270F8BB
P 4750 3200
F 0 "R1" H 4575 3200 50  0000 L CNN
F 1 "1k" V 4750 3150 50  0000 L CNN
F 2 "" V 4680 3200 50  0001 C CNN
F 3 "~" H 4750 3200 50  0001 C CNN
	1    4750 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 62DD586F
P 5875 3800
F 0 "C2" V 5620 3800 50  0000 C CNN
F 1 "100uF" V 5711 3800 50  0000 C CNN
F 2 "" H 5913 3650 50  0001 C CNN
F 3 "~" H 5875 3800 50  0001 C CNN
	1    5875 3800
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 62DE72E4
P 5625 3375
F 0 "R3" H 5675 3375 50  0000 L CNN
F 1 "22k" V 5625 3300 50  0000 L CNN
F 2 "" V 5555 3375 50  0001 C CNN
F 3 "~" H 5625 3375 50  0001 C CNN
	1    5625 3375
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 62711EBB
P 5425 3375
F 0 "R2" H 5250 3375 50  0000 L CNN
F 1 "22k" V 5425 3300 50  0000 L CNN
F 2 "" V 5355 3375 50  0001 C CNN
F 3 "~" H 5425 3375 50  0001 C CNN
	1    5425 3375
	1    0    0    -1  
$EndComp
$EndSCHEMATC