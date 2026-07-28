#include <time.h>

#include "base.h"

const char* const help =
	"Provide one of the following sets of arguments:\n"
	"\"h\" - print this Help\n"
	"\"g\" SEED DENSITY - Generate a map with seed SEED and density DENSITY (both integers) and print it\n"
	"\"v\" - read a map from stdin and print its View map\n"
	"\"t\" - run the standard suite of Tests and print the results\n"
;

int main(int argc, char* argv[]) {
	struct timespec start;
	struct timespec end;
	static uint32_t its = 100000;
	bool view_map[VIEW_DIAMETER * VIEW_DIAMETER];

	if (argc < 2 || argv[1][0] == 0) {
		fputs(help, stderr);
		return 1;
	}
	switch (argv[1][0]) {
		case 'h':
			if (argv[1][1] != 0) {
				break;
			}
			if (argc != 2) {
				fputs("Argument \"h\" takes no additional arguments.\n", stderr);
				return 1;
			}
			puts(help);
			return 0;
		case 'g':
			if (argv[1][1] != 0) {
				break;
			}
			if (argc != 4) {
				fputs("Argument \"g\" takes two additional arguments: seed and density.\n", stderr);
				return 1;
			}
			char* endptr;
			uint16_t seed = strtol(argv[2], &endptr, 0);
			if (*endptr != 0) {
				fputs("Invalid seed.\n", stderr);
				return 1;
			}
			uint16_t density = strtol(argv[3], &endptr, 0);
			if (*endptr != 0) {
				fputs("Invalid density.\n", stderr);
				return 1;
			}
			generate_map(seed, density);
			print_map();
			return 0;
		case 'v':
			if (argv[1][1] != 0) {
				break;
			}
			if (argc != 2) {
				fputs("Argument \"v\" takes no additional arguments.\n", stderr);
				return 1;
			}
			int32_t ret = read_map();
			if (ret != 0) {
				return 1;
			}
			clean_view(view_map);
			generate_view(view_map);
			print_map_view(view_map);
			return 0;
		case 't':
			if (argv[1][1] != 0) {
				break;
			}
			if (argc != 2) {
				fputs("Argument \"t\" takes no additional arguments.\n", stderr);
				return 1;
			}
			printf("Iterations=%u\n", its);
			printf("density,time(s),tile polls\n");
			for (uint32_t dens=0; dens <= DENSITY_TOP; dens+=10) {
				num_polls = 0;
				clock_gettime(CLOCK_MONOTONIC_RAW, &start);
				for (uint32_t i=0; i < its; i+=1) {
					generate_map(i, dens);
					clean_view(view_map);
					generate_view(view_map);
				}
				clock_gettime(CLOCK_MONOTONIC, &end);
				time_t secs = end.tv_sec - start.tv_sec;
				long nsecs;
				if (start.tv_nsec > end.tv_nsec) {
					secs -= 1;
					nsecs = (1000000000 - start.tv_nsec) + end.tv_nsec;
				} else {
					nsecs = end.tv_nsec - start.tv_nsec;
				}
				printf("%u,%ld.%09lu,%lu\n", dens, secs, nsecs, num_polls);
			}
			return 0;
	}
	fputs(help, stderr);
	return 1;
}
