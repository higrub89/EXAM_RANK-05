
#include "bsq.h"

int loadElements(FILE* file, t_elements* elements)
{
	int ret = fscanf(file, "%d %c %c %c", &(elements->n_lines), &(elements->empty), &(elements->obstacle), &(elements->full));

	if((ret != 4))
		return(-1);

	if(elements->n_lines <= 0)
		return(-1);
	if(elements->empty == elements->obstacle || elements->empty == elements->full || elements->obstacle == elements->full)
		return(-1);
	if(elements->empty < 32 || elements->empty > 126)
		return(-1);
	if(elements->obstacle < 32 || elements->obstacle > 126)
		return(-1);
	if(elements->full < 32 || elements->full > 126)
		return(-1);

	return(0);
}

char* ft_substr(char* arr, int len)
{
	char* str = (char*)malloc(len + 1);
	if (!str)
		return (NULL);
	int i = 0;
	while (i < len)
	{
		str[i] = arr[i];
		i++;
	}
	str[i] = '\0';
	return(str);
}

void free_map(char** arr)
{
	int i = 0;
	if(arr)
	{
		while (arr[i] != NULL)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

int element_control(char** map, char c1, char c2)
{
	int i = 0;
	while(map[i])
	{
		int j = 0;
		while(map[i][j] != '\0')
		{
			if((map[i][j] != c1) && (map[i][j] != c2))
				return(-1);
			j++;
		}
		i++;
	}
	return(0);
}

int loadMap(FILE* file, t_map* map, t_elements* elements)
{
	map->height = elements->n_lines;
	map->grid = (char**)calloc(map->height + 1, sizeof(char *));
	if(!map->grid)
		return(-1);

	char* line = NULL;
	size_t len = 0;

	if(getline(&line, &len, file) == -1) {
		free(line);
		free_map(map->grid);
		return(-1);
	}

	for(int i = 0; i < map->height; i++)
	{
		int read = getline(&line, &len, file);
		if(read == -1) {
			free(line);
			free_map(map->grid);
			return(-1);
		}
		if(line[read - 1] == '\n')
			read--;
		else{
			free(line);
			free_map(map->grid);
			return(-1);
		}
		map->grid[i] = ft_substr(line, read);
		if(!(map->grid[i]))
		{
			free(line);
			free_map(map->grid);
			return(-1);
		}

		if(i == 0)
			map->width = read;
		else{
			if(map->width != read){
				free(line);
				free_map(map->grid);
				return(-1);
			}
		}
	}

	if(element_control(map->grid, elements->empty, elements->obstacle) == -1) {
		free(line);
		free_map(map->grid);
		return(-1);
	}

	free(line);

	return (0);
}

int find_min(int n1, int n2, int n3)
{
	int min = n1;

	if(n2 < min)
		min = n2;
	if(n3 < min)
		min = n3;
	return(min);
}

void find_big_square(t_map* map, t_square* square, t_elements* elements)
{
	int *dp = (int*)calloc(map->width, sizeof(int));
	if(!dp)
		return;

	for(int i = 0; i < map->height; i++)
	{
		int prev = 0;
		for(int j = 0; j < map->width; j++)
		{
			int temp = dp[j];
			if(map->grid[i][j] == elements->obstacle)
				dp[j] = 0;
			else if(i == 0 || j == 0)
				dp[j] = 1;
			else
				dp[j] = find_min(dp[j], prev, dp[j - 1]) + 1;

			if(dp[j] > square->size)
			{
				square->size = dp[j];
				square->i = i - dp[j] + 1;
				square->j = j - dp[j] + 1;
			}
			prev = temp;
		}
	}
	free(dp);
}

void print_filled_square(t_map* map, t_square* square, t_elements* elements)
{
	for(int i = square->i; i < square->i + square->size; i++)
	{
		for(int j = square->j; j < square->j + square->size; j++)
		{
			if((i < map->height) && (j < map->width))
				map->grid[i][j] = elements->full;
		}
	}

	for(int i = 0; i < map->height; i++)
	{
		fprintf(stdout, "%s\n", map->grid[i]);
	}
}

int execute_bsq(FILE* file)
{
	t_elements elements;
	if(loadElements(file, &elements) == -1)
		return(-1);

	t_map map;
	if(loadMap(file, &map, &elements) == -1)
		return(-1);

	t_square square;
	square.size = 0; square.i = 0; square.j = 0;
	find_big_square(&map, &square, &elements);
	print_filled_square(&map, &square, &elements);
	free_map(map.grid);
	return(0);
}

int convert_file_pointer(char* name)
{
	FILE* file = fopen(name, "r");
	if(!file)
		return(-1);
	int ret = execute_bsq(file);
	fclose(file);
	return(ret);
}
