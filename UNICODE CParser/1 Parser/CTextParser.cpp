#pragma once
#include "stdafx.h"
#include "CTextParser.h"



/**
@brief 생성자1
*/
CTextParser::CTextParser()
{
	//초기화
	_len_str = 0;
	_text_path[0] = L'\0';
}

/**
@brief 생성자2

@brief 파서 대상 텍스트 경로 설정한다.

@param text_path : 텍스트 파일 경로
*/
CTextParser::CTextParser(CONST WCHAR * text_path)
{

	//클래스 멤버 초기화한다.
	_len_str = 0;
	_text_path[0] = L'\0';

	//텍스트 경로 설정한다.
	SetTextPath(text_path);

	//텍스트 내용을 클래스 내 버퍼에 저장한다.
	ReadTextFile();
}

/**
@brief 파서 대상 텍스트 경로 설정한다.

@return BOOL : 정상 작동시 true, 아닌 경우 false 반환

@param text_path : 유니코드 텍스트 파일 경로
*/
BOOL CTextParser::SetTextPath(CONST WCHAR * text_path=NULL)
{
	if (NULL == text_path) {

		return false;
	}

	//*텍스트 경로를 복사한다.
	wcscpy_s(_text_path, text_path);

	//*경로 설정 실패여부 체크한다.
	if (_text_path[0] == L'\0') {

		return false;
	}
	else {

		return true;
	}
}

/**
@brief 파서 대상 텍스트 파일을 클래스 내 버퍼에 저장한다.

@return BOOL : 정상 작동시 true, 아닌 경우 false 반환
*/
BOOL CTextParser::ReadTextFile()
{

	//*텍스트 파일 경로 지정 여부 체크한다.
	if (_text_path[0] == L'\0'){

		return false;
	}


	//*	파서 대상 텍스트 파일 오픈한다.
	FILE *tmp_file = NULL;
	_wfopen_s(&tmp_file, _text_path, L"rt+,ccs=UNICODE");

	//파일 오픈 안 된 경우 체크한다.
	if (NULL == tmp_file) {

		return false;
	}


	//파서 대상 텍스트 파일 내용을 버퍼에 저장한다.
	/// @todo 나중에 한번에 읽도록 수정하자.
	_len_str = 0; //읽은 문자 갯수
	for (UINT64 bi = 0; bi < BUF_SET::BUF_SIZE; bi++)
	{
		if (!fread_s(&(_text_buf[bi]), BUF_SET::BUF_SIZE * sizeof(WCHAR), sizeof(WCHAR), 1, tmp_file)){

			//다 읽은 경우 반복문을 종료한다.
			break;
		}

		//총 읽은 문자 길이를 증가한다.
		_len_str++;
	}


	//버퍼 내용을 문자열화 한다.
	_text_buf[_len_str] = L'\0';

	//파일을 닫는다.
	fclose(tmp_file);

	return true;
}


/**
@brief 인자로 받은 프로바이더 네임을 클래스 멤버 변수에 저장한다.

@param provider_name : 프로바이더 네임

@return BOOL : 정상 작동시 true, 아닌 경우 false 반환

@todo 만일 wcscpy_s가 실패시 어떻게 예외처리 해야하는지 더 알아볼 것.
*/
BOOL CTextParser::SetProviderName(CONST WCHAR *provider_name)
{

	if (NULL == provider_name) {

		return false;
	}

	//프로바이더 네임을 저장한다.
	wcscpy_s(_provider_name, provider_name);

	return true;
}


/**
@brief 프로바이더 설정한다.
@brief 과정1 : 버퍼 내 인자 프로바이더명과 같은 프로바이더가 존재하는지 검사한다.
@brief 과정2 : 존재 시 객체 내 버퍼 오프셋 포인터를 해당 프로바이더 시작 심볼 기호( '{' ) 이후로 이동시킨다.

@param provider_name : 설정할 프로바이더 네임

@return BOOL : 정상 작동시 true, 아닌 경우 false 반환
*/
BOOL CTextParser::SetProvider(CONST WCHAR *provider_name)
{

	//함수 인자로 프로바이더 네임을 받는 경우를 체크한다.
	if (NULL != provider_name){
		
		//프로바이더 네임을 설정한다.
		SetProviderName(provider_name);
	}

	//버퍼에서 읽는 문자열 오프셋 포인터
	WCHAR *offset_buf = NULL;
	
	//해당 오프셋의 문자값
	WCHAR ch = 0;

	//프로바이더 선언 기호( ':' ) 찾은 여부
	BOOL check_search_provider_symbol = false;


	//단어 단위(구분 문자) 저장 버퍼
	WCHAR current_word[1000];

	//단어 단위(구분 문자) 길이
	UINT64 len = 0;

	//버퍼 인덱스
	UINT64 bi = 0;

	//------------------------------------------------------------------------------
	//*프로바이더 선언 포멧 검색한다.
	//*버퍼 내 해당 프로바이더 선언 포멧( ':프로바이더 네임')형식이 존재 여부 검사한다.
	//------------------------------------------------------------------------------
	while (_text_buf[bi] != L'\0')
	{

		//해당 버퍼 오프셋 포인터 저장한다.
		offset_buf = &(_text_buf[bi]);

		//해당 버퍼 오프셋 포인터가 가리키는 문자 값 저장한다.
		ch = *offset_buf;

		//------------------------------------------------------------------------------
		//프로바이더 선언 심볼( ':' )을 찾은 경우 체크한다.
		//------------------------------------------------------------------------------
		if (ch == _declear_provider_symbol && false == check_search_provider_symbol){
			
			//프로바이더 선언 심볼 찾음으로 설정을 변경한다.
			check_search_provider_symbol = true;
		}


		//------------------------------------------------------------------------------
		//프로바이더 선언 기호( ':' ) 찾은 경우
		//프로바이더 심볼( : ) 이후 단어가 찾는 프로바이더명과 같은지 여부를 체크한다.
		//------------------------------------------------------------------------------
		if (true == check_search_provider_symbol){

			//프로바이더 선언 심볼(:) 다음 문자로 오프셋 이동한다.
			*offset_buf++;

			//다음 단어 읽어온다.
			if (!GetNextWord(&offset_buf, &len)){

				//다음 문자를 찾지 못한 경우 종료한다.
				return false;
			}

			//읽어온 다음 단어를 버퍼에 복사한다.

			memcpy(current_word, offset_buf, sizeof(WCHAR) * len );
			//문자열 형식화한다.
			current_word[len] = L'\0';


			//------------------------------------------------------------------------------
			//읽어온 문자열이 찾는 프로바이더명과 같은지 여부 체크한다.
			//------------------------------------------------------------------------------
			if (wcscmp(_provider_name, current_word) == 0)
			{

				//프로바이더 네임 다음 문자로 오프셋 이동한다.
				offset_buf = offset_buf + len;
			
				//------------------------------------------------------------------------------
				//	프로바이더 인사이드 시작 내부 심볼( '{' ) 검색한다.
				//------------------------------------------------------------------------------
				if (!GetNextWord(&offset_buf, &len)){

					//어떠한 문자도 반환하지 못한 경우 종료한다.
					return false;
				}

				//읽어온 다음 단어를 버퍼에 복사한다.
				memcpy(current_word, offset_buf, sizeof(WCHAR) * len);
				//문자열 형식화한다.
				current_word[len] = L'\0';


				//------------------------------------------------------------------------------
				///프로바이더 인사이드 시작 내부 심볼( '{' )가 다음 문자로 오는지 비교한다.
				//------------------------------------------------------------------------------
				if (current_word[0] != '{'){

					//다음 기호가 '{'가 아니므로 다시 다음 프로바이더 선언 기호를 찾아야 한다.
					check_search_provider_symbol = false;

					//------------------------------------------------------------------------------
					//프로바이더 오프셋 포인터를 재수정하여 다음부터 검색할 수 있게 설정한다.
					//------------------------------------------------------------------------------
					//_first_offset_in_provider = offset_buf + len;
				}

				//------------------------------------------------------------------------------
				//프로바이더 인사이드 시작 내부 심볼( '{' )가 다음 문자로 오는 경우
				//------------------------------------------------------------------------------
				else
				{
					//------------------------------------------------------------------------------
					//프로바이더 시작 포인터를 프로바이더 내부 시작 내부 심볼( '{' ) 이후로 설정
					//------------------------------------------------------------------------------
					_first_offset_in_provider = offset_buf + len;

					//성공!!!
					return true;
				}
			}
			
			//읽어온 문자열이 찾는 프로바이더 네임과 일치하지 않는 경우
			else
			{
				//재검색 할 수 있게 설정한다.
				check_search_provider_symbol = false;

				//오프셋 재 설정 및 인덱스 재설정한다.
				bi = bi + len;
			}
		}

		//인덱스를 증가시킨다.
		bi++;

	}


	 //------------------------------------------------------------------------------
	 //버퍼 내에서 검색 대상 프로바이더를 검색 못 한 경우
	 //------------------------------------------------------------------------------
	return false;
}


/**
@brief 다음 단어의 길이를 인자를 이용하여 반환한다.

@return BOOL : 정상 작동시 true, 아닌 경우 false 반환

@param offset_first : 다음 단어 시작 오프셋 리턴
@param out_len : 단어의 갯수
*/
//------------------------------------------------------------------------------
//	다음 단어 반환
//
//	:첫 번째 인자 = 다음 단어 시작 오프셋 리턴
//	:두 번째 인자 = 단어 길이 리턴
//------------------------------------------------------------------------------
BOOL CTextParser::GetNextWord(WCHAR **offset_first, UINT64 *out_len)
{

	//현재 문자 값
	WCHAR current_ch = L'\0';

	WCHAR *offset_skip = *offset_first;

	//------------------------------------------------------------------------------
	//프로바이더 시작 포인터 설정 여부 체크한다.
	//------------------------------------------------------------------------------
	if (NULL == offset_skip){

		return false;
	}

	UINT64 len_skip = 0;
	//------------------------------------------------------------------------------
	//단어 구분 시작 문자 이전의 불필요한 문자(주석, 공백)를 스킵한다.
	//------------------------------------------------------------------------------
	SkipNoneCommand(offset_skip, &len_skip);
	offset_skip = offset_skip + len_skip;


	//------------------------------------------------------------------------------
	//*단어 구분 문자들을 통해 단어 구분한다.
	//------------------------------------------------------------------------------
	for (UINT64 len_word = 0; ((current_ch = *(offset_skip + len_word)) != L'\0'); len_word++)
	{

		//------------------------------------------------------------------------------
		//*해당 문자가 구분 문자 여부를 검사한다.
		//------------------------------------------------------------------------------
		for (UINT64 ci = 0; ci < _cnt_symbol_delimiter ; ci++)
		{
			//------------------------------------------------------------------------------
			//*해당 문자가 구분 단어인 경우를 체크한다.
			//------------------------------------------------------------------------------
			if (current_ch == _symbol_delimiter[ci])
			{
				//길이 반환 및 시작 오프셋 재설정 후 반환한다.
				*offset_first = offset_skip;
				*out_len = len_word;
				return true;
			}

		}
	}


	//단어 구분 실패 반환한다.
	*out_len = -1;
	return false;

}



/**
@brief 단어 이전의 불필요한 문자를 스킵한다.

@return BOOL : 정상 작동시 true, 아닌 경우 false 반환

@param offset_first : 시작 오프셋

@param out_len : 스킵 할 문자 길이
*/
//------------------------------------------------------------------------------
//	스킵 : 스페이스, 텝, 엔터, 주석
//
//	:단어 구분 시작 문자 이전의 불필요한 문자를 스킵
//------------------------------------------------------------------------------
BOOL CTextParser::SkipNoneCommand(WCHAR * offset_first, UINT64 *out_len)
{

	//현재 문자 값
	WCHAR current_ch = L'\0';

	WCHAR *offset_skip = offset_first;

	//스킵 문자열 길이
	UINT64 len_skip = 0;

	//주석 플래그
	BOOL is_commant = false;

	if (offset_skip == NULL){

		return false;
	}



	UINT64 len_commant = 0;
	//------------------------------------------------------------------------------
	//*루프 : 주석( '//', '/*') 및 구분 단어들을 건너뛴다.
	//------------------------------------------------------------------------------
	while ((current_ch = *(offset_skip + len_skip)) != L'\0')
	{

		//------------------------------------------------------------------------------
		//주석 '//'인 경우를 체크한다.
		//------------------------------------------------------------------------------
		if (SkipDoubleSlash(offset_skip + len_skip, &len_commant)){

			len_skip += len_commant;
			continue;
		}

		//------------------------------------------------------------------------------
		//주석 '/*'인 경우를 체크한다.
		//------------------------------------------------------------------------------
		if (SkipSlashStar(offset_skip + len_skip, &len_commant)) {

			len_skip += len_commant;
			continue;
		}

		//------------------------------------------------------------------------------
		//단일 슬래쉬 ('/') 문자인 경우
		//------------------------------------------------------------------------------
		if (current_ch == '/')
		{
			//스킵 오프셋 길이 증가
			len_skip++;
			continue;
		}


		//------------------------------------------------------------------------------
		//해당 문자가 구분 문자 여부 체크한다.
		//------------------------------------------------------------------------------
		for (UINT64 ic = 0; ic < _cnt_symbol_delimiter; ic++){

			//------------------------------------------------------------------------------
			//구분 문자인 경우
			//스킵을 계속 진행해야 한다.
			//------------------------------------------------------------------------------
			if (current_ch == _symbol_delimiter[ic]){

				len_skip++;
				break;
			}

			//------------------------------------------------------------------------------
			//해당 문자가 단어 시작인 경우인 경우
			//오프셋 반환 후 함수 리턴한다.
			//------------------------------------------------------------------------------
			else if (ic + 1 == _cnt_symbol_delimiter){

				//길이 반환
				*out_len = len_skip;
				return true;
			}
		}
	}


	//------------------------------------------------------------------------------
	//오프셋 검출 실패 경우
	//------------------------------------------------------------------------------
	*out_len = -1;
	return false;
}



/**
@brief 파서한 킷값에 대응하는 데이터 값을 반환한다. (오버라이딩)

@return BOOL : 정상 작동시 true, 아닌 경우 false 반환

@param str_key : 킷값

@param out_value : 반환 값이 true인 경우, 킷값에 대응하는 데이터 값
*/
BOOL CTextParser::GetValue(CONST WCHAR * str_key, UINT64 * out_value)
{

	//단어 단위(구분 문자로 분류되는) 저장 버퍼
	WCHAR current_word[1000] = { 0, };

	//단어 문자열 길이
	UINT64 len_word = 0;

	//시작 오프셋 설정 및 문자열 형식화
	WCHAR *offset_skip = _first_offset_in_provider;
	WCHAR ch = L'\0';


	//------------------------------------------------------------------------------
	//해당 프로바이더 범위 내에서 킷값이 존재 시 매칭되는 데이터 값을 반환한다.
	//------------------------------------------------------------------------------
	for (; (GetNextWord(&offset_skip, &len_word)); offset_skip = offset_skip + len_word) {

		//단어 단위 복사를 한다.
		memcpy(current_word, offset_skip, sizeof(WCHAR) * len_word);
		//문자열화 한다.
		current_word[len_word] = L'\0';


		//------------------------------------------------------------------------------
		//프로바이더 범위가 끝나는 경우('}')까지 킷값을 찾지 못한 경우
		//------------------------------------------------------------------------------
		if (0 == wcscmp(_symbol_brace_in_provider[1], current_word)) {

			return false;
		}

		//------------------------------------------------------------------------------
		//킷값을 프로바이더 범위 내에서 존재하는 경우
		//------------------------------------------------------------------------------
		if (0 == wcscmp(str_key, current_word))
		{

			//다음 단어 시작 오프셋 재지정한다.
			offset_skip = offset_skip + len_word;


			//------------------------------------------------------------------------------
			//	다음 단어를 반환한다.
			//------------------------------------------------------------------------------
			if (!GetNextWord(&offset_skip, &len_word)) {

				return false;
			}

			//버퍼에 단어 단위 복사를 한다.
			memcpy(current_word, offset_skip, sizeof(WCHAR) * len_word);
			//문자열화 한다.
			current_word[len_word] = L'\0';


			//------------------------------------------------------------------------------
			//킷값 바로 다음 단어 단위가 대입 기호('=')인지 검사한다.
			//------------------------------------------------------------------------------
			if (0 == wcscmp(_symbol_assignment, current_word))
			{

				//다음 단어 시작 오프셋 재지정한다.
				offset_skip = offset_skip + len_word;

				//------------------------------------------------------------------------------
				//다음 단어를 반환한다.
				//------------------------------------------------------------------------------
				if (!GetNextWord(&offset_skip, &len_word)) {

					return false;
				}

				//버퍼에 단어 단위 복사를 한다.
				memcpy(current_word, offset_skip, sizeof(WCHAR) * len_word);
				//문자열화 한다.
				current_word[len_word] = L'\0';


				//------------------------------------------------------------------------------
				//킷값에 대응하는 데이터 값 반환한다.
				///@ todo : 키에 대응하는 값이 숫자인지 여부 체크하는 예외처리가 필요하다.
				//------------------------------------------------------------------------------
				*out_value = _wtoi(current_word);
				return true;
			}
		}//끝: 킷값을 프로바이더 범위 내에서 검출한 경우 
	}
}




/**
@brief 파서한 킷값에 대응하는 데이터 값을 반환한다. (오버라이딩)

@return BOOL : 정상 작동시 true, 아닌 경우 false 반환

@param str_key : 킷값

@param out_value : 반환 값이 true인 경우, 킷값에 대응하는 데이터 값
*/
BOOL CTextParser::GetValue(CONST WCHAR * str_key, WCHAR **out_value)
{

	//단어 단위(구분 문자로 분류되는) 저장 버퍼
	WCHAR *current_word = new WCHAR[1000];

	//단어 문자열 길이
	UINT64 len_word = 0;

	//시작 오프셋 설정 및 문자열 형식화
	WCHAR *offset_skip = _first_offset_in_provider;
	WCHAR ch = L'\0';


	//------------------------------------------------------------------------------
	//해당 프로바이더 범위 내에서 킷값이 존재 시 매칭되는 데이터 값을 반환한다.
	//------------------------------------------------------------------------------
	for (; (GetNextWord(&offset_skip, &len_word)); offset_skip = offset_skip + len_word) {

		//단어 단위 복사를 한다.
		memcpy(current_word, offset_skip, sizeof(WCHAR) * len_word);
		//문자열화 한다.
		current_word[len_word] = L'\0';


		//------------------------------------------------------------------------------
		//프로바이더 범위가 끝나는 경우('}')까지 킷값을 찾지 못한 경우
		//------------------------------------------------------------------------------
		if (0 == wcscmp(_symbol_brace_in_provider[1], current_word)) {

			return false;
		}

		//------------------------------------------------------------------------------
		//킷값을 프로바이더 범위 내에서 존재하는 경우
		//------------------------------------------------------------------------------
		if (0 == wcscmp(str_key, current_word))
		{

			//다음 단어 시작 오프셋 재지정한다.
			offset_skip = offset_skip + len_word;


			//------------------------------------------------------------------------------
			//	다음 단어를 반환한다.
			//------------------------------------------------------------------------------
			if (!GetNextWord(&offset_skip, &len_word)) {

				return false;
			}

			//버퍼에 단어 단위 복사를 한다.
			memcpy(current_word, offset_skip, sizeof(WCHAR) * len_word);
			//문자열화 한다.
			current_word[len_word] = L'\0';


			//------------------------------------------------------------------------------
			//킷값 바로 다음 단어 단위가 대입 기호('=')인지 검사한다.
			//------------------------------------------------------------------------------
			if (0 == wcscmp(_symbol_assignment, current_word))
			{

				//다음 단어 시작 오프셋 재지정한다.
				offset_skip = offset_skip + len_word;

				//------------------------------------------------------------------------------
				//다음 단어를 반환한다.
				//------------------------------------------------------------------------------
				if (!GetNextWord(&offset_skip, &len_word)) {

					return false;
				}

				//버퍼에 단어 단위 복사를 한다.
				memcpy(current_word, offset_skip, sizeof(WCHAR) * len_word);
				//문자열화 한다.
				current_word[len_word] = L'\0';


				//------------------------------------------------------------------------------
				//킷값에 대응하는 데이터 값 반환한다.
				///@ todo : 키에 대응하는 값이 숫자인지 여부 체크하는 예외처리가 필요하다.
				//------------------------------------------------------------------------------
				*out_value = current_word;
				return true;
			}
		}//끝: 킷값을 프로바이더 범위 내에서 검출한 경우 
	}
}



/**
@brief 주석 ('//')인 경우를 체크하여 성립하는 경우 out_len에 주석이 걸린 길이를 반환한다.

@return BOOL : 정상 작동시 true, 아닌 경우 false 반환

@param offset_first : 시작 오프셋

@param out_len : 반환 값이 true인 경우, 주석이 걸린 길이
*/
BOOL CTextParser::SkipDoubleSlash(WCHAR *offset_first, UINT64 *out_len) {

	UINT64 next_ch = L'\0';

	WCHAR *current_offset = offset_first;
	WCHAR current_ch = *current_offset;

	UINT64 len_skip = 0;

	if (current_ch == '/') {

		next_ch = *(current_offset + 1);

		//*주석 '//'이 성립한다.
		if (next_ch == '/') {

			UINT64 i = 2;
			for (; L'\0' != (current_ch = *(current_offset + i)); i++) {

				
				//라인 피드 또는 캐리지 리턴를 만나는 경우 '//'주석은 끝이 난다.
				if (current_ch == 0x0a || current_ch == 0x0d || current_ch == '\n') {

					i++;
					len_skip = i;
					*out_len = len_skip;
					return true;
				}
			}

			i++;
			len_skip = i;
			*out_len = len_skip;
			return true;
		}
		else {

			return false;
		}

	}
	else {

		return false;
	}


}



/**
@brief 주석 ('/*')인 경우를 체크하여 성립하는 경우 out_len에 주석이 걸린 길이를 반환한다.

@return BOOL : 정상 작동시 true, 아닌 경우 false 반환

@param offset_first : 시작 오프셋

@param out_len : 반환 값이 true인 경우, 주석이 걸린 길이
*/
BOOL CTextParser::SkipSlashStar(WCHAR *offset_first, UINT64 *out_len) {

	UINT64 next_ch = L'\0';

	WCHAR *current_offset = offset_first;
	WCHAR current_ch = *current_offset;

	UINT64 len_skip = 0;

	if (current_ch == '/') {

		next_ch = *(current_offset + 1);

		//*주석 '/*'이 성립한다.
		if (next_ch == '*') {

			UINT64 i = 2;
			for (; L'\0' != (current_ch = *(current_offset + i)); i++) {

				// '*/'을 만나면 '/*'주석은 끝이 난다.
				if (current_ch == '*') {

					i++;
					next_ch = *(current_offset + i);

					// '*/'이 성립되는 경우이다.
					if (next_ch = '/') {

						i++;
						len_skip = i;
						*out_len = len_skip;
						return true;
					}
				}
			}

			i++;
			len_skip = i;
			*out_len = len_skip;
			return true;
		}
		else {

			return false;
		}

	}
	else {

		return false;
	}


}