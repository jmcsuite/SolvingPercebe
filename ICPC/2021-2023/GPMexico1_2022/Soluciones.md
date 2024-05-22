# Problema A
Notemos que en nuestro resultado final, algunos bits siempre se suman... los bits tales que haya una cantidad impar de ellos. Tambien notemos que del resto de los bits, o se suman dos veces, o no se suman ninguna vez... es decir
$$ 
cant[i] \% 2== 1 \rarr XOR(A)\& (1<<i) == 1 || XOR(B)\& (1<<i) == 1
$$
$$ 
cant[i] \% 2== 0 \rarr XOR(A)\& (1<<i) + XOR(B)\& (1<<i) == 2x
$$

entonces en los bits de cantidad par, $XOR(A) == XOR(B)$... entonces el problema se reduce a maximizar el $XOR(subset(X))$ si solo nos importaran los bits de cantidad par. Para eso podemos apagar los bits que no nos interesan, y maximizar es $XOR(A)$

Para obtener un subset de una lista que maximize el $XOR(subset)$ se necesita entender XOR basis.

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

Otra idea interesante es sacar el menor nodo que este a una distancia K y que no sea un hijo. Para hacer esto, se llena una tabla para cada nodo... del menor nodo a distancia 0,1,2...K. Para rellenar esa tabla, cada nodo puede hacer un transversal hacia los padres, y si es el padre K, entonces se actualiza la columna K. Practicamente calculas el menor a un nivel K. 
Para saber el menor a K niveles, se recorren K padres y se busca el menor a distancia $K - dis_p$ 

---

# Problema D


