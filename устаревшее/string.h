#include<iostream>
#pragma warning(disable:4996)
using namespace std;
class pSTR{
	char* p;
	size_t len;
public:
	pSTR(){
		p=new char;
		*p='\0';
		len=1;
	}
	pSTR(char*  s){
		len=strlen(s)+1;
		p=new char[len] ;
		*this=s;
	}
	pSTR(int i,char s){
		if(i<0){
			cout<<endl<<"ERROR!(uncorrected index)"<<endl;
			system("pause");
			exit(0);
		}
		len=i+1;
		p=new char [len+1];
		for(int i=0;i<len-1;i++){
			p[i]=s;
		}
		p[len-1]='\0';
	}
	pSTR(const char*  s){
		len=strlen(s)+1;
		p=new char [len];//abc= a-0 b-1 c-2 '\0'-3 l=4
		strcpy(p,s);
		p[len-1]='\0';
	}
	pSTR(const pSTR &s){
		p=new char[s.len];
		strcpy(p,s.p);
		len=s.len;
	}
	~pSTR(){
		delete []p;
		len=0;
	}
	char* str(){
		return p;
	}
	int size(){
		return len-1;
	}
	void push_back(char symbol){
		p=(char*)realloc(p,++len);
		p[len-2]=symbol;
		p[len-1]='\0';
	}
	void pop_back(){
		p=(char*)realloc(p,--len);
		p[len-1]='\0';
	}
	void resize(int i){
		++i;
		if(i<1)return;
		if(i==0)i=1;
		bool pop;
		i>len ? pop=false : pop=true;
		if(pop){
			while(i!=len){
				pop_back();	
			}
		}
		else{
			while(i!=len){
				push_back('\0');
			}
		}
	}
	void resize(int i,char c){
		++i;
		if(i<1)return;
		if(i==0)i=1;
		bool pop;
		i>len ? pop=false : pop=true;
		if(pop){
			while(i!=len){
				pop_back();	
			}
		}
		else{
			while(i!=len){
				push_back(c);
			}
		}
	}
	void clear(){
		this->resize(0);
	}
	bool empty(){
		return (len<1);
	}
	void show(){
		cout<<p;
	}
	void showln(){
		cout<<p<<endl;
	}
	void getline(){
		this->resize(0);
		char c=' ';
		while(true){
			cin.get(c);
			if(c==10)break;
			this->push_back(c);
		}
	}
	void swap(pSTR& str){//меняет содержимое строк
		pSTR temp(str);
		str=*this;
		*this=temp;
	}
	int find(char c){//выводит индекс первого встреченного символа c(-1 в случае если такового нету)
		for(int i=0;i<len-1;i++){
			if(p[i]==c)return i;
		}
		return -1;
	}
	int count(char c){//считает количество символов c
		size_t count=0;
		for(int i=0;i<len-1;i++){
			if(p[i]==c)count++;
		}
		return count;
	}
	int search(const char* pattern){
		for(int i=0,j=0;i<len;i++){
			if(j==strlen(pattern))return i-j;
			if(p[i]==pattern[j])j++;
			else j=0;
		}
		return -1;
	}
	int search(char* pattern){
		for(int i=0,j=0;i<len;i++){
			if(j==strlen(pattern))return i-j;
			if(p[i]==pattern[j])j++;
			else j=0;
		}
		return -1;
	}
	int search(pSTR pattern){
		for(int i=0,j=0;i<len;i++){
			if(j==pattern.len-1)return i-j;
			if(p[i]==pattern[j])j++;
			else j=0;
		}
		return -1;
	}
	pSTR substr(size_t count){
		if(count<0 || count>len-1)count=len-1;
		pSTR temp(1,'0');
		temp.clear();
		for(int i=0;i<count;i++){
			temp.push_back(p[i]);
		}
		return temp;
	}
	pSTR substr(size_t pos,size_t count){
		if(pos<0 || pos>len-1)pos=0;
		if(count<0 || count>len-1)count=len-1;
		pSTR temp(1,'0');
		temp.clear();
		for(int i=pos;i<pos+count;i++){
			temp.push_back(p[i]);
		}
		return temp;
	}
	pSTR operator+(pSTR s){
		pSTR temp(*this);
		temp.resize(s.len+len-2);
		strcat(temp.p,s.p);
		return temp;
	}
	pSTR operator+=(pSTR s){
		this->resize(s.len+len-2);
		strcat(p,s.p);
		return *this;
	}
	pSTR operator+(const char* s){
		pSTR temp(*this);
		temp.resize(len+strlen(s)-1);
		strcat(temp.p,s);
		return temp; 
	}
	pSTR operator+=(const char* s){
		this->resize(strlen(s)+len-1);
		strcat(p,s);
		return *this;
	}
	pSTR operator+(char* s){
		pSTR temp(*this);
		temp.resize(len+strlen(s)-1);
		strcat(temp.p,s);
		return temp; 
	}
	pSTR operator+=(char* s){
		this->resize(strlen(s)+len-1);
		strcat(p,s);
		return *this;
	}
	pSTR operator*(int i){
		pSTR temp(*this);
		int tmp=len-1,tmp2=tmp*i;
		temp.resize(tmp2);
		for(int i=tmp;i<tmp2;){
			for(int j=0;j<tmp;j++,i++){
				temp.p[i]=temp.p[j];
				temp.p[i+1]='\0';
			}
		}
		return temp;
	}	
	pSTR& operator*=(int i){
		int tmp=len-1;
		len=(tmp*i);
		this->resize(len);
		for(int i=tmp;i<len-1;){
			for(int j=0;j<tmp;j++,i++){
				p[i]=p[j];
				p[i+1]='\0';
			}
		}
		return *this;
	}
	pSTR& operator=(char s){
		this->resize(1);
		p[0]=s;
		return *this;
	}
	pSTR& operator=(const char* s){
		this->resize(strlen(s));
		for(int i=0;i<len;i++){
			p[i]=s[i];
		}
		len=strlen(s)+1;
		return *this;
	}
	pSTR& operator=(const pSTR& s){
		len=s.len-1;
		this->resize(len);
		for(int i=0;i<len-1;i++){
			p[i]=s.p[i];
		}
		p[len-1]='\0';
		return *this;
	}
	pSTR operator-(const char& a){
		pSTR temp(*this);
		int temp_len=0,len2;
		len2=len;
		for(int i=0;i<temp.size();i++){
			if(temp.p[i]!=a)temp_len++;
		}
		temp.resize(temp_len);
		for(int i=0,j=0;i<len2;i++){
			if(p[i]!=a)temp.p[j++]=p[i];
		}
		return temp;
	}
	pSTR operator-=(const char& a){
		char* temp=new char[len];
		strcpy(temp,p);
		int temp_len=0,len2;
		len2=len;
		for(int i=0;i<len;i++){
			if(p[i]!=a)temp_len++;
		}
		len=temp_len+1;
		this->resize(len);
		for(int i=0,j=0;i<len2;i++){
			if(temp[i]!=a)p[j++]=temp[i];
		}
		return *this;
	}
	char operator[](int i){
		if(i<0 || i>len-2){
			cout<<endl<<"ERROR!(uncorrected index)"<<endl;
			system("pause");
			exit(0);
		}
		return p[i];
	}
	bool operator==(pSTR& b){
		if(len!=b.len)return false;
		int i=0;
		while(p[i]){
			if(p[i]!=b[i])return false;
			i++;
		}
		return true;
	}
	bool operator==(const char* s){
		if(len!=strlen(s)+1)return false;
		int i=0;
		while(p[i]){
			if(p[i]!=s[i])return false;
			i++;
		}
		return true;
	}
	bool operator==(char* s){
		if(len!=strlen(s)+1)return false;
		int i=0;
		while(p[i]){
			if(p[i]!=s[i])return false;
			i++;
		}
		return true;
	}
	friend pSTR operator+(char*s,pSTR a);
	friend pSTR operator+(const char*s,pSTR a);
};
pSTR operator+(char*s,pSTR a){
		pSTR temp(a);
		temp.resize(a.len+strlen(s)-1);
		strcat(temp.p,s);
		return temp; 
}
pSTR operator+(const char*s,pSTR a){
	pSTR temp(a);
	temp.resize(a.len+strlen(s)-1);
	strcat(temp.p,s);
	return temp; 
}
typedef pSTR string;