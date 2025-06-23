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

#ifndef __SERVICE_PROVIDER__MEMORY_INSPECTION__PROVIDER_H__
#define __SERVICE_PROVIDER__MEMORY_INSPECTION__PROVIDER_H__

// Robotkernel includes
#include "robotkernel/service_provider_base.h"
#include "robotkernel/service.h"
#include "robotkernel/log_base.h"

// Service provider includes
#include "service_provider/memory_inspection/base.h"
#include "service_definitions.h"

namespace service_provider {
namespace memory_inspection {

// forward declaration
class handler;

class provider : public robotkernel::service_provider_base<handler, base> {
    public:
        //! default construction
        provider(const std::string& name)
            : service_provider_base(name, "memory_inspection") {};
};

class handler : 
    public robotkernel::log_base,
    public svc_base_read_memory,
    public svc_base_write_memory,
    public svc_base_get_memory_areas
{
    public:
        typedef std::shared_ptr<service_provider::memory_inspection::base> sp_mi_base_t;
        sp_mi_base_t _instance;

        //! handler construction
        handler(const robotkernel::sp_service_interface_t& req);

        //! handler destruction
        ~handler() {}

        //! svc_read_memory
        /*!
         * \param[in]   req     Service request data.
         * \param[out]  resp    Service response data.
         */
        virtual void svc_read_memory(const struct svc_req_read_memory& req, struct svc_resp_read_memory& resp);

        //! svc_write_memory
        /*!
         * \param[in]   req     Service request data.
         * \param[out]  resp    Service response data.
         */
        virtual void svc_write_memory(const struct svc_req_write_memory& req, struct svc_resp_write_memory& resp);

        //! svc_get_memory_areas
        /*!
         * \param[in]   req     Service request data.
         * \param[out]  resp    Service response data.
         */
        virtual void svc_get_memory_areas(const struct svc_req_get_memory_areas& req, struct svc_resp_get_memory_areas& resp);
};

}; // namespace memory_inspection
}; // namespace service_provider

#endif // __SERVICE_PROVIDER__MEMORY_INSPECTION__PROVIDER_H__

