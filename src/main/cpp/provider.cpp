//! robotkernel module class
/*!
 * author: Robert Burger
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

#include "provider.h"
#include "robotkernel/exceptions.h"

SERVICE_PROVIDER_DEF(memory_inspection, service_provider::memory_inspection::provider);

using namespace std;
using namespace std::placeholders;
using namespace robotkernel;
using namespace service_provider;
using namespace string_util;

memory_inspection::handler::handler(const robotkernel::sp_service_interface_t& req) 
    : log_base("memory_inspection", req->owner + "." + req->device_name + ".memory_inspection") {
    robotkernel::kernel& k = *robotkernel::kernel::get_instance();

    _instance = std::dynamic_pointer_cast<service_provider::memory_inspection::base>(req);
    if (!_instance)
        throw str_exception("wrong base class");

    k.add_service(_instance->owner, _instance->device_name + ".read_memory", 
            service_definition_read_memory,
            std::bind(&handler::service_read_memory, this, _1, _2));
    k.add_service(_instance->owner, _instance->device_name + ".write_memory", 
            service_definition_write_memory,
            std::bind(&handler::service_write_memory, this, _1, _2));
    k.add_service(_instance->owner, _instance->device_name + ".get_memory_areas", 
            service_definition_get_memory_areas,
            std::bind(&handler::service_get_memory_areas, this, _1, _2));
}

//! handler destruction
memory_inspection::handler::~handler() {
    kernel& k = *kernel::get_instance();

    stringstream base;
    k.remove_service(_instance->owner, _instance->device_name + ".read_memory");
    k.remove_service(_instance->owner, _instance->device_name + ".write_memory");
    k.remove_service(_instance->owner, _instance->device_name + ".get_memory_areas");
};

//! service callback read memory
/*!
 * \param request service request data
 * \parma response service response data
 * \return success
 */
int memory_inspection::handler::service_read_memory(
        const robotkernel::service_arglist_t& request, 
        robotkernel::service_arglist_t& response) {
#define READ_REQ_DATA_ADR	0
#define READ_REQ_DATA_LEN	1
    uint64_t address  = request[READ_REQ_DATA_ADR];
    uint32_t length   = request[READ_REQ_DATA_LEN];
    data_t data(length);

    // response values
    string error_message = "";
    std::vector<rk_type> data_resp;

    try {
        _instance->read_memory(address, data);
        data_resp.assign(data.begin(), data.end());
    } catch (std::exception& e) {
        error_message = e.what();
    }

#define READ_RESP_DATA			0
#define READ_RESP_ERROR_MESSAGE	1
    response.resize(2);
    response[READ_RESP_DATA] = data_resp;
    response[READ_RESP_ERROR_MESSAGE] = error_message;

    return 0;
}

const std::string memory_inspection::handler::service_definition_read_memory =
"request:\n"
"   uint64_t: data_adr\n"
"   uint32_t: data_len\n"
"response:\n"
"   vector/uint8_t: data\n"
"   string: error_message\n";

//! service callback write memory
/*!
 * \param request service request data
 * \parma response service response data
 * \return success
 */
int memory_inspection::handler::service_write_memory(
        const robotkernel::service_arglist_t& request, 
        robotkernel::service_arglist_t& response) {
#define WRITE_REQ_DATA_ADR	0
#define WRITE_REQ_DATA_LEN	1
#define WRITE_REQ_DATA      2
    uint64_t address                = request[WRITE_REQ_DATA_ADR];
    std::vector<rk_type> data_req   = request[WRITE_REQ_DATA];
    data_t data;
    data.assign(data_req.begin(), data_req.end());

    // response values
    string error_message = "";

    try {
        _instance->write_memory(address, data);
    } catch (std::exception& e) {
        error_message = e.what();
    }

#define WRITE_RESP_ERROR_MESSAGE	0
    response.resize(1);
    response[WRITE_RESP_ERROR_MESSAGE] = error_message;

    return 0;
}

const std::string memory_inspection::handler::service_definition_write_memory =
"request:\n"
"   uint64_t: data_adr\n"
"   vector/uint8_t: data\n"
"response:\n"
"   string: error_message\n";

//! service callback get_info memory
/*!
 * \param request service request data
 * \parma response service response data
 * \return success
 */
int memory_inspection::handler::service_get_memory_areas(const robotkernel::service_arglist_t& request, 
        robotkernel::service_arglist_t& response) {
    // response values
    string error_message = "";
    std::vector<rk_type> address;
    std::vector<rk_type> length;

    try {
        area_list_t areas;
        _instance->get_memory_areas(areas);

        for (area_list_t::iterator it = areas.begin(); 
                it != areas.end(); ++it) {
            address.push_back(it->address);
            length.push_back(it->length);
        }
    } catch (std::exception& e) {
        error_message = e.what();
    }

#define MEMORY_AREA_RESP_ADDRESS        0
#define MEMORY_AREA_RESP_LENGTH         1
#define MEMORY_AREA_RESP_ERROR_MESSAGE	2
    response.resize(3);
    response[MEMORY_AREA_RESP_ADDRESS]       = address;
    response[MEMORY_AREA_RESP_LENGTH]        = length;
    response[MEMORY_AREA_RESP_ERROR_MESSAGE] = error_message;

    return 0;
}

const std::string memory_inspection::handler::service_definition_get_memory_areas = 
"response:\n"
"   vector/uint64_t: address\n"
"   vector/uint32_t: length\n"
"   string: error_message\n";

