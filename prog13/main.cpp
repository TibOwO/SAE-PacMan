#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

map<string, string>myMap;


template <class T, class U>
void ShowMap (const map<T,U> & AMap)
{
for (const pair <T,U> & Val : AMap)
cout << "Cle : " << Val.first << " "
<< "Valeur : " << Val.second << endl;

cout << endl;

}

template <class T, class U>
void ShowMapV2 (const map<T,U> & AMap)
{
for (typename map<T,U>::const_iterator it (AMap.begin());
it != AMap.end(); ++it)
cout << "Cle : " << it->first << " "
<< "Valeur : " << it->second << endl;
cout << endl;
}


//template <class T, class U>
//void insertIntoMapIfNotExists (const map <T, U> & MyMap, const string & Val1, const string & Val2)
//{
//    if(MyMap[Val1] = Val2)
//    {
//        cout <<"Element with key "<< Val1 <<" not inserted because already existed"<< endl;
//    }else{
//        MyMap[Val1] = Val2;
//    }
//}

//template <class T>
//unsigned find (const vector <T> & vect, const T & val){
//unsigned i (0);
//
//for (; i < vect.size () && vect[i] != val; ++i);
//
//return i;
//
//}
//
//template <class T>
//typename vector<T>::iterator find (const vector <T> & vect, const T & val){
//
//typename vector<T>::iterator it (vect.begin());
//
//for (; it != vect.end () && *it != val; ++it);
//
//return it;
//
//}
//
//template <class T, class U>
//typename map<T, U>::iterator find (const map <T, U> & aMap, const U & val){
//typename map<T, U>::iterator it (aMap.begin());
//for (; it != aMap.end () && it->second != val; ++it);
//return it;
//
//}
//

const vector <string> cleS = {"S1"};
const vector <string> cleC = {"C1", "C2", "C3", "C4"};
const vector <string> cleU = {"U1", "U2","U3"};

struct CMyParams
{
    map <string ,string> MapParamsString;
    map <string ,char> MapParamsChar;
    map <string ,unsigned> MapParamsUnsigned;

};


void LoadParams ( CMyParams & MyPar, const string nomfile)
{
    ifstream ifs(nomfile);
    char Valchar; unsigned Valunsigned; string Valstring;
    for (string cle;ifs >> cle; )
    {
        ifs >> Valchar; // pour purger le ':'
        if (cleS.end() !=find(cleS.begin(), cleS.end(),cle))
        {
            ifs >> Valstring;
            MyPar.MapParamsString[cle] = Valstring;
        }
        else if (cleC.end() !=find(cleC.begin(), cleC.end(),cle))
        {
            ifs >> Valchar;
            MyPar.MapParamsChar[cle] = Valchar;
        }
        else if (cleU.end() !=find(cleU.begin(), cleU.end(),cle))
        {
            ifs >> Valunsigned;
            MyPar.MapParamsUnsigned[cle] = Valunsigned;
        }
    }

}


int main()
{

    myMap["Casali"] = "Alain";
    myMap["Bedos"] = "Enzo";
    myMap["Ametller"] = "Thibault";
    myMap["Maoulida"] = "Raoul";


    //cout << myMap["Bedos"]<< endl << endl;
    ShowMapV2(myMap);
    cout << endl;

    cout << "----------------------------------------------------"<< endl;
    // << insertIntoMapIfNotExists(myMap, "Bedos", "Enzo");




}
