#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "PriorityQueue.hpp"

// ascending order: smaller value is “better”
PriorityQueue<int, std::less<>> Q;

TEST_CASE("PriorityQueue push/poll order")
{
    Q.push(3); Q.push(1); Q.push(2);
    REQUIRE(Q.poll() == 1);
    REQUIRE(Q.poll() == 2);
    REQUIRE(Q.poll() == 3);
    REQUIRE_THROWS_AS(Q.poll(), EmptyPriorityQueueException);
}