/**
*	\file         LibGPFonts.h
*	\brief        Library for fonts creating.
*	\author       Roman Garanin 
*/

#ifndef LIB_GP_FONTS_H
#define LIB_GP_FONTS_H

#include <stdint.h>

/**
*	\brief	Character descriptor struct.
*/
typedef struct font_char
{
  uint8_t width;	/**< Width of each character. */
  uint16_t  offset;	/**< Character offset in bitmap array. */
} FONT_CHAR;

/**
*	\brief	Font struct.
*/
typedef struct font
{
	uint8_t Heigth;				/**< Characters heigth. */
	const FONT_CHAR* FontChar;	/**< Characters descriptor array. */
	const uint8_t* Bitmap;		/**< Character bitmap array */
} FONT;

/* Font data for Times New Roman 16pt */
extern const FONT timesNewRoman_16ptFont;

#endif
