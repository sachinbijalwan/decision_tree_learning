#include <iostream>
#include<bits/stdc++.h>
#include "partition_tree.h"
#include "features.h"
using namespace std;

#define POLAR_SIZE 5000
#define LINES_IN_INPUT 1000

void make_polar(vector<int>& polar){

fstream file;
file.open("polar.txt");
int num11,num12;
//vector<int> polar;
string str;
while(getline(file,str)){
    istringstream ss(str);
    while(ss>>num11>>num12){
        polar.push_back(num11);
    }
}
file.close();
sort(polar.begin(),polar.end());

}

void make_word_count(vector<int>& polar,partition_tree* tree,double s){
	fstream file;
	file.open("subset_train.txt");
    string str;
    int true_count=0;
    int loop_count=0;
    vector<features> feat;
    double no_of_error=0;
    s/=100;
    while(getline(file,str)){


        features f;
        for(int i=0;i<str.size();i++)
            {
            if(str[i]==':')
                str[i]=' ';
            }

    istringstream ss(str);

    int num;
    int num1,num2;

    ss>>num;
    bool rate=false;

    if(num>=7)
        rate=true;
    else
        rate=false;
    if(no_of_error/(loop_count)<s){
        no_of_error++;
        rate=!rate;
    }

    if(rate)
        true_count++;
    vector<bool> entered;
    while(ss>>num1>>num2){
        bool enter=false;
        for(int l=0;l<polar.size();l++){
            if(num1==polar[l])
                {
                	enter=true;
                    f.insert(num2,rate,loop_count);

                    tree->insert_data(f,l,loop_count);
                    break;
                }
            else if(num1<polar[l])
                break;
        }
        }
        tree->check_inserted_data(rate,loop_count);
   loop_count++;

}
cout<<true_count<<" "<<no_of_error<<endl;
file.close();
}
void make_word_count(vector<int>& polar,partition_tree* tree){
features f;
f.insert(0,0,-1);
int true_count=0;
fstream file;

	file.open("subset_test.txt");

    string str;
    int loop_count=0;
    while(getline(file,str)){

        features f;
        for(int i=0;i<str.size();i++)
            {
            if(str[i]==':')
                str[i]=' ';
            }

    istringstream ss(str);

    int num;
    int num1,num2;

    ss>>num;

    bool rate=false;

    if(num>=7)
        rate=true;
    else
        rate=false;
    if(rate==true)
        true_count++;
    features p;
    p.insert(0,0,-1);
    vector<features> s(POLAR_SIZE,p);
    while(ss>>num1>>num2){
        bool enter=false;
        for(int l=0;l<polar.size();l++){
            if(num1==polar[l])
                {
                	enter=true;
                    f.insert(num2,rate,loop_count);
                    s[l]=f;
                   // test_data[l][loop_count]=f;
                    break;
                }
            else if(num1<polar[l])
                break;
        }
        }
        for(int i=0;i<s.size();i++){
            if(s[i].getindex()==-1)
                s[i].insert(0,rate,loop_count);
        }
    tree->calculate_accuracy(tree,s);
    //cout<<endl;
   loop_count++;

}
//cout<<"true count is "<<true_count<<endl;
file.close();

}
void make_word_count(vector<vector<int> >& polar,vector<partition_tree*> tree){

}
void prune_tree(){
    partition_tree* tree;
    tree=new partition_tree();
    tree->define_size(POLAR_SIZE,LINES_IN_INPUT);
   vector<int> polar;
    make_polar(polar);
    make_word_count(polar,tree,0);
    tree->read_data();
    //cout<<"first "<<endl;
  //  tree->make_accuracy();
    //tree->printaccuracy();
   // tree=tree1;
    //delete(tree->left);
    //tree->left=NULL;
   // delete(tree->right);
   // tree->right=NULL;
    tree->ispruning=true;
    tree->split_tree(tree,tree);
    //tree->make_zero(tree);
    //tree->calculate(tree,polar);
    //cout<<"whatever it is "<<endl;
    //tree->printaccuracy();
    ///exit(1);
    //cout<<"second "<<endl;
    //tree->printaccuracy();
    tree->pruning_tree(tree,tree,polar);
    //cout<<"third "<<endl;
    //tree->printaccuracy();
    //tree->make_accuracy();
    tree->make_zero(tree);
    make_word_count(polar,tree);
    //cout<<"fourth "<<endl;
    tree->printaccuracy();



}
void print_data(){
partition_tree* tree;
tree=new partition_tree();
tree->define_size(POLAR_SIZE,LINES_IN_INPUT);
vector<int> polar;
make_polar(polar);
make_word_count(polar,tree,0);
tree->read_data();
tree->split_tree(tree,tree);
make_word_count(polar,tree);
tree->printaccuracy();
}

void add_noise(double noise){
    partition_tree* tree;
tree=new partition_tree();
tree->define_size(POLAR_SIZE,LINES_IN_INPUT);
vector<int> polar;
make_polar(polar);
make_word_count(polar,tree,noise);
tree->read_data();
tree->split_tree(tree,tree);
make_word_count(polar,tree);
tree->printaccuracy();

}
void random_forest(){
vector<partition_tree*> tree(POLAR_SIZE/100);
vector<vector<int> > whole_polar;
vector<int> polar;
make_polar(polar);
for(int i=0;i<tree.size();i++)
{
    tree[i]=new partition_tree();
    tree[i]->define_size(100,LINES_IN_INPUT);
    srand((unsigned)time(0));
    for(int j=0;j<100;j++)
        whole_polar[i].push_back(polar[rand()%POLAR_SIZE]);
}
    /*make_word_count(whole_polar,tree,0);
    tree[i]->read_data();
    tree->split_tree(tree[i],tree[i]);
    make_word_count(whole_polar,tree[i]);
*/

//tree->printaccuracy();
}
int main()
{
    /*partition_tree* tree;
    tree=new partition_tree();
    tree->define_size(POLAR_SIZE,LINES_IN_INPUT);
    vector<int> polar;
    make_polar(polar);
    make_word_count(polar,tree);
    //cout<<"wherea re you "<<endl;
   // tree->compute_IG();
    //tree->print_data();
    tree->read_data(); */ //read or write should be here
    int exptno=4;
    switch(exptno){
case 2:
    print_data();
    break;
case 3:
    cout<<"accuracy for noise 0.5 "<<endl;
    add_noise(0.5);
    cout<<"accuracy for noise 1"<<endl;
    add_noise(1);
    cout<<"accuracy for noise 5 "<<endl;
    add_noise(5);
    cout<<"accuracy for noise 10 "<<endl;
    add_noise(10);
    break;
case 4:
    prune_tree();
    break;
case 5:
    random_forest();
    break;
    }
    //tree->split_tree(tree,tree);

   // vector<vector<features> > x;
       // make_word_count(polar,tree,0);
       // tree->printaccuracy();
       // tree->make_zero(tree);

        //tree->calculate(tree,polar);
        //tree->printaccuracy();
       // tree->make_zero(tree);
       // make_word_count(polar,tree,0);
       // tree->printaccuracy();
   // tree->printaccuracy();
   //prune_tree(tree,polar);
    /*cout<<"first "<<endl;
    tree->make_accuracy();
    tree->printaccuracy();
    tree->calculate(tree,polar);
    //tree->make_accuracy();
    cout<<"second "<<endl;
    tree->printaccuracy();
    tree->pruning_tree(tree,tree,polar);
    cout<<"third "<<endl;
    tree->printaccuracy();
    tree->make_accuracy();
    make_word_count(polar,tree,0);
    cout<<"fourth "<<endl;
    tree->printaccuracy();
    */
    //cout<<polar[p.first]<<" "<<p.second<<endl;
    //int i=p.first;
    //tree->print(41);
        /*for(int j=0;j<p.second;j++){
            cout<<tree->get_data(i,j).getcount()<<"  ";
        }
        cout<<endl;
        cout<<"second part "<<endl;
        for(int j=p.second;j<LINES_IN_INPUT-1;j++){
            cout<<tree->get_data(i,j).getcount()<<" ";
        }*/
   // tree->print();
    return 0;
}
