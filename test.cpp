#include <iostream>
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace httplib;
using namespace std;

int main() {
    // Points directly to the server running on port 8995
    Client cli("127.0.0.1", 9442);

    json tasks = {
        {"tasks", {
            {{"name", "Fix login bug"}, {"completed", false}},
            {{"name", "Write tests"}, {"completed", true}},
            {{"name", "Deploy app"}, {"completed", false}}
        }}
    };

    // -----------------------------
    // TEST 1 - COMPLETED TASKS
    // -----------------------------
    json completedRequest;
    completedRequest["filterType"] = "completed";
    completedRequest["tasks"] = tasks["tasks"];

    auto res1 = cli.Post("/filter/tasks", completedRequest.dump(), "application/json");

    cout << "Completed Tasks:" << endl;
    if (res1) {
        cout << res1->body << endl;
    } else {
        cout << "Request failed. Is the app server running on port 8995?" << endl;
    }
    cout << endl;

    // -----------------------------
    // TEST 2 - ACTIVE TASKS
    // -----------------------------
    json activeRequest;
    activeRequest["filterType"] = "active";
    activeRequest["tasks"] = tasks["tasks"];

    auto res2 = cli.Post("/filter/tasks", activeRequest.dump(), "application/json");

    cout << "Active Tasks:" << endl;
    if (res2) {
        cout << res2->body << endl;
    } else {
        cout << "Request failed. Is the app server running on port 8995?" << endl;
    }
    cout << endl;

    // -----------------------------
    // TEST 3 - KEYWORD FILTER
    // -----------------------------
    json keywordRequest;
    keywordRequest["filterType"] = "keyword";
    keywordRequest["filterValue"] = "bug";
    keywordRequest["tasks"] = tasks["tasks"];

    auto res3 = cli.Post("/filter/tasks", keywordRequest.dump(), "application/json");

    cout << "Keyword Filter:" << endl;
    if (res3) {
        cout << res3->body << endl;
    } else {
        cout << "Request failed. Is the app server running on port 8995?" << endl;
    }

    return 0;
}
