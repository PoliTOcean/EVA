

        /*
    * sim_ROV_v0_R2018b_data.cpp
    *
            * Academic License - for use in teaching, academic research, and meeting
* course requirements at degree granting institutions only.  Not for
* government, commercial, or other organizational use.
        *
    * Code generation for model "sim_ROV_v0_R2018b".
    *
    * Model version              : 10.0
    * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
        * C++ source code generated on : Wed May 10 11:42:16 2023
 * 
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objective: Execution efficiency
 * Validation result: Not run
    */




    
#include "sim_ROV_v0_R2018b.h"


    

    

    

    

    

    

    

    

    

    

            /* Block parameters (default storage) */
                                             P_sim_ROV_v0_R2018b_T sim_ROV_v0_R2018b_P{
                    

                        /* Variable: B
  * Referenced by: '<S24>/Buoyancy'
   */
          168.9282             , 



                    /* Variable: D_linear
  * Referenced by: '<S23>/Linear Damping'
   */
{   9.716, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 20.53, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 68.855, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.07, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.07, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.07 }              , 



                    /* Variable: D_quadratic
  * Referenced by: '<S23>/Quadratic Damping'
   */
{   18.18, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 21.66, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 36.99, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.55, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.55, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.55 }              , 



                    /* Variable: I
  * Referenced by: '<S22>/Inertia Tensor'
   */
{   0.40423, -0.04893, -0.06762, -0.04893, 0.66054, -0.01505, -0.06762, -0.01505, 0.92002 }              , 



                    /* Variable: Kq
  * Referenced by: '<S1>/Gain1'
   */
{   -14.052293786563068, -0.00072436118988949256, 9.1672283370203769E-15, -0.0080218727149945525, -1.5915302957567845, -0.0024038868499794679, -0.0010257341828741554, -14.020998360051747, -2.3537871857545344E-14, 1.8470245233788321, 0.0061160769860095889, 0.0081816219006966475, 1.312127999059641E-13, 4.3251065633191E-14, -14.142135623730917, 8.7974030309777344E-14, -7.3554501098866224E-14, -1.6603800593269574E-13, 0.0079776514809919118, -1.8470197113673619, 4.2499445627750057E-14, -14.020997949871939, 0.0010607205478544892, 0.0083610679725848874, 1.5915300530971268, -0.0061588495863648691, 3.1235423903460053E-15, 0.00065484759548933434, -14.052294848788822, 0.0017923563119103363, 0.0025944480414033131, -0.0092041904488206518, -1.3940929841376514E-13, -0.0072194499584825773, -0.0015062760509905225, -14.142130467591738 }              , 



                    /* Variable: Kx
  * Referenced by: '<S1>/Gain2'
   */
{   30.007712553860511, 0.0015952038328207003, 1.6633897979286147E-14, 0.010172445213118725, 3.5993294581444681, 0.0029316204364070388, 0.001706504234946532, 25.080381809424569, -1.0292145539446683E-14, -3.0689609442341932, -0.0065814194837628525, -0.0083668320327263176, -1.6924508905352756E-13, -1.654614571338528E-13, 21.71078314445942, -1.5055722976581933E-13, 1.8154117783015343E-13, 1.7720870063438595E-13, -0.0094928924725061221, -0.098121701209765072, -3.2385179681946153E-15, 14.947642883684312, -0.0694244900258914, -0.1136802633683934, 0.20572798218430258, 0.00748969202214085, 2.3775065685738575E-15, -0.0691064110433708, 15.53483077367394, -0.025231846431883958, -0.002887440325348308, 0.010363468000498154, 2.0055620609775746E-14, -0.094819534196238273, -0.021154822117581462, 15.88371126898428, 36.181114595141011, 0.0019433793864718722, -6.3795418877651815E-15, 0.015983024464698816, 4.3390650739341279, 0.004713810621133495, 0.002699171207330668, 38.297905593563712, 4.8831742007317758E-15, -4.8565855473540864, -0.011569701336912212, -0.014958093614160478, -5.1001572070754285E-13, -3.9669652191640541E-13, 52.549163655533114, -3.6827651017917089E-13, 3.8431488703248276E-13, 4.5665027389528781E-13, -0.015172085949825319, -2.4825724856282556, -4.652659085305797E-14, 20.825627384885319, -0.039288721417492352, -0.072616903424032084, 3.3427409887804207, 0.011765188878288988, 4.5109101770949335E-15, -0.038383924341199659, 21.258334354423521, -0.015916742044893285, -0.0046691979908373982, 0.016578587521121752, 2.4908103541186421E-13, -0.0444824759342619, -0.010006325675562032, 25.519314618907622 }              , 



                    /* Variable: M_addedMass
  * Referenced by: '<S22>/Added Mass'
   */
{   1.3169, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.5699, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 14.426, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2089, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3637, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1482 }              , 



                    /* Variable: TCM
  * Referenced by: '<S2>/Thrust Configuration Matrix'
   */
{   -0.7071, 0.7071, 0.0, -0.0223, -0.0223, 0.2425, -0.7071, -0.7071, 0.0, 0.0223, -0.0223, -0.2425, 0.7071, 0.7071, 0.0, -0.0223, 0.0223, -0.2425, 0.7071, -0.7071, 0.0, 0.0223, 0.0223, 0.2425, 0.0, 0.0, 1.0, 0.2613, -0.2613, 0.0, 0.0, 0.0, 1.0, -0.2613, -0.2613, 0.0, 0.0, 0.0, 1.0, 0.2613, 0.2613, 0.0, 0.0, 0.0, 1.0, -0.2613, 0.2613, 0.0 }              , 



                        /* Variable: W
  * Referenced by: '<S24>/Gravity Force'
   */
          162.84600000000003             , 



                    /* Variable: force
  * Referenced by:
*   '<S7>/1-D Lookup Table'
*   '<S7>/Saturation'
   */
{   -3.5168499733333336, -3.4971943199999997, -3.4926584, -3.4518351199999997, -3.4019399999999997, -3.3565807999999997, -3.29307792, -3.24771872, -3.1887517599999997, -3.1388566399999998, -3.09803336, -3.0572100799999995, -3.00277904, -2.93927616, -2.8848451199999996, -2.84855776, -2.7805189599999998, -2.76237528, -2.6898005599999997, -2.64444136, -2.5945462399999997, -2.5265074399999996, -2.49022008, -2.45393272, -2.4085735199999996, -2.34960656, -2.3359987999999996, -2.2588881599999997, -2.20445712, -2.1772416, -2.11827464, -2.0547717599999995, -2.02755624, -1.9867329599999999, -1.90962232, -1.8914786399999999, -1.81890392, -1.76447288, -1.71911368, -1.6828263200000002, -1.6329312, -1.57850016, -1.5648924, -1.5195332, -1.47870992, -1.44242256, -1.4015992800000001, -1.36984784, -1.3244886400000002, -1.28366536, -1.23830616, -1.1929469600000002, -1.16573144, -1.12490816, -1.0886208000000002, -1.0523334400000002, -1.0160460800000002, -0.98429464000000011, -0.9525432, -0.91625584, -0.8845044, -0.84821704, -0.80739376, -0.76657047999999994, -0.73935495999999989, -0.7030676, -0.680388, -0.64863655999999992, -0.62142104, -0.58513368, -0.54884632, -0.51709487999999992, -0.48987936000000004, -0.46266384, -0.42637647999999995, -0.39916096, -0.37194543999999996, -0.34926584, -0.3175144, -0.28576296, -0.25854743999999996, -0.23586784, -0.20865231999999997, -0.18597272, -0.16329311999999999, -0.14514943999999996, -0.12246984000000001, -0.09979024, -0.081646559999999993, -0.0680388, -0.0453592, -0.031751440000000006, -0.008, -0.007, -0.006, -0.005, -0.004, -0.003, -0.002, -0.001, 0.0, 0.001, 0.002, 0.003, 0.004, 0.005, 0.006, 0.007, 0.008, 0.045359199999999995, 0.063502880000000012, 0.08164656, 0.09979024, 0.12246983999999998, 0.14514944, 0.17690087999999998, 0.19958048, 0.226796, 0.26308336, 0.29029888, 0.32658623999999997, 0.36287359999999996, 0.39462504, 0.42637647999999995, 0.46266384, 0.49895120000000004, 0.53070264, 0.57606184, 0.62142104, 0.64410064, 0.68945984, 0.7257472, 0.76657047999999994, 0.82553744000000007, 0.84821704, 0.88904032, 0.92079175999999985, 0.96615095999999989, 0.99790240000000008, 1.05233344, 1.09315672, 1.14305184, 1.2020188, 1.2337702400000001, 1.27912944, 1.32448864, 1.36531192, 1.4061352, 1.4605662400000001, 1.51046136, 1.55128464, 1.60571568, 1.6510748800000001, 1.71004184, 1.7599369599999999, 1.8143679999999998, 1.85065536, 1.9096223200000004, 1.96405336, 2.0048766400000004, 2.0865232000000002, 2.1182746400000005, 2.1590979200000002, 2.2452804, 2.26796, 2.34053472, 2.4267172, 2.50382784, 2.5627948000000003, 2.6353695200000002, 2.6580491200000003, 2.75783936, 2.78051896, 2.8803092, 2.9347402400000004, 2.9937072000000002, 3.04813824, 3.1297848, 3.18875176, 3.23411096, 3.32482936, 3.36111672, 3.42008368, 3.4926584, 3.5652331200000003, 3.62420008, 3.68770296, 3.76934952, 3.8373883200000005, 3.9235708000000002, 3.9825377600000005, 4.0278969600000005, 4.10954352, 4.15490272, 4.21386968, 4.30458808, 4.38169872, 4.422522, 4.5087044800000005, 4.52684816, 4.52692421333333 }              , 



                        /* Variable: m
  * Referenced by: '<S22>/Rigid Body Mass'
   */
          16.6             , 



                    /* Variable: pwm
  * Referenced by: '<S7>/1-D Lookup Table'
   */
{   1100.0, 1104.0, 1108.0, 1112.0, 1116.0, 1120.0, 1124.0, 1128.0, 1132.0, 1136.0, 1140.0, 1144.0, 1148.0, 1152.0, 1156.0, 1160.0, 1164.0, 1168.0, 1172.0, 1176.0, 1180.0, 1184.0, 1188.0, 1192.0, 1196.0, 1200.0, 1204.0, 1208.0, 1212.0, 1216.0, 1220.0, 1224.0, 1228.0, 1232.0, 1236.0, 1240.0, 1244.0, 1248.0, 1252.0, 1256.0, 1260.0, 1264.0, 1268.0, 1272.0, 1276.0, 1280.0, 1284.0, 1288.0, 1292.0, 1296.0, 1300.0, 1304.0, 1308.0, 1312.0, 1316.0, 1320.0, 1324.0, 1328.0, 1332.0, 1336.0, 1340.0, 1344.0, 1348.0, 1352.0, 1356.0, 1360.0, 1364.0, 1368.0, 1372.0, 1376.0, 1380.0, 1384.0, 1388.0, 1392.0, 1396.0, 1400.0, 1404.0, 1408.0, 1412.0, 1416.0, 1420.0, 1424.0, 1428.0, 1432.0, 1436.0, 1440.0, 1444.0, 1448.0, 1452.0, 1456.0, 1460.0, 1464.0, 1468.0, 1472.0, 1476.0, 1480.0, 1484.0, 1488.0, 1492.0, 1496.0, 1500.0, 1504.0, 1508.0, 1512.0, 1516.0, 1520.0, 1524.0, 1528.0, 1532.0, 1536.0, 1540.0, 1544.0, 1548.0, 1552.0, 1556.0, 1560.0, 1564.0, 1568.0, 1572.0, 1576.0, 1580.0, 1584.0, 1588.0, 1592.0, 1596.0, 1600.0, 1604.0, 1608.0, 1612.0, 1616.0, 1620.0, 1624.0, 1628.0, 1632.0, 1636.0, 1640.0, 1644.0, 1648.0, 1652.0, 1656.0, 1660.0, 1664.0, 1668.0, 1672.0, 1676.0, 1680.0, 1684.0, 1688.0, 1692.0, 1696.0, 1700.0, 1704.0, 1708.0, 1712.0, 1716.0, 1720.0, 1724.0, 1728.0, 1732.0, 1736.0, 1740.0, 1744.0, 1748.0, 1752.0, 1756.0, 1760.0, 1764.0, 1768.0, 1772.0, 1776.0, 1780.0, 1784.0, 1788.0, 1792.0, 1796.0, 1800.0, 1804.0, 1808.0, 1812.0, 1816.0, 1820.0, 1824.0, 1828.0, 1832.0, 1836.0, 1840.0, 1844.0, 1848.0, 1852.0, 1856.0, 1860.0, 1864.0, 1868.0, 1872.0, 1876.0, 1880.0, 1884.0, 1888.0, 1892.0, 1896.0, 1900.0 }              , 



                    /* Variable: r_b
  * Referenced by: '<S24>/CoB'
   */
{   0.0, 0.0, -0.03 }              , 



                    /* Variable: r_g
  * Referenced by:
*   '<S17>/CoG'
*   '<S22>/CoM'
*   '<S24>/CoM'
   */
{   0.0, 0.0, 0.0 }              , 



                        /* Mask Parameter: Randombias_Ts
  * Referenced by: '<S51>/Constant1'
   */
          0.1             , 



                        /* Mask Parameter: Randombias_Ts_e
  * Referenced by: '<S37>/Constant1'
   */
          0.1             , 



                    /* Mask Parameter: ThreeaxisInertialMeasurementUni
  * Referenced by: '<S34>/Measurement bias'
   */
{   0.0, 0.0, 0.0 }              , 



                    /* Mask Parameter: ThreeaxisAccelerometer_a_pow
  * Referenced by: '<S37>/Constant'
   */
{   1.0E-5, 1.0E-5, 1.0E-5 }              , 



                    /* Mask Parameter: ThreeaxisAccelerometer_a_seeds
  * Referenced by: '<S37>/White Noise'
   */
{   23093.0, 23094.0, 23095.0 }              , 



                    /* Mask Parameter: ThreeaxisInertialMeasurementU_l
  * Referenced by: '<S34>/Scale factors & Cross-coupling  errors'
   */
{   1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 }              , 



                    /* Mask Parameter: ThreeaxisInertialMeasurementU_n
  * Referenced by: '<S35>/Measurement bias'
   */
{   0.0, 0.0, 0.0 }              , 



                    /* Mask Parameter: ThreeaxisGyroscope_g_pow
  * Referenced by: '<S51>/Constant'
   */
{   1.0E-5, 1.0E-5, 1.0E-5 }              , 



                    /* Mask Parameter: ThreeaxisGyroscope_g_seeds
  * Referenced by: '<S51>/White Noise'
   */
{   23096.0, 23097.0, 23098.0 }              , 



                    /* Mask Parameter: ThreeaxisInertialMeasurementU_p
  * Referenced by: '<S35>/g-sensitive bias'
   */
{   0.0, 0.0, 0.0 }              , 



                    /* Mask Parameter: ThreeaxisInertialMeasurementU_m
  * Referenced by: '<S35>/Scale factors & Cross-coupling  errors '
   */
{   1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 }              , 



                    /* Mask Parameter: ThreeaxisInertialMeasurementU_g
  * Referenced by: '<S34>/wl_ins'
   */
{   0.0, 0.0, 0.0 }              , 



                        /* Mask Parameter: ThreeaxisInertialMeasurementU_f
  * Referenced by:
*   '<S41>/2*zeta * wn'
*   '<S41>/wn^2'
   */
          190.0             , 



                        /* Mask Parameter: ThreeaxisInertialMeasurementU_h
  * Referenced by:
*   '<S53>/2*zeta * wn'
*   '<S53>/wn^2'
   */
          190.0             , 



                        /* Mask Parameter: ThreeaxisInertialMeasurement_gc
  * Referenced by: '<S41>/2*zeta * wn'
   */
          0.707             , 



                        /* Mask Parameter: ThreeaxisInertialMeasurementU_o
  * Referenced by: '<S53>/2*zeta * wn'
   */
          0.707             , 



                        /* Expression: pi/180
  * Referenced by: '<S4>/Gain3'
   */
          0.017453292519943295             , 



                        /* Expression: 0
  * Referenced by: '<S30>/Integrator6'
   */
          0.0             , 



                        /* Expression: 0
  * Referenced by: '<S30>/Integrator7'
   */
          0.0             , 



                        /* Expression: 0
  * Referenced by: '<S30>/Integrator8'
   */
          0.0             , 



                        /* Expression: 0
  * Referenced by: '<S30>/Integrator'
   */
          0.0             , 



                        /* Expression: 0
  * Referenced by: '<S30>/Integrator1'
   */
          0.0             , 



                        /* Expression: 0
  * Referenced by: '<S30>/Integrator2'
   */
          0.0             , 



                        /* Expression: 0
  * Referenced by: '<S30>/Integrator3'
   */
          0.0             , 



                        /* Expression: 0
  * Referenced by: '<S30>/Integrator4'
   */
          0.0             , 



                        /* Expression: 0
  * Referenced by: '<S30>/Integrator5'
   */
          0.0             , 



                        /* Expression: 0
  * Referenced by: '<S53>/Integrator, Second-Order Limited'
   */
          0.0             , 



                        /* Expression: 0
  * Referenced by: '<S53>/Integrator, Second-Order Limited'
   */
          0.0             , 



                        /* Expression: dtype_g
  * Referenced by: '<S50>/Constant'
   */
          1.0             , 



                        /* Expression: 0
  * Referenced by: '<S18>/Integrator'
   */
          0.0             , 



                        /* Expression: 1
  * Referenced by: '<S35>/Zero-Order Hold'
   */
          1.0             , 



                    /* Expression: inv(M_rigidBody+M_addedMass)
  * Referenced by: '<S18>/Inverse of total mass'
   */
{   0.055813226618444033, 0.0, 0.0, -0.0, -0.0, -0.0, 0.0, 0.052165113015717343, 0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.032231032037645845, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 1.6490230792016247, 0.080327596243710692, 0.10551746919087987, -0.0, -0.0, -0.0, 0.080327596243710692, 0.98044877000731878, 0.018898266318370618, -0.0, -0.0, -0.0, 0.10551746919087987, 0.018898266318370618, 0.94308242700452971 }              , 



                    /* Computed Parameter: T200TransferFunction1_A
  * Referenced by: '<S20>/T200 Transfer Function 1'
   */
{   -152.9, -30360.0, -2.93E+6, -1.157E+6 }              , 



                    /* Computed Parameter: T200TransferFunction1_C
  * Referenced by: '<S20>/T200 Transfer Function 1'
   */
{   0.0, -107.0, 83580.0, 39890.0 }              , 



                    /* Computed Parameter: T200TransferFunction2_A
  * Referenced by: '<S20>/T200 Transfer Function 2'
   */
{   -152.9, -30360.0, -2.93E+6, -1.157E+6 }              , 



                    /* Computed Parameter: T200TransferFunction2_C
  * Referenced by: '<S20>/T200 Transfer Function 2'
   */
{   0.0, -107.0, 83580.0, 39890.0 }              , 



                    /* Computed Parameter: T200TransferFunction3_A
  * Referenced by: '<S20>/T200 Transfer Function 3'
   */
{   -152.9, -30360.0, -2.93E+6, -1.157E+6 }              , 



                    /* Computed Parameter: T200TransferFunction3_C
  * Referenced by: '<S20>/T200 Transfer Function 3'
   */
{   0.0, -107.0, 83580.0, 39890.0 }              , 



                    /* Computed Parameter: T200TransferFunction4_A
  * Referenced by: '<S20>/T200 Transfer Function 4'
   */
{   -152.9, -30360.0, -2.93E+6, -1.157E+6 }              , 



                    /* Computed Parameter: T200TransferFunction4_C
  * Referenced by: '<S20>/T200 Transfer Function 4'
   */
{   0.0, -107.0, 83580.0, 39890.0 }              , 



                    /* Computed Parameter: T200TransferFunction5_A
  * Referenced by: '<S20>/T200 Transfer Function 5'
   */
{   -152.9, -30360.0, -2.93E+6, -1.157E+6 }              , 



                    /* Computed Parameter: T200TransferFunction5_C
  * Referenced by: '<S20>/T200 Transfer Function 5'
   */
{   0.0, -107.0, 83580.0, 39890.0 }              , 



                    /* Computed Parameter: T200TransferFunction6_A
  * Referenced by: '<S20>/T200 Transfer Function 6'
   */
{   -152.9, -30360.0, -2.93E+6, -1.157E+6 }              , 



                    /* Computed Parameter: T200TransferFunction6_C
  * Referenced by: '<S20>/T200 Transfer Function 6'
   */
{   0.0, -107.0, 83580.0, 39890.0 }              , 



                    /* Computed Parameter: T200TransferFunction7_A
  * Referenced by: '<S20>/T200 Transfer Function 7'
   */
{   -152.9, -30360.0, -2.93E+6, -1.157E+6 }              , 



                    /* Computed Parameter: T200TransferFunction7_C
  * Referenced by: '<S20>/T200 Transfer Function 7'
   */
{   0.0, -107.0, 83580.0, 39890.0 }              , 



                    /* Computed Parameter: T200TransferFunction8_A
  * Referenced by: '<S20>/T200 Transfer Function 8'
   */
{   -152.9, -30360.0, -2.93E+6, -1.157E+6 }              , 



                    /* Computed Parameter: T200TransferFunction8_C
  * Referenced by: '<S20>/T200 Transfer Function 8'
   */
{   0.0, -107.0, 83580.0, 39890.0 }              , 



                        /* Expression: 4.45
  * Referenced by: '<S16>/lbf → N'
   */
          4.45             , 



                        /* Expression: 0
  * Referenced by: '<S19>/Integrator'
   */
          0.0             , 



                        /* Expression: 1
  * Referenced by: '<S35>/Zero-Order Hold1'
   */
          1.0             , 



                        /* Expression: 0.5
  * Referenced by: '<S50>/Switch'
   */
          0.5             , 



                        /* Expression: 0
  * Referenced by: '<S51>/White Noise'
   */
          0.0             , 



                        /* Computed Parameter: WhiteNoise_StdDev
  * Referenced by: '<S51>/White Noise'
   */
          1.0             , 



                    /* Expression: g_sath
  * Referenced by: '<S35>/Saturation'
   */
{   0.0, 0.0, 0.0 }              , 



                    /* Expression: g_satl
  * Referenced by: '<S35>/Saturation'
   */
{   0.0, 0.0, 0.0 }              , 



                        /* Expression: 0
  * Referenced by: '<S1>/Integrator'
   */
          0.0             , 



                    /* Expression: TCM'*inv(TCM*TCM')
  * Referenced by: '<S7>/Control Allocation'
   */
{   -0.35355678121906375, -0.35355678121906375, 0.35355678121906375, 0.35355678121906375, 0.030173426028263, 0.030173426028263, -0.030173426028263, -0.030173426028263, 0.35355678121906375, -0.35355678121906375, 0.35355678121906375, -0.35355678121906375, 0.030173426028263, -0.030173426028263, 0.030173426028263, -0.030173426028263, 0.0, 0.0, 0.0, 0.0, 0.25, 0.25, 0.25, 0.25, 2.1261701675395451E-18, -2.1261701675395451E-18, 2.1261701675395451E-18, -2.1261701675395451E-18, 0.9567546880979716, -0.9567546880979716, 0.9567546880979716, -0.9567546880979716, 2.1261701675395451E-18, 2.1261701675395451E-18, -2.1261701675395451E-18, -2.1261701675395451E-18, -0.9567546880979716, -0.9567546880979716, 0.9567546880979716, 0.9567546880979716, 1.0309278350515465, -1.0309278350515465, -1.0309278350515465, 1.0309278350515465, 0.0, 0.0, 0.0, 0.0 }              , 



                        /* Expression: 1/9.8
  * Referenced by: '<S7>/N → kgf'
   */
          0.1020408163265306             , 



                    /* Expression: [0 0 5 0 0 0]
  * Referenced by: '<S4>/Constant Reference'
   */
{   0.0, 0.0, 5.0, 0.0, 0.0, 0.0 }              , 



                    /* Expression: [1 1 1 pi/180 pi/180 pi/180]
  * Referenced by: '<S4>/Gain'
   */
{   1.0, 1.0, 1.0, 0.017453292519943295, 0.017453292519943295, 0.017453292519943295 }              , 



                        /* Expression: 10
  * Referenced by: '<S4>/Step'
   */
          10.0             , 



                        /* Expression: 0
  * Referenced by: '<S4>/Step'
   */
          0.0             , 



                        /* Expression: 5
  * Referenced by: '<S4>/Step'
   */
          5.0             , 



                        /* Expression: 60
  * Referenced by: '<S4>/Step1'
   */
          60.0             , 



                        /* Expression: 0
  * Referenced by: '<S4>/Step1'
   */
          0.0             , 



                        /* Expression: 5
  * Referenced by: '<S4>/Step1'
   */
          5.0             , 



                        /* Expression: 0
  * Referenced by: '<S4>/Constant'
   */
          0.0             , 



                        /* Expression: pi/180
  * Referenced by: '<S4>/Gain1'
   */
          0.017453292519943295             , 



                        /* Expression: pi/180
  * Referenced by: '<S4>/Gain2'
   */
          0.017453292519943295             , 



                        /* Expression: 10
  * Referenced by: '<S4>/Step2'
   */
          10.0             , 



                        /* Expression: 0
  * Referenced by: '<S4>/Step2'
   */
          0.0             , 



                        /* Expression: 90
  * Referenced by: '<S4>/Step2'
   */
          90.0             , 



                        /* Expression: 60
  * Referenced by: '<S4>/Step3'
   */
          60.0             , 



                        /* Expression: 0
  * Referenced by: '<S4>/Step3'
   */
          0.0             , 



                        /* Expression: 90
  * Referenced by: '<S4>/Step3'
   */
          90.0             , 



                        /* Expression: 1900
  * Referenced by: '<S16>/Saturation'
   */
          1900.0             , 



                        /* Expression: 1100
  * Referenced by: '<S16>/Saturation'
   */
          1100.0             , 



                        /* Expression: -10
  * Referenced by: '<S16>/Dead Zone'
   */
          -10.0             , 



                        /* Expression: +10
  * Referenced by: '<S16>/Dead Zone'
   */
          10.0             , 



                    /* Expression: [0 0 0]
  * Referenced by: '<S17>/Gravity Acceleration'
   */
{   0.0, 0.0, 0.0 }              , 



                        /* Expression: 0
  * Referenced by: '<S41>/Integrator, Second-Order Limited'
   */
          0.0             , 



                        /* Expression: 0
  * Referenced by: '<S41>/Integrator, Second-Order Limited'
   */
          0.0             , 



                        /* Expression: dtype_a
  * Referenced by: '<S36>/Constant'
   */
          1.0             , 



                        /* Expression: 1
  * Referenced by: '<S34>/Zero-Order Hold1'
   */
          1.0             , 



                        /* Expression: 1
  * Referenced by: '<S34>/Zero-Order Hold2'
   */
          1.0             , 



                        /* Expression: 1
  * Referenced by: '<S34>/Zero-Order Hold'
   */
          1.0             , 



                        /* Expression: 1
  * Referenced by: '<S34>/Zero-Order Hold4'
   */
          1.0             , 



                    /* Expression: [1 -1 1]
  * Referenced by: '<S34>/Gain'
   */
{   1.0, -1.0, 1.0 }              , 



                        /* Expression: 1
  * Referenced by: '<S34>/Zero-Order Hold3'
   */
          1.0             , 



                        /* Expression: 0.5
  * Referenced by: '<S36>/Switch'
   */
          0.5             , 



                        /* Expression: 0
  * Referenced by: '<S37>/White Noise'
   */
          0.0             , 



                        /* Computed Parameter: WhiteNoise_StdDev_j
  * Referenced by: '<S37>/White Noise'
   */
          1.0             , 



                    /* Expression: a_sath
  * Referenced by: '<S34>/Saturation'
   */
{   0.0, 0.0, 0.0 }              , 



                    /* Expression: a_satl
  * Referenced by: '<S34>/Saturation'
   */
{   0.0, 0.0, 0.0 }              , 



                        /* Computed Parameter: ManualSwitch_CurrentSetting
  * Referenced by: '<S4>/Manual Switch'
   */
          1U 




                };

        
    



    

    

    

    

    

    

    

    

    
