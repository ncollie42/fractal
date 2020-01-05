#include "fractal.h"


int exit_hook()
{
	//Clean up??
	exit(EXIT_SUCCESS);
}

int test_expose(v_window *window){
	printf("TESTING EXPOSE\n");
	
	update(window);
	return 0;
}

//pixel ->  -1 to 1 scale convertion
t_vector pixel_to_plane(int x, int y)
{
	t_vector tmp;

	tmp.x = (x / (WIDTH / 3.0) - 2);
	tmp.y = (y / (HEIGHT / 2.0) - 1);
	// ((x / (WIDTH / 3.0) - 2)), (y / (HEIGHT / 2.0) - 1)	
	return tmp;
}


//updates X Y and calls update
int motion(int x, int y, v_window *window)
{
	window->mouse.actual = (t_vector){x, y};
	window->mouse.updated = pixel_to_plane(x, y);
	
	update(window);
	return 0;
}

//special, Update julia *, hook looks at man.

void set_hooks(t_info *info)
{
	int ii;

	ii = -1;
	while(++ii < WIN_MAX)
	{
		if (info->windows[ii])
		{
			mlx_hook(info->windows[ii]->window, 2, 0, keys, info);
			mlx_hook(info->windows[ii]->window, 12, 0, test_expose, info->windows[ii]);
			mlx_hook(info->windows[ii]->window, 17, 0, exit_hook, NULL);
			//update mouse location
			mlx_hook(info->windows[ii]->window, 6, 0, motion, info->windows[ii]);
						//          ^ Look at this window         ^ update this one
		}
	}
	if (info->windows[julia] && info->windows[mandelbrot])
	{
		mlx_hook(info->windows[mandelbrot]->window, 6, 0, motion, info->windows[julia]);
	}
	//Loop for every window and set hook - if julia and man then set motion of man for julia
	//if just man dont change? idk
}


int keys(int key)
{
	if (key == KEY_ESQ)
		exit(EXIT_SUCCESS);
	printf("%d\n", key);
	return 0;
}
