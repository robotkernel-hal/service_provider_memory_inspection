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

#ifndef __INTERFACE_MEMORY_INSPECTION_H__
#define __INTERFACE_MEMORY_INSPECTION_H__

#include "robotkernel/kernel.h"
#include "robotkernel/interface_base.h"

namespace interface_memory_inspection {

class memory_inspection : public robotkernel::interface_base {
    public:
        //! default construction
        /*!
         * \param node configuration node
         */
        memory_inspection(const YAML::Node& node);

        //! service callback read memory
        /*!
         * \param message service message
         * \return success
         */
        int service_read(YAML::Node& message);
        static const std::string service_definition_read;
        
        //! service callback write memory
        /*!
         * \param message service message
         * \return success
         */
        int service_write(YAML::Node& message);
        static const std::string service_definition_write;
        
        //! service callback get_info memory
        /*!
         * \param message service message
         * \return success
         */
        int service_get_info(YAML::Node& message);
        static const std::string service_definition_get_info;
};

} // namespace interface

#endif // __INTERFACE_MEMORY_INSPECTION_H__

