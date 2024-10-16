# Семинар №3 по СДА - Алгоритми за сортиране.
## Стабилност
Един алгоритъм ще наричаме **стабилен**, ако той ни гарантира, че елементите, които са равни помежду си, няма да променят позициите си един спрямо друг след сортиране, т.е. не се променя относителната наредба.

<img width="448" alt="image" src="https://github.com/user-attachments/assets/cda82754-edd1-43d3-9a77-7cbdb3657773">


## In-place
**In-place** алгоритмите са тези алгоритми, които **НЕ** използват допълнителна памет. Един пример за такъв алгоритъм е добре познатият на всички `Bubble Sort`.

<img width="416" alt="image" src="https://github.com/user-attachments/assets/d2500499-3d3d-4251-865e-519140b3d367">


## Алгоритми за сортиране

| **Algorithm**   | **Time Complexity (Best)** | **Time Complexity (Average)** | **Time Complexity (Worst)** | **Space Complexity** | **In-Place** | **Stable** | **When Efficient**                     |
|-----------------|----------------------------|-------------------------------|-----------------------------|----------------------|--------------|------------|-----------------------------------------|
| [**Bubble Sort**](https://github.com/desiish/SDA_2024_2025/blob/main/Sem03/sorting_algorithms/bubble-sort.cpp) | O(n)                        | O(n^2)                        | O(n^2)                      | O(1)                 | Yes          | Yes        | Useful for smaller sets of elements or when the set is almost sorted, but inefficient for larger sets.|
| [**Insertion Sort**](https://github.com/desiish/SDA_2024_2025/blob/main/Sem03/sorting_algorithms/insertion-sort.cpp) | O(n)                     | O(n^2)                        | O(n^2)                      | O(1)                 | Yes          | Yes        | Useful for small datasets, or nearly sorted lists.|
| [**Selection Sort**](https://github.com/desiish/SDA_2024_2025/blob/main/Sem03/sorting_algorithms/selection-sort.cpp) | O(n^2)                   | O(n^2)                        | O(n^2)                      | O(1)                 | Yes          | No         | Useful when memory writes are costly.         |
| [**Merge Sort**](https://github.com/desiish/SDA_2024_2025/blob/main/Sem03/sorting_algorithms/merge-sort.cpp)  | O(n log n)                  | O(n log n)                    | O(n log n)                  | O(n)                 | No           | Yes        | Useful for large datasets.                    |
| [**Quick Sort**](https://github.com/desiish/SDA_2024_2025/blob/main/Sem03/sorting_algorithms/quick-sort.cpp)  | O(n log n)                  | O(n log n)                    | O(n^2)                      | O(log n) - for the call stack| Yes          | No         | Most general-purpose sorting.          |
| [**Counting Sort**](https://github.com/desiish/SDA_2024_2025/blob/main/Sem03/sorting_algorithms/counting-sort.cpp) | O(n + k)                  | O(n + k)                      | O(n + k)                    | O(k)                 | No           | Yes        | Usefule when the range of input values is limited.|

## Функцията std::sort
`std::sort` е стандартна функция в C++, която се използва за сортиране на елементи от дадена колекция от данни. Тя е част от стандартната библиотека `<algorithm>`, която съдържа различни алгоритми за обработка на колекции от данни.

Най-често е имплементирана или чрез `Quick Sort`, или чрез алгоритъм, комбиниращ `Quick Sort`, `Heap Sort` (за който ще научите по-натам в курса) и `Insertion Sort`. 

Декларация на функцията:
```c++
#include <algorithm>

template <class RandomIt>
void sort(RandomIt first, RandomIt last);

template <class RandomIt, class Compare>
void sort(RandomIt first, RandomIt last, Compare comp);

```

- `Параметри`:
  - first: Итератор, указващ началото на колекцията елементи, които трябва да бъдат сортирани.
  - last: Итератор, указващ края на колекцията елементи, които трябва да бъдат сортирани (сочи елементът след последния елемент в диапазона).
  - comp (по избор): критерий за сортиране (по default се използва operator<).

- `Сложност`: std::sort има средна времева сложност O(n*log n), където n е броят на елементите, които искаме да бъдат сортирани.
- `In-Place`: std::sort не е in-place алгоритъм.
- `Stable`: std::sort не е стабилен алгоритъм.

- Пример:
```c++
#include <iostream>
#include <algorithm>
#include <vector>

bool compareLastDigit(int a, int b) {
    return (a % 10) < (b % 10); 
}

int main() {
    std::vector<int> v = {25, 42, 33, 14, 56};

    std::sort(v.begin(), v.end(), compareLastDigit);

    for (const int& n : v) {
        std::cout << n << ' ';
    }
    return 0;
}

```

## std::greater и std::less
- `std::less` и `std::greater` са мощни инструменти, които улесняват работата с алгоритми и контейнери в C++. Представляват функционални обекти с предефиниран оператор (), които се използват за сравняване на два обекта. Позволяват да дефинираме специфична логика за сравнение, като правят кода по-четим и лесен за поддръжка.
----
[**Визуализация на сортиращите алгоритми**](https://visualgo.net/en/sorting)
