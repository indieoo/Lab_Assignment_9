//Dominick Tulshi
//Dr. Neslisah Torosdagli
//4/11/2024
//COP 3502
#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 30

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

struct Node
{
	struct RecordType data;
	struct Node* next;
};

// Fill out this structure
struct HashType
{
	struct Node* head;
};

// Compute the hash function
int hash(int x)
{
	return x % HASH_SIZE;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

void insertRecord(struct HashType* pHashArray, struct RecordType record){
	int index = hash(record.id);
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	if(!newNode){
		printf("Memory Allocation Failed.\n");
		exit(EXIT_FAILURE);
	}
	newNode->data = record;
	newNode->next = NULL;

	if(pHashArray[index].head == NULL){
		pHashArray[index].head = newNode;
	}
	else{
		newNode->next = pHashArray[index].head;
		pHashArray[index].head = newNode;
	}
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;
	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		printf("Index %d ->", 1);
		struct Node* current = pHashArray[1].head;
		while(current != NULL){
			printf("%d, %c, %d -> ", current->data.id, current->data.name, current->data.order);
			current = current->next;
		}
		printf("NULL\n");
	}
}

void freeHashTable(struct HashType* pHashArray, int hashSz){
	int i;
	for(i = 0; i < hashSz; ++i){
		struct Node* current = pHashArray[i].head;
		while(current != NULL){
			struct Node* temp = current;
			current = current->next;
			free(temp);
		}
	}
	free(pHashArray);
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;
	int i;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	struct HashType* pHashArray = (struct HashType*)malloc(sizeof(struct HashType) * HASH_SIZE);
	if (!pHashArray){
		printf("Memory Allocation Failed.\n");
		return EXIT_FAILURE;
	}
	for(i = 0; i < HASH_SIZE; ++i){
		pHashArray[i].head = NULL;
	}
	for(i = 0; i < recordSz; ++i){
		insertRecord(pHashArray, pRecords[i]);
	}

	displayRecordsInHash(pHashArray, HASH_SIZE);
	freeHashTable(pHashArray, HASH_SIZE);

	free(pRecords);

	return 0;
}