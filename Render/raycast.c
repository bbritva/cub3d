/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:32:27 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/28 19:49:33 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		draw_view2(t_win *win, float angle)
{
	{
		int x;
		double posX = win->params->player->pos_x;
		double posY = win->params->player->pos_y;
		// position
		double dirX = -1;
		double dirY = 0; //initial direction vector
		double planeX = 0;
		double planeY = 0.66; //the 2d raycaster version of camera plane

		double time = 0; //time of current frame
		double oldTime = 0; //time of previous frame

		for(int x = 0; x < win->params->res_h; x++)
		{
			//calculate ray position and direction
				double cameraX = 2 * x / (double)win->params->res_h - 1; //x-coordinate in camera space
				double rayDirX = dirX + planeX * cameraX;
				double rayDirY = dirY + planeY * cameraX;
				//which box of the map we're in
				int mapX = (int)(posX);
				int mapY = (int)(posY);

				//length of ray from current position to next x or y-side
				double sideDistX;
				double sideDistY;

				//length of ray from one x or y-side to next x or y-side
				double deltaDistX = fabs(1 / rayDirX);
				double deltaDistY = fabs(1 / rayDirY);
				double perpWallDist;

				//what direction to step in x or y-direction (either +1 or -1)
				int stepX;
				int stepY;

				int hit = 0; //was there a wall hit?
				int side; //was a NS or a EW wall hit?
				//calculate step and initial sideDist
				if(rayDirX < 0)
				{
					stepX = -1;
					sideDistX = (posX - mapX) * deltaDistX;
				}
				else
				{
					stepX = 1;
					sideDistX = (mapX + 1.0 - posX) * deltaDistX;
				}
				if(rayDirY < 0)
				{
					stepY = -1;
					sideDistY = (posY - mapY) * deltaDistY;
				}
				else
				{
					stepY = 1;
					sideDistY = (mapY + 1.0 - posY) * deltaDistY;
				}
				//perform DDA
				while (hit == 0)
				{
					//jump to next map square, OR in x-direction, OR in y-direction
					if(sideDistX < sideDistY)
					{
						sideDistX += deltaDistX;
						mapX += stepX;
						side = 0;
					}
					else
					{
						sideDistY += deltaDistY;
						mapY += stepY;
						side = 1;
					}
					//Check if ray has hit a wall
					if(win->params->map[mapX][mapY] > 0)
						hit = 1;
				}
				//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
				if(side == 0)
					perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
				else
					perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

				//Calculate height of line to draw on screen
				int lineHeight = (int)(win->params->res_v / perpWallDist);

				//calculate lowest and highest pixel to fill in current stripe
				int drawStart = -lineHeight / 2 + win->params->res_v / 2;
				if(drawStart < 0)drawStart = 0;
				int drawEnd = lineHeight / 2 + win->params->res_v / 2;
				if (drawEnd >= win->params->res_v)
					drawEnd = win->params->res_v - 1;

				//choose wall color
//				ColorRGB color;
//				switch(worldMap[mapX][mapY])
//				{
//					case 1:  color = RGB_Red;    break; //red
//					case 2:  color = RGB_Green;  break; //green
//					case 3:  color = RGB_Blue;   break; //blue
//					case 4:  color = RGB_White;  break; //white
//					default: color = RGB_Yellow; break; //yellow
//				}

				//give x and y sides different brightness
//				if(side == 1)
//					{
//						color = color / 2;
//					}

				//draw the pixels of the stripe as a vertical line
				draw_line(x, drawStart, drawEnd, color);
			}
			//timing for input and FPS counter
			oldTime = time;
			time = getTicks();
			double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
			print(1.0 / frameTime); //FPS counter
			redraw();
			cls();

			//speed modifiers
			double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
			double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
			readKeys();
			//move forward if no wall in front of you
			if(keyDown(SDLK_UP))
			{
				if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
				if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
			}
			//move backwards if no wall behind you
			if(keyDown(SDLK_DOWN))
			{
				if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
				if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
			}
			//rotate to the right
			if(keyDown(SDLK_RIGHT))
			{
				//both camera direction and camera plane must be rotated
				double oldDirX = dirX;
				dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
				dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
				double oldPlaneX = planeX;
				planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
				planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
			}
			//rotate to the left
			if(keyDown(SDLK_LEFT))
			{
				//both camera direction and camera plane must be rotated
				double oldDirX = dirX;
				dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
				dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
				double oldPlaneX = planeX;
				planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
				planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
			}
		}
	}
}