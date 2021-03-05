#define _CRT_SECURE_NO_WARNINGS
#include "iostream"
#include "conio.h"

using namespace std;

struct Node {
	int Value;
	Node * Parent;
	Node * Left;
	Node * Right;
};

string * WidthArray;
int Levels = 0;
typedef Node * PNode;
PNode Head = NULL;

string int_to_string(int x) {
	char buffer[99];
	sprintf(buffer, "%d", x);
	return buffer;
}

PNode CreateNode(int Data, PNode Parent) {
	PNode LADR = new Node();
	LADR->Left = NULL; LADR->Right = NULL;
	LADR->Value = Data; LADR->Parent = Parent;
	return LADR;
}

PNode Search(int Data) {
	PNode LADR = Head;
	while (LADR) {
		if (Data == LADR->Value) { return LADR; }
		if (Data > LADR->Value) {
			if (LADR->Right) {
				LADR = LADR->Right; continue;
			}
		}
		if (Data < LADR->Value) {
			if (LADR->Left) {
				LADR = LADR->Left; continue;
			}
		}
	}
	return NULL;
}

PNode ClampNode(bool Max, PNode LADR) {
	if (Max) {
		while (LADR->Right) {
			LADR = LADR->Right;
		}
	} else {
		while (LADR->Left) {
			LADR = LADR->Left;
		}
	}
	return LADR;
}

void AddNewNode(int Data) {
	PNode LADR = NULL;
	if (!Head) {
		Head = CreateNode(Data, NULL); return;
	} else {
		LADR = Head;
	} while (LADR) {
		if (Data > LADR->Value) {
			if (LADR->Right) {
				LADR = LADR->Right; continue;
			} else {
				LADR->Right = CreateNode(Data, LADR); break;
			}
		}
		if (Data < LADR->Value) {
			if (LADR->Left) {
				LADR = LADR->Left; continue;
			} else {
				LADR->Left = CreateNode(Data, LADR); break;
			}
		}
	}
}

void DeleteNode(PNode ToDelete) {
	if (ToDelete->Left && ToDelete->Right) {
		PNode lMax = ClampNode(true, ToDelete->Left);
		ToDelete->Value = lMax->Value;
		DeleteNode(lMax);
		return;
	}
	else if (ToDelete->Left) {
		if (ToDelete == ToDelete->Parent->Left) {
			ToDelete->Parent->Left = ToDelete->Left;
		} else {
			ToDelete->Parent->Right = ToDelete->Left;
		}
	} else if (ToDelete->Right) {
		if (ToDelete == ToDelete->Parent->Right) {
			ToDelete->Parent->Right = ToDelete->Right;
		} else {
			ToDelete->Parent->Left = ToDelete->Right;
		}
	} else {
		if (ToDelete == ToDelete->Parent->Left) {
			ToDelete->Parent->Left = NULL;
		} else {
			ToDelete->Parent->Right = NULL;
		}
	}
	delete ToDelete;
}


void FindReport(int Data) {
	if (!Search(Data)) {
		cout << "Не найдено!\n"; return;
	} else {
		cout << "Найден узел! Адрес: " << Search(Data) << '\n';
		cout << "Родитель: "; if (Search(Data)->Parent) { cout << Search(Data)->Parent->Value << '\n'; } else { cout << "Отсутствует (корень)\n"; }
		cout << "Дети:\n"; 
		cout << "Левый узел: "; if (Search(Data)->Left) { cout << Search(Data)->Left->Value << '\n'; } else { cout << "Отсутствует!\n"; }
		cout << "Правый узел: "; if (Search(Data)->Right) { cout << Search(Data)->Right->Value << '\n'; } else { cout << "Отсутствует!\n"; }
	}
	
}

void Count(PNode LADR, int u) {
	if (!LADR) { return; } else {
		Count(LADR->Left, ++u);
		Levels < u ? Levels = u : NULL; u--;
	}
	Count(LADR->Right, ++u);
}

void TraverseWidth(PNode LADR, int u) {
	if (!LADR) { return; } else {
		TraverseWidth(LADR->Left, ++u);
		WidthArray[u - 1] += int_to_string(LADR->Value) + ' '; u--;
	}
	TraverseWidth(LADR->Right, ++u);
}

void TraversePreorder(PNode LADR) {
	if (LADR) {
		cout << LADR->Value << ' ';
		TraversePreorder(LADR->Left);
		TraversePreorder(LADR->Right);
	}
}

void TraverseInorder(PNode LADR) {
	if (LADR) {
		TraverseInorder(LADR->Left);
		cout << LADR->Value << ' ';
		TraverseInorder(LADR->Right);
	}
}

void TraversePostorder(PNode LADR) {
	if (LADR) {
		TraversePostorder(LADR->Left);
		TraversePostorder(LADR->Right);
		cout << LADR->Value << ' ';
	}
}

int main() {
	setlocale(0,"");
	int Data;
	while (1) {
		cout << "\n1 - Вставить узел\n2 - Поиск\n3 - Удаление\n4 - Обход в глубину\n5 - Обход в ширину\n8 - Удалить дерево\n";
		switch (_getch()) {
		case 49: cout << "Введите данные: "; cin >> Data; AddNewNode(Data); break;
		case 50: cout << "Введите данные для поиска: "; cin >> Data; FindReport(Data); break;
		case 51: cout << "Номер узла для удаления: "; cin >> Data; DeleteNode(Search(Data)); cout << "Узел удален!\n"; break;
		case 52:switch(_getch()){
			TraversePreorder(Head); break;
					 TraverseInorder(Head); break;
		 TraversePostorder(Head); break;
		}
		 
			Levels = 0; Count(Head, 0);
			WidthArray = new string[Levels];
			TraverseWidth(Head, 0);
			for (int i = 0; i < Levels; i++) {
				cout << WidthArray[i];
			}
			break;
		case 53: delete Head; cout << "Дерево удалено!\n"; break;
		}
	}
	return 0;
}

