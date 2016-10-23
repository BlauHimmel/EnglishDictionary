
#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

#define MAX_SIZE 26

/*
	�ڵ�����
*/
enum NodeType
{
	COMPLETE,
	UNCOMPLETE,
	NEWLY_INSERTED_WORD
};

/*
	���������ڵ㣬����Ӣ������Ŀ�ʼ���ļ�ָ��ֵ����Ӧ�ĳ���
*/
class CIndexInfo
{
public:
	int nEngPos;
	int nEngLen;
	int nChPos;
	int nChLen;
	CIndexInfo(int nEngP = 0, int nEngL = 0, int nChP = 0, int nChL = 0)
	{
		nEngPos = nEngP;
		nEngLen = nEngL;
		nChPos = nChP;
		nChLen = nChL;
	}
	void SetIndex(int nEngP = 0, int nEngL = 0, int nChP = 0, int nChL = 0)
	{
		nEngPos = nEngP;
		nEngLen = nEngL;
		nChPos = nChP;
		nChLen = nChL;
	}
};

/*
	���ڵ����ͣ����нڵ�״̬����Ӧ����ĸ�������ڵ���ӽڵ�ָ��
*/
class CTrieNode
{
public:
	NodeType enumType;
	char sAlphabet;
	CTrieNode* pChild[MAX_SIZE];
	CIndexInfo* pIndex;
	CTrieNode(char sAlp = 0)
	{
		sAlphabet = sAlp;
		enumType = UNCOMPLETE;
		pIndex = NULL;
		for (int i = 0; i < MAX_SIZE; i++)
		{
			pChild[i] = NULL;
		}
	}
};

/*
	�ֵ���
*/
class CTrieTree
{
public:
	CTrieTree();
	~CTrieTree();
	bool Init();
	/*
		���ҵ�ǰӢ�ﵥ��,����һ�������ṹ���ָ��
	*/
	CIndexInfo* Search(char* lpszVocabulary);
	/*
		��DATA�ļ���û�е���ʱ���뵥������
		���ú����дDATA�ļ�
	*/
	bool Insert(char* lpszVocabulary, char* lpszTranslation);
	/*
		ɾ����Ӧ�ĵ���
		���ú����дDATA��INDEX�ļ�
	*/
	bool Delete(char* lpszVocabulary);
	/*
		ͨ���ⲿ��TXT�ļ�����DATA�ļ�������һ��INDEX�ļ�
	*/
	bool CreateDataFile(ifstream &FileIn);
	/*
		��յ�ǰ��
	*/
	void Clear();
	CTrieNode* GetRoot()
	{
		return pRoot;
	}
private:
	/*
		���һ������������ʿ⵼���´�ʱ��дNEWLY_INSERTED_WORD

		��DATA�ļ��е����ϵ���ʱ�����������
		���ú󲻻���дDATA��INDEX�ļ�
	*/
	bool Insert(char* lpszVocabulary, int nEngPos, int nEngLen, int nChPos, int nChLen, NodeType enumType = COMPLETE);
	/*
		��ӵ��ʺ���дData�ļ�ʱ��Ҫ��д��������
	*/
	bool DataFileRewrite(char* lpszVocabulary = NULL, char* lpszTranslation = NULL);
	void Destroy(CTrieNode* pNode);
	CTrieNode* pRoot;
};

/*
	��CStringת��Ϊchar*�ַ�����֧������
	����ֵ�ڲ��ú���Ҫdelete
*/
char* CStringToChar(CString &cstr);

#endif