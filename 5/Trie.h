
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
	节点类型
*/
enum NodeType
{
	COMPLETE,
	UNCOMPLETE,
	NEWLY_INSERTED_WORD
};

/*
	单词索引节点，存有英语和中文开始的文件指针值和相应的长度
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
	树节点类型，存有节点状态、相应的字母和索引节点和子节点指针
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
	字典树
*/
class CTrieTree
{
public:
	CTrieTree();
	~CTrieTree();
	bool Init();
	/*
		查找当前英语单词,返回一个索引结构体的指针
	*/
	CIndexInfo* Search(char* lpszVocabulary);
	/*
		当DATA文件中没有单词时插入单词资料
		调用后会重写DATA文件
	*/
	bool Insert(char* lpszVocabulary, char* lpszTranslation);
	/*
		删除相应的单词
		调用后会重写DATA和INDEX文件
	*/
	bool Delete(char* lpszVocabulary);
	/*
		通过外部的TXT文件创建DATA文件并生成一个INDEX文件
	*/
	bool CreateDataFile(ifstream &FileIn);
	/*
		清空当前树
	*/
	void Clear();
	CTrieNode* GetRoot()
	{
		return pRoot;
	}
private:
	/*
		最后一个参数仅在向词库导入新词时填写NEWLY_INSERTED_WORD

		把DATA文件中的资料导入时调用这个函数
		调用后不会重写DATA和INDEX文件
	*/
	bool Insert(char* lpszVocabulary, int nEngPos, int nEngLen, int nChPos, int nChLen, NodeType enumType = COMPLETE);
	/*
		添加单词后重写Data文件时需要填写两个参数
	*/
	bool DataFileRewrite(char* lpszVocabulary = NULL, char* lpszTranslation = NULL);
	void Destroy(CTrieNode* pNode);
	CTrieNode* pRoot;
};

/*
	将CString转化为char*字符串，支持中文
	返回值在不用后需要delete
*/
char* CStringToChar(CString &cstr);

#endif