#pragma once

#include <iostream>
using namespace std;



	//------------------------------------------------------------------------------
	//	�ҹ��� �˻� 
	//------------------------------------------------------------------------------
	bool IsLowerAlphabet(char const inChar)
	{
		if ('a' <= inChar && 'z' >= inChar)
			return true;
		else
			return false;
	}

	//------------------------------------------------------------------------------
	//	�빮�� �˻�
	//------------------------------------------------------------------------------
	bool IsUpperAlphabet(char const inChar)
	{
		if ('A' <= inChar && 'Z' >= inChar)
			return true;
		else
			return false;
	}

	//------------------------------------------------------------------------------
	//	�ҹ��ڸ� �빮�ڷ� ����
	//------------------------------------------------------------------------------
	bool ToUpperAlphabet(char *inOutData)
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
	bool ToLowerAlphabet(char *inOutData)
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
	bool IsAlphabet(char const inData)
	{
		if ('a' <= inData && 'z' >= inData)
			return true;
		else if ('A' <= inData && 'Z' >= inData)
			return true;
		else
			return false;
	}


