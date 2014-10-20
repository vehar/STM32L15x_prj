/*
 *	File:	macros.h
 *	Date:	09.01.2011
 */

#ifndef MACROS_H_
#define MACROS_H_

#define BIT(NUMBER)            		(1UL << (NUMBER))

#define ARRAY_LENGHT(Value)			(sizeof(Value) / sizeof(Value[0]))

#define SET(X) X=1
#define RESET(X) X=0

#endif /* MACROS_H_ */
