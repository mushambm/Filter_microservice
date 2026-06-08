#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdio>

#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace httplib;
using namespace std;

json getSampleTasks() {
    return json::array({
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
        },
        {
            {"name", "Resolve web-app crash"},
            {"completed", false}
        },
        {
            {"name", "Update README.md"},
            {"completed", true}
        }
    });
}

// ----------------------------------------------------
// Microservice 1: Lucky's Filter Microservice
// C++ HTTP server running on localhost:8080
// Endpoint: POST /filter/tasks
// ----------------------------------------------------
void callFilterMicroservice() {
    cout << "\n========================================\n";
    cout << "MICROSERVICE 1: Filter Microservice\n";
    cout << "========================================\n";

    Client cli("localhost", 8080);

    json requestData;
    requestData["filterType"] = "active";
    requestData["tasks"] = getSampleTasks();

    cout << "\nRequest sent to Filter Microservice:\n";
    cout << requestData.dump(4) << endl;

    auto res = cli.Post("/filter/tasks", requestData.dump(), "application/json");

    cout << "\nResponse from Filter Microservice:\n";

    if (res) {
        cout << res->body << endl;
    } else {
        cout << "ERROR: No response from Filter Microservice.\n";
        cout << "Make sure app.cpp is running on port 8080.\n";
    }
}

// ----------------------------------------------------
// Microservice 2: Mehul's Removal Microservice
// Python file-based service using request.txt/response.txt
// ----------------------------------------------------
void callRemovalMicroservice() {
    cout << "\n========================================\n";
    cout << "MICROSERVICE 2: Removal Microservice\n";
    cout << "========================================\n";

    const string requestFile = "request.txt";
    const string responseFile = "response.txt";

    // Delete old response file if it exists
    remove(responseFile.c_str());

    string requestData =
        "1\n"
        "Socks,5.99\n"
        "Jacket,45.00\n"
        "Hat,15.50\n";

    cout << "\nRequest written to request.txt:\n";
    cout << requestData << endl;

    ofstream requestOut(requestFile);
    if (!requestOut) {
        cout << "ERROR: Could not create request.txt\n";
        return;
    }

    requestOut << requestData;
    requestOut.close();

    cout << "Waiting for response.txt from Removal Microservice...\n";

    int secondsWaited = 0;

    while (true) {
        ifstream responseCheck(responseFile);

        if (responseCheck.good()) {
            responseCheck.close();
            break;
        }

        this_thread::sleep_for(chrono::seconds(1));
        secondsWaited++;

        if (secondsWaited > 15) {
            cout << "ERROR: Timed out waiting for response.txt\n";
            cout << "Make sure Mehul's removal_service.py is running.\n";
            return;
        }
    }

    ifstream responseIn(responseFile);
    string line;

    cout << "\nResponse from Removal Microservice:\n";

    while (getline(responseIn, line)) {
        cout << line << endl;
    }

    responseIn.close();

    // Clean up response file after reading
    remove(responseFile.c_str());
}

// ----------------------------------------------------
// Microservice 3: James's Data Processing Microservice
// Python Flask HTTP server running on localhost:5000
// Endpoint: POST /process/stats
// ----------------------------------------------------
void callDataProcessingStats() {
    cout << "\n========================================\n";
    cout << "MICROSERVICE 3: Data Processing - Stats\n";
    cout << "========================================\n";

    Client cli("localhost", 5000);

    json requestData;
    requestData["tasks"] = getSampleTasks();

    cout << "\nRequest sent to Data Processing /process/stats:\n";
    cout << requestData.dump(4) << endl;

    auto res = cli.Post("/process/stats", requestData.dump(), "application/json");

    cout << "\nResponse from Data Processing Stats:\n";

    if (res) {
        cout << res->body << endl;
    } else {
        cout << "ERROR: No response from Data Processing Microservice.\n";
        cout << "Make sure James's app.py is running on port 5000.\n";
    }
}

// ----------------------------------------------------
// Data Processing Feature: Automated Tags
// Same James microservice, different endpoint
// Endpoint: POST /process/tags
// ----------------------------------------------------
void callDataProcessingTags() {
    cout << "\n========================================\n";
    cout << "DATA PROCESSING FEATURE: Automated Tags\n";
    cout << "========================================\n";

    Client cli("localhost", 5000);

    json requestData;
    requestData["tasks"] = getSampleTasks();

    cout << "\nRequest sent to Data Processing /process/tags:\n";
    cout << requestData.dump(4) << endl;

    auto res = cli.Post("/process/tags", requestData.dump(), "application/json");

    cout << "\nResponse from Data Processing Tags:\n";

    if (res) {
        cout << res->body << endl;
    } else {
        cout << "ERROR: No response from /process/tags.\n";
    }
}

// ----------------------------------------------------
// Dlata Processing Feature: Priority Scoring
// Same James microservice, different endpoint
// Endpoint: POST /process/priority
// ----------------------------------------------------
void callDataProcessingPriority() {
    cout << "\n========================================\n";
    cout << "DATA PROCESSING FEATURE: Priority Scoring\n";
    cout << "========================================\n";

    Client cli("localhost", 5000);

    json requestData;
    requestData["tasks"] = getSampleTasks();

    cout << "\nRequest sent to Data Processing /process/priority:\n";
    cout << requestData.dump(4) << endl;

    auto res = cli.Post("/process/priority", requestData.dump(), "application/json");

    cout << "\nResponse from Data Processing Priority:\n";

    if (res) {
        cout << res->body << endl;
    } else {
        cout << "ERROR: No response from /process/priority.\n";
    }
}

int main() {
    cout << "========================================\n";
    cout << "C++ MAIN PROGRAM RUNNING\n";
    cout << "========================================\n";
    cout << "This Main Program communicates with microservices using requests and responses.\n";
    cout << "It does not directly call functions from the microservice code.\n";
    cout << "Each microservice runs separately in its own process.\n";

    callFilterMicroservice();
    callRemovalMicroservice();
    callDataProcessingStats();
    callDataProcessingTags();
    callDataProcessingPriority();

    cout << "\n========================================\n";
    cout << "MAIN PROGRAM FINISHED\n";
    cout << "========================================\n";

    return 0;
}
