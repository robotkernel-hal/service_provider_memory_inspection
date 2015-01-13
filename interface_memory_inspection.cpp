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
#undef BUILD_DATE
#undef PACKAGE
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#undef VERSION
#include "config.h"

using namespace std;
using namespace robotkernel;
using namespace interface;
        
//! default construction
/*!
 * \param mod_name module name to register for
 */
memory_inspection::memory_inspection(const std::string& mod_name, 
        const std::string& dev_name, const int& slave_id) 
    : _mod_name(mod_name), _dev_name(dev_name), _slave_id(slave_id) {
    kernel& k = *kernel::get_instance();
    if (!k.clnt)
        throw str_exception("[interface_sercos_protocol|%s] no ln_connection!\n", 
                mod_name.c_str());
    
    stringstream base;
    base << k.clnt->name << "." << _mod_name << "." << _dev_name << ".";

    register_read(k.clnt, base.str() + "memory_inspection.read");
    register_write(k.clnt, base.str() + "memory_inspection.write");
}


int memory_inspection::on_read(ln::service_request& req, ln_service_robotkernel_memory_inspection_read& svc) {
    memory_t memory_req;
    memory_req.slave_id = _slave_id;
    memory_req.address  = svc.req.data_adr;
    memory_req.length   = svc.req.data_len;
    memory_req.data     = new uint8_t[svc.req.data_len];
    int ret = kernel::request_cb(_mod_name.c_str(), MOD_REQUEST_MEMORY_READ, (void *)&memory_req);

    if(ret == -1) {
	    svc.resp.data = NULL;
	    svc.resp.data_len = 0;
    } else {
	    svc.resp.data = memory_req.data;
	    svc.resp.data_len = memory_req.length;
    }
    req.respond();

    delete[] memory_req.data;

    return 0;
}

int memory_inspection::on_write(ln::service_request& req, ln_service_robotkernel_memory_inspection_write& svc) {
    memory_t memory_req;
    memory_req.slave_id = _slave_id;
    memory_req.address  = svc.req.data_adr;
    memory_req.length   = svc.req.data_len;
    memory_req.data     = svc.req.data;
    int ret = kernel::request_cb(_mod_name.c_str(), MOD_REQUEST_MEMORY_WRITE, (void *)&memory_req);

    req.respond();

    return 0;
}
	    
int memory_inspection::on_get_info(ln::service_request& req, ln_service_robotkernel_memory_inspection_get_info& svc) {
    memory_t memory_req;
    memory_req.slave_id = _slave_id;
    memory_req.address  = 0;
    memory_req.length   = 0;
    memory_req.data     = NULL;
    int ret = kernel::request_cb(_mod_name.c_str(), MOD_REQUEST_MEMORY_GET_INFO, (void *)&memory_req);

    if (ret == -1) {
        svc.resp.base_adr = 0;
        svc.resp.len = 0;
    } else {
        svc.resp.base_adr = memory_req.address;
        svc.resp.len = memory_req.length;
    }

    req.respond();

    return 0;
}


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

//! interface register
/*!
 * \param mod_name module name to register
 * \return interface handle
 */
INTERFACE_HANDLE intf_register(const char *mod_name, const char *dev_name, int slave_id) {
    memory_inspection *s = NULL;

    klog(interface_info, INTFNAME "%s: build by: " BUILD_USER "@" BUILD_HOST "\n", mod_name);
    klog(interface_info, INTFNAME "%s: build date: " BUILD_DATE "\n", mod_name);

    // parsing sercos ring configuration
    try {
        s = new memory_inspection(string(mod_name), string(dev_name), slave_id);
    } catch(exception& e) {
        klog(interface_error, INTFNAME "%s: error constructing intercae:\n%s", mod_name, e.what());
        goto ErrorExit;
    }

    return (INTERFACE_HANDLE)s;

ErrorExit:
    if (s)
        delete s;

    return (INTERFACE_HANDLE)NULL;
}

//! interface unregister
/*!
 * \param hdl interface handle
 */
void intf_unregister(INTERFACE_HANDLE hdl) {
    // cast struct
    memory_inspection *s = (memory_inspection *)hdl;

    if (s)
        delete s;
}

#if 0
{
#endif
#ifdef __cplusplus
}
#endif

