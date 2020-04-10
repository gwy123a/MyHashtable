#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
 
#define HASH_TABLE_MAX_SIZE   (1000) // Maximum number of elements in Hasharray
 
typedef struct HashNode_struct HashNode;
 
// Define a Hashtable node
struct HashNode_struct
{
	char * sKey;
	int nValue;
	HashNode *pNext;
};
 
HashNode * hashTable[HASH_TABLE_MAX_SIZE]; // Hashtable array
unsigned int g_hash_table_size = 0x0;
 
 
 
// Initialize the Hashtable
void hash_table_init(void)
{
	int i = 0x0;
	memset(hashTable,0,sizeof(HashNode *)*HASH_TABLE_MAX_SIZE);
	g_hash_table_size = 0x0;
 
}
 
 
// String hash function
unsigned int hash_table_hash_string(const char * sKey)
{
	const unsigned  char* p =  (const unsigned  char*) sKey;
	unsigned int value = *p;
 
	if(value)
	{
		for( p += 1; *p != '\0'; p++)
		{
			value = (value << 5) - value + *p;  
		}
	}
 
	return value;
 
}
 
 
//Add nodes to the hash table based on key-value pairs，If skey already exists, update the key-value nValue
//Return 0 if successful, -1 if failed
int hash_table_insert_node(const char * sKey, int nValue)
{
	HashNode * pHashNodeHead   = NULL;
	HashNode * pNewNode = NULL; 
	unsigned int pos = 0x0;
 
	if((g_hash_table_size >= HASH_TABLE_MAX_SIZE )||(NULL  == sKey))
		return -1;
	
	 pos =  hash_table_hash_string(sKey) % HASH_TABLE_MAX_SIZE; //Calculate the corresponding position of sKey in the hash array
 
	 printf("hash_table_insert_node : pos = %d\n",pos);
 
	pHashNodeHead = hashTable[pos];
 
	if(NULL == pHashNodeHead)
	   printf("hash_table_insert_node:NULL == pHashNodeHead\n");	
 
	while(NULL != pHashNodeHead )  // If this position does not correspond to the last node in the string, it has to move backward
    {
		if(strcmp(pHashNodeHead->sKey,sKey) == 0) //If this key-value pair already exists, just update the key-value
		{
			pHashNodeHead ->nValue = nValue;
 
			return 0;
		}
 
		pHashNodeHead = pHashNodeHead->pNext;  //向后移动,肯定会有NULL的时候
	
	}
 
	pNewNode = (HashNode *)malloc(sizeof(HashNode)); //Apply for a HashNode size memory
	if(NULL == pNewNode)
    {
		return -1;
	}
	memset(pNewNode,0,sizeof(HashNode));
 
	pNewNode ->sKey = (char *)malloc(strlen(sKey) + 1); //Apply for a sKey size memory
	if(NULL == pNewNode ->sKey )
	{
		return -1;
	}
	memset(pNewNode ->sKey,0,strlen(sKey) + 1);
 
	strcpy(pNewNode ->sKey,sKey); //Assignment the content of sKey to pNewNode-> sKey
	pNewNode ->nValue = nValue;
 
	pNewNode ->pNext = NULL; //Since it is a new node and also a tail node, pNext points to NULL
 
	pHashNodeHead  = pNewNode;
	hashTable[pos] = pHashNodeHead;
 
	g_hash_table_size ++;
 
	return 0;
 
 
}
 
 
//Print the string of hashes at a position in the array
void print_hash_node(int pos)
{
	HashNode * pHashNodeHead   = NULL;
 
	if(pos >= HASH_TABLE_MAX_SIZE)
		return;
 
	pHashNodeHead = hashTable[pos];
 
	if(NULL == pHashNodeHead)
	   printf("NULL == pHashNodeHead\n");	
	while(NULL != pHashNodeHead)
    {
		printf("come here \n");
		printf("Position:%d, sKey:%s, nValue:%d \n",pos,pHashNodeHead->sKey,pHashNodeHead->nValue);
		pHashNodeHead = pHashNodeHead->pNext;
 
	}
 
 
}
 
// According to the key-value sKey to find the corresponding hash node
HashNode * hash_table_lookup(const char *sKey)
{
	unsigned int pos = 0x0;
	HashNode * pHashHead = NULL;
 
	if(NULL == sKey)
	{
		return NULL;
	}
 
	pos = hash_table_hash_string(sKey) % HASH_TABLE_MAX_SIZE; //Calculate the position in the Hasharray
 
	pHashHead = hashTable[pos];
	
	while(NULL != pHashHead)
	{
		if(strcmp(sKey,pHashHead->sKey) == 0)//Find
			return pHashHead;
 
		pHashHead = pHashHead->pNext; // If not found, go to the next node
	}
 
	return NULL;
 
}
 
 
 
void main(void)
{
	char * pSkey = "abcd";
	int nValue = 1234;
	int ret = -1;
	int pos = 0xffffffff;
	HashNode * pHashNode = NULL;
 
	hash_table_init();
	ret = hash_table_insert_node(pSkey,nValue);
 
	printf("ret = %d\n",ret);
 
 
	if(!ret)
    {
		pos = hash_table_hash_string(pSkey) % HASH_TABLE_MAX_SIZE;
		printf("main:  pos = %d\n",pos);
		print_hash_node(pos);
	}
 
	pHashNode = hash_table_lookup(pSkey);
 
	if(NULL != pHashNode)
	{
		printf("Got it: sKey:%s, nValue: %d\n",pHashNode->sKey,pHashNode->nValue);
	}
 
	
}