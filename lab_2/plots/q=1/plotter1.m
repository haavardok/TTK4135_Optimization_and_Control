% close all
clear
load('q=1.mat')
load ('t.mat')
load ('x1.mat')
load ('x2.mat')
load ('x3.mat')
load ('x4.mat')
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
% stairs(t,u),grid
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