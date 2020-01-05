#include "fractal.h"



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



//julia
int juliaFunc(int x, int y, t_vector start)
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
	// printf("X: %f Y: %f Itter: %d\t", xx, yy, itter);
	return itter;
}

// //draw section function, Line? Quad?
// pthread_create()
// pthread_join()


//mandelbrot
int mandelbrotFunc(int x, int y)
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
	// printf("X: %f Y: %f Itter: %d\t", xx, yy, itter);
	return itter;
}
