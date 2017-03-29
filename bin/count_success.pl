#!/usr/bin/perl -w
use strict;
use warnings;

if (@ARGV != 3) {
    die "usage: count_success.pl filename expected_success expected_failures";
}

my $filename = shift;
my $expected_success = shift;
my $expected_failure = shift;

open my $file, $filename or die "Can't open $filename $!";

my $verified = 0;
my $errors = 0;
while (my $line = <$file>){
    if ($line =~ /Boogie program verifier finished with (\d+) verified, (\d+) errors/) {
	$verified = $verified + $1;
	$errors = $errors + $2;
    }
}

if($verified == $expected_success and $errors == $expected_failure){
   print "verified: $verified errors: $errors as expected\n";
} else {
    die "ERROR: Expected verified: $verified errors: $errors, got verified: $expected_success and errors: $expected_failure";
}
