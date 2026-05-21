#include <iostream>
#include <vector>
#include <string>
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace httplib;
using namespace std;

int main() {
    Server svr;

    svr.Post("/filter/tasks", [](const Request& req, Response& res) {

        json requestData = json::parse(req.body);

        string filterType = requestData["filterType"];
        string filterValue = requestData.value("filterValue", "");

        json tasks = requestData["tasks"];
        json filteredTasks = json::array();

        for (auto& task : tasks) {

            string taskName = task["name"];
            bool completed = task["completed"];

            if (filterType == "completed" && completed) {
                filteredTasks.push_back(task);
            }

            else if (filterType == "active" && !completed) {
                filteredTasks.push_back(task);
            }

            else if (filterType == "keyword") {

                if (taskName.find(filterValue) != string::npos) {
                    filteredTasks.push_back(task);
                }
            }
        }

        json responseData;
        responseData["filteredTasks"] = filteredTasks;

        res.set_content(responseData.dump(4), "application/json");
    });

    cout << "Filter Microservice running on port 8080..." << endl;

    svr.listen("localhost", 8080);

    return 0;
}
