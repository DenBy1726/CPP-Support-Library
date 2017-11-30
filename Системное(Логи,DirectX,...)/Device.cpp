/*02.02.2017 22:13
Обертка над DirectX
*/
#pragma once
#include "dinput.h"
#include <vector>
#include <string>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "comctl32.lib")

//Статический класс для получения данных текущего приложения
static class Application
{

public:

	//получает объект HInstance данного приложения
	static HINSTANCE ThisInstance()
	{
		return GetModuleHandle(NULL);
	}

	//получает окно данного приложения если таковое имеется,иначе NULL
	static HWND ThisWindow()
	{
		HWND _ThisWindow;
			EnumWindows(EnumWndProc, (LPARAM)&_ThisWindow);
		return _ThisWindow;
	}

private:
	static BOOL CALLBACK EnumWndProc(HWND hwnd, LPARAM lParam)
	{
		if (GetWindowThreadProcessId(hwnd, NULL) == GetCurrentThreadId())
		{
			*(HWND*)lParam = hwnd;
			return FALSE;
		}

		return TRUE;
	}
};



//Главный COM-интерфейс DirectInput 8. Все другие интерфейсы наследуются через него
class Device
{
protected:
	IDirectInput8* pDI;

	static BOOL ReadDevice(IDirectInputDevice8 *pDDevice,
		void *DataBuffer, long BufferSize)
	{
		HRESULT hr;

		while (1) {
			// Опрос устройства
			pDDevice->Poll();

			// Чтение состояния
			if (SUCCEEDED(hr = pDDevice->GetDeviceState(BufferSize,
				(LPVOID)DataBuffer)))
				break;

			// Возвращаем нераспознанную ошибку
			if (hr != DIERR_INPUTLOST && hr != DIERR_NOTACQUIRED)
				return FALSE;

			// Вновь захватываем устойство и пытаемся
			// получить данные еще раз
			if (FAILED(pDDevice->Acquire()))
				return FALSE;
		}
		// Сообщаем об успехе
		return TRUE;
	}

public:
	Device()
	{
		HINSTANCE hInst = Application::ThisInstance();
		DirectInput8Create(hInst, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&pDI, NULL);
	}
	//получить IDirectInput8*
	IDirectInput8* GetObject()
	{
		return pDI;
	}
	virtual IDirectInputDevice8* GetDevice() = 0;
	//для каждого вида устройства,задданного вторым и третим параметром выполняет функцию, заданную
	//первым параметром
	//прототип: BOOL CALLBACK EnumDevices(LPCDDeviceINSTANCE pdInst,LPVOID pvRef)
	void EnumDevices(LPDIENUMDEVICESCALLBACK EnumDevices, DWORD version = DIRECTINPUT_VERSION, IID  iid = IID_IDirectInput8)
	{
		pDI->EnumDevices(DI8DEVCLASS_ALL, EnumDevices, (LPVOID)NULL, DIEDFL_ALLDEVICES);
	}
	~Device()
	{
		pDI->Release();
	}

	

};

//Интерфейс для опроса клавиатуры
class KeyboardDevice :public Device
{
protected:
	IDirectInputDevice8 *keyboard;
public:
	KeyboardDevice()
		:Device()
	{
		keyboard = InitKeyboard(Application::ThisWindow(), pDI);

	}

	//возвращает массив состояния клавиатуры, определяющий какий клавиши нажаты
	std::string Pressed()
	{
		char KeyStateBuffer[256];
		ReadDevice(keyboard, (void*)KeyStateBuffer, 256);
		return std::string(KeyStateBuffer, 256);
	}

	//проверяет являются ли нажаты клавиши нажаты одновременно
	bool IsPressed(std::vector<char> IDs)
	{
		std::string state = Pressed();
		for (int i = 0; i < IDs.size(); i++)
		{
			if (state[IDs[i]] == false)
				return false;
		}
		return true;
	}

	//проверяет является ли нажата хотябы одна клавиша из списка.
	bool IsPressedOne(std::vector<char> IDs)
	{
		std::string state = Pressed();
		for (int i = 0; i < IDs.size(); i++)
		{
			if (state[IDs[i]] == true)
				return true;
		}
		return false;
	}

	//возвращает объект клавиатуры
	IDirectInputDevice8* GetDevice()
	{
		return keyboard;
	}

	~KeyboardDevice()
	{
		keyboard->Release();
	}

private:
	
	IDirectInputDevice8* InitKeyboard(HWND hWnd, IDirectInput8 *pDI)
	{
		IDirectInputDevice8 *pDDevice;

		// Создание объекта устройства
		if (FAILED(pDI->CreateDevice(GUID_SysKeyboard,
			&pDDevice, NULL)))
			return NULL;

		// Установка формата данных
		if (FAILED(pDDevice->SetDataFormat(&c_dfDIKeyboard))) {
			pDDevice->Release();
			return NULL;
		}

		// Установка режима кооперации
		if (FAILED(pDDevice->SetCooperativeLevel(hWnd,
			DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
			pDDevice->Release();
			return NULL;
		}

		HRESULT hr;
		// Захватываем устройство для использования
		if (FAILED(hr = pDDevice->Acquire())) {
			pDDevice->Release();
			return NULL;
		}

		// Если все успешно, возвращаем указатель
		return pDDevice;
	}


};

class MouseDevice : Device
{
	IDirectInputDevice8 *mouse;
public:
	MouseDevice() : Device()
	{
		mouse = InitMouse(Application::ThisWindow(), this->pDI);
		
	}
	~MouseDevice()
	{
		mouse->Release();
	}

	DIMOUSESTATE State()
	{
		DIMOUSESTATE MouseState;
		ReadDevice(mouse, (void*)&MouseState, sizeof(DIMOUSESTATE));
		return MouseState;
	}

	//возвращает объект мыши
	IDirectInputDevice8* GetDevice()
	{
		return mouse;
	}



	IDirectInputDevice8* InitMouse(HWND hWnd, IDirectInput8* pDI)
	{
		IDirectInputDevice8 *pDIDevice;

		// Создаем объект устройства
		if (FAILED(pDI->CreateDevice(GUID_SysMouse, &pDIDevice, NULL)))
			return NULL;

		// Устанавливаем формат данных
		if (FAILED(pDIDevice->SetDataFormat(&c_dfDIMouse))) {
			pDIDevice->Release();
			return NULL;
		}

		// Задаем режим кооперации
		if (FAILED(pDIDevice->SetCooperativeLevel(hWnd,
			DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
			pDIDevice->Release();
			return NULL;
		}

		// Захватываем устройство для использования
		if (FAILED(pDIDevice->Acquire())) {
			pDIDevice->Release();
			return NULL;
		}

		// Если все успешно, возвращаем указатель
		return pDIDevice;
	}

};