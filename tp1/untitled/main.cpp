#include <iostream>
#include <vector>
using namespace std;

bool isSorted (vector<int>tab);
{
     unsigned i = 0;
     while (i< tab.size())
  {
         if (tab[i] > tab [i-1])
         {
             ++1;
         }
     }

}

void triComptage (vector<int> & tab)
  int max = tab[0];
  for (unsigned i = 1;i < tab.size();++1)
  {
    if ( tab[i] > max)
{
    max = tab[i];


}
}





using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
