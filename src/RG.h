#pragma once

#include "cpn.h"

class M
{
public:
	bool control_P;
	int token_num;
	string color;
	int *n;
	double *dec;
	int n_n;
	int n_dec;
	string s;

public:
	bool operator==(const M m1);
};

class nextNode
{
public:
	int num; 
	string T; 

};

class RGNode
{
public:

	int num; 
	int enableNum; 
	vector<M> m; 
	vector<int> isfirable;  
	vector<nextNode> next; 
	bool end;
};

class RG
{
public:
	int node_num; 
	C_Petri petri;
	vector<RGNode> rgnode; 

public:
	RG(C_Petri petri);
	RG() {};
	void init_RG(C_Petri petri1);
	int create_node(C_Petri petri, vector<string> T);
	void add_next(int node_num, stack<int> &newNode);
	void release();
};

string find_P_name_1(C_Petri petri, string v_name, int current);

int model_check(C_Petri petri, RG rg, string filename);

void xml_trans_C(C_Petri petri, char *filenameC, char *to_file, vector<string> &critera);

void create_RG(RG &rg);

void print_RG(RG rg, string filename);