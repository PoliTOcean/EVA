% ************************* Critical Notes ********************************
%
% All input signals from 1100-1500µs correspond to the thruster running in 
% the REVERSE direction for the purposes of this test.
% 
% All input signals from 1500-1900µs correspond to the thruster running in
% the FORWARD direction for the purposes of this test.
% 
% This data represents Bollard thrust of the thruster in static conditions
% with a water inlet velocity of zero.
% 
% All testing is carried out with the Blue Robotics Basic ESC R3, running
% the stock firmware settings and version 16.6 of BlHeli_S. All results are
% dependent on the ESC model and firmware settings, they may vary slightly
% with other brushless ESCs.
% 
% A single standard T200 (manufactured August 2019) and Basic ESC R3 are
% used for all the following tests.
% 
% The ESC/thruster are powered by a Magna-Power XR series power supply,
% with voltage remote sense probes located at the ESC power input on the
% PCB to eliminate voltage drop between the power supply and ESC.
% 
% The ESC is connected to the thruster via soldered pairs of 4 mm bullet
% connectors on each phase, with the thruster cable being the retail
% standard 1 m long 18 AWG configuration. Longer cables will introduce more
% voltage drop and affect performance.
% 
% Voltage and current draw data was read directly from the power supply
% over serial, with the force measured by a Measurement Specialties
% FC2231-0000-0050-L force sensor. RPM is measured with an Eagle Tree
% Systems Brushless Motor RPM Sensor V2 accross 2 phases.
% 
% RPM is a resultant of the given the load on the thruster by the
% propeller/input voltage at static conditions; the Basic ESC is an open
% loop control system. There is no direct relationship between ESC PWM
% input and RPM.
% 
% Power draw and efficiency are calculated based on the above data.
% *************************************************************************

% *********************** Testing Methodology *****************************
% 
% Using a Blue Robotics testing program, the test is initialized at each
% voltage to command the ESC to run the thruster at steps of 4µs from
% neutral to full throttle.
% 
% The thruster jumps immediately from neutral to the input value, and runs
% for 1.5 seconds with no data collection. This eliminates startup transients.
% 
% The thruster continues to run for 2 more seconds, with data being
% collected at 10hz for a total of 20 data points. The short collection
% time is necessary to reduce the effect of circulating water in the tank
% making inlet velocity non-zero, and thus breaking static conditions.
% 
% The resulting data points are then averaged to generate a final set of
% values for the thruster at that throttle input level.
% 
% The thruster then rests for 30 seconds to allow the water in the test
% tank to come to a rest and re-establish static conditions.
% 
% When the final full throttle input value is achieved, the previous
% procedure is repeated 5 times for the full throttle input with all the
% data averaged. This is an attempt to make the stated full throttle values
% as fair as possible.
% 
% When organizing the collected data, all values below 300 RPM are dropped
% to zero, as rotation below this value is not consistent and results in
% jerky motion and non-constant thrust, power draw, etc.
% *************************************************************************

clear
close all
clc

%% Import data
% Choose among the following strings to fill the variable workingVoltage:
% - '10 V'
% - '12 V'
% - '14 V'
% - '16 V'
% - '18 V'
% - '20 V'
workingVoltage = '12 V';
data = xlsread('T200-Public-Performance-Data-10-20V-September-2019.xlsx', workingVoltage);

pwm = data(:,1);
force = data(:,6);

%% Plot
figure('Name', 'Motor thrust (12V)')
plot(pwm, force, 'r', 'linewidth', 1.2)
title('Motor thrust (12V)')
xlabel('ESC PWM Input Value (\mus)')
ylabel('Thrust (Kg f)')
grid on

%% Interpolation
f = fit(pwm, force, 'poly3');

%% Comparison
figure('Name', 'Fitted line')
plot(f, pwm, force)
title('Fitted line')
xlabel('ESC PWM Input Value (\mus)')
ylabel('Thrust (Kg f)')
grid on