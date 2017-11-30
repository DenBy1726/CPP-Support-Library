//#include <qstring.h>
#include <string.h>

#ifndef SINGLETON_H
#define SINGLETOH_H
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
	~Singleton()
	{
		delete _self;
	}
	//ìåòîäû 
	void Set(T x){
		Data = x;
	}
	T& Get(){
		return Data;
	}
	T Clone(){
		return Data;
	}
	//äàííûå
	T Data;
};
template <class T>
Singleton<T>* Singleton<T>::_self = 0;
class NullSingleton {
	static NullSingleton* _self;
protected:
	NullSingleton(){}
public:
	~NullSingleton()
	{
		delete _self;
	}
	static NullSingleton* Create() {
		if (!_self) _self = new NullSingleton();
		return _self;
	}
};
NullSingleton* NullSingleton::_self = 0;
#endif
class TextWorker : public NullSingleton
{
public:
	enum Alf{latin = 1,upper = 2,lower = 4,number = 8,cyrilic = 16,character = 32};
private:
	
	const char*createAlphabet(int alphabet)
	{
		char* alphabets = new char[255];
		int size = 0;
		alphabets[0] = '\0';
		int buff = 0;
		if ((alphabet & (latin | upper)) == (latin | upper))
		{
			alphabets = strcat(alphabets, "QWERTYUIOPASDFGHJKLZXCVBNM");
			size += 26;
		}
		if ((alphabet & (latin | lower)) == (latin | lower))
		{
			alphabets = strcat(alphabets, "qwertyuiopasdfghjklzxcvbnm");
			size += 26;
		}
		if ((alphabet & number) == number)
		{
			alphabets = strcat(alphabets, "0123456789");
			size += 10;
		}
		if ((alphabet & (cyrilic | upper)) == (cyrilic | upper))
		{
			alphabets = strcat(alphabets, "ÉÖÓÊÅÍÃØÙÇÕÚİÆÄËÎĞÏÀÂÛÔß×ÑÌÈÒÜÁŞ¨");
			size += 33;
		}
		if ((alphabet & (cyrilic | lower)) == (cyrilic | lower))
		{
			alphabets = strcat(alphabets, "éöóêåíãøùçõúôûâàïğîëäæıÿ÷ñìèòüáş¸");
			size += 33;
		}
		if ((alphabet & (character)) == (character))
		{
			alphabets = strcat(alphabets, " `\n~\r!\a@\0#\t$\v\b%^&*()_+!\"¹;:?_+/|\\.");
			size += 30;
		}
		//	alphabets = strcat(alphabets, '\0');
		realloc(alphabets, size + 1 * sizeof(char));
		return alphabets;
	}
public:
	int numWord(const char* text, const char* tabs,const char* exc)
	{
		int word = 0;
		int size = strlen(text);
		for(size_t i=0;i<size;i++)
		{
			if(strchr(tabs,text[i])!= NULL && strchr(tabs,text[i-1]) == NULL)
			{
				word++;
				if(strchr(exc,text[i])!= NULL && strchr(tabs,text[i-1]) == NULL && strchr(tabs,text[i+1]) == NULL)
				{
					word--;
				}
			}
		}
		if(strchr(tabs,text[size-1]) == NULL)
			word++;
		return word;
	}
	int toNum(char a)
	{
		return a > 47 && a < 58 ? a - 48 : -1;
	}
	long long cutNum(char*& text)
	{
		std::string buff(text);
		const char* alphabet = createAlphabet(Alf::number);
		while (!strchr(alphabet, buff[0]) != NULL && buff.size()!=0)
		{
			if (!strchr(alphabet, buff[0]) != NULL)
			{
				buff.erase(buff.begin());
			}
		}
		long long num = 0;
		while (strchr(alphabet, buff[0]) != NULL && buff.size() != 0)
		{
			if (strchr(alphabet, buff[0]) != NULL)
			{
				num *= 10;
				num += toNum(buff[0]);
				buff.erase(buff.begin());
			}
		}
	//	realloc(text, sizeof(char)* buff.size()+1);
		strcpy(text, buff.c_str());
		text[buff.size()] = '\0';
		delete []alphabet;
		return num;
	}
	char* copy(char* dest,const char* source, int size = 0)
	{
		if (size == 0)
			size = strlen(source);
		for (size_t i = 0; i < size; i++)
		{
			dest[i] = source[i];
		}
		return dest;
	}
	char* ChangeSymbols(int first_start, int first_finish, int second_start, char* text, int len = 0)
	{
		if (len == 0)
			len = strlen(text);
		//int range = second_start < first_start ? -1 : 1;

		for (size_t i = 0; i < len; i++)
		{
			if (text[i] >= first_start && text[i] <= first_finish)
			{
				text[i] -= first_start;
				text[i] += second_start;
			}
		}
		return text;
	}
	char* Reverse(char *src,int size = 0)
	{
		if (size == 0)
			size = strlen(src);
		char* dst = new char[size+1];
		for (int i = size - 1, a = 0; i >= 0; i--, a++)
		{
			dst[a] = src[i];
		}
		dst[size] = '\0';
		return dst;
	}
	char* ToAlphabet(char* text, int alphabet = 63)
	{
		/*char* alphabets = new char[255];
		int size = 0;
		alphabets[0] = '\0';
		int buff = 0;
		if ((alphabet & (latin | upper)) == (latin | upper))
		{
			alphabets = strcat(alphabets, "QWERTYUIOPASDFGHJKLZXCVBNM");
			size += 26;
		}
		if ((alphabet & (latin | lower)) == (latin | lower))
		{
			alphabets = strcat(alphabets, "qwertyuiopasdfghjklzxcvbnm");
			size += 26;
		}
		if ((alphabet & number) == number)
		{
			alphabets = strcat(alphabets, "0123456789");
			size += 10;
		}
		if ((alphabet & (cyrilic | upper)) == (cyrilic | upper))
		{
			alphabets = strcat(alphabets, "ÉÖÓÊÅÍÃØÙÇÕÚİÆÄËÎĞÏÀÂÛÔß×ÑÌÈÒÜÁŞ¨");
			size += 33;
		}
		if ((alphabet & (cyrilic | lower)) == (cyrilic | lower))
		{
			alphabets = strcat(alphabets, "éöóêåíãøùçõúôûâàïğîëäæıÿ÷ñìèòüáş¸");
			size += 33;
		}
		if ((alphabet & (character)) == (character) )
		{
			alphabets = strcat(alphabets, " `\n~\r!\a@\0#\t$\v\b%^&*()_+!\"¹;:?_+/|\\.");
			size += 30;
		}
	//	alphabets = strcat(alphabets, '\0');*/
	//	realloc(alphabets, size + 1 * sizeof(char));
		const char* alphabets = createAlphabet(alphabet);
		char *let = new char;
		char* rez = new char[strlen(text) + 1];
		size_t j = 0;
		for (size_t i = 0; i < strlen(text); i++)
		{
			if (strchr(alphabets, text[i]) != NULL)
			{
				rez[j] = text[i];
				j++;
			}
		}
		rez[j] = '\0';
		rez = (char*)realloc(rez, (j + 1)*sizeof(char));
		delete let;
		delete[]alphabets;
		return rez;
	}
#ifdef BITS_H
	char* CreateShiffre(char*text, int key,int size = 0)
	{
		if (size == 0)
			size = strlen(text);
		//size_t size = strlen(text);
		if (size % 2 != 0)
		{
			text = (char*)realloc(text, (size + 1)*sizeof(char));
			//text[size++] = '0';
			text[++size] = '\0';
		}
		Bits code;
		Bits k(key);
		for (size_t i = 1; i < size; i+=2)
		{
			Bits temp1(text[i - 1]);
			Bits temp2(text[i]);
			code.pushBits(FeistelNetwork(temp1, temp2, k));
			//code.pushBits(Bits('a'));
			//code.pushBits(Bits('b'));
		}
	text = code.to_string();
		return text;
	}
	char* DecryptShiffre(char*text, int key,int size)
	{
	//	size_t size = strlen(text);
		const Bits k(key);
		Bits code;
	//	Bits temp1;
	//	Bits temp2;
		for (int i = size-1; i >0; i-=2)
		{
			Bits temp1(text[i - 1]);
			Bits temp2(text[i]);
			code.pushBits(deFeistelNetwork(temp1, temp2, k));
		}
		//text = Reverse(strdup(code.to_string().c_str()));
		return Reverse(code.to_string(),size);
	//	return text;
	}
	Bits deFeistelNetwork(Bits& b, Bits& a, Bits key)
	{
		Bits temp;
		for (size_t i = 0; i < 16; i++)
		{
			a.xor(b);
			Shake(a, key);
			temp = b;
			b = a;
			a = temp;
		}
		temp.clear();
		temp.pushBits(a);
		temp.pushBits(b);
		return temp;
	}
	Bits FeistelNetwork(Bits& a, Bits& b,	const Bits& key)
	{
		Bits temp;
		for (size_t i = 0; i < 16; i++)
		{
			Shake(a, key);
			a.xor(b);
			temp = b;
			b = a;
			a = temp;
		}
		temp.clear();
		temp.pushBits(a);
		temp.pushBits(b);
		return temp;
	}
	void Shake(Bits& a,const Bits& key)
	{
		for (size_t i = 0; i < a.size() / 2; i++)
		{
			if (key[i])
				a.swap(i, a.size() - i - 1);
		}
	}
#endif
};
/*{
	QString alphabet("1234567890qwertyuiopasdfghjklzxcvbnmASDFGHJKLZXCVBNMQWERTYUIOP");
	for (size_t i = 0; i < text.length(); i++)
	{
		if (alphabet.indexOf(text[i]) < 0)
			text.remove(i, i + 1);
		if (text[i] > 'a' && text[i] < 'z')
		{
			text[i] =  text[i].toLatin1() + 32;
		}
	}
	return text;
}*/