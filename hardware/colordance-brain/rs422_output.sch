EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
L power:+5V #PWR?
U 1 1 6093201F
P 1550 2550
AR Path="/6093201F" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/6093201F" Ref="#PWR036"  Part="1" 
AR Path="/6087EBF5/6093201F" Ref="#PWR053"  Part="1" 
AR Path="/6087FA83/6093201F" Ref="#PWR070"  Part="1" 
F 0 "#PWR036" H 1550 2400 50  0001 C CNN
F 1 "+5V" H 1565 2723 50  0000 C CNN
F 2 "" H 1550 2550 50  0001 C CNN
F 3 "" H 1550 2550 50  0001 C CNN
	1    1550 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60932025
P 1550 4450
AR Path="/60932025" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/60932025" Ref="#PWR037"  Part="1" 
AR Path="/6087EBF5/60932025" Ref="#PWR054"  Part="1" 
AR Path="/6087FA83/60932025" Ref="#PWR071"  Part="1" 
F 0 "#PWR037" H 1550 4200 50  0001 C CNN
F 1 "GND" H 1555 4277 50  0000 C CNN
F 2 "" H 1550 4450 50  0001 C CNN
F 3 "" H 1550 4450 50  0001 C CNN
	1    1550 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6093202B
P 2150 2750
AR Path="/6093202B" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/6093202B" Ref="#PWR038"  Part="1" 
AR Path="/6087EBF5/6093202B" Ref="#PWR055"  Part="1" 
AR Path="/6087FA83/6093202B" Ref="#PWR072"  Part="1" 
F 0 "#PWR038" H 2150 2500 50  0001 C CNN
F 1 "GND" H 2155 2577 50  0000 C CNN
F 2 "" H 2150 2750 50  0001 C CNN
F 3 "" H 2150 2750 50  0001 C CNN
	1    2150 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60932031
P 2150 2600
AR Path="/60932031" Ref="C?"  Part="1" 
AR Path="/6092884E/60932031" Ref="C18"  Part="1" 
AR Path="/6087EBF5/60932031" Ref="C23"  Part="1" 
AR Path="/6087FA83/60932031" Ref="C28"  Part="1" 
F 0 "C18" H 2265 2646 50  0000 L CNN
F 1 "0.1uF" H 2265 2555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2188 2450 50  0001 C CNN
F 3 "~" H 2150 2600 50  0001 C CNN
	1    2150 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 2450 2150 2450
Wire Wire Line
	1550 2550 1900 2550
Wire Wire Line
	1900 2550 1900 2450
Connection ~ 1550 2550
Wire Wire Line
	1150 2800 1150 2550
Wire Wire Line
	1150 2550 1550 2550
$Comp
L Homebrew:AM26LS31x U?
U 1 1 60932044
P 1550 3400
AR Path="/60932044" Ref="U?"  Part="1" 
AR Path="/6092884E/60932044" Ref="U3"  Part="1" 
AR Path="/6087EBF5/60932044" Ref="U4"  Part="1" 
AR Path="/6087FA83/60932044" Ref="U5"  Part="1" 
F 0 "U3" H 1850 2550 50  0000 C CNN
F 1 "AM26LS31x" H 2000 2650 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 1500 4150 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/am26ls31.pdf" H 1550 3400 50  0001 C CNN
F 4 "AM26LS31CDR" H 1550 3400 50  0001 C CNN "MPN"
	1    1550 3400
	1    0    0    -1  
$EndComp
NoConn ~ 1150 2900
$Comp
L Connector:RJ45 J?
U 1 1 6093204B
P 5900 2650
AR Path="/6093204B" Ref="J?"  Part="1" 
AR Path="/6092884E/6093204B" Ref="J9"  Part="1" 
AR Path="/6087EBF5/6093204B" Ref="J11"  Part="1" 
AR Path="/6087FA83/6093204B" Ref="J13"  Part="1" 
F 0 "J9" H 5570 2746 50  0000 R CNN
F 1 "RJ45" H 5570 2655 50  0000 R CNN
F 2 "Connector_RJ:RJ45_Amphenol_54602-x08_Horizontal" V 5900 2675 50  0001 C CNN
F 3 "~" V 5900 2675 50  0001 C CNN
F 4 "54601-908WPLF" H 5900 2650 50  0001 C CNN "MPN"
	1    5900 2650
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60932053
P 5000 2750
AR Path="/60932053" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/60932053" Ref="#PWR045"  Part="1" 
AR Path="/6087EBF5/60932053" Ref="#PWR062"  Part="1" 
AR Path="/6087FA83/60932053" Ref="#PWR079"  Part="1" 
F 0 "#PWR045" H 5000 2500 50  0001 C CNN
F 1 "GND" H 5005 2577 50  0000 C CNN
F 2 "" H 5000 2750 50  0001 C CNN
F 3 "" H 5000 2750 50  0001 C CNN
	1    5000 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2750 5500 2750
Wire Wire Line
	5000 2750 5000 2650
Wire Wire Line
	5000 2650 5500 2650
Connection ~ 5000 2750
$Comp
L Device:C C?
U 1 1 60932060
P 4650 2700
AR Path="/60932060" Ref="C?"  Part="1" 
AR Path="/6092884E/60932060" Ref="C20"  Part="1" 
AR Path="/6087EBF5/60932060" Ref="C25"  Part="1" 
AR Path="/6087FA83/60932060" Ref="C30"  Part="1" 
F 0 "C20" H 4765 2746 50  0000 L CNN
F 1 "0.1uF" H 4765 2655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4688 2550 50  0001 C CNN
F 3 "~" H 4650 2700 50  0001 C CNN
	1    4650 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60932066
P 3750 2600
AR Path="/60932066" Ref="C?"  Part="1" 
AR Path="/6092884E/60932066" Ref="C19"  Part="1" 
AR Path="/6087EBF5/60932066" Ref="C24"  Part="1" 
AR Path="/6087FA83/60932066" Ref="C29"  Part="1" 
F 0 "C19" H 3865 2646 50  0000 L CNN
F 1 "0.1uF" H 3865 2555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3788 2450 50  0001 C CNN
F 3 "~" H 3750 2600 50  0001 C CNN
	1    3750 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2450 3750 2450
Wire Wire Line
	4650 2550 5500 2550
$Comp
L power:GND #PWR?
U 1 1 6093206E
P 4550 2850
AR Path="/6093206E" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/6093206E" Ref="#PWR041"  Part="1" 
AR Path="/6087EBF5/6093206E" Ref="#PWR058"  Part="1" 
AR Path="/6087FA83/6093206E" Ref="#PWR075"  Part="1" 
F 0 "#PWR041" H 4550 2600 50  0001 C CNN
F 1 "GND" H 4555 2677 50  0000 C CNN
F 2 "" H 4550 2850 50  0001 C CNN
F 3 "" H 4550 2850 50  0001 C CNN
	1    4550 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 2850 4450 2850
Wire Wire Line
	4650 2550 4450 2550
Connection ~ 4650 2550
Connection ~ 3750 2450
Wire Wire Line
	3250 2450 3550 2450
$Comp
L Device:D_TVS D?
U 1 1 60932088
P 3550 2600
AR Path="/60932088" Ref="D?"  Part="1" 
AR Path="/6092884E/60932088" Ref="D18"  Part="1" 
AR Path="/6087EBF5/60932088" Ref="D30"  Part="1" 
AR Path="/6087FA83/60932088" Ref="D42"  Part="1" 
F 0 "D18" V 3504 2679 50  0000 L CNN
F 1 "D_TVS_5V" H 3600 2700 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 3550 2600 50  0001 C CNN
F 3 "~" H 3550 2600 50  0001 C CNN
F 4 "SMBJ6.0CD-M3/H" V 3550 2600 50  0001 C CNN "MPN"
	1    3550 2600
	0    -1   -1   0   
$EndComp
Connection ~ 3550 2450
Wire Wire Line
	3550 2450 3750 2450
Connection ~ 4550 2850
Wire Wire Line
	4550 2850 4650 2850
$Comp
L power:GND #PWR?
U 1 1 60932092
P 3650 2750
AR Path="/60932092" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/60932092" Ref="#PWR039"  Part="1" 
AR Path="/6087EBF5/60932092" Ref="#PWR056"  Part="1" 
AR Path="/6087FA83/60932092" Ref="#PWR073"  Part="1" 
F 0 "#PWR039" H 3650 2500 50  0001 C CNN
F 1 "GND" H 3655 2577 50  0000 C CNN
F 2 "" H 3650 2750 50  0001 C CNN
F 3 "" H 3650 2750 50  0001 C CNN
	1    3650 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2750 3650 2750
Wire Wire Line
	3650 2750 3550 2750
Connection ~ 3650 2750
$Comp
L power:GND #PWR?
U 1 1 6093209B
P 4900 2150
AR Path="/6093209B" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/6093209B" Ref="#PWR044"  Part="1" 
AR Path="/6087EBF5/6093209B" Ref="#PWR061"  Part="1" 
AR Path="/6087FA83/6093209B" Ref="#PWR078"  Part="1" 
F 0 "#PWR044" H 4900 1900 50  0001 C CNN
F 1 "GND" H 4905 1977 50  0000 C CNN
F 2 "" H 4900 2150 50  0001 C CNN
F 3 "" H 4900 2150 50  0001 C CNN
	1    4900 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1800 4900 1800
Wire Wire Line
	4900 1800 4900 1850
Connection ~ 4900 1800
Wire Wire Line
	4900 1400 4850 1400
Wire Wire Line
	4900 1800 5100 1800
Wire Wire Line
	5100 1800 5100 2350
Wire Wire Line
	5100 2350 5500 2350
$Comp
L power:GND #PWR?
U 1 1 609320B1
P 4750 1100
AR Path="/609320B1" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/609320B1" Ref="#PWR043"  Part="1" 
AR Path="/6087EBF5/609320B1" Ref="#PWR060"  Part="1" 
AR Path="/6087FA83/609320B1" Ref="#PWR077"  Part="1" 
F 0 "#PWR043" H 4750 850 50  0001 C CNN
F 1 "GND" H 4755 927 50  0000 C CNN
F 2 "" H 4750 1100 50  0001 C CNN
F 3 "" H 4750 1100 50  0001 C CNN
	1    4750 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:D_TVS D?
U 1 1 609320B8
P 4900 1200
AR Path="/609320B8" Ref="D?"  Part="1" 
AR Path="/6092884E/609320B8" Ref="D22"  Part="1" 
AR Path="/6087EBF5/609320B8" Ref="D34"  Part="1" 
AR Path="/6087FA83/609320B8" Ref="D46"  Part="1" 
F 0 "D22" V 4854 1279 50  0000 L CNN
F 1 "D_TVS_DATA" V 4945 1279 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 4900 1200 50  0001 C CNN
F 3 "~" H 4900 1200 50  0001 C CNN
F 4 "SMBJ6.0CD-M3/H" V 4900 1200 50  0001 C CNN "MPN"
	1    4900 1200
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 1050 4750 1050
Wire Wire Line
	4750 1050 4750 1100
Wire Wire Line
	4900 1350 4900 1400
Connection ~ 4900 1400
Wire Wire Line
	4900 1400 5150 1400
Wire Wire Line
	5150 1400 5150 2250
Wire Wire Line
	5150 2250 5500 2250
$Comp
L power:GND #PWR?
U 1 1 609320CE
P 4650 4300
AR Path="/609320CE" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/609320CE" Ref="#PWR042"  Part="1" 
AR Path="/6087EBF5/609320CE" Ref="#PWR059"  Part="1" 
AR Path="/6087FA83/609320CE" Ref="#PWR076"  Part="1" 
F 0 "#PWR042" H 4650 4050 50  0001 C CNN
F 1 "GND" H 4655 4127 50  0000 C CNN
F 2 "" H 4650 4300 50  0001 C CNN
F 3 "" H 4650 4300 50  0001 C CNN
	1    4650 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3950 4650 3950
Wire Wire Line
	4650 3950 4650 4000
Connection ~ 4650 3950
Wire Wire Line
	4650 3550 4600 3550
$Comp
L power:GND #PWR?
U 1 1 609320E1
P 4500 3250
AR Path="/609320E1" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/609320E1" Ref="#PWR040"  Part="1" 
AR Path="/6087EBF5/609320E1" Ref="#PWR057"  Part="1" 
AR Path="/6087FA83/609320E1" Ref="#PWR074"  Part="1" 
F 0 "#PWR040" H 4500 3000 50  0001 C CNN
F 1 "GND" H 4505 3077 50  0000 C CNN
F 2 "" H 4500 3250 50  0001 C CNN
F 3 "" H 4500 3250 50  0001 C CNN
	1    4500 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 3200 4500 3200
Wire Wire Line
	4500 3200 4500 3250
Wire Wire Line
	4650 3500 4650 3550
Connection ~ 4650 3550
Wire Wire Line
	5250 3550 5250 2850
Wire Wire Line
	5250 2850 5500 2850
Wire Wire Line
	4650 3550 5250 3550
Wire Wire Line
	5300 3950 5300 2950
Wire Wire Line
	5300 2950 5500 2950
Wire Wire Line
	4650 3950 5300 3950
Text Label 4850 1400 2    50   ~ 0
LED2_Z
Text Label 4850 1800 2    50   ~ 0
LED2_Y
Text Label 4600 3550 2    50   ~ 0
LED1_Z
Text Label 4600 3950 2    50   ~ 0
LED1_Y
Text Label 1950 3150 0    50   ~ 0
LED1_Z
Text Label 1950 3050 0    50   ~ 0
LED1_Y
Text Label 1950 3300 0    50   ~ 0
LED2_Y
Text Label 1950 3400 0    50   ~ 0
LED2_Z
Text Label 1950 3550 0    50   ~ 0
LED3_Y
Text Label 1950 3650 0    50   ~ 0
LED3_Z
Text Label 1950 3800 0    50   ~ 0
LED4_Y
Text Label 1950 3900 0    50   ~ 0
LED4_Z
Text HLabel 1150 3100 0    50   Input ~ 0
LED1_IN
Text HLabel 1150 3350 0    50   Input ~ 0
LED2_IN
Text HLabel 1150 3600 0    50   Input ~ 0
LED3_IN
Text HLabel 1150 3850 0    50   Input ~ 0
LED4_IN
$Comp
L Connector:RJ45 J?
U 1 1 609731C6
P 9750 2650
AR Path="/609731C6" Ref="J?"  Part="1" 
AR Path="/6092884E/609731C6" Ref="J10"  Part="1" 
AR Path="/6087EBF5/609731C6" Ref="J12"  Part="1" 
AR Path="/6087FA83/609731C6" Ref="J14"  Part="1" 
F 0 "J10" H 9420 2746 50  0000 R CNN
F 1 "RJ45" H 9420 2655 50  0000 R CNN
F 2 "Connector_RJ:RJ45_Amphenol_54602-x08_Horizontal" V 9750 2675 50  0001 C CNN
F 3 "~" V 9750 2675 50  0001 C CNN
F 4 "54601-908WPLF" H 9750 2650 50  0001 C CNN "MPN"
	1    9750 2650
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 609731CC
P 8850 2750
AR Path="/609731CC" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/609731CC" Ref="#PWR052"  Part="1" 
AR Path="/6087EBF5/609731CC" Ref="#PWR069"  Part="1" 
AR Path="/6087FA83/609731CC" Ref="#PWR086"  Part="1" 
F 0 "#PWR052" H 8850 2500 50  0001 C CNN
F 1 "GND" H 8855 2577 50  0000 C CNN
F 2 "" H 8850 2750 50  0001 C CNN
F 3 "" H 8850 2750 50  0001 C CNN
	1    8850 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 2750 9350 2750
Wire Wire Line
	8850 2750 8850 2650
Wire Wire Line
	8850 2650 9350 2650
Connection ~ 8850 2750
$Comp
L Device:C C?
U 1 1 609731D6
P 8500 2700
AR Path="/609731D6" Ref="C?"  Part="1" 
AR Path="/6092884E/609731D6" Ref="C22"  Part="1" 
AR Path="/6087EBF5/609731D6" Ref="C27"  Part="1" 
AR Path="/6087FA83/609731D6" Ref="C32"  Part="1" 
F 0 "C22" H 8615 2746 50  0000 L CNN
F 1 "0.1uF" H 8615 2655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8538 2550 50  0001 C CNN
F 3 "~" H 8500 2700 50  0001 C CNN
	1    8500 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 609731DC
P 7600 2600
AR Path="/609731DC" Ref="C?"  Part="1" 
AR Path="/6092884E/609731DC" Ref="C21"  Part="1" 
AR Path="/6087EBF5/609731DC" Ref="C26"  Part="1" 
AR Path="/6087FA83/609731DC" Ref="C31"  Part="1" 
F 0 "C21" H 7715 2646 50  0000 L CNN
F 1 "0.1uF" H 7715 2555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7638 2450 50  0001 C CNN
F 3 "~" H 7600 2600 50  0001 C CNN
	1    7600 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 2450 7600 2450
Wire Wire Line
	8500 2550 9350 2550
$Comp
L power:GND #PWR?
U 1 1 609731E4
P 8400 2850
AR Path="/609731E4" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/609731E4" Ref="#PWR048"  Part="1" 
AR Path="/6087EBF5/609731E4" Ref="#PWR065"  Part="1" 
AR Path="/6087FA83/609731E4" Ref="#PWR082"  Part="1" 
F 0 "#PWR048" H 8400 2600 50  0001 C CNN
F 1 "GND" H 8405 2677 50  0000 C CNN
F 2 "" H 8400 2850 50  0001 C CNN
F 3 "" H 8400 2850 50  0001 C CNN
	1    8400 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 2850 8300 2850
Wire Wire Line
	8500 2550 8300 2550
Connection ~ 8500 2550
Connection ~ 7600 2450
Connection ~ 8400 2850
Wire Wire Line
	8400 2850 8500 2850
$Comp
L power:GND #PWR?
U 1 1 60973208
P 7500 2750
AR Path="/60973208" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/60973208" Ref="#PWR046"  Part="1" 
AR Path="/6087EBF5/60973208" Ref="#PWR063"  Part="1" 
AR Path="/6087FA83/60973208" Ref="#PWR080"  Part="1" 
F 0 "#PWR046" H 7500 2500 50  0001 C CNN
F 1 "GND" H 7505 2577 50  0000 C CNN
F 2 "" H 7500 2750 50  0001 C CNN
F 3 "" H 7500 2750 50  0001 C CNN
	1    7500 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 2750 7500 2750
Wire Wire Line
	7500 2750 7400 2750
Connection ~ 7500 2750
$Comp
L power:GND #PWR?
U 1 1 60973211
P 8750 2150
AR Path="/60973211" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/60973211" Ref="#PWR051"  Part="1" 
AR Path="/6087EBF5/60973211" Ref="#PWR068"  Part="1" 
AR Path="/6087FA83/60973211" Ref="#PWR085"  Part="1" 
F 0 "#PWR051" H 8750 1900 50  0001 C CNN
F 1 "GND" H 8755 1977 50  0000 C CNN
F 2 "" H 8750 2150 50  0001 C CNN
F 3 "" H 8750 2150 50  0001 C CNN
	1    8750 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 1800 8750 1800
Wire Wire Line
	8750 1800 8750 1850
Connection ~ 8750 1800
Wire Wire Line
	8750 1400 8700 1400
Wire Wire Line
	8750 1800 8950 1800
Wire Wire Line
	8950 1800 8950 2350
Wire Wire Line
	8950 2350 9350 2350
$Comp
L power:GND #PWR?
U 1 1 60973227
P 8600 1100
AR Path="/60973227" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/60973227" Ref="#PWR050"  Part="1" 
AR Path="/6087EBF5/60973227" Ref="#PWR067"  Part="1" 
AR Path="/6087FA83/60973227" Ref="#PWR084"  Part="1" 
F 0 "#PWR050" H 8600 850 50  0001 C CNN
F 1 "GND" H 8605 927 50  0000 C CNN
F 2 "" H 8600 1100 50  0001 C CNN
F 3 "" H 8600 1100 50  0001 C CNN
	1    8600 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 1050 8600 1050
Wire Wire Line
	8600 1050 8600 1100
Wire Wire Line
	8750 1350 8750 1400
Connection ~ 8750 1400
Wire Wire Line
	8750 1400 9000 1400
Wire Wire Line
	9000 1400 9000 2250
Wire Wire Line
	9000 2250 9350 2250
$Comp
L power:GND #PWR?
U 1 1 60973242
P 8500 4300
AR Path="/60973242" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/60973242" Ref="#PWR049"  Part="1" 
AR Path="/6087EBF5/60973242" Ref="#PWR066"  Part="1" 
AR Path="/6087FA83/60973242" Ref="#PWR083"  Part="1" 
F 0 "#PWR049" H 8500 4050 50  0001 C CNN
F 1 "GND" H 8505 4127 50  0000 C CNN
F 2 "" H 8500 4300 50  0001 C CNN
F 3 "" H 8500 4300 50  0001 C CNN
	1    8500 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 3950 8500 3950
Wire Wire Line
	8500 3950 8500 4000
Connection ~ 8500 3950
Wire Wire Line
	8500 3550 8450 3550
$Comp
L power:GND #PWR?
U 1 1 60973255
P 8350 3250
AR Path="/60973255" Ref="#PWR?"  Part="1" 
AR Path="/6092884E/60973255" Ref="#PWR047"  Part="1" 
AR Path="/6087EBF5/60973255" Ref="#PWR064"  Part="1" 
AR Path="/6087FA83/60973255" Ref="#PWR081"  Part="1" 
F 0 "#PWR047" H 8350 3000 50  0001 C CNN
F 1 "GND" H 8355 3077 50  0000 C CNN
F 2 "" H 8350 3250 50  0001 C CNN
F 3 "" H 8350 3250 50  0001 C CNN
	1    8350 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 3200 8350 3200
Wire Wire Line
	8350 3200 8350 3250
Wire Wire Line
	8500 3500 8500 3550
Connection ~ 8500 3550
Wire Wire Line
	9100 3550 9100 2850
Wire Wire Line
	9100 2850 9350 2850
Wire Wire Line
	8500 3550 9100 3550
Wire Wire Line
	9150 3950 9150 2950
Wire Wire Line
	9150 2950 9350 2950
Wire Wire Line
	8500 3950 9150 3950
Text Label 8700 1400 2    50   ~ 0
LED3_Z
Text Label 8700 1800 2    50   ~ 0
LED3_Y
Text Label 8450 3550 2    50   ~ 0
LED4_Z
Text Label 8450 3950 2    50   ~ 0
LED4_Y
Text HLabel 7100 2450 0    50   Input ~ 0
PIR3
Text HLabel 8500 2550 1    50   Input ~ 0
PIR4
Text HLabel 3250 2450 0    50   Input ~ 0
PIR1
Text HLabel 4650 2550 1    50   Input ~ 0
PIR2
$Comp
L Device:D_TVS D?
U 1 1 608F60AE
P 4900 2000
AR Path="/608F60AE" Ref="D?"  Part="1" 
AR Path="/6092884E/608F60AE" Ref="D23"  Part="1" 
AR Path="/6087EBF5/608F60AE" Ref="D35"  Part="1" 
AR Path="/6087FA83/608F60AE" Ref="D47"  Part="1" 
F 0 "D23" V 4854 2079 50  0000 L CNN
F 1 "D_TVS_DATA" V 4945 2079 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 4900 2000 50  0001 C CNN
F 3 "~" H 4900 2000 50  0001 C CNN
F 4 "SMBJ6.0CD-M3/H" V 4900 2000 50  0001 C CNN "MPN"
	1    4900 2000
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_TVS D?
U 1 1 608F64DB
P 4650 3350
AR Path="/608F64DB" Ref="D?"  Part="1" 
AR Path="/6092884E/608F64DB" Ref="D20"  Part="1" 
AR Path="/6087EBF5/608F64DB" Ref="D32"  Part="1" 
AR Path="/6087FA83/608F64DB" Ref="D44"  Part="1" 
F 0 "D20" V 4604 3429 50  0000 L CNN
F 1 "D_TVS_DATA" V 4695 3429 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 4650 3350 50  0001 C CNN
F 3 "~" H 4650 3350 50  0001 C CNN
F 4 "SMBJ6.0CD-M3/H" V 4650 3350 50  0001 C CNN "MPN"
	1    4650 3350
	0    1    1    0   
$EndComp
$Comp
L Device:D_TVS D?
U 1 1 608F6952
P 4650 4150
AR Path="/608F6952" Ref="D?"  Part="1" 
AR Path="/6092884E/608F6952" Ref="D21"  Part="1" 
AR Path="/6087EBF5/608F6952" Ref="D33"  Part="1" 
AR Path="/6087FA83/608F6952" Ref="D45"  Part="1" 
F 0 "D21" V 4604 4229 50  0000 L CNN
F 1 "D_TVS_DATA" V 4695 4229 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 4650 4150 50  0001 C CNN
F 3 "~" H 4650 4150 50  0001 C CNN
F 4 "SMBJ6.0CD-M3/H" V 4650 4150 50  0001 C CNN "MPN"
	1    4650 4150
	0    1    1    0   
$EndComp
$Comp
L Device:D_TVS D?
U 1 1 608F6F83
P 8750 2000
AR Path="/608F6F83" Ref="D?"  Part="1" 
AR Path="/6092884E/608F6F83" Ref="D29"  Part="1" 
AR Path="/6087EBF5/608F6F83" Ref="D41"  Part="1" 
AR Path="/6087FA83/608F6F83" Ref="D53"  Part="1" 
F 0 "D29" V 8704 2079 50  0000 L CNN
F 1 "D_TVS_DATA" V 8795 2079 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 8750 2000 50  0001 C CNN
F 3 "~" H 8750 2000 50  0001 C CNN
F 4 "SMBJ6.0CD-M3/H" V 8750 2000 50  0001 C CNN "MPN"
	1    8750 2000
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_TVS D?
U 1 1 608F76E0
P 8750 1200
AR Path="/608F76E0" Ref="D?"  Part="1" 
AR Path="/6092884E/608F76E0" Ref="D28"  Part="1" 
AR Path="/6087EBF5/608F76E0" Ref="D40"  Part="1" 
AR Path="/6087FA83/608F76E0" Ref="D52"  Part="1" 
F 0 "D28" V 8704 1279 50  0000 L CNN
F 1 "D_TVS_DATA" V 8795 1279 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 8750 1200 50  0001 C CNN
F 3 "~" H 8750 1200 50  0001 C CNN
F 4 "SMBJ6.0CD-M3/H" V 8750 1200 50  0001 C CNN "MPN"
	1    8750 1200
	0    1    1    0   
$EndComp
$Comp
L Device:D_TVS D?
U 1 1 608F7BC7
P 8500 3350
AR Path="/608F7BC7" Ref="D?"  Part="1" 
AR Path="/6092884E/608F7BC7" Ref="D26"  Part="1" 
AR Path="/6087EBF5/608F7BC7" Ref="D38"  Part="1" 
AR Path="/6087FA83/608F7BC7" Ref="D50"  Part="1" 
F 0 "D26" V 8454 3429 50  0000 L CNN
F 1 "D_TVS_DATA" V 8545 3429 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 8500 3350 50  0001 C CNN
F 3 "~" H 8500 3350 50  0001 C CNN
F 4 "SMBJ6.0CD-M3/H" V 8500 3350 50  0001 C CNN "MPN"
	1    8500 3350
	0    1    1    0   
$EndComp
$Comp
L Device:D_TVS D?
U 1 1 608F82B6
P 8500 4150
AR Path="/608F82B6" Ref="D?"  Part="1" 
AR Path="/6092884E/608F82B6" Ref="D27"  Part="1" 
AR Path="/6087EBF5/608F82B6" Ref="D39"  Part="1" 
AR Path="/6087FA83/608F82B6" Ref="D51"  Part="1" 
F 0 "D27" V 8454 4229 50  0000 L CNN
F 1 "D_TVS_DATA" V 8545 4229 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 8500 4150 50  0001 C CNN
F 3 "~" H 8500 4150 50  0001 C CNN
F 4 "SMBJ6.0CD-M3/H" V 8500 4150 50  0001 C CNN "MPN"
	1    8500 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	7100 2450 7400 2450
$Comp
L Device:D_TVS D?
U 1 1 608F927F
P 4450 2700
AR Path="/608F927F" Ref="D?"  Part="1" 
AR Path="/6092884E/608F927F" Ref="D19"  Part="1" 
AR Path="/6087EBF5/608F927F" Ref="D31"  Part="1" 
AR Path="/6087FA83/608F927F" Ref="D43"  Part="1" 
F 0 "D19" V 4404 2779 50  0000 L CNN
F 1 "D_TVS_5V" H 4500 2800 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 4450 2700 50  0001 C CNN
F 3 "~" H 4450 2700 50  0001 C CNN
F 4 "SMBJ6.0CD-M3/H" V 4450 2700 50  0001 C CNN "MPN"
	1    4450 2700
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_TVS D?
U 1 1 608F9926
P 7400 2600
AR Path="/608F9926" Ref="D?"  Part="1" 
AR Path="/6092884E/608F9926" Ref="D24"  Part="1" 
AR Path="/6087EBF5/608F9926" Ref="D36"  Part="1" 
AR Path="/6087FA83/608F9926" Ref="D48"  Part="1" 
F 0 "D24" V 7354 2679 50  0000 L CNN
F 1 "D_TVS_5V" H 7450 2700 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 7400 2600 50  0001 C CNN
F 3 "~" H 7400 2600 50  0001 C CNN
F 4 "SMBJ6.0CD-M3/H" V 7400 2600 50  0001 C CNN "MPN"
	1    7400 2600
	0    -1   -1   0   
$EndComp
Connection ~ 7400 2450
Wire Wire Line
	7400 2450 7600 2450
$Comp
L Device:D_TVS D?
U 1 1 608FA28D
P 8300 2700
AR Path="/608FA28D" Ref="D?"  Part="1" 
AR Path="/6092884E/608FA28D" Ref="D25"  Part="1" 
AR Path="/6087EBF5/608FA28D" Ref="D37"  Part="1" 
AR Path="/6087FA83/608FA28D" Ref="D49"  Part="1" 
F 0 "D25" V 8254 2779 50  0000 L CNN
F 1 "D_TVS_5V" H 8350 2800 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 8300 2700 50  0001 C CNN
F 3 "~" H 8300 2700 50  0001 C CNN
F 4 "SMBJ6.0CD-M3/H" V 8300 2700 50  0001 C CNN "MPN"
	1    8300 2700
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
