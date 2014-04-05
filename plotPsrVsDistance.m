clear all;

temp0 = importdata('PsrVsDistance_0.txt');
for h = 1:length(temp0)/2
    LogDistance_6(1,h) = (temp0((2*h-1),1));
    LogDistance_6(2,h) = temp0((2*h-1),2);
    LogDistance_54(1,h) = log(temp0((2*h),1));
    LogDistance_54(2,h) = temp0((2*h),2);
end

temp1 = importdata('PsrVsDistance_1.txt');
for i = 1:length(temp1)/2
    Cost231_6(1,i) = (temp1((2*i-1),1));
    Cost231_6(2,i) = temp1((2*i-1),2);
    Cost231_54(1,i) = log(temp1((2*i),1));
    Cost231_54(2,i) = temp1((2*i),2);
end

temp2 = importdata('PsrVsDistance_2.txt');
for j = 1:length(temp2)/2
    ItuR1411_6(1,j) = (temp2((2*j-1),1));
    ItuR1411_6(2,j) = temp2((2*j-1),2);
    ItuR1411_54(1,j) = log(temp2((2*j),1));
    ItuR1411_54(2,j) = temp2((2*j),2);
end

temp3 = importdata('PsrVsDistance_3.txt');
for k = 1:length(temp3)/2
    OkumuraHata_6(1,k) = (temp3((2*k-1),1));
    OkumuraHata_6(2,k) = temp3((2*k-1),2);
    OkumuraHata_54(1,k) = log(temp3((2*k),1));
    OkumuraHata_54(2,k) = temp3((2*k),2);
end

endpoint0 = length(LogDistance_6);
endpoint1 = length(Cost231_6);
endpoint2 = length(ItuR1411_6);
endpoint3 = length(OkumuraHata_6);

semilogy(LogDistance_6(1,(1:endpoint0)),LogDistance_6(2,(1:endpoint0)),':b','linewidth',2);
%hold on;
%semilogy(LogDistance_54(1,(1:endpoint0)),LogDistance_54(2,(1:endpoint0)),'b','linewidth',2);
hold on;
%semilogy(Cost231_6(1,(1:endpoint1)),Cost231_6(2,(1:endpoint1)),':r','linewidth',2);
%hold on;
%semilogy(Cost231_54(1,(1:endpoint1)),Cost231_54(2,(1:endpoint1)),'r','linewidth',2);
%hold on;
semilogy(ItuR1411_6(1,(1:endpoint2)),ItuR1411_6(2,(1:endpoint2)),':g','linewidth',2);
%hold on;
%semilogy(ItuR1411_54(1,(1:endpoint2)),ItuR1411_54(2,(1:endpoint2)),'g','linewidth',2);
%hold on;
%semilogy(OkumuraHata_6(1,(1:endpoint3)),OkumuraHata_6(2,(1:endpoint3)),':y','linewidth',2);
%hold on;
%semilogy(OkumuraHata_54(1,(1:endpoint3)),OkumuraHata_54(2,(1:endpoint3)),'y','linewidth',2);

grid on;
%axis([4, inf, -inf, inf]);
xlabel('SNR');
ylabel('PER');