#pragma once

#include <graphics.h>
#include <conio.h>
#include <algorithm>

#include "GeoCal.hpp"

namespace Moly {
	using std::cout;
	using std::endl;
	const double PI = 3.141592653589793;

	class GraphicsDevice {
	public:
		int pixelSize = 1;
		int m_margin = 10;

	private:
		int m_width;
		int m_height;

	public:
		GraphicsDevice() {
			initgraph(400, 400, EX_SHOWCONSOLE);
		}
		GraphicsDevice(int w = 400, int h = 400) {
			m_width = w;
			m_height = h;
			initgraph(w, h);
		}
		~GraphicsDevice() {
			auto _ = _getch();
			closegraph();
		}

		void SetPixel(int x, int y) {
			fillcircle(x, y, pixelSize);
		}

		void DrawLineWithOptimize(int sx, int sy, int ex, int ey) {
			double k = 1.0 * (ey - sy) / (ex - sx);
			if (fabs(k) <= 1) {
				for (int x = sx; x <= ex; x++) {
					int y = k * x;
					putpixel(x, y, RED);
				}
			}
			else {
				k = 1.0 / k;
				for (int y = sy; y <= ey; y++) {
					int x = k * y;
					putpixel(x, y, RED);
				}
			}
		}

		void DrawLine(int sx, int sy, int ex, int ey) {
			line(sx, sy, ex, ey);
			//Sleep(100);
		}

		void drawMap() {
			for (int x = m_margin; x <= m_width; x += m_margin) {
				for (int y = m_margin; y <= m_height; y += m_margin) {
					putpixel(x, y, WHITE);
				}
			}
		}

		void drawTraingle(Moly::Vec2 PointA, Moly::Vec2 PointB, Moly::Vec2 PointC) {


			DrawLine(PointA.x, PointA.y, PointB.x, PointB.y);
			DrawLine(PointA.x, PointA.y, PointC.x, PointC.y);
			DrawLine(PointC.x, PointC.y, PointB.x, PointB.y);
			std::vector<Moly::Vec2> points = { PointA, PointB, PointC };
			std::sort(points.begin(), points.end(), [&](Vec2& a, Vec2& b) {
				if (a.y != b.y) return a.y < b.y;
				return a.x < b.x;
				});
			/* this trangle will be like that through compare Y, A in top, B in middle, C in bottom
			* and then we will first draw ABP, then BCP before

							A
						   / \
						  /   \
						 /     \
						B - - - P      P is a Temp Point
						 \       \
						   \      \
							 \     \
							   \    \
								 \   \
								   \  \
									 \ C
			*/
			for (int y = points[0].y; y <= points[2].y; ++y) {
				// 找到当前扫描行与三角形的交点
				std::vector<Moly::Vec2> intersections;
				for (int i = 0; i < 3; ++i) {
					int j = (i + 1) % 3;
					if ((points[i].y <= y && points[j].y > y) || (points[i].y > y && points[j].y <= y)) {
						double x = points[i].x + (y - points[i].y) * (points[j].x - points[i].x) / (points[j].y - points[i].y);
						intersections.push_back(Moly::Vec2{ int(x), int(y) });
					}
				}
				if (intersections.size() < 2) break;
				// 对交点按 x 值进行排序
				std::sort(intersections.begin(), intersections.end(), [](const Moly::Vec2& a, const Moly::Vec2& b) {
					return a.x < b.x;
					});

				// 绘制扫描线上的线段
				for (size_t i = 0; i < intersections.size() - 1; i += 2) {
					DrawLine(intersections[i].x, y, intersections[i + 1].x, y);
				}
			}
		}

		void DrawRectangle(Moly::Vec2 PointA, Moly::Vec2 PointB) {
			drawTraingle({ PointA.x, PointA.y }, { PointA.x, PointB.y }, { PointB.x, PointB.y });
			drawTraingle({ PointA.x, PointA.y }, { PointB.x, PointA.y }, { PointB.x, PointB.y });
		}

		//这是我写的，下面是gpt的实现
		//void DrawCircle(Moly::Vec2 circleCenter, int radius = 10, int trangleCnt = 32) {
		//	double trangleDeg = 360.0 / trangleCnt;
		//	Moly::Vec2 left_cor = { circleCenter.x,  circleCenter.y + radius};
		//	Moly::Vec2 right_cor = rotatePoint(circleCenter, left_cor, trangleDeg);
		//	srand(time(nullptr));
		//	for (int i = 0; i <= trangleCnt; i++) {
		//		// 生成随机颜色
		//		int red = rand() % 256;
		//		int green = rand() % 256;
		//		int blue = rand() % 256;
		//		COLORREF randomColor = RGB(red, green, blue);
		//		//setcolor(randomColor);

		//		left_cor = right_cor;
		//		right_cor = rotatePoint(circleCenter, left_cor, trangleDeg * (PI / 180));
		//		drawTraingle(circleCenter, left_cor, right_cor);
		//	}
		//}

		void DrawCircle(const Vec2& circleCenter, int radius = 10, int triangleCnt = 32) {
			const float angleIncrement = (2 * PI) / triangleCnt;
			srand(time(nullptr));
			for (int i = 0; i < triangleCnt; i++) {
				float angle1 = i * angleIncrement;
				float angle2 = (i + 1) * angleIncrement;

				Vec2 pointA = { int(circleCenter.x + radius * cos(angle1)), int(circleCenter.y + radius * sin(angle1)) };
				Vec2 pointB = { int(circleCenter.x), int(circleCenter.y) };
				Vec2 pointC = { int(circleCenter.x + radius * cos(angle2)), int(circleCenter.y + radius * sin(angle2)) };

				// 生成随机颜色
				int red = rand() % 256;
				int green = rand() % 256;
				int blue = rand() % 256;
				COLORREF randomColor = RGB(red, green, blue);
				setcolor(randomColor);

				drawTraingle(pointA, pointB, pointC);
			}
		}
	};

}//namespace Mo ly