#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<cmath>
#include<sstream>
#include<conio.h>
#include<windows.h>
#include"pair.h"
#include"DSU.h"
#include"bits.h"
int Max_Weight=0;//Максимальный вес
#define Weight true
#define INF 2147483647//бесконечность
#define pi 3.1415829//число пи
using namespace std;
void GoToXY (int x,int y){
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};
    SetConsoleCursorPosition(StdOut, coord);
}
int StoI(string S){
	istringstream ss(S);
	int a;
	ss>>a;
	return a;
}
int CheckSize(string name){
	ifstream file;
	file.open(name.c_str());
	int max=0,a;
	string a1;
	while(!file.eof()){
		file>>a1;
		if(a1>="a" && a1<="z"){
			a=int(a1[0])-96;
		}
		else a=StoI(a1);
		if(a>max)max=a;
	}
	file.close();
	return max;
}
class OrGraph{
protected:
	vector<vector<int>> elems;
	size_t size;
public:
	OrGraph(){
		size = 0;
	}
	OrGraph(string name){
		ifstream f,w;
		bool Wflag=false;
		try{
		//флаг ,определяющий  является ли граф взвешенным
			f.open(name.c_str());
			if(f.fail())throw 1;
		}
		catch(int){
			cout<<"File not found"<<endl;
			_getch();
			return;
		};
		string name2="W"+name;
		//Для того чтобы определить граф как взвешенный необходимо
		//создать файл ,который будет отличаться от файла источника
		//на символ "W" и ввести туда последовательно веса
		w.open(name2.c_str());
		if(w.is_open())Wflag=true;
		//если файл найден то помечаем граф как взвешенный
		name2.clear();
		size_t c=0;
		if(!Wflag)c=1;
		//если граф не взвешенный то все значения ребер равны 1
		size=CheckSize(name);
		//Определяет размер графа
		string a,b;
		size_t a1,b1;
		//буферы
		elems.resize(size,vector<int>(size));
		while(!f.eof()){
			try{
				f>>a;
				f>>b;
				if(a.size()>1 || b.size()>1){
					if((a[0] <'0' || a[0] >'9') || (b[0] <'0' || b[0] >'9'))throw 1;
					//в случае если в файле слово а не буква или цифра
				}
			}
			catch(int){
				cout<<"ERROR,File is not corrected!"<<endl;
				_getch();
			};
			if(Wflag){
				//Если граф взвешенный то считываем из
				//файла с весами величину веса
				//и она максимальная,то сохраняем ее
				//значение в Max_Wight
				w>>c;
				if(c>Max_Weight)Max_Weight=c;
			}
			if(a>="a" && a<="z"){
				//если введена буква то переводим ее в цифру
				a1=int(a[0])-96;
			}
			else a1=StoI(a);
			if(b>="a" && b<="z"){
				b1=int(b[0])-96;
			}
			else b1=StoI(b);
			elems[a1-1][b1-1]=c;
		}
		f.close();
		w.close();
	}
	size_t Size(){
		return size;
	}
	vector<int> operator[](size_t i){
		return elems[i];
	}
	void Output(bool Wflag = false){
		HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
		cout<<"    ";
		for(size_t i=0;i<elems.size();i++)cout<<i+1<<" ";
		//рисуем верхнюю границу таблицы
		cout<<endl;
		//cout<<"____";
		for(size_t i=0;i<3*elems.size();i++)cout<<"_";
		//рисуем прямую линию для отделения верхнней границы
		cout<<endl;
		if(Wflag){
			for(size_t i=0;i<elems.size();i++){
			cout<<i+1<<" "<<char(124)<<" ";
			for(size_t j=0;j<elems[i].size();j++){
				if(elems[i][j]>0){
					if(elems[i][j]>Max_Weight-Max_Weight/3)SetConsoleTextAttribute(hndl, FOREGROUND_RED | FOREGROUND_INTENSITY);
					else if(elems[i][j]>Max_Weight-Max_Weight/2)SetConsoleTextAttribute(hndl, FOREGROUND_GREEN| FOREGROUND_RED | FOREGROUND_INTENSITY);
					else SetConsoleTextAttribute(hndl, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}
				cout<<elems[i][j]<<" ";
				SetConsoleTextAttribute(hndl, (WORD)(0 << 4) | 7); 
			}
			cout<<endl;
			}
		}
		else {
			for(size_t i=0;i<elems.size();i++){
				cout<<i+1<<" "<<char(124)<<" ";
				for(size_t j=0;j<elems[i].size();j++){
					cout<<elems[i][j]<<" ";
				}
				cout<<endl;
			}	
		}
		cout<<endl;
	}
	void Create(string name){
		elems.clear();
		ifstream f,w;
		bool Wflag=false;
		f.open(name.c_str());
		try{
		//флаг ,определяющий  является ли граф взвешенным
			f.open(name.c_str());
			if(f.fail())throw 1;
		}
		catch(int){
			cout<<"File not found"<<endl;
			_getch();
			return;
		};
		string name2="W"+name;
		w.open(name2.c_str());
		if(w.is_open())Wflag=true;
		name2.clear();
		size_t c=0;
		if(!w || !Wflag)c=1;
		size=CheckSize(name);
		string a,b;
		size_t a1,b1;
		elems.resize(size,vector<int>(size));
		//vector<vector<int>> elemss((size_x),vector<int> (size_y));
		while(!f.eof()){
			try{
				f>>a;
				f>>b;
				if(a.size()>1 || b.size()>1){
					if((a[0] <'0' || a[0] >'9') || (b[0] <'0' || b[0] >'9'))throw 1;
					//в случае если в файле слово а не буква или цифра
				}
			}
			catch(int){
				cout<<"ERROR,File is not corrected!"<<endl;
				_getch();
			};
			if(Wflag){
				//Если граф взвешенный то считываем из
				//файла с весами величину веса
				//и она максимальная,то сохраняем ее
				//значение в Max_Wight
				w>>c;
				if(c>Max_Weight)Max_Weight=c;
			}
			if(a>="a" && a<="z"){
				//если введена буква то переводим ее в цифру
				a1=int(a[0])-96;
			}
			else a1=StoI(a);
			if(b>="a" && b<="z"){
				b1=int(b[0])-96;
			}
			else b1=StoI(b);
			elems[a1-1][b1-1]=c;
		}
		f.close();
		w.close();
	}
	void PaintGraph(){
		_getch();
		system("cls");
		POINT op;
		//объект для отрисовки точки
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		//Хэндл потока вывода
		HWND hWnd=GetConsoleWindow();
		//Хэндл окна
		HDC hDC=GetDC(hWnd);
		//Хэндл кисти
		double centr_x=100;
		double centr_y=100;
		//условный центр окна
		vector<double> x;
		vector<double> y;
		//вектора для хранения координат точек в системе координат окна
		for(size_t i=0;i<elems.size();i++){
			double x_i=centr_x*sin((2*pi*i)/elems.size())+centr_x;
			double y_i=centr_y*cos((2*pi*i)/elems.size())+centr_y;
			              
			//			 2pi*i
			//x = x0*sin(-----) + x0
			//             n
			x.push_back(x_i);
			y.push_back(y_i);
		}
		for(size_t i=0;i<30;i++)cout<<endl;
		MoveToEx(hDC,4,4,&op);
		SelectObject(hDC, GetStockObject(DC_PEN));
		SetDCPenColor(hDC, RGB(200,0,0));
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		 int c_compr_x=7;//сжатие
		 int c_offset_x=1;//смещение
		int c_compr_y=12;
		//int c_offset_y=ENTER;
		for(size_t i=0;i<elems.size();i++){	
			GoToXY((x[i]/c_compr_x)+c_offset_x,(y[i]/c_compr_y)+0);
			//цикл для вывода номера вершины
			cout<<i+1;
		}
		for(size_t i=0,k=0;i<elems.size();i++){
			Ellipse(hDC,x[i],y[i],x[i]+4,y[i]+4);
			//рисуем эллипс(вершина)
			MoveToEx(hDC,0,0,&op);
			for(size_t j=0;j<elems[i].size();j++,k++){
				if(elems[i][j]){
					if(i==j)Rectangle(hDC,x[i]-3,y[j]-3,x[i]+4,y[j]+4);
					//если точка не является частью ребра то рисуем ее
					//не как эллипс а как квадрат
					else{
						MoveToEx(hDC,x[i],y[i],&op);
						LineTo(hDC,x[j],y[j]);
						LineTo(hDC,x[j],y[j]);
						__DrawArrow(hDC,x[i],y[i],x[j],y[j]);
					}
				}
			}
		}
		ReleaseDC(hWnd,hDC);
	 cin.get();
	}
	protected:	
		int __Angle(int w,int h){
			float fw=w,fh=h,fg=sqrt(fw*fw+fh*fh),fs,fc;
			if(fg==0) return 0;
			fs=fh/fg;fc=fw/fg;
			if(fs>=0) return 180.0*acos(fc)/3.14;
			else return 360.0-180.0*acos(fc)/3.14;
		}
		void __DrawArrow(HDC hdc, int bx, int by, int ex, int ey){
			int ug;
			POINT poly[3];//точьки для рисования стрелки
			double Gug = 150;//поворот стрелки к точке
			double Lstr = 10;//размер
			MoveToEx(hdc,bx,by,0);
			LineTo(hdc,ex,ey);
			ug=__Angle(ex-bx,ey-by);
			ug=ug-Gug;
			poly[0].x=ex;
			poly[0].y=ey;
			poly[1].x=ex+Lstr*cos(ug*pi/180);
			poly[1].y=ey+Lstr*sin(ug*pi/180);  
			ug=ug+2*Gug;
			poly[2].x=ex+Lstr*cos(ug*pi/180);
			poly[2].y=ey+Lstr*sin(ug*pi/180);
			SetPolyFillMode(hdc,WINDING);
			Polygon(hdc,poly,3);
			SetDCPenColor(hdc, RGB(200,0,0));
		}
	
};
class Graph: public OrGraph{
public:
	Graph() : OrGraph(){}
	Graph(string name){
		ifstream f,w;
		bool Wflag=false;
		f.open(name.c_str());
		try{
		//флаг ,определяющий  является ли граф взвешенным
			f.open(name.c_str());
			if(f.fail())throw 1;
		}
		catch(int){
			cout<<"File not found"<<endl;
			_getch();
			return;
		};
		string name2="W"+name;
		w.open(name2.c_str());
		if(w.is_open())Wflag=true;
		name2.clear();
		size_t c=0;
		if(!w || !Wflag)c=1;
		size=CheckSize(name);
		string a,b;
		size_t a1,b1;
		elems.resize(size,vector<int>(size));
		//vector<vector<int>> elemss((size_x),vector<int> (size_y));
		while(!f.eof()){
			try{
				f>>a;
				f>>b;
				if(a.size()>1 || b.size()>1){
					if((a[0] <'0' || a[0] >'9') || (b[0] <'0' || b[0] >'9'))throw 1;
					//в случае если в файле слово а не буква или цифра
				}
			}
			catch(int){
				cout<<"ERROR,File is not corrected!"<<endl;
				_getch();
			};
			if(Wflag){
				w>>c;
				if(c>Max_Weight)Max_Weight=c;
			}
			if(a>="a" && a<="z"){
				a1=int(a[0])-96;
			}
			else a1=StoI(a);
			if(b>="a" && b<="z"){
				b1=int(b[0])-96;
			}
			else b1=StoI(b);
			elems[a1-1][b1-1]=c;
			elems[b1-1][a1-1]=c;
		}
		f.close();
		w.close();
	}
	size_t Size(){
		return size;
	}
	vector<int> operator[](size_t i){
		return elems[i];
	}
	void Create(string name){
		elems.clear();
		ifstream f,w;
		bool Wflag=false;
		f.open(name.c_str());
		try{
		//флаг ,определяющий  является ли граф взвешенным
			f.open(name.c_str());
			if(f.fail())throw 1;
		}
		catch(int){
			cout<<"File not found"<<endl;
			_getch();
			return;
		};
		string name2="W"+name;
		w.open(name2.c_str());
		if(w.is_open())Wflag=true;
		name2.clear();
		size_t c=0;
		if(!w || !Wflag)c=1;
		size=CheckSize(name);
		string a,b;
		size_t a1,b1;
		elems.resize(size,vector<int>(size));
		//vector<vector<int>> elemss((size_x),vector<int> (size_y));
		while(!f.eof()){
			try{
				f>>a;
				f>>b;
				if(a.size()>1 || b.size()>1){
					if((a[0] <'0' || a[0] >'9') || (b[0] <'0' || b[0] >'9'))throw 1;
					//в случае если в файле слово а не буква или цифра
				}
			}
			catch(int){
				cout<<"ERROR,File is not corrected!"<<endl;
				_getch();
			};
			if(Wflag){
				w>>c;
				if(c>Max_Weight)Max_Weight=c;
			}
			if(a>="a" && a<="z"){
				a1=int(a[0])-96;
			}
			else a1=StoI(a);
			if(b>="a" && b<="z"){
				b1=int(b[0])-96;
			}
			else b1=StoI(b);
			elems[a1-1][b1-1]=c;
			elems[b1-1][a1-1]=c;
		}
		f.close();
		w.close();
	}
	void PaintGraph(){
		_getch();
		system("cls");
		POINT op;
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		HWND hWnd=GetConsoleWindow();
		HDC hDC=GetDC(hWnd);
		double centr_x=100;
		double centr_y=100;
		vector<double> x;
		vector<double> y;
		for(size_t i=0;i<elems.size();i++){
			double x_i=centr_x*sin((2*pi*i)/elems.size())+centr_x;
			double y_i=centr_y*cos((2*pi*i)/elems.size())+centr_y;
			x.push_back(x_i);
			y.push_back(y_i);
		}
		for(size_t i=0;i<30;i++)cout<<endl;
		MoveToEx(hDC,4,4,&op);
		SelectObject(hDC, GetStockObject(DC_PEN));
		SetDCPenColor(hDC, RGB(200,0,0));
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		 int c_compr_x=7;//сжатие
		 int c_offset_x=1;//смещение
		int c_compr_y=12;
		//int c_offset_y=ENTER;
		for(size_t i=0;i<elems.size();i++){	
			GoToXY((x[i]/c_compr_x)+c_offset_x,(y[i]/c_compr_y)+0);
			cout<<i+1;
		}
		for(size_t i=0,k=0;i<elems.size();i++){
			Ellipse(hDC,x[i],y[i],x[i]+4,y[i]+4);
			MoveToEx(hDC,0,0,&op);
			for(size_t j=0;j<elems[i].size();j++,k++){
				if(elems[i][j]){
					if(i==j)Rectangle(hDC,x[i]-3,y[j]-3,x[i]+4,y[j]+4);
					else{
						MoveToEx(hDC,x[i],y[i],&op);
						LineTo(hDC,x[j],y[j]);
						LineTo(hDC,x[j],y[j]);
					}
				}
			}
		}
		ReleaseDC(hWnd,hDC);
	 cin.get();
	}
	void PaintGraph(vector<Pair<int,int>> path){
			_getch();
			system("cls");
			POINT op;
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			HWND hWnd=GetConsoleWindow();
			HDC hDC=GetDC(hWnd);
			double centr_x=100;
			double centr_y=100;
			vector<double> x;
			vector<double> y;
			for(size_t i=0;i<elems.size();i++){
				double x_i=centr_x*sin((2*pi*i)/elems.size())+centr_x;
				double y_i=centr_y*cos((2*pi*i)/elems.size())+centr_y;
				x.push_back(x_i);
				y.push_back(y_i);
			}
			for(size_t i=0;i<30;i++)cout<<endl;
			MoveToEx(hDC,4,4,&op);
			SelectObject(hDC, GetStockObject(DC_PEN));
			SetDCPenColor(hDC, RGB(230,0,0));
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			 int c_compr_x=7;//сжатие
			 int c_offset_x=1;//смещение
			int c_compr_y=12;
		//int c_offset_y=ENTER;
			for(size_t i=0;i<elems.size();i++){	
				GoToXY((x[i]/c_compr_x)+c_offset_x,(y[i]/c_compr_y)+0);
				cout<<i+1;
			}
			for(size_t i=0,k=0;i<elems.size();i++){
				Ellipse(hDC,x[i],y[i],x[i]+4,y[i]+4);
				MoveToEx(hDC,0,0,&op);
				for(size_t j=0;j<elems[i].size();j++,k++){
					if(elems[i][j]){
						if(i==j)Rectangle(hDC,x[i]-3,y[j]-3,x[i]+4,y[j]+4);
						else{
							MoveToEx(hDC,x[i],y[i],&op);
							LineTo(hDC,x[j],y[j]);
							LineTo(hDC,x[j],y[j]);
						}
					}
				}
			}
			for(size_t k=0;k<path.size();k++){
				SetDCPenColor(hDC, RGB(0,150,150));
			//for(size_t m=0,i=0,j=0;m<path[k].size()-1;m++){
				int i = path[k].first;
				int j = path[k].second;
				if(i==j)Rectangle(hDC,x[i]-3,y[j]-3,x[i]+4,y[j]+4);
					else{
						MoveToEx(hDC,x[i],y[i],&op);
						LineTo(hDC,x[j],y[j]);
						LineTo(hDC,x[j],y[j]);	
					}
			//	int i=path[k][path[k].size()-1];
			//	int j=path[k][0];
				MoveToEx(hDC,x[i],y[i],&op);
				LineTo(hDC,x[j],y[j]);
				LineTo(hDC,x[j],y[j]);
			}
		ReleaseDC(hWnd,hDC);
		cin.get();
		}

};