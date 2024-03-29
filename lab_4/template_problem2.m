% TTK4135 - Helicopter lab
% Hints/template for problem 2.
% Updated spring 2018, Andreas L. Flåten

%% Initialization and model definition
init05; % Change this to the init file corresponding to your helicopter

%% Continuous time system model
A = [0      1       0           0       0       0;
     0      0     -K_2          0       0       0;
     0      0       0           1       0       0;
     0      0   -K_1*K_pp   -K_1*K_pd   0       0;
     0      0       0           0       0       1;
     0      0       0           0     -K_3*K_ep   -K_3*K_ed];

B = [   0           0;
        0           0;
        0           0;
     K_1*K_pp       0;
        0           0;
        0       K_3*K_ep];

%% Discrete time system model. x = [lambda r p p_dot e e_dot]'

% Using forward-euler 
delta_t	= 0.25; % sampling time
A1 = eye(6) + delta_t * A;
B1 = delta_t * B;

%% Number of states and inputs
mx = size(A1,2); % Number of states (number of columns in A)
mu = size(B1,2); % Number of inputs(number of columns in B)

% Initial values
x1_0 = pi;                              % Lambda
x2_0 = 0;                               % r
x3_0 = 0;                               % p
x4_0 = 0;                               % p_dot
x5_0 = 0;                               % e
x6_0 = 0;                               % e_dot
x0 = [x1_0 x2_0 x3_0 x4_0 x5_0 x6_0]';  % Initial values

% Time horizon and initialization
N  = 40;                               % Time horizon for states
M  = N;                                 % Time horizon for inputs
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
z0 = z;                                 % Initial value for optimization
z0(1) = x1_0;

%% Bounds
ul 	    = -60*pi/360;                   % Lower bound on control
uu 	    = +60*pi/360;                   % Upper bound on control

xl      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);               % Upper bound on states (no bound)
xl(3)   = ul;                           % Lower bound on state x3
xu(3)   = uu;                           % Upper bound on state x3

%% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N,M,xl,xu,ul,uu); % hint: gen_constraints
vlb(N*mx+M*mu)  = 0;                    % We want the last input to be zero
vub(N*mx+M*mu)  = 0;                    % We want the last input to be zero

%% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
Q1 = zeros(mx,mx);                      % the objective function is 1/2 x'Qx + scalar shit, so multiply by two
Q1(1,1) = 1;                            % Weight on state x1, 
Q1(2,2) = 0;                            % Weight on state x2
Q1(3,3) = 0;                            % Weight on state x3
Q1(4,4) = 0;                            % Weight on state x4
Q1(5,5) = 0;                            % Weight on state x5
Q1(6,6) = 0;                            % Weight on state x6

p1 = 1;                                 % Weight on input, THIS IS q in forarbeid
p2 = 1;
P = diag([p1 p2]);
Q = gen_q(Q1,P,N,M);                   % Generate Q, hint: gen_q
% c = zeros(N*mx+M*mu,1);                 % Generate c, this is the linear constant term in the QP

%% Generate system matrixes for linear model
Aeq = gen_aeq(A1,B1,N,mx,mu);             % Generate A, hint: gen_aeq
beq = [A1*x0; zeros((mx*N)-mx,1)];

%% Solve QP problem with linear model


alpha = 0.2;
beta = 20;
lambda_t = 2*pi/3;

options = optimoptions(@fmincon,'Algorithm','sqp','MaxFunctionEvaluations',5*10^4);
params = [N lambda_t alpha beta mx];
tic
z = fmincon(@(z)fun(z,Q),z0,[],[],Aeq,beq,vlb,vub,@(x)nonlcon(x,params),options);
t1=toc;
% Calculate objective value
phi1 = 0.0;
PhiOut = zeros(N*mx+M*mu,1);
for i=1:N*mx+M*mu
  phi1=phi1+Q(i,i)*z(i)*z(i);
  PhiOut(i) = phi1;
end


%% Extract control inputs and states
u1 = [z(N*mx+1:mu:N*mx+M*mu-1);z(N*mx+M*mu-1)]; % Control input from solution
u2 = [z(N*mx+2:mu:N*mx+M*mu);z(N*mx+M*mu)];

x1 = [x0(1);z(1:mx:N*mx)];              % State x1 from solution
x2 = [x0(2);z(2:mx:N*mx)];              % State x2 from solution
x3 = [x0(3);z(3:mx:N*mx)];              % State x3 from solution
x4 = [x0(4);z(4:mx:N*mx)];              % State x4 from solution
x5 = [x0(5);z(5:mx:N*mx)];              % State x5 from solution
x6 = [x0(6);z(6:mx:N*mx)];              % State x6 from solution


num_variables = 15/delta_t;
zero_padding = zeros(num_variables,1);

unit_padding  = ones(num_variables,1);

u1  = [zero_padding; u1; zero_padding];
u2  = [zero_padding; u2; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];
x5  = [zero_padding; x5; zero_padding];
x6  = [zero_padding; x6; zero_padding];



%% To Simulink
u1_timeTable = timetable(u1,'TimeStep',seconds(0.25));
u2_timeTable = timetable(u2,'TimeStep',seconds(0.25));
x1_timeTable = timetable(x1,'TimeStep',seconds(0.25));
x2_timeTable = timetable(x2,'TimeStep',seconds(0.25));
x3_timeTable = timetable(x3,'TimeStep',seconds(0.25));
x4_timeTable = timetable(x4,'TimeStep',seconds(0.25));
x5_timeTable = timetable(x5,'TimeStep',seconds(0.25));
x6_timeTable = timetable(x6,'TimeStep',seconds(0.25));

%% LQR
Q_LQR = diag([1 1 1 1 1 1]); %[travel travel_rate pitch pitch_rate elevation e_rate]
R_LQR = diag([1 1]);

K = dlqr(A1,B1,Q_LQR,R_LQR);

%% Plotting
t = 0:delta_t:delta_t*(length(u1)-1);

figure(2)
subplot(421);
stairs(t,u1),grid;
ylabel('$p_c$','Interpreter','latex');

subplot(422);
stairs(t,u2),grid;
ylabel('$e_c$','Interpreter','latex');

subplot(423);
plot(t,x1,'m',t,x1,'mo'),grid;
ylabel('$\lambda$','Interpreter','latex');

subplot(424);
plot(t,x2,'m',t,x2','mo'),grid;
ylabel('r');

subplot(425);
plot(t,x3,'m',t,x3,'mo'),grid;
ylabel('p');

subplot(426);
plot(t,x4,'m',t,x4,'mo'),grid;
xlabel('tid (s)')
ylabel('$\dot{p}$','Interpreter','latex');

subplot(427);
plot(t,x5,'m',t,x5,'mo'),grid;
xlabel('tid (s)')
ylabel('e');

subplot(428);
plot(t,x6,'m',t,x6,'mo'),grid;
xlabel('tid (s)')
ylabel('$\dot{e}$','Interpreter','latex');

%% Functions 

function f = fun(z,Q)
    f = 1/2*(z')*Q*z;
end

function [c,ceq] = nonlcon(x,params)
    N = params(1);
    lambda_t = params(2);
    alpha = params(3);
    beta = params(4);
    mx = params(5);

    c = alpha*exp(-beta*(x(1:mx:mx*N) - lambda_t).^2) - x(5:mx:mx*N);
    ceq = [];
end