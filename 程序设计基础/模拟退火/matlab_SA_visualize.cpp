clear;clc;close all;
set(0,'defaultfigurecolor','w');
figure
set(gcf,'Position',[200 200 600 600]);
ax = [-1000 1000 -2 0];

%初始化内存，图像
kb = 8.16173324e-5;

%玻尔兹曼常数
x = -1000:1000;
E = 0.3*sin(x/10).*exp(-abs(x/300))-1.5*exp(-abs(x/400));
pos0 = 666;
e0 = E(pos0);

%设置初始温度
T = 3000;
for i = 1:500
    tem = [num2str(T),'K'];
    for k = 1:10000
        if(rand()<0.5)
            pos = pos0+1;
        else
            pos = pos0-1;
        end
        e = E(pos);
        if(rand()<exp((e0-e)/kb/T))
            pos0 = pos;
            e0 = e;
        end
    end

clf;
subplot(2,1,1)
plot(x,E,'b-');hold on;
plot(pos0-1001,E(pos0),'r','markersize',15);
axis(ax);
text(pos0-1020,E(pos0),'O','color','r');
text(-100,-0.5,tem);
ylabel('Energy(eV)');
set(gca,'xtick',[]);

subplot(2,1,2);
rho = exp(-E/kb/T)/max(exp(-E/kb/T));
plot(x,rho,'r-')
axis([-1000 1000 0 1.1]);
ylabel('Probably density');
set(gca,'xtick',[]);
set(gca,'ytick',[]);

rgb = frame2im(getframe(gcf));
%当前帧图转化为rgb图像
[I,map] = rgb2ind(rgb,20);
%rgb图像转化为index图像，以及关联的color map
if(i==1)
    imwrite(I,map,'sim_anneal.gif','gif','Loopcount',0,'DelayTime',0.005);
else
    imwrite(I,map,'sim_anneal.gif','gif','WriteMode','append','DelayTime',0.005);
end
%逐帧写入GIF文件
T=round(T*0.995);
end
