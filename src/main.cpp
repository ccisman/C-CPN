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
string origin_dirname = "D:\\ѧϰ����\\��Ŀ����\\petri��ģ\\test7\\";
string newfile_dirname = ".\\newfile\\";

using namespace std;
int tb_num = 0;
int nextnum = 100;//���(��100��ʼ)
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
void splitExpression(string &s, vector<string>& v)//�����ַ����ͽ�����ϣ����ַ�������>,<�ȷָ��������
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
				//cout << "�����쳣!=��==" << endl;
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

int string_replace(string &s1, const string &s2, const string &s3)//��s1���ҵ�s2�ִ����滻��s3
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
		if (petri.arc[i].V != "#" && petri.arc[i].V != "executed#" && petri.arc[i].V != "executed")//��ʽ��
			out << "{" << petri.arc[i].source << "," << petri.arc[i].target << "}" << endl;
		else if (petri.arc[i].V == "executed" || petri.arc[i].V == "relation")
			out << "{" << petri.arc[i].source << "," << petri.arc[i].target << "[style=\"dashed\"]}" << endl;
	}
	out.close();
}

void readGraph(string input, string output) //.txt ת .dot
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

void makeGraph(string inputname, string outputname) //����pngͼƬ
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

void onlybuildCPN(gtree *tree, C_Petri &petri)
{
	reset_gen_cpn();

	//************************����cpn
	create_CPN(petri, tree);

	//************************���cpn
	output_CPN(petri, "output");
}

void get_names(string dirname, vector<string> &filelist)
{
	struct _finddata_t fa;
	long fHandle;
	if ((fHandle = _findfirst(dirname.c_str(), &fa)) == -1L)//������Ըĳ���Ҫ��Ŀ¼ 
	{
		printf("��ǰĿ¼��û��txt�ļ�\n");
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

//���ܣ�����CPN�Լ����ɿɴ�ͼ
//���룺�﷨��tree
//�����ͨ�������βδ�����CPN�Ϳɴ�ͼ
void DirectBuild(gtree *tree, C_Petri &petri, RG &rg)
{
	reset_gen_cpn();

	//************************����cpn
	create_CPN(petri, tree);

	//************************���cpn
	output_CPN(petri, "output");

	//************************���ɿɴ�ͼ
	vector<string> v;
	//RG rg(petri); //����ɴ�ͼ
	rg.init_RG(petri);
	create_RG(rg);
	//print_RG(rg, dirname + new_filename);
}

//���ܣ�����﷨��
//���룺Դ������
//��������﷨����pngͼƬ��ʽ����tree.png��
void out_tree(string filename)
{
	gtree *tree;
	C_Petri petri;
	RG rg;
	tree = create_tree(filename, false);
	intofile_tree(tree);
	makeGraph("tree.dot", "tree.png");
}

//���ܣ���CPN��Ƭ
//���룺׼��criteria��CPN
//�����������Ƭ���CPN
C_Petri slicing(vector<string> criteria,C_Petri petri)
{
	C_Petri petri1;
	petri1 = slice(petri, criteria);
	return petri1;

}

void write_to_txt(fstream &fout, int state_num, int p_num, int t_num, clock_t cpn_time, clock_t rg_time, clock_t mc_time)
{
	
	fout << "�ɴ�ͼ�ڵ������" << state_num << endl;
	fout << "��������:" << p_num << endl;
	fout << "��Ǩ����:" << t_num << endl;
	fout << "����PDNetʱ�䣺" << cpn_time / 1000.0 << "��" << endl;
	fout << "���ɿɴ�ͼʱ�䣺" << rg_time / 1000.0 << "��" << endl;
	fout << "ģ�ͼ��ʱ�䣺" << mc_time / 1000.0 << "��" << endl;
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
	fout << "����" << filename << endl << endl;
	
	begin = clock();
	gtree *tree = create_tree(filename, true);
	//end = clock();
	//tree_time = end - begin;

	//ֱ�ӽ�ģ

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


	fout << "ֱ�ӽ�ģ��" << endl;
	write_to_txt(fout, rg.node_num, rg.petri.p_num, rg.petri.t_num, cpn_time,rg_time,mc_time);
	rg.release();

	

	//��ִ�л���Ƭ
	
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
	
	fout << "��ͨ��Ƭ��" << endl;
	write_to_txt(fout, rg1.node_num, rg1.petri.p_num, rg1.petri.t_num, cpn_time, rg_time, mc_time);
	rg1.release();

	//��ִ�л���Ƭ
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

	fout << "��ִ�л���Ƭ��" << endl;
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

