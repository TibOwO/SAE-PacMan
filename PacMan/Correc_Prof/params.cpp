#include <iostream>
#include <string>
#include "params.h"
#include "game.h"
#include <fstream>
#include <algorithm>


using namespace std;

void InitParams (CMyParam & Param)
{
//Move Keys
Param.MapParamChar["KeyUp"] = 'Z';
Param.MapParamChar["KeyDown"] = 'S';
Param.MapParamChar["KeyLeft"] = 'Q';
Param.MapParamChar["KeyRight"] = 'D';

Param.MapParamChar["KeyUPLeft"] = 'A';
Param.MapParamChar["KeyUpRight"] = 'E';
Param.MapParamChar["KeyDownLeft"] = 'W';
Param.MapParamChar["KeyDownRight"] = 'X';

Param.MapParamChar["TokenP1"] = 'O';
Param.MapParamChar["TokenP2"] = 'X';

Param.MapParamChar["wallHor"] = '-';
Param.MapParamChar["wallVer"] = '|';

//Size of grid — suppose to be a rectangle
Param.MapParamUnsigned["NbColumn"] = 30;
Param.MapParamUnsigned["NbRow"] = 30 ;

//Display Colors
Param.MapParamString["ColorP1"] = KColor.find("KRed")->second ;
Param.MapParamString["ColorP2"] = KColor.find("KBlue")->second ;
}

void LoadParams (CMyParam & Param){
    ifstream ifs ("/amuhome/b22002844/Documents/Programme/C++/PacMan/PacMan/Nos_fichiers/config.yaml");
    if (!ifs){
        cerr << "Pas de fichier de configuration ici" << endl;
        exit(-1);
    }
    cout << "Fichier de configuration OK " << endl;
    for (string key, trash; ifs >> key; ){
        char dp;
        ifs >> dp;
        if (find(KAuthorizedKey.VParamChar.begin(), KAuthorizedKey.VParamChar.end(), key) != KAuthorizedKey.VParamChar.end()){
            char val;
            ifs >> val;
            Param.MapParamChar[key] = val;
        }
        else if (find(KAuthorizedKey.VParamUnsigned.begin(), KAuthorizedKey.VParamUnsigned.end(), key) != KAuthorizedKey.VParamUnsigned.end()){
            unsigned val;
            ifs >> val;
            Param.MapParamUnsigned[key] = val;
        }
        else if (find(KAuthorizedKey.VParamString.begin(), KAuthorizedKey.VParamString.end(), key) != KAuthorizedKey.VParamString.end()){
            string val;
            ifs >> val;
            auto it = KColor.find(val);
            if (it != KColor.end()){
                Param.MapParamString[key] = it->second;
            }
        }
        else
            getline(ifs, trash);
    }
}
