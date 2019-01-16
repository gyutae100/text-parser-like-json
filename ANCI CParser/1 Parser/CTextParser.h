///@mainpage    �����ڵ� �ؽ�Ʈ �ļ� Ŭ���� 
///@section intro �Ұ�
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

	char _text_buf[BUF_SET::BUF_SIZE]; ///<�о�� �ؽ�Ʈ ������ ������ ����

	int _len_str;					   ///<�о�� �ؽ�Ʈ �� ���� �� ����


	static const int max_len_text_path = 100; ///<�ִ� �ؽ�Ʈ ��� ���� ũ��
	char _text_path[max_len_text_path];       ///<�ļ� ��� �ؽ�Ʈ ���

	bool _use_provider;					///<���ι��̴� ���� ����
	char _provider_name[100];			///<���� ������ ���ι��̴� �̸�
	char *_first_offset_in_provider;	///<���ι��̴� ���� ���� ���� ���� ���ι��̴� 
									    ///<���� ��ȣ '{' ������ ���� �ּҸ� ����Ű�� ������ 

	static const int _cnt_symbol_delimiter = 8;				///<���й��� �� ����
	const char _symbol_delimiter[_cnt_symbol_delimiter] =   ///<���� ���� ���� ����
	{
		',',	//�ĸ�
		'.',	//��ħǥ
		'"',	//����ǥ
		0x20, //�����̽�
		0x08, //�齺���̽�
		0x09, //��
		0x0a, //���� �ǵ�
		0x0d, //ĳ���� ����
		 //'/'   //�ּ�
		//'=' ,  //���� ��ȣ
	};

	const char _symbol_command[3][3] = ///<�ּ� ���� ����
	{
		"//",
		"/*",
		"*/"
	};

	const char _declear_provider_symbol = ':'; ///<���ι��̴� �̸� �տ� �ٴ� ��ȣ

	const char _symbol_brace_in_provider[2][2] =  ///<���ι��̴� ���� ���� �� ���� �� ��ȣ ����
	{
		"{",
		"}"
	}; 

	const char *_symbol_assignment = "="; ///< ���� ��ȣ ����


public:

	//*	������ 1
	CTextParser();

	//*	������ 2
	CTextParser(const char * textpath);

	//*�ļ� ��� �ؽ�Ʈ ��θ� �����Ѵ�. 
	bool SetTextPath(const char * textpath);
	
	//*�ļ� ��� �ؽ�Ʈ ������ Ŭ���� �� ���ۿ� �����Ѵ�.
	bool ReadTextFile();
	
	//*���ι��̴� ������ �����Ѵ�. 
	bool SetProviderName(const char *provider_name);

	//*���ι��̴��� �����Ѵ�.
	bool SetProvider(const char *provider_name = NULL);

	//*���� �ܾ� ��ȯ�Ѵ�.
	bool GetNextWord(char **inout_ptr_ch, int *ptr_len);
	
	//*�ܾ� ���� ���� ���� ������ ���ʿ��� ���ڸ� ��ŵ�Ѵ�.
	bool SkipNoneCommand(char * inout_ptr_ch, int *out_len);

	//*�� ��ȯ�Ѵ�. (�������̵� ������ �� int��)
	bool GetValue(const char * szName, int * outValue);

	//*�� ��ȯ�Ѵ�. (�������̵� ������ �� string��)
	bool GetValue(const char * szName, char ** outValue);

	//*�ּ� ('//')�� ��츦 üũ�Ͽ� �����ϴ� ��� out_len�� �ּ��� �ɸ� ���̸� ��ȯ�Ѵ�.
	bool SkipSlashStar(char *offset_first, int *out_len);

	//*�ּ� ('/*')�� ��츦 üũ�Ͽ� �����ϴ� ��� out_len�� �ּ��� �ɸ� ���̸� ��ȯ�Ѵ�.
	bool SkipDoubleSlash(char *offset_first, int *out_len);
};







