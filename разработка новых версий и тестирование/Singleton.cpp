template <class T>
class Singleton {
 static Singleton* _self; 
protected: 
 Singleton(){} 
public:
 static Singleton* Create() {
  if (!_self) _self = new Singleton();
  return _self;
 }
 //методы 
 void Set(T x){
	 Data = x;
	 }
 T& Get(){
	 return Data;
	 }
 T Clone(){
	 return Data;
	 }
 //данные
 T Data;
};
template <class T>
Singleton<T>* Singleton<T>::_self=0; 
void main(){
	Singleton<int>* a = Singleton<int>::Create();
	a->Set(6);
	Singleton<int>* b = Singleton<int>::Create();
	b->Set(5);
	int c = b->Clone();
	int d = b->Get();
	c = 7;
	d = 8;

	

	}