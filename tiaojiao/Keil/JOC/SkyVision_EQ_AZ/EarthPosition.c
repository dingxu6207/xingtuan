#include <stdio.h>
#include "math.h"

/**************************************************************************************
 *EarthPosition.c
 *
 *Idea:Calculate the heliocentric coordinate of Earth, and then using them to calculate the
 *	   other planet's ra&dec value.
 *
 *Input: The Julian time from epoch J2000.0
 *Output:The L,B,R value of Earth of current Julian time.
 *
 *Usage: You can use this program by call the three function defined here, and you can
 *		 get the L,B,R value of Earth. Now it is just called by planet.c.
 *
 *1		2008-7-18	wcj.		Original version. Tested on the enviroment of Turbo C,
 *								compiling smoothly here but needed to be tested.
 **************************************************************************************/

/*************************************************************************
 *Method: getLofEarth
 *Func: Calculate the L value of earth using the julian time t.
 *Params:double --- the julian time from epoch 2000.0.
 *Return:double --- the L value of earth.
 *************************************************************************/
double getLofEarth(double t){
	int i,j;
	double earth_L0_A[64],earth_L0_B[64],earth_L0_C[64];
	double earth_L1_A[34],earth_L1_B[34],earth_L1_C[34];
	double earth_L2_A[20],earth_L2_B[20],earth_L2_C[20];
	double earth_L3_A[7],earth_L3_B[7],earth_L3_C[7];
	double earth_L4_A[3],earth_L4_B[3],earth_L4_C[3];
	double earth_L5_A[1],earth_L5_B[1],earth_L5_C[1];
	
	double L0_term[64],L1_term[34],L2_term[20],L3_term[7],L4_term[3],L5_term[1];
	double L0_sum = 0.0;
	double L1_sum = 0.0;
	double L2_sum = 0.0;
	double L3_sum = 0.0;
	double L4_sum = 0.0;
	double L5_sum = 0.0;
	double L = 0.0;
	/*L0*/
	earth_L0_A[0] = 175347046;
	earth_L0_A[1] = 3341656;
	earth_L0_A[2] = 34894;
	earth_L0_A[3] = 3497;
	earth_L0_A[4] = 3418;
	earth_L0_A[5] = 3136;
	earth_L0_A[6] = 2676;
	earth_L0_A[7] = 2343;
	earth_L0_A[8] = 1324;
	earth_L0_A[9] = 1273;
	earth_L0_A[10] = 1199;
	earth_L0_A[11] = 990;
	earth_L0_A[12] = 902;
	earth_L0_A[13] = 857;
	earth_L0_A[14] = 780;
	earth_L0_A[15] = 753;
	earth_L0_A[16] = 505;
	earth_L0_A[17] = 492;
	earth_L0_A[18] = 357;
	earth_L0_A[19] = 317;
	earth_L0_A[20] = 284;
	earth_L0_A[21] = 271;
	earth_L0_A[22] = 243;
	earth_L0_A[23] = 206;
	earth_L0_A[24] = 205;
	earth_L0_A[25] = 202;
	earth_L0_A[26] = 156;
	earth_L0_A[27] = 132;
	earth_L0_A[28] = 126;
	earth_L0_A[29] = 115;
	earth_L0_A[30] = 103;
	earth_L0_A[31] = 102;
	earth_L0_A[32] = 102;
	earth_L0_A[33] = 99;
	earth_L0_A[34] = 98;
	earth_L0_A[35] = 86;
	earth_L0_A[36] = 85;
	earth_L0_A[37] = 85;
	earth_L0_A[38] = 80;
	earth_L0_A[39] = 79;
	earth_L0_A[40] = 75;
	earth_L0_A[41] = 74;
	earth_L0_A[42] = 74;
	earth_L0_A[43] = 70;
	earth_L0_A[44] = 62;
	earth_L0_A[45] = 61;
	earth_L0_A[46] = 57;
	earth_L0_A[47] = 56;
	earth_L0_A[48] = 56;
	earth_L0_A[49] = 52;
	earth_L0_A[50] = 52;
	earth_L0_A[51] = 51;
	earth_L0_A[52] = 49;
	earth_L0_A[53] = 41;
	earth_L0_A[54] = 41;
	earth_L0_A[55] = 39;
	earth_L0_A[56] = 37;
	earth_L0_A[57] = 37;
	earth_L0_A[58] = 36;
	earth_L0_A[59] = 36;
	earth_L0_A[60] = 33;
	earth_L0_A[61] = 30;
	earth_L0_A[62] = 30;
	earth_L0_A[63] = 25;
	earth_L0_B[0] = 0;
	earth_L0_B[1] = 4.6692568;
	earth_L0_B[2] = 4.62610;
	earth_L0_B[3] = 2.7441;
	earth_L0_B[4] = 2.8289;
	earth_L0_B[5] = 3.6277;
	earth_L0_B[6] = 4.4181;
	earth_L0_B[7] = 6.1352;
	earth_L0_B[8] = 0.7425;
	earth_L0_B[9] = 2.0371;
	earth_L0_B[10] = 1.1096;
	earth_L0_B[11] = 5.233;
	earth_L0_B[12] = 2.045;
	earth_L0_B[13] = 3.508;
	earth_L0_B[14] = 1.179;
	earth_L0_B[15] = 2.533;
	earth_L0_B[16] = 4.583;
	earth_L0_B[17] = 4.205;
	earth_L0_B[18] = 2.920;
	earth_L0_B[19] = 5.849;
	earth_L0_B[20] = 1.899;
	earth_L0_B[21] = 0.315;
	earth_L0_B[22] = 0.345;
	earth_L0_B[23] = 4.806;
	earth_L0_B[24] = 1.869;
	earth_L0_B[25] = 2.458;
	earth_L0_B[26] = 0.833;
	earth_L0_B[27] = 3.411;
	earth_L0_B[28] = 1.083;
	earth_L0_B[29] = 0.645;
	earth_L0_B[30] = 0.636;
	earth_L0_B[31] = 0.976;
	earth_L0_B[32] = 4.267;
	earth_L0_B[33] = 6.21;
	earth_L0_B[34] = 0.68; 
	earth_L0_B[35] = 5.98;
	earth_L0_B[36] = 1.30;
	earth_L0_B[37] = 3.67;
	earth_L0_B[38] = 1.81;
	earth_L0_B[39] = 3.04;
	earth_L0_B[40] = 1.76;
	earth_L0_B[41] = 3.50;
	earth_L0_B[42] = 4.68;
	earth_L0_B[43] = 0.83;
	earth_L0_B[44] = 3.98;
	earth_L0_B[45] = 1.82;
	earth_L0_B[46] = 2.78;
	earth_L0_B[47] = 4.39;
	earth_L0_B[48] = 3.47;
	earth_L0_B[49] = 0.19;
	earth_L0_B[50] = 1.33;
	earth_L0_B[51] = 0.28;
	earth_L0_B[52] = 0.49;
	earth_L0_B[53] = 5.37;
	earth_L0_B[54] = 2.40;
	earth_L0_B[55] = 6.17;
	earth_L0_B[56] = 6.04;
	earth_L0_B[57] = 2.57;
	earth_L0_B[58] = 1.71;
	earth_L0_B[59] = 1.78;
	earth_L0_B[60] = 0.59;
	earth_L0_B[61] = 0.44;
	earth_L0_B[62] = 2.74;
	earth_L0_B[63] = 3.16;
	earth_L0_C[0] = 0;
	earth_L0_C[1] = 6283.07585;
	earth_L0_C[2] = 12566.15170;
	earth_L0_C[3] = 5753.3849;
	earth_L0_C[4] = 3.5231;
	earth_L0_C[5] = 77713.7715;
	earth_L0_C[6] = 7860.4194;
	earth_L0_C[7] = 3930.2097;
	earth_L0_C[8] = 11506.7698;
	earth_L0_C[9] = 529.6910;
	earth_L0_C[10] = 1577.3435;
	earth_L0_C[11] = 5884.927;
	earth_L0_C[12] = 26.298;
	earth_L0_C[13] = 398.149;
	earth_L0_C[14] = 5223.694;
	earth_L0_C[15] = 5507.553;
	earth_L0_C[16] = 18849.228;
	earth_L0_C[17] = 775.523;
	earth_L0_C[18] = 0.067;
	earth_L0_C[19] = 11790.629;
	earth_L0_C[20] = 796.298;
	earth_L0_C[21] = 10977.079;
	earth_L0_C[22] = 5486.778;
	earth_L0_C[23] = 2544.314;
	earth_L0_C[24] = 5573.143;
	earth_L0_C[25] = 6069.777;
	earth_L0_C[26] = 213.299;
	earth_L0_C[27] = 2942.463;
	earth_L0_C[28] = 20.775;
	earth_L0_C[29] = 0.980;
	earth_L0_C[30] = 4694.003;
	earth_L0_C[31] = 15720.839;
	earth_L0_C[32] = 7.114;
	earth_L0_C[33] = 2146.17;
	earth_L0_C[34] = 155.42;
	earth_L0_C[35] = 161000.69;
	earth_L0_C[36] = 6275.96;
	earth_L0_C[37] = 71430.70;
	earth_L0_C[38] = 17260.15;
	earth_L0_C[39] = 12036.46;
	earth_L0_C[40] = 5088.63;
	earth_L0_C[41] = 3154.69;
	earth_L0_C[42] = 801.82;
	earth_L0_C[43] = 9437.76;
	earth_L0_C[44] = 8827.39;
	earth_L0_C[45] = 7084.90;
	earth_L0_C[46] = 6286.60;
	earth_L0_C[47] = 14143.50;
	earth_L0_C[48] = 6279.55;
	earth_L0_C[49] = 12139.55;
	earth_L0_C[50] = 1748.02;
	earth_L0_C[51] = 5856.48;
	earth_L0_C[52] = 1194.45;
	earth_L0_C[53] = 8429.24;
	earth_L0_C[54] = 19651.05;
	earth_L0_C[55] = 10447.39;
	earth_L0_C[56] = 10213.29;
	earth_L0_C[57] = 1059.38;
	earth_L0_C[58] = 2352.87;
	earth_L0_C[59] = 6812.77;
	earth_L0_C[60] = 17789.85;
	earth_L0_C[61] = 83996.85;
	earth_L0_C[62] = 1349.87;
	earth_L0_C[63] = 4690.48;
	/*L1*/
	earth_L1_A[0] = 628331.966747E+6;
	earth_L1_A[1] = 206059;
	earth_L1_A[2] = 4303;
	earth_L1_A[3] = 425;
	earth_L1_A[4] = 119;
	earth_L1_A[5] = 109;
	earth_L1_A[6] = 93;
	earth_L1_A[7] = 72;
	earth_L1_A[8] = 68;
	earth_L1_A[9] = 67;
	earth_L1_A[10] = 59;
	earth_L1_A[11] = 56;
	earth_L1_A[12] = 45;
	earth_L1_A[13] = 36;
	earth_L1_A[14] = 29;
	earth_L1_A[15] = 21;
	earth_L1_A[16] = 19;
	earth_L1_A[17] = 19;
	earth_L1_A[18] = 17;
	earth_L1_A[19] = 16;
	earth_L1_A[20] = 16;
	earth_L1_A[21] = 15;
	earth_L1_A[22] = 12;
	earth_L1_A[23] = 12;
	earth_L1_A[24] = 12;
	earth_L1_A[25] = 12;
	earth_L1_A[26] = 11;
	earth_L1_A[27] = 10;
	earth_L1_A[28] = 10;
	earth_L1_A[29] = 9;
	earth_L1_A[30] = 9;
	earth_L1_A[31] = 8;
	earth_L1_A[32] = 6;
	earth_L1_A[33] = 6;
	earth_L1_B[0] = 0;
	earth_L1_B[1] = 2.678235;
	earth_L1_B[2] = 2.6351;
	earth_L1_B[3] = 1.590;
	earth_L1_B[4] = 5.796;
	earth_L1_B[5] = 2.966;
	earth_L1_B[6] = 2.59;
	earth_L1_B[7] = 1.14;
	earth_L1_B[8] = 1.87;
	earth_L1_B[9] = 4.41;
	earth_L1_B[10] = 2.89;
	earth_L1_B[11] = 2.17;
	earth_L1_B[12] = 0.40;
	earth_L1_B[13] = 0.47;
	earth_L1_B[14] = 2.65;
	earth_L1_B[15] = 5.34;
	earth_L1_B[16] = 1.85;
	earth_L1_B[17] = 4.97;
	earth_L1_B[18] = 2.99;
	earth_L1_B[19] = 0.03;
	earth_L1_B[20] = 1.43;
	earth_L1_B[21] = 1.21;
	earth_L1_B[22] = 2.83;
	earth_L1_B[23] = 3.26;
	earth_L1_B[24] = 5.27;
	earth_L1_B[25] = 2.08;
	earth_L1_B[26] = 0.77;
	earth_L1_B[27] = 1.30;
	earth_L1_B[28] = 4.24;
	earth_L1_B[29] = 2.70;
	earth_L1_B[30] = 5.64;
	earth_L1_B[31] = 5.30;
	earth_L1_B[32] = 2.65;
	earth_L1_B[33] = 4.67;
	earth_L1_C[0] = 0;
	earth_L1_C[1] = 6283.075850;
	earth_L1_C[2] = 12566.1517;
	earth_L1_C[3] = 3.523;
	earth_L1_C[4] = 26.298;
	earth_L1_C[5] = 1577.344;
	earth_L1_C[6] = 18849.23;
	earth_L1_C[7] = 529.69;
	earth_L1_C[8] = 398.15;
	earth_L1_C[9] = 5507.55;
	earth_L1_C[10] = 5223.69;
	earth_L1_C[11] = 155.42;
	earth_L1_C[12] = 796.30;
	earth_L1_C[13] = 775.52;
	earth_L1_C[14] = 7.11;
	earth_L1_C[15] = 0.98;
	earth_L1_C[16] = 5486.78;
	earth_L1_C[17] = 213.30;
	earth_L1_C[18] = 6275.96;
	earth_L1_C[19] = 2544.31;
	earth_L1_C[20] = 2146.17;
	earth_L1_C[21] = 10977.08;
	earth_L1_C[22] = 1748.02;
	earth_L1_C[23] = 5088.63;
	earth_L1_C[24] = 1194.45;
	earth_L1_C[25] = 4694.00;
	earth_L1_C[26] = 553.57;
	earth_L1_C[27] = 6286.60;
	earth_L1_C[28] = 1349.87;
	earth_L1_C[29] = 242.73;
	earth_L1_C[30] = 951.72;
	earth_L1_C[31] = 2352.87;
	earth_L1_C[32] = 9437.76;
	earth_L1_C[33] = 4690.48;
	/*L2*/
	earth_L2_A[0] = 52919;
	earth_L2_A[1] = 8720;
	earth_L2_A[2] = 309;
	earth_L2_A[3] = 27;
	earth_L2_A[4] = 16;
	earth_L2_A[5] = 16;
	earth_L2_A[6] = 10;
	earth_L2_A[7] = 9;
	earth_L2_A[8] = 7;
	earth_L2_A[9] = 5;
	earth_L2_A[10] = 4;
	earth_L2_A[11] = 4;
	earth_L2_A[12] = 3;
	earth_L2_A[13] = 3;
	earth_L2_A[14] = 3;
	earth_L2_A[15] = 3;
	earth_L2_A[16] = 3;
	earth_L2_A[17] = 3;
	earth_L2_A[18] = 2;
	earth_L2_A[19] = 2;
	earth_L2_B[0] = 0;
	earth_L2_B[1] = 1.0721;
	earth_L2_B[2] = 0.867;
	earth_L2_B[3] = 0.05;
	earth_L2_B[4] = 5.19;
	earth_L2_B[5] = 3.68;
	earth_L2_B[6] = 0.76;
	earth_L2_B[7] = 2.06;
	earth_L2_B[8] = 0.83;
	earth_L2_B[9] = 4.66;
	earth_L2_B[10] = 1.03;
	earth_L2_B[11] = 3.44;
	earth_L2_B[12] = 5.14;
	earth_L2_B[13] = 6.05;
	earth_L2_B[14] = 1.19;
	earth_L2_B[15] = 6.12;
	earth_L2_B[16] = 0.31;
	earth_L2_B[17] = 2.28;
	earth_L2_B[18] = 4.38;
	earth_L2_B[19] = 3.75;
	earth_L2_C[0] = 0;
	earth_L2_C[1] = 6283.0758;
	earth_L2_C[2] = 12566.152;
	earth_L2_C[3] = 3.52;
	earth_L2_C[4] = 26.30;
	earth_L2_C[5] = 155.42;
	earth_L2_C[6] = 18849.23;
	earth_L2_C[7] = 77713.77;
	earth_L2_C[8] = 775.52;
	earth_L2_C[9] = 1577.34;
	earth_L2_C[10] = 7.11;
	earth_L2_C[11] = 5573.14;
	earth_L2_C[12] = 796.30;
	earth_L2_C[13] = 5507.55;
	earth_L2_C[14] = 242.73;
	earth_L2_C[15] = 529.69;
	earth_L2_C[16] = 398.15;
	earth_L2_C[17] = 553.57;
	earth_L2_C[18] = 5223.69;
	earth_L2_C[19] = 0.98;
	/*L3*/
	earth_L3_A[0] = 289;
	earth_L3_A[1] = 35;
	earth_L3_A[2] = 17;
	earth_L3_A[3] = 3;
	earth_L3_A[4] = 1;
	earth_L3_A[5] = 1;
	earth_L3_A[6] = 1;
	earth_L3_B[0] = 5.844;
	earth_L3_B[1] = 0;
	earth_L3_B[2] = 5.49;
	earth_L3_B[3] = 5.20;
	earth_L3_B[4] = 4.72;
	earth_L3_B[5] = 5.30;
	earth_L3_B[6] = 5.97;
	earth_L3_C[0] = 6283.076;
	earth_L3_C[1] = 0;
	earth_L3_C[2] = 12566.15;
	earth_L3_C[3] = 155.42;
	earth_L3_C[4] = 3.52;
	earth_L3_C[5] = 18849.23;
	earth_L3_C[6] = 242.73;
	/*L4*/
	earth_L4_A[0] = 114;
	earth_L4_A[1] = 8;
	earth_L4_A[2] = 1;
	earth_L4_B[0] = 3.142;
	earth_L4_B[1] = 4.13;
	earth_L4_B[2] = 3.84;
	earth_L4_C[0] = 0;
	earth_L4_C[1] = 6283.08;
	earth_L4_C[2] = 12566.15;
	/*L5*/
	earth_L5_A[0] = 1;
	earth_L5_B[0] = 3.14;
	earth_L5_C[0] = 0;
	
	/*terms*/
	printf("Term calculating...");
	for(i=0;i<64;i++){
		L0_term[i] = earth_L0_A[i]*(cos(earth_L0_B[i]+earth_L0_C[i]*t));
	}
	for(i=0;i<34;i++){
		L1_term[i] = earth_L1_A[i]*(cos(earth_L1_B[i]+earth_L1_C[i]*t));
	}
	for(i=0;i<20;i++){
		L2_term[i] = earth_L2_A[i]*(cos(earth_L2_B[i]+earth_L2_C[i]*t));
	}
	for(i=0;i<7;i++){
		L3_term[i] = earth_L3_A[i]*(cos(earth_L3_B[i]+earth_L3_C[i]*t));
	}
	for(i=0;i<3;i++){
		L4_term[i] = earth_L4_A[i]*(cos(earth_L4_B[i]+earth_L4_C[i]*t));
	}
	for(i=0;i<1;i++){
		L5_term[i] = earth_L5_A[i]*(cos(earth_L5_B[i]+earth_L5_C[i]*t));
	}
	
	/*sums*/
	for(j=0;j<64;j++){
		L0_sum += L0_term[j];
	}
	for(j=0;j<34;j++){
		L1_sum += L1_term[j];
	}
	for(j=0;j<20;j++){
		L2_sum += L2_term[j];
	}
	for(j=0;j<7;j++){
		L3_sum += L3_term[j];
	}
	for(j=0;j<3;j++){
		L4_sum += L4_term[j];
	}
	for(j=0;j<1;j++){
		L5_sum += L5_term[j];
	}
	
	L = (L0_sum + L1_sum*t + L2_sum*t*t + L3_sum*t*t*t + L4_sum*t*t*t*t + L5_sum*t*t*t*t*t)/10e8;
	return L;
}

/*************************************************************************
 *Method: getBofEarth
 *Func: Calculate the B value of earth using the julian time t.
 *Params:double --- the julian time from epoch 2000.0.
 *Return:double --- the B value of earth.
 *************************************************************************/
double getBofEarth(double t){
	int i,j;
	double earth_B0_A[5],earth_B0_B[5],earth_B0_C[5];
	double earth_B1_A[2],earth_B1_B[2],earth_B1_C[2];
	
	double B0_term[5],B1_term[2];
	double B0_sum = 0.0;
	double B1_sum = 0.0;
	double B = 0.0;
	
	earth_B0_A[0] = 280;
	earth_B0_A[1] = 102;
	earth_B0_A[2]	= 80;
	earth_B0_A[3] = 44;
	earth_B0_A[4] = 32;
	earth_B0_B[0] = 3.199;
	earth_B0_B[1] = 5.422;
	earth_B0_B[2] = 3.88;
	earth_B0_B[3] = 3.70;
	earth_B0_B[4] = 4.00;
	earth_B0_C[0] = 84334.662;
	earth_B0_C[1] = 5507.553;
	earth_B0_C[2] = 5223.69;
	earth_B0_C[3] = 2352.87;
	earth_B0_C[4] = 1577.34;

	earth_B1_A[0] = 9;
	earth_B1_A[1] = 6;
	earth_B1_B[0] = 3.90;
	earth_B1_B[1] = 1.73;
	earth_B1_C[0] = 5507.55;
	earth_B1_C[1] = 1577.34;
	
	for(i=0;i<5;i++){
		B0_term[i] = earth_B0_A[i]*(cos(earth_B0_B[i]+earth_B0_C[i]*t));
	}
	
	for(i=0;i<2;i++){
		B1_term[i] = earth_B1_A[i]*(cos(earth_B1_B[i]+earth_B1_C[i]*t));
	}
	
	for(j=0;j<5;j++){
		B0_sum += B0_term[j];
	}
	
	for(j=0;j<2;j++){
		B1_sum += B1_term[j];
	}
	
	B = (B0_sum+B1_sum*t)/10e8;
	return B;
}

/*************************************************************************
 *Method: getRofEarth
 *Func: Calculate the R value of earth using the julian time t.
 *Params:double --- the julian time from epoch 2000.0.
 *Return:double --- the R value of earth.
 *************************************************************************/
double getRofEarth(double t){
	int i,j;
	double earth_R0_A[40],earth_R0_B[40],earth_R0_C[40];
	double earth_R1_A[10],earth_R1_B[10],earth_R1_C[10];
	double earth_R2_A[6],earth_R2_B[6],earth_R2_C[6];
	double earth_R3_A[2],earth_R3_B[2],earth_R3_C[2];
	double earth_R4_A[1],earth_R4_B[1],earth_R4_C[1];
	
	double R0_term[40],R1_term[10],R2_term[6],R3_term[2],R4_term[1];
	double R0_sum = 0.0;
	double R1_sum = 0.0;
	double R2_sum = 0.0;
	double R3_sum = 0.0;
	double R4_sum = 0.0;
	double R = 0.0;
	
	/*R0*/
	earth_R0_A[0] = 100013989;
	earth_R0_A[1] = 1670700;
	earth_R0_A[2] = 13956;
	earth_R0_A[3] = 3084;
	earth_R0_A[4] = 1628;
	earth_R0_A[5] = 1576;
	earth_R0_A[6] = 925;
	earth_R0_A[7] = 542;
	earth_R0_A[8] = 472;
	earth_R0_A[9] = 346;
	earth_R0_A[10] = 329;
	earth_R0_A[11] = 307;
	earth_R0_A[12] = 243;
	earth_R0_A[13] = 212;
	earth_R0_A[14] = 186;
	earth_R0_A[15] = 175;
	earth_R0_A[16] = 110;
	earth_R0_A[17] = 98;
	earth_R0_A[18] = 86;
	earth_R0_A[19] = 86;
	earth_R0_A[20] = 65;
	earth_R0_A[21] = 63;
	earth_R0_A[22] = 57;
	earth_R0_A[23] = 56;
	earth_R0_A[24] = 49;
	earth_R0_A[25] = 47;
	earth_R0_A[26] = 45;
	earth_R0_A[27] = 43;
	earth_R0_A[28] = 39;
	earth_R0_A[29] = 38;
	earth_R0_A[30] = 37;
	earth_R0_A[31] = 37;
	earth_R0_A[32] = 36;
	earth_R0_A[33] = 35;
	earth_R0_A[34] = 33;
	earth_R0_A[35] = 32;
	earth_R0_A[36] = 32;
	earth_R0_A[37] = 28;
	earth_R0_A[38] = 28;
	earth_R0_A[39] = 26;
	earth_R0_B[0] = 0;
	earth_R0_B[1] = 3.0984635;
	earth_R0_B[2] = 3.05525;
	earth_R0_B[3] = 5.1985;
	earth_R0_B[4] = 1.1739;
	earth_R0_B[5] = 2.8469;
	earth_R0_B[6] = 5.453;
	earth_R0_B[7] = 4.564;
	earth_R0_B[8] = 3.661;
	earth_R0_B[9] = 0.964;
	earth_R0_B[10] = 5.900;
	earth_R0_B[11] = 0.299;
	earth_R0_B[12] = 4.273;
	earth_R0_B[13] = 5.847;
	earth_R0_B[14] = 5.022;
	earth_R0_B[15] = 3.012;
	earth_R0_B[16] = 5.055;
	earth_R0_B[17] = 0.89;
	earth_R0_B[18] = 5.69;
	earth_R0_B[19] = 1.27;
	earth_R0_B[20] = 0.27;
	earth_R0_B[21] = 0.92;
	earth_R0_B[22] = 2.01;
	earth_R0_B[23] = 5.24;
	earth_R0_B[24] = 3.25;
	earth_R0_B[25] = 2.58;
	earth_R0_B[26] = 5.54;
	earth_R0_B[27] = 6.01;
	earth_R0_B[28] = 5.36;
	earth_R0_B[29] = 2.39;
	earth_R0_B[30] = 0.83;
	earth_R0_B[31] = 4.90;
	earth_R0_B[32] = 1.67;
	earth_R0_B[33] = 1.84;
	earth_R0_B[34] = 0.24;
	earth_R0_B[35] = 0.18;
	earth_R0_B[36] = 1.78;
	earth_R0_B[37] = 1.21;
	earth_R0_B[38] = 1.90;
	earth_R0_B[39] = 4.59;
	earth_R0_C[0] = 0;
	earth_R0_C[1] = 6283.0758500;
	earth_R0_C[2] = 12566.15170;
	earth_R0_C[3] = 77713.7715;
	earth_R0_C[4] = 5753.3849;
	earth_R0_C[5] = 7860.4194;
	earth_R0_C[6] = 11506.770;
	earth_R0_C[7] = 3930.210;
	earth_R0_C[8] = 5884.927;
	earth_R0_C[9] = 5507.553;
	earth_R0_C[10] = 5223.694;
	earth_R0_C[11] = 5573.143;
	earth_R0_C[12] = 11790.629;
	earth_R0_C[13] = 1577.344;
	earth_R0_C[14] = 10977.079;
	earth_R0_C[15] = 18849.228;
	earth_R0_C[16] = 5486.778;
	earth_R0_C[17] = 6069.78;
	earth_R0_C[18] = 15720.84;
	earth_R0_C[19] = 161000.69;
	earth_R0_C[20] = 17260.15;
	earth_R0_C[21] = 529.69;
	earth_R0_C[22] = 83996.85;
	earth_R0_C[23] = 71430.70;
	earth_R0_C[24] = 2544.31;
	earth_R0_C[25] = 775.52;
	earth_R0_C[26] = 9437.76;
	earth_R0_C[27] = 6275.96;
	earth_R0_C[28] = 4694.00;
	earth_R0_C[29] = 8827.39;
	earth_R0_C[30] = 19651.05;
	earth_R0_C[31] = 12139.55;
	earth_R0_C[32] = 12036.46;
	earth_R0_C[33] = 2942.46;
	earth_R0_C[34] = 7084.90;
	earth_R0_C[35] = 5088.63;
	earth_R0_C[36] = 398.15;
	earth_R0_C[37] = 6286.60;
	earth_R0_C[38] = 6279.55;
	earth_R0_C[39] = 10447.39;
	/*R1*/
	earth_R1_A[0] = 103019;
	earth_R1_A[1] = 1721;
	earth_R1_A[2] = 702;
	earth_R1_A[3] = 32;
	earth_R1_A[4] = 31;
	earth_R1_A[5] = 25;
	earth_R1_A[6] = 18;
	earth_R1_A[7] = 10;
	earth_R1_A[8] = 9;
	earth_R1_A[9] = 9;
	earth_R1_B[0] = 1.107490;
	earth_R1_B[1] = 1.0644;
	earth_R1_B[2] = 3.142;
	earth_R1_B[3] = 1.02;
	earth_R1_B[4] = 2.84;
	earth_R1_B[5] = 1.32;
	earth_R1_B[6] = 1.42;
	earth_R1_B[7] = 5.91;
	earth_R1_B[8] = 1.42;
	earth_R1_B[9] = 0.27;
	earth_R1_C[0] = 6283.07585;
	earth_R1_C[1] = 12566.1517;
	earth_R1_C[2] = 0;
	earth_R1_C[3] = 18849.23;
	earth_R1_C[4] = 5507.55;
	earth_R1_C[5] = 5223.69;
	earth_R1_C[6] = 1577.34;
	earth_R1_C[7] = 10977.08;
	earth_R1_C[8] = 6275.96;
	earth_R1_C[9] = 5486.78;
	/*R2*/
	earth_R2_A[0] = 4359;
	earth_R2_A[1] = 124;
	earth_R2_A[2] = 12;
	earth_R2_A[3] = 9;
	earth_R2_A[4] = 6;
	earth_R2_A[5] = 3;
	earth_R2_B[0] = 5.7846;
	earth_R2_B[1] = 5.579;
	earth_R2_B[2] = 3.14;
	earth_R2_B[3] = 3.63;
	earth_R2_B[4] = 1.87;
	earth_R2_B[5] = 5.47;
	earth_R2_C[0] = 6283.0758;
	earth_R2_C[1] = 12566.152;
	earth_R2_C[2] = 0;
	earth_R2_C[3] = 77713.77;
	earth_R2_C[4] = 5573.14;
	earth_R2_C[5] = 18849.23;
	/*R3*/
	earth_R3_A[0] = 145;
	earth_R3_A[1] = 7;
	earth_R3_B[0] = 4.273;
	earth_R3_B[1] = 3.92;
	earth_R3_C[0] = 6283.076;
	earth_R3_C[1] = 12566.15;
	/*R4*/
	earth_R4_A[0] = 4;
	earth_R4_B[0] = 2.56;
	earth_R4_C[0] = 6283.08;
	
	/*terms*/
	for(i=0;i<40;i++){
		R0_term[i] = earth_R0_A[i]*(cos(earth_R0_B[i]+earth_R0_C[i]*t));
	}
	for(i=0;i<10;i++){
		R1_term[i] = earth_R1_A[i]*(cos(earth_R1_B[i]+earth_R1_C[i]*t));
	}
	for(i=0;i<6;i++){
		R2_term[i] = earth_R2_A[i]*(cos(earth_R2_B[i]+earth_R2_C[i]*t));
	}
	for(i=0;i<2;i++){
		R3_term[i] = earth_R3_A[i]*(cos(earth_R3_B[i]+earth_R3_C[i]*t));
	}
	for(i=0;i<1;i++){
		R4_term[i] = earth_R4_A[i]*(cos(earth_R4_B[i]+earth_R4_C[i]*t));
	}
	
	/*sums*/
	for(j=0;j<40;j++){
		R0_sum += R0_term[i];
	}
	for(j=0;j<10;j++){
		R1_sum += R1_term[i];
	}
	for(j=0;j<6;j++){
		R2_sum += R2_term[i];
	}
	for(j=0;j<2;j++){
		R3_sum += R3_term[i];
	}
	for(j=0;j<1;j++){
		R4_sum += R4_term[i];
	}
	
	R = (R0_sum + R1_sum*t + R2_sum*t*t + R3_sum*t*t*t + R4_sum*t*t*t*t)/10e8;
	return R;
}
