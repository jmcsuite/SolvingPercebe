# Soluciones

## Problema H

La solucion se divide en dos partes

### Abstraccion del problema
 Primero hay que ver que una secuencia de brackets se puede ver como 1s y -1s. Una secuencia es valida solo si la suma final es 0, y la suma de cualquier prefijo nunca es menor a 0.

 La suma final es la misma sin importar el orden.
 Por ende, lo que nos importa es escoger un orden en el que la suma a cualquier prefijo sea positivo o cero.

 Veamos que para cada segmento, podemos calcular su prefijo minimo, y para poder agregar el segmento, el a $BalancePrevio + MinimoPrefijo >= 0$

 Entonces el problema se reduce a que tenemos una lista de enteros $x_i, y_i$ ($x_i$ es el minimo prefijo del segmento $i$ y $y_i$ es el balance final del segmento $i$) donde se tiene un balance $S$, y para insertar un elemento $ S >= -x_i $ y despues de insertarlo se tiene una un nuevo balance $S = S + y_i$

 ### Greedy :o

Primero se seleccionan los segmentos con un balance positivo, en orden del maximo minimo prefijo al minimo minimo prefijo. Si en algun punto el balance es menor al necesario para hacer la insercion, entonces es imposible encontrar un acomodo. Despues, para el los segmentos de balance final negativo, lo importante es agregar en orden de  $MinimoPrefijo - BalanceFinal$ de la mayor diferencia a la menor diferencia.

La intuicion de que este ultimo paso funciona es la siguiente
> Si tenemos que $Balance_i = MinPrefijo_i$ para todos los segmentos... no nos importa el orden, solo nos importa que es Balance inicial sea igual a la de todos los balances

> Si tenemos $Balance_i + x = MinPrefijo_i$ para todos los segmentos... (notemos que x es positiva siempre) entonces sigue sin importar el orden, y el balance inicial tiene que ser igual a la suma de los $MinPrefijo_i$ + $x$

> Por ultimo se analiza que pasa si  $Balance_i + x_i = MinPrefijo_i$ y se intenta calcular es balance inicial necesario para poder agregar todos los segmentos

---
## Problema J

Si modelamos el problema como un grafo, lo podemos dividir en dos subproblemas

1. Supongamos que nuestra entrada $M$ es infinita. to be continued




