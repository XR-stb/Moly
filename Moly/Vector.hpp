#include <tuple>
#include <utility> // 包含 std::exchange 函数的头文件

namespace Moly {
    class Vec1 {
    public:
        int x;

        Vec1() : x(0) {}

        Vec1(int x) : x(x) {}

        Vec1(const Vec1& other) : x(other.x) {}

        Vec1(Vec1&& other) noexcept : x(std::exchange(other.x, 0)) {}

        Vec1& operator=(const Vec1& other) {
            if (this != &other) {
                x = other.x;
            }
            return *this;
        }

        Vec1& operator=(Vec1&& other) noexcept {
            if (this != &other) {
                x = std::exchange(other.x, 0);
            }
            return *this;
        }

        std::tuple<int> getValue() const {
            return std::make_tuple(x);
        }
    };

    class Vec2 {
    public:
        int x;
        int y;

        Vec2() : x(0), y(0) {}

        Vec2(int x, int y) : x(x), y(y) {}

        Vec2(double x, double y) : x(static_cast<int>(x)), y(static_cast<int>(y)) {}

        Vec2(const Vec2& other) : x(other.x), y(other.y) {}

        Vec2(Vec2&& other) noexcept : x(std::exchange(other.x, 0)), y(std::exchange(other.y, 0)) {}

        Vec2& operator=(const Vec2& other) {
            if (this != &other) {
                x = other.x;
                y = other.y;
            }
            return *this;
        }

        Vec2& operator=(Vec2&& other) noexcept {
            if (this != &other) {
                x = std::exchange(other.x, 0);
                y = std::exchange(other.y, 0);
            }
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
            os << "(" << vec.x << ", " << vec.y << ")";
            return os;
        }

        std::tuple<int, int> getValue() const {
            return std::make_tuple(x, y);
        }
    };

    class Line {
    public:
        Vec2 endian_A, endian_B;
        Line(int xa, int ya, int xb, int yb) : endian_A(xa, ya), endian_B(xb, yb) {}
        Line(Vec2 A, Vec2 B) : endian_A(A), endian_B(B) {}
        bool isXOnLine(int x) {

        }
    };

}//namespace Moly