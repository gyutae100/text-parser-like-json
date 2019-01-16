#pragma once

#include <iostream>
using namespace std;



	//------------------------------------------------------------------------------
	//	소문자 검사 
	//------------------------------------------------------------------------------
	BOOL IsLowerAlphabet(WCHAR CONST inWCHAR)
	{
		if ('a' <= inWCHAR && 'z' >= inWCHAR)
			return true;
		else
			return false;
	}

	//------------------------------------------------------------------------------
	//	대문자 검사
	//------------------------------------------------------------------------------
	BOOL IsUpperAlphabet(WCHAR CONST inWCHAR)
	{
		if ('A' <= inWCHAR && 'Z' >= inWCHAR)
			return true;
		else
			return false;
	}

	//------------------------------------------------------------------------------
	//	소문자를 대문자로 변경
	//------------------------------------------------------------------------------
	BOOL ToUpperAlphabet(WCHAR *inOutData)
	{
		//소문자 검사
		if (!IsLowerAlphabet(*inOutData))
			return false;
		else
		{
			//대문자로 변경
			*inOutData = *inOutData - 32; // 
		}
	}


	//------------------------------------------------------------------------------
	//	대문자를 소문자로 변경
	//------------------------------------------------------------------------------
	BOOL ToLowerAlphabet(WCHAR *inOutData)
	{
		//소문자 검사
		if (!IsUpperAlphabet(*inOutData))
			return false;
		else
		{
			//소문자로 변경
			*inOutData = *inOutData + 32; // 
		}
	}

	//------------------------------------------------------------------------------
	//	알파벳인지 검사
	//------------------------------------------------------------------------------
	BOOL IsAlphabet(WCHAR CONST inData)
	{
		if ('a' <= inData && 'z' >= inData)
			return true;
		else if ('A' <= inData && 'Z' >= inData)
			return true;
		else
			return false;
	}


