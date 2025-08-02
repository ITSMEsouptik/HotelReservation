 This project implements a hotel reservation system in C++ as per the specifications provided in the "Hotel Reservations" problem.

 ## Compilation Instructions

 The project consists of a single source file: `HotelReservations.cpp`.

 To compile the program, use a C++ compiler that supports C++11 or later. For example, using `g++`:

 ```bash
 g++ -std=c++11 HotelReservations.cpp -o HotelReservations
 ```

 ## Running the Program

 After compilation, run the executable:

 ```bash
 ./HotelReservations
 ```

 On Windows, if using MinGW or another compiler, run:

 ```bash
 HotelReservations.exe
 ```

 The program executes a series of test cases (1a, 1b, 2, 3, 4, and 5) as specified, printing the results for each booking and indicating whether each test case passes or fails.

 ## Dependencies

 - Standard C++ library (no external dependencies required).
 - C++11 or later for `std::tuple` and other features.

 ## Assumptions

 - When multiple rooms are available for a booking, the program assigns the booking to the room with the most days already booked (most utilized). This heuristic aims to leave less utilized rooms available for potentially longer future stays, though the problem specifies not to optimize for future requests. In case of ties, the lowest room number is chosen.
 - The maximum planning period is set to 366 days (accounting for a leap year) to handle test cases within a reasonable range.
 - Invalid bookings (e.g., start > end, or dates outside the planning period [0, 365]) are declined.

 ## Test Cases

 The program includes all test cases specified in the problem:
 - Test 1a: Single room, booking outside planning period (4-2).
 - Test 1b: Single room, booking far outside planning period (200-400).
 - Test 2: Three rooms, multiple bookings all accepted.
 - Test 3: Three rooms, bookings with one declined due to no available rooms.
 - Test 4: Three rooms, bookings with one declined followed by an accepted booking.
 - Test 5: Two rooms, complex sequence of bookings with multiple accepts and declines.

 ## Git Repository

 This project is version-controlled using Git. To clone or work with the repository:

 ```bash
 git clone <repository-url>
 ```

 The repository contains:
 - `HotelReservations.cpp`: The main source code.
 - `README.md`: This documentation file.