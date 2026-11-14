# COP5611_Manufacturing_Software_Test_Suite
COP 5611 Semester Project inspired by real world development

## Overview

This repository contains the COP-5611 semester project, consisting of an ETS server application and an ATP testing application with a web-based interface.

The project includes:

- **ETS Software (`etssoftware`)** Server application that executes and manages the ETS server.
- **ATP Test Software (`atptest`)** Python-based testing application providing a web interface for executing ESS and ATP tests.
- **Utilities Library (`utilities`)** Shared library required by the ETS software.

## 1. Building the Project

To build all modules, navigate to the project's root directory and execute:

```bash
make clean
make
```

- `make clean` Removes previously generated build files.
- `make` Compiles all project modules.

Alternatively, you can navigate into individual subdirectories and build each module separately using `make`.

## 2. Configuring the Shared Library

The ETS software dynamically links against the utilities library. Therefore, the system must be able to locate this library at runtime.

Set the `LD_LIBRARY_PATH` environment variable:

```bash
export LD_LIBRARY_PATH=/home/<yourpath>/COP5611SemesterProject/utilities
```

Replace `<yourpath>` with the appropriate directory path on your system.

Alternatively, after building the project, you can install the utilities shared library into a system library directory, such as `/usr/lib`, provided that it is appropriate for your Linux distribution.

Using `LD_LIBRARY_PATH` is recommended for local development because it avoids modifying system library directories.

## 3. Running the ETS Server

Navigate to the `etssoftware` directory and execute:

```bash
./etssoftware
```

At the ETS command prompt, enter `help` to display the available commands:

```text
ETS->help

exit     - Exit program
runserv  - Run server
stopserv - Stop server

ETS->
```

To start the ETS server, execute:

```text
ETS->runserv
```

The ETS server is now ready to accept test requests from the ATP testing application.

## 4. Running the ATP Testing Application

Open a separate terminal and navigate to the `atptest` directory.

The ATP testing application requires Python 3 and Flask.

Install Flask using:

```bash
pip install flask
```

Start the application directly:

```bash
./atpsoftware.py
```

Alternatively, you can use a production WSGI server such as Gunicorn on Linux or Waitress on Windows.

### 4.1 Running with Gunicorn (Linux)

WSGI stands for **Web Server Gateway Interface**. It is a standard interface between Python web applications and web servers.

Install Gunicorn:

```bash
pip install gunicorn
```

Gunicorn can also be installed using your Linux distribution's package manager, if available.

Start the ATP application:

```bash
gunicorn -w 11 -b 0.0.0.0:8484 atpsoftware:app
```

Command-line options:

- `-w 11` Starts 11 worker processes.
- `-b 0.0.0.0:8484` Binds the server to port 8484 on all network interfaces.
- `atpsoftware:app` Specifies the Python module and Flask application object.

A commonly used starting guideline for Gunicorn worker processes is:

```text
workers = (2 × CPU cores) + 1
```

For example, using five CPU cores:

```text
workers = (2 × 5) + 1 = 11
```

The optimal worker count depends on the workload and available system resources.

### 4.2 Running with Waitress (Windows)

For Windows environments, Waitress provides an alternative WSGI server.

Install Waitress:

```bash
pip install waitress
```

Start the ATP application:

```bash
waitress-serve --port=8484 --threads=31 atpsoftware:app
```

Command-line options:

- `--port=8484` Listens on port 8484.
- `--threads=31` Configures 31 worker threads.
- `atpsoftware:app` Specifies the Python module and Flask application object.

For this project, the thread count was selected using:

```text
threads = (2 × CPU cores) + 1
```

For example, using 15 CPU cores:

```text
threads = (2 × 15) + 1 = 31
```

This is an example configuration rather than a universal recommendation. Waitress thread counts should be adjusted according to application requirements and performance testing.

## 5. Accessing the ATP Web Interface

Once the ATP application is running, open a web browser and navigate to:

```text
http://<your-ip-address>:8484
```

Replace `<your-ip-address>` with the IP address of the machine running the ATP application.

From the web interface, select either:

- **ESS Testing**
- **ATP Testing**

### Executing Tests

1. Select the desired testing interface.
2. Enter `7` in the test bitmask field to enable all three tests.
3. Enter the ETS server's IP address and port:

   ```text
   <your-ip-address>:8080
   ```

4. Start the test using the web interface.

The ATP application will communicate with the ETS server and execute the selected tests.

## 6. Software Requirements

The project requires the following components:

| Component | Purpose |
|---|---|
| Linux | Building and running the ETS software |
| Make | Compiling the project modules |
| Python 3 | Running the ATP testing application |
| Flask | Providing the ATP web application |
| Gunicorn | Optional WSGI server for Linux |
| Waitress | Optional WSGI server for Windows |
| Utilities shared library | Runtime dependency of the ETS software |

## 7. Network Configuration

The project uses the following default ports:

| Application | Port | Purpose |
|---|---|---|
| ETS Server | 8080 | Receives and processes test requests |
| ATP Web Application | 8484 | Provides the browser-based testing interface |

Ensure the required ports are accessible between the ATP testing application and the ETS server.

**Security note:** Binding a web server to `0.0.0.0` exposes it on all available network interfaces. Use this configuration only on trusted networks or with appropriate firewall restrictions.

## 8. Application Architecture

The project uses a client-server architecture:

```text
       Web Browser
            |
            | HTTP (Port 8484)
            v
    ATP Testing Application
       (Python / Flask)
            |
            | Test Requests
            v
        ETS Server
        (Port 8080)
            |
            v
      Utilities Library
```

The browser provides the user interface, the ATP application coordinates testing, and the ETS server processes the requests using its linked utilities library.
