#include "../base.h"

// Shamelessly stolen from the wikipedia article on Bresenham's line algorithm.
static void plot_line(bool* view_map,
	int64_t x0, int64_t y0,
	int64_t x1, int64_t y1
) {
	int64_t dx = labs(x1 - x0);
	int64_t sx = x0 < x1 ? 1 : -1;
	int64_t dy = -labs(y1 - y0);
	int64_t sy = y0 < y1 ? 1 : -1;
	int64_t error = dx + dy;

	while (1) {
		view_map[coords_to_index(x0, y0)] = true;
		if (is_opaque(x0, y0)) {
			break;
		}
		int64_t e2 = 2 * error;
		if (e2 >= dy) {
			if (x0 == x1) {
				break;
			}
			error = error + dy;
			x0 = x0 + sx;
		}
		if (e2 <= dx) {
			if (y0 == y1) {
				break;
			}
			error = error + dx;
			y0 = y0 + sy;
		}
	}
}

void generate_view(bool *view_map) {
	view_map[coords_to_index(0,0)] = true;
	for (int64_t i=-VIEW_RADIUS; i < VIEW_RADIUS; i+= 1) {
		plot_line(view_map, 0, 0, VIEW_RADIUS, i);
		plot_line(view_map, 0, 0, -VIEW_RADIUS, i);
		plot_line(view_map, 0, 0, i, VIEW_RADIUS);
		plot_line(view_map, 0, 0, i, -VIEW_RADIUS);
	}
}
