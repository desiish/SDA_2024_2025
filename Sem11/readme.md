# Семинар №11 по СДА, спец. СИ - Графи.

Графи. Какво представляват те?

Ощe от дискретната математика знаем, че графът представлява наредена двойка: 
```
G = (V, E)
```
- V e непразно множество, чиито елементи се наричат върхове. 
- Множеството **E** е крайно множество от ребра. Ребро наричаме двуелементно множество {v1, v2}, където v1 и v2 са елементи на **V**.

Нека сега разгледаме различните видове графи.

## Видове графи

### Неориенрирани графи
Когато говорим за графи, по подразбиране визираме неориентиран граф. Неориентираният граф се характеризира с това, че ребрата му са от вида двуелементни подмножества {a, b}.
Това означава, че реброто {a, b} е същото като реброто {b, a}. В случая не различаваме посока на реброто. 

<img width="411" alt="image" src="https://github.com/user-attachments/assets/ade70a5c-11c0-43a9-b9f6-934ea14c93e0">

### Ориентирани графи
При ориентираните графи вече различаваме посока на реброто. Ребрата са наредени двойки от вида (a, b) = {a, {a, b}}, като в общия случай (a, b) != (b, a), освен когато a = b.

<img width="412" alt="image" src="https://github.com/user-attachments/assets/541aaf51-5930-45f1-87f4-b74d62907a2a">

### Тегловен граф
Можем да представим например картата на България като един граф, в който върховете ще са градовете, а ребрата - пътищата между тях. С какво се отличават пътищата - ами всеки
един си има дължина. Тази дължина можем да я "закачим" към съответното ребро и да получим т.нар. тегло на реброто. Това ни е необходимо понякога, когато ни интересува да анализираме
по някакъв начин тази допълнителна стойност на реброто.

<img width="293" alt="image" src="https://github.com/user-attachments/assets/4833f649-4a90-46e0-ae31-3012fa4d692e">

### Мултиграф
Мултиграф ще наричаме граф, който може да има повече от едно ребро между зададени от конкретна наредена двойка върхове.

## Дефиниции
| Понятие                        | Дефиниция 
| :---                           |    :----:   
| Примка в граф                  | Ребро от типа {v, v} (неформално ребро от връх към себе си).
| Път в граф                     | Редица от върхове (v_1, v_2, ..., v_n) за които е в сила {v_i, v_{i + 1}} е елемент на E.
| Цикъл в граф                   | Път **p** за който v_1 = v_n се нарича цикъл. 
| Прост път                      | Път **p** e прост ако всички елементи в редицата са уникални, т.е. i != j <=> v_i != v_j.
| Дължина на път                 | Дължината на пътя е **броя на ребрата в него**.
| Ацикличен граф                 | Граф, в който няма цикъл. Ако в графът има цикъл то той се нарича цикличен.
| Свързан граф                   | Граф е свързан ако за всеки два върха u, v съществува път между u и v.
| Силно свързани върхове         | В **ориентиран граф** казваме, че върхове u, v са силно свързани ако съществува път от u до v и от v до u
| Силно свързан граф             | Силно свързан граф е **ориентиран** граф, за който всеки два върха са силно свързани.

## Графи в програмирането
Графите представляват **ADT**, който поддържа следните операции:
- add_vertex() - добавя връх;
- remove_vertex() - премахва връх;
- add_edge() - добавяме ребро;
- remove_edge() - премахваме ребро;
- get_successors() - взимаме преките наследници на даден връх(в ориентиран граф);
- get_predecessors() - взимаме преките предшественици на даден връх(в ориентиран граф)
- adjacent() - взимаме съседите на даден връх(в неориенторан граф).

За да имплементираме граф, наивно можем да тръгнем от двете множества - E и V. В последствие обаче ще установим, че това ще е доста бавно.
Съответно ще се насочим към друг вариант - например чрез матрица на съседство. 

## Представяне чрез матрица на съседство
Ако си представим, че върховете на даден граф са ни именувани от 0 до N - 1, нека имаме матрица **NxN**. Матрицата ще е от тип *bool*, където стойността на клетката [i][j] ще е 1, ако имаме ребро между v_i и v_j, 
и 0 ако нямаме. Ако искаме графът ни да е тегловен, просто вместо *bool*, ще използваме например *int* и вместо 1, стойността на клетката [i][j] ще е съответното тегло на реброто между върховете v_i и v_j.

Предимствата на това представяне са, че можем да проверим, дали има ребро от който и да е връх до който и да е връх за константно време. Също така за линейно време за някой възел можем да вземем всички негови съседни върхове. 

Проблемът е, че често това представяне заема твърде много памет (O(|V|^2)). Ако графът има твърде много върхове а твърде малко ребра, матрицата ще има много нули (така наречената разредена матрица). Така ще ни се наложи да представяме малко информация с много памет.

## Представяне чрез списък на съседите
Друг начин да представим и имплементираме граф, е да поддържаме списък (или масив) от |V| списъка. Вярно е, че списъкът на позиция i съдържа всички наследници на връх i.

Сега, ако искаме да проверим дали има ребро между връх i и връх j, то трябва да извършим следната операция: lists[i].contains(j);

Тегловни графи можем да представим, като вече списъците не са от числа а от двойки (Връх, Тегло).

Предимството на тази реализация е, че бързо можем да добавяме върхове и ребра. Също така паметта ни вече не е O(|V|^2) а O(|V| + |E|).

## Обхождания на граф. BFS и DFS
Вече разгледахме възможните имплементации на графи, сега ше разгледаме и възможните обхождания. 

## BFS
Breadth-First Search е сравнително прост алгоритъм за търсене в граф, но върху идеята, която той носи се базират други алгоритми върху графи, които ще разгледаме по-натам в курса.

Като вход получаваме граф G = (V, E) и връх s. BFS систематично открива всички върхове, които са достижими от s. Чрез него можем да изчислим разстоянието (най - малкия брой ребра) от s до всеки друг връх. Алгоритъмът работи за ориентирани и неориентирани графи. 

BFS използва структурата от данни опашка, за да работи коректно. Самата идея е следната: Имаме начален връх, той ще бъде първият посетен. Добри кандидати да бъдат посетени след това са неговите съседи. Имаме функция adjacent (за ориентирани графи successors). Добавяме ги в опашката, където чакат да бъдат посетени. След това последователно ги изваждаме от нея, като добавяме всички техни непосетени съседи в опашката, където чакат да бъдат посетени.

Трябва ни обаче някакъв начин, чрез който да разбираме дали даден връх е бил посетен. Ако нямаме тази информация, зацикляме. С този проблем лесно се справяме, правейки масив, в който записваме дали даден връх е посетен, или не.

Псведокод:
```
BFS(G = (V, E), s начален връх) 
    Създай опашка q и добави s вътре.
    Създай булев масив visited[0..|V| - 1] със стойности false.

    q.push(s).

    while(!q.empty())
        Нека cVertex е q.top().
        q.pop().
        Посети cVertex.
        Добави в q всеки съсед на cVertex, който не е посетен.
```

Ако графът не е тегловен BFS може да се използва за намирането на най - къс път между два върха. 

## DFS
BFS обхожда графа ниво по ниво. DFS използва различна стратегия. Вървим по път, докато не "стигнем до края на този път" (нямаме накъде да отидем повече). След това се връщаме назад, докато не стигнем връх, който има непосетен съсед. Рекурсивно повтаряме тази стратегия върху непосетения съсед и внимаваме да не повторим връх два пъти.

DFS използва структурата от данни stack, за да работи коректно. За наше улеснение ще направим функцията рекурсивна и ще използваме системния стек. 

DFS посещава всеки връх и всяко ребро точно един път, което води до сложност O(|V| + |E|).

DFS има много приложения, използва се за намиране на цикъл в граф, топологично сортиране на DAG (directet acyclic graph), търсене на пътища и др.

Псведокод:
```
DFS(G = (V, E), s начален връх, visited[0...|V| - 1]) 
    маркирай s като посетен.

    За всеки съсед adj на s:
      ако visited[adj] = false, изпълни DFS(adj).
```

---
Задачи 😸
- [**1. Course schedule II**](https://leetcode.com/problems/course-schedule-ii/description/)
- [**2. Shortest Path With Alternating Colors**](https://leetcode.com/problems/shortest-path-with-alternating-colors/description/)
- [**3. Път в граф**](https://www.hackerrank.com/contests/sda-hw-10-2022/challenges/challenge-2852/problem)
- [**4. Студентски празник**](https://www.hackerrank.com/contests/sda-hw-10-2022/challenges/challenge-3782)
