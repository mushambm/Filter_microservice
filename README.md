# Filter Microservice

## Overview

The Filter Microservice filters a list of tasks based on a requested filter type. It receives task data, processes the request, and returns only the tasks that match the filter.

This microservice supports three filter types:

* `completed` – returns only completed tasks
* `active` – returns only incomplete tasks
* `keyword` – returns tasks whose name contains a specific keyword

## Request Data

The microservice expects task data in JSON format.

Example request:

```json
{
  "filterType": "keyword",
  "filterValue": "bug",
  "tasks": [
    {
      "name": "Fix login bug",
      "completed": false
    },
    {
      "name": "Write tests",
      "completed": true
    },
    {
      "name": "Deploy app",
      "completed": false
    }
  ]
}
```

## Request Fields

* `filterType`: The type of filter being requested.
* `filterValue`: The keyword used when `filterType` is set to `keyword`.
* `tasks`: A list of task objects.
* `name`: The name of each task.
* `completed`: A Boolean value showing whether the task is completed.

## Response Data

The microservice returns JSON data containing the filtered list of tasks.

Example response:

```json
{
  "filteredTasks": [
    {
      "name": "Fix login bug",
      "completed": false
    }
  ]
}
```

## How to Run the Microservice

Compile the microservice:

```bash
g++ app.cpp -o app
```

Run the microservice:

```bash
./app
```

The microservice runs on:

```text
http://localhost:8080/filter/tasks
```

## How to Run the Test Program

Open a second terminal window and compile the test program:

```bash
g++ test.cpp -o test
```

Run the test program:

```bash
./test
```

The test program sends three requests:

1. A request for completed tasks
2. A request for active tasks
3. A request for keyword-matching tasks

## Example Test Output

```text
Completed Tasks:
{
  "filteredTasks": [
    {
      "name": "Write tests",
      "completed": true
    }
  ]
}

Active Tasks:
{
  "filteredTasks": [
    {
      "name": "Fix login bug",
      "completed": false
    },
    {
      "name": "Deploy app",
      "completed": false
    }
  ]
}

Keyword Filter:
{
  "filteredTasks": [
    {
      "name": "Fix login bug",
      "completed": false
    }
  ]
}
```

## Notes

This microservice uses a REST API style request and response format. JSON is used so that the main program and microservice can exchange data in a clear, structured format.
