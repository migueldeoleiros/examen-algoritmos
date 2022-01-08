# Cotas
La cota ajustada deberia andar cerca del 2, las otras 2 sobre 0.2 arriba y abajo, probad en el pc y que cada uno ponga la que se ajuste

# Pseudocodigo
Como el pseudocodigo no esta en las diapositivas, lo busque por google y utilice este (va a variar casi 100%):

```
procedimiento Burbuja(var T[1..n])
    para j=1 hasta n hacer
        para i=1 hasta n-j hacer
            si T[i] > T[i+1] entonces   %Intercambiar los numeros
                temp = v[i];
                v[i] = v[i+1];
                v[i+1] = temp;
            fin si
        fin para
    fin para
fin procedimiento
```
