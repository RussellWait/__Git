#include "StringHash.h"

using namespace std;


static const unsigned long HASH_OFFSET = 0;
static const unsigned long HASH_A = 1;
static const unsigned long HASH_B = 2;


StringHash::StringHash(const long nTableLength /* = MAX_TABLE_LEN */)
{
	initCryptTable();
	m_tableLength = nTableLength;

	// ��ʼ��hash��
	m_hashIndexTable = new HashTable[nTableLength];
	for (int i = 0; i < nTableLength; i++)
	{
		m_hashIndexTable[i].nHashA	= -1;
		m_hashIndexTable[i].nHashB	= -1;
		m_hashIndexTable[i].bExists	= false;
	}
}

StringHash::~StringHash(void)
{
	if (nullptr != m_hashIndexTable)
	{
		delete []m_hashIndexTable;
		m_hashIndexTable = nullptr;
		m_tableLength = 0;
	}
}

/************************************************************************/
/* ��������	hash
/* ���ܣ�	hashһ���ַ���
/* ����ֵ��	�ɹ�������true��ʧ�ܣ�����false
/************************************************************************/
bool StringHash::hash(string lpszString)
{
	unsigned long nHash = makeHashValue(lpszString, HASH_OFFSET);
	unsigned long nHashStart = nHash % m_tableLength;
	unsigned long nHashPos = nHashStart;

	while (m_hashIndexTable[nHashPos].bExists)
	{
		nHashPos = (nHashPos + 1) % m_tableLength;
		if (nHashPos == nHashStart)
		{
			// hash����û�п����λ���ˣ��޷����hash
			return false;
		}
	}

	m_hashIndexTable[nHashPos].bExists = true;
	m_hashIndexTable[nHashPos].nHashA = makeHashValue(lpszString, HASH_A);
	m_hashIndexTable[nHashPos].nHashB = makeHashValue(lpszString, HASH_B);

	return true;
}

/************************************************************************/
/* ��������	hashed
/* ���ܣ�	���һ���ַ����Ƿ�hash��
/* ����ֵ��	������ڣ�����λ�ã����򣬷���-1
/************************************************************************/
unsigned long StringHash::hashed(string lpszString)
{
	unsigned long nHash = makeHashValue(lpszString, HASH_OFFSET);
	unsigned long nHashA = makeHashValue(lpszString, HASH_A);
	unsigned long nHashB = makeHashValue(lpszString, HASH_B);
	unsigned long nHashStart = nHash % m_tableLength;
	unsigned long nHashPos = nHashStart;

	while (m_hashIndexTable[nHashPos].bExists)
	{
		if (m_hashIndexTable[nHashPos].nHashA == nHashA &&
			m_hashIndexTable[nHashPos].nHashB == nHashB)
		{
			return nHashPos;
		}
		else
		{
			nHashPos = (nHashPos + 1) % m_tableLength;
		}

		if (nHashPos == nHashStart)
		{
			break;
		}
	}

	return -1;
}

/************************************************************************/
/* ��������	initCryptTable
/* ���ܣ�	�Թ�ϣ������Ԥ����
/* ����ֵ��	��
/************************************************************************/
void StringHash::initCryptTable(void)
{
	unsigned long seed = 0x00100001;
	
	for (unsigned long index1 = 0; index1 < 0x100; index1++)
	{
		for (unsigned long index2 = index1, i = 0; i < 5; i++, index2 += 0x100)
		{
			unsigned long temp1, temp2;
			seed = (seed * 125 + 3) % 0x2AAAAB;
			temp1 = (seed & 0xFFFF) << 0x10;
			seed = (seed * 125 + 3) % 0x2AAAAB;
			temp2 = (seed & 0xFFFF);
			m_cryptTable[index2] = (temp1 | temp2);
		}
	}
}

/************************************************************************/
/* ��������	makeHashValue
/* ���ܣ�	��ȡ��ϣֵ
/* ����ֵ��	����hashֵ
/************************************************************************/
unsigned long StringHash::makeHashValue(const string &lpszString, unsigned long dwHashType)
{
	unsigned char *key = (unsigned char *)(const_cast<char *>(lpszString.c_str()));
	unsigned long seed1 = 0x7FED7FED;
	unsigned long seed2 = 0xEEEEEEEE;
	int ch;

	while (*key)
	{
		ch = toupper(*key++);

		seed1 = m_cryptTable[(dwHashType << 8) + ch] ^ (seed1 + seed2);
		seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
	}

	return seed1;
}
