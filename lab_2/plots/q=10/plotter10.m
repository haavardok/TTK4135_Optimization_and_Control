% close all
clear
load('q=10.mat')
load ('fra_andre/t.mat')
load ('fra_andre/x1.mat')
load ('fra_andre/x2.mat')
load ('fra_andre/x3.mat')
load ('fra_andre/x4.mat')
load ('fra_andre/u_q=10.mat')
time = data(1,:);
travel = data(2,:);
travel_rate = data(3,:);
pitch = data(4,:);
pitch_rate = data(5,:);
elevation = data(6,:);
elevation_rate = data(7,:);


stop = 55*501;

figure(1)

subplot(511)
stairs(t,u),grid
subplot(512)
plot(time(1:stop),travel(1:stop),'r');
hold on 
plot(t,x1,'b'),grid
ylabel('lambda')

subplot(513)
plot(time(1:stop),travel_rate(1:stop),'r');
hold on 
plot(t,x2,'b'),grid
ylabel('r')

subplot(514)
plot(time(1:stop),pitch(1:stop),'r');
hold on 
plot(t,x3,'b'),grid
ylabel('p')

subplot(515)
plot(time(1:stop),pitch_rate(1:stop),'r');
hold on 
plot(t,x4,'b'),grid
xlabel('tid (s)'),ylabel('pdot')
legend()