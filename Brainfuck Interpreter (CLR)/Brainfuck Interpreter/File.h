#pragma once

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <Shobjidl.h>

std::ifstream* LoadFile()
{

	std::ifstream *file;
	file = new std::ifstream();
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	PWSTR pszFilePath = NULL;
	LPOPENFILENAME filename = NULL;
	IFileOpenDialog *pFile;
	hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
		IID_IFileOpenDialog, reinterpret_cast<void**>(&pFile));

	if (SUCCEEDED(hr))
	{
		// Show the Open dialog box.
		hr = pFile->Show(NULL);
	}

	if (SUCCEEDED(hr))
	{
		IShellItem *pItem;
		hr = pFile->GetResult(&pItem);
		if (SUCCEEDED(hr))
		{

			hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

			pItem->Release();
		}
	}
	if(pszFilePath!=nullptr)
		file->open(pszFilePath);



	pFile->Release();
	CoUninitialize();
	if (pszFilePath != nullptr)
		return file;
	else return NULL;
}


std::ofstream* SaveFile() {

	std::ofstream *file;
	file = new std::ofstream();
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	PWSTR pszFilePath = NULL;
	LPOPENFILENAME filename = NULL;
	IFileSaveDialog *pFile;
	hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
		IID_IFileSaveDialog, reinterpret_cast<void**>(&pFile));

	if (SUCCEEDED(hr))
	{
		COMDLG_FILTERSPEC rgSpec[] =
		{
			{ L"Brainfuck file", L"*.bf" },
		{ L"All Files", L"*.*" },
		};
		// Show the Open dialog box.
		pFile->SetFileTypes(2, rgSpec);
		hr = pFile->Show(NULL);
	}

	if (SUCCEEDED(hr))
	{
		IShellItem *pItem;
		hr = pFile->GetResult(&pItem);
		if (SUCCEEDED(hr))
		{

			hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

			pItem->Release();

		}
	}
	if (pszFilePath != nullptr) {	//if file doesnt have an extension add .bf
		std::wstring name = pszFilePath;
		if(name.find('.') == std::string::npos)
		name += L".bf";
		LPCWSTR fullFileName = name.c_str();
		
		file->open(fullFileName);
		return file;
	}

	else return NULL;

}
