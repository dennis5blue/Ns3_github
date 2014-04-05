%p2p rate = 5Mbps, p2p delay = 2ms
%csma rate = 100Mbps, csma delay = 6560ns
data0 = dlmread('mysecond_3_1-1000_001_1024_speed0.txt'); 
throughput0 = data0(:,1)';
dataLength0 = length(throughput0);
maxPacket0 = [1:dataLength0];
maxPacket0 = 10*maxPacket0;

%p2p rate = 5Mbps, p2p delay = 2ms
%csma rate = 50Mbps, csma delay = 6560ns
data1 = dlmread('mysecond_3_1-1000_001_1024_speed1.txt'); 
throughput1 = data1(:,1)';
dataLength1 = length(throughput1);
maxPacket1 = [1:dataLength1];
maxPacket1 = 10*maxPacket1;

%p2p rate = 5Mbps, p2p delay = 2ms
%csma rate = 20Mbps, csma delay = 6560ns
data5 = dlmread('mysecond_3_1-1000_001_1024_speed5.txt'); 
throughput5 = data5(:,1)';
dataLength5 = length(throughput5);
maxPacket5 = [1:dataLength5];
maxPacket5 = 10*maxPacket5;

%p2p rate = 5Mbps, p2p delay = 2ms
%csma rate = 15Mbps, csma delay = 6560ns
data6 = dlmread('mysecond_3_1-1000_001_1024_speed6.txt'); 
throughput6 = data6(:,1)';
dataLength6 = length(throughput6);
maxPacket6 = [1:dataLength6];
maxPacket6 = 10*maxPacket6;

for ii=1:(length(throughput5)-1)
    if(throughput5(ii+1) < throughput5(ii))
        throughput5(ii+1) = throughput5(ii);
    end
end

figure;
%G0 = plot(maxPacket0,throughput0,'r','linewidth',2);
%hold on;
%G2 = plot(maxPacket2,throughput2,'b','linewidth',2);
%hold on;
%G3 = plot(maxPacket3,throughput3,'g','linewidth',2);
%hold on;
G1 = plot(maxPacket1,throughput1,'r','linewidth',2);
hold on;
G5 = plot(maxPacket5,throughput5,'g','linewidth',2);
hold on;
G6 = plot(maxPacket6,throughput6,'b','linewidth',2);


axis([0,1000,-inf,inf]);
hleg = legend('50M','20M','15M','location','NorthEast');
grid on;
title('Network throughput under different channel rate','FontSize',11);
xlabel('Total transmitted packet','FontSize',11);
ylabel('Throughput (kb/s)','FontSize',11);