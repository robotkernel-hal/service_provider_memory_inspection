//! robotkernel module class
/*!
 * author: Robert Burger
 *
 * $Id$
 */

/*
 * This file is part of robotkernel.
 *
 * robotkernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * robotkernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with robotkernel.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __INTERFACE_MEMORY_INSPECTION_MODULE_INTF_H__
#define __INTERFACE_MEMORY_INSPECTION_MODULE_INTF_H__

#include "robotkernel/module_intf.h"

// -----------------------------------------------------------------------------
// get process data pointers
//
typedef struct memory {
    uint32_t slave_id; //! [in]     device slave_id
    uint64_t address;
    uint32_t length;
    uint8_t *data;
} memory_t;

#define MOD_REQUEST_MEMORY_INSPECTION_MAGIC  0x20
#define MOD_REQUEST_MEMORY_INSPECTION(x, s) \
    __MOD_REQUEST((MOD_REQUEST_MEMORY_INSPECTION_MAGIC), (x), __MOD_REQUEST_TYPE(s))
#define MOD_REQUEST_MEMORY_READ            MOD_REQUEST_MEMORY_INSPECTION(0x0001, memory_t)
#define MOD_REQUEST_MEMORY_WRITE           MOD_REQUEST_MEMORY_INSPECTION(0x0002, memory_t)
#define MOD_REQUEST_MEMORY_GET_INFO        MOD_REQUEST_MEMORY_INSPECTION(0x0003, memory_t)

#endif // __INTERFACE_MEMORY_INSPECTION_MODULE_INTF_H__

