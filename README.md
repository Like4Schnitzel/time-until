# time-until
Simple C++ REST API server that returns the time between now and a given date.

## Usage
Sending a GET request to localhost:8080/`YYYY-MM-DDTHH:MM:SS` will respond with the amount of days remaining as an int.

## Building
[Install the C++ REST SDK](https://github.com/microsoft/cpprestsdk#getting-started).

```
cmake -B build
cmake --build build
```
