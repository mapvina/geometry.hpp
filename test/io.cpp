#include <catch2/catch_all.hpp>
#include <mapvina/geometry_io.hpp>

#include <iostream>

TEST_CASE("operator<<")
{
    mapvina::geometry::empty empty;
    mapvina::geometry::point<double> point{10, 20};
    mapvina::geometry::point<double> point2{30, 40};
    mapvina::geometry::line_string<double> lineString{point, point2};
    mapvina::geometry::polygon<double> polygon{mapvina::geometry::linear_ring<double>{point, point2}};
    mapvina::geometry::multi_point<double> multiPoint{point, point2};
    mapvina::geometry::multi_line_string<double> multiLineString{lineString, lineString};
    mapvina::geometry::multi_polygon<double> multiPolygon{polygon};
    mapvina::geometry::geometry_collection<double> collection{multiPolygon};

    std::stringstream stream;
    stream << empty << std::endl;
    stream << point << std::endl;
    stream << lineString << std::endl;
    stream << polygon << std::endl;
    stream << multiPoint << std::endl;
    stream << multiLineString << std::endl;
    stream << multiPolygon << std::endl;
    stream << collection << std::endl;
    stream << mapvina::geometry::geometry<double>{collection} << std::endl;

    std::string line;

    std::getline(stream, line);
    CHECK(line == std::string("[]"));

    std::getline(stream, line);
    CHECK(line == std::string("[10,20]"));

    std::getline(stream, line);
    CHECK(line == std::string("[[10,20],[30,40]]"));

    std::getline(stream, line);
    CHECK(line == std::string("[[[10,20],[30,40]]]"));

    std::getline(stream, line);
    CHECK(line == std::string("[[10,20],[30,40]]"));

    std::getline(stream, line);
    CHECK(line == std::string("[[[10,20],[30,40]],[[10,20],[30,40]]]"));

    std::getline(stream, line);
    CHECK(line == std::string("[[[[10,20],[30,40]]]]"));

    std::getline(stream, line);
    CHECK(line == std::string("[[[[[10,20],[30,40]]]]]"));

    std::getline(stream, line);
    CHECK(line == std::string("[[[[[10,20],[30,40]]]]]"));
}

TEST_CASE("operator<< feature value")
{
    mapvina::feature::null_value_t null;
    mapvina::feature::value val_null{};
    mapvina::feature::value val_int{1};
    mapvina::feature::value val_uint{1U};
    mapvina::feature::value val_double{1.2};
    mapvina::feature::value val_str{"foo"};
    mapvina::feature::value val_str_quote{"\"foo\""};
    mapvina::feature::value val_str_backslash{"\\"};
    mapvina::feature::value val_bool_true{true};
    mapvina::feature::value val_bool_false{false};
    std::vector<mapvina::feature::value> vec = {1, "fee", true, "\"faa\"", "\\"};
    mapvina::feature::value val_vec{vec};
    std::unordered_map<std::string, mapvina::feature::value> map = {{"fee", "foo"}, {"blah\"", 12}};
    mapvina::feature::value val_map{map};

    std::stringstream stream;
    stream << null << std::endl;
    stream << val_null << std::endl;
    stream << val_int << std::endl;
    stream << val_uint << std::endl;
    stream << val_double << std::endl;
    stream << val_str << std::endl;
    stream << val_str_quote << std::endl;
    stream << val_str_backslash << std::endl;
    stream << val_bool_true << std::endl;
    stream << val_bool_false << std::endl;
    stream << vec << std::endl;
    stream << val_vec << std::endl;
    stream << map << std::endl;
    stream << val_map << std::endl;

    std::string line;

    std::getline(stream, line);
    CHECK(line == std::string("null"));

    std::getline(stream, line);
    CHECK(line == std::string("null"));

    std::getline(stream, line);
    CHECK(line == std::string("1"));

    std::getline(stream, line);
    CHECK(line == std::string("1"));

    std::getline(stream, line);
    CHECK(line == std::string("1.2"));

    std::getline(stream, line);
    CHECK(line == std::string("\"foo\""));

    std::getline(stream, line);
    CHECK(line == std::string("\"\\\"foo\\\"\""));

    std::getline(stream, line);
    CHECK(line == std::string("\"\\\\\""));

    std::getline(stream, line);
    CHECK(line == std::string("true"));

    std::getline(stream, line);
    CHECK(line == std::string("false"));

    std::getline(stream, line);
    CHECK(line == std::string("[1,\"fee\",true,\"\\\"faa\\\"\",\"\\\\\"]"));

    std::getline(stream, line);
    CHECK(line == std::string("[1,\"fee\",true,\"\\\"faa\\\"\",\"\\\\\"]"));

    std::getline(stream, line);
    CHECK(line == std::string("{\"blah\\\"\":12,\"fee\":\"foo\"}"));

    std::getline(stream, line);
    CHECK(line == std::string("{\"blah\\\"\":12,\"fee\":\"foo\"}"));
}

TEST_CASE("operator<< feature identifier")
{
    mapvina::feature::identifier id_null{};
    mapvina::feature::identifier id_int{static_cast<std::int64_t>(1)};
    mapvina::feature::identifier id_uint{static_cast<std::uint64_t>(1U)};
    mapvina::feature::identifier id_double{static_cast<double>(1.2)};
    mapvina::feature::identifier id_str{"foo"};
    mapvina::feature::identifier id_str_quote{"\"foo\""};
    mapvina::feature::identifier id_str_backslash{"\\"};

    std::stringstream stream;
    stream << id_null << std::endl;
    stream << id_int << std::endl;
    stream << id_uint << std::endl;
    stream << id_double << std::endl;
    stream << id_str << std::endl;
    stream << id_str_quote << std::endl;
    stream << id_str_backslash << std::endl;

    std::string line;

    std::getline(stream, line);
    CHECK(line == std::string("null"));

    std::getline(stream, line);
    CHECK(line == std::string("1"));

    std::getline(stream, line);
    CHECK(line == std::string("1"));

    std::getline(stream, line);
    CHECK(line == std::string("1.2"));

    std::getline(stream, line);
    CHECK(line == std::string("\"foo\""));

    std::getline(stream, line);
    CHECK(line == std::string("\"\\\"foo\\\"\""));

    std::getline(stream, line);
    CHECK(line == std::string("\"\\\\\""));
}
