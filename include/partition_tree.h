#ifndef PARTITION_TREE_H
#define PARTITION_TREE_H

#include <vector>
#include <utility>
#include "features.h"



class partition_tree
{
    public:
        partition_tree();
        partition_tree *left,*right;
        void insert_data(std::vector<std::vector<features> >&);
        void insert_data(std::vector<features>&,int);
        void insert_data(features,int,int);
        void print();
        void print(int);
        void split_tree(partition_tree*,partition_tree*);
        features get_data(int,int);
        virtual ~partition_tree();
        void define_size(int,int);
        std::pair<bool,bool> check_whole_one();
        void setlabel(bool);
        void check_inserted_data(bool,int);

        double get_entropy(std::vector<std::vector<features> >&,int,int,int);
        double find_information_gain(std::vector<std::vector<features> >&,int,int);
        void compute_IG();
        std::pair<int,int> get_best_attribute();
        void copy_values(partition_tree*,partition_tree*);
        void print_data();
        void read_data();
        void make_zero(partition_tree*);
        bool ispruning;
        void assign_most_common_label(partition_tree*);
        void calculate_accuracy(partition_tree*,std::vector<features>&);
        void pruning_tree(partition_tree*,partition_tree*,std::vector<int>&);
        void calculate(partition_tree*,std::vector<int>&);
        void printaccuracy();
        void make_accuracy();
        int ri,le;
    protected:
    private:
        std::vector<std::vector<features> > data;
        std::vector<bool> isin;
        std::vector<std::vector<double> > IG;
        bool label;
        int word_no;
        int word_count;

};

#endif // PARTITION_TREE_H
