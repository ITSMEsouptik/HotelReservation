
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <queue>
#include <bitset>

/**
 * @class Hotel
 * @brief Manages hotel room bookings using multiple algorithms for comparison.
 *
 * Supports three booking strategies:
 *   - Book: Brute-force approach using a 2D vector.
 *   - Book_V2: Heap-based approach using a 2D vector.
 *   - Book_V3: Bitset + utilization array + heap for optimal performance.
 */
class Hotel
{
private:
    int size; ///< Number of rooms in the hotel
    static const int MaxDays = 366; ///< Maximum number of days (0-based, e.g., 0-365)
    /**
     * @brief Occupancy tracking for Book and Book_V2 (brute-force/heap-based)
     * occupied_bf[room][day] == true if room is booked on that day
     */
    std::vector<std::vector<bool>> occupied_bf;
    using Bitset = std::bitset<MaxDays>;
    /**
     * @brief Occupancy tracking for Book_V3 (bitset-based)
     * occupied_bs[room].test(day) == true if room is booked on that day
     */
    std::vector<Bitset> occupied_bs;
    /**
     * @brief Utilization array for Book_V3 (number of booked days per room)
     */
    std::vector<int> utilization;

    /**
     * @brief Counts the number of booked days for a room (brute-force/heap-based)
     * @param room Room index
     * @return Number of days the room is booked
     */
    int countUtilization_bf(int room) const
    {
        int count = 0;
        for (int d = 0; d < MaxDays; ++d)
        {
            if (occupied_bf[room][d])
                ++count;
        }
        return count;
    }
    /**
     * @brief Returns the number of booked days for a room (bitset-based)
     * @param room Room index
     * @return Number of days the room is booked
     */
    int countUtilization_bs(int room) const
    {
        return utilization[room];
    }

public:
    /**
     * @brief Constructs a Hotel with the given number of rooms.
     * @param s Number of rooms
     */
    Hotel(int s)
        : size(s),
          occupied_bf(s, std::vector<bool>(MaxDays, false)),
          occupied_bs(s, Bitset()),
          utilization(s, 0) {}

    /**
     * @brief Brute-force booking: finds the most utilized available room for the requested period.
     *
     * @param start Start day (inclusive)
     * @param end End day (inclusive)
     * @return "Accept" if booking is successful, "Decline" otherwise
     */

    std::string Book(int start, int end)
    {
        if (start < 0 || end >= MaxDays || start > end)
        {
            return "Decline";
        }

        // Find all free rooms for the period
        std::vector<int> freeRooms;
        for (int r = 0; r < size; ++r)
        {
            bool isFree = true;
            for (int d = start; d <= end; ++d)
            {
                if (occupied_bf[r][d])
                {
                    isFree = false;
                    break;
                }
            }
            if (isFree)
            {
                freeRooms.push_back(r);
            }
        }

        if (freeRooms.empty())
        {
            return "Decline";
        }

        // Assign to the most utilized room (leave less utilized rooms for future stays)
        // In case of ties, choose the lowest room number
        int maxOccupiedCount = -1;
        int chosenRoom = -1;
        for (int r : freeRooms)
        {
            int count = countUtilization_bf(r);
            if (count > maxOccupiedCount || (count == maxOccupiedCount && (chosenRoom == -1 || r < chosenRoom)))
            {
                maxOccupiedCount = count;
                chosenRoom = r;
            }
        }

        // Assign the booking to the chosen room
        for (int d = start; d <= end; ++d)
        {
            occupied_bf[chosenRoom][d] = true;
        }

        return "Accept";
    }

    /**
     * @brief Heap-based booking: selects the most utilized available room using a max-heap.
     *
     * @param start Start day (inclusive)
     * @param end End day (inclusive)
     * @return "Accept" if booking is successful, "Decline" otherwise
     */
    std::string Book_V2(int start, int end)
    {
        if (start < 0 || end >= MaxDays || start > end)
        {
            return "Decline";
        }

        // Find all free rooms for the period
        std::vector<int> freeRooms;
        for (int r = 0; r < size; ++r)
        {
            bool isFree = true;
            for (int d = start; d <= end; ++d)
            {
                if (occupied_bf[r][d])
                {
                    isFree = false;
                    break;
                }
            }
            if (isFree)
            {
                freeRooms.push_back(r);
            }
        }

        if (freeRooms.empty())
        {
            return "Decline";
        }

        // Use a max-heap to select the most utilized room (lowest room number in case of tie)
        using RoomInfo = std::pair<int, int>; // (utilization, -room number)
        std::priority_queue<RoomInfo> pq;
        for (int r : freeRooms)
        {
            pq.push({countUtilization_bf(r), -r});
        }
        int chosenRoom = -pq.top().second;

        // Assign the booking to the chosen room
        for (int d = start; d <= end; ++d)
        {
            occupied_bf[chosenRoom][d] = true;
        }
        return "Accept";
    }
    /**
     * @brief Bitset + heap + utilization array: most optimal booking approach.
     *
     * Uses bitsets for fast occupancy checks, a utilization array for O(1) lookup, and a heap for efficient selection.
     *
     * @param start Start day (inclusive)
     * @param end End day (inclusive)
     * @return "Accept" if booking is successful, "Decline" otherwise
     */
    std::string Book_V3(int start, int end)
    {
        if (start < 0 || end >= MaxDays || start > end)
            return "Decline";

        std::vector<int> freeRooms;
        for (int r = 0; r < size; ++r)
        {
            bool isFree = true;
            for (int d = start; d <= end; ++d)
            {
                if (occupied_bs[r].test(d))
                {
                    isFree = false;
                    break;
                }
            }
            if (isFree)
                freeRooms.push_back(r);
        }
        if (freeRooms.empty())
            return "Decline";

        // Use a max-heap to select the most utilized room (lowest room number in case of tie)
        using RoomInfo = std::pair<int, int>; // (utilization, -room number)
        std::priority_queue<RoomInfo> pq;
        for (int r : freeRooms)
        {
            pq.push({utilization[r], -r});
        }
        int chosenRoom = -pq.top().second;

        // Assign the booking
        for (int d = start; d <= end; ++d)
        {
            occupied_bs[chosenRoom].set(d);
        }
        utilization[chosenRoom] += (end - start + 1);
        return "Accept";
    }
};

void RunTest(const std::string &testName, int size, const std::vector<std::tuple<int, int, std::string>> &bookings)
{
    std::cout << "Running " << testName << " (Size=" << size << ")" << std::endl;
    Hotel hotel(size);
    int bookingNum = 1;
    bool passed = true;
    for (const auto &booking : bookings)
    {
        int start = std::get<0>(booking);
        int end = std::get<1>(booking);
        std::string expected = std::get<2>(booking);
        std::string result = hotel.Book_V3(start, end);
        std::cout << "Booking " << bookingNum << ": " << start << "-" << end << " " << result << " (expected: " << expected << ")" << std::endl;
        if (result != expected)
        {
            std::cout << "FAIL: Expected " << expected << " but got " << result << std::endl;
            passed = false;
        }
        ++bookingNum;
    }
    if (passed)
    {
        std::cout << "PASS" << std::endl;
    }
    std::cout << std::endl;
}

int main()
{

    RunTest("Test 1a", 1, {{-4, 2, "Decline"}});

    RunTest("Test 1b", 1, {{200, 400, "Decline"}});

    RunTest("Test 2", 3, {{0, 5, "Accept"}, {7, 13, "Accept"}, {3, 9, "Accept"}, {5, 7, "Accept"}, {6, 6, "Accept"}, {0, 4, "Accept"}});

    RunTest("Test 3", 3, {{1, 3, "Accept"}, {2, 5, "Accept"}, {1, 9, "Accept"}, {0, 15, "Decline"}});

    RunTest("Test 4", 3, {{1, 3, "Accept"}, {0, 15, "Accept"}, {1, 9, "Accept"}, {2, 5, "Decline"}, {4, 9, "Accept"}});

    RunTest("Test 5", 2, {{1, 3, "Accept"}, {0, 4, "Accept"}, {2, 3, "Decline"}, {5, 5, "Accept"}, {4, 10, "Accept"}, {10, 10, "Accept"}, {6, 7, "Accept"}, {8, 10, "Decline"}, {8, 9, "Accept"}});

    std::cout << "All tests completed." << std::endl;
    return 0;
}