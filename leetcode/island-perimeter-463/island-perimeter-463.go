package main

import "fmt"

var visit [][]bool

func my_init(n, m int) {
	visit = make([][]bool, n)
	for i := 0; i < n; i++ {
		visit[i] = make([]bool, m)
	}
}

var directions [][]int = [][]int{
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1},
}

func islandPerimeter(grid [][]int) int {
	n := len(grid)
	if n <= 0 {
		return 0
	}
	m := len(grid[0])
	my_init(n, m)

	var advance = func(i, j, direction int) (int, int, bool) {
		x, y := i+directions[direction][0], j+directions[direction][1]
		if x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 1 {
			return x, y, true
		}
		return x, y, false
	}

	perimeter := 0
	var dfs func(i, j int)
	dfs = func(i, j int) {
		if visit[i][j] || grid[i][j] == 0 {
			return
		}
		visit[i][j] = true
		for d := 0; d < 4; d++ {
			x, y, island := advance(i, j, d)
			if !island {
				perimeter++
			} else {
				dfs(x, y)
			}
		}
	}

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			dfs(i, j)
		}
	}
	return perimeter
}

func main() {
	fmt.Println(islandPerimeter([][]int{[]int{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}}))
}
