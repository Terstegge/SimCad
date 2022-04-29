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
L Device:R R1
U 1 1 6044A8D0
P 5750 3100
F 0 "R1" H 5820 3146 50  0000 L CNN
F 1 "0" H 5820 3055 50  0000 L CNN
F 2 "" V 5680 3100 50  0001 C CNN
F 3 "~" H 5750 3100 50  0001 C CNN
	1    5750 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 6044B00B
P 5750 3650
F 0 "R2" H 5820 3696 50  0000 L CNN
F 1 "0" H 5820 3605 50  0000 L CNN
F 2 "" V 5680 3650 50  0001 C CNN
F 3 "~" H 5750 3650 50  0001 C CNN
	1    5750 3650
	1    0    0    -1  
$EndComp
Text Label 5750 2850 0    50   ~ 0
p1
Text Label 6100 3375 0    50   ~ 0
p2
Text Label 5750 3900 0    50   ~ 0
p3
Wire Wire Line
	5750 3250 5750 3375
Wire Wire Line
	5750 3375 6100 3375
Connection ~ 5750 3375
Wire Wire Line
	5750 3375 5750 3500
Wire Wire Line
	5750 2950 5750 2850
Wire Wire Line
	5750 3900 5750 3800
$EndSCHEMATC
