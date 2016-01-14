#!/usr/bin/env python
from lxml import etree
from lxml import objectify
from copy import deepcopy
import sys
SLOT_SIZE_LBA=40000
GAP_LBA=50

def generate_xml(fn, images, slot_size, gap):
    f = open("template.xml")
    tree = etree.parse(f)
    f.close()
    tree.getroot().text="\n"
    tree.getroot().insert(0, etree.Comment("\n\n\nThis file is autogenerated by %s, please do not modify manually!\n\n\n"%(sys.argv[0])))
    tree.getroot()[0].tail="\n  "
    os_image = list(tree.getroot().iter("os_image"))[0]
    START_LBA = gap
    first_image = True
    for attr in images:
        if not first_image:
            # duplicate the template's os_image to create another one
            os_image_copy = deepcopy(os_image)
            os_image.getparent().append(os_image_copy)
            os_image = os_image_copy
        # not sure if there is no easiest way of doing this..
        list(os_image.iter("image_attributes"))[0].text=str(attr)
        list(os_image.iter("starting_LBA_in_512_byte_blocks"))[0].text=str(START_LBA)
        START_LBA += slot_size
        first_image = False
    f = open(fn, "w")
    f.write(etree.tostring(tree))
    f.close()
generate_xml("FASTBOOT.XML", [ 0x1, 0xd, 0xf ], SLOT_SIZE_LBA, GAP_LBA)
generate_xml("COMBINED.XML", [ 0x1, 0x11 ], SLOT_SIZE_LBA, GAP_LBA)
# workaround bug in IAFW that wont boot correct osimage after os recovery
# we put 0xd osip entry pointing which is the fallback that will always boot
generate_xml("DROIDBOOT.XML", [ 0xd ], 0, GAP_LBA)

generate_xml("MOS_OTA.XML", [ 0x1 ], SLOT_SIZE_LBA, 0)
generate_xml("FASTBOOT_OTA.XML", [ 0xf ], SLOT_SIZE_LBA, 0)
generate_xml("COMBINED_OTA.XML", [ 0x11 ], SLOT_SIZE_LBA, 0)
generate_xml("DROIDBOOT_OTA.XML", [ 0xf ], SLOT_SIZE_LBA, 0)
generate_xml("RECOVERY_OTA.XML", [ 0xd ], SLOT_SIZE_LBA, 0)
