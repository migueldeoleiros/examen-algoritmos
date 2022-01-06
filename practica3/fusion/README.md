El algoritmo de ordenación por fusión o mergesort se implementa de forma parecida 
a quicksort, por ese motivo no me extrañaría un ejercicio que te pida que substituyas 
uno por otro o que te pida que compares dos umbrales diferentes con fusión.

# cotas
La cota ajustada para umbral uno es n^2 sin duda, como cota inferior usé 1.5 y como
superior 2.3 para asegurarme de tener 3 cifras significativas. Dependiento de la 
velocidad de tu ordenador las cotas superior e inferior podrian necesitar ajuste 
para cumplir esto.

# pseudocódigo
Usé el pseudocódigo de las diapositivas, pero no me extrañaría que variara un poco.

```
function Fusión (var T[izq..der], Centro:izq..der)
  i := izq; j := Centro+1; k := izq;
  while i < Centro and j <= der do
    if T[i] <= T[j] then
      aux[k] := T[i]; i := i+1;
    else Aux[k] := T[j]; j := j+1;
    k := k+1;
  while i <= Centro do
    aux[k] := T[i]; i := i+1; k := k+1;
  while j <= der do
    aux[k] := T[j]; j := j+1; k := k+1;
  for k := izq to der
    T[k] := aux[k];
end function;

function Fusión_recursivo (var T[izq..der])
  if izq+UMBRAL < der then
    Centro := (izq+der) div 2;
    Fusión_recursivo (T[izq..Centro]);
    Fusión_recursivo (T[Centro+1..der]);
    Fusión (T[izq..der], Centro)
  else Inserción (T[izq..der])
end function;

function Ordenación por Fusión (var T[1..n])
    Fusión_recursivo (T[1..n]);
end function;
```
