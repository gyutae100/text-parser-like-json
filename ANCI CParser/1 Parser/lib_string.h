#pragma once

#include <iostream>
using namespace std;



	//------------------------------------------------------------------------------
	//	소문자 검사 
	//------------------------------------------------------------------------------
	bool IsLowerAlphabet(char const inChar)
	{
		if ('a' <= inChar && 'z' >= inChar)
			return true;
		else
			return false;
	}

	//------------------------------------------------------------------------------
	//	대문자 검사
	//------------------------------------------------------------------------------
	bool IsUpperAlphabet(char const inChar)
	{
		if ('A' <= inChar && 'Z' >= inChar)
			return true;
		else
			return false;
	}

	//------------------------------------------------------------------------------
	//	소문자를 대문자로 변경
	//------------------------------------------------------------------------------
	bool ToUpperAlphabet(char *inOutData)
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
	bool ToLowerAlphabet(char *inOutData)
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
	bool IsAlphabet(char const inData)
	{
		if ('a' <= inData && 'z' >= inData)
			return true;
		else if ('A' <= inData && 'Z' >= inData)
			return true;
		else
			return false;
	}


