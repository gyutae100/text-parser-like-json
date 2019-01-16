#pragma once

#include <iostream>
using namespace std;



	//------------------------------------------------------------------------------
	//	�ҹ��� �˻� 
	//------------------------------------------------------------------------------
	BOOL IsLowerAlphabet(WCHAR CONST inWCHAR)
	{
		if ('a' <= inWCHAR && 'z' >= inWCHAR)
			return true;
		else
			return false;
	}

	//------------------------------------------------------------------------------
	//	�빮�� �˻�
	//------------------------------------------------------------------------------
	BOOL IsUpperAlphabet(WCHAR CONST inWCHAR)
	{
		if ('A' <= inWCHAR && 'Z' >= inWCHAR)
			return true;
		else
			return false;
	}

	//------------------------------------------------------------------------------
	//	�ҹ��ڸ� �빮�ڷ� ����
	//------------------------------------------------------------------------------
	BOOL ToUpperAlphabet(WCHAR *inOutData)
	{
		//�ҹ��� �˻�
		if (!IsLowerAlphabet(*inOutData))
			return false;
		else
		{
			//�빮�ڷ� ����
			*inOutData = *inOutData - 32; // 
		}
	}


	//------------------------------------------------------------------------------
	//	�빮�ڸ� �ҹ��ڷ� ����
	//------------------------------------------------------------------------------
	BOOL ToLowerAlphabet(WCHAR *inOutData)
	{
		//�ҹ��� �˻�
		if (!IsUpperAlphabet(*inOutData))
			return false;
		else
		{
			//�ҹ��ڷ� ����
			*inOutData = *inOutData + 32; // 
		}
	}

	//------------------------------------------------------------------------------
	//	���ĺ����� �˻�
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


