#include "StdAfx.h"
#include "ChineseCode.h"

namespace EAViewEngine
{
	void CChineseCode::UnicodeToUTF8(const std::wstring &src, std::string& result)
	{
		int n = WideCharToMultiByte( CP_UTF8, 0, src.c_str(), -1, 0, 0, 0, 0 );
		result.resize(n);
		::WideCharToMultiByte( CP_UTF8, 0, src.c_str(), -1, (char*)result.c_str(), result.length(), 0, 0 );
	}

	void CChineseCode::GB2312ToUnicode(const std::string& src, std::wstring& result)
	{
		int n = MultiByteToWideChar( CP_ACP, 0, src.c_str(), -1, NULL, 0 );
		result.resize(n);
		::MultiByteToWideChar( CP_ACP, 0, src.c_str(), -1, (LPWSTR)result.c_str(), result.length());
	}

	void CChineseCode::GB2312ToUtf8(const std::string& src, std::string& result)
	{
		std::wstring strWideChar;
		GB2312ToUnicode(src, strWideChar);
		UnicodeToUTF8(strWideChar, result);
	}

	/*另一种方法的代码，留用仅供学习
	void CChineseCode::UTF_8ToUnicode(wchar_t* pOut,char *pText)
	{
		char* uchar = (char *)pOut;
		uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
		uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);
		return;
	}
	void CChineseCode::UnicodeToUTF_8(char* pOut,wchar_t* pText)
	{
		// 注意 WCHAR高低字的顺序,低字节在前，高字节在后
		char* pchar = (char *)pText;
		pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
		pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
		pOut[2] = (0x80 | (pchar[0] & 0x3F));
		return;
	}

	void CChineseCode::UnicodeToGB2312(char* pOut,wchar_t uData)
	{
		WideCharToMultiByte(CP_ACP,NULL,&uData,1,pOut,sizeof(wchar_t),NULL,NULL);
		return;
	}        



	void CChineseCode::Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer)
	{
		::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
		return;
	} */ 

	bool CChineseCode::StringToWString(const std::string &str,std::wstring &wstr)
	{    
		int nLen = (int)str.length();    
		wstr.resize(nLen,L' ');
   
		int nResult = MultiByteToWideChar(CP_ACP,0,(LPCSTR)str.c_str(),nLen,(LPWSTR)wstr.c_str(),nLen);
   
		if (nResult == 0)
		{
			return false;
		}
  
		return true;
	}
	//wstring高字节不为0，返回FALSE
	bool CChineseCode::WStringToString(const std::wstring &wstr,std::string &str)
	{    
		int nLen = (int)wstr.length();    
		str.resize(nLen,' ');
  
		int nResult = WideCharToMultiByte(CP_ACP,0,(LPCWSTR)wstr.c_str(),nLen,(LPSTR)str.c_str(),nLen,NULL,NULL);
  
		if (nResult == 0)
		{
			return false;
		}
  
		return true;
	}

	/*
	void CChineseCode::GB2312ToUTF_8(std::string& pOut,char *pText, int pLen)
	{
		char buf[4];
		int nLength = pLen* 3;
		char* rst = new char[nLength];
		memset(buf,0,4);
		memset(rst,0,nLength);
		int i = 0;
		int j = 0;
		while(i < pLen)
		{
			//如果是英文直接复制就可以
			if( *(pText + i) >= 0)
			{
				rst[j++] = pText[i++];
			}
			else 
			{ 
				wchar_t pbuffer;
				Gb2312ToUnicode(&pbuffer,pText+i);
				//UnicodeToUTF_8(buf,&pbuffer);
				UnicodeToUTF8(buf,pbuffer,0);
				unsigned short int tmp = 0;
				tmp = rst[j] = buf[0];
				tmp = rst[j+1] = buf[1];
				tmp = rst[j+2] = buf[2];
				j += 3;
				i += 2;
			}
		}
		rst[j] = '\0';
		//返回结果
		pOut = rst;
		delete []rst;
		return;
	}

	void CChineseCode::UTF_8ToGB2312(std::string &pOut, char *pText, int pLen)
	{
		char * newBuf = new char[pLen];
		char Ctemp[4];
		memset(Ctemp,0,4);
		int i =0;
		int j = 0;
		while(i < pLen)
		{
			if(pText > 0)
			{
				newBuf[j++] = pText[i++];
			}
			else
			{
				WCHAR Wtemp;
				UTF_8ToUnicode(&Wtemp,pText + i);
				UnicodeToGB2312(Ctemp,Wtemp);
				newBuf[j] = Ctemp[0];
				newBuf[j + 1] = Ctemp[1];
				i += 3;
				j += 2;
			}
		}
		newBuf[j] = '\0';    
		pOut = newBuf;    
		delete []newBuf;  
		return;
	}*/
}