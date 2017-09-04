#ifndef FEATURES_H
#define FEATURES_H

#include<bits/stdc++.h>

class features
{
    public:
    features()
    {
        count=0;
        rating=false;
        index=-1;
    }
        void insert(int,bool,int);
        void copy(std::vector<std::vector<features> >&,std::vector<std::vector<features> >&);
        int getcount();
        bool getrating();
        int getindex();
    protected:
    private:
        int count;
        bool rating;
        int index;
};

#endif // FEATURES_H
