#include "paginator.h"
#include "read_input_functions.h"
#include "request_queue.h"
#include "search_server.h"

#include <iostream>

//тут виртуальные печеньки ревьюеру
//а тут просьба оставить побольше замечаний - я, похоже, учусь, только когда меня носом тычут в проблемы
using namespace std;
//отсюда тоже лучше убрать неймспейс?


int main() {
    SearchServer search_server;
    search_server.AddDocument(0, "белый кот и модный ошейник"s,        DocumentStatus::ACTUAL, {8, -3});
    search_server.AddDocument(1, "пушистый кот пушистый хвост"s,       DocumentStatus::ACTUAL, {7, 2, 7});
    search_server.AddDocument(2, "ухоженный пёс выразительные глаза"s, DocumentStatus::ACTUAL, {5, -12, 2, 1});
    search_server.AddDocument(3, "ухоженный скворец евгений"s,         DocumentStatus::BANNED, {9});
    cout << "ACTUAL by default:"s << endl;
    for (const Document& document : search_server.FindTopDocuments("пушистый ухоженный кот"s)) {
        cout << document<< endl;
    }
    cout << "BANNED:"s << endl;
    for (const Document& document : search_server.FindTopDocuments("пушистый ухоженный кот"s, DocumentStatus::BANNED)) {
        cout << document<< endl;
    }
    cout << "Even ids:"s << endl;
    for (const Document& document : search_server.FindTopDocuments("пушистый ухоженный кот"s, [](int document_id, DocumentStatus status, int rating) { return document_id % 2 == 0; })) {
        cout << document<< endl;
    }
    return 0;
} 
