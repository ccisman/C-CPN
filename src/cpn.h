#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<stack>
#include<sstream>

//CPN structure

#include"tree.h"
using namespace std;

//const string colorset[] = { "int","char","float","double","short","long" };

extern bool execute_flag;

class Arc
{
public:
	
	static int total_num;

	string source;
	string target;
	string V;
	int id_num;
	int sourceNum = 0;
	int targetNum = 0;
	bool sourceP;
	int type;

	Arc(string s, string t, string v, bool s_P);
};


class Place
{
public:
	int id_num;
	static int total_num;
	string name;
	string v_name;
	string str;
	int token_num;
	string colorset_tag;
	int *num;
	int n_num;
	double *decimal;
	int n_decimal;
	bool controlP;
	bool ispoint;
	bool is_goto;
	string goto_label;

	vector<string> false_exit;

	vector<string> enter;
	vector<string> exit;
	vector<string> enter_P;
	vector<string> control_T;
	vector<string> call_P;
	vector<string> label_after_P;
	string fun_P;
	bool global;
	string pre_executed_P;

public:
	Place(string n, string v_n, string colorset_t, bool c_P);
	void set_Place_value(int num);
	void set_Place_value(double decimal);
	void set_Place_value(string str);
};

class Transition
{
public:
	
	static int total_num;

	string name;
	string booleanExpression;
	string v_Expression;

	int id_num;
	int current_P_num;
	bool controlT;

	Transition(string n, bool c_T, int current_P_num);
	void set_C_Transition_value(string str);
	void set_V_Transition_value(string str);
};

class C_Petri
{
public:
	int p_num;
	int t_num;
	int arcnum;


	vector<Place> place;
	vector<Transition> transition;
	vector<Arc> arc;


public:
	C_Petri();
	void operator=(C_Petri p1)
	{
		arc = p1.arc;
		arcnum = p1.arcnum;
		place = p1.place;
		p_num = p1.p_num;
		transition = p1.transition;
		t_num = p1.t_num;
	}
	void Add_Place(Place p);
	void Add_Place(string name, string v_name, string colorset_tag, bool controlP, bool t, int n, double dec, string s, int array_size, bool ispoint);//t=true表示有初始值


	void Add_Transition(Transition t);
	void Add_Transition(string name, bool controlT, string s, int current_P_num);


	void Add_Arc(Arc a);
	void Add_Arc(string source, string target, string V, bool sourceP);

	string find_place(string t_name, string V);

	bool Add_Place_enter(string name, string s);
	bool Add_Place_enter(string name, vector<string> s);
	bool Add_Place_exit(string name, string s);
	bool Add_Place_exit(string name, vector<string> s);
	//	bool Add_Place_controlT(string name, vector<string> s);
	bool is_enable(string t);
	bool guard(string booleanExpression, string T); 
	//bool guard_process(string booleanExpression, string T);
	string Delete_Arc(int i);
	string Delete_Arc(string source, string target);
	void Change_Arc(int i, string source, string target, string V, bool sourceP);
	void delete_all_connected_arc(string place);

	vector<string> get_enter(string name);
	vector<string> get_exit(string name);

	//	vector<string> get_controlT(string name);
	vector<string> enable_T(); 
	vector<string> find_all_place(string t_name);

	int get_current_P_num(string T);
	void set_point_flag(string p_name);
	bool get_point_flag(string p_name);
	void set_false_exit(string p_name, vector<string> false_exit);
	vector<string> get_false_exit(string p_name);
	void set_enter_P(string p_name, vector<string> enter_P);
	vector<string> get_enter_P(string p_name);
	void set_control_T(string p_name, vector<string> control_T);
	vector<string> get_control_T(string p_name);
	void clear_enter(string p_name);
	void set_arc_type(string source, string target, int type);
	int get_arc_type(string source, string target);
	void add_call_P(string p_name, string call_P);
	vector<string> get_call_P(string p_name);
	void set_fun_P(string p_name, string fun_P);
	string get_fun_P(string p_name);
	void set_global(string p_name);
	bool get_global(string p_name);
	void set_pre_executed_P(string p_name, string pre_executed_P);
	string get_pre_executed_P(string p_name);
	void add_label_P(string p_name, string call_P);
	vector<string> get_label_P(string p_name);
	void release();
};


string find_P_name(C_Petri petri, string v_name);
string find_T_name(C_Petri petri, string v_name);
double change_and_cal(string s, vector<Place> place, int current);

C_Petri slice(C_Petri &petri, vector<string> change_places);

int string_replace(string &s1, const string &s2, const string &s3);

void SplitString(const string& s, vector<string>& v, const string& c);

void splitExpression(string &s, vector<string>& v);

void ast_to_cpn(C_Petri &petri, gtree *p, int addition);

void reset_gen_cpn();

void process_label(C_Petri &petri);

string find_P_name(C_Petri petri, string v_name);

string find_P_name_1(C_Petri petri, string v_name, int current);

void readGraph(string input, string output);

void makeGraph(string inputname, string outputname);

void intofile(C_Petri petri);

void create_CPN(C_Petri &petri, gtree *tree);

void output_CPN(C_Petri petri, string filePrefix);