#include <iostream>
#include <string>
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace httplib;
using namespace std;

int main() {
    Server svr;

    svr.Post("/filter/tasks", [](const Request& req, Response& res) {
        try {
            json requestData = json::parse(req.body);

            string filterType = requestData["filterType"];
            string filterValue = requestData.value("filterValue", "");
            json tasks = requestData["tasks"];
            json filteredTasks = json::array();

            for (auto& task : tasks) {
                string taskName = task["name"];
                bool completed = task["completed"];

                // Return completed tasks
                if (filterType == "completed" && completed) {
                    filteredTasks.push_back(task);
                }
                // Return active tasks
                else if (filterType == "active" && !completed) {
                    filteredTasks.push_back(task);
                }
                // Return keyword matching tasks
                else if (filterType == "keyword") {
                    if (taskName.find(filterValue) != string::npos) {
                        filteredTasks.push_back(task);
                    }
                }
            }

            json responseData;
            responseData["filteredTasks"] = filteredTasks;

            res.set_content(responseData.dump(4), "application/json");
        }
        catch (const exception& e) {
            res.status = 400;
            res.set_content("{\"error\": \"Invalid JSON format\"}", "application/json");
        }
    });

    cout << "Filter Microservice running on http://127.0.0.1:8995" << endl;
    
    // Explicit loopback mapping on custom student port
    svr.listen("127.0.0.1", 9442);

    return 0;
}
