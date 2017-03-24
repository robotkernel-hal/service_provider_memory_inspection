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

#include "robotkernel/service_provider_base.h"
#include "robotkernel/service_provider_intf.h"
#include "robotkernel/service.h"
#include "robotkernel/kernel.h"
#include "robotkernel/log_base.h"

#include "service_provider/memory_inspection/base.h"

namespace service_provider {
    namespace memory_inspection {
        // forward declaration
        class handler;

        class provider : public robotkernel::service_provider_base<handler> {
            public:
                //! default construction
                provider()
                    : service_provider_base("memory_inspection") {};
        };

        class handler : public robotkernel::log_base {
            public:
                typedef std::shared_ptr<service_provider::memory_inspection::base> sp_mi_base_t;
                sp_mi_base_t _instance;

                //! handler construction
                handler(const robotkernel::sp_service_requester_t& req);

                //! handler destruction
                ~handler();

                //! service callback read memory
                /*!
                 * \param request service request data
                 * \parma response service response data
                 * \return success
                 */
                int service_read_memory(const robotkernel::service_arglist_t& request, 
                        robotkernel::service_arglist_t& response);
                static const std::string service_definition_read_memory;

                //! service callback write memory
                /*!
                 * \param request service request data
                 * \parma response service response data
                 * \return success
                 */
                int service_write_memory(const robotkernel::service_arglist_t& request, 
                        robotkernel::service_arglist_t& response);
                static const std::string service_definition_write_memory;

                //! service callback get_info memory
                /*!
                 * \param request service request data
                 * \parma response service response data
                 * \return success
                 */
                int service_get_memory_areas(const robotkernel::service_arglist_t& request, 
                        robotkernel::service_arglist_t& response);
                static const std::string service_definition_get_memory_areas;
        };

    }; // namespace memory_inspection

}; // namespace service_provider

#endif // __SERVICE_PROVIDER__MEMORY_INSPECTION__PROVIDER_H__

