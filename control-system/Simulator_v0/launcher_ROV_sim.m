close all
clear
clc

%% EQUATION PARAMETERS
m = 16.6;               % [kg] mass of the ROV (EVA)
g = 9.81;               %w [m/s^2] gravity acceleration

x_g = 0;                % [m] CoM x displacement w.r.t. Body Frame
y_g = 0;                % [m] CoM y displacement w.r.t. Body Frame
z_g = 0;                % [m] CoM z displacement w.r.t. Body Frame

r_g = [x_g y_g z_g]';   % [m] position of the CoM w.r.t. Body Frame

x_b = 0;                % [m] CoB x displacement w.r.t. Body Frame
y_b = 0;                % [m] CoB y displacement w.r.t. Body Frame
z_b = -0.03;            % [m] CoB z displacement w.r.t. Body Frame

r_b = [x_b y_b z_b]';   % [m] position of the CoB w.r.t. Body Frame

rho = 1000;             % [kg/m^3] Water density
V = 0.0123;             % [m^3] Water volume displaced by the ROV

W = m*g;                % [N] Gravity force
B = rho*V*g*1.4;        % [N] Buoyancy

%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Inertia Matrix %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

I_xx = 0.40423;         % [kg*m^2]
I_yy = 0.66054;         % [kg*m^2]
I_zz = 0.92002;         % [kg*m^2]

% I_xy = 0;               % [kg*m^2]
% I_xz = 0;               % [kg*m^2]
% I_yz = 0;               % [kg*m^2]

I_xy = 0.04893;         % [kg*m^2]
I_xz = 0.06762;         % [kg*m^2]
I_yz = 0.01505;         % [kg*m^2]

I_yx = I_xy;            % [kg*m^2]
I_zx = I_xz;            % [kg*m^2]
I_zy = I_yz;            % [kg*m^2]

I = [I_xx   -I_xy   -I_xz
    -I_yx    I_yy   -I_yz
    -I_zx   -I_zy    I_zz];

%%%%%%%%%%%%%%%%%%%%%%%%% Rigid Body Mass Matrix %%%%%%%%%%%%%%%%%%%%%%%%%%

M_rigidBody = [m        0        0        0          m*z_g     -m*y_g
               0        m        0       -m*z_g      0          m*x_g
               0        0        m        m*y_g     -m*x_g      0
               0       -m*z_g    m*y_g    I_xx      -I_xy      -I_xz
               m*z_g    0       -m*x_g   -I_yx       I_yy      -I_yz
              -m*y_g    m*x_g    0       -I_zx      -I_zy       I_zz];

%%%%%%%%%%%%%%%%%%%%%%%%%% Added Mass Matrix %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% M_addedMass = [1.3169   -0.0021    0.0696   -0.0048   -0.1638    0.0566
%               -0.0060    2.5699   -1.5636    0.2205   -0.0630    0.1964
%                0.0840   -1.3483   14.4260   -1.0902    0.2693    0.0582
%               -0.0071    0.1903   -1.0924    0.2089   -0.0750   -0.0300
%               -0.1308   -0.0560    0.2805   -0.0761    0.3637   -0.0061
%                0.0616    0.1961    0.0680   -0.0313   -0.0085    0.1482];

M_addedMass = [1.3169    0         0         0         0         0
               0         2.5699    0         0         0         0
               0         0        14.4260    0         0         0
               0         0         0         0.2089    0         0
               0         0         0         0         0.3637    0
               0         0         0         0         0         0.1482];

%%%%%%%%%%%%%%%%%%%%%%%%%%% Damping Matrices %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Linear damping
D_u = 9.716;
D_v = 20.53;
D_w = 68.855;

D_p = 0.07;   %
D_q = 0.07;   % da rivedere
D_r = 0.07;   %

D_linear = diag([D_u, D_v, D_w, D_p, D_q, D_r]);

% Quadratic damping
D_uu = 18.18;   %
D_vv = 21.66;   % da rivedere
D_ww = 36.99;   %

D_pp = 1.55;   %
D_qq = 1.55;   % da rivedere
D_rr = 1.55;   %

D_quadratic = diag([D_uu, D_vv, D_ww, D_pp, D_qq, D_rr]);

%% MOTOR DYNAMICS

%%%%%%%%%%%%%%%%%%%%%%% Thrust Configuration Matrix %%%%%%%%%%%%%%%%%%%%%%%

% TCM = [ -0.7071   -0.7071    0.7071    0.7071    0         0         0         0
%          0.7071   -0.7071    0.7071   -0.7071    0         0         0         0
%          0         0         0         0         1.0000    1.0000    1.0000    1.0000
%         -0.0223    0.0223   -0.0223    0.0223    0.2187   -0.2297    0.2944   -0.3026
%         -0.0223   -0.0223    0.0223    0.0223   -0.2187   -0.2297    0.2944    0.3026
%          0.2056   -0.2183   -0.2667    0.2795    0         0         0         0 ];

TCM = [ -0.7071   -0.7071    0.7071    0.7071    0         0         0         0
         0.7071   -0.7071    0.7071   -0.7071    0         0         0         0
         0         0         0         0         1.0000    1.0000    1.0000    1.0000
        -0.0223    0.0223   -0.0223    0.0223    0.2613   -0.2613    0.2613   -0.2613
        -0.0223   -0.0223    0.0223    0.0223   -0.2613   -0.2613    0.2613    0.2613
         0.2425   -0.2425   -0.2425    0.2425    0         0         0         0 ];

%%%%%%%%%%%%%%%%%%%%%%%%%%% Look-Up Table %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

lookup = readtable('lookup.xlsx');
pwm = lookup.PWM;
force = lookup.Force_14V_Kgf;

load lqr

%% SIMULATION SETTINGS
sim_time = 100;
Ts = 0.01;
open('sim_ROV_v0_R2018b.slx')
% sim('sim_ROV_v0_R2018b.slx')