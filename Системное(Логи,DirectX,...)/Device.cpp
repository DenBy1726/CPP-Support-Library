/*02.02.2017 22:13
������� ��� DirectX
*/
#pragma once
#include "dinput.h"
#include <vector>
#include <string>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "comctl32.lib")

//����������� ����� ��� ��������� ������ �������� ����������
static class Application
{

public:

	//�������� ������ HInstance ������� ����������
	static HINSTANCE ThisInstance()
	{
		return GetModuleHandle(NULL);
	}

	//�������� ���� ������� ���������� ���� ������� �������,����� NULL
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



//������� COM-��������� DirectInput 8. ��� ������ ���������� ����������� ����� ����
class Device
{
protected:
	IDirectInput8* pDI;

	static BOOL ReadDevice(IDirectInputDevice8 *pDDevice,
		void *DataBuffer, long BufferSize)
	{
		HRESULT hr;

		while (1) {
			// ����� ����������
			pDDevice->Poll();

			// ������ ���������
			if (SUCCEEDED(hr = pDDevice->GetDeviceState(BufferSize,
				(LPVOID)DataBuffer)))
				break;

			// ���������� �������������� ������
			if (hr != DIERR_INPUTLOST && hr != DIERR_NOTACQUIRED)
				return FALSE;

			// ����� ����������� ��������� � ��������
			// �������� ������ ��� ���
			if (FAILED(pDDevice->Acquire()))
				return FALSE;
		}
		// �������� �� ������
		return TRUE;
	}

public:
	Device()
	{
		HINSTANCE hInst = Application::ThisInstance();
		DirectInput8Create(hInst, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&pDI, NULL);
	}
	//�������� IDirectInput8*
	IDirectInput8* GetObject()
	{
		return pDI;
	}
	virtual IDirectInputDevice8* GetDevice() = 0;
	//��� ������� ���� ����������,���������� ������ � ������ ���������� ��������� �������, ��������
	//������ ����������
	//��������: BOOL CALLBACK EnumDevices(LPCDDeviceINSTANCE pdInst,LPVOID pvRef)
	void EnumDevices(LPDIENUMDEVICESCALLBACK EnumDevices, DWORD version = DIRECTINPUT_VERSION, IID  iid = IID_IDirectInput8)
	{
		pDI->EnumDevices(DI8DEVCLASS_ALL, EnumDevices, (LPVOID)NULL, DIEDFL_ALLDEVICES);
	}
	~Device()
	{
		pDI->Release();
	}

	

};

//��������� ��� ������ ����������
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

	//���������� ������ ��������� ����������, ������������ ����� ������� ������
	std::string Pressed()
	{
		char KeyStateBuffer[256];
		ReadDevice(keyboard, (void*)KeyStateBuffer, 256);
		return std::string(KeyStateBuffer, 256);
	}

	//��������� �������� �� ������ ������� ������ ������������
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

	//��������� �������� �� ������ ������ ���� ������� �� ������.
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

	//���������� ������ ����������
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

		// �������� ������� ����������
		if (FAILED(pDI->CreateDevice(GUID_SysKeyboard,
			&pDDevice, NULL)))
			return NULL;

		// ��������� ������� ������
		if (FAILED(pDDevice->SetDataFormat(&c_dfDIKeyboard))) {
			pDDevice->Release();
			return NULL;
		}

		// ��������� ������ ����������
		if (FAILED(pDDevice->SetCooperativeLevel(hWnd,
			DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
			pDDevice->Release();
			return NULL;
		}

		HRESULT hr;
		// ����������� ���������� ��� �������������
		if (FAILED(hr = pDDevice->Acquire())) {
			pDDevice->Release();
			return NULL;
		}

		// ���� ��� �������, ���������� ���������
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

	//���������� ������ ����
	IDirectInputDevice8* GetDevice()
	{
		return mouse;
	}



	IDirectInputDevice8* InitMouse(HWND hWnd, IDirectInput8* pDI)
	{
		IDirectInputDevice8 *pDIDevice;

		// ������� ������ ����������
		if (FAILED(pDI->CreateDevice(GUID_SysMouse, &pDIDevice, NULL)))
			return NULL;

		// ������������� ������ ������
		if (FAILED(pDIDevice->SetDataFormat(&c_dfDIMouse))) {
			pDIDevice->Release();
			return NULL;
		}

		// ������ ����� ����������
		if (FAILED(pDIDevice->SetCooperativeLevel(hWnd,
			DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
			pDIDevice->Release();
			return NULL;
		}

		// ����������� ���������� ��� �������������
		if (FAILED(pDIDevice->Acquire())) {
			pDIDevice->Release();
			return NULL;
		}

		// ���� ��� �������, ���������� ���������
		return pDIDevice;
	}

};