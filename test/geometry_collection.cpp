#include <catch2/catch_all.hpp>
#include <mapvina/geometry.hpp>

TEST_CASE("test geometry collection with out geometry compiles correctly")
{
    mapvina::geometry::geometry_collection<double> gc;
    CHECK(gc.empty());
}
