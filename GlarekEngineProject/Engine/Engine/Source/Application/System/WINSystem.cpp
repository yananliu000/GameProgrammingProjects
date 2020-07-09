#include <windows.h> //system info
#include <filesystem> //system info
#include <ctime> //time
#include <chrono> //time
#include <iomanip> //time
#include <time.h> //time
#include <stdio.h> 
#include <Shlobj.h> //user dir
#include "comutil.h" //gpu
#include "Wbemcli.h" //gpu
#include "Wbemidl.h" //gpu

#include "WINSystem.h"
#include "../../Utility/MyLogger.h"

using Engine::WINSystem;
namespace fs = std::experimental::filesystem;
#define WriteAndReset result = m_stringstream.str(); m_stringstream.clear(); m_stringstream = std::stringstream(); g_Logger.write(MyLogger::LogLevel::System_Normal, result);
#define WIDTH 7
#define DIV 1048576 //Use to convert bytes to MB

bool Engine::WINSystem::Init()
{
	//system info
	LogSystemInfo();

	//message box
	//OpenMessageBox("test","test");

	//dir contents
	LogDirectoryContents("\Temp");

	//time stamp
	GetSystemTimestamp();

	//hard drive info
	LogHardDriveInfo("E:/");
	LogHardDriveInfo("C:/");

	//user dir
	g_Logger.write(MyLogger::LogLevel::System_Normal, GetUserDirectory());

	//gpu info
	//LogGpuInfo();

	return true;
}

void Engine::WINSystem::LogSystemInfo()
{
	//https://stackoverflow.com/questions/282194/how-to-get-memory-usage-under-windows-in-c
	// get system info
	SYSTEM_INFO info;
	GetSystemInfo(&info);

	//get exact info
	int processorNum = info.dwNumberOfProcessors;

	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);

	//log
	std::string result;
	m_stringstream << "Processors Found: " << info.dwNumberOfProcessors;
	WriteAndReset;
	m_stringstream << "There is " << statex.dwMemoryLoad << " percent of memory in use.";
	WriteAndReset;
	m_stringstream << "There are " << statex.ullTotalPhys / DIV << " total MB of physical memory.";
	WriteAndReset;
	m_stringstream << "There are " << statex.ullAvailPhys / DIV << " free MB of physical memory.";
	WriteAndReset;
	m_stringstream << "There are " << statex.ullTotalPageFile / DIV << " total MB of paging file.";
	WriteAndReset;
	m_stringstream << "There are " << statex.ullAvailPageFile / DIV << " free MB of paging file.";
	WriteAndReset;
	m_stringstream << "There are " << statex.ullTotalVirtual / DIV << " total MB of virtual memory.";
	WriteAndReset;
	m_stringstream << "There are " << statex.ullAvailVirtual / DIV << " free MB of virtual memory.";
	WriteAndReset;
	m_stringstream << "There are " << statex.ullAvailExtendedVirtual / DIV << " free MB of extended memory.";
	WriteAndReset;
}

void Engine::WINSystem::OpenMessageBox(const char * Name, const char * Message)
{
	//MessageBox(NULL, LPCSTR(Name), LPCSTR(Message), MB_OK | MB_SYSTEMMODAL);
}

void Engine::WINSystem::OpenExe(const char * filepath, char ** argv)
{
	//code reference: https://stackoverflow.com/questions/15435994/how-do-i-open-an-exe-from-another-c-exe
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up
	CreateProcess(LPCTSTR(filepath),   // the path
		LPSTR(argv[1]),        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void Engine::WINSystem::LogDirectoryContents(std::string folder)
{
	//https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
	std::string result;
	std::string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
			{
				m_stringstream << folder << "/" << fd.cFileName;
				WriteAndReset;
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
}

std::string Engine::WINSystem::GetSystemTimestamp()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	struct tm timeinfo;
	localtime_s(&timeinfo, &now_c);
	m_stringstream << std::put_time(&timeinfo, "%F,%T ");
	std::string result = m_stringstream.str();
	m_stringstream.clear(); 
	m_stringstream = std::stringstream();

	return result;
}

void Engine::WINSystem::LogHardDriveInfo(const char* drive)
{
	LPSTR pszDrive = LPSTR(drive);
	BOOL test, fResult;

	__int64 lpFreeBytesAvailable, lpTotalNumberOfBytes, lpTotalNumberOfFreeBytes;
	DWORD dwSectPerClust, dwBytesPerSect, dwFreeClusters, dwTotalClusters;

	test = GetDiskFreeSpaceEx(
		pszDrive,
		(PULARGE_INTEGER)&lpFreeBytesAvailable,
		(PULARGE_INTEGER)&lpTotalNumberOfBytes,
		(PULARGE_INTEGER)&lpTotalNumberOfFreeBytes
	);

	fResult = GetDiskFreeSpace(pszDrive,
		&dwSectPerClust,
		&dwBytesPerSect,
		&dwFreeClusters,
		&dwTotalClusters);

	std::string result;
	if (test != 0 && fResult != 0)
	{
		m_stringstream << "Drive to be checked: " << pszDrive;
		WriteAndReset;
		m_stringstream << "Total number of free bytes available for user-caller: " << lpFreeBytesAvailable;
		WriteAndReset;
		m_stringstream << "Total number of bytes available for user: " << lpTotalNumberOfBytes;
		WriteAndReset;
		m_stringstream << "Total number of free bytes on disk: " << lpTotalNumberOfFreeBytes;
		WriteAndReset;
		m_stringstream << "Sector per cluster =  " << dwSectPerClust;
		WriteAndReset;
		m_stringstream << "Bytes per sector = " << dwBytesPerSect;
		WriteAndReset;
		m_stringstream << "Free cluster = " << dwFreeClusters;
		WriteAndReset;
		m_stringstream << "Total cluster = " << dwTotalClusters;
		WriteAndReset;
		m_stringstream << "Total free bytes = " << dwFreeClusters*dwSectPerClust*dwBytesPerSect;
		WriteAndReset;
	}
	else
	{
		m_stringstream << "Could not log the hard drive info: " << pszDrive;
		WriteAndReset;
	}
}

std::string Engine::WINSystem::GetUserDirectory()
{
	WCHAR path[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path))) 
	{
		std::wstring ws(path);
		std::string str(ws.begin(), ws.end());
		return str;
	}
	return std::string();
}

std::vector<std::string> Engine::WINSystem::GetFilesInFolder(const char * path, bool recursive)
{
	std::vector<std::string> vec;
	GetFiles(path, vec, recursive);
	return vec;
}

void Engine::WINSystem::GetFiles(const char * path, std::vector<std::string>& vec, bool recursive)
{
	for (const auto & entry : fs::directory_iterator(path))
	{
		auto e = entry.path().c_str();
		std::wstring ws(e);
		std::string p(ws.begin(), ws.end());

		if (!fs::is_directory(entry))
		{
			vec.push_back(p);
		}
		if (recursive)
		{
			GetFiles(p.c_str(), vec, true);
		}
	}
}

/* not getting resonable result
void Engine::WINSystem::LogGpuInfo()
{
	//https://www.gamedev.net/forums/topic/495075-how-to-retrieve-info-about-videocard/
	HRESULT hr;
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	IWbemLocator *pIWbemLocator = NULL;
	hr = CoCreateInstance(__uuidof(WbemLocator), NULL,
		CLSCTX_INPROC_SERVER, __uuidof(IWbemLocator),
		(LPVOID *)&pIWbemLocator);

	BSTR bstrServer = SysAllocString(L"\\\\.\\root\\cimv2");
	IWbemServices *pIWbemServices;
	hr = pIWbemLocator->ConnectServer(bstrServer, NULL, NULL, 0L, 0L, NULL,
		NULL, &pIWbemServices);

	hr = CoSetProxyBlanket(pIWbemServices, RPC_C_AUTHN_WINNT,
		RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL,
		RPC_C_IMP_LEVEL_IMPERSONATE, NULL,
		EOAC_DEFAULT);

	BSTR bstrWQL = SysAllocString(L"WQL");
	BSTR bstrPath = SysAllocString(L"select * from Win32_VideoController");
	IEnumWbemClassObject* pEnum;
	hr = pIWbemServices->ExecQuery(bstrWQL, bstrPath, WBEM_FLAG_FORWARD_ONLY, NULL, &pEnum);

	IWbemClassObject* pObj = NULL;
	ULONG uReturned;
	VARIANT var;
	hr = pEnum->Next(WBEM_INFINITE, 1, &pObj, &uReturned);

	std::string result;

	if (uReturned)
	{
		hr = pObj->Get(L"AdapterRAM", 0, &var, NULL, NULL);
		if (SUCCEEDED(hr))
		{
			i64 value = var.lVal / (1024 * 1024);
			m_stringstream << "Adapter RAM: " << value;
			WriteAndReset;
		}

		hr = pObj->Get(L"ConfigManagerErrorCode", 0, &var, NULL, NULL);
		if (SUCCEEDED(hr))
		{
			m_stringstream << "ConfigManagerErrorCode: " << var.lVal;
			WriteAndReset;
		}

		hr = pObj->Get(L"Name", 0, &var, NULL, NULL);
		if (SUCCEEDED(hr))
		{
			m_stringstream << "Drive Name: " << var.bstrVal;
			WriteAndReset;
		}

		hr = pObj->Get(L"DeviceID", 0, &var, NULL, NULL);
		if (SUCCEEDED(hr))
		{
			m_stringstream << "Device ID: " << var.bstrVal;
			WriteAndReset;
		}

		hr = pObj->Get(L"DriverVersion", 0, &var, NULL, NULL);
		if (SUCCEEDED(hr))
		{
			m_stringstream << "Driver Version: " << var.bstrVal;
			WriteAndReset;
		}

		hr = pObj->Get(L"VideoProcessor", 0, &var, NULL, NULL);
		if (SUCCEEDED(hr))
		{
			m_stringstream << "Video Processor: " << var.bstrVal;
			WriteAndReset;
		}

		hr = pObj->Get(L"VideoModeDescription", 0, &var, NULL, NULL);
		if (SUCCEEDED(hr))
		{
			m_stringstream << "Video Mode Description: " << var.bstrVal;
			WriteAndReset;
		}

		hr = pObj->Get(L"AdapterDACType", 0, &var, NULL, NULL);
		if (SUCCEEDED(hr))
		{
			m_stringstream << "Adapter DAC Type: " << var.bstrVal;
			WriteAndReset;
		}

		hr = pObj->Get(L"VideoArchitecture", 0, &var, NULL, NULL);
		if (SUCCEEDED(hr))
		{
			m_stringstream << "Video Architecture: " << var.lVal;
			WriteAndReset;
		}
	}
}
*/
