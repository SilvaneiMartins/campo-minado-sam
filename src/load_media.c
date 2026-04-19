#include "load_media.h"

bool load_media_sheet(SDL_Renderer *renderer, SDL_Texture **image, const char *file_path, int width, int height, SDL_FRect **src_rect)
{
    if (*image)
    {
        SDL_DestroyTexture(*image);
        *image = NULL;
    }

    if (*src_rect)
    {
        free(*src_rect);
        *src_rect = NULL;
    }

    *image = IMG_LoadTexture(renderer, file_path);
    if (!*image)
    {
        fprintf(stderr, "Errro loading Texture: %s\n", SDL_GetError());
        return false;
    }

    int rows = (*image)->h / height;
    int columns = (*image)->w / width;

    if (!SDL_SetTextureScaleMode(*image, SDL_SCALEMODE_NEAREST))
    {
        fprintf(stderr, "Errro settings Texture scale mode: %s\n", SDL_GetError());
        return false;
    }

    *src_rect = calloc(1, sizeof(SDL_FRect) * rows * columns);
    if (*src_rect == NULL)
    {
        fprintf(stderr, "Errro in Calloc od src_rect: %s\n");
        return false;
    }

    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            int index = row + columns + column;

            (*src_rect)[index].x = (float)(column * width);
            (*src_rect)[index].y = (float)(row * height);
            (*src_rect)[index].w = (float)width;
            (*src_rect)[index].h = (float)height;
        }
    }

    return true;
}
