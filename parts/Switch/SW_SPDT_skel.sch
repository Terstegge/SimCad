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
L Device:R R21
U 1 1 6276D0BA
P 5450 3250
F 0 "R21" V 5243 3250 50  0000 C CNN
F 1 "0" V 5334 3250 50  0000 C CNN
F 2 "" V 5380 3250 50  0001 C CNN
F 3 "~" H 5450 3250 50  0001 C CNN
	1    5450 3250
	0    1    1    0   
$EndComp
$Comp
L Device:R R23
U 1 1 6276D5BB
P 5450 3650
F 0 "R23" V 5243 3650 50  0000 C CNN
F 1 "1M" V 5334 3650 50  0000 C CNN
F 2 "" V 5380 3650 50  0001 C CNN
F 3 "~" H 5450 3650 50  0001 C CNN
	1    5450 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	5300 3250 5300 3450
Wire Wire Line
	5300 3450 5075 3450
Connection ~ 5300 3450
Wire Wire Line
	5300 3450 5300 3650
Wire Wire Line
	5600 3250 5800 3250
Wire Wire Line
	5600 3650 5800 3650
Text Label 5075 3450 2    50   ~ 0
p2
Text Label 5800 3250 0    50   ~ 0
p1
Text Label 5800 3650 0    50   ~ 0
p3
$EndSCHEMATC
