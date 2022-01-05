# Informe
    Las cotas parecen ser iguales que con mediana de tres, por lo tanto el informe sería exactamente igual que el original. Lo más posible es que en el examen si pidieran esto no hará falta hacer todas las tablas y solo te pediran una o dos.
# pseudocódigo
    El algoritmo cambia un poco si lo comparas con el de mediana de 3, no es solo la funcion para selecionar el pivote, puede que se pueda hacer diferente, pero este es el pseudocódigo que encontré en los apuntes.
```
procedimiento ordenarAux (v[izq..der]){
    si izq+UMBRAL <= der entonces
        x := aleatorio en el rango(izq..der);
        pivote := v[x];
        intercambiar(v[izq],v[x]);
        i := izq+1;
        j := der;
        mientras i <= j hacer
            mientras i<=der y v[i]<pivote hacer
                i := i + 1;
            fin mientras;
            mientras v[j]>pivote hacer
                j := j - 1;
            fin mientras;
            si i<=j entonces
                intercambiar(v[i],v[j]);
                i := i + 1;
                j := j - 1;
            fin si;
        fin mientras;
        intercambiar(v[izq],v[j]);
        ordenarAux(v[izq..j-1]);
        ordenarAux(v[j+1..der]);
    fin si;
fin procedimiento;
```
