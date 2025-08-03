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


## Room Assignment Approach


Brute Force Approach (Book)

When multiple rooms are available for a booking, the program assigns the booking to the room that is already booked for the most days (the most utilized room). This is done by counting the number of days each available room is already occupied and selecting the one with the highest count. If there is a tie, the room with the lowest room number is chosen.

**Time Complexity**
- For each booking, the algorithm checks every room and every day in the booking range to find available rooms, resulting in O(rooms × days) per booking.
- For each available room, it counts the total number of occupied days (O(days)), to select the most utilized room.
- Overall, for N bookings, the worst-case time complexity is O(N × rooms × days).

Optimized Heap-Based Approach (Book_V2)

The optimized approach uses a max-heap (priority queue) to efficiently select the most utilized available room. For each booking:

- All available rooms are pushed into a max-heap as pairs (utilization, -room number), so the room with the highest utilization (and lowest room number in case of ties) is chosen efficiently.
- This reduces the time to select the room among free rooms to O(freeRooms × log(freeRooms)) per booking.

**Time Complexity**
- For each booking, finding free rooms is O(rooms × daysInBooking).
- Selecting the most utilized room among free rooms is O(freeRooms × log(freeRooms)).
- Overall, for N bookings, the worst-case time complexity is O(N × rooms × daysInBooking + N × freeRooms × log(freeRooms)).

**Rationale:**
- This heuristic helps to leave less utilized rooms as open as possible for future bookings, especially for longer stays, by concentrating bookings in already-busy rooms. This reduces fragmentation of availability across rooms and maximizes flexibility for future reservations.
- The approach is simple and efficient for the problem size, but more advanced data structures (like interval trees or bitsets) could be used for larger datasets.

The maximum planning period is set to 366 days (accounting for a leap year) to handle test cases within a reasonable range. Invalid bookings (e.g., start > end, or dates outside the planning period [0, 365]) are declined.

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