#include "triangle.h"
#include "display.h"

void int_swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    float inv_slope_1 = (float)(x1 - x0) / (y1 - y0);
    float inv_slope_2 = (float)(x2 - x0) / (y2 - y0);

    float x_start = x0;
    float x_end = x0;

    for (int y = y0; y <= y2 ; y++) {
        draw_line(x_start, y, x_end, y, color);
        x_start += inv_slope_1;
        x_end += inv_slope_2;
    }
}

void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    float inv_slope_1 = (float)(x2 - x0) / (y2 - y0);
    float inv_slope_2 = (float)(x2 - x1) / (y2 - y1);

    float x_start = x2;
    float x_end = x2;

    for (int y = y2; y >= y0 ; y--) {
        draw_line(x_start, y, x_end, y, color);
        x_start -= inv_slope_1;
        x_end -= inv_slope_2;
    }
}

void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
	// We need to sort the vertices by y-coordinate ascending (y0 < y1 < y2)
	if (y0 > y1) {
		int_swap(&y0, &y1);
		int_swap(&x0, &x1);
	}
	if (y1 > y2) {
		int_swap(&y1, &y2);
		int_swap(&x1, &x2);
	}
	if (y0 > y1) {
		int_swap(&y0, &y1);
		int_swap(&x0, &x1);
	}

	if (y1 == y2) {
		// Draw flat-bottom triangle
		fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
	} else if (y0 == y1) {
		// Draw flat-top triangle
		fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
	} else {
		// Calculate the new vertex (Mx,My) using triangle similarity
		int My = y1;
		int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

		// Draw flat-bottom triangle
		fill_flat_bottom_triangle(x0, y0, x1, y1, Mx, My, color);

		// Draw flat-top triangle
		fill_flat_top_triangle(x1, y1, Mx, My, x2, y2, color);
	}
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
	draw_line(x0, y0, x1, y1, color);
	draw_line(x1, y1, x2, y2, color);
	draw_line(x2, y2, x0, y0, color);
}
