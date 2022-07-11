# Robocross
АННОТАЦИЯ

Проект был создан для участия в РОБОКРОСС 2022 - ежегодные всероссийские испытания беспилотного транспорта. Проект создан при поддержке Донского государственного технического университета и структурного подразделения Ресурсного Центра Робототехники (РЦР). Работа была начата в октябре 2021 года на серийном автомобиле ВАЗ-1111, а в марте 2022 года университетом был предоставлен серийный автомобиль более нового образца - Лада гранта. Так как автомобиль необходимо собрать, в рамках соревнований, беспилотным, то были проведены следующие работы: автономность поворота электроусилителя руля(ЭУРа), автономность системы нажатия педалей (сцепление, газ, тормоз), автономность механической коробки передач. 
Проект для управления всей периферией, за исключением рулевого, был создан с использованием операционной системой реального времени - FreeRTOS. Были использованы наброски самодельной периферийной библиотеки для микроконтроллера STM32, которая имееет название FIL (Fast Initialization Library). Данные отправляются по последовательному интерфейску UART с использованием протокола ModBus ASCII.
______________________________________________________________________________________________________________________________

1. Начало 

Каждому члену нашей команды была отведена задача, которую необходимо реализовать, в рамках подготовки в всероссийским испытаниям беспилотного транспорта.
Мне, как программисту-разработчику нижнего уровня, необходимо было вести проект управления исполнительными элементами автомобиля. В число элементов входил педальный узел(сцепление, тормоз, газ), управление электроусилителем руля, управление механической коробкой передач и передача актуальных данных ЭВМ верхнего уровня.
Испытания проводились на серийном автомобиле Лада Гранта FL учебной комплектации с параллельным педальным узлом.
![CmmQlvBD8uk37-oiVmhUjIeTMFEuv8TjOS72Y_4P4vU-f_4QHIoWXfCxOsIcmFV7m69jP-LEAnb2WX9gmhC8HsLO](https://user-images.githubusercontent.com/91759086/178328498-c113d7da-5a7d-46d6-baa2-a3d285c33250.jpg)

С марта 2022 года была начата работа с электроусилителем руля. Использование стандартного блока управления накладывало множество трудностей с управлением в связи с тем, что ЭБУ автомобиля от подмены данных постоянно переходил в защищенное состояние с ошибкой, поэтому в рамках подготовки к соревнованиям было принято решение приостановить идею с таким типом управления. Был использован самодельный драйвер бесколекторного двигателя. Плата с наработки по программному обеспечению были предоставлены сотрудником дружественной лаборатории НИЛ ИЭСМиК Назаренко Дмитрием Владимировичем, за что я выражаю отдельную благодарность. В связи с договоренностью о нераспространении ПО рулевого управления, в данном проекте отсутстует программный код управления, только изображение стенда, на котором отлаживалась работа с электоуслителем руля. Принцип управления отталкивался от встроенных в двигатель двух датчиков холла. Получая с них данные, они преобразовывались в электрический угол рулевой рейки и подавались на вход ПИ-регулятора положения, для отработки заданного целевого угла поворота.

![image](https://user-images.githubusercontent.com/91759086/178329387-0888fb21-c78e-41d0-86f8-4fc4bb16544f.png)

2. Обмен данными с ЭВМ верхнего уровня

С конца мая началась работа по проектированию и написанию алгоритма управления остальными системами автомобиля. Первой нерешенной задачей было обеспечение обмена данными между ЭВМ и двумя периферийными устройствами: электроусилитель руля на контроллере dsPIC32EP64 и платой управления остальными системами на контроллере STM32F407. Для первичного проектирования был выбран протокол ModBus ASCII как наиболее удобный и наглядно показывающий структуру присылаемых данных. Код 0х06 предназначался для записи целевых значений, присылаемых с ПК, код на чтение 0х03 был предусмотрен, но впоследствии было принято решение сделать просто периодическую отправку текущего состояния в связи с загруженностью разработчика ПО верхнего уровня.

3. Управление механической коробкой передач

Управление КПП было реализовано через управление двумя двигателями постоянного тока. Так как, механика реализована ременной системой Core XY, то необходимым условием работы было поддержание одинаковой скорости двигателей. Был учтен тот факт, что даже одинаковые двигатели были куплены в один день, то не факт что их выходные характеристики будут идентичными. Поэтому был написан простой ПИД-регулятор скорости, который получал входные данные с угловых энкодеров магнитного типа AS5040. Итоговое управление передачей реализовано матричным способом - в матрице хранились значения направлений, по которым двигался селектор, а ключевыми отметками служили датчики холла. Приведен скриншот модели и изображение как было реализовано механическое исполнение. Управление коробкой передач осуществляется через функцию Set_Transmission(int transmission), тело которой находится в файле Car_Management.c

![image](https://user-images.githubusercontent.com/91759086/178335250-1f2487bd-1f0c-4023-a280-8e5804121554.png)
![image](https://user-images.githubusercontent.com/91759086/178335775-206e5586-5139-4fc2-9813-e9316a437fa1.png)

4. Управление педальным узлом

Комплект педалей инструктора, установленный в комплектации «учебная», состоит из механических педалей тормоза и сцепления. Для управления положением дроссельной заслонки была произведена модификация заводской электронной педали газа. Модифицированная педаль управляется шаговым двигателем, для контроля положения был использован таймер, настроенный на режим OPM (One Pulse Mode) для контроля за количеством посылаемых импульсов.

![image](https://user-images.githubusercontent.com/91759086/178336223-675bb1f7-c833-44d2-83ab-7a42889f328f.png)

Нажатие на педаль тормоза осуществляется пневмоцилиндром с демпфером  для регулировки скорости выдвижения штока. Бесперебойную работу привода тормозящего механизма обеспечивает пневморессивер, изготовленный из медицинского кислородного баллона, давление в котором поддерживается автомобильным пневматическим компрессором, оснащённым системой контроля давления в подключённом контуре. Компрессор включается автоматически для поддержания рабочего давления в баллоне. Управление тормозом осуществляется путем подачи постоянного сигнала на дроссель, с помощью макроопределения set_pin(). 

![image](https://user-images.githubusercontent.com/91759086/178336273-102059bb-6052-4ae2-93da-f08a10bfe1fb.png)
![image](https://user-images.githubusercontent.com/91759086/178336313-75395bad-d8b7-4080-8d60-5c210ea9d341.png)


Нажатие на педаль сцепления осуществляется шаговым двигателем, при помощи кулачка, закреплённого на выходном валу. Основанием для использования шагового двигателя является простота управления положением и возможность обеспечения равномерного усилия во всех положениях при различной скорости. Привод представлял собой тот же шаговый двигатель, но редукторного типа, поэтому для расчет перемещения был использован тот же режим таймера, но значение импульсов было отмасштабировано с учетом редукции.

![image](https://user-images.githubusercontent.com/91759086/178336674-5819243d-fddb-47b2-85bb-ef44722ea404.png)

5. Одометрия и расчет скорости движения

![image](https://user-images.githubusercontent.com/91759086/178339724-75469d24-cc35-4beb-b042-e1cd469c7c01.png)
![image](https://user-images.githubusercontent.com/91759086/178339756-054c044d-0793-4e26-8f90-d5a23a9d1811.png)

Для должного функционирования симуляции верхнего уровня ПО необходимо вести расчеты перемещения транспортного средства. Первоначальный вариант был реализован в виде простого расчета скорости - количество задетых магнитов перемеденное в перемещение поделить на время фиксации(10 Гц = 0,1 с). При отладке и тестировании были проблемы с точностью поскольку такой расчет не мог быть применим к малым перемещениям. Поэтому был реализована модификация расчета - был использован таймер, настроенный на режим захвата фронта (PWM Input Capture) по которому определялась длина импульса и масштабировалась для расчета в метрах в секунду. Все наработки по данному сектору можно ознакомиться в файле Car_Regulator.с. Для универсальности были оставлены в финальном программном коде оба варианта.

6. Структура ПО. Общий взгляд

Данные раздел был вынесен не на первый план для опционального дополнения. Для наглядности работы проекта был сделана диаграмма работы алгоритма в обших чертах. Она содержит основные блоки обработки входящих пакетов, периодическая отправка текущего состояния скорости автомобиля, а также команды на непосредственно КПП и педальный узел.

![робокросс](https://user-images.githubusercontent.com/91759086/178346902-595ccda9-6f64-49ba-aff1-9f38ef380de0.png)

Разработанное ПО нижнего уровня структуризировано и объединено с использованием технологии продвинутого программирования - операционной системы реального времени (ОСРВ) для микроконтроллеров FreeRTOS. Изучение данной операционной системы было произведено заранее, в сентябре 2021 года, поэтому настройка и отладка запуска работы не заняло существенного количества времени. Данное нововведение в проектах команды было использовано впервые, чтобы получить практические навыки в работе с ОС для микроконтроллеров и обеспечить максимальное быстродействие и безопасность системы.
При разработке подобной структуры появился ряд проблем, связанный с грамотной организации ОС микроконтроллера. В том числе, распределение приоритетов и параллелизма выполнения задач. Связано это с тем, что разработка требует много затрат трудовых и временных ресурсов в общем, и, поэтому, использование FreeRTOS в данном проекте - это и отличная возможность расширить опыт работы с многопоточностью на практике, помимо чтения литературы и разработки малых проектов.

7. Итоги

Приняв участие в 2022 году 4-8 июля во всероссийских испытаниях беспилотного транспорта нашей команде удалось занять третье место в таблице лидеров. Были множество проблем, в том числе с выведенным из строя сканирующим датчиком, но это не помешало показать достойный результат. Испытания на полигоне показали эффективность и безотказность работы операционной системы, несмотря на наличие проблем с отладкой на полигоне. Планируется использование операционной системы в других проектах, а также модификация транспортного средства, однако, работа на этот год и её отчет закончены. Спасибо за внимание, с вами была команда Ресурсного центра робототехники ДГТУ.

![e6f5fcc1-9c15-4db3-80fd-fa21faa51ff0](https://user-images.githubusercontent.com/91759086/178348507-a6dad4d4-5894-47aa-9b6d-2f1542d6e738.jpg)
