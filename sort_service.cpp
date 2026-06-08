#include <iostream>
#include <algorithm>
#include <string>
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace httplib;
using namespace std;

int main() {
    Server svr;

    svr.Post("/sort/tasks", [](const Request& req, Response& res) {
        try {
            json requestData = json::parse(req.body);

            string sortType = requestData.value("sortType", "priority");
            json tasks = requestData["tasks"];

            if (sortType == "priority") {
                sort(tasks.begin(), tasks.end(), [](const json& a, const json& b) {
                    int priorityA = a.value("priority", 0);
                    int priorityB = b.value("priority", 0);
                    return priorityA > priorityB;
                });
            }

            else if (sortType == "dueDate") {
                sort(tasks.begin(), tasks.end(), [](const json& a, const json& b) {
                    string dueA = a.value("dueDate", "");
                    string dueB = b.value("dueDate", "");
                    return dueA < dueB;
                });
            }

            json responseData;
            responseData["sortedTasks"] = tasks;

            res.set_content(responseData.dump(4), "application/json");
        }

        catch (const exception& e) {
            json errorResponse;
            errorResponse["error"] = "Invalid request";
            errorResponse["details"] = e.what();

            res.status = 400;
            res.set_content(errorResponse.dump(4), "application/json");
        }
    });

    cout << "Task Sorting Microservice running on port 8081..." << endl;
    cout << "Endpoint: POST /sort/tasks" << endl;

    svr.listen("localhost", 8081);

    return 0;
}
