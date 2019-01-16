///@mainpage    유니코드 텍스트 파서 클래스 
///@section UINT64ro 소개
///- 부분1 : 유니코드 텍스트 파일을 읽어와서 버퍼에 저장한다. 
///- 부분2 : 유니코드 텍스트 파일 내에 존재하는 주석 스타일( //, /*)은 자동 무시한다.
///- 부분3 : 유니코드 내 존재하는 포멧 형식에 맞게 버퍼 내에 존재하는 프로바이더(제공자)를 검색한다.
///- 부분4 : 프로바이더(제공자)가 존재하면 제공자 내부에 존재하는 수치 이름과 수치 이름에 일대일 매핑 되는 해당 수치 값을 검색한다.
///- 부분5 : 수치 이름과 해당 수치 값이 존재하는 경우 프로그램 내에 지정한 변수에 해당 수치 이름의 해당 수치 값을 복사한다.
///@section Program 프로그램명
///- 프로그램 명  :   CTextParser
///- 프로그램 내용    : 유니코드 형식 텍스트 파일 내에 존재하는 수치 이름에 일대일 매핑 되는 해당 수치 값을 프로그램 코드 내 지정한 변수에 대입한다.
///@section CREATEINFO 작성정보
///- 작성자      :   김규태(gyutae100@gmail.com)
///- 작성일      :   2018/04/24
///@section MODIFYINFO 수정정보
///- 수정자/수정일   : 작성자와 동일
///- 2018.05.22    : Doxygen 주석화
///-@version 1.0


#pragma once


/**
@class CTextParser

@brief 유니코드 형식 텍스트 파일 내에 존재하는 수치 이름에 일대일 매핑 되는 해당 수치 값을 
       프로그램 코드 내 지정한 변수에 대입한다.
*/
class CTextParser{

private:

	/**
	@enum BUF_SET

	@brief 유니코드 텍스트 저장 버퍼 사이즈 설정
	*/
	typedef enum BUF_SET{
		BUF_SIZE = 1000
	}BUF_SET;

	WCHAR _text_buf[BUF_SET::BUF_SIZE]; ///<읽어온 텍스트 내용을 저장한 버퍼

	UINT64 _len_str;					   ///<읽어온 텍스트 내 문자 총 갯수


	static CONST UINT64 max_len_text_path = 100; ///<최대 텍스트 경로 문자 크기
	WCHAR _text_path[max_len_text_path];       ///<파서 대상 텍스트 경로

	BOOL _use_provider;					///<프로바이더 지정 여부
	WCHAR _provider_name[100];			///<현재 지정한 프로바이더 이름
	WCHAR *_first_offset_in_provider;	///<프로바이더 지정 이후 버퍼 내에 프로바이더 
									    ///<시작 기호 '{' 이후의 버퍼 주소를 가리키는 포인터 

	static CONST UINT64 _cnt_symbol_delimiter = 8;				///<구분문자 총 갯수
	CONST WCHAR _symbol_delimiter[_cnt_symbol_delimiter] =   ///<구분 문자 종류 설정
	{
		',',	//컴마
		'.',	//마침표
		'"',	//따옴표
		0x20, //스페이스
		0x08, //백스페이스
		0x09, //텝
		0x0a, //라인 피드
		0x0d //캐리지 리턴
	};

	CONST WCHAR _symbol_command[3][3] = ///<주석 문자 설정
	{
		L"//",
		L"/*",
		L"*/"
	};

	CONST WCHAR _declear_provider_symbol = L':'; ///<프로바이더 이름 앞에 붙는 기호

	CONST WCHAR _symbol_brace_in_provider[2][2] =  ///<프로바이더 선언 시작 및 선언 끝 기호 설정
	{
		L"{",
		L"}"
	}; 

	CONST WCHAR *_symbol_assignment = L"="; ///< 대입 기호 설정


public:

	// 생성자 1
	CTextParser();

	// 생성자 2
	CTextParser(CONST WCHAR * textpath);

	//파서 대상 텍스트 경로를 설정한다. 
	BOOL SetTextPath(CONST WCHAR * textpath);
	
	//파서 대상 텍스트 파일을 클래스 내 버퍼에 저장한다.
	BOOL ReadTextFile();

	//프로바이더 네임을 저장한다. 
	BOOL SetProviderName(CONST WCHAR *provider_name);

	//프로바이더를 설정한다.
	BOOL SetProvider(CONST WCHAR *provider_name = NULL);

	//다음 단어 반환한다.
	BOOL GetNextWord(WCHAR **inout_ptr_ch, UINT64 *ptr_len);
	
	//단어 구분 시작 문자 이전의 불필요한 문자를 스킵한다.
	BOOL SkipNoneCommand(WCHAR * inout_ptr_ch, UINT64 *out_len);

	//값 반환한다. (오버라이딩 데이터 값 UINT64형)
	BOOL GetValue(CONST WCHAR * szName, UINT64 * outValue);

	//값 반환한다. (오버라이딩 데이터 값 string형)
	BOOL GetValue(CONST WCHAR * szName, WCHAR ** outValue);

	//주석 ('//')인 경우를 체크하여 성립하는 경우 out_len에 주석이 걸린 길이를 반환한다.
	BOOL SkipSlashStar(WCHAR *offset_first, UINT64 *out_len);

	//주석 ('/*')인 경우를 체크하여 성립하는 경우 out_len에 주석이 걸린 길이를 반환한다.
	BOOL SkipDoubleSlash(WCHAR *offset_first, UINT64 *out_len);
};







