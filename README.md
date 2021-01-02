# qt_asio_sample
Sample application that integrates Qt and Boost ASIO. This application uses seperate threads for Qt and Boost ASIO and communicates between threads.



Dependencies
---

- Qt 5.15.1 or higher
- Boost 1.57 or higher

Development Dependencies
---

- cmake 3.19.2 or higher


Supported OS
---

- Mac BigSur
(Might work on windows and linux)

Installing Dependencies
---

- Download and install [Qt Community addition](https://www.qt.io/download-open-source)
- `brew install boost`

Building
---

- `mkdir build && cd build`
- `cmake ..`
- `make`

Running
---

- `./qt_asio_sample`

