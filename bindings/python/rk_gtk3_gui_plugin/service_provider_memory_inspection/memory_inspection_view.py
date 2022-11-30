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
from __future__ import absolute_import
from __future__ import division

import os
import gi
gi.require_version('Gtk', '3.0')
gi.require_version('GLib', '2.0')
from gi.repository import Gtk
from gi.repository import GObject
import traceback
import math

import helpers

from .memory_inspection_device import *

class memory_inspection_view(helpers.service_provider_view, helpers.builder_base):
    def __init__(self, parent, container):
        fn = os.path.join(os.path.dirname(__file__), 'memory_inspection_view.ui')
        helpers.builder_base.__init__(self, fn, 'memory_inspection_box', 'pdi_adjustment')
        helpers.service_provider_view.__init__(self, parent.app, parent, self.memory_inspection_box, 'get_memory_areas')


        refresh_spin = self.refresh_spin
        refresh_spin.adjustment = self.pdi_adjustment

        # remove all previous content of the container
        container.foreach(self.remove)
        container.pack_start(self.memory_inspection_box, True, True, 0)

        #self.kv_refresh_btn.connect("clicked", self.on_refresh)

        fd = helpers.gui_utils.get_monospace_font_description()
        self.mem_tv.modify_font(fd)

        self.timer = 0
        self.timer_id = None
        self.is_running = False

        self.last_hex = {}
        self.devices = {}
        self.current_device = None

    def show(self, module, device):
        helpers.service_provider_view.show(self)
        self.last_hex = {}

        device_key = (module, device)

        if device_key not in self.devices:
            self.devices[device_key] = memory_inspection_device(self.app.clnt,
                    "{}.{}.{}.memory_inspection".format(self.parent.name, module, device))

        if self.current_device != device_key:
            if self.current_device:
                self.devices[self.current_device].abort = True

            self.current_device = device_key

            if len(self.devices[self.current_device].buf) > 0:
                self.update()
            else:
                self.do_refresh()

    def update(self):
        dev = self.devices[self.current_device]
        self.show_data("mem_tv", dev.buf)

    def do_refresh(self):
        if self.current_device is None:
            return False

        self.devices[self.current_device].update(0, 4096, self)

    def generate_hex_listing(self, data, line_len=16):
        text = []
        if len(data) > 0:
            ml = 2 * int(math.ceil(math.log(len(data)) / math.log(2) / 8.))
            ml = max(ml, 4)
            o = 0
            while o < len(data):
                line = "0x%0*x  %s " % (ml, o, " ".join(["%02x" % f for f in data[o:o+line_len]]))
                for c in data[o:o+line_len]:
                    if c > 32 and c < 126:
                        line += "%c" %c
                    else:
                        line += "."
                text.append(line)
                o += line_len
        return "\n".join(text)

    def show_data(self, tv_name, data):
        hex = self.generate_hex_listing(data)
        tv = getattr(self, tv_name)
        b = tv.get_buffer()
        b.set_text(hex)
        return

    def show_exception(self, text=None, reraise=True):
        traceback.print_exc()

        dlg = Gtk.MessageDialog(
            self.app.window,
            Gtk.DialogFlags.DESTROY_WITH_PARENT,
            Gtk.MessageType.ERROR,
            buttons=Gtk.ButtonsType.OK)

        if text is None:
            stack = traceback.format_exc().split("\n")
            stack = "\n".join(stack[2:])
            stack = stack.replace("<", "&lt;").replace(">", "&gt;")
            text = 'exception in\n<span weight="bold" font_family="monospace">%s</span>' % (stack, )

        dlg.label.set_line_wrap(False)
        dlg.set_markup(text)
        dlg.connect("delete-event", lambda w: w.destroy())
        dlg.connect("response", lambda w, rid: w.destroy())
        dlg.show()
        raise


    def on_refresh_btn_clicked(self, btn):
        self.do_refresh()

    def on_pdi_adjustment_value_changed(self, adj):
        v = adj.get_value()
        self.timer = int(v / 0.1) * 0.1
        if self.timer_id is not None:
            GObject.source_remove(self.timer_id)
            self.timer_id = None
        if self.timer > 0:
            self.timer_id = GObject.timeout_add(int(v * 1000), self.on_timeout)

    def on_timeout(self):
        if self.timer <= 0:
            return False
        self.do_refresh()
        return True
