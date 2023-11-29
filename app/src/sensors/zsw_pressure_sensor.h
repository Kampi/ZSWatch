/*
 * This file is part of ZSWatch project <https://github.com/jakkra/ZSWatch/>.
 * Copyright (c) 2023 Jakob Krantz.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <zephyr/drivers/sensor.h>

#include <math.h>

#include "../../drivers/sensor/bmp581/bosch_bmp581.h"

inline __attribute__((always_inline)) float zsw_pressure_get_relative_height_m(float relative_pressure,
                                                                               float new_pressure,
                                                                               float temperature)
{
    return ((powf((relative_pressure / new_pressure), 1.f / 5.257f) - 1.f) * (temperature + 273.15f)) / 0.0065f;
}

int zsw_pressure_sensor_init(void);

int zsw_pressure_sensor_set_odr(uint8_t odr);

int zsw_pressure_sensor_get_pressure(float *pressure);

int zsw_pressure_sensor_get_temperature(float *temperature);