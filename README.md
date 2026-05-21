## Microservice API Documentation: Task Filter

### 1. How to Request Data
To filter tasks, send an HTTP POST request to the endpoint `/filter/tasks` with a JSON payload specifying the `filterType` ("completed", "active", or "keyword").

#### Example Request Call:
```json
{
    "filterType": "keyword",
    "filterValue": "bug",
    "tasks": [
        {"name": "Fix login bug", "completed": false},
        {"name": "Write tests", "completed": true}
    ]
}
