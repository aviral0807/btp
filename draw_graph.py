import matplotlib.pyplot as plt
import networkx as nx
import numpy as np

def draw():
	adjacency_matrix = np.genfromtxt('output.txt', dtype=int)
	rows, cols = np.where(adjacency_matrix == 1)
	edges = zip(rows.tolist(), cols.tolist())
	gr = nx.Graph()
	gr.add_edges_from(edges)
	nx.draw(gr, show_labels=True)
	plt.show()

if __name__ == '__main__':
	draw()