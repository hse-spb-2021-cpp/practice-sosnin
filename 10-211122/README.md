# Общее
Цель занятия: сделать приложение с плагином в виде разделяемой библиотеки (shared library) с использованием Boost.DLL.

Установите себе Boost и начните выполнять упражнения заранее.
Boost будет долго скачиваться и устанавливаться.

Если возникают проблемы — обращайтесь к преподавателю, чат оперативной помощи или во флудилку.

# Boost
Для работы вам потребуется установить себе библиотеку Boost и научиться её подключать при компиляции.
Способ подключения будет разный для разных компиляторов и/или сред разработки.

Boost (как и любая библиотека для C++) состоит из двух больших кусков:

1. Заголовочные файлы. Они сами адаптируются под ОС и компилятор в процессе компиляции.
   У Boost обычно все заголовки ставятся одним скопом.
2. Скомпилированные в статическую библиотеку объектные файлы.
   Не все части Boost требуют объектные файлы (такие называются "header-only").
   А те, кто требует, обычно предоставляют отдельную статическую библиотеку: например, `boost_filesystem` и `boost_system`.

Вам точно требуется установить заголовочные файлы и статические библиотеки для Boost.Filesystem и Boost.System.
Если хотите, можете установить вообще все статические библиотеки Boost одним скопом, но они могут занять пару гигабайт.

Инструкции по установке для разных систем есть на Wiki.
Крайне рекомендуется устанавливать через пакетный менеджер, но для Visual Studio под Windows такой опции,
к сожалению, нет — придётся ставить и настраивать вручную.

## Ручная настройка компилятора
Это не требуется, если вы установили Boost через пакетный менеджер.

После установки вам требуется найти две папки:

* `BOOST_ROOT`: в ней лежит папка `boost`, в которой лежат заголовки вроде `version.hpp`.
* `BOOST_LIBRARY_DIRS`: в ней лежат скомпилированные файлы с именами вроде `libboost_filesystem.a` или `boost_filesystem.lib` или более сложными.
  Обычно `BOOST_LIBRARY_DIRS` лежит в `BOOST_ROOT` с названием `lib`.

Обычно надо добавить в компилятор три настройки:

1. Путь поиска заголовочных файлов (здесь `/foo/bar/baz` — полный путь к `BOOST_ROOT`):
    * GCC/Clang: `-I/foo/bar/baz`
    * [Visual Studio](https://docs.microsoft.com/en-us/cpp/build/reference/i-additional-include-directories?view=msvc-160):
      `/I /foo/bar/baz` (консоль) или добавить `/foo/bar/baz` в Additional Include Directories (графический интерфейс).
2. Путь поиска статических библиотек (здесь `/foo/bar/baz` — полный путь к `BOOST_LIBRARY_DIRS`):
    * GCC/Clang: `-L/foo/bar/baz`
    * [Visual Studio](https://docs.microsoft.com/en-us/cpp/build/reference/libpath-additional-libpath?view=msvc-160):
      `/libpath:/foo/bar/baz` после [разделителя `/link`](https://docs.microsoft.com/en-us/cpp/build/reference/compiler-command-line-syntax?view=msvc-160) (регистр важен)
      или добавить `/foo/bar/baz` в Additional Library Directories (графический интерфейс).
3. Для GCC/Clang также требуется явно написать, какие статические библиотеки подключать при помощи ключа `-lLIBRARY`,
   где строчку `LIBRARY` вы узнаете ниже.
   Для Visual Studio это не требуется.
   Чтобы узнать строчку `LIBRARY`:
   1. Найдите в папке `BOOST_LIBRARY_DIRS` файл с подстрокой `boost_filesystem` в названии
   1. Если файлы называются по-другому, попросите помощи.
   1. Если есть несколько файлов, то при наличии выбора выбирайте:
      * Без `.dll` или `.so` в названии (чтобы была статическая линковка)
      * С `mt` в названии (чтобы работало в многопоточных приложениях, нам это пригодится в конце семестра)
   1. Файл должен начинаться с `lib` и заканчивается на `.a`, это название статической библиотеки в стиле Linux.
      Отбросьте префикс и суффикс, результат — строчка `LIBRARY`.
      Например: `boost_filesystem`, `boost_filesystem-mt`.

Примеры:

* `g++-10 main.cpp -I/foo/bar/baz -L/foo/bar/baz/lib -lboost_filesystem-wtf`
* `cl main.cpp /I /foo/bar/baz /link /libpath:/foo/bar/baz/lib`

## Популярные проблемы
### Visual Studio: `fatal error LNK1104: cannot open file '...-x32-.lib'`
Вероятно, вы пытаетесь компилировать 32-битным компилятором, но поставили 64-битный Boost.
Либо установите 32-битный Boost, либо переключитесь на 64-битную компиляцию:
в графическом интерфейсе выберите цель сборки `x64` вместо `x86`,
в консоли запускаете `cl` из [`x64 Native Tools Command Prompt`](https://docs.microsoft.com/en-us/cpp/build/how-to-enable-a-64-bit-visual-cpp-toolset-on-the-command-line)
вместо обычного `Developer Command Prompt`.

### Visual Studio: `fatal error LNK2019: unresolved external symbol "...throw_exception..."`
В Boost для обработки ошибок используется механизм исключений, в Visual Studio он из-за совместимости со старыми Visual Studio работает по-другому.
Включите стандартный режим ключом [`/EHsc` в начале командной строки или настройкой "Enable C++ Exceptions" в интерфейсе](https://docs.microsoft.com/en-us/cpp/build/reference/eh-exception-handling-model?view=msvc-160).

# Упражнения
Сначала научитесь выполнять упражнения **без CMake и CLion**.
Приступайте к ним только после того, как всё получилось.

## `01-boost-header-only`
Скомпилируйте и запустите код без CMake, он должен вывести `All OK`.
Если у вас слишком новый Boost, будет `WARNING` при запуске.

В этом упражнении проверяется, что вы корректно установили заголовочные файлы.
Линковать с библиотеками не требуется.

Если вы ставите Boost вручную, а не через пакетный менеджер (`pacman`, `brew`), вам потребуется научить компилятор искать заголовки (смотри выше).

## `02-boost-link-filesystem`
Скомпилируйте и запустите код без CMake, он должен вывести `All OK`.

В этом упражнении проверяется, что вы умеет линковать с библиотеками.
Надо слинковать с библиотекой `boost_filesystem`.
Для GCC/Clang это отдельный параметр (смотри выше), для Visual Studio всё произойдёт автоматически.

Если вы ставите Boost вручную, а не через пакетный менеджер (`pacman`, `brew`), вам потребуется научить компилятор искать библиотеку (смотри выше).

## `03-boost-dll` (часть I)
Скомпилируйте три `.cpp` независимо друг от друга без CMake:

* `main.cpp` — в исполняемый файл `main`. Потребуется слинковать с `boost_filesystem`.
* `plugin_a.cpp` — в разделяемую библиотеку `liba.so` (Linux), `a.dll` (Windows), `liba.dylib` (macOS).
* `plugin_b.cpp` — в разделяемую библиотеку `libb.so`/`b.dll`/`libb.dylib`.

Чтобы собрать разделяемую библиотеку вместо исполняемого файла, добавьте ключ компилятору:

* GCC/Clang: `-shared` обязательно.
  Также лучше добавить флаги `-fPIC` (генерация position-independent-code) и `-fvisibility=hidden`,
  иначе на некоторых системах могут быть странные ошибки и/или предупреждения.
* Visual Studio: [`/DLL`](https://docs.microsoft.com/en-us/cpp/build/reference/dll-build-a-dll?view=msvc-170) после `/link`
  или смените Configuration Type на `Dynamic Library (.dll)` в интерфейсе.

При запуске `./main путь-до-библиотеки-a` (например, `main a.dll`) должно напечататься `value=123`,
а при запуске с другим плагином в качестве аргумента — `value=456`.

## Сборка через CMake/CLion
Если хотите, попробуйте сделать всё то же самое при помощи CMake/CLion.
За основу возьмите `CMakeLists.txt` с лекции.

Если CMake не может найти библиотеку Boost — укажите ему параметр `-DBOOST_ROOT=/foo/bar/baz`, где `/foo/bar/baz` — папка `BOOST_ROOT`.

Если возникает предупреждение `New Boost version may have incorrect or missing dependencies and imported targets` — у вас либо слишком старый CMake,
либо слишком новый Boost: CMake не уверен, какие зависимости у каких библиотек нужны, но попробует угадать.
Можно проигнорировать, если всё скомпилировалось.

## `03-boost-dll` (часть II)
1. Создайте файл `secret_api.h` по образу и подобию `api.h`
   В нём должен быть абстрактный класс с одним виртуальным методом, возвращающим секретный `float`.
2. В `plugin_b.cpp` (но не в `plugin_a.cpp`) добавьте реализацию этого секретного класса, которая возвращает `531.5`.
  Опубликуйте глобальную переменную такого типа с каким-нибудь новым названием (не `plugin`, чтобы не было пересечений).
3. В `main.cpp` допишите код, который проверяет, есть ли в плагине секретная переменная из предыдущего пункта,
   и если есть — вызывает её виртуальный метод и выводит на экран секретное значение.
   Иначе выводит `no secret found`.

Теперь при запуске на `b.dll` вывод должен получиться таким:

```
value=456
secret=531.5
```

а при запуске на `a.dll` программа должна падать.

## `10-add-virtual`
У вас есть два класса-наследника, из которых можно собрать арифметическое выражение с константами и плюсиками
в виде [абстрактного синтаксического дерева](https://ru.wikipedia.org/wiki/%D0%90%D0%B1%D1%81%D1%82%D1%80%D0%B0%D0%BA%D1%82%D0%BD%D0%BE%D0%B5_%D1%81%D0%B8%D0%BD%D1%82%D0%B0%D0%BA%D1%81%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B5_%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE) (abstract syntax tree, AST):
каждое выражение — это либо константа-литерал (`literal`), либо сумма двух выражений (`sum`).

Уже есть виртуальный метод `evaluate()`.
Добавьте методы `to_string()` и `to_string_spaced()`.

Убедитесь, что пришлось изменить все три класса: базовый и двух наследников.

## `11-add-free-function`
Решаем ту же задачу, что и в предыдущем упражении, но другим способом.

Добавьте свободные функции `to_string(expr)` и `to_string_spaced(expr)`,
которые при помощи `dynamic_cast` определяют, что делать со своим параметром.

Убедитесь, что вам не пришлось никак менять существующий код,
только дописать новую функцию.

## `12-add-visitor`
Решаем ту же задачу, что и в предыдущем упражении, но другим способом.

Допишите недостающие куски паттерна `visitor`.
Вам придётся обновить все три класса.

Добавьте класс `to_string_visitor`, соответствующий операции `to_string` из предыдущего упражнения.
Будем считать, что результат он хранит в своём публичном поле `std::string result;`.

Теперь допишите аналогичный класс `to_string_spaced_visitor`.
Убедитесь, что вам не пришлось никак менять существующий код, только дописать нового наследника.

## `20-boost-dll-has`
Это продолжение задания `03-boost-dll`.
Возьмите своё решение оттуда.

Воспользуйтесь классом [`boost::dll::shared_library`](https://www.boost.org/doc/libs/1_71_0/doc/html/boost/dll/shared_library.html)
и его методам `has`, чтобы перед обращением к секретной глобальной переменной в плагине проверить, что она есть.
Иначе выведите `no secrets`.

Теперь при запуске на `b.dll` вывод не изменился, а при запуске на `a.dll` получился такой:

```
value=123
no secrets
```