///@mainpage    �����ڵ� �ؽ�Ʈ �ļ� Ŭ���� 
///@section UINT64ro �Ұ�
///- �κ�1 : �����ڵ� �ؽ�Ʈ ������ �о�ͼ� ���ۿ� �����Ѵ�. 
///- �κ�2 : �����ڵ� �ؽ�Ʈ ���� ���� �����ϴ� �ּ� ��Ÿ��( //, /*)�� �ڵ� �����Ѵ�.
///- �κ�3 : �����ڵ� �� �����ϴ� ���� ���Ŀ� �°� ���� ���� �����ϴ� ���ι��̴�(������)�� �˻��Ѵ�.
///- �κ�4 : ���ι��̴�(������)�� �����ϸ� ������ ���ο� �����ϴ� ��ġ �̸��� ��ġ �̸��� �ϴ��� ���� �Ǵ� �ش� ��ġ ���� �˻��Ѵ�.
///- �κ�5 : ��ġ �̸��� �ش� ��ġ ���� �����ϴ� ��� ���α׷� ���� ������ ������ �ش� ��ġ �̸��� �ش� ��ġ ���� �����Ѵ�.
///@section Program ���α׷���
///- ���α׷� ��  :   CTextParser
///- ���α׷� ����    : �����ڵ� ���� �ؽ�Ʈ ���� ���� �����ϴ� ��ġ �̸��� �ϴ��� ���� �Ǵ� �ش� ��ġ ���� ���α׷� �ڵ� �� ������ ������ �����Ѵ�.
///@section CREATEINFO �ۼ�����
///- �ۼ���      :   �����(gyutae100@gmail.com)
///- �ۼ���      :   2018/04/24
///@section MODIFYINFO ��������
///- ������/������   : �ۼ��ڿ� ����
///- 2018.05.22    : Doxygen �ּ�ȭ
///-@version 1.0


#pragma once


/**
@class CTextParser

@brief �����ڵ� ���� �ؽ�Ʈ ���� ���� �����ϴ� ��ġ �̸��� �ϴ��� ���� �Ǵ� �ش� ��ġ ���� 
       ���α׷� �ڵ� �� ������ ������ �����Ѵ�.
*/
class CTextParser{

private:

	/**
	@enum BUF_SET

	@brief �����ڵ� �ؽ�Ʈ ���� ���� ������ ����
	*/
	typedef enum BUF_SET{
		BUF_SIZE = 1000
	}BUF_SET;

	WCHAR _text_buf[BUF_SET::BUF_SIZE]; ///<�о�� �ؽ�Ʈ ������ ������ ����

	UINT64 _len_str;					   ///<�о�� �ؽ�Ʈ �� ���� �� ����


	static CONST UINT64 max_len_text_path = 100; ///<�ִ� �ؽ�Ʈ ��� ���� ũ��
	WCHAR _text_path[max_len_text_path];       ///<�ļ� ��� �ؽ�Ʈ ���

	BOOL _use_provider;					///<���ι��̴� ���� ����
	WCHAR _provider_name[100];			///<���� ������ ���ι��̴� �̸�
	WCHAR *_first_offset_in_provider;	///<���ι��̴� ���� ���� ���� ���� ���ι��̴� 
									    ///<���� ��ȣ '{' ������ ���� �ּҸ� ����Ű�� ������ 

	static CONST UINT64 _cnt_symbol_delimiter = 8;				///<���й��� �� ����
	CONST WCHAR _symbol_delimiter[_cnt_symbol_delimiter] =   ///<���� ���� ���� ����
	{
		',',	//�ĸ�
		'.',	//��ħǥ
		'"',	//����ǥ
		0x20, //�����̽�
		0x08, //�齺���̽�
		0x09, //��
		0x0a, //���� �ǵ�
		0x0d //ĳ���� ����
	};

	CONST WCHAR _symbol_command[3][3] = ///<�ּ� ���� ����
	{
		L"//",
		L"/*",
		L"*/"
	};

	CONST WCHAR _declear_provider_symbol = L':'; ///<���ι��̴� �̸� �տ� �ٴ� ��ȣ

	CONST WCHAR _symbol_brace_in_provider[2][2] =  ///<���ι��̴� ���� ���� �� ���� �� ��ȣ ����
	{
		L"{",
		L"}"
	}; 

	CONST WCHAR *_symbol_assignment = L"="; ///< ���� ��ȣ ����


public:

	// ������ 1
	CTextParser();

	// ������ 2
	CTextParser(CONST WCHAR * textpath);

	//�ļ� ��� �ؽ�Ʈ ��θ� �����Ѵ�. 
	BOOL SetTextPath(CONST WCHAR * textpath);
	
	//�ļ� ��� �ؽ�Ʈ ������ Ŭ���� �� ���ۿ� �����Ѵ�.
	BOOL ReadTextFile();

	//���ι��̴� ������ �����Ѵ�. 
	BOOL SetProviderName(CONST WCHAR *provider_name);

	//���ι��̴��� �����Ѵ�.
	BOOL SetProvider(CONST WCHAR *provider_name = NULL);

	//���� �ܾ� ��ȯ�Ѵ�.
	BOOL GetNextWord(WCHAR **inout_ptr_ch, UINT64 *ptr_len);
	
	//�ܾ� ���� ���� ���� ������ ���ʿ��� ���ڸ� ��ŵ�Ѵ�.
	BOOL SkipNoneCommand(WCHAR * inout_ptr_ch, UINT64 *out_len);

	//�� ��ȯ�Ѵ�. (�������̵� ������ �� UINT64��)
	BOOL GetValue(CONST WCHAR * szName, UINT64 * outValue);

	//�� ��ȯ�Ѵ�. (�������̵� ������ �� string��)
	BOOL GetValue(CONST WCHAR * szName, WCHAR ** outValue);

	//�ּ� ('//')�� ��츦 üũ�Ͽ� �����ϴ� ��� out_len�� �ּ��� �ɸ� ���̸� ��ȯ�Ѵ�.
	BOOL SkipSlashStar(WCHAR *offset_first, UINT64 *out_len);

	//�ּ� ('/*')�� ��츦 üũ�Ͽ� �����ϴ� ��� out_len�� �ּ��� �ɸ� ���̸� ��ȯ�Ѵ�.
	BOOL SkipDoubleSlash(WCHAR *offset_first, UINT64 *out_len);
};







