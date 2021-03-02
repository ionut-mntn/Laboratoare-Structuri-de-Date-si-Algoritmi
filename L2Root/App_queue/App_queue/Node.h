#pragma once
typedef int TElem;
struct Node			// nu stiu de ce, dar daca declar struct ul aici, nu e vizibil in .cpp
{
	TElem data;
	Node* next;
};
