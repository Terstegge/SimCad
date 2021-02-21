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
L Device:R R4
U 1 1 600E24D4
P 6725 4125
F 0 "R4" V 6825 4125 50  0000 C CNN
F 1 "1k12" V 6725 4125 50  0000 C CNN
F 2 "" V 6655 4125 50  0001 C CNN
F 3 "~" H 6725 4125 50  0001 C CNN
	1    6725 4125
	-1   0    0    1   
$EndComp
Connection ~ 5950 4525
$Comp
L Device:R R3
U 1 1 600E8C58
P 6725 3375
F 0 "R3" V 6825 3375 50  0000 C CNN
F 1 "1k8" V 6725 3375 50  0000 C CNN
F 2 "" V 6655 3375 50  0001 C CNN
F 3 "~" H 6725 3375 50  0001 C CNN
	1    6725 3375
	-1   0    0    1   
$EndComp
$Comp
L pspice:ISOURCE I1
U 1 1 600EA72A
P 7250 3825
F 0 "I1" H 6872 3871 50  0000 R CNN
F 1 "5mA" H 6872 3780 50  0000 R CNN
F 2 "" H 7250 3825 50  0001 C CNN
F 3 "~" H 7250 3825 50  0001 C CNN
	1    7250 3825
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6725 3225 6725 3100
Wire Wire Line
	6725 4275 6725 4525
Wire Wire Line
	7250 3425 7250 3100
Wire Wire Line
	7250 4225 7250 4525
Wire Wire Line
	6725 3100 7250 3100
$Comp
L Device:R R1
U 1 1 600E0725
P 5950 3375
F 0 "R1" V 6050 3375 50  0000 C CNN
F 1 "1k6" V 5950 3375 50  0000 C CNN
F 2 "" V 5880 3375 50  0001 C CNN
F 3 "~" H 5950 3375 50  0001 C CNN
	1    5950 3375
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 600E0E0D
P 5950 4150
F 0 "R2" V 6050 4150 50  0000 C CNN
F 1 "2k4" V 5950 4150 50  0000 C CNN
F 2 "" V 5880 4150 50  0001 C CNN
F 3 "~" H 5950 4150 50  0001 C CNN
	1    5950 4150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 600E1865
P 6350 3800
F 0 "R5" V 6450 3800 50  0000 C CNN
F 1 "1k32" V 6350 3800 50  0000 C CNN
F 2 "" V 6280 3800 50  0001 C CNN
F 3 "~" H 6350 3800 50  0001 C CNN
	1    6350 3800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5950 3225 5950 3100
Wire Wire Line
	5950 4300 5950 4525
$Comp
L pspice:VSOURCE V1
U 1 1 600ED628
P 5175 3825
F 0 "V1" H 4809 3779 50  0000 R CNN
F 1 "15V" H 4809 3870 50  0000 R CNN
F 2 "" H 5175 3825 50  0001 C CNN
F 3 "~" H 5175 3825 50  0001 C CNN
	1    5175 3825
	1    0    0    1   
$EndComp
Wire Wire Line
	6725 4525 7250 4525
Wire Wire Line
	5950 4525 6725 4525
Wire Wire Line
	5175 4525 5950 4525
Wire Wire Line
	5175 3100 5950 3100
Connection ~ 6725 4525
Wire Wire Line
	5175 4525 5175 4125
Wire Wire Line
	5175 3100 5175 3525
Wire Wire Line
	5950 3525 5950 3800
Wire Wire Line
	6200 3800 5950 3800
Connection ~ 5950 3800
Wire Wire Line
	5950 3800 5950 4000
Wire Wire Line
	6725 3800 6725 3975
Wire Wire Line
	6725 3525 6725 3800
Connection ~ 6725 3800
Wire Wire Line
	6500 3800 6725 3800
$EndSCHEMATC
