#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>  
#include<string>
#include<iomanip>
#include<fstream>
#include<stack>
#include<sstream>
#include<vector>
#include<time.h>
#include<io.h>

#include"tree.h"
#include"cpn.h"
#include"RG.h"
//#include"AST_compare.h"


#define keywordNum 20

string rg_dirname = ".\\rg\\";
string rg_sliceOnly_dirname = ".\\rg_sliceOnly\\";
string origin_dirname = "D:\\学习资料\\项目资料\\petri建模\\test7\\";
string newfile_dirname = ".\\newfile\\";

using namespace std;
int tb_num = 0;
int nextnum = 100;//标号(从100开始)
int labelnum = 1;
int labelnum1 = 1;


void SplitString(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}
void splitExpression(string &s, vector<string>& v)//传入字符串和结果集合，将字符串根据>,<等分割并放入结果集
{
	string s1;
	bool flag_shut = false;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == '(' || s[i] == ')')
			continue;
		else if (s[i] == '#')
			flag_shut = true;
		if (s[i] == '<' || s[i] == '>')
		{
			if (s[i + 1] == '=')
				i++;
			
			v.push_back(s1);
			s1.clear();
			flag_shut = false;
		}
		else if (s[i] == '=')
		{
			v.push_back(s1);
			s1.clear();
			flag_shut = false;
		}
		else if (s[i] == '|')
		{
			if (s[i + 1] == '|')
				i++;
			v.push_back(s1);
			s1.clear();
			flag_shut = false;
		}
		else if (s[i] == '&')
		{
			if (s[i + 1] == '&')
				i++;
			v.push_back(s1);
			s1.clear();
			flag_shut = false;
		}
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
		{
			v.push_back(s1);
			s1.clear();
			flag_shut = false;
		}
		else if (s[i] == '!' || s[i] == '=')
		{
			if (s[i + 1] == '=')
				i++;
			//else
				//cout << "出现异常!=或==" << endl;
			v.push_back(s1);
			s1.clear();
			flag_shut = false;
		}
		else if (s[i] == '%')
		{
			v.push_back(s1);
			s1.clear();
			flag_shut = false;
		}
		else if (flag_shut == false)
			s1 = s1 + s[i];
	}

	v.push_back(s1);
}


int string_replace(string &s1, const string &s2, const string &s3)//在s1中找到s2字串，替换成s3
{
	string::size_type pos = 0;
	string::size_type a = s2.size();
	string::size_type b = s3.size();
	while ((pos = s1.find(s2, pos)) != string::npos)
	{
		s1.replace(pos, a, s3);
		pos += b;
	}
	return 0;
}


int find_T_exist(vector<Transition> transition, string s)//找库所中是否有v_name等于s的，并且返回有几个
{
	vector<string> v;
	for (int i = int(transition.size() - 1); i >= 0; i--)
	{
		if (transition[i].booleanExpression == "")
			SplitString(transition[i].v_Expression, v, "#");
		else
			SplitString(transition[i].booleanExpression, v, "#");
		if (v[0] == s)
		{
			if (v.size() == 1)
			{
				return 1;
			}
			else
			{
				return atoi(v[1].c_str()) + 1;

			}
		}
	}
	return 0;
}

void travel_tree(gtree *tree,ofstream &out,vector<pair<string,int>> &list)
{

	if (tree == NULL)
		return;
	string parent_place, child_place;
	int parent_no, child_no;
	if (tree->parent != NULL)
	{
		
		parent_place = tree->parent->place;
		parent_no = tree->parent->num;
		child_place = tree->place;
		child_no = tree->num;
		out << "node" << to_string(parent_no) << "[label=\"" << parent_place << "\"]" << endl;
		out << "node" << to_string(child_no) << "[label=\"" << child_place << "\"]" << endl;
		out << "node" << to_string(parent_no) << "->" << "node" << to_string(child_no) << ";" << endl;

	}
	travel_tree(tree->child, out, list);
	travel_tree(tree->next, out, list);


	//out.close();
}

void intofile_tree(gtree *tree)
{
	ofstream out;
	vector<pair<string,int>> list;
	out.open("tree.dot", ios::out);

	out << "digraph G{" << endl;
	travel_tree(tree, out, list);
	out << "}" << endl;
	out.close();
	
}

void intofile(C_Petri petri)
{
	ofstream out;
	out.open("output.txt", ios::out);
	//out << "Place:" << endl;
	//out << "-----------------------------------" << endl;

	string fillcolor = "chartreuse";
	for (int i = 0; i < petri.p_num; i++)
	{
		if (petri.place[i].controlP == false)
			out << "subgraph cluster_" << petri.place[i].name << "{label=\"" <<
			petri.place[i].v_name << "\"color=\"white\"" << petri.place[i].name <<
			"[shape=circle, style=\"filled\",color=\"black\",fillcolor=\"" << fillcolor << "\"]}" << endl;
		else
		{
			out << petri.place[i].name << "[shape=circle," << "label=\"" << petri.place[i].v_name << "\"]" << endl;
		}
	}
	//out << "-----------------------------------" << endl; 
	//out << "Transition:" << endl;
	//out << "-----------------------------------" << endl;
	for (int i = 0; i < petri.t_num; i++)
	{
		out << petri.transition[i].name << "[shape=box]" << endl;
	}
	//out << "-----------------------------------" << endl;
	//out << "Arc:" << endl;
	//out << "-----------------------------------" << endl;

	for (int i = 0; i < petri.arcnum; i++)
	{
		if (petri.arc[i].V != "#" && petri.arc[i].V != "executed#" && petri.arc[i].V != "executed")//隐式弧
			out << "{" << petri.arc[i].source << "," << petri.arc[i].target << "}" << endl;
		else if (petri.arc[i].V == "executed" || petri.arc[i].V == "relation")
			out << "{" << petri.arc[i].source << "," << petri.arc[i].target << "[style=\"dashed\"]}" << endl;
	}
	out.close();
}


void readGraph(string input, string output) //.txt 转 .dot
{

	const char* in = input.data();
	const char* ou = output.data();

	ifstream fin;
	fin.open(in, ios::in);

	ofstream fout;
	fout.open(ou, ios::out);

	fout << "digraph G{" << endl << "rankdir = LR" << endl;
	string s;
	while (getline(fin, s))
	{
		if (s[0] != '{') {
			fout << s << '\n';
			continue;
		}

		string u, v, lable;
		int n = int(s.length());
		int i = 1;
		//cout << s << n << endl;
		while (s[i] != ',') i++;
		//cout << i << endl;
		u += s.substr(1, i - 1);
		//cout << u << endl;
		int j = n - 2;
		while (s[j] != ',') j--;
		//cout << j << endl;
		v += s.substr(j + 1, n - 1 - j - 1);
		//cout << v << endl;
		//lable = s.substr(i + 1, j - i - 1);

		string edge = "";
		edge += u;
		edge += "->";
		edge += v;
		//edge += "[label=\"";
		//edge += lable;
		//edge += "\"];";
		fout << edge << endl;
	}
	fout << "}" << endl;
	fin.close();
	fout.close();
}

void makeGraph(string inputname, string outputname) //生成png图片
{
	string s = "";
	s += "dot -Tpng ";
	s += inputname;
	s += " -o ";
	s += outputname;
	const char* cmd = s.data();
	const char* iname = inputname.data();
	system(cmd);
}




//evolution部分结束
//********************//
//********************//

bool exist_in(vector<string> v, string s);

void initializing(C_Petri &petri)//初始化petri网，main_begin赋上token，连接main_begin和main_v
{
	///初始给main的token赋值
	for (int i = 0; i < petri.p_num; i++)
	{
		if (petri.place[i].v_name == "main begin")
		{
			petri.place[i].token_num = 1;
			break;
		}
	}

	string main_v = find_P_name(petri, "main_v");
	vector<string> main_exit_T = petri.get_exit(find_P_name(petri, "main begin"));
	for (unsigned int i = 0; i < main_exit_T.size(); i++)
		petri.Add_Arc(main_exit_T[i], main_v, "", false);
}

void initial_changeAnalyse_cpn(C_Petri &petri1, C_Petri &petri, vector<string> change_P, vector<string> change_T, vector<Arc> &change_Arc);

void create_CPN(C_Petri &petri, gtree *tree)
{
	ast_to_cpn(petri, tree, 0);
	process_label(petri);
	initializing(petri);
}

void output_CPN(C_Petri petri, string filePrefix)
{
	intofile(petri);

	readGraph(filePrefix + ".txt", filePrefix + ".dot");
	makeGraph(filePrefix + ".dot", filePrefix + ".png");
}

void onlybuildCPN(gtree *tree, C_Petri &petri)
{
	reset_gen_cpn();

	//************************生成cpn
	create_CPN(petri, tree);

	//************************输出cpn
	output_CPN(petri, "output");
}

void get_names(string dirname, vector<string> &filelist)
{
	struct _finddata_t fa;
	long fHandle;
	if ((fHandle = _findfirst(dirname.c_str(), &fa)) == -1L)//这里可以改成需要的目录 
	{
		printf("当前目录下没有txt文件\n");
		return;
	}
	else
		do
		{
			//if (strstr(fa.name, "new.c") != NULL)
			if (strstr(fa.name, ".c") != NULL)
				filelist.push_back(fa.name);
		} while (_findnext(fHandle, &fa) == 0);

}

vector<string> get_criteria(C_Petri petri,string filename)
{
	vector<string> result;
	string xml = filename;
	xml.replace(xml.find("new.c"), 5, "LTL.xml");

	char xml1[100], xml2[100];
	strcpy(xml1, xml.c_str());
	xml.replace(xml.find("LTL.xml"), 7, "LTL1.xml");
	strcpy(xml2, xml.c_str());

	xml_trans_C(petri, xml1, xml2, result);
	for (int i = 0; i < petri.p_num; i++)
	{
		string temp = petri.place[i].v_name;
		if (temp == "main begin")
		{
			result.push_back(petri.place[i].name);
			break;
		}
	}
	return result;
}

//功能：构建CPN以及生成可达图
//输入：语法树tree
//输出：通过引用形参传出，CPN和可达图
void DirectBuild(gtree *tree, C_Petri &petri, RG &rg)
{
	reset_gen_cpn();

	//************************生成cpn
	create_CPN(petri, tree);

	//************************输出cpn
	output_CPN(petri, "output");

	//************************生成可达图
	vector<string> v;
	//RG rg(petri); //定义可达图
	rg.init_RG(petri);
	create_RG(rg);
	//print_RG(rg, dirname + new_filename);
}

//功能：输出语法树
//输入：源程序名
//输出：将语法树以png图片格式放在tree.png中
void out_tree(string filename)
{
	gtree *tree;
	C_Petri petri;
	RG rg;
	tree = create_tree(filename, false);
	intofile_tree(tree);
	makeGraph("tree.dot", "tree.png");
}

//功能：对CPN切片
//输入：准则criteria，CPN
//输出：返回切片后的CPN
C_Petri slicing(vector<string> criteria,C_Petri petri)
{
	C_Petri petri1;
	petri1 = slice(petri, criteria);
	return petri1;

}

void write_to_txt(fstream &fout, int state_num, int p_num, int t_num, clock_t cpn_time, clock_t rg_time, clock_t mc_time)
{
	
	fout << "可达图节点个数：" << state_num << endl;
	fout << "库所个数:" << p_num << endl;
	fout << "变迁个数:" << t_num << endl;
	fout << "生成PDNet时间：" << cpn_time / 1000.0 << "秒" << endl;
	fout << "生成可达图时间：" << rg_time / 1000.0 << "秒" << endl;
	fout << "模型检测时间：" << mc_time / 1000.0 << "秒" << endl;
	fout << endl;
}

void compare(string filename)
{
	string xml = filename;
	xml.replace(xml.find("new.c"), 5, "LTL1.xml");

	C_Petri petri, petri1, petri2;
	RG rg, rg1, rg2;
	vector<string> criteria;
	clock_t begin, end, cpn_time, rg_time, mc_time;
	fstream fout;
	fout.open("result.txt", ios::out | ios::app);
	fout << "程序：" << filename << endl << endl;
	
	begin = clock();
	gtree *tree = create_tree(filename, true);
	//end = clock();
	//tree_time = end - begin;

	//直接建模

	//begin = clock();
	//DirectBuild(tree, filename, petri, rg);
	onlybuildCPN(tree, petri);
	end = clock();
	cpn_time = end - begin;

	criteria = get_criteria(petri, origin_dirname + filename);

	begin = clock();
	rg.init_RG(petri);
	create_RG(rg);
	end = clock();
	rg_time = end - begin;

	begin = clock();
	model_check(petri, rg, origin_dirname + xml);
	end = clock();
	mc_time = end - begin;


	fout << "直接建模：" << endl;
	write_to_txt(fout, rg.node_num, rg.petri.p_num, rg.petri.t_num, cpn_time,rg_time,mc_time);
	rg.release();

	

	//无执行弧切片
	
	begin = clock();
	execute_flag = false;
	petri1 = slicing(criteria, petri);
	end = clock();
	cpn_time = end - begin;

	begin = clock();
	rg1.init_RG(petri1);
	create_RG(rg1);
	end = clock();
	rg_time = end - begin;

	begin = clock();
	//model_check(petri1, rg1, origin_dirname + xml);
	end = clock();
	mc_time = end - begin;
	
	fout << "普通切片：" << endl;
	write_to_txt(fout, rg1.node_num, rg1.petri.p_num, rg1.petri.t_num, cpn_time, rg_time, mc_time);
	rg1.release();

	//有执行弧切片
	execute_flag = true;
	
	begin = clock();
	petri2 = slicing(criteria, petri);
	end = clock();
	cpn_time = end - begin;

	begin = clock();
	rg2.init_RG(petri2);
	create_RG(rg2);
	end = clock();
	rg_time = end - begin;

	begin = clock();
	model_check(petri2, rg2, origin_dirname + xml);
	end = clock();
	mc_time = end - begin;

	fout << "带执行弧切片：" << endl;
	write_to_txt(fout, rg2.node_num, rg2.petri.p_num, rg2.petri.t_num, cpn_time, rg_time, mc_time);
	rg2.release();

	petri.release();
	fout.close();
}

int main()
{
	
	vector<string> filelist;

	string filename, new_filename;
	
	get_names(origin_dirname + "*", filelist);

	//compare("bor&zero_sum.c", "bor&zero_sum - new.c");
	for (unsigned int i = 0; i < filelist.size(); i++)
	{
		compare(filelist[i]);

	}

}

