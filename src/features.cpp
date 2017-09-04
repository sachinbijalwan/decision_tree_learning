#include "features.h"
#include<bits/stdc++.h>
using namespace std;
void features::insert(int cou,bool rate,int ind){
if(cou>1000)
{
    cout<<"error"<<endl;
    exit(1);
}
count=cou;
rating=rate;
index=ind;
}
void features::copy(vector<vector<features> >& a,vector<vector<features> >& b){

    for(int i=0;i<a.size();i++){
          //  vector<features> x;
        for(int j=0;j<a[i].size();j++){
        //    features f;
            b[i][j].insert(a[i][j].count,a[i][j].rating,a[i][j].index);
      //      x.push_back(f);
        }
    //b.push_back(x);
    }

}
int features::getcount(){
return count;
}
bool features::getrating(){
    return rating;
}
int features::getindex(){
return index;
}
