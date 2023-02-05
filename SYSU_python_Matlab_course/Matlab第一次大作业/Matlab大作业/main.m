clc,clear;
syms x1 x2 s; %声明符号变量
f1 =2*x1^2+4*x2^2-6*x1-2*x1*x2;%设定目标函数
[k f1 f2 f3]=grad(f1,x1,x2,s,[0,1],10^(-5));  %设定起始点[x1 x2]=[-2.5,4.25]和精度10^(-2)
[result]=sprintf('在 %d 次迭代后求出极小值\n',k);%在迭代多少次之后求出极小值
disp(result);
figure(1)
plot(1:k,f3)
title('迭代过程')
xlabel('迭代次数')
ylabel('极小值')
figure(2)
plot3(f1,f2,f3)
hold on
syms x1 x2
f=2*x1^2+4*x2^2-6*x1-2*x1*x2;
fmesh(f)


