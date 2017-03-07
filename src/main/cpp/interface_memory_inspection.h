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

#include "robotkernel/service_provider_base.h"
#include "robotkernel/service_provider_intf.h"
#include "robotkernel/service.h"
#include "robotkernel/kernel.h"
#include "robotkernel/log_base.h"

namespace interface_memory_inspection {
	extern const char* memory_inspection_sp_magic;

	// forward declaration
	class memory_inspection_handler;

	class memory_inspection : 
		public robotkernel::service_provider_base<memory_inspection_handler> {
		public:
			//! default construction
			/*!
			 * \param node configuration node
			 */
			memory_inspection()
				: service_provider_base("memory_inspection") {};

			~memory_inspection() {};

			//! service provider magic 
			/*!
			 * \return return service provider magic string
			 */
			const char* get_sp_magic() 
			{ return memory_inspection_sp_magic; };
	};

	class memory_inspection_handler : public robotkernel::log_base {
		public:
			std::string mod_name;	//!< slave owner module
			std::string dev_name;	//!< service device name
			int slave_id;			//!< slave identifier

			//! handler construction
			memory_inspection_handler(std::string mod_name, std::string dev_name, 
					int slave_id);
			
			//! handler destruction
			~memory_inspection_handler();

			//! service callback read memory
			/*!
			 * \param request service request data
			 * \parma response service response data
			 * \return success
			 */
			int service_read(const robotkernel::service_arglist_t& request, 
					robotkernel::service_arglist_t& response);
			static const std::string service_definition_read;

			//! service callback write memory
			/*!
			 * \param request service request data
			 * \parma response service response data
			 * \return success
			 */
			int service_write(const robotkernel::service_arglist_t& request, 
					robotkernel::service_arglist_t& response);
			static const std::string service_definition_write;

			//! service callback get_info memory
			/*!
			 * \param request service request data
			 * \parma response service response data
			 * \return success
			 */
			int service_get_info(const robotkernel::service_arglist_t& request, 
					robotkernel::service_arglist_t& response);
			static const std::string service_definition_get_info;
	};

} // namespace interface

#endif // __INTERFACE_MEMORY_INSPECTION_H__

