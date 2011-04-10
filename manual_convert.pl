#!/usr/bin/perl

open(F, "doc/quickstart.txt");

@manual_content = <F>;

close (F);

print 'static char manual_content[] = "\\';
print "\n";

foreach $line (@manual_content) {
	chop($line);
	$line =~ s/([\\%"])/\\$1/g;
	printf "$line\\n\\\n";
}

print "\";\n";
