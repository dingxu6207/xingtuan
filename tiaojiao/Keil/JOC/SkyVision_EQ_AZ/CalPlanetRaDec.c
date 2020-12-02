#include <stdio.h>
#include "PlanetPosition.c"

void FCalSunMoonPlanetPos(int fnum)
{
	double jed;
	double *coord;
	jed = getJD();
	jed=2454816.73456; 
	switch(fnum){
		case 0:
		  calSunPos(jed);
		
			//calSunPos(jed);
			break;
		case 1:
			//显示月球坐标，目前还没有实现
			/*coord = calMoonPos(jed);
			*fra = coord[0];
			*fdec = coord[1];*/
			calMoonPos(jed);
			break;
		case 2:
			/*coord = calPlanetPos(jed,fnum);
			*fra = coord[0] + 180;
			*fdec = -coord[1];	 */
			calPlanetPos(jed,fnum);
			break;	
		case 3:
			/*coord = calPlanetPos(jed,fnum);
			*fra = coord[0] + 180;
			*fdec = -coord[1];	*/
			calPlanetPos(jed,fnum);
			break;
		case 4:
		/*	coord = calPlanetPos(jed,fnum);
			*fra = coord[0] + 180;
			*fdec = -coord[1];		   */
			calPlanetPos(jed,fnum);
			break;
		case 5:
		/*	coord = calPlanetPos(jed,fnum);
			*fra = coord[0] + 360;
			*fdec = coord[1];		   */
			calPlanetPos(jed,fnum);
			break;
		case 6:
		/*	coord = calPlanetPos(jed,fnum);
			*fra = coord[0] + 180;
			*fdec = -coord[1];			*/
			calPlanetPos(jed,fnum);
			break;
		case 7:
		/*	coord = calPlanetPos(jed,fnum);
			*fra = coord[0] + 360;
			*fdec = coord[1];			*/
			calPlanetPos(jed,fnum);
			break;
		case 8:
		/*	coord = calPlanetPos(jed,fnum);
			*fra = coord[0] + 360;
			*fdec = coord[1];			*/
			calPlanetPos(jed,fnum);
			break;
		case 9:
			/*coord = calPlutoPosition(jed);
			*fra = coord[0];
			*fdec = coord[1]; */
			calPlutoPos(jed);
			break;
		default:
			break;
	}
}
