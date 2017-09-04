#include "partition_tree.h"
#include<bits/stdc++.h>
#define POLAR_SIZE 5000

using namespace std;

int no_of_nodes=0;
int rite=0;
int wrong=0;
int prune_rite=0;
int prune_wrong=0;
void partition_tree::insert_data(vector<vector<features> >& f){
data=f;
}
void partition_tree::calculate(partition_tree* tree,vector<int>& polar){
fstream file;
file.open("subset_validation.txt");
string t;
int loop_count=0;
tree->make_zero(tree);
//vector<features> s;
while(getline(file,t)){
    for(int i=0;i<t.size();i++)
            {
            if(t[i]==':')
                t[i]=' ';
            }
  istringstream ss(t);
    int num;
    ss>>num;

    bool rate=false;
    if(num>=7)
        rate=true;
    int num1,num2;
    features f;
     features p;
    p.insert(0,0,-1);
    vector<features> s(POLAR_SIZE,p);
    while(ss>>num1>>num2){
//        bool enter=false;
        for(unsigned int l=0;l<polar.size();l++){
            if(num1==polar[l])
                {
//                	enter=true;
                    f.insert(num2,rate,loop_count);
                    s[l]=f;
                   // test_data[l][loop_count]=f;
                    break;
                }
            else if(num1<polar[l])
                break;
        }
        }
        for(unsigned int i=0;i<s.size();i++){
            if(s[i].getindex()==-1)
                s[i].insert(0,rate,loop_count);
        }
        loop_count++;
   tree->calculate_accuracy(tree,s);

}
//printaccuracy();
//cout<<"loop count is "<<loop_count<<endl;
}
void partition_tree::pruning_tree(partition_tree* tree,partition_tree* tree2,vector<int>& polar){
if(tree->left || tree->right)
{
    pruning_tree(tree->left,tree2,polar);
    pruning_tree(tree->right,tree2,polar);
    calculate(tree2,polar);
    int r=tree2->ri;
    int l=tree2->le;
    rite=0;
    wrong=0;
    partition_tree *part1,*part2;
    part1=tree->left;
    part2=tree->right;
    tree->left=NULL;
    tree->right=NULL;
    make_zero(tree2);
    calculate(tree2,polar);
    double accuracy1=0,accuracy2=0;
    accuracy1=r;
    accuracy1/=(r+l);
    accuracy2=tree2->ri;
    accuracy2/=(tree2->ri+tree2->le);
    //cout<<"accuracies are "<<accuracy1<<" "<<accuracy2<<endl;
    if(accuracy1<accuracy2){
      //  cout<<"going left"<<endl;
        return;
    }
    else{
       // cout<<"going right"<<endl;
        tree->left=part1;
        tree->right=part2;
        calculate(tree2,polar);
    }
  /*  tree->left=NULL;
    tree->le=tree->right->le;
    tree->ri=tree->right->ri;
    calculate(tree2,polar);
    double accuracy1,accuracy2;
    accuracy1=r;
    accuracy1/=(r+l);
    accuracy2=tree->ri;
    accuracy2/=(tree->ri+tree->le);
    cout<<"here are the accuracy "<<accuracy1<<" "<<accuracy2<<endl;
    if(accuracy1<accuracy2){
        cout<<"going left here "<<endl;
    }
    else{
        rite=r;
        wrong=l;
        tree->left=part1;
        tree->le=(part1->le+part2->le);
        tree->ri=(part1->ri+part2->ri);
    //    tree->right=part2;
    }
    r=tree->ri;
    l=tree->le;
    rite=0;
    wrong=0;
    tree->right=NULL;   //
    tree->le=part1->le; //
    tree->ri=part1->ri; //
    calculate(tree2,polar);
    accuracy1=r;
    accuracy1/=(r+l);
    accuracy2=tree->ri;
    accuracy2/=(tree->ri+tree->le);
    //cout<<accuracy1<<" "<<accuracy2<<endl;
    if(accuracy1<accuracy2){
            cout<<"going right here "<<endl;
    }
    else{
        rite=r;
        wrong=l;
        tree->right=part2;
        tree->le=0;
        tree->ri=0;
        if(tree->left)
            {
                tree->le+=tree->left->le;
                tree->ri+=tree->left->ri;
            }
        if(tree->right)
        {
            tree->ri+=tree->right->ri;
            tree->le+=tree->right->le;
        }
*/
    }
    //cout<<"right and wrong are "<<rite<<" "<<wrong<<endl;
}
void partition_tree::make_accuracy(){
rite=0;
wrong=0;
}
void partition_tree::insert_data(vector<features>& f,int i){
//data[i]=f;
data.insert(data.begin()+i,f);
}

void partition_tree::insert_data(features f,int i,int j){
data[i][j]=f;
}

features partition_tree::get_data(int i,int j){
features f;
if(i>data.size() || j>data[i].size())
return f;
else
    return data[i][j];
}
partition_tree::partition_tree()
{
      le=0;
      ri=0;
      ispruning=false; //ctor
}

partition_tree::~partition_tree()
{
    //dtor
}

void partition_tree::print_data(){
fstream f;
f.open("output.txt",ios::out);
for(int i=0;i<IG.size();i++){
    for(int j=0;j<IG[i].size();j++){
       f<<setprecision(15)<<IG[i][j]<<" ";
    }
    f<<endl;
}
    f.close();
}
void partition_tree::read_data(){
fstream f;
f.open("output.txt");
string s;
int i=0,j=0;
while(getline(f,s)){
        j=0;
    istringstream ss(s);
    double num1;
    while(ss>>num1){
        IG[i][j]=num1;
        j++;
    }
    i++;
}
}

bool sorting(features f,features g){
if(f.getcount()<g.getcount())
    return true;
}

void partition_tree::check_inserted_data(bool rate,int loop_count){
features f;
f.insert(0,rate,loop_count);
for(unsigned int i=0;i<data.size();i++){
    if(data[i][loop_count].getindex()==-1)
    {
        insert_data(f,i,loop_count);
    }
    if(data[i][loop_count].getcount()>1000)
    {
        cout<<i<<" "<<loop_count<<endl;
        exit(1);
    }
    }
}
void sortin(vector<features>& a){
    int min=-1,max=-1;
    vector<features> b(a.size());
for(unsigned int i=0;i<a.size();i++){
    if(a[i].getindex()==-1)
        continue;
    if(min==-1 || min>a[i].getcount())
        min=a[i].getcount();
    if(max==-1 || max< a[i].getcount())
        max=a[i].getcount();
}
vector<int> count(max-min+1);
for(int i=0;i<a.size();i++){
    if(a[i].getindex()==-1)
        continue;
    count[a[i].getcount()]++;
}
for(int i=1;i<count.size();i++){
count[i]+=count[i-1];
}
for(int i=0;i<a.size();i++){
    if(a[i].getindex()==-1)
        continue;

    b[count[a[i].getcount()]]=a[i];
    count[a[i].getcount()]--;
}
//cout<<"printing started "<<endl;
for(int i=0;i<a.size();i++)
{
    if(a[i].getindex()!=-1)
    a[i]=b[i];
  //  cout<<a[i].getcount()<<" "<<a[i].getindex()<<endl;
}
//cout<<"printing done "<<endl;

}
pair<int,int> partition_tree::get_best_attribute(){
double max_IG=-1;
pair<int,int> p;
for(int i=0;i<IG.size();i++){
    for(int j=0;j<IG[i].size();j++){
            if(!isin[j])
            continue;
        if(max_IG<IG[i][j])
        {
            max_IG=IG[i][j];

            p=make_pair(i,j);
            if(max_IG==1)
                return p;
        }
    }
}
//ispruning=false;
if(max_IG<0.001 && (!ispruning || max_IG==0))
    p.first=-1;
//cout<<"max_IG is "<<max_IG<<endl;
return p;
}
void partition_tree::printaccuracy(){
cout<<"accuracy is "<<ri<<" "<<le<<endl;
cout<<"right and wrong are "<<rite<<" "<<wrong<<endl;
}
void partition_tree::compute_IG(){
  /*cout<<"started "<<endl;
  //sortin(data[0]);

  //sort(data[0].begin(),data[0].end(),sorting);
  cout<<"printing started "<<endl;
 vector<features> a=data[0];
for(int i=0;i<a.size();i++)
{
    cout<<a[i].getcount()<<" "<<a[i].getindex()<<endl;
}
cout<<"printing done "<<endl;


  cout<<"done "<<endl;
  pair<int,int> p;
  return p;*/
  double max_IG=-1;
  //cout<<"copying "<<endl;
  vector<vector<features> > A(data);
    //cout<<"copied "<<endl;
  for(int i=0;i<A[0].size();i++){
    if(isin[i]==false){
        for(int j=0;j<A.size();j++)
            A[j][i].insert(0,0,-1);

    }
  }
  pair<int,int> p;
  for(int i=0;i<A.size();i++){
        sortin(A[i]);
        int x=0;
        for(int j=0;j<A[i].size()-1;j++){
        cout<<i<<" "<<j<<endl;

            if(A[i][j].getrating()!=A[i][j+1].getrating() &&  A[i][j+1].getindex()!=-1){
                double information_gain=find_information_gain(A,i,j+1);
                int k=j;
                while(A[i][k].getcount()==A[i][k+1].getcount() && k<A[i].size()-1)k++;

               /* bool x=A[i][j].getrating();
                bool y=A[i][j+1].getrating();
                int k=j;
                int count_downward=0;
                while(A[i][k].getrating()==x && k!=0)
                    k--;
                count_downward=j-k;
                int count_upward=0;
                k=j+1;
                while(A[i][k]==y && k<A[i].size())
                    k++;
                count_upward=k-j;
                if(count_upward)*/
                IG[i][A[i][j+1].getindex()]=information_gain;

                information_gain=find_information_gain(A,i,k+1);
                IG[i][A[i][k+1].getindex()]=information_gain;
            }
    }
  }
  //exit(1);
}
void partition_tree::calculate_accuracy(partition_tree* tree,vector<features>& f){
int ri1=0,le1=0,ri2=0,le2=0;
//cout<<"label is "<<tree->label<<endl;
if(tree->left || tree->right){
if(tree->left && word_count>f[tree->word_no].getcount())
        {
            calculate_accuracy(tree->left,f);
            ri1=tree->left->ri;
            le1=tree->left->le;
          //  cout<<"coming left "<<endl;
        }
        else if(tree->left){
            ri1=tree->left->ri;
            le1=tree->left->le;
        }
if(tree->right && word_count<=f[tree->word_no].getcount())
        {
            calculate_accuracy(tree->right,f);
            ri2=tree->right->ri;
            le2=tree->right->le;
         //   cout<<"coming right "<<endl;
        }
        else if(tree->right){
            ri2=tree->right->ri;
            le2=tree->right->le;
        }
        tree->ri=(ri1+ri2);
        tree->le=(le1+le2);
        //cout<<tree->ri<<" "<<tree->le<<endl;
}
    else if(f[0].getrating()==tree->label){
            rite++;
            tree->ri++;
    }
    else{
        wrong++;
        tree->le++;
    }
//    double f=rite;
  //  f/=(rite+wrong);
   // cout<<"right and wrong are "<<rite<<" "<<wrong<<" "<<f<<endl;
}
void partition_tree::make_zero(partition_tree* tree){
if(!tree)
    return;
tree->ri=0;
tree->le=0;
make_zero(tree->left);
make_zero(tree->right);
}
double partition_tree::find_information_gain(vector<vector<features> >& f,int x,int partition){

    double whole_tree_entropy=get_entropy(f,0,f[0].size(),x);
    /*if(isnan(whole_tree_entropy)){
        cout<<"whole tree entropy is nan "<<endl;
        exit(1);
    }
    */
    double first=0,second=0;
    first=get_entropy(f,0,partition,x);
    /*if(isnan(first))
    {
        cout<<"first is nan "<<endl;
        exit(1);
    }
    */
    second=get_entropy(f,partition,data[0].size(),x);
 /*   if(isnan(second))
    {
        cout<<" second is nan "<<endl;
        exit(1);
    }
    */
    int first_count=0,second_count=0;
    for(int i=0;i<partition;i++){
            if(!isin[i])
            continue;
        first_count+=f[x][i].getcount();
    }
    for(int i=partition;i<f[x].size();i++){
        if(!isin[i])
        continue;
        second_count+=f[x][i].getcount();
    }
    if(first_count==0 && second_count==0)
        return 0;
    double final_entropy=((first_count*first)/(first_count+second_count))+((second_count*second)/(first_count+second_count));
    return (whole_tree_entropy-final_entropy);
}
double partition_tree::get_entropy(vector<vector<features> >& f,int start,int end,int x){  //start-end is the range of elements
                                                    //and x is the co-ordinate on which entropy is calculated
    double entropy;
	double total_count=0;
	int i=0;
	entropy=0;
	long positive_count=0;
	long negative_count=0;
	bool isrun=false;
	for(int i=start;i<end;i++){
            if(!isin[i])
            continue;
        if(f[x][i].getrating()){
            positive_count+=f[x][i].getcount();
        }
        else{
            negative_count+=f[x][i].getcount();
        }
	}

	total_count=(positive_count+negative_count);
	if(positive_count==0 || negative_count==0)
		return 0;


	double positive_ratio,negative_ratio;

	positive_ratio=positive_count/total_count;
	negative_ratio=negative_count/total_count;
	entropy=positive_ratio*(log10(positive_ratio)/log10(2))+negative_ratio*(log10(negative_ratio)/log10(2));
	entropy*=-1;
	return entropy;
}

void partition_tree::define_size(int x,int y){
    vector<features> f(y);
    vector<double> c(y,-1);
    for(int j=0;j<x;j++){
        data.push_back(f);
        IG.push_back(c);
    }
  /*  cout<<x<<" "<<y<<endl;
    features *f=new features();
    for(int i=0;i<x;i++){
            vector<features> g;
            vector<double> c;
        for(int j=0;j<y;j++){
            f=new features();
            double *d=new double();
            g.push_back(*f);
            c.push_back(*d);
        }*/
    data.push_back(f);
    IG.push_back(c);
    for(int j=0;j<y;j++){
        isin.push_back(true);
    }
}
void partition_tree::copy_values(partition_tree* a,partition_tree* b){
//a->data=b->data;
cout<<"started "<<endl;
a->define_size(b->data.size(),b->data[0].size());
cout<<"reached "<<endl;
b->data[0][0].copy(b->data,a->data);
cout<<"here no problem "<<endl;
a->IG=b->IG;
cout<<"now real problem is here "<<endl;
a->isin=b->isin;
cout<<"maybe here "<<endl;
}
void partition_tree::assign_most_common_label(partition_tree* tree2){
int false_label=0;
int right_label=0;
for(int i=0;i<data[0].size();i++){
    if(!isin[i])
        continue;
    if(!data[0][i].getrating())
    false_label++;
    else
    right_label++;
}
//cout<<"false labels and right labels are "<<false_label<<" "<<right_label<<endl;
if(false_label<right_label)
    tree2->label=true;
else
    tree2->label=false;
}

void partition_tree::split_tree(partition_tree* tree,partition_tree* tree2){
int no_count=0;
for(int i=0;i<isin.size();i++)
    if(isin[i])
    no_count++;
tree->assign_most_common_label(tree2);
//cout<<"count is "<<no_count<<"and label is "<<tree2->label<<endl;
pair<bool,bool> q=tree->check_whole_one();
//cout<<"reaching first "<<endl;
if(q.first==true){
    tree2->setlabel(q.second);
    tree2->left=NULL;
    tree2->right=NULL;
  //  cout<<"returning "<<endl;
    return;
}

bool retu=true;
for(int i=0;i<isin.size();i++)
{
    if(tree->isin[i])
    {
        retu=false;
        break;
    }
}
//cout<<"reaching second "<<endl;
if(retu)
{
    tree2->left=NULL;
    tree2->right=NULL;
    //cout<<"Returning "<<endl;
    return;
}
no_of_nodes++;
//cout<<"no of nodes is "<<no_of_nodes<<endl;
//cout<<"reaching 2.1 "<<endl;
//cout<<"reaching 2.2 "<<endl;
//copy_values(tree->left,tree);
//cout<<"reaching 2.3 "<<endl;
//copy_values(tree->right,tree);
//cout<<"reaching third "<<endl;
pair<int,int> p=get_best_attribute();
if(p.first==-1)
    {
        tree2->left=NULL;
        tree2->right=NULL;
        return;
    }
int index_x=p.first;
int index_y=p.second;
tree2->word_no=index_x;
tree2->word_count=data[index_x][index_y].getcount();
while(tree2->word_count==0){
    IG[index_x][index_y]=-1;
    p=get_best_attribute();
    index_x=p.first;
    if(p.first==-1)
        {
            tree2->left=NULL;
            tree2->right=NULL;
            return ;
        }
    index_y=p.second;
    tree2->word_no=index_x;
    //cout<<index_x<<" "<<index_y<<endl;

    tree2->word_count=data[index_x][index_y].getcount();
}
//cout<<p.first<<" "<<p.second<<endl;

/*for(int j=0;j<data[0].size();j++){
    if(data[index_x][j].getcount()<data[index_x][index_y].getcount() && tree->right)
       tree->right->isin[j]=false;
    else if(tree->left)
        tree->left->isin[j]=false;
}
cout<<tree->left->IG.size()<<" "<<index_x<<endl;
*/

/*tree->left->IG.erase(tree->left->IG.begin()+index_x);
tree->right->IG.erase(tree->right->IG.begin()+index_x);
tree->left->data.erase(tree->left->data.begin()+index_x);
tree->right->data.erase(tree->right->data.begin()+index_x);
cout<<"reaching here "<<endl;
*/
vector<int> locations;
for(int j=0;j<data[0].size();j++){
    if(data[index_x][j].getcount()>=data[index_x][index_y].getcount())
    {
        tree->isin[j]=false;
        locations.push_back(j);
    }
}
vector<double> c=IG[index_x];
double z;
//z=IG[index_x][index_y];
//IG[index_x][index_y]=-1;
tree->IG.erase(tree->IG.begin()+index_x);
tree2->left=new partition_tree();
split_tree(tree,tree2->left);
for(int i=0;i<locations.size();i++)
{
    tree->isin[locations[i]]=true;
}
locations.clear();
for(int j=0;j<data[0].size();j++){
    if(data[index_x][j].getcount()<data[index_x][index_y].getcount())
    {
        tree->isin[j]=false;
        locations.push_back(j);
    }
}
//(tree->left->IG)=tree->IG;
//(tree->right->IG)=tree->IG;
tree2->right=new partition_tree();
split_tree(tree,tree2->right);
//IG[index_x][index_y]=z;
tree->IG.insert(tree->IG.begin()+index_x,c);
for(int i=0;i<locations.size();i++){
    tree->isin[locations[i]]=true;
}


}

void partition_tree::setlabel(bool a){
    label=a;
}

pair<bool,bool> partition_tree::check_whole_one(){
bool x;
x=data[0][0].getrating();
//cout<<"size of data is "<<data[0].size()<<endl;
for(int i=0;i<data[0].size();i++)
{
    if(isin[i]==false)
        continue;

    if(data[0][i].getrating()!=x){
        pair<bool,bool> p;
        p.first=false;
        return p;
    }
}
pair<bool,bool> p;
p.first=true;
p.second=x;
return p;
}

void partition_tree::print(){

for(int i=0;i<data.size();i++){
    for(int j=0;j<data[i].size();j++){
        cout<<data[i][j].getcount()<<" ";

 }
}
}
void partition_tree::print(int i){
int count=0;

for(int j=0;j<data[i].size();j++)
    cout<<data[i][j].getcount()<<" ";
       cout<<endl;
    cout<<i<<" "<<count<<endl;

}
