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

#include "interface_memory_inspection.h"
#include "robotkernel/exceptions.h"
#include "module_intf.h"

INTERFACE_DEF(memory_inspection, interface_memory_inspection::memory_inspection)

using namespace std;
using namespace robotkernel;
using namespace interface_memory_inspection;
        
//! default construction
/*!
 * \param node configuration node
 */
memory_inspection::memory_inspection(const YAML::Node& node)
    : interface_base("memory_inspection", node) {
    kernel& k = *kernel::get_instance();
    
    stringstream base;
    base << mod_name << "." << dev_name << "." << ".memory_inspection.";
    
    k.add_service(mod_name, base.str() + "read", service_definition_read,
            boost::bind(&memory_inspection::service_read, this, _1));
    k.add_service(mod_name, base.str() + "write", service_definition_write,
            boost::bind(&memory_inspection::service_write, this, _1));
    k.add_service(mod_name, base.str() + "get_info",service_definition_get_info,
            boost::bind(&memory_inspection::service_get_info, this, _1));
}

//! service callback read memory
/*!
 * \param message service message
 * \return success
 */
int memory_inspection::service_read(YAML::Node& message) {
    memory_t memory_req;
    memory_req.slave_id = slave_id;
    memory_req.address  = get_as<uint64_t>(message["request"], "data_adr");
    memory_req.length   = get_as<uint32_t>(message["request"], "data_len");

    std::vector<uint8_t> data;
    data.resize(memory_req.length);
    memory_req.data     = &data[0];
    
    // default response values
    message["response"]["data"] = data;
    message["response"]["error_message"] = "";

    int ret = kernel::request_cb(mod_name.c_str(), 
            MOD_REQUEST_MEMORY_READ, (void *)&memory_req);

    if (ret == -1) {
        message["response"]["error_message"] =
            "MOD_REQUEST_MEMORY_READ failed!";
        return 0;
    }

    message["response"]["data"] = data;

    return 0;
}

const std::string memory_inspection::service_definition_read =
    "request:\n"
    "   uint64_t: data_adr\n"
    "   uint32_t: data_len\n"
    "response:\n"
    "   uint8_t*: data\n"
    "   string: error_message\n";

//! service callback write memory
/*!
 * \param message service message
 * \return success
 */
int memory_inspection::service_write(YAML::Node& message) {
    memory_t memory_req;
    memory_req.slave_id = slave_id;
    memory_req.address  = get_as<uint64_t>(message["request"], "data_adr");
    memory_req.length   = get_as<uint32_t>(message["request"], "data_len");

    std::vector<uint8_t> data = get_as<std::vector<uint8_t> >(
            message["request"], "data");
    memory_req.data     = &data[0];
    
    // default response values
    message["response"]["error_message"] = "";

    int ret = kernel::request_cb(mod_name.c_str(), 
            MOD_REQUEST_MEMORY_WRITE, (void *)&memory_req);

    if (ret == -1) {
        message["response"]["error_message"] =
            "MOD_REQUEST_MEMORY_WRITE failed!";
        return 0;
    }

    return 0;
}

const std::string memory_inspection::service_definition_write =
    "request:\n"
    "   uint64_t: data_adr\n"
    "   uint32_t: data_len\n"
    "   uint8_t*: data\n"
    "response:\n"
    "   string: error_message\n";

	    
//int memory_inspection::on_get_info(ln::service_request& req, ln_service_robotkernel_memory_inspection_get_info& svc) {
//    memory_t memory_req;
//    memory_req.slave_id = slave_id;
//    memory_req.address  = 0;
//    memory_req.length   = 0;
//    memory_req.data     = NULL;
//    
//    svc.resp.base_adr = 0;
//    svc.resp.len = 0;
//    try {
//	    int ret = kernel::request_cb(mod_name.c_str(), MOD_REQUEST_MEMORY_GET_INFO, (void *)&memory_req);
//	    
//	    if (ret == -1) 
//		    throw str_exception("MOD_REQUEST_GET_INFO failed!");
//
//	    svc.resp.base_adr = memory_req.address;
//	    svc.resp.len = memory_req.length;
//	    
//	    svc.resp.error_message_len = 0;
//	    
//	    req.respond();
//    }
//    catch(const exception& e) {
//	    ln::string_buffer err(&svc.resp.error_message, e.what());
//	    req.respond();
//    }
//
//
//    return 0;
//}
        
//! service callback get_info memory
/*!
 * \param message service message
 * \return success
 */
int memory_inspection::service_get_info(YAML::Node& message) {
    return 0;
}

const std::string memory_inspection::service_definition_get_info = 
    "response:\n"
    "   uint64_t: base_adr\n"
    "   uint32_t: len\n"
    "   string: error_message\n";

