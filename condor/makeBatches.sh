#!/bin/bash

mu="A B C D"
muA="A1 A2 A3 A4 A5 A6"
muB="B1 B2 B3 B4 B5 B6 B7 B8 B9 B10 B11 B12 B13 B14 B15 B16 B17 B18 B19 B20"
muC="C1 C2 C3 C4 C5 C6 C7 C8 C9 C10 C11 C12 C13 C14 C15 C16 C17 C18 C19 C20 C21 C22 C23 C24 C25 C26 C27 C28 C29 C30 C31 C32 C33 C34"
muD="D1 D2 D3 D4 D5 D6 D7 D8 D9 D10 D11 D12 D13 D14 D15 D16 D17 D18 D19 D20 D21 D22 D23 D24 D25 D26 D27 D28 D29"

e="A B C D"
eA="A1 A2 A3 A4 A5"
eB="B1 B2 B3 B4 B5 B6 B7 B8 B9 B10 B11 B12 B13 B14 B15"
eC="C1 C2 C3 C4 C5 C6 C7 C8 C9 C10 C11 C12 C13 C14 C15 C16 C17 C18 C19 C20 C21 C22 C23 C24"
eD="D1 D2 D3 D4 D5 D6 D7 D8 D9 D10 D11 D12 D13 D14 D15 D16 D17 D18 D19 D20 D21 D22 D23 D24 D25 D26 D27 D28 D29 D30"

met="A B C D"
metA="A"
metB="B1 B2 B3 B4"
metC="C1 C2 C3 C4 C5 C6 C7 C8"
metD="D1 D2 D3 D4 D5 D6"

tt="TT1 TT2 TT3 TT4 TT5 TT6 TT7 TT8 TT9 TT10 TT11 TT12 TTll1 TTll2 TTll3 TTll4 TTll5 TTll6 TThh1 TThh2 TThh3 TThh4 TThh5 TThh6 TThh7 TThh8 TTlh1 TTlh2 TTlh3 TTlh4 TTlh5 TTlh6 TTlh7"
wj="WJ1 WJ2 WJ3 WJ4 WJ5 WJ6 WJ7 WJ8 WJ9 WJ10 WJ11 WJ12 WJ13 WJ14 WJ15 WJ16 WJ17 WJ18 WJ19 WJ20 WJ21 WJ22 WJ23 WJ24 WJ25 WJ26 WJ27 WJ28 WJ29"
w1j="W1J1 W1J2 W1J3 W1J4 W1J5 W1J6 W1J7 W1J8 W1J9 W1J10 W1J11 W1J12"
w2j="W2J1 W2J2 W2J3 W2J4 W2J5 W2J6 W2J7 W2J8 W2J9 W2J10 W2J11 W2J12 W2J13 W2J14 W2J15 W2J16 W2J17"
w3j="W3J1 W3J2 W3J3 W3J4 W3J5 W3J6 W3J7 W3J8"
w4j="W4J1 W4J2 W4J3 W4J4 W4J5 W4J6 W4J7" 
zn="ZN1 ZN2 ZN3 ZN4"
zj="ZJ1 ZJ2 ZJ3 ZJ4 ZJ5 ZJ6 ZJ7 ZJ8 ZJ9 ZJ10 ZJ11 ZJ12 ZJ13 ZJ14 ZJ15 ZJ16"
vv="WW1 WW2 WW3 WW4 WW5 WZ1 WZ2 WZ3 WZ4 WZ5 ZZ1 ZZ2 ZZ3 ZZ4 ZZ5"
top="T1 T2 T3 T4 T5 T6"

w3jsu="W3Jsu1 W3Jsu2 W3Jsu3 W3Jsu4"
w3jsd="W3Jsd1 W3Jsd2 W3Jsd3 W3Jsd4"
w3jmu="W3Jmu1 W3Jmu2 W3Jmu3 W3Jmu4 W3Jmu5"
w3jmd="W3Jmd1 W3Jmd2 W3Jmd3 W3Jmd4 W3Jmd5"
w4jsu="W4Jsu1 W4Jsu2 W4Jsu3 W4Jsu4 W4Jsu5 W4Jsu6"
w4jsd="W4Jsd1 W4Jsd2 W4Jsd3 W4Jsd4 W4Jsd5"
w4jmu="W4Jmu1 W4Jmu2 W4Jmu3 W4Jmu4"
w4jmd="W4Jmd1 W4Jmd2 W4Jmd3 W4Jmd4 W4Jmd5"

#qcd="QCD_170_300 QCD_300_470 QCD_470_600 QCD_600_800 QCD_800_1000 QCD_1000_1400 QCD_1400_1800"
#processes="C1 C2 C3 C4 C5 C6 C7 C8 C9 C10 C11 C12 C13 C14 C15"
##sm="/home/kkotov/CMSSW_5_3_8/src/OSUAnalysis/BEANsTools/SingleMu2012"
##processes="$sm\B_0/ $sm\B_1/ $sm\B_2/ $sm\B_3/ $sm\B_4/ $sm\B_5/ $sm\B_6/ $sm\B_7/ $sm\B_8/ $sm\D_0/ $sm\D_1/ $sm\D_2/ $sm\D_3/ $sm\D_4/ $sm\D_5/ $sm\D_6/ $sm\D_7/ $sm\D_8/ $sm\D_9/ $sm\D_10/ $sm\D_11/ $sm\D_12/ $sm\D_13/"
#processes="$tt $wj $w1j $w2j $w3j $w4j $zn $zj $top $vv"
#processes="$muA $muB $muC $muD $tt $wj $w1j $w2j $w3j $w4j $zj $top $vv"
#processes="$eA $eB $eC $eD $tt $wj $w1j $w2j $w3j $w4j $zj $top $vv"
#processes="C2 C3 C4 C5 C6 C7 C8 C9 C30 C31 C32 C33 C34 D10 D11 D12 D13 D14 D15 D16 D17 D18 D19"
#processes="$metA $metB $metC $metD $tt $wj $w1j $w2j $w3j $w4j $zn $top $vv"
#processes="$w3jsu $w3jsd $w3jmu $w3jmd $w4jsu $w4jsd $w4jmu $w4jmd"
processes="D TTlh1 TTlh2 TTlh3 TTlh4 TTlh5 TTlh6 TTlh7"
#processes="$muA $muB $muC $muD"

for s in $processes; do
   arguments="-sd -d$s -o/data/users/kkotov/2013.12.10/"
   cat batch.jdf | sed -e "s|ARGS|$arguments|g" -e "s|OUT|$s|g" -e "s|ERR|$s|g" -e "s|LOG|$s|g" > tmp/batch$s""met.jdf
done;
