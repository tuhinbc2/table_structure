#include <iostream>
#include <vector>

#include "tablepixel.h"


int main()
{
	/*Dimension x(100, 10, 10);
	std::vector<int> pos;
	pos = x.get_start_positions();
	for (int i = 0; i < (int)pos.size();i++){
		printf("X: %d <---> %d\n", pos[i], x.get_end_position(i));
	}*/

	TablePixel table(100, 100, 5, 8, 10);
	std::pair<int, int> val;

	for (int i = 0; i < (int)table.get_number_of_rows();i++){
		for(int j = 0; j < (int)table.get_number_of_columns();j++){
			if(table.get_start_position(i, j, &val) == INVALID_INDEX) return (-1);
			printf("< (%d,%d) X:%2d Y:%2d ----->", i, j, val.first, val.second);

			if(table.get_end_position(i, j, &val) == INVALID_INDEX) return (-1);
			printf(" X:%2d Y:%2d >\n", val.first, val.second);
		}

		ObjDetails details;
		if(table.get_vertical_border_details(i, &details) == SUCCESS){
			printf("|| no: %d x:%d y:%d height:%d width:%d\n", i, details.x, details.y, details.height, details.width);
			if(table.get_horizontal_border_details(i, &details) == SUCCESS){
				printf("-- no: %d x:%d y:%d height:%d width:%d\n", i, details.x, details.y, details.height, details.width);
			}else{
				printf("-- no. invalid\n");
			}
		}else{
			printf("|| no. invalid\n");
		}
	}

	printf("%d\n", int (sizeof(table)));

	return 0;
}