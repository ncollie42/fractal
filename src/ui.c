#include "fractal.h"

void ui(v_window *window)
{
	// if (enabled)
	// {
		char tmp[50];
		sprintf(tmp, "X: %f Y: %f", window->mouse.updated.x, window->mouse.updated.y);
		// mlx_clear_window(window->mlx, window->window);
		mlx_string_put(window->mlx, window->window, 0 , 0, 0xffffff, tmp);
		
		// mlx_string_put(info->mlx, info->window1, 0 , 0, 0xffffff, tmp);
		// Same for color ^^
		// mlx_string_put(window->mlx, window->window, 0 , 0, 0xffffff, "Test UI Hud");
	// }
}