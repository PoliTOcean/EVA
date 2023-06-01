close all;
clear all;
clc;

test1 = readtable("test_down.csv");

figure(1)
hold on
title("Postion (Test Down)")
xlabel("t","Interpreter","latex")
ylabel("z","Interpreter","latex")
plot(test1.Time,test1.Position);
hold off

figure(2)
hold on
title("Force (Test Down)")
xlabel("t","Interpreter","latex")
ylabel("KgF","Interpreter","latex")
plot(test1.Time,test1.Force);
hold off

figure(3)
hold on
title("PWM (Test Down)")
xlabel("t","Interpreter","latex")
ylabel("PWM")
plot(test1.Time,test1.PWM);
hold off

test2 = readtable("test_up.csv");
ref = 0;

figure(4)
hold on
title("Postion (Test Up)")
xlabel("t","Interpreter","latex")
ylabel("z","Interpreter","latex")
plot(test2.Time,test1.Position,"k");
hold off

figure(5)
hold on
title("Force (Test Up)")
xlabel("t","Interpreter","latex")
ylabel("KgF","Interpreter","latex")
plot(test2.Time,test1.Force,"k");
hold off

figure(6)
hold on
title("PWM (Test Up)")
xlabel("t","Interpreter","latex")
ylabel("PWM")
plot(test2.Time,test1.PWM,"k");
hold off
