//! robotkernel service provider memory inspection
/*!
 * author: Robert Burger <robert.burger@dlr.de>
 */

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab:

/*
 * This file is part of service_provider_memory_inspection.
 *
 * service_provider_memory_inspection is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * 
 * service_provider_memory_inspection is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with service_provider_memory_inspection; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef SERVICE_PROVIDER_MEMORY_INSPECTION__BASE_H
#define SERVICE_PROVIDER_MEMORY_INSPECTION__BASE_H

#include <list>

#include "robotkernel/service_interface.h"

namespace service_provider_memory_inspection {

typedef struct memory {
    uint64_t address;
    uint32_t length;
} memory_t;

typedef std::list<memory_t> area_list_t;
typedef std::vector<uint8_t> data_t;

class base : public robotkernel::service_interface {
    public:
        //! construction
        base(std::string owner, std::string service_prefix)
            : robotkernel::service_interface(owner, service_prefix + ".memory_inspection") {};

        //! destruction
        virtual ~base() = 0;

        //! retreave all readable/writeable memory areas
        /*!
         * \param areas list of areas
         */
        virtual void get_memory_areas(area_list_t& areas) = 0;

        //! read memory
        /*!
         * \param address start address
         * \param data read data
         */
        virtual void read_memory(const uint64_t& address, data_t& data) = 0;

        //! write memory
        /*!
         * \param address start address
         * \param data data to write
         */
        virtual void write_memory(const uint64_t& address, const data_t& data) = 0;
};

inline base::~base() { }

}; // namespace service_provider_memory_inspection

#endif // ERVICE_PROVIDER_MEMORY_INSPECTION__BASE_H

