#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <queue>
#include <bitset>

class Hotel
{
private:
    int size;
    static const int MaxDays = 366;
    // Using a brute-force approach with a 2D vector for occupancy tracking
    std::vector<std::vector<bool>> occupied_bf;
    using Bitset = std::bitset<MaxDays>;
    // Using a bitset for occupancy tracking in each room
    std::vector<Bitset> occupied_bs;
    std::vector<int> utilization;

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
    int countUtilization_bs(int room) const
    {
        return utilization[room];
    }

public:
    Hotel(int s)
        : size(s),
          occupied_bf(s, std::vector<bool>(MaxDays, false)),
          occupied_bs(s, Bitset()),
          utilization(s, 0) {}
    // Basic booking function: Book
    // Uses a brute-force approach to find the most utilized room

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

        // Assumption: Assign to the most utilized room to leave less utilized rooms for future stays
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

    // Optimized heap-based approach: Book_V2
    // Uses a priority queue to select the most utilized available room efficiently
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

        // Use a max-heap to select the most utilized room (with lowest room number in case of tie)
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
    // Book_V3: Most optimal approach using bitsets and priority queue
    // This method finds the most utilized room that is available for the requested period
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