# K-MEANS (clustering)

Autor: **Jan Bajer**

# Zadání:
K-means je jednoduchý iterativní algoritmus pro shlukování množiny bodů do k skupin (kde k je známé předem) s jednoduchou paralelizací. Vstupem je množina bodů (standardní vstup nebo soubor) a počet skupin (parametr na příkazové řádce), na výstupu vrací seznam bodů a jejich příslušnost do skupiny.

# Implementace:

Program vyuziva algoritmus kmeans, který používá data bodů. Nejdříve si zvolíme K počet centroidů. V tomto programu to je prvních K bodů dat.

1. Data proiterujeme. Pro každý bod zjistíme a přidělíme nejbližší centroid.
2. Spočítáme nové souřadnice centroidů, které zjistíme průměrem všech bodů patřící k danému centroidu.
3. Opakujeme 1. a 2. krok dokud se souřadnice centroidů nepřestanou měnit.
4. Výsledek: Data ke kterým je přiděleno centroid ID, centroidy (jejich souřadnice)

Class: **algorithm**
- logika aplikace (algoritmus kmeans)
- čtení dat ze souboru 

Class: **point**
- pro výpočet vzdálenosti mezi 2 body, souřadnice

Class: **main**
- zjišťuje, jestli byly zadány správné vstupy
- ukládá data do souboru
- vypíše výsledek


# Použití:
Pro spuštění programu jsou nutná data z textového souboru, specifikovat clustery a název výsledného souboru do příkazové řádky. Jsou připravené 3 soubory ve složce /testData. Přesuňte tyto 3 soubory (bez jejich directory) prosím po vybuildění do složky cmake-build-debug. Pokud budou v nějaké directory, tak tyto soubory nebudou nalezeny.

<br>**Povinné argumenty pro spuštění programu jsou:** 
- **-clusters** .... Je nutný počet clusterů (minimálně 1)
- **-input** ..... název vstupního souboru ze kterého se vezmou data 
- **-output**  ..... název výsledného souboru kam se vypíšou body a ke kterému clusteru patří (je u nich ID clusteru)

**Dobrovolné argumenty:**
- **-centroids** ... název souboru kam se vypíšou centroidy (defaultně do centroids.txt)

**Příklad použití:**
- -clusters 2 -input sample_1.txt -output result1.txt -centroids centroids1.txt
- -clusters 2 -input sample_2.txt -output result2.txt -centroids centroids2.txt
- -clusters 2 -input sample_3.txt -output result3.txt -centroids centroids3.txt

# Měření:
Měření proběhlo s procesorem Intel Core i7 9750H Coffee Lake s  2,6 GHz a 16 GB RAM v CLion.
<br>
Výstup z měření:
- Pro **sample_1.txt** (6 vzorků, 2 clustery): <br>
-Time: _0 ms to finish_ <br>
-Iterations: _2_

- Pro **sample_2.txt** (500 vzorků, 2 clustery): <br>
-Time: _1 ms to finish_ <br>
-Iterations: _3_

- Pro **sample_3.txt** (100 000 vzorků, 2 clustery): <br>
-Time: _277 ms to finish_ <br>
-Iterations: _3_
