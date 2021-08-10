/**
 *	\file         LibGP.c
 *	\brief        Graphics primitives library implementation.
 *	\author       Roman Garanin
 * 	\mail         r_o.m.a_n@mail.ru
 *
 *
 */

#include "LibGP.h"

#define LIB_GP_PRINT_DEBUG
#ifdef LIB_GP_PRINT_DEBUG
#define DEBUG_PRINT(...); printf(__VA_ARGS__);
#else
#define DEBUG_PRINT(...);
#endif


void GP_ClearBuffer(uint16_t *Buffer,
                    uint16_t w,
                    uint16_t h)
{
  for (int i = 0; i < w * h; i++)
  {
    *Buffer = 0x0;
    Buffer++;
  }
}

void GP_SetPixelNormal(uint16_t x,
                       uint16_t y,
                       uint16_t color,
                       uint16_t *Buffer,
                       uint32_t w,
                       uint32_t h)
{
  Buffer += (x + w * (y));
  *Buffer = color;
}

void GP_SetPixelRotate(uint16_t x,
                       uint16_t y,
                       uint16_t color,
                       uint16_t *Buffer,
                       uint32_t w,
                       uint32_t h)
{
  Buffer += (w - x + w * (h - y));
  *Buffer = color;
}

static void (*pGP_SetPixel)(uint16_t x,
                            uint16_t y,
                            uint16_t color,
                            uint16_t *Buffer,
                            uint32_t w,
                            uint32_t h) = GP_SetPixelNormal;

uint16_t GP_GetColorNormal(uint16_t x,
                           uint16_t y,
                           uint16_t *Buffer,
                           uint32_t w,
                           uint32_t h)
{
  Buffer += (x + w * (y));
  return *Buffer;
}

uint16_t GP_GetColorRotate(uint16_t x,
                           uint16_t y,
                           uint16_t *Buffer,
                           uint32_t w,
                           uint32_t h)
{
  Buffer += (800 - x + w * (600 - y));
  return *Buffer;
}

static uint16_t (*pGP_GetColor)(uint16_t x,
                                uint16_t y,
                                uint16_t *Buffer,
                                uint32_t w,
                                uint32_t h) = GP_GetColorNormal;

void GP_RotateScreen()
{
  if (pGP_SetPixel == GP_SetPixelNormal){
    pGP_SetPixel = GP_SetPixelRotate;
    pGP_GetColor = GP_GetColorRotate;
  } else {
    pGP_SetPixel = GP_SetPixelNormal;
    pGP_GetColor = GP_GetColorNormal;
  }
}

void GP_FILL(uint16_t x1,
             uint16_t y1,
             uint16_t x2,
             uint16_t y2,
             uint16_t color,
             uint16_t *Buffer,
             uint32_t w,
             uint32_t h)
{
  for (uint16_t i = y1; i < y2; i++)
  {
    for (uint16_t j = x1; j < x2; j++)
    {
      pGP_SetPixel(j, i, color, Buffer, w, h);
    }
  }
}

void GP_SetLineH(uint16_t x,
                 uint16_t y,
                 uint16_t length,
                 uint16_t color,
                 uint16_t *Buffer,
                 uint32_t w,
                 uint32_t h)
{
  for (uint16_t i = x; i < x + length; i++)
  {
    pGP_SetPixel(i, y, color, Buffer, w, h);
  }
}

void GP_SetLineV(uint16_t x,
                 uint16_t y,
                 uint16_t length,
                 uint16_t color,
                 uint16_t *Buffer,
                 uint32_t w,
                 uint32_t h)
{
  for (uint16_t i = y; i < y + length; i++)
  {
    pGP_SetPixel(x, i, color, Buffer, w, h);
  }
}

void GP_SetCross(uint16_t x,
                 uint16_t y,
                 uint16_t width,
                 uint16_t color,
                 uint16_t *Buffer,
                 uint32_t w,
                 uint32_t h)
{
  GP_SetLineH(x - width / 2, y, width, color, Buffer, w, h);
  GP_SetLineV(x, y - width / 2, width, color, Buffer, w, h);
  GP_SetBresenhamCircle(x, y, 20, color, Buffer, w, h);
}

void GP_SetSquare(uint16_t x,
                  uint16_t y,
                  uint16_t width,
                  uint16_t height,
                  uint16_t color,
                  uint16_t *Buffer,
                  uint32_t w,
                  uint32_t h)
{
  GP_SetLineH(x - width / 2, y - height / 2, width, color, Buffer, w, h);
  GP_SetLineH(x - width / 2, y + height / 2, width, color, Buffer, w, h);
  GP_SetLineV(x - width / 2, y - height / 2, height, color, Buffer, w, h);
  GP_SetLineV(x + width / 2, y - height / 2, height, color, Buffer, w, h);
}

void GP_SetBresenhamLine(uint16_t x0,
                         uint16_t y0,
                         uint16_t x1,
                         uint16_t y1,
                         uint16_t color,
                         uint16_t *Buffer,
                         uint32_t w,
                         uint32_t h)
{
  int16_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int16_t dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int16_t err = (dx > dy ? dx : -dy) / 2, e2;

  for (;;)
  {
    pGP_SetPixel(x0, y0, color, Buffer, w, h);
    if (x0 == x1 && y0 == y1)
      break;
    e2 = err;
    if (e2 > -dx) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dy) {
      err += dx;
      y0 += sy;
    }
  }
}

void GP_SetBresenhamCircle(uint16_t x0,
                           uint16_t y0,
                           uint16_t r,
                           uint16_t color,
                           uint16_t *Buffer,
                           uint32_t w,
                           uint32_t h)
{
  int16_t x = 0;
  int16_t y = r;
  int16_t delta = 1 - 2 * r;
  int16_t error = 0;
  while (y >= 0)
  {
    pGP_SetPixel(x0 + x, y0 + y, color, Buffer, w, h);
    pGP_SetPixel(x0 + x, y0 - y, color, Buffer, w, h);

    pGP_SetPixel(x0 - x, y0 + y, color, Buffer, w, h);
    pGP_SetPixel(x0 - x, y0 - y, color, Buffer, w, h);
    error = 2 * (delta + y) - 1;
    if (delta < 0 && error <= 0) {
      ++x;
      delta += 2 * x + 1;
      continue;
    }
    error = 2 * (delta - x) - 1;
    if (delta > 0 && error > 0) {
      --y;
      delta += 1 - 2 * y;
      continue;
    }
    ++x;
    delta += 2 * (x - y);
    --y;
  }
}

void GP_RoundedRect(uint16_t x0,
                    uint16_t y0,
                    int16_t width,
                    int16_t heigth,
                    uint16_t r,
                    uint16_t color,
                    uint16_t *Buffer,
                    uint32_t w,
                    uint32_t h)
{
  int16_t x = 0;
  int16_t y = r;
  int16_t delta = 1 - 2 * r;
  int16_t error = 0;

  GP_SetLineH((x0 - width / 2) + r, (y0 - heigth / 2), width - r * 2, color,
              Buffer, w, h);
  GP_SetLineH((x0 - width / 2) + r, (y0 + heigth / 2), width - r * 2, color,
              Buffer, w, h);
  GP_SetLineV(x0 - width / 2 - 1, y0 - heigth / 2 + r, heigth - r * 2, color,
              Buffer, w, h);
  GP_SetLineV(x0 + width / 2 + 1, y0 - heigth / 2 + r, heigth - r * 2, color,
              Buffer, w, h);

  while (y >= 0) {
    pGP_SetPixel(x0 + x + (width / 2 - r), y0 + y + (heigth / 2 - r), color,
                 Buffer, w, h);
    pGP_SetPixel(x0 + x + (width / 2 - r), y0 - y - (heigth / 2 - r), color,
                 Buffer, w, h);

    pGP_SetPixel(x0 - x - (width / 2 - r), y0 + y + (heigth / 2 - r), color,
                 Buffer, w, h);
    pGP_SetPixel(x0 - x - (width / 2 - r), y0 - y - (heigth / 2 - r), color,
                 Buffer, w, h);
    error = 2 * (delta + y) - 1;
    if (delta < 0 && error <= 0) {
      ++x;
      delta += 2 * x + 1;
      continue;
    }
    error = 2 * (delta - x) - 1;
    if (delta > 0 && error > 0) {
      --y;
      delta += 1 - 2 * y;
      continue;
    }
    ++x;
    delta += 2 * (x - y);
    --y;
  }
}

void GP_DrawFilledCircle(int16_t x0,
                         int16_t y0,
                         int16_t r,
                         uint16_t color,
                         uint16_t *Buffer,
                         uint32_t w,
                         uint32_t h)
{
  int16_t x = r;
  int16_t y = 0;
  int16_t xChange = 1 - (r << 1);
  int16_t yChange = 0;
  int16_t rError = 0;

  while (x >= y) {
    for (int i = x0 - x; i <= x0 + x; i++) {
      pGP_SetPixel(i, y0 + y, color, Buffer, w, h);
      pGP_SetPixel(i, y0 - y, color, Buffer, w, h);
    }
    for (int i = x0 - y; i <= x0 + y; i++) {
      pGP_SetPixel(i, y0 + x, color, Buffer, w, h);
      pGP_SetPixel(i, y0 - x, color, Buffer, w, h);
    }
    y++;
    rError += yChange;
    yChange += 2;
    if (((rError << 1) + xChange) > 0) {
      x--;
      rError += xChange;
      xChange += 2;
    }
  }
}

void GP_DrawRoundedFill(int16_t x0,
                        int16_t y0,
                        int16_t width,
                        int16_t high,
                        int16_t r,
                        uint16_t color,
                        uint16_t *Buffer,
                        uint32_t w,
                        uint32_t h)
{
  int16_t x = r;
  int16_t y = 0;
  int16_t xChange = 1 - (r << 1);
  int16_t yChange = 0;
  int16_t rError = 0;

  GP_FILL(x0 - (width) / 2 + r, y0 - (high / 2), x0 + (width) / 2 - r,
          y0 + (high / 2), color, Buffer, w, h);
  GP_FILL(x0 - (width) / 2, y0 - (high / 2) + r, x0 + (width) / 2 + 1,
          y0 + (high / 2) - r, color, Buffer, w, h);

  while (x >= y)
  {
    for (int i = x0 - x - (width) / 2 + r; i <= x0 + x + (width) / 2 - r; i++)
    {
      pGP_SetPixel(i, y0 + y + (high / 2) - r, color, Buffer, w, h);
      pGP_SetPixel(i, y0 - y - (high / 2) + r, color, Buffer, w, h);
    }
    for (int i = x0 - y - (width) / 2 + r; i <= x0 + y + (width) / 2 - r; i++)
    {
      pGP_SetPixel(i, y0 + x + (high / 2) - r, color, Buffer, w, h);
      pGP_SetPixel(i, y0 - x - (high / 2) + r, color, Buffer, w, h);
    }
    y++;
    rError += yChange;
    yChange += 2;
    if (((rError << 1) + xChange) > 0) {
      x--;
      rError += xChange;
      xChange += 2;
    }
  }
}

void GP_SetArc(uint16_t x,
               uint16_t y,
               uint16_t a1,
               uint16_t a2,
               uint16_t r,
               uint16_t color,
               uint16_t *Buffer,
               uint32_t w,
               uint32_t h)
{
  printf("This function is not implemented yet\n");
  return;
}

void GP_PutTriangle(uint16_t x,
                    uint16_t y,
                    uint16_t width,
                    uint16_t heigth,
                    uint8_t side,
                    uint16_t color,
                    uint16_t *Buffer,
                    uint32_t w,
                    uint32_t h)
{
  uint16_t x1, y1, x2, y2, x3, y3;
  switch (side) {
  case NORTH:
    x1 = x;
    y1 = y - heigth / 2;
    x2 = x - width / 2;
    y2 = y + heigth / 2;
    x3 = x + width / 2;
    y3 = y + heigth / 2;
    break;
  case SOUTH:
    x1 = x;
    y1 = y + heigth / 2;
    x2 = x - width / 2;
    y2 = y - heigth / 2;
    x3 = x + width / 2;
    y3 = y - heigth / 2;
    break;
  case WEST:
    x1 = x - width / 2;
    y1 = y;
    x2 = x + width / 2;
    y2 = y - heigth / 2;
    x3 = x + width / 2;
    y3 = y + heigth / 2;
    break;
  case EAST:
    x1 = x + width / 2;
    y1 = y;
    x2 = x - width / 2;
    y2 = y + heigth / 2;
    x3 = x - width / 2;
    y3 = y - heigth / 2;
    break;
  default:
    return;
  }
  GP_SetBresenhamLine(x1, y1, x2, y2, color, Buffer, w, h);
  GP_SetBresenhamLine(x2, y2, x3, y3, color, Buffer, w, h);
  GP_SetBresenhamLine(x3, y3, x1, y1, color, Buffer, w, h);
}

void GP_PutArrow(uint16_t x,
                 uint16_t y,
                 uint16_t width,
                 uint16_t heigth,
                 uint8_t side,
                 uint16_t color,
                 uint16_t *Buffer,
                 uint32_t w,
                 uint32_t h)
{

  uint16_t l_w, l_h, x0, y0, x1_1, x1_2, y1_1, y1_2;
  uint16_t x1, y1, x2, y2, x3, y3, x4, y4;

  switch (side) {
  case NORTH:
    l_w = heigth;
    l_h = width;
    x0 = x;
    y0 = y - l_h / 2;
    x1_1 = x - l_w / 2;
    y1_1 = y - l_h / 6;
    x1_2 = x + l_w / 2;
    y1_2 = y - l_h / 6;

    x1 = x - l_w / 4;
    y1 = y - l_h / 6;
    x2 = x + l_w / 4;
    y2 = y1;
    x3 = x1;
    y3 = y + l_h / 2;
    x4 = x2;
    y4 = y3;

    break;
  case SOUTH:
    l_w = heigth;
    l_h = width;
    x0 = x;
    y0 = y + l_h / 2;
    x1_1 = x + l_w / 2;
    y1_1 = y + l_h / 6;
    x1_2 = x - l_w / 2;
    y1_2 = y + l_h / 6;

    x1 = x + l_w / 4;
    y1 = y + l_h / 6;
    x2 = x - l_w / 4;
    y2 = y1;
    x3 = x1;
    y3 = y - l_h / 2;
    x4 = x2;
    y4 = y3;

    break;
  case WEST:
    l_w = width;
    l_h = heigth;

    x0 = x - l_w / 2;
    y0 = y;
    x1_1 = x - l_w / 6;
    y1_1 = y + l_h / 2;

    x1_2 = x - l_w / 6;
    y1_2 = y - l_h / 2;

    x1 = x - l_w / 6;
    y1 = y + l_h / 4;
    x2 = x1;
    y2 = y - l_h / 4;
    x3 = x + l_w / 2;
    y3 = y1;
    x4 = x3;
    y4 = y2;

    break;
  case EAST:
    l_w = width;
    l_h = heigth;

    x0 = x + l_w / 2;
    y0 = y;
    x1_1 = x + l_w / 6;
    y1_1 = y - l_h / 2;
    x1_2 = x + l_w / 6;
    y1_2 = y + l_h / 2;

    x1 = x + l_w / 6;
    y1 = y - l_h / 4;
    x2 = x1;
    y2 = y + l_h / 4;
    x3 = x - l_w / 2;
    y3 = y1;
    x4 = x3;
    y4 = y2;
    break;
  default:
    return;
  }
  GP_SetBresenhamLine(x0, y0, x1_1, y1_1, color, Buffer, w, h);
  GP_SetBresenhamLine(x0, y0, x1_2, y1_2, color, Buffer, w, h);

  GP_SetBresenhamLine(x1_1, y1_1, x1, y1, color, Buffer, w, h);
  GP_SetBresenhamLine(x2, y2, x1_2, y1_2, color, Buffer, w, h);

  GP_SetBresenhamLine(x1, y1, x3, y3, color, Buffer, w, h);
  GP_SetBresenhamLine(x2, y2, x4, y4, color, Buffer, w, h);

  GP_SetBresenhamLine(x3, y3, x4, y4, color, Buffer, w, h);
}

void GP_FillArea(uint16_t x,
                 uint16_t y,
                 uint16_t heigth,
                 uint16_t width,
                 uint16_t color,
                 uint16_t border_color,
                 uint16_t *Buffer,
                 uint32_t w,
                 uint32_t h)
{
  uint16_t x1 = x;
  uint16_t y1 = y;
  bool xflag = false;
  bool yflag = false;
  for (y1 = y; y1 < y + heigth / 2; y1++) {
    if (border_color == pGP_GetColor(x1, y1, Buffer, w, h)) {
      yflag = true;
    }
    for (x1 = x; x1 < x + width / 2; x1++) {
      if (border_color == pGP_GetColor(x1, y1, Buffer, w, h)) {
        xflag = true;
      }
      if ((!xflag) && (!yflag)) {
        pGP_SetPixel(x1, y1, color, Buffer, w, h);
      }
    }
    xflag = false;
    x1 = x;
  }

  xflag = false;
  yflag = false;

  for (y1 = y - 1; y1 > y - heigth / 2; y1--) {
    if (border_color == pGP_GetColor(x1, y1, Buffer, w, h)) {
      yflag = true;
    }

    for (x1 = x - 1; x1 > x - width / 2; x1--) {
      if (border_color == pGP_GetColor(x1, y1, Buffer, w, h)) {
        xflag = true;
      }
      if ((!xflag) && (!yflag)) {
        pGP_SetPixel(x1, y1, color, Buffer, w, h);
      }
    }
    xflag = false;
    x1 = x - 1;
  }

  xflag = false;
  yflag = false;
  x1 = x + 1;
  y1 = y - 1;

  for (y1 = y - 1; y1 > (y - heigth / 2); y1--) {
    if (border_color == pGP_GetColor(x1, y1, Buffer, w, h)) {
      yflag = true;
    }

    for (x1 = x; x1 < x + width / 2; x1++) {
      if (border_color == pGP_GetColor(x1, y1, Buffer, w, h)) {
        xflag = true;
      }
      if ((!xflag) && (!yflag)) {
        pGP_SetPixel(x1, y1, color, Buffer, w, h);
      }
    }
    xflag = false;
    x1 = x;
  }

  xflag = false;
  yflag = false;

  x1 = x - 1;
  y1 = y + 1;

  for (y1 = y; y1 < y + heigth / 2; y1++) {
    if (border_color == pGP_GetColor(x1, y1, Buffer, w, h)) {
      yflag = true;
    }
    for (x1 = x - 1; x1 > x - width / 2; x1--) {
      if (border_color == pGP_GetColor(x1, y1, Buffer, w, h)) {
        xflag = true;
      }
      if ((!xflag) && (!yflag)) {
        pGP_SetPixel(x1, y1, color, Buffer, w, h);
      }
    }
    xflag = false;
    x1 = x - 1;
  }
}

void GP_PutChar(uint16_t x,
                uint16_t y,
                uint16_t color,
                const uint8_t Ch,
                const FONT *f,
                uint16_t *Buffer,
                uint32_t w,
                uint32_t h,
                unsigned cbc)
{
  const uint8_t *fPtr = f->Bitmap;
  uint8_t mask = 0x80;
  uint8_t width;

  fPtr += f->FontChar[Ch].offset;

  width = f->FontChar[Ch].width / 8;
  if (f->FontChar[Ch].width % 8 != 0)
    width++;

  uint16_t BcGrCol = 0;
  if (!cbc)
    BcGrCol = pGP_GetColor(x, y, Buffer, w, h);

  for (uint16_t i = 0; i < f->Heigth; i++)
  {
    for (uint16_t j = 0; j < width; j++)
    {
      for (uint16_t k = 0; k < 8; k++) {
        if (*fPtr & mask) {
          pGP_SetPixel(x, y, color, Buffer, w, h);
        } else {
            pGP_SetPixel(x, y, BcGrCol, Buffer, w, h);
        }
        x++;
        mask >>= 0x01;
      }
      pGP_SetPixel(x, y, BcGrCol, Buffer, w, h);
      pGP_SetPixel(x + 1, y, BcGrCol, Buffer, w, h);
      mask = 0x80;
      fPtr++;
    }
    y++;
    x -= 8 * width;
  }
}

void GP_PutString(uint16_t x,
                  uint16_t y,
                  uint16_t color,
                  const uint8_t *String,
                  const FONT *f,
                  uint16_t *Buffer,
                  uint32_t w,
                  uint32_t h,
                  unsigned cbc)
{
  uint8_t Ch;

  while (*String != 0)
  {
    Ch = (uint8_t)(*String);

    if (Ch > 126) {
      Ch -= 96;
    } else {
      Ch -= 32;
    }
   GP_PutChar(x, y, color, Ch, f, Buffer, w, h, cbc);
    x += f->FontChar[Ch].width + 2;
    String++;
  }
}

void GP_PutStringInTheCenter(uint16_t x,
                             uint16_t y,
                             uint16_t color,
                             const uint8_t *String,
                             const FONT *f,
                             uint16_t *Buffer,
                             uint32_t w,
                             uint32_t h,
                             unsigned cbc)
{
  uint16_t SLP = 0; // String Lenghth in pixels
  const uint8_t *StrPtr = String;
  uint8_t Ch;
  uint32_t xx;
  uint32_t yy;

  if (*String == 0)
    return;
  do {

    Ch = (uint8_t)(*StrPtr);

    if (Ch > 126)
      Ch -= 96;
    else
      Ch -= 32;
    SLP += f->FontChar[Ch].width + 2;
    StrPtr++;
  } while (*StrPtr != '\0');

  StrPtr = String;
  xx = x - SLP / 2;
  yy = y - f->Heigth / 2;

  do {
    Ch = (uint8_t)(*StrPtr);

    if (Ch > 126)
      Ch -= 96;
    else
      Ch -= 32;
    GP_PutChar(xx, yy, color, Ch, f, Buffer, w, h, cbc);
    xx += f->FontChar[Ch].width + 2;
    StrPtr++;
  } while (*StrPtr != '\0');
}

void BMP_DrawTransp(uint16_t Xpos,
                    uint16_t Ypos,
                    uint8_t *pbmp,
                    uint16_t color,
                    uint16_t *Buffer,
                    uint32_t w,
                    uint32_t h)
{

    return;
}
