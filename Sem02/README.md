# Семинар №2 по СДА - Определяне на сложност на алгоритми. Решаване на задачи.

Определете сложността:

```c++
void f(vector<int>& arr) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += arr[0];
    }
}
```

```c++
void f(vector<int> arr) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += arr[0];
    }
}
```

```c++
void f(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        for (int j = n - i + 5; j <= n; j++)
            cout << 1;
    }
}
```

```c++
void f(vector<int>& arr) {
    int n = arr.size();
    for (int i = n - 1; i >= 0; i /= 7) {
        cout << 1;
    }
}
```

```c++
void f(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        cout << 1;
    }
    for (int i = 1; i > n; i *= 2) {
        cout << 1;
    }
}
```

```c++
int f(int n) {
    if (n <= 0)
        return 0;
    return 1 + f(n - 1);
}
```

```c++
int f(int n) {
    if (n <= 0)
        return 0;
    return 1 + f(n/2);
}
```
