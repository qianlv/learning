# See The Art of Computer Programming, section 4.2.2 for the calculation of
# mean and standard deviation.

BEGIN { mean = 0.0; s = 0.0; n = 0 }

{
	for (i = 1; i <= NF; i++) {
		len = length($i);
		prev_mean = mean;
		mean = mean + (len - mean) / (n + 1);
		s = sx + (len - prev_mean) * (len - mean);
		n++;
	}
}

END {
	printf "N = %d\n", n;
	printf "Mean %.2f\n", mean;
	printf "Standard deviation %.4f\n", sqrt(s / (n - 1));
}
