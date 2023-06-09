close all;
clear all;
clc;

%Read Data
csv_table = readtable("lookup.xlsx");
%Take only pwm and Force_12V_Kgf columns from the table
csv_table = csv_table(:,["Force_12V_Kgf","PWM"]);

%Interval of separation of the three parts 
%   < -eps
%   -eps<= && <=eps
%   > eps
eps = 1e-2;

hold on
%Plot original Data
plot(csv_table.Force_12V_Kgf,csv_table.PWM,"b-")
xline(-eps);
xline(eps)

%Separate the table according to the three intervals of roce prviously
%defined
table_1 = csv_table(csv_table.Force_12V_Kgf<-eps,:);
table_2 = csv_table(csv_table.Force_12V_Kgf>eps,:);
table_center = csv_table(csv_table.Force_12V_Kgf>=-eps & csv_table.Force_12V_Kgf<=eps,:);

%Extract the force from the three tables and generate the matrices for the
%LS interpolation of second order (for the first two intervals):
%theta(1)*f^2 + theta(2)*f + theta(3)
%LS interpolation for the cerntal interval
%theta(1)*f + theta(2)
force_1 = [table_1.Force_12V_Kgf.^2 table_1.Force_12V_Kgf table_1.Force_12V_Kgf.^0];
force_2 = [table_2.Force_12V_Kgf.^2 table_2.Force_12V_Kgf table_2.Force_12V_Kgf.^0];
force_center = [table_center.Force_12V_Kgf table_center.Force_12V_Kgf.^0];

%Obtain theta from LS method
theta_1 = force_1\table_1.PWM
theta_2 = force_2\table_2.PWM
theta_center = force_center\table_center.PWM

%Vector containing the range of forces
force = table2array(csv_table(:,1));

%Vector containg the pwm
pwm = [];

%Generate pwm based on the force and in which interval it belongs to
for f=1:height(csv_table)
    if force(f)<-eps
        pwm(end+1) = force(f)^2*theta_1(1) + force(f)*theta_1(2) + theta_1(3);
    elseif force(f)>eps
        pwm(end+1) = force(f)^2*theta_2(1) + force(f)*theta_2(2) + theta_2(3);
    else
        pwm(end+1) = force(f)*theta_center(1) + theta_center(2);
    end
end

%Plot obtained results
plot(force,pwm,"g-")

%Evaluate interpolation errors
errors = pwm-csv_table.PWM(:)';
max_error = max(errors)
mean_error = mean(errors)

%Plot interpolation errors
for i=1:height(csv_table)
    plot([force(i) force(i)], [pwm(i) csv_table.PWM(i)],"r")
end

hold off