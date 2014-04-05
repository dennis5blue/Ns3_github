for (( i = 1; i <= 100; i++));
do
  arg1=`bc <<< "${i}*10"`
  arg2=`bc <<< "${i}*0.001"`
  #       echo $arg1 
  #       echo $arg2
  #./waf --run "scratch/mysecond --nCsma=3 --maxPacket=${arg1} --interval=0.001"
  ./waf --run "scratch/mysecond --nCsma=3 --maxPacket=${arg1} --interval=0.001 --packetSize=1024" 
  #      ${arg2}"
done
