/* Copyright (C) 2003 MySQL AB

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

/*
   Shared, independent copyright: (C) 2001 Jan Pazdziora.

   Development of this software was supported by Neocortex, s.r.o.
   MySQL AB expresses its gratitude to Jan for for giving us this software.

   Bug reports and suggestions are always welcome.

   This file implements the collating sequence for Windows-1250
   character set. It merely extends the binary sorting of US-ASCII
   by adding characters with diacritical marks into proper places.
   In addition, it sorts 'ch' between 'h' and 'i', and the sorting
   is case sensitive, with uppercase being sorted first, in the
   second pass.
*/

/*
 * This comment is parsed by configure to create ctype.c,
 * so don't change it unless you know what you are doing.
 *
 * .configure. strxfrm_multiply_win1250ch=2
 */

#define REAL_MYSQL
#ifdef REAL_MYSQL

#include "my_global.h"
#include "m_string.h"
#include "m_ctype.h"

#else

#include <stdio.h>
#define uchar unsigned char

#endif

#ifdef HAVE_CHARSET_cp1250


static uint16 tab_cp1250_uni[256]={
     0,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,
0x0008,0x0009,0x000A,0x000B,0x000C,0x000D,0x000E,0x000F,
0x0010,0x0011,0x0012,0x0013,0x0014,0x0015,0x0016,0x0017,
0x0018,0x0019,0x001A,0x001B,0x001C,0x001D,0x001E,0x001F,
0x0020,0x0021,0x0022,0x0023,0x0024,0x0025,0x0026,0x0027,
0x0028,0x0029,0x002A,0x002B,0x002C,0x002D,0x002E,0x002F,
0x0030,0x0031,0x0032,0x0033,0x0034,0x0035,0x0036,0x0037,
0x0038,0x0039,0x003A,0x003B,0x003C,0x003D,0x003E,0x003F,
0x0040,0x0041,0x0042,0x0043,0x0044,0x0045,0x0046,0x0047,
0x0048,0x0049,0x004A,0x004B,0x004C,0x004D,0x004E,0x004F,
0x0050,0x0051,0x0052,0x0053,0x0054,0x0055,0x0056,0x0057,
0x0058,0x0059,0x005A,0x005B,0x005C,0x005D,0x005E,0x005F,
0x0060,0x0061,0x0062,0x0063,0x0064,0x0065,0x0066,0x0067,
0x0068,0x0069,0x006A,0x006B,0x006C,0x006D,0x006E,0x006F,
0x0070,0x0071,0x0072,0x0073,0x0074,0x0075,0x0076,0x0077,
0x0078,0x0079,0x007A,0x007B,0x007C,0x007D,0x007E,0x007F,
0x20AC,     0,0x201A,     0,0x201E,0x2026,0x2020,0x2021,
     0,0x2030,0x0160,0x2039,0x015A,0x0164,0x017D,0x0179,
     0,0x2018,0x2019,0x201C,0x201D,0x2022,0x2013,0x2014,
     0,0x2122,0x0161,0x203A,0x015B,0x0165,0x017E,0x017A,
0x00A0,0x02C7,0x02D8,0x0141,0x00A4,0x0104,0x00A6,0x00A7,
0x00A8,0x00A9,0x015E,0x00AB,0x00AC,0x00AD,0x00AE,0x017B,
0x00B0,0x00B1,0x02DB,0x0142,0x00B4,0x00B5,0x00B6,0x00B7,
0x00B8,0x0105,0x015F,0x00BB,0x013D,0x02DD,0x013E,0x017C,
0x0154,0x00C1,0x00C2,0x0102,0x00C4,0x0139,0x0106,0x00C7,
0x010C,0x00C9,0x0118,0x00CB,0x011A,0x00CD,0x00CE,0x010E,
0x0110,0x0143,0x0147,0x00D3,0x00D4,0x0150,0x00D6,0x00D7,
0x0158,0x016E,0x00DA,0x0170,0x00DC,0x00DD,0x0162,0x00DF,
0x0155,0x00E1,0x00E2,0x0103,0x00E4,0x013A,0x0107,0x00E7,
0x010D,0x00E9,0x0119,0x00EB,0x011B,0x00ED,0x00EE,0x010F,
0x0111,0x0144,0x0148,0x00F3,0x00F4,0x0151,0x00F6,0x00F7,
0x0159,0x016F,0x00FA,0x0171,0x00FC,0x00FD,0x0163,0x02D9
};


/* 0000-00FD , 254 chars */
static uchar tab_uni_cp1250_plane00[]={
0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xA0,0x00,0x00,0x00,0xA4,0x00,0xA6,0xA7,0xA8,0xA9,0x00,0xAB,0xAC,0xAD,0xAE,0x00,
0xB0,0xB1,0x00,0x00,0xB4,0xB5,0xB6,0xB7,0xB8,0x00,0x00,0xBB,0x00,0x00,0x00,0x00,
0x00,0xC1,0xC2,0x00,0xC4,0x00,0x00,0xC7,0x00,0xC9,0x00,0xCB,0x00,0xCD,0xCE,0x00,
0x00,0x00,0x00,0xD3,0xD4,0x00,0xD6,0xD7,0x00,0x00,0xDA,0x00,0xDC,0xDD,0x00,0xDF,
0x00,0xE1,0xE2,0x00,0xE4,0x00,0x00,0xE7,0x00,0xE9,0x00,0xEB,0x00,0xED,0xEE,0x00,
0x00,0x00,0x00,0xF3,0xF4,0x00,0xF6,0xF7,0x00,0x00,0xFA,0x00,0xFC,0xFD};

/* 0102-017E , 125 chars */
static uchar tab_uni_cp1250_plane01[]={
0xC3,0xE3,0xA5,0xB9,0xC6,0xE6,0x00,0x00,0x00,0x00,0xC8,0xE8,0xCF,0xEF,0xD0,0xF0,
0x00,0x00,0x00,0x00,0x00,0x00,0xCA,0xEA,0xCC,0xEC,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC5,0xE5,0x00,0x00,0xBC,0xBE,0x00,0x00,0xA3,
0xB3,0xD1,0xF1,0x00,0x00,0xD2,0xF2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD5,0xF5,
0x00,0x00,0xC0,0xE0,0x00,0x00,0xD8,0xF8,0x8C,0x9C,0x00,0x00,0xAA,0xBA,0x8A,0x9A,
0xDE,0xFE,0x8D,0x9D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD9,0xF9,0xDB,0xFB,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8F,0x9F,0xAF,0xBF,0x8E,0x9E};

/* 2013-20AC , 154 chars */
static uchar tab_uni_cp1250_plane20[]={
0x96,0x97,0x00,0x00,0x00,0x91,0x92,0x82,0x00,0x93,0x94,0x84,0x00,0x86,0x87,0x95,
0x00,0x00,0x00,0x85,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x89,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x8B,0x9B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80};

/* 02C7-02DD ,  23 chars */
static uchar tab_uni_cp1250_plane02[]={
0xA1,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xA2,0xFF,0x00,0xB2,0x00,0xBD};

/* 2122-2122 ,   1 chars */
static uchar tab_uni_cp1250_plane21[]={
0x99};


static MY_UNI_IDX idx_uni_cp1250[]={
  {0x0000,0x00FD,tab_uni_cp1250_plane00},
  {0x0102,0x017E,tab_uni_cp1250_plane01},
  {0x2013,0x20AC,tab_uni_cp1250_plane20},
  {0x02C7,0x02DD,tab_uni_cp1250_plane02},
  {0x2122,0x2122,tab_uni_cp1250_plane21},
  {0,0,NULL}
};


static uchar NEAR ctype_win1250ch[] = {
0x00,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x28, 0x28, 0x28, 0x28, 0x28, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x48, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84,
0x84, 0x84, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x02,
0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
0x02, 0x02, 0x02, 0x10, 0x10, 0x10, 0x10, 0x20,
0x20, 0x20, 0x10, 0x20, 0x10, 0x10, 0x10, 0x10,
0x20, 0x10, 0x01, 0x10, 0x01, 0x01, 0x01, 0x01,
0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x20, 0x10, 0x02, 0x10, 0x02, 0x02, 0x02, 0x02,
0x48, 0x10, 0x10, 0x01, 0x10, 0x01, 0x10, 0x01,
0x10, 0x10, 0x01, 0x10, 0x10, 0x10, 0x10, 0x01,
0x10, 0x10, 0x10, 0x02, 0x10, 0x10, 0x10, 0x10,
0x10, 0x02, 0x02, 0x10, 0x01, 0x10, 0x02, 0x02,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x10,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02,
0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x10,
0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x10
};

static uchar NEAR to_lower_win1250ch[] = {
0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
0x40, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
0x78, 0x79, 0x7a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
0x88, 0x89, 0x9a, 0x8b, 0x9c, 0x9d, 0x9e, 0x9f,
0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
0xa0, 0xa1, 0xa2, 0xb3, 0xa4, 0xb9, 0xa6, 0xdf,
0xa8, 0xa9, 0xba, 0xab, 0xac, 0xad, 0xae, 0xbf,
0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
0xb8, 0xb9, 0xba, 0xbb, 0xbe, 0xbd, 0xbe, 0xbf,
0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xd7,
0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xdf,
0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
};

static uchar NEAR to_upper_win1250ch[] = {
0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
0x60, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
0x58, 0x59, 0x5a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
0x98, 0x99, 0x8a, 0x9b, 0x8c, 0x8d, 0x8e, 0x8f,
0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
0xb0, 0xb1, 0xb2, 0xa3, 0xb4, 0xb5, 0xb6, 0xb7,
0xb8, 0xa5, 0xaa, 0xbb, 0xbc, 0xbd, 0xbc, 0xaf,
0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xa7,
0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xf7,
0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xff
};



static uchar NEAR sort_order_win1250ch[] = {
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
};

static uchar NEAR _sort_order_win1250ch1[] = {
0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
/* space ord 32 0x20 */
0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91,
/* 0 ord 48 0x30 */
0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99,
0x9a, 0x9b,
	    /* colon ord 58 0x3a */
	    0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1,
0xa2,
      /* A ord 65 0x41 */
      0xa4, 0xa5,
		  /* C ord 67 0x43 */
		  0xff, 0xa8, 0xa9, 0xaa, 0xab,
0xac, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
0xb5, 0xb6,
	    /* R ord 82 0x52 */
	    0xb7, 
		  /* S ord 83 0x53 */
		  0xb9, 0xbc, 0xbd, 0xbe, 0xbf,
0xc0, 0xc1, 0xc2,
		  /* [ ord 91 0x5b */
		  0xc4, 0xc5, 0xc6, 0xc7, 0xc8,
0xc9,
      /* a ord 97 0x61 */
      0xa4, 0xa5, 0xff, 0xa8, 0xa9, 0xaa, 0xab,
0xac, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
0xb5, 0xb6, 0xb7, 0xb9, 0xbc, 0xbd, 0xbe, 0xbf,
0xc0, 0xc1, 0xc2,
		  /* { ord 123 0x7b */
		  0xca, 0xcb, 0xcc, 0xcd, 0x81,
0x81, 0x81, 0xce, 0x81, 0xcf, 0xd0, 0xd1, 0xd2,
0x81, 0xd3,
	    /* Scaron ord 138 0x8a */
	    0xba, 0xd4, 0xb9, 0xbc, 0xc3, 0xc2,
0x81, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb,
0x81, 0xdc, 0xba, 0xdd, 0xb9, 0xbc, 0xc3, 0xc2,
/* nobreakspace ord 160 0xa0 */
0x82, 0xde, 0xdf, 0xb1, 0xe0, 0xa4, 0xe1, 0xe2,
0xe3, 0xe4, 0xb9, 0xe5, 0xe6, 0xe7, 0xe8, 0xc2,
0xe9, 0xea, 0xeb, 0xb1, 0xed, 0xee, 0x81, 0xef,
/* cedilla ord 183 0xb8 */
0xf0, 0xa4, 0xb9, 0xf1, 0xb1, 0xf2, 0xb1, 0xc2,
0xb7, 0xa4, 0xa4, 0xa4, 0xa4, 0xb1, 0xa6, 0xa6,
0xa7, 0xa9, 0xa9, 0xa9, 0xa9, 0xae, 0xae, 0xa8,
/* Eth ord 208 0xd0 */
0xa8, 0xb3, 0xb3, 0xb4, 0xb4, 0xb4, 0xb4, 0xf3,
0xb8, 0xbd, 0xbd, 0xbd, 0xbd, 0xc1, 0xbc, 0xbb,
/* racute ord 224 0xe0 */
0xb7, 0xa4, 0xa4, 0xa4, 0xa4, 0xb1, 0xa6, 0xa6,
0xa7, 0xa9, 0xa9, 0xa9, 0xa9, 0xae, 0xae, 0xa8,
/* eth ord 240 0xf0 */
0xa8, 0xb3, 0xb3, 0xb4, 0xb4, 0xb4, 0xb4, 0xf4,
0xb8, 0xbd, 0xbd, 0xbd, 0xbd, 0xc1, 0xbc, 0xf5
};

static uchar NEAR _sort_order_win1250ch2[] = {
0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11,
0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21,
/* space ord 32 0x20 */
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
/* 0 ord 48 0x30 */
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01,
	    /* colon ord 58 0x3a */
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01,
      /* A ord 65 0x41 */
      0x01, 0x01,
		  /* C ord 67 0x43 */
		  0xff, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01,
	    /* R ord 82 0x52 */
	    0x01, 
		  /* S ord 83 0x53 */
		  0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01,
		  /* [ ord 91 0x5b */
		  0x01, 0x01, 0x01, 0x01, 0x01,
0x01,
      /* a ord 97 0x61 */
      0x02, 0x02, 0xff, 0x02, 0x02, 0x02, 0x02,
0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
0x02, 0x02, 0x02,
		  /* { ord 123 0x7b */
		  0x01, 0x01, 0x01, 0x01, 0x22,
0x23, 0x24, 0x01, 0x25, 0x01, 0x01, 0x01, 0x01,
0x26, 0x01,
	    /* Scaron ord 138 0x8a */
	    0x01, 0x01, 0x03, 0x03, 0x01, 0x05,
0x27, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x28, 0x01, 0x02, 0x01, 0x04, 0x04, 0x02, 0x06,
/* nobreakspace ord 160 0xa0 */
0x02, 0x01, 0x01, 0x07, 0x01, 0x11, 0x01, 0x01,
0x01, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x03,
0x01, 0x01, 0x01, 0x08, 0x01, 0x01, 0x29, 0x01,
/* cedilla ord 184 0xb8 */
0x01, 0x12, 0x06, 0x01, 0x05, 0x01, 0x06, 0x04,
0x03, 0x03, 0x05, 0x07, 0x09, 0x03, 0x03, 0x05,
0x01, 0x03, 0x09, 0x07, 0x05, 0x03, 0x05, 0x03,
/* Eth ord 208 0xd0 */
0x05, 0x03, 0x05, 0x03, 0x05, 0x09, 0x07, 0x01,
0x01, 0x05, 0x03, 0x09, 0x07, 0x03, 0x05, 0x01,
/* racute ord 224 0xe0 */
0x04, 0x04, 0x06, 0x08, 0x0a, 0x04, 0x04, 0x06,
0x02, 0x04, 0x0a, 0x08, 0x06, 0x04, 0x06, 0x04,
/* eth ord 240 0xf0 */
0x06, 0x04, 0x06, 0x04, 0x06, 0x0a, 0x08, 0x01,
0x02, 0x06, 0x04, 0x0a, 0x08, 0x04, 0x06, 0x01
};

struct wordvalue {
	const uchar * word;
	uchar pass1;
	uchar pass2;
};
static struct wordvalue doubles[] = {
	{ (uchar*) "ch", 0xad, 0x03 },
	{ (uchar*) "c",  0xa6, 0x02 },
	{ (uchar*) "Ch", 0xad, 0x02 },
	{ (uchar*) "CH", 0xad, 0x01 },
	{ (uchar*) "C",  0xa6, 0x01 },
};

#define NEXT_CMP_VALUE(src, p, pass, value, len)			\
	while (1) {							\
		if (IS_END(p, src, len)) {				\
			if (pass == 0) { p = src; pass++; }		\
			else { value = 0; break; }			\
		}							\
		value = ((pass == 0) ? _sort_order_win1250ch1[*p]	\
			: _sort_order_win1250ch2[*p]);			\
		if (value == 0xff) {					\
			int i;						\
			for (i = 0; i < (int) sizeof(doubles); i++) {	\
				const uchar * patt = doubles[i].word;	\
				const uchar * q = (const uchar *) p;	\
				while (*patt				\
					&& !(IS_END(q, src, len))	\
					&& (*patt == *q)) {		\
					patt++; q++;			\
				}					\
				if (!(*patt)) {				\
					value = (int)((pass == 0)	\
						? doubles[i].pass1	\
						: doubles[i].pass2);	\
					p = (const uchar *) q - 1;	\
					break;				\
				}					\
			}						\
		}							\
		p++;							\
		break;							\
	}

#define IS_END(p, src, len)	(((char *)p - (char *)src) >= (len))

static int my_strnncoll_win1250ch(CHARSET_INFO *cs __attribute__((unused)), 
				  const uchar * s1, uint len1,
                                  const uchar * s2, uint len2,
                                  my_bool s2_is_prefix)
{
  int v1, v2;
  const uchar * p1, * p2;
  int pass1 = 0, pass2 = 0;
  int diff;

  if (s2_is_prefix && len1 > len2)
    len1=len2;

  p1 = s1;	p2 = s2;

  do
  {
    NEXT_CMP_VALUE(s1, p1, pass1, v1, (int)len1);
    NEXT_CMP_VALUE(s2, p2, pass2, v2, (int)len2);
    if ((diff = v1 - v2))
      return diff;
  } while (v1);
  return 0;
}


/*
  TODO: Has to be fixed as strnncollsp in ctype-simple
*/

static
int my_strnncollsp_win1250ch(CHARSET_INFO * cs, 
			     const uchar *s, uint slen, 
			     const uchar *t, uint tlen)
{
  for ( ; slen && s[slen-1] == ' ' ; slen--);
  for ( ; tlen && t[tlen-1] == ' ' ; tlen--);
  return my_strnncoll_win1250ch(cs,s,slen,t,tlen,0);
}


static int my_strnxfrm_win1250ch(CHARSET_INFO * cs  __attribute__((unused)),
				 uchar * dest, uint len, 
				 const uchar * src, uint srclen)
{
  int value;
  const uchar * p;
  int pass = 0;
  uint totlen = 0;
  p = src;

  do {
    NEXT_CMP_VALUE(src, p, pass, value, (int)srclen);
    if (totlen <= len)
      dest[totlen] = value;
    totlen++;
  } while (value) ;
  return totlen;
}

#undef IS_END

#ifdef REAL_MYSQL

static uchar NEAR like_range_prefix_min_win1250ch[] =
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
96, 54, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 165, 124, 125, 126, 0,
0, 0, 130, 0, 132, 133, 134, 135, 0, 137, 138, 139, 83, 84, 142, 90,
0, 145, 146, 147, 148, 149, 150, 151, 0, 153, 138, 155, 83, 84, 142, 90,
32, 161, 162, 76, 164, 165, 166, 167, 168, 65, 83, 171, 172, 173, 174, 90,
176, 177, 178, 76, 180, 181, 0, 183, 184, 65, 83, 187, 76, 189, 76, 90,
82, 65, 65, 65, 65, 76, 67, 67, 200, 69, 69, 69, 69, 73, 73, 68,
68, 78, 78, 79, 79, 79, 79, 215, 216, 85, 85, 85, 85, 89, 84, 223,
82, 65, 65, 65, 65, 76, 67, 67, 200, 69, 69, 69, 69, 73, 73, 68,
68, 78, 78, 79, 79, 79, 79, 247, 216, 85, 85, 85, 85, 89, 84, 255,
};
static uchar NEAR like_range_prefix_max_win1250ch[] = {
182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
160, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
64, 185, 98, 73, 240, 234, 102, 103, 104, 238, 106, 107, 179, 109, 242, 245,
112, 113, 224, 186, 254, 251, 118, 119, 120, 253, 159, 91, 92, 93, 94, 95,
96, 54, 98, 73, 240, 234, 102, 103, 104, 238, 106, 107, 179, 109, 242, 245,
112, 113, 224, 186, 254, 251, 118, 119, 120, 253, 159, 165, 124, 125, 126, 182,
182, 182, 130, 182, 132, 133, 134, 135, 182, 137, 154, 139, 186, 254, 158, 159,
182, 145, 146, 147, 148, 149, 150, 151, 182, 153, 154, 155, 186, 254, 158, 159,
32, 161, 162, 179, 164, 165, 166, 167, 168, 185, 186, 171, 172, 173, 174, 159,
176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 179, 189, 179, 159,
224, 185, 185, 185, 185, 179, 238, 238, 200, 234, 234, 234, 234, 238, 238, 240,
240, 242, 242, 245, 245, 245, 245, 215, 248, 251, 251, 251, 251, 253, 254, 223,
224, 185, 185, 185, 185, 179, 238, 238, 200, 234, 234, 234, 234, 238, 238, 240,
240, 242, 242, 245, 245, 245, 245, 247, 248, 251, 251, 251, 251, 253, 254, 255,
};

#define min_sort_char '\x00'
#define max_sort_char '\xff'

/*
** Calculate min_str and max_str that ranges a LIKE string.
** Arguments:
** ptr		Pointer to LIKE string.
** ptr_length	Length of LIKE string.
** escape	Escape character in LIKE.  (Normally '\').
**		All escape characters should be removed from min_str and max_str
** res_length   Length of min_str and max_str.
** min_str      Smallest case sensitive string that ranges LIKE.
**		Should be space padded to res_length.
** max_str	Largest case sensitive string that ranges LIKE.
**		Normally padded with the biggest character sort value.
**
** The function should return 0 if ok and 1 if the LIKE string can't be
** optimized !
*/

static my_bool
my_like_range_win1250ch(CHARSET_INFO *cs __attribute__((unused)),
			const char *ptr, uint ptr_length,
			pbool escape, pbool w_one, pbool w_many,
			uint res_length,
			char *min_str, char *max_str,
			uint *min_length, uint *max_length)
{

  int only_min_found= 1;
  const char *end = ptr + ptr_length;
  char *min_org = min_str;
  char *min_end = min_str + res_length;

  /* return 1; */

  for (; ptr != end && min_str != min_end ; ptr++)
  {
    if (*ptr == escape && ptr+1 != end)
      ptr++;					/* Skip escape */
    else if (*ptr == w_one || *ptr == w_many)	/* '_' or '%' in SQL */
      break;
    *min_str = like_range_prefix_min_win1250ch[(uint)(*ptr)];
    if (*min_str != min_sort_char)
      only_min_found= 0;
    min_str++;
    *max_str++ = like_range_prefix_max_win1250ch[(uint)(*ptr)];
  }

  *min_length = (uint) (min_str - min_org);
  *max_length = res_length;
  while (min_str != min_end)
  {
    *min_str++ = min_sort_char;
    *max_str++ = max_sort_char;
  }
  return (only_min_found);
}


static MY_COLLATION_HANDLER my_collation_czech_ci_handler =
{
  my_strnncoll_win1250ch,
  my_strnncollsp_win1250ch,
  my_strnxfrm_win1250ch,
  my_like_range_win1250ch,
  my_wildcmp_8bit,
  my_strcasecmp_8bit,
  my_instr_simple,
  my_hash_sort_simple
};


CHARSET_INFO my_charset_cp1250_czech_ci =
{
  34,0,0,			/* number    */
  MY_CS_COMPILED|MY_CS_STRNXFRM,		/* state     */
  "cp1250",			/* cs name    */
  "cp1250_czech_cs",		/* name      */
  "",				/* comment   */
  ctype_win1250ch,
  to_lower_win1250ch,
  to_upper_win1250ch,
  sort_order_win1250ch,
  NULL,				/* sort_order_big*/
  tab_cp1250_uni,		/* tab_to_uni   */
  idx_uni_cp1250,		/* tab_from_uni */
  "","",
  2,				/* strxfrm_multiply */
  1,				/* mbminlen  */
  1,				/* mbmaxlen  */
  0,				/* min_sort_char */
  0,				/* max_sort_char */
  &my_charset_8bit_handler,
  &my_collation_czech_ci_handler
};


#endif /* REAL_MYSQL */

#endif /* HAVE_CHARSET_cp1250 */
