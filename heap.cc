#include <Windows.h>
#include <stdio.h>
#include <vector>

using namespace std;

#define CHUNK_SIZE 0x190
#define ALLOC_COUNT 10

class SomeObject {
public:
	void function1(){
	};
 
	virtual void virtualFunction(){
		printf("test\n");
	};
};

int main(int args, char ** argv){
	int i;
	HANDLE hChunk;
	void * allocations[ALLOC_COUNT];
	SomeObject * objects[5];
	SomeObject * obj = new SomeObject();
	printf("SomeObject address : 0x%08p\n", obj);
	int vectorSize = 40;

	HANDLE defaultHeap = GetProcessHeap();

	for(i = 0; i < ALLOC_COUNT; i++){
	hChunk = HeapAlloc(defaultHeap, 0, CHUNK_SIZE);
	memset(hChunk, 'A', 0x190);
	char return_address_1[] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
	char return_address_2[] = "\xCC\xCC\xCC\xCC";
	char return_address_3[] = "\xDD\xDD\xDD\xDD";
	char payload[] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC";
	// EAX OFFSET = 24
	// EDX offset = 28
	memmove((char *) hChunk + 400, return_address_1, 0x18);
	memmove((char *) hChunk + 424, return_address_2, 0x4);
	memmove((char *) hChunk + 428, return_address_3, 0x4);
	memmove((char *) hChunk + 432, payload, 0x1C);
	allocations[i] = hChunk;

	printf("[%d] Heap chunk in backend : 0x%08x\n", i, hChunk);
	}

	HeapFree(defaultHeap, HEAP_NO_SERIALIZE, allocations[3]);

	vector<SomeObject*> v1(vectorSize, obj);
	vector<SomeObject*> v2(vectorSize, obj);
	vector<SomeObject*> v3(vectorSize, obj);
	vector<SomeObject*> v4(vectorSize, obj);
	vector<SomeObject*> v5(vectorSize, obj);
	vector<SomeObject*> v6(vectorSize, obj);
	vector<SomeObject*> v7(vectorSize, obj);
	vector<SomeObject*> v8(vectorSize, obj);
	vector<SomeObject*> v9(vectorSize, obj); 
	vector<SomeObject*> v10(vectorSize, obj);

	printf("vector : 0x%08p\n", (void*) &v1);
	printf("vector : 0x%08p\n", (void*) &v2);
	printf("vector : 0x%08p\n", (void*) &v3);
	printf("vector : 0x%08p\n", (void*) &v4);
	printf("vector : 0x%08p\n", (void*) &v5);
	printf("vector : 0x%08p\n", (void*) &v6);
	printf("vector : 0x%08p\n", (void*) &v7);
	printf("vector : 0x%08p\n", (void*) &v8);
	printf("vector : 0x%08p\n", (void*) &v9);
	printf("vector : 0x%08p\n", (void*) &v10);

	memset(allocations[2], 'B', CHUNK_SIZE + 8 + 32);
	v1.at(0)->virtualFunction();
	system("PAUSE");

	return 0;
}