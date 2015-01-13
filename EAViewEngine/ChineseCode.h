#pragma once
#include <wchar.h>
#include <windows.h>
#include <string>

namespace EAViewEngine
{
	class CChineseCode
	{
	public: 
		static void CChineseCode::UnicodeToUTF8(const std::wstring &src, std::string& result);

		static void CChineseCode::GB2312ToUnicode(const std::string& src, std::wstring& result);

		static void CChineseCode::GB2312ToUtf8(const std::string& src, std::string& result);

    	static bool CChineseCode::StringToWString(const std::string &str,std::wstring &wstr);

		static bool CChineseCode::WStringToString(const std::wstring &wstr,std::string &str);
		/*
		static void UTF_8ToUnicode(wchar_t* pOut,char *pText);  // 把UTF-8转换成Unicode  

		static void UnicodeToUTF_8(char* pOut,wchar_t* pText);  //Unicode 转换成UTF-8  

		static void UnicodeToGB2312(char* pOut,wchar_t uData);  // 把Unicode 转换成 GB2312

		static void GB2312ToUTF_8(std::string& pOut,char *pText, int pLen);//GB2312 转为 UTF-8  

		static void UTF_8ToGB2312(std::string &pOut, char *pText, int pLen);//UTF-8 转为 GB2312

		static void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// GB2312 转换成　Unicode 

		static void UnicodeToUTF8(std::string& result, const wstring &src,int i);
		*/

	}; 
}
