/*********************************************************************
* Classification and Regression Tree (CART) V1.0
* Implemented by heshenghuan (heshenghuan999@163.com)
* Last updated on 2015-09-09
**********************************************************************/

#pragma once

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<math.h>

#define VERSION			"V1.0"
#define VERSION_DATE	"2015-09-09"

using namespace std;

struct sparse_feat
{
	vector<int> id_vec;
	vector<float> value_vec; 
};

struct node
{
	int leaf;
    int left_child;
    int right_child;
    int id;
    int j;      //the splitting variable, jth feat of feat_vec
    float s;    //the splitting point, valut of jth feat
    float c;    //the output value
};

class CART
{
protected:
	vector<sparse_feat> samp_feat_vec;
	vector<float> samp_class_vec;
	int feat_set_size;
	int class_set_size;
	vector<node> tree;
	int tree_id;

public:
	CART();
	~CART();
	void save_model(string model_file);
	void load_model(string model_file);
	void load_training_data(string training_file);
	void learn(int tree_type);
	vector<float> predict_vari_regression(sparse_feat samp_feat);
	vector<float> predict_class_classification(sparse_feat samp_feat);
	float predict_test_data(string test_file, string output_file, int tree_type);

protected:
	vector<string> string_split(string terms_str, string splitting_tag);
	void read_samp_file(string samp_file, vector<sparse_feat> &samp_feat_vec, vector<float> &samp_class_vec);
	float calc_acc(vector<float> &true_class_vec, vector<float> &pred_class_vec);
	void create_regression_tree();
	void create_classification_tree();
	void pruning_regression_tree();
	void pruning_classification_tree();
};