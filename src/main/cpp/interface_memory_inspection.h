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
#include "robotkernel/module.h"
#include "robotkernel/interface_intf.h"
#include "robotkernel/interface_base.h"
#include "module_intf.h"

#include <list>

#include <stdint.h>
#include <ln_cppwrapper.h>

namespace interface_memory_inspection {

#define LN_UNREGISTER_SERVICE_IN_BASE_DETOR
#ifdef BUILD_INTERFACE_MEMORY_INSPECTION
#include "interface_memory_inspection_ln_messages.h"
#else
#include <interface_memory_inspection/interface_memory_inspection_ln_messages.h>
#endif
#undef LN_UNREGISTER_SERVICE_IN_BASE_DETOR

class memory_inspection : 
    public robotkernel::interface_base, 
    public ln_service_read_base,
    public ln_service_write_base,
    public ln_service_get_info_base
{
    public:
        //! default construction
        /*!
         * \param node configuration node
         */
        memory_inspection(const YAML::Node& node);

        int on_read(ln::service_request& req, ln_service_robotkernel_memory_inspection_read& svc);
        int on_write(ln::service_request& req, ln_service_robotkernel_memory_inspection_write& svc);
	    int on_get_info(ln::service_request& req, ln_service_robotkernel_memory_inspection_get_info& svc);
};

} // namespace interface

#endif // __INTERFACE_MEMORY_INSPECTION_H__

