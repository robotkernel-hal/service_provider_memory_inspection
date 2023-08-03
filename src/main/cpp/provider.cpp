//! robotkernel module class
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

#include "provider.h"
#include "service_definitions.h"

#include "robotkernel/exceptions.h"

SERVICE_PROVIDER_DEF(memory_inspection, service_provider::memory_inspection::provider);

using namespace std;
using namespace std::placeholders;
using namespace robotkernel;
using namespace service_provider;
using namespace string_util;

memory_inspection::handler::handler(const robotkernel::sp_service_interface_t& req) 
    : log_base(req->owner, "memory_inspection", req->device_name) 
{
    _instance = std::dynamic_pointer_cast<service_provider::memory_inspection::base>(req);
    if (!_instance)
        throw str_exception("wrong base class");

    add_svc_read_memory(_instance->owner, _instance->device_name + ".read_memory");
    add_svc_write_memory(_instance->owner, _instance->device_name + ".write_memory");
    add_svc_get_memory_areas(_instance->owner, _instance->device_name + ".get_memory_areas");
}

//! svc_read_memory
/*!
 * \param[in]   req     Service request data.
 * \param[out]  resp    Service response data.
 */
void memory_inspection::handler::svc_read_memory(const struct svc_req_read_memory& req, struct svc_resp_read_memory& resp) {
    resp.data.resize(req.data_len);

    try {
        _instance->read_memory(req.data_adr, resp.data);
    } catch (std::exception& e) {
        resp.error_message = e.what();
    }
}

//! svc_write_memory
/*!
 * \param[in]   req     Service request data.
 * \param[out]  resp    Service response data.
 */
void memory_inspection::handler::svc_write_memory(const struct svc_req_write_memory& req, struct svc_resp_write_memory& resp) {
    try {
        _instance->write_memory(req.data_adr, req.data);
    } catch (std::exception& e) {
        resp.error_message = e.what();
    }
}

//! svc_get_memory_areas
/*!
 * \param[in]   req     Service request data.
 * \param[out]  resp    Service response data.
 */
void memory_inspection::handler::svc_get_memory_areas(const struct svc_req_get_memory_areas& req, struct svc_resp_get_memory_areas& resp) {
    try {
        area_list_t areas;
        _instance->get_memory_areas(areas);

        for (area_list_t::iterator it = areas.begin(); it != areas.end(); ++it) {
            resp.address.push_back(it->address);
            resp.length.push_back(it->length);
        }
    } catch (std::exception& e) {
        resp.error_message = e.what();
    }
}

