# АСПЗ

## Практична робота №12-13, Варіант 7

Був використаний запуск shell скриптів для швидкої компіляції та тестування програми.

---

### 12-13.1 — Обробка SIGINT

#### Умова

```c
#include <signal.h>
#include <stdio.h>

void handle_sigint(int sig) {
    printf("Caught signal %d\n", sig);
}

int main() {
    signal(SIGINT, handle_sigint);
    while (1) {} // нескінченний цикл
}
```

#### Скріншоти

![screenshot](https://github.com/KostyaKindaluk/practice-12-13/blob/master/task1/screenshot.png)

---

### Варіант 7 — Обробка помилок з метою правильного завершення програми

#### Умова

Реалізуйте сигналобезпечну функцію обробки помилки, яка намагається коректно завершити роботу з усіма ресурсами, включаючи сокети, тимчасові файли та потокові буфери.

### Опис рішення

Програма обробляє сигнали SIGINT та SIGTERM, забезпечуючи коректне завершення: закриває сокет (/dev/null), видаляє тимчасовий файл, скидає буфери виводу. У сигналобезпечному обробнику (signal_handler) використовуються лише безпечні функції (write, close, _exit). Основна функція встановлює обробники сигналів, відкриває ресурси та імітує роботу у циклі. Завершення завжди відбувається через cleanup_and_exit() або _exit(), залежно від контексту.

#### Скріншоти

![screenshot](https://github.com/KostyaKindaluk/practice-12-13/blob/master/variant7/screenshot.png)

---