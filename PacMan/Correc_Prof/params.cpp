#include <string>
#include "params.h"
#include "game.h"

using namespace std;

void InitParams (CMyParam & Param)
{
//Move Keys
Param.MapParamChar["KeyUp"] = 'z';
Param.MapParamChar["KeyDown"] = 's';
Param.MapParamChar["KeyLeft"] = 'q';
Param.MapParamChar["KeyRight"] = 'd';

Param.MapParamChar["TokenP1"] = 'O';
Param.MapParamChar["TokenP2"] = 'X';

//Size of grid — suppose to be a rectangle
Param.MapParamUnsigned["NbColumn"] = 10;
Param.MapParamUnsigned["NbLine"] = 10;

//Display Colors
Param.MapParamString["ColorP1"] = KColor.find("KRed")->second ;
Param.MapParamString["ColorP2"] = KColor.find("KBlue")->second ;

}
