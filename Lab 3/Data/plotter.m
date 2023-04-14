close all
clear
%% Load data in wonky way
load('q=1111r=1.mat')       % 1
time_1          = data(1,:);
t_1             = data(2,:);
t_r_1           = data(3,:);
p_1             = data(4,:);
p_r_1           = data(5,:);
e_1             = data(6,:);
e_r_1           = data(7,:);

load('q=1111r=2.mat')       % 2
time_2          = data(1,:);
t_2             = data(2,:);
t_r_2           = data(3,:);
p_2             = data(4,:);
p_r_2           = data(5,:);
e_2             = data(6,:);
e_r_2           = data(7,:);

load('q=5111r=1.mat')       % 3
time_3          = data(1,:);
t_3             = data(2,:);
t_r_3           = data(3,:);
p_3             = data(4,:);
p_r_3           = data(5,:);
e_3             = data(6,:);
e_r_3           = data(7,:);
load('q=5121r=1.mat')       % 4
time_4          = data(1,:);
t_4             = data(2,:);
t_r_4           = data(3,:);
p_4             = data(4,:);
p_r_4           = data(5,:);
e_4             = data(6,:);
e_r_4           = data(7,:);
load('q=20111r=1.mat')      % 5
time_5          = data(1,:);
t_5             = data(2,:);
t_r_5           = data(3,:);
p_5             = data(4,:);
p_r_5           = data(5,:);
e_5             = data(6,:);
e_r_5           = data(7,:);
load('q=11201r=1.mat')      % 6
time_6          = data(1,:);
t_6             = data(2,:);
t_r_6           = data(3,:);
p_6             = data(4,:);
p_r_6           = data(5,:);
e_6             = data(6,:);
e_r_6           = data(7,:);
load('q=1000111r=1.mat')    % 7
time_7          = data(1,:);
t_7             = data(2,:);
t_r_7           = data(3,:);
p_7             = data(4,:);
p_r_7           = data(5,:);
e_7             = data(6,:);
e_r_7           = data(7,:);


%% Plot
start = 10*500 + 1;
stop = 35*500 + 1;

figure(1)
subplot(211)
hold on
plot(time_1(start:stop),t_1(start:stop));
plot(time_1(start:stop),t_2(start:stop));
hold off
grid
ylabel('$\lambda$ [rad]',Interpreter='latex')
legend('T1','T2')

subplot(212)
hold on
plot(time_1(start:stop),p_1(start:stop));
plot(time_1(start:stop),p_2(start:stop));
hold off
grid
ylabel('$p$ [rad]',Interpreter='latex')
xlabel('time [s]')

figure(2)
subplot(211)
hold on
plot(time_1(start:stop),t_3(start:stop));
plot(time_1(start:stop),t_4(start:stop));
hold off
grid
ylabel('$\lambda$ [rad]',Interpreter='latex')
legend('T3','T4')
subplot(212)
hold on
plot(time_1(start:stop),p_3(start:stop));
plot(time_1(start:stop),p_4(start:stop));
hold off
grid
ylabel('$p$ [rad]',Interpreter='latex')
xlabel('time [s]')

figure(3)
subplot(211)
hold on
plot(time_1(start:stop),t_5(start:stop));
plot(time_1(start:stop),t_6(start:stop));
plot(time_1(start:stop),t_7(start:stop));
hold off
grid
ylabel('$\lambda$ [rad]',Interpreter='latex')
legend('T5','T6','T7')

subplot(212)
hold on
plot(time_1(start:stop),p_5(start:stop));
plot(time_1(start:stop),p_6(start:stop));
plot(time_1(start:stop),p_7(start:stop));
hold off
grid
ylabel('$p$ [rad]',Interpreter='latex')
xlabel('time [s]')

figure(4)
subplot(211)
hold on
plot(time_1(start:stop),t_1(start:stop));
plot(time_1(start:stop),t_2(start:stop));
plot(time_1(start:stop),t_3(start:stop));
plot(time_1(start:stop),t_4(start:stop));
hold off
grid
ylabel('$\lambda$ [rad]',Interpreter='latex')
legend('T1','T2','T3','T4')

subplot(212)
hold on
plot(time_1(start:stop),p_1(start:stop));
plot(time_1(start:stop),p_2(start:stop));
plot(time_1(start:stop),p_3(start:stop));
plot(time_1(start:stop),p_4(start:stop));
hold off
grid
ylabel('$p$ [rad]',Interpreter='latex')
xlabel('time [s]')

figure(5)
subplot(211)
hold on
plot(time_1(start:stop),t_1(start:stop));
plot(time_1(start:stop),t_2(start:stop));
plot(time_1(start:stop),t_3(start:stop));
plot(time_1(start:stop),t_4(start:stop));
plot(time_1(start:stop),t_5(start:stop));
plot(time_1(start:stop),t_6(start:stop));
plot(time_1(start:stop),t_7(start:stop));
hold off
grid
ylabel('$\lambda$ [rad]',Interpreter='latex')
legend('T1','T2','T3','T4','T5','T6','T7')

subplot(212)
hold on
plot(time_1(start:stop),p_1(start:stop));
plot(time_1(start:stop),p_2(start:stop));
plot(time_1(start:stop),p_3(start:stop));
plot(time_1(start:stop),p_4(start:stop));
plot(time_1(start:stop),p_5(start:stop));
plot(time_1(start:stop),p_6(start:stop));
plot(time_1(start:stop),p_7(start:stop));
hold off
grid
ylabel('$p$ [rad]',Interpreter='latex')


% figure(6)
% subplot(411)
% hold on
% plot(time_1(start:stop),t_1(start:stop));
% plot(time_1(start:stop),t_2(start:stop));
% plot(time_1(start:stop),t_3(start:stop));
% plot(time_1(start:stop),t_4(start:stop));
% plot(time_1(start:stop),t_5(start:stop));
% plot(time_1(start:stop),t_6(start:stop));
% plot(time_1(start:stop),t_7(start:stop));
% hold off
% grid
% ylabel('$\lambda$ [rad]',Interpreter='latex')
% legend('T1','T2','T3','T4','T5','T6','T7')
% 
% subplot(412)
% hold on
% plot(time_1(start:stop),t_r_1(start:stop));
% plot(time_1(start:stop),t_r_2(start:stop));
% plot(time_1(start:stop),t_r_3(start:stop));
% plot(time_1(start:stop),t_r_4(start:stop));
% plot(time_1(start:stop),t_r_5(start:stop));
% plot(time_1(start:stop),t_r_6(start:stop));
% plot(time_1(start:stop),t_r_7(start:stop));
% hold off
% grid
% ylabel('$r$ [rad/s]',Interpreter='latex')
% 
% subplot(413)
% hold on
% plot(time_1(start:stop),p_1(start:stop));
% plot(time_1(start:stop),p_2(start:stop));
% plot(time_1(start:stop),p_3(start:stop));
% plot(time_1(start:stop),p_4(start:stop));
% plot(time_1(start:stop),p_5(start:stop));
% plot(time_1(start:stop),p_6(start:stop));
% plot(time_1(start:stop),p_7(start:stop));
% hold off
% grid
% ylabel('$p$ [rad]',Interpreter='latex')
% 
% subplot(414)
% hold on
% plot(time_1(start:stop),p_r_1(start:stop));
% plot(time_1(start:stop),p_r_2(start:stop));
% plot(time_1(start:stop),p_r_3(start:stop));
% plot(time_1(start:stop),p_r_4(start:stop));
% plot(time_1(start:stop),p_r_5(start:stop));
% plot(time_1(start:stop),p_r_6(start:stop));
% plot(time_1(start:stop),p_r_7(start:stop));
% hold off
% grid
% xlabel('time [s]')
% ylabel('$\dot{p}$ [rad/s]',Interpreter='latex')