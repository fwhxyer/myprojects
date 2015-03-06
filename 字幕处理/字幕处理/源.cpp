#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<string>
#include<map>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
//powered by fwhxyer

string path="C:\\Users\\WayneFan\\Desktop\\";
string patht="C:\\Users\\WayneFan\\Desktop\\";
string namesource="1";
string name="1";
int namecount=1;
bool userbreak=0;
bool usercheck1=0;//for all text check
bool usercheck2=0;//for all text check

int main(){
	ifstream fin,tfout;
	ofstream fout;
	stringstream ss;
	ss<<path;
	ss<<namecount++;
	ss<<"fixed.txt";
	ss>>patht;
	tfout.open(patht);
	while (tfout) {
		ss.clear();
		ss.sync();
		ss<<path;
		ss<<namecount++;
		ss<<"fixed.txt";
		patht.clear();
		ss>>patht;
		tfout.close();
		tfout.open(patht);
	};
	fout.open(patht);
	do{
		fin.open(path+namesource+".txt");
	}while (!fin&&cin>>namesource);
	
	string s1,s2,s3;
	int t=0;
	while (usercheck1&&getline(fin,s1)){
		if (userbreak) cout<<s1<<endl;
		fout<<s1<<endl;
		if (userbreak&&++t%5==0) system("pause");
	}
	while (getline(fin,s1))	if (s1=="[Events]")	break;
	while (getline(fin,s1))	if (s1[0]=='D')	break;
	t=0;
	do{
		int h2=s1.find_first_of('{')-2;
		s2=s1.substr(0,h2);
		if (s2.length()<63) continue;
		s2=s2.substr(63,s2.length()-63);
		while (s2.length()>0&&(int)s2[0]<=255&&(int)s2[0]>=0)
			s2=s2.substr(1,s2.length()-1);
		while (s2.length()>0&&(int)s2[s2.length()-1]<=255&&(int)s2[s2.length()-1]>=0)
			s2=s2.substr(0,s2.length()-1);
		if (s1.substr(s1.length()-4,4)=="{\\r}") s3=s1.substr(0,s1.length()-4);
		else s3=s1;
		int t3=s3.find_last_of('}')+1;
		if (t3==0&&s1.length()!=0) continue;
		s3=s3.substr(t3,s3.length()-t3);
		
		if (usercheck2) cout<<endl;
		fout<<endl;
		if (usercheck2) cout<<s3<<endl;
		fout<<s3<<endl;
		if (usercheck2) cout<<s2<<endl;
		fout<<s2<<endl;

		if (usercheck2&&++t%5==0) system("pause");
	}while (getline(fin,s1));

	fin.close();
	fout.close();

	cout<<"successed!\n";
	if (usercheck2)	system("pause");

	return 0;
}