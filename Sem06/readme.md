# Семинар №6 по СДА, спец. СИ - Дек, стек и опашка.

Време е да се запознаем със следващите две важни структури от данни, а именно - стек и опашка.

## `std::stack` 
Стекът представлява колекция от данни, която поддържа 3 главни операции:
- `push(el)`
- `pop()`
- `peek()` -> .top()

Важно е, че **не** поддържа iterator pattern и пряка индексация. 

Стекът работи на принципа `LIFO` - last in first out. Това идва именно от поддържаните операции.
Операцията `push` добавя елемент към колекцията. Операцията `pop` премахва последно добавения елемент от колекцията.

<img width="460" alt="image" src="https://github.com/user-attachments/assets/2d605a83-7bf8-454d-9577-bdcc7f041c03">

Има и метод, който достъпва "най-горния" елемент. И именно около него се "върти" концепцията на стека - само до него имаме достъп и само него ще можем да модифицираме - да достъпваме, променяме или премахваме.

Не изглежда много сложно, но нека си зададем въпроса - как е имплементиран? Всъщност се оказва, че ако досега всичките структури от данни, които разглеждахме, приемаха само тип на елементите от колекциите в темплейта си, 
то стекът приема и контейнер. Единственото условие е контейнера да поддържа функциите:
- `back()`
- `push_back()`
- `pop_back()`

Съответно за контейнер можем да използваме както вектор, така и свързан списък. По дефолт обаче се използва контейнерът `std::deque`, който ще разгледаме след малко.

## `std::queue`
Нека първо разгледаме опашката. Тя много прилича на стека - отново поддържа операциите:
- `push(el)`
- `pop()`
- `peek()` -> .front(), .back()

Важно е, че отново не поддържа iterator pattern и пряка индексация. 

Тази структура работи на принципа FIFO - first in first out. За да обясним работата на опашката, ще разгледаме следния пример: Представете си, че сте лекарф в кабинет. Пред кабинета има опашка от пациенти, като вие започвате да приемате пациентите по ред на идване - първия дошъл, втория и т.н. Вас ви интересува само кой е дошъл най-рано и съответно че неговият ред е дошъл. Пациентите обаче ги интересува и последния на опашката - за да знаят след кого им идва реда. Те образуват една "опашка", подобна на stl-ската. Вие като доктор pop-вате пациенти от началото на опашката, а новодошлите се push-ват в края й. С това се обобщават и методите на опашката, които са написани по-горе. 

<img width="463" alt="image" src="https://github.com/user-attachments/assets/7a175d4b-0d22-4f81-a794-eb2aec042f0c">

Опашката също приема както тип на данните в колекцията си, така и контейнер, в който да се съхраняват. Този контейнер трябва да поддържа операциите:
- `.front()`
- `.back()`
- `.pop_front()`
- `.push_back()`\

Съответно можем да използваме doubly linked list или структурата, зададена по default - `std::deque`.

## `std::deque`
Нека разгледаме този контейнер, който използват стека и опашката, а именно дек. Срещат се различни имплементации на дека, като например:
- circular buffer
- doubly linked list
- segment array.

Ние ще разгледаме последната имплементация, коато всъщност е и стандартната имплементация, а именно - на сегментен масив. 
Понятието "сегментен масив" може би звучи сложно първоначално, но сами ще се убедите, че няма нищо сложно в него. 
Данните ни се съхраняват в "блокчета" памет с константна големина. Тоест, за да ги съхраним, ни трябва масивче от указатели към такива блокчета памет. Ще пазим индекс на първия елемент (offset) и размера на колекцията (size), за да намерим последния (offset + size). Идеята му е, че започваме да добавяме елементи от средата на нашия "map" от блокчета по 2 начина:
- в началото, като там местим offset назад и увеличаваме сайза;
- в края, като просто увеличаваме сайза;

При resize на масивчето от блокчета просто се копират указателите, което прави resize-овете доста по-cheap отколкото при вектора. Стария "map" се поставя в средата на новия, за да имаме място отгоре за push_front() и отдолу за push_back(). 

Друго важно нещо е, че тук имаме пряка индексация на елементите чрез operator[]. Имаме и итератор патърн. 

[Добра визуализация на deque](https://medium.com/@ssakib/how-does-std-deque-actually-work-part-1-482a3273d773)

---
## Задачи 💮
- [Backspace String Compare](https://leetcode.com/problems/backspace-string-compare/description/)
- [Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/description/)
- [Valid Parentheses](https://leetcode.com/problems/valid-parentheses/description/)
- [Slidingb Window Maximum](https://leetcode.com/problems/sliding-window-maximum/description/)
- [Welcome To The Jungle](https://www.hackerrank.com/contests/practice-4-sda/challenges/welcome-to-the-jungle)

Задача 6:
Generate Binary Numbers

Да се напише функция, която генерира всички двоични числа от 1 до n, използвайки опашка.

Пример:

n = 10 ➡ 1 10 11 100 101 110 111 1000 1001 1010
