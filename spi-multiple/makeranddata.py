#!/usr/bin/env python3

# Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels

import argparse
import random

parser = argparse.ArgumentParser("""Script to generate randomized sensor data
for the VD002 sensor module, in the format correct for sensordata.hex. NOTE:
this tool does not generate the trailing 0x0 required by the VD002.""")

parser.add_argument("--streams", "-n", type=int, default=1,
        help="Specify the number of streams to generate. (default: 1)")

parser.add_argument("--minlen", "-m", type=int, default=5,
        help="Specify the lower bound on stream length. (default: 5)")

parser.add_argument("--maxlen", "-M", type=int, default=64,
        help="Specify the upper bound on stream length. (default: 64)")

args = parser.parse_args()

for i in range(args.streams):
    l = random.randrange(args.minlen, args.maxlen)
    print("%x" % l)
    for j in range(l):
        print("%x" % random.randrange(0, 255))
