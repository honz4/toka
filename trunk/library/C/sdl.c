/***************************************************************
 * Simple Directmedia Layer (SDL) Abstraction Layer
 *
 * This is part of a hybrid library module for Toka. It helps
 * abstract the underlying SDL implementation making basic SDL
 * programming easier.
 ***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


SDL_Surface *screen;
long width, height;

void sdl_setup(long req_width, long req_height)
{
   height = req_height;
   width  = req_width;
   SDL_Init(SDL_INIT_VIDEO);
   screen = SDL_SetVideoMode((int)width, (int)height, 32, SDL_SWSURFACE);
}

void sdl_render()
{
  SDL_UpdateRect(screen, 0, 0, width, height);
}

long sdl_event_type(SDL_Event *event)
{
  return (long)event->type;
}

long sdl_surface_size()
{
  return (long)sizeof(SDL_Surface);
}

long sdl_event_size()
{
  return (long)sizeof(SDL_Event);
}


void sdl_putpixel(long x, long y, long color)
{
  unsigned int *ptr = (unsigned int*)screen->pixels;
  int lineoffset = (int)y * (screen->pitch / 4);
  ptr[lineoffset + x] = (int)color;
}
