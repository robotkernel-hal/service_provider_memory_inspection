//! robotkernel service provider memory inspection
/*!
 * author: Robert Burger
 */

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab:

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

#ifndef __SERVICE_PROVIDER__MEMORY_INSPECTION__BASE__H__
#define __SERVICE_PROVIDER__MEMORY_INSPECTION__BASE__H__

#include <list>

#include "robotkernel/service_interface.h"

namespace service_provider {

    namespace memory_inspection {

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

    }; // namespace memory_inspection

}; // namespace service_provider

#endif // __SERVICE_PROVIDER__MEMORY_INSPECTION__BASE__H__

