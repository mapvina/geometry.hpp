[![MapVina Logo](https://avatars.githubusercontent.com/u/282217237?s=400&u=edd583b269cdb491b5775bdf10978cde217b841e&v=4)](https://mapvina.com/)

# geometry.hpp

Provides header-only, generic C++ interfaces for geometry types, geometry collections, and features.

 - `mapvina::geometry::point`
 - `mapvina::geometry::multi_point`
 - `mapvina::geometry::line_string`
 - `mapvina::geometry::multi_line_string`
 - `mapvina::geometry::polygon`
 - `mapvina::geometry::multi_polygon`
 - `mapvina::geometry::geometry_collection`
 - `mapvina::feature::feature`

Dependency of [MapVina Native](https://github.com/mapvina/mapvina-native).

### Design

These types are designed to be easy to parse and serialize to [GeoJSON](http://geojson.org/).

They should also be a robust and high performance container for data processing and conversion.


### Goals

 - Header-only
 - Fast compile
 - C++20
 - No external dependencies for usage of core types (point, line_string, etc)
 - No dependencies for usage of enclosing `geometry` type
 - Easily [adaptable to `boost::geometry`](http://www.boost.org/doc/libs/1_56_0/libs/geometry/doc/html/geometry/examples/example__adapting_a_legacy_geometry_object_model.html)


### Usage

Using a single type directly:

```cpp
#include <mapvina/geometry/point.hpp>
#include <iostream>

using mapvina::geometry::point;

int main() {
    point<double> pt(1.0,0.0);
    std::clog << "x: " << pt.x << " y: " << pt.y << "\n";
}
```

Creating a geometry collection:

```cpp
#include <mapvina/geometry/geometry.hpp>
#include <variant>
#include <iostream>

using mapvina::geometry::geometry_collection;
using mapvina::geometry::geometry;
using mapvina::geometry::point;

using point_type = point<double>;

struct printer
{
    printer() {}

    void operator()(point_type const& pt) const
    {
        std::clog << "x: " << pt.x << " y: " << pt.y << "\n";
    }

    template <typename T>
    void operator()(T const& g) const
    {
        std::clog << "encountered non-point geometry\n";
    }
};

int main() {
    geometry_collection<double> gc;
    gc.emplace_back(point_type(1.0,0.0));
    geometry<double> const& geom = gc.at(0);
    printer visitor;
    std::visit(visitor, geom);
}
```
