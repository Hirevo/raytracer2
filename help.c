/*
** help.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun May 28 19:10:47 2017 Nicolas Polomack
** Last update Sun May 28 19:19:02 2017 Nicolas Polomack
*/

#include "my.h"

static const char	*help =
  "Usage: raytracer2 [-uSch] [--cluster=\"ip\"]\
 [--res=width,height] [--ssaa=nb] [--soft=nb]\n\
       		  [--fov=nb] [--dof=nb] [--tesla=nb] \
[--depth=nb] [--stereo]\
 scene_file\n\nRenders the scene for the provided scene_file.\n\n  -u\
\n	Live updates the rendered part of the image as the laoding\
 progresses.\n  -S\n	Enables stereoscopic anaglyph 3D rendering.\
 This flag may disable \
some effects such as depth of field or anti-aliasing.\n  -c\n\
	Enable cluster mode as the master server, clients can then connect\
 and start computing parts of the image\n  -h\n	Displays this help message\
\n\n  --cluster=\"ip\"\n	ip: an ip address (i.e.: 192.168.1.11)\n\
	Enable cluster mode as a client and tries to connect to the \
specified ip address\n\n  --res=width,height\n\
	Sets the resolution of the rendered image to the one specified\n\n\
  --ssaa=nb\n	Enables SSAA (SuperSampled Anti-Aliasing) with the specified \
resolution multiplier\n\n  --soft=nb\n	Enables soft shadows with \
the specified number of samples per shadow \
computation\n\n  --fov=nb\n	Sets the fov to the specified value\n\n\
  --dof=nb\n	Enables depth-of-field with the specified number of \
samples per pixel\n\n  --tesla=nb\n	Generates an image with \
the specified value as the size of the \
rendered pixels.\n	The image is then re-rendered at a higher \
level of detail, until\
 the tesselation level equals 1.\n\n  --depth=nb\n	Sets the limit \
for how much reflection and refraction can a single\
 ray perform to the specified value.\n\n  --stereo\n	The effect is \
the same as the \"-S\" flag. Enables stereoscopic\
 anaglyph 3D rendering.";

int	disp_guide()
{
  my_printf("%s\n", help);
  return (0);
}
