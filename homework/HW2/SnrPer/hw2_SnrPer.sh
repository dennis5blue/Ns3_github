#!/bin/bash
step=1
errorModel=3
echo "Type: Psr" > hw2SnrPer3.txt

if [ "${errorModel}" = "1" ]; then
  echo "Yans error rate model" >> hw2SnrPer1.txt
fi
if [ "${errorModel}" = "2" ]; then
  echo "Nist error rate model" >> hw2SnrPer2.txt
fi
if [ "${errorModel}" = "3" ]; then
  echo "Dsss error rate model" >> hw2SnrPer3.txt
fi

echo "SNR PER" >> hw2SnrPer3.txt

for (( i=50; i<=200; i=i+1 )) do
  arg1=$(( ${i}*${step} ))
  echo ${arg1}
  ./waf --run "scratch/mywifi-phy-test Psr --Distance=${arg1} --NPackets=1 --TxPowerLevel=0 --ErrorRateModel=${errorModel}" >> hw2SnrPer3.txt
done
