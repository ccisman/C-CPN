#include"product.h"
#define FILE_BUFFER_LENGTH 30000
#include <fstream>

/******************************Global_fucntions*********************************/
bool judgeF(string s)//
{
	int pos = int(s.find("<="));
	if (pos == string::npos)
	{
		return true;           
	}
	else return false;        
}

/*
int convert(RG rg, C_Petri ptnet, int i, int j)//rgnode[i].m[j]
{
	int x = 0;
	int sum1 = 0;
	int sum2 = 0;

	for (int ii = 0; ii < ptnet.m; ii++)
	{
		sum1 += ptnet.place[j].solution[ii] * rg.rgnode[0].m[ii];
		//cout << "ptnet.place["<<j<<"].solution["<<ii<<"]: " << ptnet.place[j].solution[ii]<<endl;
		//cout << "rg.rgnode[0].m[" << ii << "]: " << rg.rgnode[0].m[ii] << endl;
	}
	//cout << "sum1:" << sum1 << endl;
	for (int jj = 0; jj < ptnet.m; jj++)
	{
		if (jj == j)
			continue;
		else
			sum2 += ptnet.place[j].solution[jj] * rg.rgnode[i].m[jj];
	}
	//cout << "sum2:" << sum2 << endl;
	x = (sum1 - sum2) / ptnet.place[j].solution[j];

	return x;
}*/



int sumtoken(C_Petri ptnet, RG rg, string s, int statenum)//
{
	int sum = 0;
	while (1)
	{
		int pos = int(s.find_first_of(","));
		if (pos == string::npos)
			break;
		string subs = s.substr(0, pos);
		//	cout<<"   "<<subs<<" ";
		for (int i = 0; i < int(rg.petri.place.size()); i++)
		{
			if (subs == rg.petri.place[i].name)
			{

				sum += rg.rgnode[statenum].m[i].token_num;
				break;
			}
		}
		s = s.substr(pos + 1, s.length() - pos);
	}
	return sum;
}

bool handleFLTLF(C_Petri ptnet, RG rg, string s, int statenum)
{
	int i, j;
	if (s[0] == '!')
	{

		s = s.substr(2, s.length() - 1);
		bool flag = true;               
		while (1)
		{
			int pos = int(s.find_first_of(","));
			if (pos < 0)
				break;
			string subs = s.substr(0, pos);
			for (i = 0; i < ptnet.t_num; i++)
			{
				if (ptnet.transition[i].name == subs)
				{
					int idex = ptnet.transition[i].id_num;
			
					for (j = 0; j < rg.rgnode[statenum].enableNum; j++)
					{
						if (idex == rg.rgnode[statenum].isfirable[j])
						{
							break;
						}
					}
					if (j >= rg.rgnode[statenum].enableNum) {
						flag = false;
					}
					break; 
				}
			}
			if (flag == false)
			{
				
				break;
			}

			//cout<<subs<<endl;
			s = s.substr(pos + 1, s.length() - pos);
		}
		return flag;

	}
	else
	{
		s = s.substr(1, s.length() - 1);
		bool flag = false;
		while (1)
		{
			int pos = int(s.find_first_of(","));
			if (pos < 0)break;
			string subs = s.substr(0, pos);

			for (i = 0; i < ptnet.t_num; i++)
			{
				if (ptnet.transition[i].name == subs)
				{
					int idex = ptnet.transition[i].id_num;
					for (j = 0; j < rg.rgnode[statenum].enableNum; j++)
					{
						if (idex == rg.rgnode[i].isfirable[j])
						{
							break;
						}
					}
					if (j >= rg.rgnode[statenum].enableNum) {
						flag = true;
					}
					break; 
				}
			}
			if (flag == true)
			{

				break;
			}
			//cout<<subs<<endl;
			s = s.substr(pos + 1, s.length() - pos);
		}
		return flag;

	}
}
void handleLTLCstep(C_Petri ptnet, RG rg, int &front_sum, int &latter_sum, string s, int statenum)
{
	if (s[0] == 't')
	{
		int pos = int(s.find_first_of("<="));
		string s_tokon = s.substr(12, pos - 13);
		//cout<<" "<<s_tokon<<" ";
		front_sum = sumtoken(ptnet, rg, s_tokon, statenum);

		s = s.substr(pos + 2, s.length() - pos - 2); 

		if (s[0] == 't')
		{
			string s_tokon = s.substr(12, pos - 13);
			latter_sum = sumtoken(ptnet, rg, s_tokon, statenum);

		}
		else
		{
			s = s.substr(0, s.length() - 1);
			latter_sum = atoi(s.c_str());

		}

	}
	else
	{
		
		int pos = int(s.find_first_of("<="));
		string num = s.substr(0, pos);
		front_sum = atoi(num.c_str());
		//	 cout<< " "<<front_sum<<" ";

	
		s = s.substr(pos + 14, s.length() - pos - 15);
		//	 cout<<" "<<s<<" ";
		latter_sum = sumtoken(ptnet, rg, s, statenum);
	}
}
bool handleLTLC(C_Petri ptnet, RG rg, string s, int statenum, ofstream &ofe)
{
	int front_sum, latter_sum;
	if (s[0] == '!')
	{

		s = s.substr(2, s.length() - 2);
	//	cout<<s;
		handleLTLCstep(ptnet, rg, front_sum, latter_sum, s, statenum);
		ofe << "sum of the former:" << front_sum << " sum of the later:" << latter_sum << endl;
		if (front_sum <= latter_sum)
			return true;
		else
			return false;

	}
	else
	{
	
		s = s.substr(1, s.length() - 1);
		handleLTLCstep(ptnet, rg, front_sum, latter_sum, s, statenum);
		ofe << "sum of the former:" << front_sum << " sum of the later:" << latter_sum << endl;
		if (front_sum <= latter_sum)
			return false;
		else
			return true;
	}
}
/****************************Global_fucntions End*******************************/
int cnt, tot, stack_id;
string to_String(int n)
{
	int m = n;
	char s[max_to_string];
	char ss[max_to_string];
	int i = 0, j = 0;
	if (n < 0)
	{
		m = 0 - m;
		j = 1;
		ss[0] = '-';
	}
	while (m > 0)
	{
		s[i++] = m % 10 + '0';
		m /= 10;
	}
	s[i] = '\0';
	i = i - 1;
	while (i >= 0)
	{
		ss[j++] = s[i--];
	}
	ss[j] = '\0';
	return ss;
}

void Product_Automata::getProduct(C_Petri ptnet, RG rg, SBA ba)
{
	int cont;                                
	ofstream outfile("getproduct.txt", ios::out);
	ofstream ofe("islabel.txt", ios::out);
	outfile << endl;
	outfile << "out put the label in BA node:\n";
	for (int i = 0; i < ba.svex_num; i++)
	{
		outfile << "node" << i << "'s label:" << ba.svertics[i].label << endl;
		outfile << "node" << i << "'s isaccept:" << ba.svertics[i].isAccept << endl;
		outfile << "node" << i << "'s isinitial:" << ba.svertics[i].isInitial << endl;


	}
	outfile << endl;
	cont = 1;
	for (int i = 0; i < rg.node_num; i++)
	{
		for (int j = 0; j < ba.svex_num; j++)
		{
			if (isLabel(ptnet, rg, ba, i, j, ofe))                        
			{

				Product N;                                  

				N.BAname_id = j;
				N.RGname_id = i;
				N.pro_id = cont++;                              
				addstatus(N);                              
				outfile << "输出添加的迁移关系：\n";
				addtransitionF(rg, ba, i, j, N, outfile);                
				addtransitionR(rg, ba, i, j, N, outfile);               
				addinitial_status(ba, i, j, N);                  
				addisaccept(ba, j, N);                        
			}
		}
	}
}

void Product_Automata::addstatus(Product n)
{
	status.push_back(n);
}

void Product_Automata::addtransitionF(RG rg, SBA ba, int i, int j, Product n, ofstream &outfile)  
{
	outfile << "添加正向的迁移关系集合" << endl;
	vector<Product>::iterator it_P;    
	SArcNode *pba = new SArcNode;       

	bool flag_v, flag_s;   

	outfile << "N的RGname:" << n.RGname << " N的BAname:" << n.BAname << endl;

	for (it_P = status.begin(); it_P != status.end(); it_P++)
	{
		outfile << "遍历得到的RGname:" << (*it_P).RGname << " BAname:" << (*it_P).BAname << endl;

		int idex = it_P->RGname_id;

	 
		RGNode temprgnode = rg.rgnode[idex];

		flag_v = false;
		for (unsigned int k = 0; k < temprgnode.next.size(); k++)
		{
			if (temprgnode.next[k].num == i)
			{
				flag_v = true;
				break;
			}

		}

 
		idex = it_P->BAname_id;


		pba = ba.svertics[idex].firstarc;
		//cout << "ba.vertics[idex]:"<< ba.vertics[idex].data  << endl;
		while (pba != NULL)
		{
			if (pba->adjvex == j)
			{
				flag_s = true;
				break;
			}
			pba = pba->nextarc;
		}
		if (pba == NULL)
			flag_s = false;


		if (flag_v && flag_s) 
		{
			T t;
			t.s = (*it_P);
			t.e = n;
			transition.push_back(t);
			outfile << " begin id:" << t.s.pro_id << " end id:" << t.e.pro_id << endl;
		}
	}
	outfile << "\n\n\n";
}


void Product_Automata::addtransitionR(RG rg, SBA ba, int i, int j, Product n, ofstream &outfile)   
{
	outfile << "add reverse relationship set" << endl;
	vector<Product>::iterator it_P;   
	SArcNode *pba = new SArcNode;        
	bool flag_v, flag_s;  

	outfile << "N RGname:" << n.RGname << " N BAname:" << n.BAname << endl;

	for (it_P = status.begin(); it_P != status.end(); it_P++)
	{
		outfile << "RGname:" << (*it_P).RGname << " BAname:" << (*it_P).BAname << endl;

		int idex = it_P->RGname_id;
		RGNode temprgnode = rg.rgnode[i];

		flag_v = false;
		for (unsigned int k = 0; k < temprgnode.next.size(); k++)
		{
			if (temprgnode.next[k].num == idex)
			{
				flag_v = true;
				break;
			}

		}



		idex = it_P->BAname_id;

		pba = ba.svertics[j].firstarc;
		//cout << "ba.vertics[idex]:"<< ba.vertics[idex].data  << endl;
		while (pba != NULL)
		{
			if (pba->adjvex == idex)  
			{
				flag_s = true;
				break;
			}
			pba = pba->nextarc;
		}
		if (pba == NULL)
			flag_s = false;


		if (flag_v && flag_s) 
		{
			T t;
			t.s = n;
			t.e = (*it_P);
			transition.push_back(t);
			outfile << " begin id:" << t.s.pro_id << " end id:" << t.e.pro_id << endl;
		}
	}
	outfile << "\n\n\n";
}


void  Product_Automata::addinitial_status(SBA ba, int i, int j, Product n)
{

	if (ba.svertics[j].isInitial  && i == 0)
	{
		initial_status.push_back(n);
	}
}

void  Product_Automata::addisaccept(SBA ba, int i, Product n)
{
	
	bool flag = ba.svertics[i].isAccept;
	if (flag)
	{
		isaccept.push_back(n);
	}
}

bool isLabel(C_Petri ptnet, RG rg, SBA ba, int vi, int sj, ofstream &ofe)
{

	string str = ba.svertics[sj].label;
	if ("" == str)
		return true;
	bool  mark = false; 
	while (1)
	{
		int pos = int(str.find_first_of("&&"));
		ofe << "RG node num:" << vi << " BA node num:" << sj << " BA's label:" << str << endl;
		if (pos == string::npos)
		{
			//cout<<str;
			if (judgeF(str)) 
			{

				mark = handleFLTLF(ptnet, rg, str, vi);
				if (mark == true)
				{
					break;
				}
			}
			else {
				mark = handleLTLC(ptnet, rg, str, vi, ofe);
				if (mark == true)
				{
					break;
				}
			}
			break;
		}

		string subprop = str.substr(0, pos);
		//cout<<subprop<<" ";

		if (judgeF(subprop))
		{ 
			mark = handleFLTLF(ptnet, rg, subprop, vi);
			if (mark == true)
			{
				break;
			}
		}
		else
		{

			mark = handleLTLC(ptnet, rg, subprop, vi, ofe);
			if (mark == true)
			{
				break;
			}
		}
		//cout<<endl;
		str = str.substr(pos + 2, str.length() - pos);
	}

	if (mark == true)
	{

		ofe << "false" << endl << endl;
		return false;
	}

	else 
	{
		ofe << "not false build node" << endl << endl;
		return true;
	}

}

void add(int x, int y, node *edge, int *heads)
{

	edge[++cnt].next = heads[x];
	edge[cnt].to = y;
	heads[x] = cnt;
	return;
}

Product_Automata::Product_Automata()
{

}
void Product_Automata::tarjan(int x, node *edge, int *LOW, int *DFN, int *stack, int *visit, int *heads)
{
	if (result == false)
	{
		return;
	}

	DFN[x] = LOW[x] = ++tot;

	stack[++stack_id] = x;

	visit[x] = 1;

	for (int i = heads[x]; i != -1; i = edge[i].next)
	{

		if (!DFN[edge[i].to]) {

			tarjan(edge[i].to, edge, LOW, DFN, stack, visit, heads);
			if (!result)return;

			LOW[x] = min(LOW[x], LOW[edge[i].to]);

		}

		else if (visit[edge[i].to]) {  

			LOW[x] = min(LOW[x], LOW[edge[i].to]);

		}

	}
	if (LOW[x] == DFN[x] && stack[stack_id] == x)
	{
		visit[stack[stack_id]] = 0;

		stack_id--;
	}
	else if (LOW[x] == DFN[x])

	{
		//cout << "flag****************************";
		vector<int>::iterator it;
		bool flag = false;
		do {
			//cout << stack[stack_id] << " ";

			it = find(isAccept_id.begin(), isAccept_id.end(), stack[stack_id]);

			if (it != isAccept_id.end())
			{
				flag = true;
			}
			visit[stack[stack_id]] = 0;

			stack_id--;

		} while (x != stack[stack_id + 1]);

		if (flag)
		{
			result = false;
		}
		//cout << endl;
	}

	return;

}

void Product_Automata::ModelChecker(C_Petri ptnet, RG rg, SBA ba, string propertyid)
{
	ofstream outfile("transition.txt", ios::out);
	vector<Product>::iterator it_P;      
	vector<T>::iterator it_T;                

	result = true;//
	tot = cnt = stack_id = 0;
	getProduct(ptnet, rg, ba);
	//cout<<"ok \n";
	initate_array();
	int x, y;
	outfile << isaccept.size() << endl;
	outfile << status.size() << endl;
	outfile << transition.size() << endl;
	outfile << endl;
	for (it_P = isaccept.begin(); it_P != isaccept.end(); it_P++)
	{
		//cout << "id:" << (*it_P).id << " BAname:" << (*it_P).BAname << " RGname:" << (*it_P).RGname << endl;
		outfile << it_P->pro_id << endl;
		isAccept_id.push_back(it_P->pro_id);
	}


	for (it_T = transition.begin(); it_T != transition.end(); it_T++)
	{
		x = (*it_T).s.pro_id;
		y = (*it_T).e.pro_id;
		outfile << x << " " << y << endl;

		//cout << "<" << x << "," << y << ">" << endl;
		add(x, y, edge, heads);
	}
	//cout <<"Transition num:" << transition.size() << endl;
	outfile << "initial state node num:" << endl;
	for (it_P = initial_status.begin(); it_P != initial_status.end(); it_P++)
	{
		int t = (*it_P).pro_id;
		outfile << t << endl;

		//cout << t << endl;
		if (!DFN[t])
			tarjan(t, edge, LOW, DFN, stack, visit, heads);
	}
	/*for (int i = 1; i <= 24; i++)
	{
		if (!DFN[i])
			tarjan(i);
	}*/

	string re;
	if (result)
	{
		re = "TRUE";
	}
	else
	{
		re = "FALSE";
	}

	cout << "FORMULA " + propertyid + " " + re << endl;
	cout << "======================================================" << endl;
	initate_array();
	/*delete[] DFN;
	delete[] LOW;
	delete[] stack;
	delete[] visit;
	delete[] edge;
	delete[] heads;*/
	return;
}

void Product_Automata::initate_array()
{
	heads = new int[status.size() + 1];
	DFN = new int[status.size() + 1];
	LOW = new int[status.size() + 1];
	stack = new int[status.size() + 1];
	visit = new int[status.size() + 1];
	edge = new node[transition.size() + 1];
	result = true;
	for (unsigned int i = 0; i < status.size() + 1; i++)
	{
		heads[i] = -1;
		DFN[i] = LOW[i] = stack[i] = visit[i] = 0;
	}

}
Product_Automata::~Product_Automata()
{
	delete[] DFN;
	delete[] LOW;
	delete[] stack;
	delete[] visit;
	delete[] edge;
	delete[] heads;
}
