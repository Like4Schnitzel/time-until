# time-until
Simple C++ REST API server that returns the time between now and a given date.

## Usage
Sending a GET request to localhost:8080/`YYYY-MM-DD[THH:MM:SS]` will respond with the amount of days remaining as an int.

The port can be changed by specifying it in the first CLI arg, i.e. `time-until 8081`.

You can specify any of the following units in the query like so: localhost:8080/`YYYY-MM-DD[THH:MM:SS]`?`UNIT`:
- `y`, `year`, `years`
- `M`, `month`, `months`
- `d`, `day`, `days`
- `h`, `hour`, `hours`
- `m`, `minute`, `minutes`
- `s`, `second`, `seconds`
besides `M` and `m`, none of the units are case sensitive.

### Examples:
`curl localhost:8080/2022-12-24`
`curl localhost:8080/2022-12-24T05:00:00`
`curl localhost:8080/2025-07-28T7:15:00?MINUTES`
`curl localhost:8080/2006-11-19?y`

## Building
[Install the C++ REST SDK](https://github.com/microsoft/cpprestsdk#getting-started).

```
cmake -B build
cmake --build build
```
