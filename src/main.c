#include <string.h>
#include "fractal.h"
#include <pthread.h>


//get color pixel
//Does calculation, equaltion is a function pointer set depending on the params
#define POS(x, y, width) ((x) + (y) * (width * 4))	//Fix for efficicy

typedef struct s_threading_info {
	int start;
	int end;
	v_window *window;
} t_threading_info; 

void *getPixels(void *arg)
{
	t_threading_info *tmp;

	tmp = (t_threading_info *)arg;
	char *pixels;
	int color;

	pixels = tmp->window->pixel;
	for (int y = tmp->start; y < tmp->end; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			color = tmp->window->func(x, y, tmp->window->mouse.updated);

			pixels[POS(x * 4, y, WIDTH)] = color; 
			pixels[POS(((x * 4) + 1), y, WIDTH)] = color; 
			pixels[POS(((x * 4) + 2), y, WIDTH)] = color; 
			pixels[POS(((x * 4) + 3), y, WIDTH)] = 0; 
		}
	}
	return NULL;	
}


void drawWindow2(v_window *window)
{
	// getPixels(&(t_threading_info){0, HEIGHT, window});
	pthread_t thread;
	pthread_t thread2;
	pthread_t thread3;
	int section;

	section = HEIGHT / 4;
	getPixels(&(t_threading_info){0, section, window});
	pthread_create(&thread, NULL, getPixels, &(t_threading_info){section * 1, section * 2, window});
	pthread_create(&thread2, NULL, getPixels, &(t_threading_info){section * 2, section * 3, window});
	pthread_create(&thread3, NULL, getPixels, &(t_threading_info){section * 3, HEIGHT, window});
	pthread_join(thread, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	// char *tmp;

	// tmp = window->pixel;
	// // printf("What's up \n");

	// int color;
	// for (int y = 0; y < HEIGHT; y++)
	// {
	
	// 	// printf("-------  Y  -------%d \n", y);
	// 	//multthread here

	// 	for (int x = 0; x < WIDTH; x++)
	// 	{
	// 		// color = mandelbrot(x, y);
	// 		color = window->func(x, y, window->mouse.updated);
	// 		// color = 100;	
	// 		tmp[POS(x * 4, y, WIDTH)] = color; 
	// 		tmp[POS(((x * 4) + 1), y, WIDTH)] = color; 
	// 		tmp[POS(((x * 4) + 2), y, WIDTH)] = color; 
	// 		tmp[POS(((x * 4) + 3), y, WIDTH)] = 0; 
	// 	}
	// 	// printf("\n");
	// }
}

void update(v_window *window)
{

	//setPixels
	//UI -> location / colors
	//clear
	//set cordinates
	//put on screen



	drawWindow2(window);
	// window->update = true;
	//Some how sinc, wait for a something?

	mlx_clear_window(window->mlx, window->window);	//Flip these two + Add UI
	mlx_put_image_to_window(window->mlx, window->window, window->image, 0, 0);
	ui(window);
}







// void fillImage(char *tmp, int (*fractal))
// {
// 	int color;

			
// }



v_window *createWindow(void *mlx, char *name)
{
	v_window *tmp;
	int num;

	tmp = malloc(sizeof(v_window));
	//Set function pointer?
	if (!strcmp(name, "julia"))
	{
		tmp->func = juliaFunc;
		tmp->type = julia;
	}
	if (!strcmp(name, "man"))
	{
		tmp->func = mandelbrotFunc;
		tmp->type = mandelbrot;
	}
	tmp->window = mlx_new_window(mlx, WIDTH, HEIGHT, name);
	tmp->image = mlx_new_image(mlx, WIDTH, HEIGHT);
	tmp->pixel = mlx_get_data_addr(tmp->image, &num, &num, &num);
	tmp->mlx = mlx; //This pointer wont work
	tmp->mouse.actual = (t_vector){-0.7, 0.27015}; //Default
	tmp->mouse.updated = (t_vector){-0.7, 0.27015}; //Default
	return tmp;
}


t_info *newInfo(int argc, char **argv)
{
	t_info *info;
	v_window *tmp;

	info = malloc(sizeof(t_info));
	info->mlx = mlx_init();
	info->windows = malloc(sizeof(v_window *) * WIN_MAX);
	bzero(info->windows, sizeof(v_window *) * WIN_MAX);
	//Loop to get dimention?
	while (--argc)
	{
		tmp = createWindow(info->mlx, argv[argc]);
		if (info->windows[tmp->type] == NULL)
		{
			info->windows[tmp->type] = tmp;
		}
		else 
		{
			printf("Duplicates are not allowed\n");
			exit(EXIT_FAILURE);	
		}
	}
	return (info);
}



int main(int argc, char **argv)
{
	t_info *info;

	if (argc == 1)
	{
		printf("Usage of ./fractal:\n\tEither: MJ or other\n");
		exit(EXIT_FAILURE);
	}
	info = newInfo(argc, argv);
	
	
	set_hooks(info);
	// mlx_hook(window, 17, 0, exit_hook, NULL); 
	mlx_loop(info->mlx);
	return (0);
}




// [0] blue
// [1] green
// [2] red
// [3] ??
