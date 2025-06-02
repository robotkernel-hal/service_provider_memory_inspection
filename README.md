# Service Provider Memory Inspection

That service provider suppliles services for all robotkernel modules
with support for memory inspection devices. The service provider will
provide acyclic calls to access the memory on the devices.

## Usage

No specific configuration is needed for the service provider. The
robotkernel just needs to know which service provider to load. To load
der *service_provider_memory_inspection* just add it to your config
file.

```yaml
service_providers:
- name: mi_sp
  so_file: libservice_provider_memory_inspection.so
```

## Services

**read_memory**
:   Reads memory from specified address *data_adr* with length
    *data_len* and return the *data*. On error, the *error_message*
    field will be filled with the error cause.

```yaml
request:
- uint64_t: data_adr
- uint32_t: data_len
response:
- vector/uint8_t: data
- string: error_message
```

**write_memory**
:   Writes *data* to address *data_adr*. The length is implied from the
    length of *data* supplied. On error, the *error_message* field will
    be filled with the error cause.

```yaml
request:
- uint64_t: data_adr
- vector/uint8_t: data
response:
- string: error_message
```

**get_memory_areas**
:   Returns a list with all available memory regions. They consist of a
    start *address* and a *length* in bytes. On error, the
    *error_message* field will be filled with the error cause.

```yaml
response:
- vector/uint64_t: address
- vector/uint32_t: length
- string: error_message
```

All of these services will be available through a robotkernel brigdge
(e.g. [bridge_ln](robotkernel-5/bridge_ln "wikilink"),
[bridge_jsonrpc](robotkernel-5/bridge_jsonrpc "wikilink"),
[bridge_cli](robotkernel-5/bridge_cli "wikilink"), \...)

[Serivice Provider Memory Inspection](Category:Robotkernel-5 "wikilink")

## Implementation specific

Either use conan to add the needed include and library pathes to you project or use pkg-config with the 
provided pkc-file.

First thing to do is to include the base header:

```c++
#include "service_provider/memory_inspection/base.h"

```

After this you have to dervive a class from the `service_provider::memory_inspection::base` class 
and implement the corresponding memory inspection functions.

```c++
class my_class : public service_provider::memory_inspection::base {
    public:
        my_class() { /* init things here */ }

        //! retreave all readable/writeable memory areas
        /*!
         * \param areas list of areas
         */
        virtual void get_memory_areas(area_list_t& areas) { /* fill areas with available memory ranges */ }

        //! read memory
        /*!
         * \param address start address
         * \param data read data
         */
        virtual void read_memory(const uint64_t& address, data_t& data) { /* fill data beginning from addresss */ }

        //! write memory
        /*!
         * \param address start address
         * \param data data to write
         */
        virtual void write_memory(const uint64_t& address, const data_t& data) { /* write data beginning at address */ }
};
```

