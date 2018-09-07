'''
(C) Robert Burger <robert.burger@dlr.de>

This file is part of Robotkernel-GUI.

Robotkernel-GUI is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Robotkernel-GUI is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Robotkernel-GUI.  If not, see <http://www.gnu.org/licenses/>.
'''

import time, traceback
import helpers

class memory_inspection_device(object, helpers.svc_wrapper):
    def __init__(self, clnt, prefix):
        helpers.svc_wrapper.__init__(self, clnt, prefix)
        self.clnt = clnt
        self.name = '.'.join(prefix.split('.')[:-1])
        self.buf = []
        self.abort = False

    def read_block(self, start_adr, end_adr, bs=16, view=None):
        if self.abort:
            return

        def cb_read_memory(starttime):
            #callback after canopen_protocol returned with data
            try:
                self.buf += self.svc_read_memory.resp.data.tolist()

                if view:
                    view.update()

                if (start_adr + bs) < end_adr:
                    self.read_block(start_adr + bs, end_adr, bs, view)
            except:
                print traceback.format_exc()
            return False

        #non-blocking read on data, with callback (see get_data)
        self.svc_read_memory.req.data_adr = start_adr
        self.svc_read_memory.req.data_len = min(bs, end_adr - start_adr)
        self.svc_read_memory.call_async()
        self.svc_read_memory.gobject_on_async_finish(cb_read_memory, time.time())

    def update(self, start_adr, end_adr, view):
        self.abort = False
        self.buf = []
        self.read_block(start_adr, end_adr, view=view)

