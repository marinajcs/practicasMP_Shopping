# practicasMP
Recopilación de prácticas de Metodología de la Programación, realizadas en 1º de Ingeniería Informática (UGR, curso 20-21).

APUNTES SHOPPING 5 (PROYECTO FINAL)

/*** Index() ***/

- Añadir tipo de index para Session (getInOnWhich = 2)
	Establecer relaciones entre marcas R(X,Y,type) 
		-> deben estar en misma sesión y compartir tipo
- BuildIndex, ordenado a partir de session

session   position (in index)
1) S1	      6      <- Marcas en pos 6 y 8 relacionadas
2) S1	      8
3) S2       15
...
10) S5      27

Cómo hacerlo:
- FindUnique para hallar todas sesiones diferentes
- Lower y upperbound de S1, S2, ..., Sn
- Hacer bucles for (usando lower y upper) para elem de sesiones
(otras opciones: RawFilter...)


*******************************************************

for (int i = ub; i < idx.size(); i++){
	session = getEvent(evs, idx, ub).getSession();
	lb = idx.lower_bound(session);
	ub = idx.upper_bound(session);

	for (int i = lb; i < ub-1; i++)
		for (int j = i+1; j < ub; j++){

			brand1 =  evs.at(idx.at(i).getPos).getBrand();
			brand2 = evs.at(idx.at(j).getPos).getBrand();

			if (brand1 != brand2){
				m_adj(brand1,brand2)++;
				m_adj(brand2, brand1)++;
			}
	}
k = ub;


}


double rest_elem;
bool may_umbral = false;


for (int i = 0; i < n && !may_umbral; i++)
	rest_elem = Pr.at(0,i) - CopyPr.at(0,i);
	
if (RestaPr > threshold)
	may_umbral = true;




********************************************************

/*** PageRank _ Matrix() ***/

1. MATRIZ DE ADYACENCIA

- Inicializar a 0 matriz bidimensional
- Representa relaciones:

En grafo, con las relaciones (simétricas) a-b,b-c,c-d se tendría:

	a	b	c	d
a	0	1	0	0

b	1	0	1	0

c	0	1	0	1

d	0	0	1	0

- Tamaño (n_filas y n_columnas) con findUnique
- Se usará Matriz 2D usando array 1D de punteros a único array (pg 61 del pdf)

Ejemplo matriz. Cuenta cuantas relaciones hay:

0  2  0  0  0		nodo   fil/col
2  0  1  2  0		 A    	0
0  1  0  1  0		 B	    1
0  2  1  0  0		 C	    2
0  0  0  0  0		 D      3
			           E      4

Se trabaja con etiquetas (dch.) que funcionan como index, 
no hay elementos duplicados (A, B, C, D, E...)


2. NORMALIZACIÓN DE MATRIZ

Trabajando con probabilidades
Sumar por filas y dividir cada componente por dicho valor
Si suma es 0 (E en ejemplo anterior) se fija valor uniforme (1/n_marcas)

double unif = 1/n_fil;
double sum_fil[n_fil];

for (int i = 0; i < n_fil; i++)
  for (int j = 0; j < n_col; j++)
     sum_fil[i] += m[i][j];

for (int i = 0; i < n_fil; i++)
  for (int j = 0; j < n_col; j++)
      if (sum_fil[i] == 0)
         m[i][j] = unif;
      else
         m[i][j] = m[i][j]/sum_fil[i];
  


3. TELETRANSPORTE 

Teletrasporte = pequeña probabilidad de "pegar un salto" entre elementos
de grafo aparentemente no conectados [mirar fórmula del pdf]

Aplicar fórmula, usando operadores que se explicarán más tarde.

matrix = alpha*matrix + (1-alpha)/n_fil;

void resize(size_t nrows, size_t ncols, double defValue = 0.0){
	nfil = nrows;
	ncol = ncols;
	
	inicializar a defValue...
}

Operators:

Matrix & operator=(const Matrix & m){
	Matrix block;
	block.resize(m.rows(), m.columns());

	for (int i = 0; i < nfil; i++)
  	   for (int j = 0; j < ncol; j++)
		block[i][j] = m[i][j]

	return block;
}

Matrix & operator*=(double val)
	for (int i = 0; i < nfil; i++)
  	   for (int j = 0; j < ncol; j++)
		m[i][j] = m[i][j]*val;
return block...

Matrix & operator*(const Matrix & m2) const {  //REVISAR
	Matrix block;
	double sum_prod[nfil*ncol];

	for (int i = 0; i < nfil; i++)
		sum_prod[i] = 0;
  	   for (int j = 0; j < ncol; j++)
		prod = m[i][j]*m2[j][i];
		sum_prod[i] += prod;
	   
int k = 0;
for (int i = 0...
   for (int j = 0...
     block[i][j] = sum_prod[k]
     k++;


}





4. CÁLCULO DE PAGERANK

Algoritmo iterativo, maneja probabilidades

Partiendo de valores iniciales (el uniforme 1/n_marcas)
Matriz de 1xn (horizontal, siendo n = n_marcas)
Calcular producto de matrices con operator [1xn  x  nxn  = '1xn']
Se repite proceso hasta que: 
	valor abs de diferencia entre PR y su consecutivo PR 
	esté por debajo de un umbral

	 A	B	C	
it 0: 	 0.2	0.2	0.2
it 1: 	 0.132	0.432	0.154
...
it 16:	0.167	0.386	0.169

Resumen: mirar esquema de pg 13

(FUNCIONAMIENTO DEL PROGRAMA MAIN)

gestión de argumentos del main viene hecho ya [pg 15]
funcionamiento y valores de salida explicados en pg 15 también


****************************************************

MATRIZ BIDIMENSIONAL ETIQUETADA

Se le añaden etiquetas (cadenas  [Cuadro 7 - pg 16]
para poder indexar en la propia matriz
Diferencia: fil y col eran iguales en la anterior (A,B,C,D,E,F)
	    en esta son diferentes 
		(fil: W,X,Y,Z,U,V // col: A,D,E,B,C,F)

Mirar 5.1 Representación

2 índices: rowLabels y colLabels

Ejemplo [Cuadro 8 - pg 17] - En matriz desordenados, en index ordenados

EtqCol	 Pos      EtiqFil    Pos
A	  0	     U        4
B	  3	     V        5
C	  4 	     W        0
D	  1	     X        1
E	  2	     Y        2
F	  5	     Z	      3


/////////////////////////////////////////////////////////

Clase nueva: Matrix()

Constructor de copia -> para probarlo, crear objeto a partir de otro en main

diferencia de at y operator() -> uno compara rango, el otro no. 
Unos de consulta otros de modificación.

Matriz etiqueta (especifica etiquetas de fil y col, matrices cuadradas)

labetAtRow/Col -> en matriz
getRow/ColLabels -> en index/etiq

void resize (aumentar/disminuir dimensiones de matriz, contenidos a 0)
uno para matriz genérica y otro para etiquetada


/////////////////////////////////////////////////////////

***NOTAS EXTRA***

- No incluir marcas vacías a la hora de establecer relaciones
- Añadir descripciones de doxygen a los métodos extra
- No olvidar añadir clear en métodos de lectura
- Hacer nuestros propios tests, creando funciones específicas 
  [a partir de pg 18]. Ejemplos de lectura/salida datos [pg 19]
- Algunos métodos comentados, el main ya viene implementado
- No hay que modificar clases antiguas, excepto:
	Index -> build, setIOnWhich, rawFilterIndex (añadir "Session")
  Estos cambios vienen implementados en la pg 21 del pdf

/////////////////////////////////////////////////////////
