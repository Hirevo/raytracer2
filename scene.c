/*
** scene.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Apr  4 15:04:25 2017 Nicolas Polomack
** Last update Wed Apr  5 13:01:56 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "my.h"
#include "bmp.h"
#include "raytracer.h"
#include "sfcaster.h"

void	init_reflect(t_params *params)
{
  params->config.fov = 80;
  params->start.x = -150;
  params->start.y = 0;
  params->start.z = 20;
  params->r.x = 0;
  params->r.y = 0;
  params->r.z = 0;
  params->nb_objs = 5;
  params->objs = malloc(sizeof(t_obj) * 5);
  my_memset((char *)params->objs, 0, sizeof(t_obj) * 5);
  params->objs[0].type = 10;
  params->objs[0].pos.x = -10;
  params->objs[0].pos.y = 55;
  params->objs[0].pos.z = 20;
  params->objs[0].r.x = 0;
  params->objs[0].r.y = -90;
  params->objs[0].r.z = 60;
  params->objs[0].rad = 25;
  params->objs[0].p1.x = 30;
  params->objs[0].p2.y = 30;
  params->objs[0].p2.x = 0;
  params->objs[0].p1.y = 0;
  params->objs[0].rad = 10;
  params->objs[0].reflect = 0.5;
  //params->objs[0].spec_coef = 50;
  params->objs[0].col = get_sfcolor(255, 0, 0, 255);
  params->objs[1].type = 0;
  params->objs[1].pos.x = -10;
  params->objs[1].pos.y = 0;
  params->objs[1].pos.z = 20;
  params->objs[1].r.x = 0;
  params->objs[1].r.y = 0;
  params->objs[1].r.z = -120;
  params->objs[1].rad = 25;
  params->objs[1].reflect = 0.3;
  params->objs[1].spec_coef = 50;
  params->objs[1].buffer = load_bmp("resources/EtoileNoire.bmp", NULL, NULL);
  params->objs[1].col = get_sfcolor(255, 0, 0, 255);
  params->objs[2].type = 0;
  params->objs[2].pos.x = -10;
  params->objs[2].pos.y = -55;
  params->objs[2].pos.z = 20;
  params->objs[2].r.x = 0;
  params->objs[2].r.y = 0;
  params->objs[2].r.z = 0;
  params->objs[2].rad = 25;
  params->objs[2].reflect = 0.3;
  params->objs[2].spec_coef = 50;
  params->objs[2].col = get_sfcolor(0, 0, 255, 255);
  params->objs[3].type = 1;
  params->objs[3].pos.x = 30;
  params->objs[3].pos.y = 0;
  params->objs[3].pos.z = 0;
  params->objs[3].r.x = 0;
  params->objs[3].r.y = -90;
  params->objs[3].r.z = 0;
  params->objs[3].rad = 20;
  params->objs[3].aper = 20;
  params->objs[3].height = 50;
  params->objs[3].reflect = 0;
  params->objs[3].spec_coef = 20;
  params->objs[3].col = get_sfcolor(100, 100, 100, 255);
  params->objs[4].type = 1;
  params->objs[4].pos.x = 0;
  params->objs[4].pos.y = 0;
  params->objs[4].pos.z = -25;
  params->objs[4].r.x = 0;
  params->objs[4].r.y = 0;
  params->objs[4].r.z = 0;
  params->objs[4].reflect = 0;
  params->objs[4].spec_coef = 20;
  params->objs[4].col = get_sfcolor(100, 100, 100, 255);
  params->nb_lights = 1;
  params->lights = malloc(sizeof(t_light) * 1);
  params->lights[0].pos.x = -150;
  params->lights[0].pos.y = 0;
  params->lights[0].pos.z = 100;
  params->config.ambient = 0;
  params->config.reflect_depth = 3;
  params->config.depth_rays = 1;
  params->config.ssaa = 1;
}

void	init_test(t_params *params)
{
  params->config.fov = 70;
  params->start.x = -400;
  params->start.y = 0;
  params->start.z = 0;
  params->r.x = 0;
  params->r.y = 0;
  params->r.z = 0;
  params->nb_objs = 2;
  params->objs = malloc(sizeof(t_obj) * 2);
  my_memset((char *)params->objs, 0, sizeof(t_obj) * 2);
  params->objs[0].type = 10;
  params->objs[0].pos.x = 0;
  params->objs[0].pos.y = 0;
  params->objs[0].pos.z = 0;
  params->objs[0].r.x = 0;
  params->objs[0].r.y = 45;
  params->objs[0].r.z = 45;
  params->objs[0].rad = 20;
  params->objs[0].reflect = 0;
  params->objs[0].buffer = NULL;
  //params->objs[0].spec_coef = 50;
  params->objs[0].col = get_sfcolor(255, 0, 0, 255);
  params->objs[1].type = 0;
  params->objs[1].pos.x = 0;
  params->objs[1].pos.y = 0;
  params->objs[1].pos.z = 40;
  params->objs[1].r.x = 0;
  params->objs[1].r.y = 0;
  params->objs[1].r.z = 0;
  params->objs[1].rad = 15;
  params->objs[1].reflect = 0;
  params->objs[1].buffer = NULL;
  params->objs[1].spec_coef = 50;
  params->objs[1].col = get_sfcolor(255, 0, 0, 255);
  params->nb_lights = 1;
  params->lights = malloc(sizeof(t_light) * 1);
  params->lights[0].pos.x = -100;
  params->lights[0].pos.y = 200;
  params->lights[0].pos.z = 0;
  params->config.ambient = 0.1;
  params->config.reflect_depth = 0;
  params->config.ssaa = 1;
  params->config.depth_rays = 1;
}

void	init_room(t_params *params)
{
  params->start.x = -400;
  params->start.y = -20;
  params->start.z = 40;
  params->r.x = 0;
  params->r.y = 0;
  params->r.z = 0;
  params->nb_objs = 12;
  params->objs = malloc(sizeof(t_obj) * 12);
  my_memset((char *)params->objs, 0, sizeof(t_obj) * 12);
  params->objs[0].type = 0;
  params->objs[0].pos.x = -75;
  params->objs[0].pos.y = -20;
  params->objs[0].pos.z = 75;
  params->objs[0].r.x = 0;
  params->objs[0].r.y = 0;
  params->objs[0].r.z = 0;
  params->objs[0].rad = 50;
  params->objs[0].reflect = 0.5;
  params->objs[0].spec_coef = 50;
  params->objs[0].col = get_sfcolor(192, 57, 43, 255);
  params->objs[1].type = 1;
  params->objs[1].pos.x = 0;
  params->objs[1].pos.y = 0;
  params->objs[1].pos.z = -25;
  params->objs[1].r.x = 0;
  params->objs[1].r.y = 0;
  params->objs[1].r.z = 0;
  params->objs[1].reflect = 0.5;
  params->objs[1].col = get_sfcolor(50, 50, 50, 255);
  params->objs[2].type = 1;
  params->objs[2].pos.x = 200;
  params->objs[2].pos.y = 0;
  params->objs[2].pos.z = -25;
  params->objs[2].r.x = 0;
  params->objs[2].r.y = 90;
  params->objs[2].r.z = 0;
  params->objs[2].reflect = 0.5;
  params->objs[2].col = get_sfcolor(50, 50, 50, 255);
  params->objs[3].type = 1;
  params->objs[3].pos.x = -450;
  params->objs[3].pos.y = 0;
  params->objs[3].pos.z = -25;
  params->objs[3].r.x = 0;
  params->objs[3].r.y = -90;
  params->objs[3].r.z = 0;
  params->objs[3].reflect = 0.5;
  params->objs[3].col = get_sfcolor(50, 50, 50, 255);
  params->objs[4].type = 1;
  params->objs[4].pos.x = 0;
  params->objs[4].pos.y = 120;
  params->objs[4].pos.z = 0;
  params->objs[4].r.x = 90;
  params->objs[4].r.y = 0;
  params->objs[4].r.z = 0;
  params->objs[4].reflect = 0.5;
  params->objs[4].col = get_sfcolor(50, 50, 50, 255);
  params->objs[5].type = 1;
  params->objs[5].pos.x = 0;
  params->objs[5].pos.y = -220;
  params->objs[5].pos.z = 0;
  params->objs[5].r.x = -90;
  params->objs[5].r.y = 0;
  params->objs[5].r.z = 0;
  params->objs[5].reflect = 0.5;
  params->objs[5].col = get_sfcolor(50, 50, 50, 255);
  params->objs[6].type = 1;
  params->objs[6].pos.x = 0;
  params->objs[6].pos.y = 0;
  params->objs[6].pos.z = 175;
  params->objs[6].r.x = 180;
  params->objs[6].r.y = 0;
  params->objs[6].r.z = 0;
  params->objs[6].reflect = 0.5;
  params->objs[6].col = get_sfcolor(50, 50, 50, 255);
  params->objs[7].type = 0;
  params->objs[7].pos.x = -100;
  params->objs[7].pos.y = 50;
  params->objs[7].pos.z = 30;
  params->objs[7].r.x = 0;
  params->objs[7].r.y = 0;
  params->objs[7].r.z = 0;
  params->objs[7].rad = 25;
  params->objs[7].reflect = 0.5;
  params->objs[7].spec_coef = 50;
  params->objs[7].col = get_sfcolor(120, 120, 120, 255);
  params->objs[8].type = 10;
  params->objs[8].pos.x = -175;
  params->objs[8].pos.y = -75;
  params->objs[8].pos.z = 0;
  params->objs[8].r.x = 45;
  params->objs[8].r.y = 0;
  params->objs[8].r.z = 45;
  params->objs[8].rad = 10;
  params->objs[8].height = 50;
  params->objs[8].reflect = 0.3;
  params->objs[8].col = get_sfcolor(41, 128, 185, 255);
  params->objs[9].type = 2;
  params->objs[9].pos.x = -50;
  params->objs[9].pos.y = -75;
  params->objs[9].pos.z = 0;
  params->objs[9].r.x = 0;
  params->objs[9].r.y = 90;
  params->objs[9].r.z = 90;
  params->objs[9].rad = 10;
  params->objs[9].reflect = 0;
  params->objs[9].col = get_sfcolor(62, 80, 50, 255);
  params->objs[10].type = 6;
  params->objs[10].pos.x = -50;
  params->objs[10].pos.y = 75;
  params->objs[10].pos.z = 150;
  params->objs[10].r.x = 0;
  params->objs[10].r.y = 0;
  params->objs[10].r.z = 0;
  params->objs[10].aper = 25;
  params->objs[10].height = 50;
  params->objs[10].col = get_sfcolor(39, 174, 96, 255);
  params->objs[11].type = 4;
  params->objs[11].pos.x = 0;
  params->objs[11].pos.y = -170;
  params->objs[11].pos.z = 50;
  params->objs[11].r.x = 25;
  params->objs[11].r.y = -20;
  params->objs[11].r.z = 0;
  params->objs[11].aper = 25;
  params->objs[11].reflect = 0;
  params->objs[11].col = get_sfcolor(39, 174, 96, 255);
  params->nb_lights = 1;
  params->lights = malloc(sizeof(t_light) * 1);
  params->lights[0].pos.x = -200;
  params->lights[0].pos.y = -40;
  params->lights[0].pos.z = 150;
  params->config.ambient = 0.1;
  params->config.reflect_depth = 3;
  params->config.fov = 70;
  params->config.depth_rays = 1;
  params->config.ssaa = 1;
}
