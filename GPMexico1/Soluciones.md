# Problema B

La idea es agarro el menor nodo posible, a partir de ese nodo corro un BFS de K niveles, y actualizo los nodos posibles. Para obtener/actualizar los nodos posibles, basta con insertar los nodos visitados a un set.  La complejidad del algoritmo seria $N*(BFS)$ y BFS es $N + E$ entonces la complejidad es $N*N$

Para reducir la complejdad, notemos que una vez que visitamos el nodo $x_i$ en el nivel $a$ de nuestro BFS, no nos conviene visitar el mismo nodo $x_i$ pero en ningun nivel $b$ con $b >= a$. La intuicion es que todos los nodos que se alcanzan con el nivel $b$, se alcanzaron en un BFS anterior. Como $K <= 100$ y en cada visita a un nodo $k_i$ decrece, la complejidad queda en $O(N*K)$

## Remarks
En el problema se usa un arbol, pero funciona la idea para cualquier grafo.

## Ideas fallidas pero interesantes
Una idea es:
1. Rooteas el arbol en 1
2. Vas haciendo las BFS en el mismo orden que en la solucion... pero solo propagas la BFS hacia tus hijos. 

Se puede hacer un contraejemplo para ver que no funciona, pero lo interesante es ver que la complejidad del algoritmo es $O(N*K)$. La idea ver que a cada hijo lo van a visitar a lo mas K padres. Tambien se puede ver que hacer esto, es lo mismo que por cada nodo, hacer un transversal haca arriba de K niveles.

---

# Problema D


