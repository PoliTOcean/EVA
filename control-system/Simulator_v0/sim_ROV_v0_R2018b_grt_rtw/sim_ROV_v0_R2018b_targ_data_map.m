    function targMap = targDataMap(),

    ;%***********************
    ;% Create Parameter Map *
    ;%***********************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 2;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc paramMap
        ;%
        paramMap.nSections           = nTotSects;
        paramMap.sectIdxOffset       = sectIdxOffset;
            paramMap.sections(nTotSects) = dumSection; %prealloc
        paramMap.nTotData            = -1;

        ;%
        ;% Auto data (sim_ROV_v0_R2018b_P)
        ;%
            section.nData     = 109;
            section.data(109)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_P.B
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_P.D_linear
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% sim_ROV_v0_R2018b_P.D_quadratic
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 37;

                    ;% sim_ROV_v0_R2018b_P.I
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 73;

                    ;% sim_ROV_v0_R2018b_P.Kq
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 82;

                    ;% sim_ROV_v0_R2018b_P.Kx
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 118;

                    ;% sim_ROV_v0_R2018b_P.M_addedMass
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 190;

                    ;% sim_ROV_v0_R2018b_P.TCM
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 226;

                    ;% sim_ROV_v0_R2018b_P.W
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 274;

                    ;% sim_ROV_v0_R2018b_P.force
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 275;

                    ;% sim_ROV_v0_R2018b_P.m
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 476;

                    ;% sim_ROV_v0_R2018b_P.pwm
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 477;

                    ;% sim_ROV_v0_R2018b_P.r_b
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 678;

                    ;% sim_ROV_v0_R2018b_P.r_g
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 681;

                    ;% sim_ROV_v0_R2018b_P.Randombias_Ts
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 684;

                    ;% sim_ROV_v0_R2018b_P.Randombias_Ts_e
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 685;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementUni
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 686;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisAccelerometer_a_pow
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 689;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisAccelerometer_a_seeds
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 692;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_l
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 695;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_n
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 704;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisGyroscope_g_pow
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 707;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisGyroscope_g_seeds
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 710;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_p
                    section.data(24).logicalSrcIdx = 23;
                    section.data(24).dtTransOffset = 713;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_m
                    section.data(25).logicalSrcIdx = 24;
                    section.data(25).dtTransOffset = 716;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_g
                    section.data(26).logicalSrcIdx = 25;
                    section.data(26).dtTransOffset = 725;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_f
                    section.data(27).logicalSrcIdx = 26;
                    section.data(27).dtTransOffset = 728;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_h
                    section.data(28).logicalSrcIdx = 27;
                    section.data(28).dtTransOffset = 729;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurement_gc
                    section.data(29).logicalSrcIdx = 28;
                    section.data(29).dtTransOffset = 730;

                    ;% sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_o
                    section.data(30).logicalSrcIdx = 29;
                    section.data(30).dtTransOffset = 731;

                    ;% sim_ROV_v0_R2018b_P.Gain3_Gain
                    section.data(31).logicalSrcIdx = 30;
                    section.data(31).dtTransOffset = 732;

                    ;% sim_ROV_v0_R2018b_P.Integrator6_IC
                    section.data(32).logicalSrcIdx = 31;
                    section.data(32).dtTransOffset = 733;

                    ;% sim_ROV_v0_R2018b_P.Integrator7_IC
                    section.data(33).logicalSrcIdx = 32;
                    section.data(33).dtTransOffset = 734;

                    ;% sim_ROV_v0_R2018b_P.Integrator8_IC
                    section.data(34).logicalSrcIdx = 33;
                    section.data(34).dtTransOffset = 735;

                    ;% sim_ROV_v0_R2018b_P.Integrator_IC
                    section.data(35).logicalSrcIdx = 34;
                    section.data(35).dtTransOffset = 736;

                    ;% sim_ROV_v0_R2018b_P.Integrator1_IC
                    section.data(36).logicalSrcIdx = 35;
                    section.data(36).dtTransOffset = 737;

                    ;% sim_ROV_v0_R2018b_P.Integrator2_IC
                    section.data(37).logicalSrcIdx = 36;
                    section.data(37).dtTransOffset = 738;

                    ;% sim_ROV_v0_R2018b_P.Integrator3_IC
                    section.data(38).logicalSrcIdx = 37;
                    section.data(38).dtTransOffset = 739;

                    ;% sim_ROV_v0_R2018b_P.Integrator4_IC
                    section.data(39).logicalSrcIdx = 38;
                    section.data(39).dtTransOffset = 740;

                    ;% sim_ROV_v0_R2018b_P.Integrator5_IC
                    section.data(40).logicalSrcIdx = 39;
                    section.data(40).dtTransOffset = 741;

                    ;% sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited_IC
                    section.data(41).logicalSrcIdx = 40;
                    section.data(41).dtTransOffset = 742;

                    ;% sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited__c
                    section.data(42).logicalSrcIdx = 41;
                    section.data(42).dtTransOffset = 743;

                    ;% sim_ROV_v0_R2018b_P.Constant_Value
                    section.data(43).logicalSrcIdx = 42;
                    section.data(43).dtTransOffset = 744;

                    ;% sim_ROV_v0_R2018b_P.Integrator_IC_m
                    section.data(44).logicalSrcIdx = 43;
                    section.data(44).dtTransOffset = 745;

                    ;% sim_ROV_v0_R2018b_P.ZeroOrderHold_Gain
                    section.data(45).logicalSrcIdx = 44;
                    section.data(45).dtTransOffset = 746;

                    ;% sim_ROV_v0_R2018b_P.Inverseoftotalmass_Value
                    section.data(46).logicalSrcIdx = 45;
                    section.data(46).dtTransOffset = 747;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction1_A
                    section.data(47).logicalSrcIdx = 46;
                    section.data(47).dtTransOffset = 783;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction1_C
                    section.data(48).logicalSrcIdx = 47;
                    section.data(48).dtTransOffset = 787;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction2_A
                    section.data(49).logicalSrcIdx = 48;
                    section.data(49).dtTransOffset = 791;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction2_C
                    section.data(50).logicalSrcIdx = 49;
                    section.data(50).dtTransOffset = 795;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction3_A
                    section.data(51).logicalSrcIdx = 50;
                    section.data(51).dtTransOffset = 799;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction3_C
                    section.data(52).logicalSrcIdx = 51;
                    section.data(52).dtTransOffset = 803;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction4_A
                    section.data(53).logicalSrcIdx = 52;
                    section.data(53).dtTransOffset = 807;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction4_C
                    section.data(54).logicalSrcIdx = 53;
                    section.data(54).dtTransOffset = 811;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction5_A
                    section.data(55).logicalSrcIdx = 54;
                    section.data(55).dtTransOffset = 815;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction5_C
                    section.data(56).logicalSrcIdx = 55;
                    section.data(56).dtTransOffset = 819;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction6_A
                    section.data(57).logicalSrcIdx = 56;
                    section.data(57).dtTransOffset = 823;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction6_C
                    section.data(58).logicalSrcIdx = 57;
                    section.data(58).dtTransOffset = 827;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction7_A
                    section.data(59).logicalSrcIdx = 58;
                    section.data(59).dtTransOffset = 831;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction7_C
                    section.data(60).logicalSrcIdx = 59;
                    section.data(60).dtTransOffset = 835;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction8_A
                    section.data(61).logicalSrcIdx = 60;
                    section.data(61).dtTransOffset = 839;

                    ;% sim_ROV_v0_R2018b_P.T200TransferFunction8_C
                    section.data(62).logicalSrcIdx = 61;
                    section.data(62).dtTransOffset = 843;

                    ;% sim_ROV_v0_R2018b_P.lbfN_Gain
                    section.data(63).logicalSrcIdx = 62;
                    section.data(63).dtTransOffset = 847;

                    ;% sim_ROV_v0_R2018b_P.Integrator_IC_j
                    section.data(64).logicalSrcIdx = 63;
                    section.data(64).dtTransOffset = 848;

                    ;% sim_ROV_v0_R2018b_P.ZeroOrderHold1_Gain
                    section.data(65).logicalSrcIdx = 64;
                    section.data(65).dtTransOffset = 849;

                    ;% sim_ROV_v0_R2018b_P.Switch_Threshold
                    section.data(66).logicalSrcIdx = 65;
                    section.data(66).dtTransOffset = 850;

                    ;% sim_ROV_v0_R2018b_P.WhiteNoise_Mean
                    section.data(67).logicalSrcIdx = 66;
                    section.data(67).dtTransOffset = 851;

                    ;% sim_ROV_v0_R2018b_P.WhiteNoise_StdDev
                    section.data(68).logicalSrcIdx = 67;
                    section.data(68).dtTransOffset = 852;

                    ;% sim_ROV_v0_R2018b_P.Saturation_UpperSat
                    section.data(69).logicalSrcIdx = 68;
                    section.data(69).dtTransOffset = 853;

                    ;% sim_ROV_v0_R2018b_P.Saturation_LowerSat
                    section.data(70).logicalSrcIdx = 69;
                    section.data(70).dtTransOffset = 856;

                    ;% sim_ROV_v0_R2018b_P.Integrator_IC_a
                    section.data(71).logicalSrcIdx = 70;
                    section.data(71).dtTransOffset = 859;

                    ;% sim_ROV_v0_R2018b_P.ControlAllocation_Gain
                    section.data(72).logicalSrcIdx = 71;
                    section.data(72).dtTransOffset = 860;

                    ;% sim_ROV_v0_R2018b_P.Nkgf_Gain
                    section.data(73).logicalSrcIdx = 72;
                    section.data(73).dtTransOffset = 908;

                    ;% sim_ROV_v0_R2018b_P.ConstantReference_Value
                    section.data(74).logicalSrcIdx = 73;
                    section.data(74).dtTransOffset = 909;

                    ;% sim_ROV_v0_R2018b_P.Gain_Gain
                    section.data(75).logicalSrcIdx = 74;
                    section.data(75).dtTransOffset = 915;

                    ;% sim_ROV_v0_R2018b_P.Step_Time
                    section.data(76).logicalSrcIdx = 75;
                    section.data(76).dtTransOffset = 921;

                    ;% sim_ROV_v0_R2018b_P.Step_Y0
                    section.data(77).logicalSrcIdx = 76;
                    section.data(77).dtTransOffset = 922;

                    ;% sim_ROV_v0_R2018b_P.Step_YFinal
                    section.data(78).logicalSrcIdx = 77;
                    section.data(78).dtTransOffset = 923;

                    ;% sim_ROV_v0_R2018b_P.Step1_Time
                    section.data(79).logicalSrcIdx = 78;
                    section.data(79).dtTransOffset = 924;

                    ;% sim_ROV_v0_R2018b_P.Step1_Y0
                    section.data(80).logicalSrcIdx = 79;
                    section.data(80).dtTransOffset = 925;

                    ;% sim_ROV_v0_R2018b_P.Step1_YFinal
                    section.data(81).logicalSrcIdx = 80;
                    section.data(81).dtTransOffset = 926;

                    ;% sim_ROV_v0_R2018b_P.Constant_Value_c
                    section.data(82).logicalSrcIdx = 81;
                    section.data(82).dtTransOffset = 927;

                    ;% sim_ROV_v0_R2018b_P.Gain1_Gain
                    section.data(83).logicalSrcIdx = 82;
                    section.data(83).dtTransOffset = 928;

                    ;% sim_ROV_v0_R2018b_P.Gain2_Gain
                    section.data(84).logicalSrcIdx = 83;
                    section.data(84).dtTransOffset = 929;

                    ;% sim_ROV_v0_R2018b_P.Step2_Time
                    section.data(85).logicalSrcIdx = 84;
                    section.data(85).dtTransOffset = 930;

                    ;% sim_ROV_v0_R2018b_P.Step2_Y0
                    section.data(86).logicalSrcIdx = 85;
                    section.data(86).dtTransOffset = 931;

                    ;% sim_ROV_v0_R2018b_P.Step2_YFinal
                    section.data(87).logicalSrcIdx = 86;
                    section.data(87).dtTransOffset = 932;

                    ;% sim_ROV_v0_R2018b_P.Step3_Time
                    section.data(88).logicalSrcIdx = 87;
                    section.data(88).dtTransOffset = 933;

                    ;% sim_ROV_v0_R2018b_P.Step3_Y0
                    section.data(89).logicalSrcIdx = 88;
                    section.data(89).dtTransOffset = 934;

                    ;% sim_ROV_v0_R2018b_P.Step3_YFinal
                    section.data(90).logicalSrcIdx = 89;
                    section.data(90).dtTransOffset = 935;

                    ;% sim_ROV_v0_R2018b_P.Saturation_UpperSat_f
                    section.data(91).logicalSrcIdx = 90;
                    section.data(91).dtTransOffset = 936;

                    ;% sim_ROV_v0_R2018b_P.Saturation_LowerSat_p
                    section.data(92).logicalSrcIdx = 91;
                    section.data(92).dtTransOffset = 937;

                    ;% sim_ROV_v0_R2018b_P.DeadZone_Start
                    section.data(93).logicalSrcIdx = 92;
                    section.data(93).dtTransOffset = 938;

                    ;% sim_ROV_v0_R2018b_P.DeadZone_End
                    section.data(94).logicalSrcIdx = 93;
                    section.data(94).dtTransOffset = 939;

                    ;% sim_ROV_v0_R2018b_P.GravityAcceleration_Value
                    section.data(95).logicalSrcIdx = 94;
                    section.data(95).dtTransOffset = 940;

                    ;% sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited__j
                    section.data(96).logicalSrcIdx = 95;
                    section.data(96).dtTransOffset = 943;

                    ;% sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited__e
                    section.data(97).logicalSrcIdx = 96;
                    section.data(97).dtTransOffset = 944;

                    ;% sim_ROV_v0_R2018b_P.Constant_Value_b
                    section.data(98).logicalSrcIdx = 97;
                    section.data(98).dtTransOffset = 945;

                    ;% sim_ROV_v0_R2018b_P.ZeroOrderHold1_Gain_m
                    section.data(99).logicalSrcIdx = 98;
                    section.data(99).dtTransOffset = 946;

                    ;% sim_ROV_v0_R2018b_P.ZeroOrderHold2_Gain
                    section.data(100).logicalSrcIdx = 99;
                    section.data(100).dtTransOffset = 947;

                    ;% sim_ROV_v0_R2018b_P.ZeroOrderHold_Gain_a
                    section.data(101).logicalSrcIdx = 100;
                    section.data(101).dtTransOffset = 948;

                    ;% sim_ROV_v0_R2018b_P.ZeroOrderHold4_Gain
                    section.data(102).logicalSrcIdx = 101;
                    section.data(102).dtTransOffset = 949;

                    ;% sim_ROV_v0_R2018b_P.Gain_Gain_f
                    section.data(103).logicalSrcIdx = 102;
                    section.data(103).dtTransOffset = 950;

                    ;% sim_ROV_v0_R2018b_P.ZeroOrderHold3_Gain
                    section.data(104).logicalSrcIdx = 103;
                    section.data(104).dtTransOffset = 953;

                    ;% sim_ROV_v0_R2018b_P.Switch_Threshold_j
                    section.data(105).logicalSrcIdx = 104;
                    section.data(105).dtTransOffset = 954;

                    ;% sim_ROV_v0_R2018b_P.WhiteNoise_Mean_g
                    section.data(106).logicalSrcIdx = 105;
                    section.data(106).dtTransOffset = 955;

                    ;% sim_ROV_v0_R2018b_P.WhiteNoise_StdDev_j
                    section.data(107).logicalSrcIdx = 106;
                    section.data(107).dtTransOffset = 956;

                    ;% sim_ROV_v0_R2018b_P.Saturation_UpperSat_e
                    section.data(108).logicalSrcIdx = 107;
                    section.data(108).dtTransOffset = 957;

                    ;% sim_ROV_v0_R2018b_P.Saturation_LowerSat_a
                    section.data(109).logicalSrcIdx = 108;
                    section.data(109).dtTransOffset = 960;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_P.ManualSwitch_CurrentSetting
                    section.data(1).logicalSrcIdx = 109;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            paramMap.sections(2) = section;
            clear section


            ;%
            ;% Non-auto Data (parameter)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        paramMap.nTotData = nTotData;



    ;%**************************
    ;% Create Block Output Map *
    ;%**************************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 7;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc sigMap
        ;%
        sigMap.nSections           = nTotSects;
        sigMap.sectIdxOffset       = sectIdxOffset;
            sigMap.sections(nTotSects) = dumSection; %prealloc
        sigMap.nTotData            = -1;

        ;%
        ;% Auto data (sim_ROV_v0_R2018b_B)
        ;%
            section.nData     = 31;
            section.data(31)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_B.Integrator6
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_B.Integrator7
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% sim_ROV_v0_R2018b_B.Integrator8
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% sim_ROV_v0_R2018b_B.Integrator
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% sim_ROV_v0_R2018b_B.Integrator1
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% sim_ROV_v0_R2018b_B.Integrator2
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 5;

                    ;% sim_ROV_v0_R2018b_B.Integrator3
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 6;

                    ;% sim_ROV_v0_R2018b_B.Integrator4
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 7;

                    ;% sim_ROV_v0_R2018b_B.Integrator5
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 8;

                    ;% sim_ROV_v0_R2018b_B.ThrustN
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 9;

                    ;% sim_ROV_v0_R2018b_B.ForcesMoments
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 17;

                    ;% sim_ROV_v0_R2018b_B.Pose
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 23;

                    ;% sim_ROV_v0_R2018b_B.Sum
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 29;

                    ;% sim_ROV_v0_R2018b_B.Add
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 35;

                    ;% sim_ROV_v0_R2018b_B.BodyAcceleration
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 41;

                    ;% sim_ROV_v0_R2018b_B.Product
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 47;

                    ;% sim_ROV_v0_R2018b_B.Saturation
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 50;

                    ;% sim_ROV_v0_R2018b_B.Acceleration
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 53;

                    ;% sim_ROV_v0_R2018b_B.Gain
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 59;

                    ;% sim_ROV_v0_R2018b_B.Gain1
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 65;

                    ;% sim_ROV_v0_R2018b_B.Gain2
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 66;

                    ;% sim_ROV_v0_R2018b_B.TmpSignalConversionAtIntegrator
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 67;

                    ;% sim_ROV_v0_R2018b_B.DeadZone
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 73;

                    ;% sim_ROV_v0_R2018b_B.ZeroOrderHold2
                    section.data(24).logicalSrcIdx = 23;
                    section.data(24).dtTransOffset = 81;

                    ;% sim_ROV_v0_R2018b_B.Gain_n
                    section.data(25).logicalSrcIdx = 24;
                    section.data(25).dtTransOffset = 84;

                    ;% sim_ROV_v0_R2018b_B.Product_i
                    section.data(26).logicalSrcIdx = 25;
                    section.data(26).dtTransOffset = 87;

                    ;% sim_ROV_v0_R2018b_B.Saturation_m
                    section.data(27).logicalSrcIdx = 26;
                    section.data(27).dtTransOffset = 90;

                    ;% sim_ROV_v0_R2018b_B.Sum2
                    section.data(28).logicalSrcIdx = 27;
                    section.data(28).dtTransOffset = 93;

                    ;% sim_ROV_v0_R2018b_B.Sum2_c
                    section.data(29).logicalSrcIdx = 28;
                    section.data(29).dtTransOffset = 96;

                    ;% sim_ROV_v0_R2018b_B.eta_dot
                    section.data(30).logicalSrcIdx = 29;
                    section.data(30).dtTransOffset = 99;

                    ;% sim_ROV_v0_R2018b_B.F_g
                    section.data(31).logicalSrcIdx = 30;
                    section.data(31).dtTransOffset = 105;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_B.LowpassFilter5.LowpassFilter3
                    section.data(1).logicalSrcIdx = 34;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(2) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_B.LowpassFilter4.LowpassFilter3
                    section.data(1).logicalSrcIdx = 35;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(3) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_B.LowpassFilter3.LowpassFilter3
                    section.data(1).logicalSrcIdx = 36;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(4) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_B.LowpassFilter2.LowpassFilter
                    section.data(1).logicalSrcIdx = 37;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(5) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_B.LowpassFilter1.LowpassFilter
                    section.data(1).logicalSrcIdx = 38;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(6) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_B.LowpassFilter.LowpassFilter
                    section.data(1).logicalSrcIdx = 39;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(7) = section;
            clear section


            ;%
            ;% Non-auto Data (signal)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        sigMap.nTotData = nTotData;



    ;%*******************
    ;% Create DWork Map *
    ;%*******************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 19;
        sectIdxOffset = 7;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc dworkMap
        ;%
        dworkMap.nSections           = nTotSects;
        dworkMap.sectIdxOffset       = sectIdxOffset;
            dworkMap.sections(nTotSects) = dumSection; %prealloc
        dworkMap.nTotData            = -1;

        ;%
        ;% Auto data (sim_ROV_v0_R2018b_DW)
        ;%
            section.nData     = 6;
            section.data(6)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.NextOutput
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_DW.TimeStampA
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 3;

                    ;% sim_ROV_v0_R2018b_DW.LastUAtTimeA
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 4;

                    ;% sim_ROV_v0_R2018b_DW.TimeStampB
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 10;

                    ;% sim_ROV_v0_R2018b_DW.LastUAtTimeB
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 11;

                    ;% sim_ROV_v0_R2018b_DW.NextOutput_p
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 17;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 7;
            section.data(7)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.Scope_PWORK.LoggedData
                    section.data(1).logicalSrcIdx = 6;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_DW.VisualizationKinematics_PWORK.LoggedData
                    section.data(2).logicalSrcIdx = 7;
                    section.data(2).dtTransOffset = 1;

                    ;% sim_ROV_v0_R2018b_DW.VisualizationPropulsion_PWORK.LoggedData
                    section.data(3).logicalSrcIdx = 8;
                    section.data(3).dtTransOffset = 7;

                    ;% sim_ROV_v0_R2018b_DW.Scope_PWORK_i.LoggedData
                    section.data(4).logicalSrcIdx = 9;
                    section.data(4).dtTransOffset = 9;

                    ;% sim_ROV_v0_R2018b_DW.Scope1_PWORK.LoggedData
                    section.data(5).logicalSrcIdx = 10;
                    section.data(5).dtTransOffset = 10;

                    ;% sim_ROV_v0_R2018b_DW.Scope2_PWORK.LoggedData
                    section.data(6).logicalSrcIdx = 11;
                    section.data(6).dtTransOffset = 11;

                    ;% sim_ROV_v0_R2018b_DW.Scope3_PWORK.LoggedData
                    section.data(7).logicalSrcIdx = 12;
                    section.data(7).dtTransOffset = 12;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
            clear section

            section.nData     = 5;
            section.data(5)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.sfEvent
                    section.data(1).logicalSrcIdx = 13;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_DW.sfEvent_o
                    section.data(2).logicalSrcIdx = 14;
                    section.data(2).dtTransOffset = 1;

                    ;% sim_ROV_v0_R2018b_DW.sfEvent_ou
                    section.data(3).logicalSrcIdx = 15;
                    section.data(3).dtTransOffset = 2;

                    ;% sim_ROV_v0_R2018b_DW.sfEvent_i
                    section.data(4).logicalSrcIdx = 16;
                    section.data(4).dtTransOffset = 3;

                    ;% sim_ROV_v0_R2018b_DW.sfEvent_c
                    section.data(5).logicalSrcIdx = 17;
                    section.data(5).dtTransOffset = 4;

            nTotData = nTotData + section.nData;
            dworkMap.sections(3) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.RandSeed
                    section.data(1).logicalSrcIdx = 18;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_DW.RandSeed_l
                    section.data(2).logicalSrcIdx = 19;
                    section.data(2).dtTransOffset = 3;

            nTotData = nTotData + section.nData;
            dworkMap.sections(4) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited_MO
                    section.data(1).logicalSrcIdx = 20;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited__o
                    section.data(2).logicalSrcIdx = 21;
                    section.data(2).dtTransOffset = 3;

            nTotData = nTotData + section.nData;
            dworkMap.sections(5) = section;
            clear section

            section.nData     = 5;
            section.data(5)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.is_active_c3_sim_ROV_v0_R2018b
                    section.data(1).logicalSrcIdx = 22;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_DW.is_active_c1_sim_ROV_v0_R2018b
                    section.data(2).logicalSrcIdx = 23;
                    section.data(2).dtTransOffset = 1;

                    ;% sim_ROV_v0_R2018b_DW.is_active_c2_sim_ROV_v0_R2018b
                    section.data(3).logicalSrcIdx = 24;
                    section.data(3).dtTransOffset = 2;

                    ;% sim_ROV_v0_R2018b_DW.is_active_c4_sim_ROV_v0_R2018b
                    section.data(4).logicalSrcIdx = 25;
                    section.data(4).dtTransOffset = 3;

                    ;% sim_ROV_v0_R2018b_DW.is_active_c6_sim_ROV_v0_R2018b
                    section.data(5).logicalSrcIdx = 26;
                    section.data(5).dtTransOffset = 4;

            nTotData = nTotData + section.nData;
            dworkMap.sections(6) = section;
            clear section

            section.nData     = 7;
            section.data(7)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited_DW
                    section.data(1).logicalSrcIdx = 27;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited__i
                    section.data(2).logicalSrcIdx = 28;
                    section.data(2).dtTransOffset = 1;

                    ;% sim_ROV_v0_R2018b_DW.doneDoubleBufferReInit
                    section.data(3).logicalSrcIdx = 29;
                    section.data(3).dtTransOffset = 2;

                    ;% sim_ROV_v0_R2018b_DW.doneDoubleBufferReInit_e
                    section.data(4).logicalSrcIdx = 30;
                    section.data(4).dtTransOffset = 3;

                    ;% sim_ROV_v0_R2018b_DW.doneDoubleBufferReInit_n
                    section.data(5).logicalSrcIdx = 31;
                    section.data(5).dtTransOffset = 4;

                    ;% sim_ROV_v0_R2018b_DW.doneDoubleBufferReInit_b
                    section.data(6).logicalSrcIdx = 32;
                    section.data(6).dtTransOffset = 5;

                    ;% sim_ROV_v0_R2018b_DW.doneDoubleBufferReInit_a
                    section.data(7).logicalSrcIdx = 33;
                    section.data(7).dtTransOffset = 6;

            nTotData = nTotData + section.nData;
            dworkMap.sections(7) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter5.obj
                    section.data(1).logicalSrcIdx = 34;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(8) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter5.objisempty
                    section.data(1).logicalSrcIdx = 35;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter5.isInitialized
                    section.data(2).logicalSrcIdx = 36;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            dworkMap.sections(9) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter4.obj
                    section.data(1).logicalSrcIdx = 37;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(10) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter4.objisempty
                    section.data(1).logicalSrcIdx = 38;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter4.isInitialized
                    section.data(2).logicalSrcIdx = 39;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            dworkMap.sections(11) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter3.obj
                    section.data(1).logicalSrcIdx = 40;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(12) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter3.objisempty
                    section.data(1).logicalSrcIdx = 41;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter3.isInitialized
                    section.data(2).logicalSrcIdx = 42;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            dworkMap.sections(13) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter2.obj
                    section.data(1).logicalSrcIdx = 43;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(14) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter2.objisempty
                    section.data(1).logicalSrcIdx = 44;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter2.isInitialized
                    section.data(2).logicalSrcIdx = 45;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            dworkMap.sections(15) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter1.obj
                    section.data(1).logicalSrcIdx = 46;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(16) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter1.objisempty
                    section.data(1).logicalSrcIdx = 47;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter1.isInitialized
                    section.data(2).logicalSrcIdx = 48;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            dworkMap.sections(17) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter.obj
                    section.data(1).logicalSrcIdx = 49;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(18) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter.objisempty
                    section.data(1).logicalSrcIdx = 50;
                    section.data(1).dtTransOffset = 0;

                    ;% sim_ROV_v0_R2018b_DW.LowpassFilter.isInitialized
                    section.data(2).logicalSrcIdx = 51;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            dworkMap.sections(19) = section;
            clear section


            ;%
            ;% Non-auto Data (dwork)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        dworkMap.nTotData = nTotData;



    ;%
    ;% Add individual maps to base struct.
    ;%

    targMap.paramMap  = paramMap;
    targMap.signalMap = sigMap;
    targMap.dworkMap  = dworkMap;

    ;%
    ;% Add checksums to base struct.
    ;%


    targMap.checksum0 = 1276681435;
    targMap.checksum1 = 2568100812;
    targMap.checksum2 = 462248302;
    targMap.checksum3 = 1687718604;

