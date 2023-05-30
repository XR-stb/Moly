#pragma once

#include <vector>

namespace Moly {
    double gradient(Moly::Vec2 PointA, Moly::Vec2 PointB) {
        return (PointA.y - PointB.y) / (PointA.x - PointB.x);
    }

    double calculateIntersectionY(double x, double x1, double y1, double x2, double y2) {
        double k = (y2 - y1) / (x2 - x1);
        double b = y1 - k * x1;
        double y = k * x + b;
        return y;
    }

    double calculateIntersectionX(double y, double x1, double y1, double x2, double y2) {
        double k = (y2 - y1) / (x2 - x1);
        double b = y1 - k * x1;
        double x = (y - b) / k;
        return x;
    }

    std::vector<double> lineCrossPoint(const std::vector<double>& line1, const std::vector<double>& line2) {
        double x1 = line1[0];
        double y1 = line1[1];
        double x2 = line1[2];
        double y2 = line1[3];

        double x3 = line2[0];
        double y3 = line2[1];
        double x4 = line2[2];
        double y4 = line2[3];

        double k1, b1, k2, b2;
        if (x2 - x1 == 0) {
            k1 = 0;
            b1 = y1;
        }
        else {
            k1 = (y2 - y1) / (x2 - x1);
            b1 = y1 - x1 * k1;
        }

        if (x4 - x3 == 0) {
            k2 = 0;
            b2 = y3;
        }
        else {
            k2 = (y4 - y3) / (x4 - x3);
            b2 = y3 - x3 * k2;
        }

        if (k1 == 0 && k2 == 0) {
            if (x1 == x3) {
                std::vector<double> result{ x1, y1 };
                return result;
            }
            else {
                return std::vector<double>();
            }
        }
        else if (k1 != 0 && k2 == 0) {
            double x = x3;
            double y = k1 * x + b1;
            std::vector<double> result{ x, y };
            return result;
        }
        else if (k1 == 0 && k2 != 0) {
            double x = x1;
            double y = k2 * x + b2;
            std::vector<double> result{ x, y };
            return result;
        }
        else {
            if (k1 == k2) {
                if (b1 == b2) {
                    std::vector<double> result{ x1, y1 };
                    return result;
                }
                else {
                    return std::vector<double>();
                }
            }
            else {
                double x = (b2 - b1) / (k1 - k2);
                double y = k1 * x + b1;
                std::vector<double> result{ x, y };
                return result;
            }
        }
    }

    Moly::Vec2 rotatePoint(const Moly::Vec2& A, const Moly::Vec2& B, double angle) {
        // 平移到以点A为原点
        double xb_prime = B.x - A.x;
        double yb_prime = B.y - A.y;

        // 进行旋转变换
        double xb_double_prime = xb_prime * cos(angle) - yb_prime * sin(angle);
        double yb_double_prime = xb_prime * sin(angle) + yb_prime * cos(angle);

        // 还原到原来的位置
        double xb = xb_double_prime + A.x;
        double yb = yb_double_prime + A.y;

        Moly::Vec2 rotatedPoint = { int(xb), int(yb) };
        return rotatedPoint;
    }

}