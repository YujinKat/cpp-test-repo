#include "request_queue.h"

    RequestQueue::RequestQueue(const SearchServer& search_server) : search_server_(search_server) {}

    std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
        return AddFindRequest(raw_query, [status](int, DocumentStatus doc_status, int) {
            return doc_status == status;
        });
    }

    std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
        return AddFindRequest(raw_query, DocumentStatus::ACTUAL);
    }
    
    int RequestQueue::GetNoResultRequests() const {
        int emptyresults = 0;
        for (auto qr : requests_) {
            if (qr.isempty == true) {
               ++emptyresults;
            }
        }
        return emptyresults;
    };


   
