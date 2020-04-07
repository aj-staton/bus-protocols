#!/usr/bin/env python3

# Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels

# This script consumes a VCD file on standard input. It assumes that it will
# contain the signal names data_wren, dataaddr, and data_value, which it will
# use to re-construct the contents of a VD003 flash memory and display them.

# This script is not robust against invalid inputs.

import sys

dvsym = None # data value
dwsym = None # data write enable
dasym = None # data address enable

# running values
dvval = 0
dwval = 0
daval = 0

# array to store re-constructed flash contents in 
mem = [0 for i in range(256 * 265)]

for line in ([x.strip() for x in l.split(" ") if x != ""] for l in sys.stdin):
    if (line[0] == "$var") and (line[4] == "data_value"):
        dvsym = line[3]

    elif (line[0] == "$var") and (line[4] == "data_wren"):
        dwsym = line[3]

    elif (line[0] == "$var") and (line[4] == "dataaddr"):
        dasym = line[3]

    elif line[0][1:] == dwsym:
        # 1 bit value for we
        prev = dwval
        dwval = int(line[0][0] == '1')
        if (prev == 1) and (dwval == 0):
            # rising edge of write enable
            mem[daval] = dvval
            #  print("write 0x%x to addr 0x%x" % (dvval, daval))

    elif len(line) < 2:
        continue

    elif line[1] == dvsym:
        dvval = int(line[0][1:], 2)

    elif line[1] == dasym:
        daval = int(line[0][1:], 2)

for pageno in range(256):
    header = False
    for rowstart in range(0, 256, 8):
        row = [mem[pageno*256 + i] for i in range(rowstart, rowstart+8)]
        rownz = False
        for item in row:
            if item != 0:
                rownz = True
                break

        if rownz and not header:
            print("\n\nContents of page 0x%02x" % pageno)
            header=True

        if rownz:
            print("0x%02x: %s" % (rowstart, (" ".join(["0x%02x" % v for v in row]))))

