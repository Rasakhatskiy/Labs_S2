## Лаба 1  
5. Інформація про повідомлення у децентралізованій соціальній мережі (є
багато серверів, на кожному сервері до 40000 користувачів,
повідомлення в рамках одного серверу). Для кожного повідомлення
зберігаються такі дані: текст повідомлення; точна дата і час
відправлення повідомлення; користувач-автор повідомлення; адресат
повідомлення (існує спеціальний адресат, що позначає повідомлення
для всіх); тип повідомлення – новини, питання, відповідь на питання,
запрошення на подію, коментар до іншого повідомлення; оцінка
повідомлення від системи боротьби зі спамом (дійсне невід’ємне
число, чим ближче до 0 – тим менше шансів, що це спам). Критерії
пошуку:
c. Повідомлення, що містять заданий фрагмент тексту;
повідомлення з оцінкою у заданому діапазоні від заданого
автора; повідомлення заданого типу, надіслані до заданого часу.  

## Лаба 2 A
Реалізувати структуру даних «циклічний список» з наступними операціями: 
1) create_empty – створення пустого списку;  
2) insert – вставка елементу перед елементом з індексом k;  
3) remove – видалення елементу з індексом k;   
4) get, set – доступ до елементу за індексом.  

В структурі зберігаються точки у тривимірному просторі (дійсні координати)

## Лаба 2 B
Лабораторні роботи 2a та 2b є двома частинами однієї лабораторної (присвяченої спискам), тому треба виконувати обидві частини для отримання повних балів.
Ця лабораторна робота складається з кількох задач, які помічені зірочками відповідно до складності (*) – більш прості задачі, (**) – задачі середньої складності, (***) – більш складні задачі. Необхідно реалізувати одну чи декілька задач, виходячи з наступних критеріїв:
1.	Для студентів, що претендують на мінімум 60 балів за предмет (оцінка «задовільно») – сумарна складність мінімум (*).
2.	Для студентів, що претендують на мінімум 75 балів за предмет (оцінка «добре») – сумарна складність мінімум (**).
3.	Для студентів, що претендують на мінімум 80 балів за предмет (оцінка «добре») – сумарна складність мінімум (**), не менше однієї задачі складності не менше (**).
4.	Для студентів, що претендують на мінімум 85 балів за предмет (оцінка «добре») – сумарна складність мінімум (***), не менше однієї задачі складності не менше (**).
5.	Для студентів, що претендують на мінімум 90 балів за предмет (оцінка «відмінно») – сумарна складність мінімум (****), не менше однієї задачі складності не менше (**).
6.	Для студентів, що претендують на мінімум 95 балів за предмет (оцінка «відмінно») – сумарна складність мінімум (*****), не менше однієї задачі складності (***).
Можна реалізувати більше задач і отримати за це додаткові бали, проте працює схема diminishing returns – якщо реалізувати вдвічі більше задач, то кількість балів буде менш ніж вдвічі більшою. 
Деякі з задач є досить близькими за формулюваннями. Якщо один студент реалізує кілька схожих задач – в сумарну кількість зірочок зараховується лише одна з них, з найбільшою кількістю зірочок. Інші реалізовані задачі можуть впливати на додаткові бали.
В задачах, де треба реалізувати якусь структуру даних, і не вказано, яку саме реалізацію використати – можна використати реалізацію на основі вже реалізованої лабораторної 2а. В задачах зі складністю (*) та (**) передбачається реалізація на основі зв’язних списків, в задачах зі складністю (***) можна обрати самостійно найбільш доцільну реалізацію списків (в тому числі можна використовувати бібліотечні реалізації). Не обов’язково робити кілька різних реалізацій – проте можна так зробити і порівняти їх, за це будуть виставлені додаткові бали.
Кожна задача може бути реалізована окремою програмою. Також можна реалізувати одну програму, яка дозволяє викликати будь-яку з реалізованих задач. Проте різні задачі мають бути чітко розділені як в коді, так і в інтерфейсі користувача. Необхідно реалізувати наступні режими роботи для кожної задачі: 
1.	Інтерактивний діалоговий режим – коли користувач може вибирати, які операції виконувати та задавати необхідні параметри. 
2.	Демонстраційний режим – задаються фіксовані значення та послідовності виконання операцій, що демонструють правильність роботи структур даних та операцій в різних ситуаціях. В цьому режимі користувач не має нічого вводити. 
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
14.	(**) Реалізувати структуру даних «черга з пріоритетами» 
(Priority Queue) на основі зв’язного списку. 
Під час додавання елементів вказується значення та пріоритет. 
Елементи з меншим значенням пріоритету вставляються раніше за елементи з більшим значенням. 
Елементи з однаковим значенням вставляються в порядку додавання. 
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
24.	(***) Реалізувати структуру даних «список з CDR кодуванням» 
(CDR coding, див. наприклад https://en.wikipedia.org/wiki/CDR_coding ). 
Операції стандартні для списків – обхід, додавання елементу (в кінець, 
початок або довільну позицію), видалення елементу, доступ за індексом, пошук за значенням.