
use strict;

open FILE, ">>" , "results.txt";

my @test_files = ("small.xml","medium.xml");
my $s;

for my $test (@test_files) {
	open PARAM2, ">", "param2.xml";
	open PARAM, "<", "param.xml";
	while (<PARAM>) {			
			if ($_ =~ m/\<parameter\smeshfile\=\".*\"\/\>.*/g) {
				print PARAM2 "\t\<parameter meshfile=\"input\/$test\"\/\>" ."\n";
			}
			else {
				print PARAM2 $_;
			}		
	}
	close PARAM2;
	close PARAM;
	

	 $s = qx (./lesson);
	 print FILE $s;
}
