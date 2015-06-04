/**
 ******************************************************************************
 * @file    GyroSensor.h
 * @author  AST / EST
 * @version V0.0.1
 * @date    13-April-2015
 * @brief   This file contains the abstract class describing in general
 *          the interfaces of a gyroscope
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Define to prevent from recursive inclusion --------------------------------*/
#ifndef __GYRO_SENSOR_CLASS_H
#define __GYRO_SENSOR_CLASS_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Classes  ------------------------------------------------------------------*/
/** An abstract class for a Gyroscope
 */
class GyroSensor
{
 public:
	/**
	 * @brief       Initialization of gyroscope
	 * @param[out]  Pointer to device specific initalization structure
	 * @retval      0 in case of success, an error code otherwise
	 */
	virtual int Init(void*) = 0;
	
	/**
	 * @brief       Get ID of gyroscope
	 * @param[out]  Pointer to where to store the ID to
	 * @retval      0 in case of success, an error code otherwise
	 */
	virtual int ReadID(uint8_t*) = 0;

	/**
	 * @brief       Get current gyroscope angular rate X/Y/Z-axes values 
	 *              in standard data units [mdps]
	 * @param[out]  Pointer to where to store angular rates to.
	 *              Pointer must point to an array of (at least) three elements, where:
	 *              ptr[0] corresponds to X-axis
	 *              ptr[1] corresponds to Y-axis
	 *              ptr[2] corresponds to Z-axis
	 * @retval      0 in case of success, an error code otherwise
	 */
	virtual int Get_G_Axes(int32_t*) = 0;

	/**
	 * @brief       Get current gyroscope raw data X/Y/Z-axes values 
	 *              in device sepcific LSB units
	 * @param[out]  Pointer to where to store gyroscope raw data to.
	 *              Pointer must point to an array of (at least) three elements, where:
	 *              ptr[0] corresponds to X-axis
	 *              ptr[1] corresponds to Y-axis
	 *              ptr[2] corresponds to Z-axis
	 * @retval      0 in case of success, an error code otherwise
	 */
	virtual int Get_G_AxesRaw(int16_t*) = 0;

	/**
	 * @brief       Get gyroscope's current sensitivity [mdps/LSB]
	 * @param[out]  Pointer to where the gyroscope's sensitivity is stored to
	 * @retval      0 in case of success, an error code otherwise
	 */
	virtual int Get_G_Sensitivity(float*) = 0;
	
	/**
	 * @brief       Get gyroscope's current output data rate [Hz]
	 * @param[out]  Pointer to where the gyroscope output data rate is stored to
	 * @retval      0 in case of success, an error code otherwise
	 */
	virtual int Get_G_ODR(float*) = 0;

	/**
	 * @brief      Set gyroscope's output data rate
	 * @param[in]  New value for gyroscope's output data rate in [Hz]
	 * @retval     0 in case of success, an error code otherwise
	 */
	virtual int Set_G_ODR(float) = 0;
	
	/**
	 * @brief       Get gyroscope's full scale value
	 *              i.e. min/max measurable value [dps]
	 * @param[out]  Pointer to where the gyroscope full scale value is stored to
	 * @retval      0 in case of success, an error code otherwise
	 */
	virtual int Get_G_FS(float*) = 0;
	
	/**
	 * @brief      Set gyroscope's full scale value
	 *             i.e. min/max measurable value
	 * @param[in]  New full scale value for gyroscope in [dps]
	 * @retval     0 in case of success, an error code otherwise
	 */
	virtual int Set_G_FS(float) = 0;
};

#endif /* __GYRO_SENSOR_CLASS_H */
