#pragma once

#include <string>


#define MAX_TABLE_LEN	1024					// 默认哈希索引表大小

// 哈希索引表定义
typedef struct _HashTable
{
	long nHashA;
	long nHashB;
	bool bExists;
}HashTable, *PHashTable;

// 类定义
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
	unsigned long	m_cryptTable[0x500];		// 哈希索引表
	unsigned long	m_tableLength;				// 哈希表长度
	PHashTable		m_hashIndexTable;			// 哈希表
};
