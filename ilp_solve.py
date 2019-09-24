import numpy as np
import cvxpy as cp 
import random
import numpy.linalg as npl
import sys

PARTITION_SCALE = 15

def main():
	fp  = open('input.txt', 'r')

	no_partitions = int(fp.readline())
	Q = np.zeros((no_partitions, no_partitions), dtype=int)
	for i in range(no_partitions):
		Q[i] = np.array(list(map(int, fp.readline().split())))
	fp.close()

	no_pairs = (no_partitions*(no_partitions-1))//2

	A = np.zeros((no_pairs,no_partitions), dtype=int)
	x_L = np.zeros((no_partitions,1))
	scale = np.ones(no_partitions, dtype=int)

	i=0
	for j in range(0,no_partitions):

		if Q[j][j]%2==1:
			scale[j]=2

		mx = Q[j][j]+1
		for k in range(j):
			if(j!=k):
				A[i][j]=Q[j][k]
				A[i][k]=-Q[k][j]
				mx = max(mx,Q[k][j])
				i+=1

		x_L[j][0] = (1-((Q[j][j]%2)/2))*mx

	A = A*scale
	if(npl.matrix_rank(A)==no_partitions):
		sys.exit(1)
	print(A)
	x = cp.Variable((no_partitions,1), integer=True)
	c = np.random.randint(10,size=(1,no_partitions))

	obj = cp.Minimize(c@x)
	cons = [A@x==0,
			x>=x_L]

	prob = cp.Problem(obj, cons)
	prob.solve()

	x_ans = np.array(np.round_(x.value), dtype=int).T
	x_ans = PARTITION_SCALE*x_ans*scale

	fp  = open('temp.txt', 'a')
	fp.write('\n')
	for i in x_ans[0]:
		fp.write(str(i) + " ")
	fp.close()

if __name__ == '__main__':
	main()
