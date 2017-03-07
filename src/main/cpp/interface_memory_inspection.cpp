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

SERVICE_PROVIDER_DEF(memory_inspection, interface_memory_inspection::memory_inspection);

using namespace std;
using namespace std::placeholders;
using namespace robotkernel;
using namespace interface_memory_inspection;

const char* interface_memory_inspection::memory_inspection_sp_magic = "memory_inspection"; 

//! handler construction
memory_inspection_handler::memory_inspection_handler(
		std::string mod_name, std::string dev_name, int slave_id) : 
	log_base(mod_name, (mod_name + "." + dev_name + ".memory_inspection")), 
	mod_name(mod_name), dev_name(dev_name), slave_id(slave_id) {
	kernel& k = *kernel::get_instance();

	stringstream base;
	base << mod_name << "." << dev_name << ".memory_inspection.";

	k.add_service(mod_name, base.str() + "read", service_definition_read,
			std::bind(&memory_inspection_handler::service_read, this, _1, _2));
	k.add_service(mod_name, base.str() + "write", service_definition_write,
			std::bind(&memory_inspection_handler::service_write, this, _1, _2));
//	k.add_service(mod_name, base.str() + "get_info",service_definition_get_info,
//			std::bind(&memory_inspection_handler::service_get_info, this, _1, _2));
}

//! handler destruction
memory_inspection_handler::~memory_inspection_handler() {
	kernel& k = *kernel::get_instance();

	stringstream base;
	base << mod_name << "." << dev_name << ".memory_inspection.";
	k.remove_service(base.str() + "read");
	k.remove_service(base.str() + "write");
//	k.remove_service(base.str() + "get_info");
};

//! service callback read memory
/*!
 * \param request service request data
 * \parma response service response data
 * \return success
 */
int memory_inspection_handler::service_read(const robotkernel::service_arglist_t& request, 
		robotkernel::service_arglist_t& response) {
	memory_t memory_req;
	memory_req.slave_id = slave_id;
#define READ_REQ_DATA_ADR	0
#define READ_REQ_DATA_LEN	1
	memory_req.address  = request[READ_REQ_DATA_ADR];
	memory_req.length   = request[READ_REQ_DATA_LEN];

	// response values
	string error_message = "";
	std::vector<rk_type> data_resp;

	std::vector<uint8_t> data;
	data.resize(memory_req.length);
	memory_req.data     = &data[0];

	int ret = kernel::request_cb(mod_name.c_str(), 
			MOD_REQUEST_MEMORY_READ, (void *)&memory_req);

	if (ret == -1) {
		error_message = "MOD_REQUEST_MEMORY_READ failed!";
	} else 
		data_resp.assign(data.begin(), data.end());

#define READ_RESP_DATA			0
#define READ_RESP_ERROR_MESSAGE	1
	response.resize(2);
	response[READ_RESP_DATA] = data_resp;
	response[READ_RESP_ERROR_MESSAGE] = error_message;

	return 0;
}

const std::string memory_inspection_handler::service_definition_read =
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
int memory_inspection_handler::service_write(const robotkernel::service_arglist_t& request, 
		robotkernel::service_arglist_t& response) {
	memory_t memory_req;
	memory_req.slave_id = slave_id;
#define WRITE_REQ_DATA_ADR	0
#define WRITE_REQ_DATA_LEN	1
#define WRITE_REQ_DATA		2
	memory_req.address  			= request[WRITE_REQ_DATA_ADR];
	memory_req.length   			= request[WRITE_REQ_DATA_LEN];
	std::vector<rk_type> data_req 	= request[WRITE_REQ_DATA];

	// response
	string error_message = "";

	std::vector<uint8_t> data;
	data.assign(data_req.begin(), data_req.end());

	int ret = kernel::request_cb(mod_name.c_str(), 
			MOD_REQUEST_MEMORY_WRITE, (void *)&memory_req);

	if (ret == -1)
		error_message = "MOD_REQUEST_MEMORY_WRITE failed!";

#define WRITE_RESP_ERROR_MESSAGE	0
	response.resize(1);
	response[WRITE_RESP_ERROR_MESSAGE] = error_message;

	return 0;
}

const std::string memory_inspection_handler::service_definition_write =
"request:\n"
"   uint64_t: data_adr\n"
"   uint32_t: data_len\n"
"   vector/uint8_t: data\n"
"response:\n"
"   string: error_message\n";

//! service callback get_info memory
/*!
 * \param request service request data
 * \parma response service response data
 * \return success
 */
int memory_inspection_handler::service_get_info(const robotkernel::service_arglist_t& request, 
		robotkernel::service_arglist_t& response) {
	return 0;
}

const std::string memory_inspection_handler::service_definition_get_info = 
"response:\n"
"   uint64_t: base_adr\n"
"   uint32_t: len\n"
"   string: error_message\n";

