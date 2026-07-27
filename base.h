// This file represents a standard interface for testing view-calculating
// algorithms. Each algorithm should implement `generate_view`. Some of these
// functions are intended for use in the algorithm, some are not. More
// information can be found at the declaration of the `generate_view`.
//
// A couple of other notes:
// - The map data structure is intentionally hidden.
// - Don't question the weird mix of `int32_t` and `int64_t`.
// - A careful programmer (I saw that in a man page once) will make all other
//   functions in their implementation `static`.

#ifndef BASE_H
#define BASE_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// The viewable square has side lengths of `VIEW_DIAMETER`.
#define VIEW_RADIUS 15
#define VIEW_DIAMETER (VIEW_RADIUS * 2 + 1)

// Generates the map to be viewed.
// `density` is the probability ([0-1] maps to [0-256]) that any given tile is
// opaque.
void generate_map(uint16_t seed, uint16_t density);

// Reads in map data from stdin. It should be formatted as an ascii square with
// side lengths `VIEW_DIAMETER`, where each row is delimited by a newline
// character. '#' is used to indicate an opaque tile. Everything else is
// considered transparent, but it is encouraged to put a '@' at the center to
// indicate the player and use '.' for generic floor tiles. Everything after the
// first `(VIEW_DIAMETER + 1) * VIEW_DIAMETER` bytes is ignored.
//
// Upon success, returns `0`. Upon failure, returns `-1` and prints the error to
// stderr (and the contents of the map are undefined).
int32_t read_map(void);

// This tracks how many times a tile was polled for opacity. You should
// probably reset this to 0 between tests.
extern uint64_t num_polls;

// Returns `true` if the tile is opaque. Tiles beyond the view radius are
// considered opaque. The player is at (0,0). Increments `num_polls`.
bool is_opaque(int64_t x, int64_t y);

// This is not implemented in `base.c`, it is for you to implement. `view_map`
// should be filled with which tiles are visible. (0,0), the location of the
// character, should be visible. Opaque tiles which can be seen should also be
// considered visible.
//
// `view_map` is of length `VIEW_DIAMETER * VIEW_DIAMETER`. Visible tiles are
// marked with `true`, and non-visible tiles are marked with `false`. It should
// be filled with `false` before this function is called. It is in row-major
// order and the coordinates are offset by `VIEW_RADIUS`.
//
// Symbols intended to be used by this function:
// - `is_opaque`
// - `coords_to_index`
// - `index_to_coords`
// - `VIEW_DIAMETER`
// - `VIEW_RADIUS`
void generate_view(bool *view_map);

// Initializes a view map as it should be before calling `generate_view`.
static void clean_view(bool *view_map) {
	memset(view_map, 0, VIEW_DIAMETER * VIEW_DIAMETER);
}

// These 2 are helper functions / reference implementations for the relationship
// between the parameters to `is_opaque` and the indexing of view maps.
static void index_to_coords(size_t i, int64_t* x, int64_t* y) {
	*x = (int64_t)(i % VIEW_DIAMETER) - VIEW_RADIUS;
	*y = (int64_t)(i / VIEW_DIAMETER) - VIEW_RADIUS;
}
static size_t coords_to_index(int64_t x, int64_t y) {
	return (y + VIEW_RADIUS) * VIEW_DIAMETER + x + VIEW_RADIUS;
}

// Prints the map to stdout.
void print_map(void);

// Prints the visible tiles of the map to stdout. Invisible tiles are printed as
// ' '.
void print_map_view(bool* view_map);

#endif
