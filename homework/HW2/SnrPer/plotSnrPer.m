clear all;

Yans = importdata('hw2SnrPer1.txt');
for j = 1:length(Yans.data)
    plotYans(1,j) = log(Yans.data((length(Yans.data)-j+1),1));
    plotYans(2,j) = Yans.data((length(Yans.data)-j+1),2);
end
Nist = importdata('hw2SnrPer2.txt');
for i = 1:length(Nist.data)
    plotNist(1,i) = log(Nist.data((length(Nist.data)-i+1),1));
    plotNist(2,i) = Nist.data((length(Nist.data)-i+1),2);
end
Dsss = importdata('hw2SnrPer3.txt');
for k = 1:length(Dsss.data)
    plotDsss(1,k) = log(Dsss.data((length(Dsss.data)-k+1),1));
    plotDsss(2,k) = Dsss.data((length(Dsss.data)-k+1),2);
end

%endpoint1=length(Yans.data);
endpoint1=70;
%endpoint2=length(Nist.data);
endpoint2=89;
%endpoint3=length(Dsss.data);
endpoint3=108;
semilogy(plotYans(1,(1:endpoint1)),plotYans(2,(1:endpoint1)),'linewidth',2,'color','b');
hold on;
semilogy(plotNist(1,(1:endpoint2)),plotNist(2,(1:endpoint2)),'linewidth',2,'color','r');
hold on;
semilogy(plotDsss(1,(1:endpoint3)),plotDsss(2,(1:endpoint3)),'linewidth',2,'color',[0.3 0.7 0.1]);
legend('Yans error rate model','Nist error rate model','Dsss error rate model','location','southwest');
grid on;
%axis([-0.5, 3, -inf, inf]);
xlabel('SNR');
ylabel('PER');