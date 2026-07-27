#include "base.h"

int main(int argc, char* argv[]) {
	read_map();
	// generate(0xBEEF, 15);
	print_map();
	bool view_map[VIEW_DIAMETER * VIEW_DIAMETER];
	clean_view(view_map);
	generate_view(view_map);
	print_map_view(view_map);
}
