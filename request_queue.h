#pragma once

#include "search_server.h"

#include <deque>

class RequestQueue {
public:
   explicit RequestQueue(const SearchServer& search_server);
    
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
        std::vector<Document> documents = search_server_.FindTopDocuments(raw_query, document_predicate);
        QueryResult q;
        if (documents.empty()) {
            q.isempty = true;
            q.result=documents;
        } else {
            q.isempty = false;
            q.result = documents;
        }
        requests_.push_back(q);
        if (requests_.size()>min_in_day_) {requests_.pop_front();}
        return documents;
    }

    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
    
    std::vector<Document> AddFindRequest(const std::string& raw_query);


    int GetNoResultRequests() const;

private:
    struct QueryResult {
        bool isempty = false;
        std::vector<Document> result;
    };
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    const SearchServer& search_server_;
}; 
