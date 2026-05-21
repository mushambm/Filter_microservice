#include <iostream>
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace httplib;
using namespace std;

int main() {

    Client cli("localhost", 8080);

    json tasks = {
        {"tasks", {
            {
                {"name", "Fix login bug"},
                {"completed", false}
            },
            {
                {"name", "Write tests"},
                {"completed", true}
            },
            {
                {"name", "Deploy app"},
                {"completed", false}
            }
        }}
    };

    // Test 1 - Completed Tasks
    json completedRequest;
    completedRequest["filterType"] = "completed";
    completedRequest["tasks"] = tasks["tasks"];

    auto res1 = cli.Post("/filter/tasks",
                         completedRequest.dump(),
                         "application/json");

    cout << "Completed Tasks:" << endl;
    cout << res1->body << endl << endl;

    // Test 2 - Active Tasks
    json activeRequest;
    activeRequest["filterType"] = "active";
    activeRequest["tasks"] = tasks["tasks"];

    auto res2 = cli.Post("/filter/tasks",
                         activeRequest.dump(),
                         "application/json");

    cout << "Active Tasks:" << endl;
    cout << res2->body << endl << endl;

    // Test 3 - Keyword Filter
    json keywordRequest;
    keywordRequest["filterType"] = "keyword";
    keywordRequest["filterValue"] = "bug";
    keywordRequest["tasks"] = tasks["tasks"];

    auto res3 = cli.Post("/filter/tasks",
                         keywordRequest.dump(),
                         "application/json");

    cout << "Keyword Filter:" << endl;
    cout << res3->body << endl;

    return 0;
}
