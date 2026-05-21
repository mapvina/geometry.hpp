#include <catch2/catch_all.hpp>
#include <mapvina/geometry/empty.hpp>

using mapvina::geometry::empty;

TEST_CASE("test empty")
{
    empty n1;
    empty n2;
    CHECK(n1 == n2);
    CHECK(!(n1 != n2));
    CHECK(!(n1 < n2));
    CHECK(!(n1 > n2));
    CHECK(n1 <= n2);
    CHECK(n1 >= n2);
}
