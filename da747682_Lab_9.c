#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
	struct RecordType* next;
};
// Fill out this structure
struct HashType
{
	struct RecordType* head;
};

// Compute the hash function
int hash(int x, int size)
{
	return x%size;
}

struct HashType* createTable(int size){
	struct HashType* Table = (struct HashType*)malloc(sizeof(struct HashType));
	if(Table == NULL)
	{
		printf("NULL");
		return 0;
	}
	int i;
	for(i = 0; i<size;++i){
		Table[i].head = NULL;
	}
	return Table;
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

void insert(struct HashType* Table, struct RecordType* value, int size){
	int index = hash(value->id, size);
	value->next = Table[index].head;
	Table[index].head = value;
}

// prints the records
void printRecords(struct RecordType pData[],int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray,int hashSz)
{
	int i;
	struct RecordType* data;
	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		if(pHashArray[i].head != NULL){
			printf("\nIndex %d ->",i);
			for(data = pHashArray[i].head; data != NULL; data = data->next){
				printf("\nid: %d name: %c order: %d \n",data->id, data->name, data->order);
			}
		}else{
			prinf("\nNULL");
		}
	}
}
int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	int Size = recordSz;
	struct HashType* Table = createTable(Size);
	int i;
	for(i = 0;i < recordSz; ++i){
		insert(Table, &pRecords[i], Size);
	}
	displayRecordsInHash(Table, Size);
}