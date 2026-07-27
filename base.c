#include "base.h"

uint8_t map[VIEW_DIAMETER * VIEW_DIAMETER];

uint64_t num_polls;

bool is_opaque(int64_t x, int64_t y) {
	num_polls += 1;
	if (labs(x) > VIEW_RADIUS || labs(y) > VIEW_RADIUS) {
		return true;
	}
	size_t i = coords_to_index(x, y);
	return map[i] == '#';
}

void generate_map(uint16_t seed, uint16_t density) {
	// LFSR doesn't tolerate 0s.'
	if (seed == 0) {
		seed = 1;
	}
	for (size_t i=0; i < VIEW_DIAMETER * VIEW_DIAMETER; i+=1) {
		for (int j=0; j < 8; j+=1) {
			bool lsb = seed & 1;
			seed >>= 1;
			if (lsb) {
				seed ^= 0xB400u;
			}
		}
		uint8_t opacity = (uint8_t)seed & 0xFF;
		map[i] = opacity < density ? '#' : '.';
	}
	map[VIEW_RADIUS * VIEW_DIAMETER + VIEW_RADIUS] = '@';
}

int32_t read_map(void) {
	uint8_t buf[VIEW_DIAMETER+1];
	for (size_t i=0; i < VIEW_DIAMETER; i+=1) {
		ssize_t ret = read(STDIN_FILENO, buf, sizeof(buf));
		if (ret < 0) {
			perror("Couldn't read from stdin");
			return -1;
		}
		if (ret != sizeof(buf)) {
			fputs("Invalid read size.", stderr);
			return -1;
		}
		if (buf[VIEW_DIAMETER] != '\n') {
			fprintf(stderr, "Expected newline after %d characters.\n", VIEW_DIAMETER);
			return -1;
		}
		memcpy(&map[i * VIEW_DIAMETER], buf, VIEW_DIAMETER);
	}
	return 0;
}

void print_map(void) {
	uint8_t line[VIEW_DIAMETER + 1];
	line[VIEW_DIAMETER] = 0;
	for (size_t y=0; y < VIEW_DIAMETER * VIEW_DIAMETER; y+=VIEW_DIAMETER) {
		memcpy(line, &map[y], VIEW_DIAMETER);
		puts(line);
	}
}

void print_map_view(bool* view_map) {
	uint8_t line[VIEW_DIAMETER + 1];
	line[VIEW_DIAMETER] = 0;
	size_t i = 0;
	for (size_t y=0; y < VIEW_DIAMETER; y+=1) {
		memcpy(line, &map[i], VIEW_DIAMETER);
		for (size_t x=0; x < VIEW_DIAMETER; x+=1) {
			if (view_map[i] == false) {
				line[x] = ' ';
			}
			i += 1;
		}
		puts(line);
	}
}
