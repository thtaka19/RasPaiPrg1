/**********************************************************************
 *
 * Filename:    cli.h
 * 
 * Description: Header file for command line interface module.
 *
 * Notes:       
 * 
 * Copyright (c) 2006 Anthony Massa and Michael Barr. All rights reserved.
 * This code is from the book Programming Embedded Systems, With C and
 * GNU Development Tools, 2nd Edition.
 * It is provided AS-IS, WITHOUT ANY WARRANTY either expressed or implied.
 * You may study, use, and modify it for any non-commercial purpose,
 * including teaching and use in open-source projects.
 * You may distribute it non-commercially as long as you retain this notice.
 * For a commercial use license, or to purchase the book,
 * please visit http://www.oreilly.com/catalog/embsys2.
 *
 **********************************************************************/

#ifndef _CLI_H
#define _CLI_H


typedef struct
{
    char const    *name;
    void          (*function)(void);
	// int  data ;
} command_t;


extern command_t const gCommandTable[];


void cliProcessCommand(void);
int cliBuildCommand(char nextChar);


#endif /* _CLI_H */
