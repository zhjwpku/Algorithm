// Levenshtein Distance i.e. Edit distance
// https://en.wikipedia.org/wiki/Levenshtein_distance
// Ref: https://github.com/texttheater/golang-levenshtein/blob/master/levenshtein/levenshtein.go

package main

import (
	"fmt"
)

const (
	Ins = iota
	Del
	Sub
	Match
)

type MatchFunction func(rune, rune) bool

type Options struct {
	InsCost int
	DelCost int
	SubCost int
	Matches MatchFunction
}

// DefaultOptions is the default options
var DefaultOptions = Options{
	InsCost: 1,
	DelCost: 1,
	SubCost: 2,
	Matches: func(source rune, target rune) bool {
		return source == target
	},
}

func LevenshteinDistance(source []rune, target []rune, op Options) int {
	height := len(source) + 1
	width := len(target) + 1
	matrix := make([][]int, 2) // 只需要存储前一行和当前行
	for i := 0; i < 2; i++ {
		matrix[i] = make([]int, width)
		matrix[i][0] = i // 初始化第一列
	}

	for j := 1; j < width; j++ {
		matrix[0][j] = j // 初始化第一行
	}

	for i := 1; i < height; i++ {
		cur := matrix[i%2]
		prev := matrix[(i-1)%2]
		cur[0] = i
		for j := 1; j < width; j++ { // 更新当前行
			delCost := prev[j] + op.DelCost
			matchSubCost := prev[j-1]
			if !op.Matches(source[i-1], target[j-1]) {
				matchSubCost += op.SubCost
			}
			insCost := cur[j-1] + op.InsCost
			cur[j] = min(delCost, min(matchSubCost, insCost))
		}
	}

	return matrix[(height-1)%2][width-1]
}

func main() {
	source := "abcdabcd"
	target := "acdda"
	distance := LevenshteinDistance([]rune(source), []rune(target), DefaultOptions)
	fmt.Printf("%d", distance)
}

func min(x, y int) int {
	if x > y {
		return y
	}
	return x
}
