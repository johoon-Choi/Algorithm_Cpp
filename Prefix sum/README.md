<div align="center"><h1> Prefix sum (구간 합) </h1></div>

<div align="center"> arr[0] 부터 arr[k] (0 <= k < n) 까지의 합을 구한 후 i ~ j 번째 원소들의 (0 <= i < j < n) 구간 합을 구할 수 있다. </div>  
<br></br>
- sum[k] == 0 ~ k 번째 원소들의 합 이라고 할 때
  5 ~ 12 번째 원소들의 구간 합 == sum[12] - sum[4]
