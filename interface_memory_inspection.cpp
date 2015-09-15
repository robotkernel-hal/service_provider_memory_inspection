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
    if (!k.clnt)
        throw str_exception("[interface_sercos_protocol|%s] no ln_connection!\n", 
                mod_name.c_str());
    
    stringstream base;
    base << k.clnt->name << "." << mod_name << "." << dev_name << ".";

    register_read(k.clnt, base.str() + "memory_inspection.read");
    register_write(k.clnt, base.str() + "memory_inspection.write");
}


int memory_inspection::on_read(ln::service_request& req, ln_service_robotkernel_memory_inspection_read& svc) {
    memory_t memory_req;
    memory_req.slave_id = slave_id;
    memory_req.address  = svc.req.data_adr;
    memory_req.length   = svc.req.data_len;
    memory_req.data     = new uint8_t[svc.req.data_len];
    
    svc.resp.data = NULL;
    svc.resp.data_len = 0;
    try {
	    int ret = kernel::request_cb(mod_name.c_str(), MOD_REQUEST_MEMORY_READ, (void *)&memory_req);
	    if(ret == -1)
		    throw str_exception("MOD_REQUEST_MEMORY_READ failed!");

	    svc.resp.data = memory_req.data;
	    svc.resp.data_len = memory_req.length;
	    
	    svc.resp.error_message_len = 0;
	    req.respond();
    }
    catch(const exception& e) {
	    ln::string_buffer err(&svc.resp.error_message, e.what());
	    req.respond();
    }

    delete[] memory_req.data;

    return 0;
}

int memory_inspection::on_write(ln::service_request& req, ln_service_robotkernel_memory_inspection_write& svc) {
    memory_t memory_req;
    memory_req.slave_id = slave_id;
    memory_req.address  = svc.req.data_adr;
    memory_req.length   = svc.req.data_len;
    memory_req.data     = svc.req.data;
    try {
	    int ret = kernel::request_cb(mod_name.c_str(), MOD_REQUEST_MEMORY_WRITE, (void *)&memory_req);
	    if(ret == -1)
		    throw str_exception("MOD_REQUEST_MEMORY_WRITE failed!");

	    svc.resp.error_message_len = 0;
	    req.respond();
    }
    catch(const exception& e) {
	    ln::string_buffer err(&svc.resp.error_message, e.what());
	    req.respond();
    }
    
    return 0;
}
	    
int memory_inspection::on_get_info(ln::service_request& req, ln_service_robotkernel_memory_inspection_get_info& svc) {
    memory_t memory_req;
    memory_req.slave_id = slave_id;
    memory_req.address  = 0;
    memory_req.length   = 0;
    memory_req.data     = NULL;
    
    svc.resp.base_adr = 0;
    svc.resp.len = 0;
    try {
	    int ret = kernel::request_cb(mod_name.c_str(), MOD_REQUEST_MEMORY_GET_INFO, (void *)&memory_req);
	    
	    if (ret == -1) 
		    throw str_exception("MOD_REQUEST_GET_INFO failed!");

	    svc.resp.base_adr = memory_req.address;
	    svc.resp.len = memory_req.length;
	    
	    svc.resp.error_message_len = 0;
	    
	    req.respond();
    }
    catch(const exception& e) {
	    ln::string_buffer err(&svc.resp.error_message, e.what());
	    req.respond();
    }


    return 0;
}

