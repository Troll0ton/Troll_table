# Hash_table
Данный проект нацелен на изучение принципов работы хэш-таблиц, сравнение различных хэш-функций и изучение их поведения на конкретных наборах данных, развитие практических навыков при работе с профайлингом, в применении оптимизаций на различных уровнях. Важной составляющей исследовательской работы является написание README, объёмно отражающей ход проделанной на всех этапах работы.

![kek](https://github.com/Troll0ton/Hash_table/tree/main/images/kek.jpg)

---

## Первая часть
Первая часть проекта посвящена изучению работ различных хэш-функций и выявление их преимуществ и недостатков. Необходимо исследовать поведение хэш-функций на примере работы с текстом и проанализировать число коллизий в каждом отдельном случае. Все хэш-функции проверяются на тексте трагедии Уильяма Шекспира "Трагическая история о Гамлете, принце датском", представленном на анлийском языке.

### Теория
В моем проекте используется открытое хэширование, которое представляет из себя работу со списками. Открытое хеширование или Метод цепочек – это технология разрешения коллизий, которая состоит в том, что элементы множества с равными хеш-значениями связываются в цепочку-список (можно почитать про это здесь https://intuit.ru/studies/courses/648/504/lecture/11467?page=3):

![hash][hash]

[hash]: https://github.com/Troll0ton/Hash_table/tree/main/images/hash.jpg

---

### Сравнение хэш-функций
Для проведения сранения были выбраны 7 различных хэш-функий, отличающихся своими подходами к хэшированию данных:

---

### const hash function
Данная функция всегда возвращает 1 при любых вводных данных. Очевидно, что число коллизий в данном случае максимально, так как используется только один список из всей хэш-таблицы. Данный пример отражает нижнюю оценку работы всех возможных хэш-функций. Будет с чем сравнить)

```c++
unsigned int constHf (char *line)
{
    return 1;
}
```

![hf1][hf1]

[hf1]: https://github.com/Troll0ton/Hash_table/tree/main/images/hf1.png

### first symbol hash function
Данная функция возвращает ASCII-код первого символа всей строки. Число коллизий уменьшено по сравнению с предыдущей функцией. По ниже приведенному графику несложно догадаться, что максимумы обусловлены лишь фонетическими особенностями исходных данных. Все зависит от распространнености слов, начинающихся с определенных букв, что при особенностях работы с текстом, приводит к большому числу коллизий в отдельных вёдрах.

```c++
unsigned int firstSymHf (char *line)
{
    return (line[0] % hash_size);
}
```

![hf2][hf2]

[hf2]: https://github.com/Troll0ton/Hash_table/tree/main/images/hf2.png

### length hash function
Данная хэш-функция возвращает длину получаемой строки. Заметим, что все записи лежат в самых первых вёдрах, а остальные - пусты. Это обусловлено тем, что длина слов во входном тексте (в языке) варьируется в этой области. Неэффективно, но все же лучше первой функции.  

```c++
unsigned int lenHf (char *line)
{
    return (strlen (line) % hash_size);
}
```

![hf3][hf3]

[hf3]: https://github.com/Troll0ton/Hash_table/tree/main/images/hf3.png

### sum hash function
Данная хэш-функция возвращает сумму всех ASCII-кодов символов, взятой по модулю размера хэш таблицы. Опять же, работа данной хэш функции сильно будет зависеть от длин слов в исходном тексте, и при больших размерах хэш-таблиц это привёдет к малой заселенности последних вёдер. Но пока это самая лучшая хэш-функция из представленных ранее. 

```c++
unsigned int sumHf (char *line)
{
    unsigned int hash_sum = 0;
    unsigned int line_len = strlen (line);

    for(unsigned int i = 0; i < line_len; i++)
    {
        hash_sum = (hash_sum + line[i]);
    }

    return (hash_sum % hash_size);
}
```

![hf4][hf4]

[hf4]: https://github.com/Troll0ton/Hash_table/tree/main/images/hf4.png

### right cycle rotate hash function
Эти и последующие хэш-функции являются наиболее эффективными, так как они позволяют избежать совпадения возвращаемых значений для почти одинаковых слов, максимально неочевидны в получении результата. Изучение поведения работ таких хэш-функций требует полное исследование принципов, на которых они основаны. Но такие хэш-функции позволяют распределить записи равномерно по хэш-таблице.

```c++
unsigned int roundRightHf (char *line)
{
    unsigned int hash_sum = 0;
    unsigned int line_len = strlen (line);

    for(unsigned int i = 0; i < line_len; i++)
    {
        hash_sum = (hash_sum >> 1) | (hash_sum << (32 - 1));
        hash_sum ^= line[i];
    }

    return (hash_sum % hash_size);
}
```

![hf5][hf5]

[hf5]: https://github.com/Troll0ton/Hash_table/tree/main/images/hf5.png

### left cycle rotate hash function
Данная функция не отличается идейно от предыдущей, но на проверяемых мною данных показала лучший результат. Прослеживается зависимость числа коллизий от выбора направления циклического вращения. (слева-направо и справа-налево соответсвенно - увеличивается число коллизий). Также заметно, что влияние циклических экстремумов на распределение уменьшено. 

```c++
unsigned int roundLeftHf (char *line)
{
    unsigned int hash_sum = 0;
    unsigned int line_len = strlen (line);

    for(unsigned int i = 0; i < line_len; i++)
    {
        hash_sum = (hash_sum << 1) | (hash_sum >> (32 - 1));
        hash_sum ^= line[i];
    }

    return (hash_sum % hash_size);
}
```

![hf6][hf6]

[hf6]: https://github.com/Troll0ton/Hash_table/tree/main/images/hf6.png

### super secret hash function
Проект включает и изучение работы собственно предложенной хэш-функции. Мною была выбрана полиномиальная хэш функция, которая основана на принципах хэш-суммы, но при этом вычисляется значение многочлена с заданными коэффициентами (символы в строке). Этот пример является лучшим из всех предыдущих, но и left cycle rotate hash function не сильно от него остает. 

```c++
unsigned int superSecretHf (char *line)
{
    unsigned int hash_sum = 0;
    unsigned int hash_par = 1;
    unsigned int hash_base = hash_size + 1;
    unsigned int line_len = strlen (line);

    for(unsigned int i = 0; i < line_len; i++)
    {
        hash_sum += (unsigned int) (line[i]) * hash_par;
        hash_par *= hash_base;
    }

    return (hash_sum % hash_size);
}
```

![hf7][hf7]

[hf7]: https://github.com/Troll0ton/Hash_table/tree/main/images/hf7.png

---

## Вторая часть
Вторая часть моей работы посвящена работе с профайлером и поиском-применением оптимизаций в нужных местах. Я использовал valgrind (профайлер) в качестве инструмента для сбора информации по исполнению, callgrind для ее наглядного представления и изучения. Чтобы исключить влияние остальных частей программы, поиск конкретных элементов производился three hundred раз. В этом случае это позволяло максимально полно отразить картину работы поиска записи в хэш-таблице.

---

### Применение AVX-инструкций
При проведении первого исследования работы программы, оказалось, что большего всего времени тратилось на сравнение текущей и требуемой строк:

![type1][type1]

[type1]: https://github.com/Troll0ton/Hash_table/tree/main/images/type1.png

Чтобы ускорить этот процесс было решено перевести исходные данные в 256-битный формат. Это позволило использовать соответсвующие SIMD-инструкции и регистры для сравнения строк: 

```c++
int strcmpAvx (const char *s1, const char *s2)
{
    __m256i *s1_vector = ( __m256i* ) s1;
    __m256i *s2_vector = ( __m256i* ) s2;

    __m256i cmp = _mm256_cmpeq_epi8 (*s1_vector, *s2_vector);
    int cmp_mask = _mm256_movemask_epi8 (cmp);

    if(cmp_mask == equal_mask) 
    {
        return 0;
    }

    return 1;
}
```

| режимы        | число м. команд    | ускорение          |
| ------------- | ------------------ | ------------------ |
| NO AVX        | 5765331050         | 1.0                |
| AVX           | 4215002668         | 1.36               |

После проведения соответсвующих оптимизаций скорость работы программы увеличилась на 30 процентов. 

Оказалось, что для удобной и красивой обработки входных данных достаточно преобразовать исходные данные так, что в дальнейшем с ними было удобно оперировать. Хотя и время, которое тратится на преобразование входных данных увеличилось, время работы программы уменьшилось. Так работает закон Амдала. Таким образом, нам опять пригодилось использование AVX-инструкций, которые хорошо подходят для обработки большого числа данных.

### Ассемблерные функции.
На следующем этапе оказалось, что больше всего стала весить хэш-функция. 

![type2][type2]

[type2]: https://github.com/Troll0ton/Hash_table/tree/main/images/type2.png

Было решено преписать ёё в ассемблерном виде и вызывать её уже в самой программе. 

```
_trollohash:  
            push rbp								 	
            mov rbp, rsp
            push rbx                            ; rdi - ptr to curr str 
            xor r11, r11
            mov rbx, 1001
            mov rcx, 1

.next:      xor rax, rax
            mov al, byte [rdi]
            cmp al, 0
            je .end
            mul rcx
            add r11, rax
            mov rax, rcx
            mul rbx
            mov rcx, rax
            inc rdi
            jmp .next

.end:
            mov rax, r11
            mov rbx, qword [rbp - 8]
            mov rsp, rbp                        ; skip local data
            pop rbp

            ret
```

Казалось, что компилятор не очень умный, и я смогу сделать функцию ещё быстрее. Но в итоге скорость работы программы уменьшилась:

![type3_asm][type3_asm]

[type3_asm]: https://github.com/Troll0ton/Hash_table/tree/main/images/type3_asm.png

| режимы        | число м. команд    | ускорение          |
| ------------- | ------------------ | ------------------ |
| NO ASM        | 4215002668         | 1.0                |
| ASM           | 4452129302         | 0.94               |

Не всегда попытки оптимизаций оканчиваются успехом, особенно если мы пытаемся использовать функции, написанные на ассемблере.

### Использование интрисиков
Чтобы попытаться максимально ускорить работу хэш функций, было принято решение использовать интринсики. В частности, попробуем использовать CRC32:

```c++
unsigned int Crc32hf (char *line)
{
    __m256i *line_vector = (__m256i*) line;

    int hash_sum = 0;

    hash_sum = _mm_crc32_u64 (hash_sum, _mm256_extract_epi64 (*line_vector, 3));
    hash_sum = _mm_crc32_u64 (hash_sum, _mm256_extract_epi64 (*line_vector, 2));
    hash_sum = _mm_crc32_u64 (hash_sum, _mm256_extract_epi64 (*line_vector, 1));
    hash_sum = _mm_crc32_u64 (hash_sum, _mm256_extract_epi64 (*line_vector, 0));
    
    return hash_sum;
}
```

![type4][type4]

[type4]: https://github.com/Troll0ton/Hash_table/tree/main/images/type4.png

Использование такой хэш функции на преобразованных в 256-битный формат похволило ускорить работу функции почти в два раза.

| режимы        | число м. команд    | ускорение          |
| ------------- | ------------------ | ------------------ |
| NO CRC32      | 4215002668         | 1.0                |
| CRC32         | 2729766089         | 1.54               |


---

### Вывод

В данной работе были исследованы устройство хэш-таблиц, работы хэш-функций, было проведено их сравнение. Также активно проводился анализ работы программы через профайлер, изучено влияние отдельных компонентов программы. Главным выводом из проделанной работы является тот факт, что выгодно преобразовать данные так, чтобы их можно было удобнее обрабатывать. На текущей задаче были использованы SIMD-инструкции, которые позволили ускорить программу в 2.1 раз. 

![lol][lol]

[lol]: https://github.com/Troll0ton/Hash_table/tree/main/images/lol.jpg "me after hash-table laba"
...


 
