That service provider suppliles services for all robotkernel modules
with support for memory inspection devices. The service provider will
provide acyclic calls to access the memory on the devices.

# Configuration

No specific configuration is needed for the service provider. The
robotkernel just needs to know which service provider to load. To load
der *service_provider_memory_inspection* just add it to your config
file.

```yaml
service_providers:
- name: mi_sp
  so_file: libservice_provider_memory_inspection.so
```

# Services

read_memory
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

write_memory
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

get_memory_areas
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
