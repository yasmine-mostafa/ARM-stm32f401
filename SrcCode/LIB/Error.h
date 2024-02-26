/*
 * Error.h
 *
 *  Created on: Feb 19, 2024
 *      Author: top one
 */

#ifndef LIB_ERROR_H_
#define LIB_ERROR_H_

/**
*@brief  :Error Status For Operations
*/
typedef enum
{
	/**
	*@brief  :Operation is Done Correctly.
	*/
	Error_OK,
	/**
	*@brief  :Operation is Not Done Correctly.
	*/
	Error_NOK,
	/**
	*@brief  :Operation is Timed Out.
	*/
	Error_Timeout,
	/**
	*@brief  :Invalid Clock Input.
	*/
	Error_InvalidInput,

	Error_NULLPointer
}Error_t;

#endif /* LIB_ERROR_H_ */
