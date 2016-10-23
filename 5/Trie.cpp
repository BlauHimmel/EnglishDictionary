#include "stdafx.h"
#include "Trie.h"

#define VISIT()

CTrieTree::~CTrieTree()
{
	Destroy(pRoot);
}

CTrieTree::CTrieTree()
{
	pRoot = new CTrieNode();
}

void CTrieTree::Destroy(CTrieNode* pNode)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (pNode->pChild[i] != NULL)
		{
			Destroy(pNode->pChild[i]);
		}
	}
	if (pNode != NULL)
	{
		delete pNode->pIndex;
		pNode->pIndex = NULL;
		delete pNode;
		pNode = NULL;
	}
}

bool CTrieTree::Init()
{
	ifstream IndexFileIn("Index.data", ios::binary);
	ifstream DataFileIn("DATA.data");

	if ((!IndexFileIn) || (!DataFileIn))
	{
		return false;
	}

	IndexFileIn.seekg(0, ios::end);
	int nFileSize = (int)IndexFileIn.tellg() - 0;
	IndexFileIn.seekg(0, ios::beg);

	int* nzIndex = new int[4];

	while (true)
	{
		/*
		0 nEngPos, 1 nEngLen, 2 nChPos, 3 nChLen
		*/
		if (!IndexFileIn.read((char*)nzIndex, 4 * sizeof(int)))
		{
			return false;
		}

		char* lpszEngBuffer = new char[nzIndex[1]];
		char* lpszChBuffer = new char[nzIndex[3]];

		if (lpszChBuffer == NULL || lpszEngBuffer == NULL)
		{
			return false;
		}

		DataFileIn.seekg(nzIndex[0], ios::beg);
		DataFileIn.getline(lpszEngBuffer, nzIndex[1]);
		DataFileIn.seekg(nzIndex[2], ios::beg);
		DataFileIn.getline(lpszChBuffer, nzIndex[3]);

		Insert(lpszEngBuffer, nzIndex[0], nzIndex[1], nzIndex[2], nzIndex[3]);

		delete[] lpszEngBuffer;
		delete[] lpszChBuffer;
		if ((int)IndexFileIn.tellg() == nFileSize)
		{
			break;
		}
	}
	delete[] nzIndex;
	IndexFileIn.close();
	DataFileIn.close();
	return true;
}

void CTrieTree::Clear()
{
	Destroy(pRoot);
}

CIndexInfo* CTrieTree::Search(char* lpszVocabulary)
{
	CTrieNode* pCurrent = pRoot;
	while (*lpszVocabulary&&pCurrent)
	{
		pCurrent = pCurrent->pChild[*lpszVocabulary - 'a'];
		lpszVocabulary++;
	}
	if (pCurrent != NULL&&pCurrent->enumType == COMPLETE)
	{
		return pCurrent->pIndex;
	}
	else
	{
		return NULL;
	}
}

bool CTrieTree::Insert(char* lpszVocabulary, int nEngPos, int nEngLen, int nChPos, int nChLen, NodeType enumType/* = COMPLETE*/)
{
	CTrieNode* pCurrent = pRoot;
	while (*lpszVocabulary)
	{
		if (isupper(*lpszVocabulary))
		{
			*lpszVocabulary = tolower(*lpszVocabulary);
		}
		if (pCurrent->pChild[*lpszVocabulary - 'a'] == NULL)
		{
			CTrieNode* pNewNode = new CTrieNode(*lpszVocabulary);
			if (pNewNode == NULL)
			{
				return false;
			}
			pCurrent->pChild[*lpszVocabulary - 'a'] = pNewNode;
		}
		pCurrent = pCurrent->pChild[*lpszVocabulary - 'a'];
		lpszVocabulary++;
	}
	if (pCurrent->enumType == COMPLETE)
	{
		return false;
	}
	pCurrent->enumType = enumType;
	pCurrent->pIndex = new CIndexInfo(nEngPos, nEngLen, nChPos, nChLen);
	return true;
}

bool CTrieTree::Insert(char* lpszVocabulary, char* lpszTranslation)
{
	if (!Insert(lpszVocabulary, 0, 0, 0, 0, NEWLY_INSERTED_WORD))
	{
		return false;
	}
	if (!DataFileRewrite(lpszVocabulary, lpszTranslation))
	{
		return false;
	}
	return true;
} 

bool CTrieTree::Delete(char* lpszVocabulary)
{
	CTrieNode* pCurrent = pRoot;
	while (*lpszVocabulary&&pCurrent)
	{
		if (isupper(*lpszVocabulary))
		{
			*lpszVocabulary = tolower(*lpszVocabulary);
		}
		pCurrent = pCurrent->pChild[*lpszVocabulary - 'a'];
		lpszVocabulary++;
	}
	if (pCurrent != NULL&&pCurrent->enumType == COMPLETE)
	{
		pCurrent->enumType = UNCOMPLETE;
		delete pCurrent->pIndex;
		pCurrent->pIndex = NULL;
		DataFileRewrite();
		return true;
	}
	else
	{
		return false;
	}
}

bool CTrieTree::CreateDataFile(ifstream &FileIn)
{
	Clear();
	pRoot = new CTrieNode();
	ofstream FileOut("DATA.data");
	ofstream IndexFileOut("Index.data", ios::binary);
	if (!FileOut)
	{
		return false;
	}

	int* nzIndex = new int[4];
	char* lpszEngBuffer = new char[20];
	char* lpszChBuffer = new char[50];

	while (!FileIn.eof())
	{
		FileIn.getline(lpszEngBuffer, 20);
		FileIn.getline(lpszChBuffer, 100);

		int nEngPos = FileOut.tellp();
		FileOut << lpszEngBuffer;
		FileOut << '\n';
		int nEngLen = (int)FileOut.tellp() - nEngPos + 1;

		int nChPos = FileOut.tellp();
		FileOut << lpszChBuffer;
		FileOut << '\n';
		int nChLen = (int)FileOut.tellp() - nChPos + 1;

		Insert(lpszEngBuffer, nEngPos, nEngLen, nChPos, nChLen);

		nzIndex[0] = nEngPos;
		nzIndex[1] = nEngLen;
		nzIndex[2] = nChPos;
		nzIndex[3] = nChLen;
		IndexFileOut.write((char*)nzIndex, 4 * sizeof(int));
	}
	delete[] lpszChBuffer;
	delete[] lpszEngBuffer;
	delete[] nzIndex;

	FileIn.close();
	FileOut.close();
	IndexFileOut.close();

	return true;
}

bool CTrieTree::DataFileRewrite(char* lpszVocabulary/* = NULL */, char* lpszTranslation/* =NULL */)
{
	ofstream NewIndexFile("Index_temp.data", ios::binary);
	ofstream NewDataFile("DATA_temp.data");
	ifstream DataFile("DATA.data");

	if ((!NewDataFile) || (!DataFile))
	{
		return false;
	}

	queue<CTrieNode*> queueDFS;

	queueDFS.push(pRoot);

	while (!queueDFS.empty())
	{
		CTrieNode* pTemp = queueDFS.front();
		queueDFS.pop();
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (pTemp->pChild[i] != NULL)
			{
				queueDFS.push(pTemp->pChild[i]);
			}
		}

		if (pTemp->enumType == COMPLETE)
		{
			char* lpszEngBuffer = new char[pTemp->pIndex->nEngLen];
			char* lpszChBuffer = new char[pTemp->pIndex->nChLen];

			DataFile.seekg(pTemp->pIndex->nEngPos, ios::beg);
			DataFile.getline(lpszEngBuffer, pTemp->pIndex->nEngLen);
			DataFile.seekg(pTemp->pIndex->nChPos, ios::beg);
			DataFile.getline(lpszChBuffer, pTemp->pIndex->nChLen);

			/*0 nEngPos,1 nEngLen,2 nChPos,3 nChLen*/
			int* nzIndex = new int[4];

			nzIndex[0] = NewDataFile.tellp();
			NewDataFile << lpszEngBuffer;
			NewDataFile << '\n';
			nzIndex[1] = (int)NewDataFile.tellp() - nzIndex[0] + 1;
			nzIndex[2] = NewDataFile.tellp();
			NewDataFile << lpszChBuffer;
			NewDataFile << '\n';
			nzIndex[3] = (int)NewDataFile.tellp() - nzIndex[2] + 1;

			NewIndexFile.write((char*)nzIndex, 4 * sizeof(int));

			CIndexInfo* pTempIndex = new CIndexInfo(nzIndex[0], nzIndex[1], nzIndex[2], nzIndex[3]);
			delete pTemp->pIndex;
			pTemp->pIndex = pTempIndex;

			delete[] nzIndex;
			delete[] lpszChBuffer;
			delete[] lpszEngBuffer;
		}
		else if (pTemp->enumType == NEWLY_INSERTED_WORD)
		{
			/*0 nEngPos,1 nEngLen,2 nChPos,3 nChLen*/
			int* nzIndex = new int[4];

			nzIndex[0] = NewDataFile.tellp();
			NewDataFile << lpszVocabulary;
			NewDataFile << '\n';
			nzIndex[1] = (int)NewDataFile.tellp() - nzIndex[0] + 1;
			nzIndex[2] = NewDataFile.tellp();
			NewDataFile << lpszTranslation;
			NewDataFile << '\n';
			nzIndex[3] = (int)NewDataFile.tellp() - nzIndex[2] + 1;

			NewIndexFile.write((char*)nzIndex, 4 * sizeof(int));

			CIndexInfo* pTempIndex = new CIndexInfo(nzIndex[0], nzIndex[1], nzIndex[2], nzIndex[3]);
			pTemp->pIndex = pTempIndex;
			pTemp->enumType = COMPLETE;

			delete[] nzIndex;
		}
	}

	DataFile.close();
	NewDataFile.close();
	NewIndexFile.close();

	DeleteFile(_T("DATA.data"));
	rename("DATA_temp.data", "DATA.data");
	DeleteFile(_T("Index.data"));
	rename("Index_temp.data", "Index.data");


	return true;
}

char* CStringToChar(CString &cstr)
{
	int nLength = WideCharToMultiByte(CP_ACP, 0, cstr, cstr.GetLength(), NULL, 0, NULL, NULL);
	char* pBuffer = new char[nLength + 1];
	WideCharToMultiByte(CP_ACP, 0, cstr, cstr.GetLength(), pBuffer, nLength, NULL, NULL);
	pBuffer[nLength] = '\0';
	return pBuffer;
}