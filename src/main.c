#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIDTH 1500
#define HEIGHT 1000

#define KEY_ESQ 53

int exit_hook()
{
	//Clean up??
	exit(EXIT_SUCCESS);
}

int test_expose(){
	printf("TESTING EXPOSE\n");
}


typedef struct s_mouse
{
	int x;
	int y;
	double xx;
	double yy;
} t_mouse;

typedef struct s_info
{
	void *mlx;
	void *window1;
	void *window2;
	void *image1;
	void *image2;
	char *pixel1;
	char *pixel2;
	// void *window3;
	// scaling? moving?
	double horizontal;	
	double vertical;
	//Mouse Pos
	t_mouse mouse;
	//fractal mode
	int mode;
} t_info;

int motion(int x, int y, t_info *info)
{
	char tmp[50];
	sprintf(tmp, "X: %f Y: %f", ((x / (WIDTH / 3.0) - 2)), (y / (HEIGHT / 2.0) - 1));
	// sprintf(tmp, "X: %f Y: %f", x * 1.0, -1 * ((y / (HEIGHT / 2 ) - 1)));
	// sprintf(tmp, "X: %f Y: %f", (x / 500.0) - 1, -1 * (y / HEIGHT / 2) + 1);
	mlx_clear_window(info->mlx, info->window1);
	mlx_string_put(info->mlx, info->window1, 0 , 0, 0xffffff, tmp);
}

int keys(int key)
{
	if (key == KEY_ESQ)
		exit(EXIT_SUCCESS);
	printf("%d\n", key);
}


typedef struct s_vector 
{
	double x;
	double y;
} t_vector;

double vector_distance(t_vector v)
{
	return (v.x * v.x + v.y * v.y);
}
//v.x * v.x is happening twice, getting distance and squaring
t_vector vector_square_i(t_vector v)
{
	return (t_vector){v.x*v.x-v.y*v.y, 2*v.x*v.y};
}

t_vector vector_add(t_vector v, t_vector add)
{
	return (t_vector){v.x + add.x, v.y + add.y};
}

//Distance, squareing, add methods


//pixel ->  -1 to 1 scale convertion
t_vector pixel_to_plane(int x, int y)
{

}



//julia
int julia(int x, int y, t_vector start)
{
	unsigned char itter;
	t_vector z;
	t_vector c;
	double xx;
	double yy;
	c = start;
	itter = 0;
	xx = (x / (WIDTH / 3.0) - 2);
	yy = (y / (HEIGHT / 2.0) - 1);
	z = (t_vector){xx,yy}; 
	while (itter < 255)
	{
		z = vector_add(vector_square_i(z), c); 
		if (vector_distance(z) > 4)
			break;
		itter++;
				// if distance > r == 2 || h == 4; break
	}
	printf("X: %f Y: %f Itter: %d\t", xx, yy, itter);
	return itter;
}

// //draw section function, Line? Quad?
// pthread_create()
// pthread_join()


//mandelbrot
int mandelbrot(int x, int y)
{
	unsigned char itter;
	t_vector z;
	t_vector c;
	double xx;
	double yy;
	z = (t_vector){0,0};
	itter = 0;
	xx = (x / (WIDTH / 3.0) - 2);
	yy = (y / (HEIGHT / 2.0) - 1);
	c = (t_vector){xx,yy}; 
	while (itter < 255)
	{
		z = vector_add(vector_square_i(z), c); 
		if (vector_distance(z) > 4)
			break;
		itter++;
				// if distance > r == 2 || h == 4; break
	}
	printf("X: %f Y: %f Itter: %d\t", xx, yy, itter);
	return itter;
}

//get color pixel
//Does calculation, equaltion is a function pointer set depending on the params
#define POS(x, y, width) ((x) + (y) * (width * 4))	//Fix for efficicy

void drawWindow2(char *tmp)
{
	printf("What's up \n");
	int color;
	for (int y = 0; y < HEIGHT; y++)
	{
		printf("-------  Y  -------%d \n", y);
		//multthread here
		for (int x = 0; x < WIDTH; x++)
		{
			// color = mandelbrot(x, y);
			color = julia(x, y, (t_vector){-0.7, 0.27015});
			// color = 100;	
			tmp[POS(x * 4, y, WIDTH)] = color; 
			tmp[POS(((x * 4) + 1), y, WIDTH)] = color; 
			tmp[POS(((x * 4) + 2), y, WIDTH)] = color; 
			tmp[POS(((x * 4) + 3), y, WIDTH)] = 0; 
		}
		printf("\n");
	}
}
#define other 3
void update(t_info *info)
{
	if (info->mode == other)
	{
		//drawfractal 3
	} else {

	}

	//setPixels
	//clear
	//set cordinates
	//put on screen
	// drawWindow2(tmp);
	// mlx_put_image_to_window(mlx, window1, image, 0, 0);

}


void fillImage(char *tmp, int (*fractal))
{
	int color;

			
}


void set_hooks(t_info *info)
{
	mlx_hook(info->window1, 2, 0, keys, info);
	mlx_hook(info->window1, 12, 0, test_expose, NULL);
	mlx_hook(info->window1, 17, 0, exit_hook, NULL);
	//update mouse location
	mlx_hook(info->window1, 6, 0, motion, info);
}

t_info *newInfo(char *arg)
{
	t_info *info;
	int tmp;

	info = malloc(sizeof(t_info));
	info->mlx = mlx_init();
	if (!strcmp("MJ", arg))
	{
		info->window1 = mlx_new_window(info->mlx, WIDTH, HEIGHT, "Mandelbrot");	
		info->window2 = mlx_new_window(info->mlx, WIDTH, HEIGHT, "Julia");	
		info->image2 = mlx_new_image(info->mlx, WIDTH, HEIGHT);
		info->pixel2 = mlx_get_data_addr(info->image2, &tmp, &tmp, &tmp);	//Can keep it as null?
	} else
	{
		info->window1 = mlx_new_window(info->mlx, WIDTH, HEIGHT, "other");	
	}
	info->image1 = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->pixel1 = mlx_get_data_addr(info->image1, &tmp, &tmp, &tmp);
	



	return (info);
}



int main(int argc, char **argv)
{
	t_info *info;

	if (argc == 1)
	{
		printf("Usage of ./fractal:\n\tEither: MJ or other\n");
		exit(EXIT_FAILURE);
	} else if (argc == 2) 
	{
		if ((strcmp("MJ", argv[1]) && strcmp("other", argv[1])))
		{
			printf("Usage of ./fractal:\n\tEither: MJ or other\n");
			exit(EXIT_FAILURE);	
		}
	}
	
	info = newInfo(argv[1]);
	

	
	
	// 
	set_hooks(NULL);
	// mlx_hook(window, 17, 0, exit_hook, NULL); 
	mlx_loop(info->mlx);
	return (0);
}




// [0] blue
// [1] green
// [2] red
// [3] ??
