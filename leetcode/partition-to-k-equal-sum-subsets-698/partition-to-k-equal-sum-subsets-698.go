package main

import "fmt"

func rightStatus(sums []int, subSum int) []int {
	n := len(sums)
	status := make([]int, 0)
	for i := 0; i < (1 << uint32(n)); i++ {
		s := 0
		for j := 0; j < n; j++ {
			if i&(1<<uint32(j)) != 0 {
				s += sums[j]
			}
		}
		if s == subSum {
			status = append(status, i)
		}
	}
	return status
}

func canPartitionKSubsets(sums []int, k int) bool {
	n := len(sums)
	dp := make([][]bool, 2)
	for i := range dp {
		dp[i] = make([]bool, 1<<uint32(n))
	}

	s := 0
	for _, v := range sums {
		s += v
	}
	if s%k != 0 {
		return false
	}

	status := rightStatus(sums, s/k)
	for _, j := range status {
		dp[0][j] = true
	}
	i := 1
	for ; i < k; i++ {
		for j := range dp[(i-1)%2] {
			if !dp[(i-1)%2][j] {
				continue
			}
			for _, v := range status {
				if (j & v) != 0 {
					continue
				}
				dp[i%2][j|v] = true
			}
		}
		for j := 0; j < (1 << uint32(n)); j++ {
			dp[(i-1)%2][j] = false
		}
	}
	return dp[(i-1)%2][(1<<uint32(n))-1]
}

func main() {
	fmt.Println(canPartitionKSubsets([]int{4, 4, 1, 3}, 3))
	fmt.Println(canPartitionKSubsets([]int{4, 3, 2, 3, 5, 2, 1}, 4))
}
