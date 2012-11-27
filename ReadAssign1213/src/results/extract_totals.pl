#!/usr/bin/perl

use strict;
use Math::BigFloat;

my $file = shift;
glob $file;
open FILE ,"<", $file;
open FILE2 ,">>", "plot_totals.txt";

my $dcal1;
my $dcml1;

my $dcal2;
my $dcml2;

while(<FILE>) {

	if ($_ =~ m/PAPI_L1_DCA\t+(\d+)/g) {
		$dcal1 = $1;			
	}
	if ($_ =~ m/PAPI_L1_DCM\t+(\d+)/g) {
		$dcml1 = $1;			
	}

	if ($_ =~ m/PAPI_L2_DCA\t+(\d+)/g) {
		$dcal2 = $1;			
	}
	if ($_ =~ m/PAPI_L2_DCM\t+(\d+)/g) {
		$dcml2 = $1;			
	}
	
}

print FILE2 "PAPI_L1_DCA\t" . $dcal1 . "\n";
print FILE2 "PAPI_L1_DCM\t" . $dcml1 . "\n";
print FILE2 "PAPI_L2_DCA\t" . $dcal2 . "\n";
print FILE2 "PAPI_L2_DCM\t" . $dcml2 . "\n";

__END__

PAPI_TOT_CYC		361656		269
PAPI_TOT_INS		776707		254
PAPI_LD_INS		255512		253
PAPI_SR_INS		5196		253
PAPI_FP_OPS		250010		256
PAPI_FP_INS		250003		253
PAPI_L1_DCA		258412		253
PAPI_L1_DCM		595		253
PAPI_L2_DCA		590		253
PAPI_L2_DCM		132		255
PAPI_L3_DCA		133		256