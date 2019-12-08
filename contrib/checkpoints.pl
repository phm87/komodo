#!/usr/bin/perl
use warnings;
use strict;
# Generate checkpoint data for use in src/main.cpp

my $hush    = "./src/hush-cli";
my $gethash = "$hush getblockhash";
my $stride  = shift || 1000;
my $count   = 0;
my $blocks  = qx{$hush getblockcount};

while (1) {
	$count++;
	my $block = $stride*$count;
	last if ($block > $blocks);
	my $blockhash = qx{$gethash $block};
	chomp $blockhash;
	print qq{($block,     uint256S("0x$blockhash"))\n};
}
