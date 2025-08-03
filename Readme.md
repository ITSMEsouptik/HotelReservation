# Hotel Reservation System Approaches

This project implements and benchmarks three approaches for the dynamic hotel room booking problem:

## 1. Book (Brute-force)

- Uses a 2D vector<bool> to track occupancy for each room and day.
- For each booking, checks every room and every day in the requested range.
- Counts utilization by scanning all days for each free room.
- **Time Complexity:** O(rooms × days) per booking.

## 2. Book_V2 (Heap-based)

- Also uses a 2D vector<bool> for occupancy.
- Uses a max-heap to efficiently select the most utilized free room.
- Still scans all days for availability and utilization.
- **Time Complexity:** O(rooms × days) per booking (slightly better in practice, but not asymptotically).

## 3. Book_V3 (Bitset + Utilization Array)

- Uses a std::bitset for each room to track occupancy, allowing O(1) checks for any day.
- Maintains a utilization array for each room, updated only when a booking is made.
- For each booking:
  - Checks each room for availability in the requested range using bitset.
  - Selects the most utilized free room using the utilization array (O(1) lookup).
  - Updates occupancy and utilization in O(daysInBooking) time.
- **Time Complexity:**
  - O(rooms) for free room search (since bitset check is O(1) per day).
  - O(1) for utilization lookup.
  - O(daysInBooking) for update.
- **True asymptotic improvement** over Book and Book_V2.

---

### Summary Table

| Approach | Data Structure       | Free Room Search | Utilization Lookup | Update Booking   | Overall Complexity       |
| -------- | -------------------- | ---------------- | ------------------ | ---------------- | ------------------------ |
| Book     | vector<vector<bool>> | O(rooms × days)  | O(days)            | O(days)          | O(rooms × days)          |
| Book_V2  | vector<vector<bool>> | O(rooms × days)  | O(days)            | O(days)          | O(rooms × days)          |
| Book_V3  | bitset + array       | O(rooms)         | O(1)               | O(daysInBooking) | O(rooms + daysInBooking) |

---

**Book_V3 is recommended for large-scale or performance-critical scenarios.**
This project implements a hotel reservation system in C++ as per the specifications provided in the "Hotel Reservations" problem.

## How to Build and Run the Executable in VS Code (Windows)

1. **Open the Project in VS Code**

   - Open the folder containing `HotelReservations.cpp` in Visual Studio Code.

2. **Build the Executable**

   - Press `Ctrl+Shift+B` to run the default build task.
   - This will compile `HotelReservations.cpp` and create `HotelReservations.exe` in the same folder.
   - The build uses static linking (see `.vscode/tasks.json`), so the `.exe` should not require external DLLs for standard C++ runtime.

3. **Run the Executable**
   - Open the integrated terminal in VS Code (`Ctrl+`` or from the menu: View > Terminal).
   - Make sure you are in the project directory (where `HotelReservations.exe` is located).
   - Run the program by typing:
     ```
     .\HotelReservations.exe
     ```
   - The output will be displayed in the terminal and will not disappear after the program finishes.

**Note:**

- If you double-click the `.exe` in Windows Explorer, the console window will open and close immediately. Always run from a terminal to see the output.

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
