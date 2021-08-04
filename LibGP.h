/**
 *	\file         LibGP.h
 *	\brief        Graphics primitives library implementation.
 *	\author       Roman Garanin
 * 	\mail         r_o.m.a_n@mail.ru
 *
 *	\abbreviations:
 * 	\prefixes:
 *              GP_ - Graphics Primitives;
 *              p - Pointer to function;
 *
 */

#ifndef LIB_GP_H
#define LIB_GP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Fonts/LibGPFonts.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/**
 *	\brief Macro converts RGB data to RGB 565 format and save it in uint16_t.
 * 	\param R - Red color.
 * 	\param G - Green color.
 * 	\param B - Blue color.
 *	\return - no.
 */
#define RGB565(R, G, B) (uint16_t)((((uint16_t)R & 0xF8) << 8) |	\
                                   (((uint16_t)G & 0xFC) << 3) |	\
                                            ((uint16_t)B >> 3))

/**
 *	\brief  Colors.
 */
#define WHITE RGB565(255, 255, 255)         /**< White */
#define BLACK RGB565(0, 0, 0)               /**< Black*/
#define DARK_GRAY RGB565(15, 15, 15)        /**< Dark gray */
#define YELLOW RGB565(255, 255, 0)          /**< Yellow */
#define RED RGB565(255, 0, 0)               /**< Red */
#define GREEN RGB565(60, 255, 0)            /**< Green */
#define LIGHT_BLUE RGB565(161, 162, 172)    /**< Light blue*/
#define LIGHT_GREY RGB565(170, 170, 170)    /**< Light gray*/
#define ORANGE RGB565(255, 215, 0)          /**< Orange*/
#define GRAY RGB565(102, 102, 102)          /**< Gray */
#define BLUE RGB565(29, 21, 255)            /**< Blue */

/**
 *	\brief Function clears video buffer.
 *	\param Buffer - A pointer to video buffer to clear.
 *	\param w - Width of screen.
 *	\param h - high of screen.
 *	\return - no.
 */
void GP_ClearBuffer(uint16_t *Buffer, uint16_t w, uint16_t h);

/**
 *	\brief Function rotates an image in video buffer.
 * 	\return - no.
 */
void GP_RotateScreen();

/**
 *	\brief Function fills a square in video buffer.
 *	\params - x1, y1, x2, y2 - a coordinates of square.
 *	\param - color - color of filling.
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 * 	\return - no.
 */
void GP_FILL(uint16_t x1,
             uint16_t y1,
             uint16_t x2,
             uint16_t y2,
             uint16_t color,
             uint16_t *Buffer,
             uint32_t w,
             uint32_t h);

/**
 *	\brief function draws a horizontal line .
 *	\params - x, y - a coordinates of start of the horizontal line.
 *	\param  - lenght of the horizontal line.
 *	\param - color - color of the horizontal line.
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void GP_SetLineH(uint16_t x,
                 uint16_t y,
                 uint16_t length,
                 uint16_t color,
                 uint16_t *Buffer,
                 uint32_t w,
                 uint32_t h);

/**
 *	\brief function draws a vertical line.
 *	\param - x, y - a coordinates of start of the vertical line.
 *	\param - lenght of the vertical line.
 *	\param - color - color of the vertical line.
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void GP_SetLineV(uint16_t x,
                 uint16_t y,
                 uint16_t length,
                 uint16_t color,
                 uint16_t *Buffer,
                 uint32_t w,
                 uint32_t h);

/**
 *	\brief function draws a simple cross .
 *	\param - x, y - a coordinates of the cross.
 *	\param - width - width of the cross.
 *	\param - color - color of the cross.
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void GP_SetCross(uint16_t x,
                 uint16_t y,
                 uint16_t width,
                 uint16_t color,
                 uint16_t *Buffer,
                 uint32_t w,
                 uint32_t h);

/**
 *	\brief - function draws a square.
 *	\param - x, y - a coordinates of center of the Square.
 *	\param - width - width of the square.
 * 	\param - height - height of the square.
 *	\param - color - color of the square.
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void GP_SetSquare(uint16_t x,
                  uint16_t y,
                  uint16_t width,
                  uint16_t height,
                  uint16_t color,
                  uint16_t *Buffer,
                  uint32_t w,
                  uint32_t h);

/**
 *	\brief - function draws a dotted horizontal line.
 *	\param - x, y - a coordinates of start of the dotted horiszontal line.
 *	\param - length - length of the dotted horizontal line.
 * 	\param - dot_length - lenght of dotts.
 * 	\param - space_length - length of space between dotts.
 *	\param - color - color of the horizontal dotted line.
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void GP_SetLineDottedH(uint16_t x,
                       uint16_t y,
                       uint16_t length,
                       uint16_t dot_length,
                       uint16_t space_length,
                       uint16_t color,
                       uint16_t *Buffer,
                       uint32_t w,
                       uint32_t h);

/**
 *	\brief - function draws a dotted vertical line.
 *	\param - x, y - a coordinates of start of the dotted vertical line.
 *	\param - length - length of the dotted vertical line.
 * 	\param - dot_length - lenght of the dotts.
 * 	\param - space_length - length of space between dotts.
 *	\param - color - color of the dotted vertical line.
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void GP_SetLineDotedV(uint16_t x,
                      uint16_t y,
                      uint16_t length,
                      uint16_t dot_length,
                      uint16_t space_length,
                      uint16_t color,
                      uint16_t *Buffer,
                      uint32_t w,
                      uint32_t h);

/**
 *	\brief function draws a Bresenham line.
 *	\param  - x1, y1, x2, y2 - a coordinates of the Bresenham line.
 *	\param - color - color of the Bresenham line.
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void GP_SetBresenhamLine(uint16_t x1,
                         uint16_t y1,
                         uint16_t x2,
                         uint16_t y2,
                         uint16_t color,
                         uint16_t *Buffer,
                         uint32_t w,
                         uint32_t h);

/**
 *	\brief function draws Bresenham circle.
 *	\param - x0, y0 - a coordinates of center of the Bresenham circle.
 *	\param - r - radius of the Bresenham circle.
 *	\param - color - color of the Bresenham circle.
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void GP_SetBresenhamCircle(uint16_t x0,
                           uint16_t y0,
                           uint16_t r,
                           uint16_t color,
                           uint16_t *Buffer,
                           uint32_t w,
                           uint32_t h);

/**
 *	\brief function draws a rouned rectangular.
 *	\param - x0, y0 - a coordinates of the rounded rectangular.
 *	\param - width and heigth - witdth and heigth of the rounded rectangular.
 * 	\param - r - rounding radius of the rectangular.
 *	\param - color - color of the rounded rectangular.
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void GP_RoundedRect(uint16_t x0,
                    uint16_t y0,
                    int16_t width,
                    int16_t heigth,
                    uint16_t r,
                    uint16_t color,
                    uint16_t *Buffer,
                    uint32_t w,
                    uint32_t h);

/**
 *	\brief function draws a filled Bresenham circle.
 *	\param - x0, y0 - a coordinates of the Bresenham filled circle.
 *	\param - r - radius of the Bresenham filled circle.
 *	\param - color - color of the Bresenham filled circle.
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void GP_DrawFilledCircle(int16_t x0,
                         int16_t y0,
                         int16_t r,
                         uint16_t color,
                         uint16_t *Buffer,
                         uint32_t w,
                         uint32_t h);

/**
 *	\brief function draws rounded fill.
 *	\param - x0, y0 - a coordinates of the rounded fill.
 *	\param - width and heigth - witdth and heigth of the rounded fill.
 * 	\param - r - radius of roundings of the rounded fill.
 *	\param - color - color of the rounded fill.
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void GP_DrawRoundedFill(int16_t x0,
                        int16_t y0,
                        int16_t width,
                        int16_t high,
                        int16_t r,
                        uint16_t color,
                        uint16_t *Buffer,
                        uint32_t w,
                        uint32_t h);

/**
 *	\brief - function drwaws arc. (not implemented)
 *	\param - x0, y0 - a coordinates of arc.
 *	\param - a1, a2 - start and end angle of arc.
 * 	\param - r - radius of arc.
 *	\param - color - color of square.
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void GP_SetArc(uint16_t x,
               uint16_t y,
               uint16_t a1,
               uint16_t a2,
               uint16_t r,
               uint16_t color,
               uint16_t *Buffer,
               uint32_t w,
               uint32_t h);

#define NORTH 1
#define SOUTH 2
#define WEST 3
#define EAST 4

#define ARROW_NORTH 5
#define ARROW_SOUTH 6
#define ARROW_WEST 7
#define ARROW_EAST 8

#define TRIANGLE_NORTH 9
#define TRIANGLE_SOUTH 10
#define TRIANGLE_WEST 11
#define TRIANGLE_EAST 12

/**
 *	\brief  - function draws a simple triangle.
 *	\param  - .
 *	\param  - .
 *	\param  - .
 *	\return - no.
 */
void GP_PutTriangle(uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t heigth,
    uint8_t side,
    uint16_t color,
    uint16_t *Buffer,
    uint32_t w,
    uint32_t h);

/**
 *	\brief - function draws a simple arrow.
 *	\param  - .
 *	\param  - .
 *	\param - color - color of .
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void GP_PutArrow(uint16_t x,
                 uint16_t y,
                 uint16_t width,
                 uint16_t heigth,
                 uint8_t side,
                 uint16_t color,
                 uint16_t *Buffer,
                 uint32_t w,
                 uint32_t h);

/**
 *	\brief function.
 *	\param  - .
 *	\param  - .
 *	\param  - .
 *	\return - no.
 */
void GP_FillArea(uint16_t x,
                 uint16_t y,
                 uint16_t heigth,
                 uint16_t width,
                 uint16_t color,
                 uint16_t border_color,
                 uint16_t *Buffer,
                 uint32_t w,
                 uint32_t h);

/**
 *	\brief function.
 *	\param  - .
 *	\param  - .
 *	\param  - .
 *	\return - no.
 */
void GP_PutChar(uint16_t x,
    uint16_t y,
    uint16_t color,
    const uint8_t Ch,
    const FONT *f,
    uint16_t *Buffer,
    uint32_t w,
    uint32_t h,
    unsigned cbc);

/**
 *	\brief - function prints a string.
 *	\param  - .
 *	\param  - .
 *	\param  - .
 *	\return - no.
 */
void GP_PutString(uint16_t x,
                  uint16_t y,
                  uint16_t color,
                  const uint8_t *String,
                  const FONT *f,
                  uint16_t *Buffer,
                  uint32_t w,
                  uint32_t h,
                  unsigned cbc);

/**
 *	\brief function prints string around a center.
 *	\param  - .
 *	\param  - .
 *	\param  - .
 *	\return - no.
 */
void GP_PutStringInTheCenter(uint16_t x,
                             uint16_t y,
                             uint16_t color,
                             const uint8_t *String,
                             const FONT *f,
                             uint16_t *Buffer,
                             uint32_t w,
                             uint32_t h,
                             unsigned cbc);

/**
 *	\brief function draws a bitmaps.
 *	\param  - .
 *	\param  - .
 *	\param - color - color of .
 *	\param - *Buffer - a pointer to a video buffer.
 *	\params - w, h width and height of the video buffer.
 *	\return - no.
 */
void BMP_DrawTransp(uint16_t x,
                    uint16_t y,
                    uint8_t *pbmp,
                    uint16_t color,
                    uint16_t *Buffer,
                    uint32_t w,
                    uint32_t h);

#ifdef __cplusplus
}
#endif
#endif
