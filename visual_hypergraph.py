import numpy as np
import matplotlib.pyplot as plt
import hypernetx as hnx


scenes = {}
cnt = 0
with open ('./datasets/NDCC', 'r') as f:
    for line in f:
        data = line.split()
        scenes[cnt] = set(data)
        cnt += 1
        
# scenes = {
#     0: ('FN', 'TH'),
#     1: ('TH', 'JV'),
#     2: ('BM', 'FN', 'JA'),
#     3: ('JV', 'JU', 'CH', 'BM'),
#     4: ('JU', 'CH', 'BR', 'CN', 'CC', 'JV', 'BM'),
#     5: ('TH', 'GP'),
#     6: ('GP', 'MP'),
#     7: ('MA', 'GP')
# }

H = hnx.Hypergraph(scenes)
hnx.drawing.draw(H)
plt.savefig('hypergraph.png')