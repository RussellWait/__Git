#pragma once

#include <string>


#define MAX_TABLE_LEN	1024					// Ĭ�Ϲ�ϣ�������С

// ��ϣ��������
typedef struct _HashTable
{
	long nHashA;
	long nHashB;
	bool bExists;
}HashTable, *PHashTable;

// �ඨ��
class StringHash
{
public:
	StringHash(const long nTableLength = MAX_TABLE_LEN);
	virtual ~StringHash(void);

	bool hash(std::string lpszString);
	unsigned long hashed(std::string lpszString);

private:
	void initCryptTable(void);
	unsigned long makeHashValue(const std::string &lpszString, unsigned long dwHashType);

private:
	unsigned long	m_cryptTable[0x500];		// ��ϣ������
	unsigned long	m_tableLength;				// ��ϣ����
	PHashTable		m_hashIndexTable;			// ��ϣ��
};
