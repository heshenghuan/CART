/*********************************************************************
* Classification and Regression Tree (CART) V1.0
* Implemented by heshenghuan (heshenghuan999@163.com)
* Last updated on 2015-09-09
**********************************************************************/

#include"CART.h"

CART::CART()
{
	tree_id = 0;
}

CART::~CART()
{
}

void CART::save_model(string model_file)
{
	cout<<"Saving model..."<<endl;
	ofstream fout(model_file.c_str());
	fout<<feat_set_size<<" "<<class_set_size<<endl;
	for(int j = 0;j < tree.size(); j++)
	{
		fout<<tree[j].leaf<<" "<<tree[j].left_child<<" "
			<<tree[j].right_child<<" "<<tree[j].id<<" "
			<<tree[j].j<<" "<<tree[j].s<<" "<<tree[j].c<<endl;
	}
	fout.close();
}

void CART::load_model(string model_file)
{
	cout<<"Loading model..."<<endl;
	tree.clear();
	tree_id = 0;
	ifstream fin(model_file.c_str());
	if(!fin)
	{
		cerr<<"Error opening file: "<<model_file<<endl;
	}
	string line_str;
	getline(fin, line_str);
	vector<string> first_line_vec = string_split(line_str, " ");
	feat_set_size = (int)atoi(first_line_vec[0].c_str());
	class_set_size = (int)atoi(first_line_vec[1].c_str());
	while(getline(fin, line_str))
	{
		vector<string> line_vec = string_split(line_str, " ");
		if(line_vec.size() != 7)
		{
			cerr<<"Error reading model data: "<<line_str<<endl;
			exit(0);
		}
		node p = node();
		p.leaf = (int)atoi(line_vec[0].c_str());
		p.left_child = (int)atoi(line_vec[1].c_str());
		p.right_child = (int)atoi(line_vec[2].c_str());
		p.id = (int)atoi(line_vec[3].c_str());
		p.j = (int)atoi(line_vec[4].c_str());
		p.s = (float)atof(line_vec[5].c_str());
		p.c = (float)atof(line_vec[6].c_str());
		tree.push_back(p);
	}
	fin.close();
	tree_id = tree.size();
}

void CART::load_training_data(string training_file)
{
	cout<<"Loading training data..."<<endl;
	read_samp_file(training_file, samp_feat_vec, samp_class_vec);
	feat_set_size = 0;
	class_set_size = 0;
	for(size_t i = 0; i < samp_class_vec.size(); i++)
	{
		if(samp_class_vec[i] > class_set_size)
			class_set_size = samp_class_vec[i];
		if(samp_feat_vec[i].id_vec.back() > feat_set_size)
			feat_set_size = samp_feat_vec[i].id_vec.back();
	}
}

void CART::learn(int tree_type)
{
	if(tree_type == 1)
		create_classification_tree();
	else
		create_regression_tree();
}

void CART::read_samp_file(string samp_file, vector<sparse_feat> &samp_feat_vec, vector<float> &samp_class_vec)
{
	ifstream fin(samp_file.c_str());
	if(!fin)
	{
		cerr<<"Error opening file: "<<samp_file<<endl;
		exit(0);
	}
	string line_str;
	while (getline(fin, line_str))
	{
		size_t class_pos = line_str.find_first_of("\t");
		float class_id = atof(line_str.substr(0, class_pos).c_str());
		samp_class_vec.push_back(class_id);
		string terms_str = line_str.substr(class_pos+1);
		sparse_feat samp_feat;
		if(terms_str!="")
		{
			vector<string> feat_vec = string_split(terms_str, " ");
			for(vector<string>::iterator it = feat_vec.begin(); it !=feat_vec.end(); it++)
			{
				size_t feat_pos = it->find_first_of(":");
				int feat_id = atoi(it->substr(0, feat_pos).c_str());
				float feat_value = (float)atof(it->substr(feat_pos+1).c_str());
				if(feat_value != 0)
				{
					samp_feat.id_vec.push_back(feat_id);
					samp_feat.value_vec.push_back(feat_value);
				}
			}
		}
		samp_feat_vec.push_back(samp_feat);
	}
	fin.close();
}

vector<string> CART::string_split(string terms_str, string splitting_tag)
{
	vector<string> feat_vec;
    size_t term_beg_pos = 0;
    size_t term_end_pos = 0;
    while ((term_end_pos = terms_str.find_first_of(splitting_tag, term_beg_pos)) != string::npos) {
        if (term_end_pos > term_beg_pos) {
            string term_str = terms_str.substr(term_beg_pos, term_end_pos - term_beg_pos);
            feat_vec.push_back(term_str);
        }
        term_beg_pos = term_end_pos + 1;
    }
    if (term_beg_pos < terms_str.size()) {
        string end_str = terms_str.substr(term_beg_pos);
        feat_vec.push_back(end_str);
    }
    return feat_vec;
}

float CART::calc_acc(vector<float> &test_class_vec, vector<float> &pred_class_vec)
{
    size_t len = test_class_vec.size();
    if (len != pred_class_vec.size())
	{
        cerr << "Error: two vectors should have the same lenght." << endl;
        exit(0);
    }
    int err_num = 0;
    for (size_t id = 0; id != len; id++)
	{
        if (test_class_vec[id] != pred_class_vec[id])
            err_num++;
    }
    return 1 - ((float)err_num) / len;
}