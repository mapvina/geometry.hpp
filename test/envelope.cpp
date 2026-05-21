#include <catch2/catch_all.hpp>
#include <mapvina/geometry/envelope.hpp>

using mapvina::geometry::box;
using mapvina::geometry::envelope;
using mapvina::geometry::geometry;
using mapvina::geometry::geometry_collection;
using mapvina::geometry::line_string;
using mapvina::geometry::multi_line_string;
using mapvina::geometry::multi_point;
using mapvina::geometry::multi_polygon;
using mapvina::geometry::point;
using mapvina::geometry::polygon;

TEST_CASE("test envelope")
{
    CHECK(envelope(point<int64_t>(0, 0)) == box<int64_t>({0, 0}, {0, 0}));
    CHECK(envelope(line_string<int64_t>({{0, 1}, {2, 3}})) == box<int64_t>({0, 1}, {2, 3}));
    CHECK(envelope(polygon<int64_t>({{{0, 1}, {2, 3}}})) == box<int64_t>({0, 1}, {2, 3}));

    CHECK(envelope(multi_point<int64_t>({{0, 0}})) == box<int64_t>({0, 0}, {0, 0}));
    CHECK(envelope(multi_line_string<int64_t>({{{0, 1}, {2, 3}}})) == box<int64_t>({0, 1}, {2, 3}));
    CHECK(envelope(multi_polygon<int64_t>({{{{0, 1}, {2, 3}}}})) == box<int64_t>({0, 1}, {2, 3}));

    CHECK(envelope(geometry<int>(point<int>(0, 0))) == box<int>({0, 0}, {0, 0}));
    CHECK(envelope(geometry_collection<int>({point<int>(0, 0)})) == box<int>({0, 0}, {0, 0}));
}
