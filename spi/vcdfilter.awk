# Copyright 2020 Jason Bakos, Philip Conrad, Charles Daniels

# Usage: awk -f ./vcdfilter.awk -v SELECT=signal1,signals2,...,signalN

# To disable scope generating, also append -v NOSCOPE=1. This may be useful
# when generating VCD files for Sigrok.

# To ignore signals nested more deeply than a specified amount, append -v
# MAXDEPTH=n

# Consumes a Verilog VCD file on standard input, and emits a version of that
# file with only specific signals retained.

BEGIN {
	split(SELECT, select_signals, ",");
	if (MAXDEPTH==0) { MAXDEPTH = 100000; }
}


$1 ~ /[$]scope/ {
	# we have just entered a new scope
	nscope++;
	scopevar[nscope] = 0;

	if (nscope > MAXDEPTH) { next; }

	if ((NOSCOPE != 1) || (nscope<2)) {print;}

	next;
}

$1 ~ /[$]upscope/ {
	# this scope is done, so we should print out all the variables
	
	if (nscope > MAXDEPTH) { nscope--; next; }

	for (i = 0 ; i < scopevar[nscope]; i++) {
		print(thisscope[nscope,i]);
	}

	if ((NOSCOPE != 1) || (nscope<2)) {
		print($0);
	}

	nscope--;
	next;
}

$1 ~ /[$]var/ {

	# drop any variables that don't match our filter
	permit = 0;
	for (i in select_signals) {
		sig = select_signals[i];
		if ($5 == sig) {
			permit = 1;
		}
	}
	if (permit == 0) { next; }

	# signal 2 hash
	s2h[$5] = $4;

	# track this variable as being in this particular scope
	thisscope[nscope,scopevar[nscope]] = $0;
	scopevar[nscope] ++;

	# don't otherwise process this line
	next;
}

# always allow time markers
$1 ~ /^[#]/ {print; next;}

# or other "commands" that we don't explicitly process
$1 ~ /^[$]/ {print; next;}

# filter out any data lines which don't have a signal hash we like
(NF == 2) {
	permit = 0;
	for (i in select_signals) {
		if ($2 == s2h[select_signals[i]]) { permit = 1; }
	}
	if (permit != 1) { next; }
}

# as above, but for single bit values
(NF ==1 ) {
	permit = 0;
	for (i in select_signals) {
		if (substr($1, 2) == s2h[select_signals[i]]) { permit = 1; }
	}
	if (permit != 1) { next; }
}

# print any lines we didn't otherwise process
{print;}
