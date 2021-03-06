/**
@file main.cpp

@date 2018/05/22

@brief 사용 예제
*/

#include "stdafx.h"

#include "CTextParser.h"

int main()
{

	////*테스트 코드1
	//TextParser test1;
	//if (!test1.SetTextPath((WCHAR*)"test1.txt"))
	//{
	//	cout << "텍스트 경로 설정 실패";
	//}

	//if (!test1.openTextFile())
	//{
	//	cout << "파일 오픈 실패";
	//}

	CTextParser test1(L"test2nd.txt");

	UINT64 value = 0;


	//------------------------------------------------------------------------------
	//*1 번째 프로바이더 이용 수치 데이터 복사 부분
	//------------------------------------------------------------------------------
	//*프로바이더 설정한다.
	test1.SetProvider(L"namespace1");

	//*해당 스트링명의 수치 데이터를 복사한다.
	test1.GetValue(L"hi", &value);
	//*확인 출력한다.
	wcout << value <<endl;

	//*해당 스트링명의 수치 데이터를 복사한다.
	test1.GetValue(L"bye", &value);
	//*확인 출력한다.
	wcout << value<<endl;

	//------------------------------------------------------------------------------
	//*2 번째 프로바이더 이용 수치 데이터 복사 부분
	//------------------------------------------------------------------------------
	//*프로바이더 설정한다.
	test1.SetProvider(L"namespace2");

	//*해당 스트링명의 수치 데이터를 복사한다.
	test1.GetValue(L"see", &value);
	//*확인 출력한다.
	wcout << value << endl;

	//*해당 스트링명의 수치 데이터를 복사한다.
	test1.GetValue(L"you", &value);
	//*확인 출력한다.
	wcout << value << endl;

	//------------------------------------------------------------------------------
	//*2 번째 프로바이더 이용 수치 데이터 복사 부분
	//------------------------------------------------------------------------------
	//*프로바이더 설정한다.
	test1.SetProvider(L"namespace3");

	//*해당 스트링명의 수치 데이터를 복사한다.
	test1.GetValue(L"good", &value);
	//*확인 출력한다.
	wcout << value << endl;

	//*해당 스트링명의 수치 데이터를 복사한다.
	test1.GetValue(L"luck", &value);
	//*확인 출력한다.
	wcout << value << endl;

	//------------------------------------------------------------------------------
	//*3 번째 프로바이더 이용 수치 데이터 복사 부분
	//------------------------------------------------------------------------------
	//*프로바이더 설정한다.
	test1.SetProvider(L"namespace4");

	//*해당 스트링명의 수치 데이터를 복사한다.
	test1.GetValue(L"have", &value);
	//*확인 출력한다.
	wcout << value << endl;

	//*프로바이더 설정한다.
	test1.GetValue(L"fun", &value);
	//*확인 출력한다.
	wcout << value << endl;

	//------------------------------------------------------------------------------
	//*4 번째 프로바이더 이용 수치 데이터 복사 부분
	//------------------------------------------------------------------------------
	test1.SetProvider(L"namespace5");

	WCHAR *teststr = NULL;
	WCHAR *teststr2 = NULL;

	//*해당 스트링명의 수치 데이터를 복사한다.
	test1.GetValue(L"string1" ,&teststr);
	//*확인 출력한다.
	wcout << teststr << endl;

	//*해당 스트링명의 수치 데이터를 복사한다.
	test1.GetValue(L"string2", &teststr2);
	//*확인 출력한다.
	wcout << teststr2 << endl;

	//*해당 스트링명의 수치 데이터를 복사한다.
	test1.GetValue(L"string1", &teststr);
	//*확인 출력한다.
	wcout << teststr << endl;

	//*해당 스트링명의 수치 데이터를 복사한다.
	test1.GetValue(L"string2", &teststr2);
	//*확인 출력한다.
	wcout << teststr2 << endl;


	while (true){

	}

    return 0;
}

