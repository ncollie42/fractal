#ifndef FRACTAL_H
#define FRACTAL_H
#define WIDTH (1500 / 2)
#define HEIGHT (1000 / 2)
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#define KEY_ESQ 53
#define WIN_MAX 5

enum fractals
{
	julia,
	mandelbrot
};

typedef struct s_vector 
{
	double x;
	double y;
} t_vector;

typedef struct s_mouse {
	t_vector actual;
	t_vector updated;
} t_mouse;

typedef struct s_window {
	enum fractals type;
	void *mlx;
	void *window;
	void *image;
	char *pixel;
	int (*func)();
	//Color info
	t_mouse mouse;
	//Precalculated struct, ->
} v_window;

/*
	PreCalculate
	W && height dimentions
	width / 3 && height / 2 for pixel->plane
	POS calc
	Vector math?
*/ 

typedef struct s_info
{
	void *mlx;
	v_window **windows; //if julia and madelbrot, 
	// scaling? moving?
} t_info;


// Fractal equations
int juliaFunc(int x, int y, t_vector start);
int mandelbrotFunc(int x, int y);

//ui
void ui(v_window *window);

void update(v_window *window);

// Hook functions
void set_hooks(t_info *info);
int keys(int key);

#endif