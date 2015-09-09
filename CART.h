/************************************************************
* Classification and Regression Tree (CART) V1.0
* Implemented by heshenghuan (heshenghuan999@163.com)
* Last updated on 2015-09-09
*************************************************************/

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
    int id;
    int j;      //the splitting variable, jth feat of feat_vec
    float s;    //the splitting point, valut of jth feat
    float c;    //the output value
	int leaf;
    int left_child;
    int right_child;
};

class CART
{
protected:
	vector<sparse_feat> samp_feat_vec;
	vector<float> samp_class_vec;
	int feat_set_size;
	int class_set_size;
	vector<node> tree;
};
